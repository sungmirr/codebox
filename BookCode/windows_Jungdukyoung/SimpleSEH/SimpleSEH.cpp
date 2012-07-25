/*++
    SimpleSEH

     - 2012 . 7. 25 19:30

     - Compiler ���� ���� ���� ó���� �����ϴ� ���� �ڵ�

 --*/

#include "stdafx.h"
#include <windows.h>

ULONG G_nValid;

EXCEPTION_DISPOSITION __cdecl except_handler(
    struct _EXCEPTION_RECORD *ExceptionRecord,
    void *EstablisherFrame,
    struct _CONTEXT *ContextRecord,
    void *DispatcherContext
    )
{
    _tprintf(_T("Exception Address : %08x Exception Code : %08x\n"), 
                ExceptionRecord->ExceptionAddress, ExceptionRecord->ExceptionCode);
    ContextRecord->Eax = (DWORD)&G_nValid;

    return ExceptionContinueExecution;
}

int _tmain(int argc, _TCHAR* argv[])
{
    DWORD nHandler = (DWORD)except_handler;
    
    // EXCEPTION_REGISTRATION_RECORD�� ���ÿ� ���� �� �� ����
    __asm
    {
        push nHandler
        push fs:[0]
        mov fs:[0], esp
    }

    __asm
    {
        mov eax, 0
        mov [eax], 'a'
    }

    __asm
    {
        // mov fs:[0], [esp]  <--- ������ ����
        mov eax, [esp]
        mov fs:[0], eax
        add esp, 8
    }
    
	return 0;
}

