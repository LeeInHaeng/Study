
// MFC_C3_1.h : MFC_C3_1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFC_C3_1App:
// �� Ŭ������ ������ ���ؼ��� MFC_C3_1.cpp�� �����Ͻʽÿ�.
//

class CMFC_C3_1App : public CWinApp
{
public:
	CMFC_C3_1App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_C3_1App theApp;
