/*******************************************************************
 * �� �� : BasicApp.C
 * �� �� : C��ü
 * �� �� : WinMain - Win32 Entry Point.
 *		   WndProc - Windows Procedure.
 * �� �� : ���� �������� �������� GUI ���ø� ĳ�̼��� ����
 *------------------------------------------------------------------
 * �� �� : Min Chang, Sung
 * �� ¥ : 2011.1.22
 * �� �� : 1.0
 * ȸ �� : Cosm Corporation ( sungmirr.tistory.com )
 *******************************************************************/

#include <windows.h>
#include <tchar.h>
#include <winnt.h>

TCHAR g_szAppName[] = _T("Basic GUI Application");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*******************************************************************
 * �� �� : Win32 ��Ʈ�� ����Ʈ �Լ�
 * �� �� : ����
 * �� �� : WinMain
 * �� �� : HINSTANCE hInstance [IN] : �� ���μ����� �ν��Ͻ� �ڵ�(���� ����)
 *		   HINSTANCE hPrevInst [IN] : ������ 0, ����(16��Ʈ���� ȣȯ�� ����)
 *         PSTR      szCmdLine [IN] : Ŀ�ǵ� ���� �Ķ����
 *         int       iCmdShow  [IN] : �����찡 �������� ����
 * �� ȯ : int :
 * �� �� : WIN32 ��Ʈ�� ����Ʈ �Լ�
 *		   �ܼ� ���α׷�(main)���� �ٸ��� GUI������ WinMain�� ��Ʈ�� ����Ʈ �Լ��� �ν��Ѵ�.
 *------------------------------------------------------------------
 * �� �� : Min Chang, Sung
 * �� ¥ : 2011.1.22
 * �� �� : 1.0
 * ȸ �� : Cosm Corporation ( sungmirr.tistory.com )
*******************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PSTR pszCmdLine, int iCmdShow)
{
	HWND hWnd;
	MSG  msg;
	WNDCLASS wndclass;

	/// ������ Ŭ���� ���
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance  = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = g_szAppName;
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, _T("Window Class Registration Failure!!"), g_szAppName, MB_ICONERROR );
		return 0;
	}

	hWnd = CreateWindow(g_szAppName,
						g_szAppName,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						400,
						150,
						NULL,
						NULL,
						hInstance,
						NULL);
	if( !hWnd )
	{
		MessageBox(NULL, _T("Window Createion Failure!!!"), g_szAppName, MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);


	/// �޼��� ����
	while( GetMessage( &msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}




/*******************************************************************
 * �� �� : �������� ���ν��� �Լ�(�ݹ� �Լ�)
 * �� �� : ����
 * �� �� : WndProc
 * �� �� : HWND		hWnd	[IN] : �޼����� ���� ������ �ڵ� 
 *         UINT	    uMsg    [IN] : �޼���
 *         WPARAM   wParam  [IN] : ����1
 *         LPARAM   lParam  [IN] : ����2
 * �� ȯ : LRESULT :
 * �� �� : �����������ν���
 *		   WINDOWCLASS�� lpfnWndProc �ʵ忡 �� �Լ��� ������ ����ؾ� ��������
 *         ������ �� �Լ� ������ ��Ʈ�� �Ѵ�.
 *------------------------------------------------------------------
 * �� �� : Min Chang, Sung
 * �� ¥ : 2011.1.22
 * �� �� : 1.0
 * ȸ �� : Cosm Corporation ( sungmirr.tistory.com )
*******************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam ,LPARAM lParam)
{
	static TCHAR szOutBuf[] = _T("The Most Simple Windows GUI Program");
	HDC hDC;
	PAINTSTRUCT ps;
	RECT	rc;

	switch(uMsg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rc);
		DrawText(hDC, 
			szOutBuf, 
			lstrlen(szOutBuf), 
			&rc, 
			DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint (hWnd, &ps) ;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}