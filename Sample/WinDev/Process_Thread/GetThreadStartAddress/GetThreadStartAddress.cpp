/*++
    GetThreadStartAddress
      - NtQueryInformationThread API를 이용 스레드 시작주소 구하기

    reference
      - http://www.jiniya.net/wp/archives/7676

    2012.07.25 22:00
 --*/

#include <windows.h>
#include <winternl.h>
#include <tchar.h>

#define ThreadQuerySetWin32StartAddress 9
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

typedef NTSTATUS (WINAPI *NtQueryInformationThreadT)(HANDLE, ULONG, PVOID, ULONG, PULONG);

BOOL
GetThreadStartAddress(ULONG tid, PVOID *address)
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    NtQueryInformationThreadT pNTQIT;
    pNTQIT = (NtQueryInformationThreadT) 
        GetProcAddress(ntdll, "NtQueryInformationThread");
    if(!pNTQIT)
        return FALSE;

    // OpenProcess랑 다르게 별다른 권한이 필요없다
    HANDLE h = OpenThread(THREAD_QUERY_INFORMATION, FALSE, tid);
    if(!h)
        return FALSE;

    PVOID addr;
    NTSTATUS s;

    s = pNTQIT(h
        , ThreadQuerySetWin32StartAddress
        , &addr
        , sizeof(addr)
        , NULL);

    CloseHandle(h);

    if(!NT_SUCCESS(s))
        return FALSE;

    *address = addr;
    return TRUE;
}


int _tmain(int argc, TCHAR **argv)
{
    if(argc != 2)
    {
        _tprintf(_T("GetThreadAddress.exe <tid>\n"));
        return 0;
    }

    DWORD dwPid = _tcstoul(argv[1], 0, 0);
    PVOID pAddr = NULL;
    if(GetThreadStartAddress(dwPid, &pAddr))
    {
        _tprintf(_T("[%d] start address - %08x\n"), dwPid, pAddr);
    }
    else
        _tprintf(_T("fail"));

    return 0;
}