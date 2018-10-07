
// MFC_C4_1Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMFC_C4_1Dlg 대화 상자
class CMFC_C4_1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_C4_1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_C4_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
