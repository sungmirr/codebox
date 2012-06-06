#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DEF_DLL_NAME _T("CBTHook.dll")
#define DEF_HOOKSTART   "HookStart"
#define DEF_HOOKSTOP   "HookStop"

typedef void (WINAPI *PFN_HOOKSTART)(void);
typedef void (WINAPI *PFN_HOOKSTOP)(void);

void ShowErrorMessage(HRESULT hr)
{
    LPVOID lpMsgBuff = NULL;

    if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER    | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuff, 0, NULL))
    {
        MessageBox(0, _T("�� �� ���� ������ �߻��߽��ϴ�."), NULL, 0);
        return;
    }
    MessageBox(0, (LPCTSTR)lpMsgBuff, NULL, 0);
    LocalFree(lpMsgBuff);
}


int _tmain(void)
{
    HMODULE hDll = NULL;
    PFN_HOOKSTART HookStart = NULL;
    PFN_HOOKSTOP HookStop = NULL;

    try
    {
        hDll = LoadLibrary(DEF_DLL_NAME);
        if(!hDll)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        HookStart = (PFN_HOOKSTART)GetProcAddress(hDll, DEF_HOOKSTART);
        if(!HookStart)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        HookStop = (PFN_HOOKSTOP)GetProcAddress(hDll, DEF_HOOKSTOP);
        if(!HookStop)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());



        // Hook�� ��ġ�Ѵ�.
        HookStart();

        _tprintf(_T("press 'q' to quit\n"));
        while(getchar() != '\q') ;

        // Hook�� �����Ѵ�.
        HookStop();

    }
    catch(HRESULT hr)
    {
        ShowErrorMessage(hr);
    }
    catch(...)
    {
        MessageBox(0, _T("Exception was raise"), NULL, 0);
    }

    if(hDll)
        FreeLibrary(hDll);

    return 0;
}