
// é5����View.cpp : Cé5����View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "é5����.h"
#endif

#include "é5����Doc.h"
#include "é5����View.h"
#include "m_ClockTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cé5����View

IMPLEMENT_DYNCREATE(Cé5����View, CView)

BEGIN_MESSAGE_MAP(Cé5����View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cé5����View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ViewTime, &Cé5����View::OnViewtime)
END_MESSAGE_MAP()

// Cé5����View ����/�Ҹ�

Cé5����View::Cé5����View()
	: m_strYMD(_T(""))
	, m_strHMS(_T(""))
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Cé5����View::~Cé5����View()
{
}

BOOL Cé5����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cé5����View �׸���

void Cé5����View::OnDraw(CDC* pDC)
{
	Cé5����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	pDC->TextOutW(20, 20, m_strYMD);
	pDC->TextOutW(20, 50, m_strHMS);
}


// Cé5����View �μ�


void Cé5����View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cé5����View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Cé5����View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Cé5����View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void Cé5����View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cé5����View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cé5����View ����

#ifdef _DEBUG
void Cé5����View::AssertValid() const
{
	CView::AssertValid();
}

void Cé5����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cé5����Doc* Cé5����View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cé5����Doc)));
	return (Cé5����Doc*)m_pDocument;
}
#endif //_DEBUG


// Cé5����View �޽��� ó����


void Cé5����View::OnViewtime()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ClockTable *pClock = new m_ClockTable;

	m_ClockTable2.Create(IDD_DIALOG1, this);
	m_ClockTable2.ShowWindow(SW_SHOW);

	if (pClock->DoModal() == IDOK)
	{
		if (pClock->m_bTimerType)
			m_strHMS.Format(_T("%s %s�� %s�� %s��"), pClock->m_EditAMPM, pClock->m_EditHour, pClock->m_EditMin,
				pClock->m_EditSec);
		else
			m_strHMS.Format(_T("%s�� %s�� %s��"), pClock->m_EditHour, pClock->m_EditMin, pClock->m_EditSec);

		m_strYMD.Format(_T("%s�� %s�� %s��"), pClock->m_EditYear, pClock->m_EditMonth, pClock->m_EditDay);

		if (!pClock->m_bYMD)
			m_strYMD = _T("");
		if (!pClock->m_bHMS)
			m_strHMS = _T("");
		m_ClockTable2.ShowWindow(SW_HIDE);
		m_ClockTable2.DestroyWindow();
	}
	Invalidate();
}
