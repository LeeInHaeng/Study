#pragma once


// m_ClockTable ��ȭ �����Դϴ�.

class m_ClockTable : public CDialogEx
{
	DECLARE_DYNAMIC(m_ClockTable)

public:
	m_ClockTable(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~m_ClockTable();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
