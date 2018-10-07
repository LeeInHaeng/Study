
// MFC_C3_1View.cpp : CMFC_C3_1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_C3_1.h"
#endif

#include "MFC_C3_1Doc.h"
#include "MFC_C3_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_C3_1View

IMPLEMENT_DYNCREATE(CMFC_C3_1View, CView)

BEGIN_MESSAGE_MAP(CMFC_C3_1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMFC_C3_1View 생성/소멸

CMFC_C3_1View::CMFC_C3_1View()
	: m_bTimerType(true)
	, m_strTimer(_T(""))
	, m_bTimerRun(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC_C3_1View::~CMFC_C3_1View()
{
}

BOOL CMFC_C3_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC_C3_1View 그리기

void CMFC_C3_1View::OnDraw(CDC* pDC)
{
	CMFC_C3_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(rect);
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CMFC_C3_1View 인쇄

BOOL CMFC_C3_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC_C3_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC_C3_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC_C3_1View 진단

#ifdef _DEBUG
void CMFC_C3_1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_C3_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_C3_1Doc* CMFC_C3_1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_C3_1Doc)));
	return (CMFC_C3_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_C3_1View 메시지 처리기


void CMFC_C3_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerType==true)
	{
		if (AfxMessageBox(_T("시, 분, 초 형태로 표시하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_bTimerType = false;
	}
	else
	{
		if (AfxMessageBox(_T("년, 월, 일, 시, 분, 초 형태로 표시하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_bTimerType = true;
	}
	

	CView::OnLButtonDown(nFlags, point);
}


void CMFC_C3_1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CTime timer;
	timer = CTime::GetCurrentTime();

	if (m_bTimerType)
		m_strTimer.Format(_T("현재는 %d년 %d월 %d일 %d시 %d분 %d초"), timer.GetYear(), timer.GetMonth(), timer.GetDay(),
			timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	else
	{
		if (timer.GetHour() >= 12)
			m_strTimer.Format(_T("지금은 PM %d시 %d분 %d초"), (timer.GetHour() - 12), timer.GetMinute(), timer.GetSecond());
		else
			m_strTimer.Format(_T("지금은 AM %d시 %d분 %d초"), timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	}
	Invalidate();

	CView::OnTimer(nIDEvent);
}


int CMFC_C3_1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 1000, NULL);
	m_bTimerRun = TRUE;
	return 0;
}


void CMFC_C3_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerRun)
	{
		if (AfxMessageBox(_T("정말로 디지털 시계 동작을 멈추겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);
			m_bTimerRun = FALSE;
		}
	}
	else
	{
		if (AfxMessageBox(_T("디지털시계를 동작시키겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			SetTimer(0, 1000, NULL);
			m_bTimerRun = TRUE;
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CMFC_C3_1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bTimerRun)
		KillTimer(0);
}
