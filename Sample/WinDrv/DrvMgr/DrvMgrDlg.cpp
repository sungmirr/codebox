/*++
    DrvMgr : 
        ����̹� ���(\HKLM\SYSTEM\CurrentControlSet\Services�� ���)
         - OpenSCManager
         - CreateService
        ����̹� ����(unregister, ������Ʈ������ ����)
         - OpenSCManager
         - OpenService
         - DeleteService
        ����̹� ����(DriverEntry()ȣ��, procexp�� systemȮ��)
         - OpenSCManager
         - OpenService
         - StartService
        ����̹� ����(����̹��� Unload��ƾ ȣ��, procexp�� system ��Ͽ��� ����)
         - OpenSCManager
         - OpenService
         - ControlService( , SERVICE_CONTROL_STOP, )

     MFC :
        CString, CFileDialog, CEdit
    
 --*/
#include "stdafx.h"
#include "DrvMgr.h"
#include "DrvMgrDlg.h"
#include <WinSvc.h>
#include <strsafe.h>


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


// CDrvMgrDlg ��ȭ ����




CDrvMgrDlg::CDrvMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrvMgrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrvMgrDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_STATUS, m_Edit);
}

BEGIN_MESSAGE_MAP(CDrvMgrDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_DIR, &CDrvMgrDlg::OnBnClickedButtonDir)
    ON_BN_CLICKED(IDC_BUTTON_INSTALL, &CDrvMgrDlg::OnBnClickedButtonInstall)
    ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CDrvMgrDlg::OnBnClickedButtonRemove)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CDrvMgrDlg::OnBnClickedButtonStop)
    ON_BN_CLICKED(IDC_BUTTON_START, &CDrvMgrDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CDrvMgrDlg �޽��� ó����

BOOL CDrvMgrDlg::OnInitDialog()
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

void CDrvMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDrvMgrDlg::OnPaint()
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
HCURSOR CDrvMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDrvMgrDlg::OnBnClickedButtonDir()
{
    // TODO: Add your control notification handler code here
    // cf) SHBrowseForFolder, BROWSEINFO bi;�� ����ã�� ��ȭ����

    CFileDialog dlg(TRUE, _T("SYS"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
                    _T("SYS Files(*.sys)|*.sys|All Files(*.*)|*.*||"), this);

    if(dlg.DoModal() == IDOK)
    {
#if 1
        CString str = _T("");
        str.Format(_T("Full path : %s, Filename : %s, Extension: %s"), dlg.GetPathName(), dlg.GetFileName(), dlg.GetFileExt());
        AfxMessageBox(str);
#endif
        // SetDlgItemText(, LPCTSTR lpszString);
        // CString CFileDialog::GetPathName() const
        StringCbCopy(m_szDrvPath, sizeof(m_szDrvPath), dlg.GetPathName().GetBuffer());
        StringCbCopy(m_szDrvName, sizeof(m_szDrvName), dlg.GetFileName().GetBuffer());
        TCHAR *p = _tcsrchr(m_szDrvName, _T('.'));
        *p = NULL;
        SetDlgItemText(IDC_EDIT_PATH, dlg.GetPathName());
#if 0
        WCHAR wStr[MAX_PATH];
        CString szStr = ....;
        StringCchCopyW(wStr, MAX_PATH, (LPCWSTR)(LPCTSTR)szStr);
#endif
    }
    
}

void CDrvMgrDlg::OnBnClickedButtonInstall()
{
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;


    hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if(!hSCMan)
    {
        SetStatusEditString(_T("Install::OpenSCManager fail"));
        return;
    }

    hService = CreateService(hSCMan, m_szDrvName, m_szDrvName, GENERIC_READ, 
                            SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START,
                            SERVICE_ERROR_NORMAL, m_szDrvPath, NULL, NULL,
                            NULL, NULL, NULL);
    if(!hService)
    {
        SetStatusEditString(_T("Install::CreateService fail"));
        CloseServiceHandle(hSCMan);
        return;
    }
    else
    {
        SetStatusEditString(_T("Install::CreateService success"));
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCMan);
}

int CDrvMgrDlg::SetStatusEditString(LPCTSTR String)
{
    int nLen = m_Edit.GetWindowTextLength();
    m_Edit.SetFocus();
    m_Edit.SetSel(nLen, nLen);
    m_Edit.ReplaceSel(String);
    m_Edit.ReplaceSel(_T("\r\n"));

    return 0;
}

void CDrvMgrDlg::OnBnClickedButtonRemove()
{
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;

    hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if(!hSCMan)
    {
        SetStatusEditString(_T("Remove::OpenSCManager fail"));
        return;
    }

    hService = OpenService(hSCMan, m_szDrvName, DELETE);
    if(!hService)
    {
        SetStatusEditString(_T("Remove::OpenService fail"));
        CloseServiceHandle(hSCMan);
        return;
    }

    if(!DeleteService(hService))
    {
        SetStatusEditString(_T("Remove::DeleteService fail"));
    }
    else
    {
         SetStatusEditString(_T("Remove::DeleteService success"));
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCMan);
}

void CDrvMgrDlg::OnBnClickedButtonStart()
{
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;

    hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if(!hSCMan)
    {
        SetStatusEditString(_T("Start::OpenSCManager fail"));
        return;
    }

    hService = OpenService(hSCMan, m_szDrvName, SERVICE_START);
    if(!hService)
    {
        SetStatusEditString(_T("Start::OpenService fail"));
        CloseServiceHandle(hSCMan);
        return;
    }

    if(!StartService(hService, 0, NULL))
    {
        SetStatusEditString(_T("Start::StartService fail"));
    }
    else
    {
        SetStatusEditString(_T("Start::StartService success"));
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCMan);

    /*++
    sprintf(szDrvName, "\\\\.\\%s", m_szDrvName);
    HANDLE h = CreateFile(szDrvName, ... );
    �ش� handle�� DeviceIoControl, ReadFile, WriteFile �� �̿� ����̹��� ���
     --*/
}


void CDrvMgrDlg::OnBnClickedButtonStop()
{
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS serviceStatus;

    hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if(!hSCMan)
    {
        SetStatusEditString(_T("Stop::OpenSCManager fail"));
        return;
    }
    
    hService = OpenService(hSCMan, m_szDrvName, SERVICE_STOP);
    if(!hService)
    {
        SetStatusEditString(_T("Stop::OpenService fail"));
        CloseServiceHandle(hSCMan);
        return;
    }
    if(!ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus))
    {
        SetStatusEditString(_T("Stop::ControlService stop fail"));
    }
    else
    {
        SetStatusEditString(_T("Stop::ControlService stop success"));
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCMan);
}

