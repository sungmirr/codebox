
// ConformSelDlg.h : ��� ����
//

#pragma once


// CConformSelDlg ��ȭ ����
class CConformSelDlg : public CDialog
{
// �����Դϴ�.
public:
	CConformSelDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONFORMSEL_DIALOG };

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
    afx_msg void OnBnClickedButtonCreatesel();
    afx_msg void OnBnClickedButtonTest();
    afx_msg void OnBnClickedButtonReleasesel();
    virtual BOOL DestroyWindow();
};
