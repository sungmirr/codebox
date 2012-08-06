
// ConformSelDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ConformSel.h"
#include "ConformSelDlg.h"

//++  sys�� ���� �κ�
 
#include "DrvFunc.h"
#include "..\sys\prism.h"

HANDLE G_hDrv = NULL;
#define DRIVE_NAME _T("ConformSel")

unsigned short G_ConformSel = 0;

//--



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CConformSelDlg ��ȭ ����




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


// CConformSelDlg �޽��� ó����

BOOL CConformSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CConformSelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
