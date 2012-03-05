#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL ExtractBinResource(LPCTSTR lpBinname)
{
    HRSRC hRes = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_RT_BIN1), _T("RT_BIN"));
    if(!hRes)
    {
        _tprintf(_T("FindResource fail\n"));
        return FALSE;
    }

    HGLOBAL hResLoad = LoadResource(GetModuleHandle(NULL), hRes);
    if(!hResLoad)
    {
        _tprintf(_T("LoadResource fail\n"));
        return FALSE;
    }

    // Retrieve resource pointer
    LPVOID lpResLock = LockResource(hResLoad);
    if(!lpResLock)
    {
        _tprintf(_T("LockResource fail\n"));
        return FALSE;
    }

    SIZE_T resSize = SizeofResource(NULL, hRes);

    HANDLE h = CreateFile(lpBinname, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
    if(h == INVALID_HANDLE_VALUE)
    {
        _tprintf(_T("CreateFile fail\n"));
        return FALSE;
    }

    DWORD written;
    WriteFile(h, lpResLock, resSize, &written, NULL);

    CloseHandle(h);

}

int _tmain(void)
{
    _tprintf(_T("extract resource binary.... ProcessHacker.exe\n"));

    if(ExtractBinResource(_T("extract.exe")))
    {
        _tprintf(_T("success\n"));
        return 0;
    }

    _tprintf(_T("fail\n"));
    return 0;
}