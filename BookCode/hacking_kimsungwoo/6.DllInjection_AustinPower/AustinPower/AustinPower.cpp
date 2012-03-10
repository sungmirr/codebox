#include <windows.h>
#include <stddef.h>
#include "AustinPower.h"
#include <stdio.h>


AustinPower::AustinPower()
{
    FFirstBreakpointHit = false;
}

BOOL AustinPower::CreateAustinPower(char* szFileCmd, char* szDllName)
{
    STARTUPINFO sInfo;
    ZeroMemory(&sInfo, sizeof(sInfo));
    sInfo.cb = sizeof(sInfo);

    if(CreateProcess(0, szFileCmd, 0, 0, FALSE,
                                DEBUG_ONLY_THIS_PROCESS, 
                                0, 0, &sInfo, &ProcessInfo))
    {
        strncpy(szHookedDllName, szDllName, strlen(szDllName)+1);
        DebugLoop();
        CloseHandle(ProcessInfo.hThread);
        CloseHandle(ProcessInfo.hProcess);
        return true;

    }

    return false;
}

void AustinPower::DebugLoop()
{
    DEBUG_EVENT event;
    DWORD continueStatus;
    /*
    #define EXCEPTION_DEBUG_EVENT       1
    #define CREATE_THREAD_DEBUG_EVENT   2
    #define CREATE_PROCESS_DEBUG_EVENT  3
    #define EXIT_THREAD_DEBUG_EVENT     4
    #define EXIT_PROCESS_DEBUG_EVENT    5
    #define LOAD_DLL_DEBUG_EVENT        6
    #define UNLOAD_DLL_DEBUG_EVENT      7
    #define OUTPUT_DEBUG_STRING_EVENT   8
    #define RIP_EVENT                   9
     */

    while(1)
    {
        // ContinueDebugEvent(pid, thread_id, continueStatus
        // 정상적으로 처리 된경우 : DBG_CONTINUE
        // 처리못했거나, 어플리케이션의 SEH에서 처리하길 원할 때 : DBG_EXCEPTION_NOT_HANDLED
        WaitForDebugEvent(&event, INFINITE);
        continueStatus = DBG_EXCEPTION_NOT_HANDLED;

        if(event.dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT)
        {
            printf("CREATE_PROCESS_DEBUG_EVENT\n");
            ProcessDbgInfo = event.u.CreateProcessInfo;          /////// CREATE_PROCESS_DEBUG_INFO StartAddress(entryPoint)
            AddressOfBase = ProcessDbgInfo.lpStartAddress;
        }
        else if(event.dwDebugEventCode == EXCEPTION_DEBUG_EVENT)
        {
            printf("EXCEPTION_DEBUG_EVENT\n");
            HandleException(&event, &continueStatus);
        }
        else if(event.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
        {
            printf("EXIT_PROCESS_DEBUG_EVENT\n");
            return;
        }
        else if(event.dwDebugEventCode == CREATE_THREAD_DEBUG_EVENT)
            printf("CREATE_THREAD_DEBUG_EVENT\n");
        else if(event.dwDebugEventCode == EXIT_THREAD_DEBUG_EVENT)
            printf("EXIT_THREAD_DEBUG_EVENT\n");
        else if(event.dwDebugEventCode == LOAD_DLL_DEBUG_EVENT)
            printf("LOAD_DLL_DEBUG_EVENT\n");
        else if(event.dwDebugEventCode == UNLOAD_DLL_DEBUG_EVENT)
            printf("UNLOAD_DLL_DEBUG_EVENT\n");
        else if(event.dwDebugEventCode == OUTPUT_DEBUG_STRING_EVENT)
            printf("OUTPUT_DEBUG_STRING_EVENT\n");
        else if(event.dwDebugEventCode == RIP_EVENT)
            printf("RIP_EVENT\n");
        else
            printf("UNKNWON EVENT : 0x%08x\n", event.dwDebugEventCode);
            

        ContinueDebugEvent(event.dwProcessId, event.dwThreadId, continueStatus);
    }
}

// This occurs only if, during the search for structured exception handlers, 
// either no handler was found or the exception was continued.
void AustinPower::HandleException(LPDEBUG_EVENT lpEvent, PDWORD continueStatus)
{
    EXCEPTION_RECORD &exceptRect = lpEvent->u.Exception.ExceptionRecord;
    if(lpEvent->u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT)
    {
        if(FFirstBreakpointHit == FALSE)
        {
            //* 현재 EIP와 ProcessDbgInfo.lpStartAddress 확인
            CONTEXT cxt;
            cxt.ContextFlags = CONTEXT_FULL;
            GetThreadContext(ProcessInfo.hThread, &cxt);
            printf("First EXCEPTION_DEBUG_EVENT\n\teip=0x%08x\n\tCREATE_PROCESS_DEBUG_INFO.StartAddress=%08x\n\t"
                        "CREATE_PROCESS_DEBUG_INFO.BaseAddress=0x%08x\n", 
                        cxt.Eip, ProcessDbgInfo.lpStartAddress, ProcessDbgInfo.lpBaseOfImage);
            //* end
            SetEntryPointBP();
            FFirstBreakpointHit = TRUE;
        }
        else if(exceptRect.ExceptionAddress == AddressOfBase)
        {
            //* 현재 EIP와 ProcessDbgInfo.lpStartAddress 확인
            CONTEXT cxt;
            cxt.ContextFlags = CONTEXT_FULL;
            GetThreadContext(ProcessInfo.hThread, &cxt);
            printf("StartAddress EXCEPTION_DEBUG_EVENT\n\teip=0x%08x\n\tCREATE_PROCESS_DEBUG_INFO.StartAddress=%08x\n\t"
                        "CREATE_PROCESS_DEBUG_INFO.BaseAddress=0x%08x\n", 
                        cxt.Eip, ProcessDbgInfo.lpStartAddress, ProcessDbgInfo.lpBaseOfImage);
            //* end
            RemoveEntryPointBP();
            InjectSpyDll();
        }
        else if(exceptRect.ExceptionAddress == TargetStubBP)
        {
            //* 현재 EIP와 ProcessDbgInfo.lpStartAddress 확인
            CONTEXT cxt;
            cxt.ContextFlags = CONTEXT_FULL;
            GetThreadContext(ProcessInfo.hThread, &cxt);
            printf("TargetStubBP EXCEPTION_DEBUG_EVENT\n\teip=0x%08x\n\tCREATE_PROCESS_DEBUG_INFO.StartAddress=%08x\n\t"
                        "CREATE_PROCESS_DEBUG_INFO.BaseAddress=0x%08x\n", 
                        cxt.Eip, ProcessDbgInfo.lpStartAddress, ProcessDbgInfo.lpBaseOfImage);
            //* end
            ReplaceOrginalPagesAndContext();
        }
        else
        {
            //* 현재 EIP와 ProcessDbgInfo.lpStartAddress 확인
            CONTEXT cxt;
            cxt.ContextFlags = CONTEXT_FULL;
            GetThreadContext(ProcessInfo.hThread, &cxt);
            printf("BREAKPOINT????? EXCEPTION_DEBUG_EVENT\n\teip=0x%08x\n\tCREATE_PROCESS_DEBUG_INFO.StartAddress=%08x\n\t"
                        "CREATE_PROCESS_DEBUG_INFO.BaseAddress=0x%08x\n", 
                        cxt.Eip, ProcessDbgInfo.lpStartAddress, ProcessDbgInfo.lpBaseOfImage);
            //* end
        }


        *continueStatus = DBG_CONTINUE;
    }
    else
    {
        *continueStatus = DBG_EXCEPTION_NOT_HANDLED;
    }
}

BOOL AustinPower::SetEntryPointBP()
{
    DWORD cBytesMoved;

    BOOL retValue = ReadProcessMemory(ProcessInfo.hProcess, AddressOfBase, 
                            &m__originalExeEntryPointOpcode, sizeof(m__originalExeEntryPointOpcode), &cBytesMoved);

    if(!retValue)
        return FALSE;

    BYTE bpOpcode = 0xCC;

    return WriteProcessMemory(ProcessInfo.hProcess, AddressOfBase, 
                            &bpOpcode, sizeof(bpOpcode), &cBytesMoved);
}

BOOL AustinPower::RemoveEntryPointBP()
{
    DWORD cBytesMoved;

    return WriteProcessMemory(ProcessInfo.hProcess, AddressOfBase, 
                &m__originalExeEntryPointOpcode, sizeof(m__originalExeEntryPointOpcode), &cBytesMoved);
}

BOOL AustinPower::InjectSpyDll(void)
{
    DWORD cBytesMoved;

    OriginalThreadContext.ContextFlags = CONTEXT_FULL;
    if(!GetThreadContext(ProcessDbgInfo.hThread, &OriginalThreadContext))
        return FALSE;

    OriginalThreadContext.Eip = OriginalThreadContext.Eip - 1;

    TargetStub = (FAKE_LOADLIBRARY_CODE *)GetMemoryForLoadLibraryStub();

    if(!TargetStub)
        return FALSE;

    TargetStubBP = (PBYTE)TargetStub + offsetof(FAKE_LOADLIBRARY_CODE, instr_INT_3);
    printf("*1 TargetStub 0x%08x, TargetStubBP 0x%08x\n", TargetStub, TargetStubBP);


    strcpy(SourceStub.data_DllName, szHookedDllName);

  //  TargetStubBP = (PBYTE)TargetStub + offsetof(FAKE_LOADLIBRARY_CODE, instr_INT_3);
  //  printf("*2 TargetStub 0x%08x, TargetStubBP 0x%08x\n", TargetStub, TargetStubBP);

    SourceStub.operand_PUSH_value = (DWORD)TargetStub + offsetof(FAKE_LOADLIBRARY_CODE, data_DllName);

    SourceStub.operand_MOV_EAX = (DWORD)GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "LoadLibraryA");

    BOOL retValue;
    retValue = WriteProcessMemory(ProcessInfo.hProcess, TargetStub, &SourceStub, 
                                                            sizeof(SourceStub), &cBytesMoved);
    if(!retValue)
        return FALSE;

    CONTEXT stubContext = OriginalThreadContext;
    stubContext.Eip = (DWORD)TargetStub;
    printf("*InjectSpyDll complete NEW EIP=0x%08x\n", stubContext.Eip);
    if(!SetThreadContext(ProcessDbgInfo.hThread, &stubContext))
    {
        printf("InjectSpydll::SetThreadContext fail");
        return FALSE;
    }

    return TRUE;
}

