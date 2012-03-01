#pragma once

class AustinPower
{
private:
    BOOL FFirstBreakpointHit;
    CONTEXT OriginalThreadContext, FakeLoadLibraryContext;
    PVOID AddressOfBase;
    BYTE m__originalExeEntryPointOpcode;
    char szHookedDllName[MAX_PATH];
    PROCESS_INFORMATION ProcessInfo;
    CREATE_PROCESS_DEBUG_INFO ProcessDbgInfo;

#pragma pack(push, 1)
    struct FAKE_LOADLIBRARY_CODE
    {
        BYTE instr_PUSH;
        DWORD operand_PUSH_value;
        BYTE instr_MOV_EAX;
        DWORD operand_MOV_EAX;
        WORD instr_CALL_EAX;
        BYTE instr_INT_3;
        char data_DllName[MAX_PATH];

        // Constructor builds known in advance fields
        FAKE_LOADLIBRARY_CODE() : instr_PUSH(0x68), 
                                                instr_MOV_EAX(0xB8), 
                                                instr_CALL_EAX(0xD0FF),
                                                instr_INT_3(0xCC) { }
    };
#pragma pack(pop)

    FAKE_LOADLIBRARY_CODE SourceStub;
    FAKE_LOADLIBRARY_CODE *TargetStub;
    PVOID TargetStubBP;

public:
    AustinPower();
    BOOL CreateAustinPower(char* szFileCmd, char* szDllName);
    void DebugLoop();
    BOOL InjectSpyDll();
    BOOL ReplaceOrginalPagesAndContext();
    PVOID FindFirstCodePage(HANDLE hProcess, PVOID PProcessBase);
    void HandleException(LPDEBUG_EVENT lpEvent, PDWORD continueStatus);
    PVOID GetMemoryForLoadLibraryStub();
    BOOL SetEntryPointBP();
    BOOL RemoveEntryPointBP();
};