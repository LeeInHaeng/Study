#pragma once


// m_ClockTable 대화 상자입니다.

class m_ClockTable : public CDialogEx
{
	DECLARE_DYNAMIC(m_ClockTable)

public:
	m_ClockTable(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~m_ClockTable();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditYear;
	CString m_EditMonth;
	CString m_EditDay;
	CString m_EditAMPM;
	CString m_EditHour;
	CString m_EditMin;
	CString m_EditSec;
	bool m_bYMD;
	bool m_bHMS;
	bool m_bTimerType;
	virtual BOOL OnInitDialog();
	bool m_bTimeRun;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRadio12();
	afx_msg void OnRadio24();
	afx_msg void OnClickedCheckYmd();
	afx_msg void OnClickedCheckHms();
};
