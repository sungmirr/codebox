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
        MessageBox(0, _T("알 수 없는 에러가 발생했습니다."), NULL, 0);
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
         * 특정 프로세스에대한 키입력을 받기 위해 로드 하자마자 프로세스 이름 확인
         * notepade.exe가 아닌 경우 DLL을 언로드 한다   => 실패
         */
        /*
            여기서 FreeLibrary해버리면 해당 프로세스는 죽어버린다.. 
            FreeLibrary는 외부에서 해줘야지!!!  
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
    SYSTEM QUEUE에서 APPLICATION QUEUE로 오는 메세지를 HOOK한 결과
     notepad의 경우('a' 버튼 누름)
     [7948] code : 0, wParam : 0x41, lParam : 0x1e0001
     [7948] code : 0, wParam : 0x41, lParam : 0xc01e0001


     devenv의 경우 
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
    