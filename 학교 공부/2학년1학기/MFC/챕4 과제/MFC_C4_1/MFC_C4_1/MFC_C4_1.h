
// MFC_C4_1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_C4_1App:
// �� Ŭ������ ������ ���ؼ��� MFC_C4_1.cpp�� �����Ͻʽÿ�.
//

class CMFC_C4_1App : public CWinApp
{
public:
	CMFC_C4_1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_C4_1App theApp;