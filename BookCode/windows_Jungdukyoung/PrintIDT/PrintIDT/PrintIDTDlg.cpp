/*++ 2012.8 .15
    
    BUG - 

    PrintIDT.sys�� (�������Ϳ� �����) StartService���� �����ϴ� ��� �߻�
    �� �� �������� service�� ����� ����� �ȵ��־ �߻�..
    DrvMgr�� ������ �ٽ� ����� ������ PrintIDT.exe�� StartService���ָ� ���д� ����
    
--*/


// PrintIDTDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PrintIDT.h"
#include "PrintIDTDlg.h"


//++  SYS ����

#include "DrvFunc.h"
#include "..\sys\prism.h"

#define DRIVE_NAME _T("PrintIDT")
//--

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CPrintIDTDlg ��ȭ ����




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


// CPrintIDTDlg �޽��� ó����

BOOL CPrintIDTDlg::OnInitDialog()
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPrintIDTDlg::OnPaint()
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
