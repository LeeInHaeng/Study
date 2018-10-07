
// MFC_C3_2View.cpp : CMFC_C3_2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CMFC_C3_2View ����/�Ҹ�

CMFC_C3_2View::CMFC_C3_2View()
	: m_strOutText(_T(""))
	, m_ptNow(0)
	, m_ptClientSize(0)
	, m_bDrag(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFC_C3_2View::~CMFC_C3_2View()
{
}

BOOL CMFC_C3_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFC_C3_2View �׸���

void CMFC_C3_2View::OnDraw(CDC* pDC)
{
	CMFC_C3_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	pDC->TextOut(m_ptNow.x, m_ptNow.y, m_strOutText);
}


// CMFC_C3_2View �μ�

BOOL CMFC_C3_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFC_C3_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFC_C3_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFC_C3_2View ����

#ifdef _DEBUG
void CMFC_C3_2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_C3_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_C3_2Doc* CMFC_C3_2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_C3_2Doc)));
	return (CMFC_C3_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_C3_2View �޽��� ó����


void CMFC_C3_2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
		AfxMessageBox(_T("�������� �� �̻� �̵��� �� �����ϴ�."));
	}
	if (m_ptNow.y < 0)
	{
		m_ptNow.y = 0;
		AfxMessageBox(_T("�������� �� �̻� �̵��� �� �����ϴ�."));
	}
	if (m_ptNow.x > m_ptClientSize.x)
	{
		m_ptNow.x = m_ptClientSize.x;
		AfxMessageBox(_T("���������� �� �̻� �̵��� �� �����ϴ�."));
	}
	if (m_ptNow.y > m_ptClientSize.y)
	{
		m_ptNow.y = m_ptClientSize.y;
		AfxMessageBox(_T("�Ʒ������� �� �̻� �̵��� �� �����ϴ�."));
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFC_C3_2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;

	Invalidate();
}


void CMFC_C3_2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	m_ptNow.x = point.x;
	m_ptNow.y = point.y;
	m_bDrag = true;

	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CMFC_C3_2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (!m_strOutText.IsEmpty())
	{
		if (AfxMessageBox(_T("���ڸ� ��� ����ðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_strOutText.Empty();
	}
	else
		AfxMessageBox(_T("���ڿ��� �Է��Ͻÿ�."));
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CMFC_C3_2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (point.x >= 0 && point.y >= 0 && point.x <= m_ptClientSize.x && point.y <= m_ptClientSize.y)
	{
		m_bDrag = false;
		m_ptNow.x = point.x;
		m_ptNow.y = point.y;
	}

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}
