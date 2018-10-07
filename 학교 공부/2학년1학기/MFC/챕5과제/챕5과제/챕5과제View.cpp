
// 챕5과제View.cpp : C챕5과제View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "챕5과제.h"
#endif

#include "챕5과제Doc.h"
#include "챕5과제View.h"
#include "m_ClockTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C챕5과제View

IMPLEMENT_DYNCREATE(C챕5과제View, CView)

BEGIN_MESSAGE_MAP(C챕5과제View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &C챕5과제View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ViewTime, &C챕5과제View::OnViewtime)
END_MESSAGE_MAP()

// C챕5과제View 생성/소멸

C챕5과제View::C챕5과제View()
	: m_strYMD(_T(""))
	, m_strHMS(_T(""))
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

C챕5과제View::~C챕5과제View()
{
}

BOOL C챕5과제View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// C챕5과제View 그리기

void C챕5과제View::OnDraw(CDC* pDC)
{
	C챕5과제Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOutW(20, 20, m_strYMD);
	pDC->TextOutW(20, 50, m_strHMS);
}


// C챕5과제View 인쇄


void C챕5과제View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL C챕5과제View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void C챕5과제View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void C챕5과제View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void C챕5과제View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C챕5과제View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C챕5과제View 진단

#ifdef _DEBUG
void C챕5과제View::AssertValid() const
{
	CView::AssertValid();
}

void C챕5과제View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C챕5과제Doc* C챕5과제View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C챕5과제Doc)));
	return (C챕5과제Doc*)m_pDocument;
}
#endif //_DEBUG


// C챕5과제View 메시지 처리기


void C챕5과제View::OnViewtime()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ClockTable *pClock = new m_ClockTable;

	m_ClockTable2.Create(IDD_DIALOG1, this);
	m_ClockTable2.ShowWindow(SW_SHOW);

	if (pClock->DoModal() == IDOK)
	{
		if (pClock->m_bTimerType)
			m_strHMS.Format(_T("%s %s시 %s분 %s초"), pClock->m_EditAMPM, pClock->m_EditHour, pClock->m_EditMin,
				pClock->m_EditSec);
		else
			m_strHMS.Format(_T("%s시 %s분 %s초"), pClock->m_EditHour, pClock->m_EditMin, pClock->m_EditSec);

		m_strYMD.Format(_T("%s년 %s월 %s일"), pClock->m_EditYear, pClock->m_EditMonth, pClock->m_EditDay);

		if (!pClock->m_bYMD)
			m_strYMD = _T("");
		if (!pClock->m_bHMS)
			m_strHMS = _T("");
		m_ClockTable2.ShowWindow(SW_HIDE);
		m_ClockTable2.DestroyWindow();
	}
	Invalidate();
}
