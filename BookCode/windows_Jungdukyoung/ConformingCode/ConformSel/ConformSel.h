
// ConformSel.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CConformSelApp:
// �� Ŭ������ ������ ���ؼ��� ConformSel.cpp�� �����Ͻʽÿ�.
//

class CConformSelApp : public CWinAppEx
{
public:
	CConformSelApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CConformSelApp theApp;