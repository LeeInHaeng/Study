// m_ClockTable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "챕5과제.h"
#include "m_ClockTable.h"
#include "afxdialogex.h"


// m_ClockTable 대화 상자입니다.

IMPLEMENT_DYNAMIC(m_ClockTable, CDialogEx)

m_ClockTable::m_ClockTable(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_EditYear(_T(""))
	, m_EditMonth(_T(""))
	, m_EditDay(_T(""))
	, m_EditAMPM(_T(""))
	, m_EditHour(_T(""))
	, m_EditMin(_T(""))
	, m_EditSec(_T(""))
	, m_bYMD(false)
	, m_bHMS(true)
	, m_bTimerType(true)
	, m_bTimeRun(false)
{

}

m_ClockTable::~m_ClockTable()
{
}

void m_ClockTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Year, m_EditYear);
	DDX_Text(pDX, IDC_EDIT_Month, m_EditMonth);
	DDX_Text(pDX, IDC_EDIT_Day, m_EditDay);
	DDX_Text(pDX, IDC_EDIT_AMPM, m_EditAMPM);
	DDX_Text(pDX, IDC_EDIT_Hour, m_EditHour);
	DDX_Text(pDX, IDC_EDIT_Min, m_EditMin);
	DDX_Text(pDX, IDC_EDIT_Sec, m_EditSec);
}


BEGIN_MESSAGE_MAP(m_ClockTable, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(IDC_RADIO_12, &m_ClockTable::OnRadio12)
	ON_COMMAND(IDC_RADIO_24, &m_ClockTable::OnRadio24)
	ON_BN_CLICKED(IDC_CHECK_YMD, &m_ClockTable::OnClickedCheckYmd)
	ON_BN_CLICKED(IDC_CHECK_HMS, &m_ClockTable::OnClickedCheckHms)
END_MESSAGE_MAP()


// m_ClockTable 메시지 처리기입니다.


BOOL m_ClockTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_12))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_HMS))->SetCheck(TRUE);

	GetDlgItem(IDC_EDIT_Year)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_Year)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_Month)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_Month)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_Day)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_Day)->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


int m_ClockTable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_bTimeRun = TRUE;
	SetTimer(0, 1000, NULL);

	return 0;
}


void m_ClockTable::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bTimeRun)
		KillTimer(0);
}


void m_ClockTable::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CTime timer;
	timer = CTime::GetCurrentTime();

	m_EditYear.Format(_T("%d"), timer.GetYear());
	m_EditMonth.Format(_T("%d"), timer.GetMonth());
	m_EditDay.Format(_T("%d"), timer.GetDay());

	if (!m_bTimerType) // 24시 표기법
		m_EditHour.Format(_T("%d"), timer.GetHour());
	else // 12시 표기법
	{
		if (timer.GetHour() >= 12) // 오후
		{
			m_EditHour.Format(_T("%d"), timer.GetHour() - 12);
			m_EditAMPM = _T("PM");
		}
		else // 오전
		{
			m_EditHour.Format(_T("%d"), timer.GetHour());
			m_EditAMPM = _T("AM");
		}
		
	}
		
	m_EditMin.Format(_T("%d"), timer.GetMinute());
	m_EditSec.Format(_T("%d"), timer.GetSecond());

	SetDlgItemText(IDC_EDIT_Year, m_EditYear);
	SetDlgItemText(IDC_EDIT_Month, m_EditMonth);
	SetDlgItemText(IDC_EDIT_Day, m_EditDay);
	SetDlgItemText(IDC_EDIT_AMPM, m_EditAMPM);
	SetDlgItemText(IDC_EDIT_Hour, m_EditHour);
	SetDlgItemText(IDC_EDIT_Min, m_EditMin);
	SetDlgItemText(IDC_EDIT_Sec, m_EditSec);

	if (!m_bTimerType)
		GetDlgItem(IDC_EDIT_AMPM)->ShowWindow(FALSE);
	else
		GetDlgItem(IDC_EDIT_AMPM)->ShowWindow(TRUE);

	if (m_bYMD)
	{
		GetDlgItem(IDC_EDIT_Year)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_Month)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_Day)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_Year)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_Month)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_Day)->ShowWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_Year)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_Month)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_Day)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_Year)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_Month)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_Day)->ShowWindow(FALSE);
	}

	if (m_bHMS)
	{
		GetDlgItem(IDC_EDIT_Hour)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_Min)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_Sec)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_Hour)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_Min)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_Sec)->ShowWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_Hour)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_Min)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_Sec)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_Hour)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_Min)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_Sec)->ShowWindow(FALSE);
	}

	m_ClockTable *pClock = new m_ClockTable;

	Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}


void m_ClockTable::OnRadio12()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bTimerType = TRUE;
}


void m_ClockTable::OnRadio24()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bTimerType = FALSE;
}


void m_ClockTable::OnClickedCheckYmd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bYMD)
		m_bYMD = FALSE;
	else
		m_bYMD = TRUE;
}


void m_ClockTable::OnClickedCheckHms()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bHMS)
		m_bHMS = FALSE;
	else
		m_bHMS = TRUE;
}
