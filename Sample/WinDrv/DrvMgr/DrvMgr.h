
// DrvMgr.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDrvMgrApp:
// �� Ŭ������ ������ ���ؼ��� DrvMgr.cpp�� �����Ͻʽÿ�.
//

class CDrvMgrApp : public CWinAppEx
{
public:
	CDrvMgrApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDrvMgrApp theApp;