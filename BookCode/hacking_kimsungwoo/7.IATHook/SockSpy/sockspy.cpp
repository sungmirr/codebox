#include <windows.h>
#include "sockspy.h"

BOOL InitHookSocket();
BOOL InitInterceptStub();
BOOL SetHookInDLL(PVOID pBaseOfFunction);
void HookProc(PDWORD pParam);

PFUNCSTUB pInterceptedSend = NULL;

int WINAPI DllMain(HANDLE h, ULONG ul, LPVOID lp)
{
    switch(ul)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, "Hi11111", "keke", NULL);
        if(FALSE == InitHookSocket())
            return FALSE;
        break;
    case DLL_PROCESS_DETACH:
        if(pInterceptedSend)
            free(pInterceptedSend);
        break;
    }

    return TRUE;
}



BOOL InitHookSocket()
{
    HMODULE hMod;

    if(!(hMod = GetModuleHandle(NULL)))
        return FALSE;

    if(!InitInterceptStub())
        return FALSE;

    return SetHookInDLL(hMod);
}

BOOL InitInterceptStub()
{
    //char szModuleName[] = "KERNEL32.DLL", szFuncName[] = "GetStartupInfoA";
    char szModuleName[] = "USER32.DLL", szFuncName[] = "MessageBoxA";
    PVOID pRealAddress;
    HMODULE hModule;

    if(!(hModule = GetModuleHandle(szModuleName)))
        return FALSE;

    if(!(pRealAddress = GetProcAddress(hModule, szFuncName)))
        return FALSE;

    if(!(pInterceptedSend = (PFUNCSTUB)malloc(sizeof(FUNCSTUB))))
        return FALSE;

    pInterceptedSend->RealProcAddress = pRealAddress;
    pInterceptedSend->opPUSHAD = 0x60;
    pInterceptedSend->opCALL = 0xE8;
    pInterceptedSend->offHookProc = (DWORD)HookProc - (DWORD)&pInterceptedSend->opPOPAD;
    pInterceptedSend->opPOPAD = 0x61;
    pInterceptedSend->opJMP = 0x25FF;
    pInterceptedSend->offRealAddress = (DWORD)pInterceptedSend;     // CHECK

    return TRUE;
}

BOOL SetHookInDLL(PVOID pBaseOfFunction)
{
    PIMAGE_DOS_HEADER pIDH = (PIMAGE_DOS_HEADER)pBaseOfFunction;
    PIMAGE_NT_HEADERS pINH = (PIMAGE_NT_HEADERS)((DWORD)pIDH + pIDH->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR pIID;

    pIID = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)pBaseOfFunction +
        pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    if(pIDH->e_magic != IMAGE_DOS_SIGNATURE)
        return FALSE;
    if(pINH->Signature != IMAGE_NT_SIGNATURE)
        return FALSE;
    while(pIID->Name)
    {
        char *p;
        PIMAGE_THUNK_DATA pITD = (PIMAGE_THUNK_DATA)((DWORD)pBaseOfFunction + pIID->FirstThunk);
        p = (char *)((DWORD)pBaseOfFunction + (DWORD)pIID->Name);
        while(pITD->u1.Function)
        {
            if(pITD->u1.Function == (DWORD)pInterceptedSend->RealProcAddress)
            {
                DWORD flOldProtect, flNewProtect, flDontCare;
                MEMORY_BASIC_INFORMATION mbi;
                VirtualQuery(&pITD->u1.Function, &mbi, sizeof(mbi));
                flNewProtect = mbi.Protect;
                flNewProtect &= ~(PAGE_READONLY | PAGE_EXECUTE_READ);  // PAGE_READONLY, PAGE_EXCUTE_READ 제거
                flNewProtect |= (PAGE_READWRITE);       // PAGE_READWRITE 추가

                VirtualProtect(&pITD->u1.Function, sizeof(PVOID), flNewProtect, &flOldProtect);
                pITD->u1.Function = (DWORD)&pInterceptedSend->opPOPAD;    // CHECK
                VirtualProtect(&pITD->u1.Function, sizeof(PVOID), flOldProtect, &flDontCare);

                return TRUE;
            }
            else
                pITD++;
        }

        pIID++;
    }

    return FALSE;
}


// CEHCK
void HookProc(PDWORD pParam)
{
    MessageBox(NULL, "Information", "OK! It's success!", MB_OK);

    PCHAR szSendBuf;

    szSendBuf = (PCHAR)*pParam;
}