
// é7 Ʈ�� ��Ʈ��.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cé7Ʈ����Ʈ��App:
// �� Ŭ������ ������ ���ؼ��� é7 Ʈ�� ��Ʈ��.cpp�� �����Ͻʽÿ�.
//

class Cé7Ʈ����Ʈ��App : public CWinApp
{
public:
	Cé7Ʈ����Ʈ��App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cé7Ʈ����Ʈ��App theApp;