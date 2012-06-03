#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
/*
 * LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
 */

#define DEF_PROCESS_NAME1 _T("notepad.exe")
#define DEF_PROCESS_NAME2 _T("HookMain.exe")

HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL;

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
        MessageBox(0, _T("�� �� ���� ������ �߻��߽��ϴ�."), NULL, 0);
        return;
    }

    MessageBox(0, (LPCTSTR)lpMsgBuff, NULL, 0);
    LocalFree(lpMsgBuff);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hInstance = hinstDLL;
#if _DEBUG
        /*
         * Ư�� ���μ��������� Ű�Է��� �ޱ� ���� �ε� ���ڸ��� ���μ��� �̸� Ȯ��
         * notepade.exe�� �ƴ� ��� DLL�� ��ε� �Ѵ�   => ����
         */
        /*
            ���⼭ FreeLibrary�ع����� �ش� ���μ����� �׾������.. 
            FreeLibrary�� �ܺο��� �������!!!  
        */

        TCHAR *p;
        TCHAR szPath[MAX_PATH];
        if(!GetModuleFileName(NULL, szPath, sizeof(szPath)))
            ;
//            FreeLibrary(hinstDLL);
//        p = _tcsrchr(szPath, _T('\\'));
//        if(_tcscmp(p+1, DEF_PROCESS_NAME1) &&_tcscmp(p+1, DEF_PROCESS_NAME2))
//        {
//           FreeLibrary(hinstDLL); 
//        }
        OutputDebugString(szPath);
#endif
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}



/*
 * Keyboard Hook Procedure
 */
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    TCHAR szPath[MAX_PATH] = {0, };
    TCHAR *p = NULL;

#if _DEBUG
    /*
    SYSTEM QUEUE���� APPLICATION QUEUE�� ���� �޼����� HOOK�� ���
     notepad�� ���('a' ��ư ����)
     [7948] code : 0, wParam : 0x41, lParam : 0x1e0001
     [7948] code : 0, wParam : 0x41, lParam : 0xc01e0001


     devenv�� ��� 
     [1008] code : 3, wParam : 0x41, lParam : 0x1e0001
     [1008] code : 0, wParam : 0x41, lParam : 0x1e0001
     [1008] code : 3, wParam : 0x41, lParam : 0xc01e0001
     [1008] code : 0, wParam : 0x41, lParam : 0xc01e0001
    */
    TCHAR tmp[MAX_PATH]  = {0};
    StringCbPrintf(tmp, sizeof(tmp), _T("code : %d, wParam : 0x%02x, lParam : 0x%02x"), code, wParam, lParam);
    OutputDebugString(tmp);
#endif
#if 0
    if(code > 0)
    {

        // bit 31 : 0 => key press, 1=> key release
        if(!(lParam & 0x80000000))
        {
            GetModuleFileName(NULL, szPath, sizeof(szPath));
            if(GetModuleFileName(NULL, szPath, sizeof(szPath)))
            {
                p = _tcsrchr(szPath, _T('\\'));
                if(!_tcscmp(p+1, DEF_PROCESS_NAME))
                    return 1;
            }

        }
    }
#endif

    return CallNextHookEx(g_hHook, code, wParam, lParam);
}

#if 0
#ifdef __cplusplus
extern "C"
{
__declspec(dllexport) void WINAPI HookStart()
#endif
#endif
void WINAPI HookStart()
{
    g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);
}

#if 0
__declspec(dllexport) void WINAPI HookStop()
#endif
void WINAPI HookStop()
{
    if(g_hHook)
    {
        UnhookWindowsHookEx(g_hHook);
        g_hHook = NULL;
    }
}

#if 0
#ifdef __cplusplus
}
#endif
#endif
    