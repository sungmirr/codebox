#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "urlmon.lib")

#define DEF_NAVER_ADDR L"http://www.naver.com/index.html"
#define DEF_INDEX_PATH L"C:\\index.html"


// URLDownloadToFIle이 hang이 걸리는 경우가 있어, 별도의 쓰레드에서 작업
DWORD WINAPI ThreadProc(LPVOID lParam)
{
    URLDownloadToFile(NULL, DEF_NAVER_ADDR, DEF_INDEX_PATH, 0, NULL);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    HANDLE hThread = NULL;

    switch(fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(0, "myhack.dll attach", "hi", 0);
        hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
        CloseHandle(hThread);
        break;
    }

    return TRUE;

}

