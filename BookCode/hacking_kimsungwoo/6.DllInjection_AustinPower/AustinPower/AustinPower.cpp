#include <windows.h>
#include <stddef.h>
#include "AustinPower.h"


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
        strncpy(szHookedDllName, szDllName, strlen(szDllName));
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

    while(1)
    {
        // ContinueDebugEvent(pid, thread_id, continueStatus
        // 정상적으로 처리 된경우 : DBG_CONTINUE
        // 처리못했거나, 어플리케이션의 SEH에서 처리하길 원할 때 : DBG_EXCEPTION_NOT_HANDLED
        WaitForDebugEvent(&event, INFINITE);
        continueStatus = DBG_EXCEPTION_NOT_HANDLED;

        if(event.dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT)
            ProcessDbgInfo = event.u.CreateProcessInfo;          /////// CREATE_PROCESS_DEBUG_INFO StartAddress(entryPoint)
        else if(event.dwDebugEventCode == EXCEPTION_DEBUG_EVENT)
            HandleException(&event, &continueStatus);

        if(event.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
            return;

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
            SetEntryPointBP();
            FFirstBreakpointHit = TRUE;
        }
        else if(exceptRect.ExceptionAddress == AddressOfBase)
        {
            RemoveEntryPointBP();
            InjectSpyDll();
        }
        else if(exceptRect.ExceptionAddress == TargetStubBP)
        {
            ReplaceOrginalPagesAndContext();
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
    
    AddressOfBase = ProcessDbgInfo.lpStartAddress;

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

    strcpy(SourceStub.data_DllName, szHookedDllName);

    SourceStub.operand_PUSH_value = (DWORD)TargetStub + offsetof(FAKE_LOADLIBRARY_CODE, data_DllName);

    SourceStub.operand_MOV_EAX = (DWORD)GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "LoadLibraryA");

    BOOL retValue;
    retValue = WriteProcessMemory(ProcessInfo.hProcess, TargetStub, &SourceStub, 
                                                            sizeof(SourceStub), &cBytesMoved);
    if(!retValue)
        return FALSE;

    CONTEXT stubContext = OriginalThreadContext;
    stubContext.Eip = (DWORD)TargetStub;
    SetThreadContext(ProcessDbgInfo.hThread, &stubContext);

    return TRUE;
}

BOOL AustinPower::ReplaceOrginalPagesAndContext(void)
{
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