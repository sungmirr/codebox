
// PrintIDT.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPrintIDTApp:
// �� Ŭ������ ������ ���ؼ��� PrintIDT.cpp�� �����Ͻʽÿ�.
//

class CPrintIDTApp : public CWinAppEx
{
public:
	CPrintIDTApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPrintIDTApp theApp;