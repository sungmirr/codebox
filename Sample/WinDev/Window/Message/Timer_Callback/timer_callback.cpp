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
�� ������ �ݹ� �Լ��� ����Ͽ� ������ �ذ��ߴµ� WM_TIMER �޽����� ����ص� ������ �ذ��� �� �ִ�. 
�������̶�� WM_TIMER �޽����� �ٸ� �޽����� ���� ��� ���� ������ �з� �ʰ� ȣ��Ǵ� ��찡 ������ 
�ݹ� �Լ��� ����ϸ� ��Ȯ�� �ð��� ȣ��ȴٴ� ���̴�. 
�׷��� ��Ȯ���� ���ϴ� �۾��� Ÿ�̸� �޽������ٴ� �ݹ� �Լ��� ����ϴ� ���� �� ����.
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
        // WM_TIMER�޼����� �߻���Ű�� ���, TimerProc�� �ֱ������� ȣ��
        SetTimer(hWnd, 1, 100, TimerProc);
        return 0;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}