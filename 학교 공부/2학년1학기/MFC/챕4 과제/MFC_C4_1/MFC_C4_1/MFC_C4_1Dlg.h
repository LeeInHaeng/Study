
// MFC_C4_1Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMFC_C4_1Dlg ��ȭ ����
class CMFC_C4_1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_C4_1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_C4_1_DIALOG };
#endif

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
	CString m_Edit1;
	CString m_Edit2;
	CListBox m_List;
	CComboBox m_Combo;
//	afx_msg void OnBnClickedCheck1();
	bool m_bCheck;
	afx_msg void OnClickedCheck1();
	afx_msg void OnClickedButtonWiRight();
	afx_msg void OnClickedButtonWiLeft();
	afx_msg void OnClickedButtonLefDown();
	afx_msg void OnClickedButtonLefUp();
	afx_msg void OnClickedButtonRigDown();
	afx_msg void OnClickedButtonRigUp();
	afx_msg void OnClickedButtonAreRight();
	afx_msg void OnClickedButtonAreLeft();
};
