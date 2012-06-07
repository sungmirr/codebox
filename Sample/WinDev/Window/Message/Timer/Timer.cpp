#include <windows.h>
#include <time.h>
#include <tchar.h>

#define MYTIMER_ID 1
#define MYBEEFER_ID 2

HINSTANCE g_hInst = NULL;
LPTSTR lpszClass = _T("MyTimer");
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    __time64_t curtime;
    static TCHAR *str = NULL;
    static RECT rt = {100, 100, 400, 120};
    HDC hdc;
    PAINTSTRUCT ps;


    switch(iMessage)
    {
    case WM_CREATE:
        SetTimer(hWnd, MYTIMER_ID, 1000, NULL);
        SetTimer(hWnd, MYBEEFER_ID, 5000, NULL);
        // 강제로 메세지를 발생시킨다
        // 차일드 윈도우를 컨트롤할때 주로 쓰인다
        // 매개변수는 WndProc과 같다(wParam은 TimerID)
        SendMessage(hWnd, WM_TIMER, 1, 0);
        return 0;

    case WM_TIMER:
        switch(wParam)
        {
        case MYTIMER_ID:
            _time64(&curtime);
            str = _tctime64(&curtime);
            // 깜빡임을 최소화 하기 위해 시간이 표시된 영역(RECT)만 지운다
            InvalidateRect(hWnd, &rt, TRUE);
            break;

        case MYBEEFER_ID:
            MessageBeep(MB_OK);
        }
        
        return 0;

    case WM_PAINT:
        if(str)
        {
            hdc = BeginPaint(hWnd, &ps);
            TextOutW(hdc, 100, 100, str, _tcslen(str)-1);
            EndPaint(hWnd, &ps);
            return 0;
        }
        break;

    case WM_DESTROY:
        KillTimer(hWnd, MYTIMER_ID);
        KillTimer(hWnd, MYBEEFER_ID);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}