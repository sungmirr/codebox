#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;

void ShowErrorMessage(HRESULT hr)
{
    LPVOID lpMsgBuff = NULL;

    if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, hr, 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        (LPTSTR)&lpMsgBuff, 0, NULL))
    {
        OutputDebugString(_T("알 수 없는 에러가 발생했습니다."));
        return;
    }
    OutputDebugString((LPCTSTR)lpMsgBuff);
    LocalFree(lpMsgBuff);
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hInstance = hinstDLL;
#ifdef _DEBUG
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, sizeof(szPath));
        OutputDebugString(szPath);
#endif
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
// #ifdef _DEBUG
//     TCHAR tmp[MAX_PATH]  = {0};
//     StringCbPrintf(tmp, sizeof(tmp), _T("nCode : %d, wParam : 0x%02x, lParam : 0x%02x"), nCode, wParam, lParam);
//     OutputDebugString(tmp);
// #endif

    if(nCode >= 0)
    {
        // 키입력
        if(nCode == HCBT_KEYSKIPPED && (lParam & 0x40000000))
        {
#ifdef _DEBUG
            TCHAR tmp[MAX_PATH]  = {0};
            StringCbPrintf(tmp, sizeof(tmp), _T("Key Input >> nCode : %d, wParam : 0x%02x, lParam : 0x%02x"), nCode, wParam, lParam);
            OutputDebugString(tmp);
#endif
        }
        // 윈도우 포커스
        else if(nCode == HCBT_SETFOCUS)
        {
#ifdef _DEBUG
            TCHAR tmp[MAX_PATH]  = {0};
            StringCbPrintf(tmp, sizeof(tmp), _T("SetFocus >> nCode : %d, wParam : 0x%02x, lParam : 0x%02x"), nCode, wParam, lParam);
            OutputDebugString(tmp);
#endif

        }

    }

    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

void WINAPI HookStart()
{
    g_hHook = SetWindowsHookEx(WH_CBT, CBTProc, g_hInstance, 0);
}

void WINAPI HookStop()
{
    if(g_hHook)
    {
        UnhookWindowsHookEx(g_hHook);
        g_hHook = NULL;
    }
}

