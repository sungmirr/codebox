/*++
    DrvMgr : 
        드라이버 등록(\HKLM\SYSTEM\CurrentControlSet\Services에 등록)
         - OpenSCManager
         - CreateService
        드라이버 해지(unregister, 레지스트리에서 제거)
         - OpenSCManager
         - OpenService
         - DeleteService
        드라이버 시작(DriverEntry()호출, procexp의 system확인)
         - OpenSCManager
         - OpenService
         - StartService
        드라이버 종료(드라이버의 Unload루틴 호출, procexp의 system 목록에서 삭제)
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


// CDrvMgrDlg 대화 상자




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


// CDrvMgrDlg 메시지 처리기

BOOL CDrvMgrDlg::OnInitDialog()
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDrvMgrDlg::OnPaint()
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
HCURSOR CDrvMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDrvMgrDlg::OnBnClickedButtonDir()
{
    // TODO: Add your control notification handler code here
    // cf) SHBrowseForFolder, BROWSEINFO bi;는 폴더찾기 대화상자

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
    해당 handle로 DeviceIoControl, ReadFile, WriteFile 을 이용 드라이버와 통신
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

