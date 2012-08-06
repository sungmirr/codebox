
// ConformSelDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ConformSel.h"
#include "ConformSelDlg.h"

//++  sys와 연동 부분
 
#include "DrvFunc.h"
#include "..\sys\prism.h"

HANDLE G_hDrv = NULL;
#define DRIVE_NAME _T("ConformSel")

unsigned short G_ConformSel = 0;

//--



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CConformSelDlg 대화 상자




CConformSelDlg::CConformSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConformSelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConformSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConformSelDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_CREATESEL, &CConformSelDlg::OnBnClickedButtonCreatesel)
    ON_BN_CLICKED(IDC_BUTTON_TEST, &CConformSelDlg::OnBnClickedButtonTest)
    ON_BN_CLICKED(IDC_BUTTON_RELEASESEL, &CConformSelDlg::OnBnClickedButtonReleasesel)
END_MESSAGE_MAP()


// CConformSelDlg 메시지 처리기

BOOL CConformSelDlg::OnInitDialog()
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

void CConformSelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CConformSelDlg::OnPaint()
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
HCURSOR CConformSelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CConformSelDlg::OnBnClickedButtonCreatesel()
{
    CONFORMING_INFO conformingInfo;

    if(G_hDrv == NULL)
    {
        G_hDrv = MakeDrvSimpleStart(NULL, DRIVE_NAME);      // #define DOS_DEVICE_NAME     L"\\DosDevices\\ConformSel"
        if(G_hDrv == NULL)
        {
            AfxMessageBox(_T("MakeDrvSimpleStart fail"));
            return;
        }
    }

    MakeDrvIoControl(G_hDrv, IOCTL_CREATE_CONFORMING_CODE, &conformingInfo, sizeof(CONFORMING_INFO),
                                &conformingInfo, sizeof(CONFORMING_INFO));

    G_ConformSel = conformingInfo.ConformingSel;

    CString str = _T("");
    str.Format(_T("conformingcode create 0x%04x"), G_ConformSel);
    AfxMessageBox(str);
}

#if 0
static TEST_BODY()
{
    int nTest;

    nTest = 10;
}
#endif

static void __declspec(naked) TEST()
{
#if 0
    TEST_BODY();
#else
    int nTest;
    nTest = 10;
#endif

    __asm
    {
        retf
    }
}


void CConformSelDlg::OnBnClickedButtonTest()
{
    short farcall[3];
    DWORD *p;

    p = (DWORD *)farcall;
    *p = (DWORD)TEST;
    farcall[2] = G_ConformSel;

    __asm
    {
        call fword ptr [farcall]
    }
}

void CConformSelDlg::OnBnClickedButtonReleasesel()
{
    CONFORMING_INFO conformInfo;

    if(G_hDrv && G_ConformSel)
    {
        conformInfo.ConformingSel = G_ConformSel;
        MakeDrvIoControl(G_hDrv, IOCTL_RELEASE_CONFORMING_CODE, &conformInfo, sizeof(CONFORMING_INFO),
                            &conformInfo, sizeof(CONFORMING_INFO));

        G_ConformSel = 0;
    }
}



BOOL CConformSelDlg::DestroyWindow()
{
    if(G_hDrv)
    {
        MakeDrvStop(DRIVE_NAME, G_hDrv);
    }

    return CDialog::DestroyWindow();
}