BOOL AustinPower::ReplaceOrginalPagesAndContext(void)
{
    printf("\tRestore context : EIP 0x%08x\n", OriginalThreadContext.Eip);
    if(!SetThreadContext(ProcessDbgInfo.hThread, &OriginalThreadContext))
        return FALSE;

    return TRUE;
}

typedef LPVOID (WINAPI *PFNVIRTALLEX)(
                                     HANDLE,
                                     LPVOID,
                                     SIZE_T,
                                     DWORD,
                                     DWORD);

PVOID AustinPower::GetMemoryForLoadLibraryStub(void)
{
    OSVERSIONINFO osvi = { sizeof(osvi) };

    GetVersionEx(&osvi);

    if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        PFNVIRTALLEX pfnVirtualAllocEx = (PFNVIRTALLEX)GetProcAddress(GetModuleHandle("kernel32.dll"),"VirtualAllocEx");
        LPVOID pStubMemory = pfnVirtualAllocEx(ProcessDbgInfo.hProcess,
                                                   0, sizeof(FAKE_LOADLIBRARY_CODE), MEM_COMMIT, PAGE_READWRITE);
        return (FAKE_LOADLIBRARY_CODE *)pStubMemory;
    }
    else if(osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
        HANDLE hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, // system paging file mappping
                                                         0, PAGE_READWRITE | SEC_COMMIT, 0, sizeof(FAKE_LOADLIBRARY_CODE), 0);
        if(hFileMapping)
        {
            LPVOID pStubMemory = MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, sizeof(FAKE_LOADLIBRARY_CODE));
            return (FAKE_LOADLIBRARY_CODE *)pStubMemory;
        }
        else
            CloseHandle(hFileMapping);
    }

    return 0;
}

