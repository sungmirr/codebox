
// DrvMgrDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CDrvMgrDlg ��ȭ ����
class CDrvMgrDlg : public CDialog
{
// �����Դϴ�.
public:
	CDrvMgrDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DRVMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonDir();
    afx_msg void OnBnClickedButtonInstall();
    CEdit m_Edit;                   // CEdit property : Multiline, ReadOnly
    int SetStatusEditString(LPCTSTR String);
    TCHAR m_szDrvPath[MAX_PATH];          // full path
    TCHAR m_szDrvName[MAX_PATH];          // Ȯ���� ������ ����̹� �̸�
    afx_msg void OnBnClickedButtonRemove();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnBnClickedButtonStart();
};
