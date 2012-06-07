#include <windows.h>
#include <time.h>
#include <tchar.h>

#define MYTIMER_ID 1

HINSTANCE g_hInst = NULL;
LPTSTR lpszClass = _T("TimerCallback");
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClass.cbClsExtra=0;
    WndClass.cbWndExtra=0;
    WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
    WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    WndClass.hInstance=hInstance;
    WndClass.lpfnWndProc=(WNDPROC)WndProc;
    WndClass.lpszClassName=lpszClass;
    WndClass.lpszMenuName=NULL;
    WndClass.style=CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&WndClass);

    hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,600,400,
        NULL,(HMENU)NULL,hInstance,NULL);
    ShowWindow(hWnd,nCmdShow);

    while(GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

/*
이 예제는 콜백 함수를 사용하여 문제를 해결했는데 WM_TIMER 메시지를 사용해도 문제를 해결할 수 있다. 
차이점이라면 WM_TIMER 메시지는 다른 메시지가 있을 경우 실행 순서에 밀려 늦게 호출되는 경우가 있지만 
콜백 함수를 사용하면 정확한 시간에 호출된다는 점이다. 
그래서 정확도를 요하는 작업은 타이머 메시지보다는 콜백 함수를 사용하는 것이 더 좋다.
*/

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    HDC hdc;
    int i;
    hdc = GetDC(hWnd);
    for(i=0; i < 100; i++)
        SetPixel(hdc, rand()%500, rand()%400, RGB(rand()%256, rand()%256, rand()%256));
    ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch(iMessage)
    {
    case WM_CREATE:
        // WM_TIMER메세지를 발생시키는 대신, TimerProc을 주기적으로 호출
        SetTimer(hWnd, 1, 100, TimerProc);
        return 0;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}