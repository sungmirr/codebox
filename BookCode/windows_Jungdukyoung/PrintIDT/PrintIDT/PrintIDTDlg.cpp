/*++ 2012.8 .15
    
    BUG - 

    PrintIDT.sys를 (레지스터에 등록후) StartService에서 실패하는 경우 발생
    이 때 레지스터 service에 제대로 등록이 안되있어서 발생..
    DrvMgr로 삭제후 다시 등록한 다음에 PrintIDT.exe로 StartService해주면 실패는 안함
    
--*/


// PrintIDTDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PrintIDT.h"
#include "PrintIDTDlg.h"


//++  SYS 연동

#include "DrvFunc.h"
#include "..\sys\prism.h"

#define DRIVE_NAME _T("PrintIDT")
//--

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CPrintIDTDlg 대화 상자




CPrintIDTDlg::CPrintIDTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintIDTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrintIDTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrintIDTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_PRINT, &CPrintIDTDlg::OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CPrintIDTDlg 메시지 처리기

BOOL CPrintIDTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPrintIDTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
// 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
// 	{
// 		CAboutDlg dlgAbout;
// 		dlgAbout.DoModal();
// 	}
// 	else
//	{
		CDialog::OnSysCommand(nID, lParam);
//	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPrintIDTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPrintIDTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPrintIDTDlg::OnBnClickedButtonPrint()
{
   
    HANDLE hDrv;
    DWORD dummy;

    hDrv = MakeDrvSimpleStart(NULL, DRIVE_NAME);
    if(!hDrv)
    {
        AfxMessageBox(_T("error"));
        return;
    }
    AfxMessageBox(_T("driver start success"));

    MakeDrvIoControl(hDrv, IOCTL_PRINT_IDT, &dummy, sizeof(dummy), &dummy, sizeof(dummy));
    MakeDrvStop(DRIVE_NAME, hDrv);   
}
