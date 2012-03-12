#include <windows.h>
#include <stdio.h>

LPVOID g_pfWriteFile = NULL;
CREATE_PROCESS_DEBUG_INFO g_cdpi;
BYTE g_opINT3 = 0xCC;
BYTE g_OrgByte = 0;


void DebugLoop(void);
BOOL OnCreateProcessDebugEvent(LPDEBUG_EVENT pEvent);
BOOL OnExceptionDebugEvent(LPDEBUG_EVENT pEvent);
void init_arg(PDWORD);



int main(void)
{
    DWORD pid;
    init_arg(&pid);

    if(DebugActiveProcess(pid))
    {
        DebugLoop();
    }
    else
    {
        printf("DebugActiveProcess fail\n");
    }

    return 0;
}


void DebugLoop(void)
{
    DEBUG_EVENT event;
    DWORD dwContinueStatus;

    while(WaitForDebugEvent(&event, INFINITE))
    {
        dwContinueStatus = DBG_CONTINUE;

        // attach event 
        if(event.dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT)
        {
            OnCreateProcessDebugEvent(&event);
        }
        else if(event.dwDebugEventCode == EXCEPTION_DEBUG_EVENT)
        {
            if(OnExceptionDebugEvent(&event))
                continue;
        }
        else if(event.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
        {
            // debuggee 종료 -> debugger 종료
            break;
        }

        // dwContinueStatus
        // DBG_CONTINUE 정상적으로 처리된 경우
        // DBG_EXCEPTION_NOT_HANDLED 어플리케이션의 SEH에서 처리하기 원할 때
        ContinueDebugEvent(event.dwProcessId, event.dwThreadId, dwContinueStatus);
    }
}


BOOL OnCreateProcessDebugEvent(LPDEBUG_EVENT pEvent)
{
    g_pfWriteFile = GetProcAddress(GetModuleHandle("kernel32.dll"), "WriteFile");

    g_cdpi = pEvent->u.CreateProcessInfo;


    // Debug Method가 아니면 OpenProcess()를 통해서 해당 프로세스의 핸들을 얻는다
    ReadProcessMemory(g_cdpi.hProcess, g_pfWriteFile, &g_OrgByte, sizeof(g_OrgByte), NULL);

    WriteProcessMemory(g_cdpi.hProcess, g_pfWriteFile, &g_opINT3, sizeof(g_opINT3), NULL);

    return TRUE;
}

BOOL OnExceptionDebugEvent(LPDEBUG_EVENT pEvent)
{
    CONTEXT ctx;
    PBYTE buf = NULL;

    PEXCEPTION_RECORD pExcpRecord = &pEvent->u.Exception.ExceptionRecord;

    DWORD param2_buf, param3_size;

    // BREAKPOINT가 맞는지 확인 
    // BREAKPOINT 지점이 WriteFile이 맞는지 확인
    // UnHook : 0xCC 원래 값으로 복원
    // context를 얻는다
    // WriteFile의 debugee buffer의 주소값!!, buffsize를 얻는다 ESP+0x8(param  2) ESP + 0xC(param 3)
    // buffer조작 param2에 WriteProcessMemory
    // eip - 1
    
    // SetThreadContext
    // ContinueDebugEvent(DBG_CONTINUE)
    // Sleep()
    // Hook : 0xCC

    if(pExcpRecord->ExceptionCode == EXCEPTION_BREAKPOINT)
    {
        if(g_pfWriteFile == pExcpRecord->ExceptionAddress)
        {
            WriteProcessMemory(g_cdpi.hProcess, g_pfWriteFile, &g_OrgByte, sizeof(g_OrgByte), NULL);

            ctx.ContextFlags = CONTEXT_CONTROL;
            GetThreadContext(g_cdpi.hProcess, &ctx);

            ReadProcessMemory(g_cdpi.hProcess, (LPVOID)(ctx.Esp + 0x8), &param2_buf, sizeof(param2_buf), NULL);
            ReadProcessMemory(g_cdpi.hProcess, (LPVOID)(ctx.Esp + 0xC), &param3_size, sizeof(param3_size), NULL);

            
            ///////// WriteFile의 버퍼를 임시 버퍼에 복사
            buf = (PBYTE)malloc(param3_size + 1);
            memset(buf, 0, param3_size + 1);
            ReadProcessMemory(g_cdpi.hProcess, (LPVOID)param2_buf, buf, param3_size, NULL);
            printf("\n### original string : %s\n", buf);
            for(int i=0; i < param3_size; ++i)
            {
                if(0x61 <= buf[i] && buf[i] <= 0x7A)
                    buf[i] -= 0x20;
            }
            printf("\n### converted string : %s\n", buf);


            WriteProcessMemory(g_cdpi.hProcess, (LPVOID)param2_buf, buf, param3_size, NULL);

            free(buf);

            ctx.Eip = (DWORD)g_pfWriteFile;
            SetThreadContext(g_cdpi.hProcess, &ctx);

            ContinueDebugEvent(pEvent->dwProcessId, pEvent->dwThreadId, DBG_CONTINUE);

            Sleep(0);


            WriteProcessMemory(g_cdpi.hProcess, g_pfWriteFile, &g_opINT3, sizeof(g_opINT3), NULL);

            return TRUE;
        }
    }

    return FALSE;

}



void init_arg(PDWORD pid)
{
    printf("input notepad.exe pid");
    scanf("%d", pid);
}