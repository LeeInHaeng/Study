
// MFC_C3_2View.cpp : CMFC_C3_2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_C3_2.h"
#endif

#include "MFC_C3_2Doc.h"
#include "MFC_C3_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_C3_2View

IMPLEMENT_DYNCREATE(CMFC_C3_2View, CView)

BEGIN_MESSAGE_MAP(CMFC_C3_2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFC_C3_2View 생성/소멸

CMFC_C3_2View::CMFC_C3_2View()
	: m_strOutText(_T(""))
	, m_ptNow(0)
	, m_ptClientSize(0)
	, m_bDrag(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC_C3_2View::~CMFC_C3_2View()
{
}

BOOL CMFC_C3_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC_C3_2View 그리기

void CMFC_C3_2View::OnDraw(CDC* pDC)
{
	CMFC_C3_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOut(m_ptNow.x, m_ptNow.y, m_strOutText);
}


// CMFC_C3_2View 인쇄

BOOL CMFC_C3_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC_C3_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC_C3_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC_C3_2View 진단

#ifdef _DEBUG
void CMFC_C3_2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_C3_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_C3_2Doc* CMFC_C3_2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_C3_2Doc)));
	return (CMFC_C3_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_C3_2View 메시지 처리기


void CMFC_C3_2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nCharIndex;
	nCharIndex = m_strOutText.GetLength();

	if (nChar == VK_BACK)
		m_strOutText.Delete(nCharIndex - 1, 1);
	else
		m_strOutText += (WCHAR)nChar;

	Invalidate();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFC_C3_2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_LEFT:
		m_ptNow.x -= 5;
		break;
	case VK_RIGHT:
		m_ptNow.x += 5;
		break;
	case VK_UP:
		m_ptNow.y -= 5;
		break;
	case VK_DOWN:
		m_ptNow.y += 5;
		break;
	case VK_PRIOR:
		m_ptNow.y -= 50;
		break;
	case VK_NEXT:
		m_ptNow.y += 50;
		break;
	case VK_HOME:
		m_ptNow = CPoint(0, 0);
		break;
	}

	if (m_ptNow.x < 0)
	{
		m_ptNow.x = 0;
		AfxMessageBox(_T("왼쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptNow.y < 0)
	{
		m_ptNow.y = 0;
		AfxMessageBox(_T("위쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptNow.x > m_ptClientSize.x)
	{
		m_ptNow.x = m_ptClientSize.x;
		AfxMessageBox(_T("오른쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptNow.y > m_ptClientSize.y)
	{
		m_ptNow.y = m_ptClientSize.y;
		AfxMessageBox(_T("아래쪽으로 더 이상 이동할 수 없습니다."));
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFC_C3_2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;

	Invalidate();
}


void CMFC_C3_2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	m_ptNow.x = point.x;
	m_ptNow.y = point.y;
	m_bDrag = true;

	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CMFC_C3_2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_strOutText.IsEmpty())
	{
		if (AfxMessageBox(_T("문자를 모두 지우시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_strOutText.Empty();
	}
	else
		AfxMessageBox(_T("문자열을 입력하시오."));
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CMFC_C3_2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		m_ptNow.x = point.x;
		m_ptNow.y = point.y;
	}
	Invalidate();

	CView::OnMouseMove(nFlags, point);
}


void CMFC_C3_2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (point.x >= 0 && point.y >= 0 && point.x <= m_ptClientSize.x && point.y <= m_ptClientSize.y)
	{
		m_bDrag = false;
		m_ptNow.x = point.x;
		m_ptNow.y = point.y;
	}

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}
