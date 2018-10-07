
// MFC_C3_1View.cpp : CMFC_C3_1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMFC_C3_1View ����/�Ҹ�

CMFC_C3_1View::CMFC_C3_1View()
	: m_bTimerType(true)
	, m_strTimer(_T(""))
	, m_bTimerRun(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFC_C3_1View::~CMFC_C3_1View()
{
}

BOOL CMFC_C3_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFC_C3_1View �׸���

void CMFC_C3_1View::OnDraw(CDC* pDC)
{
	CMFC_C3_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CRect rect;
	GetClientRect(rect);
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CMFC_C3_1View �μ�

BOOL CMFC_C3_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFC_C3_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFC_C3_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFC_C3_1View ����

#ifdef _DEBUG
void CMFC_C3_1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_C3_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_C3_1Doc* CMFC_C3_1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_C3_1Doc)));
	return (CMFC_C3_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_C3_1View �޽��� ó����


void CMFC_C3_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bTimerType==true)
	{
		if (AfxMessageBox(_T("��, ��, �� ���·� ǥ���Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_bTimerType = false;
	}
	else
	{
		if (AfxMessageBox(_T("��, ��, ��, ��, ��, �� ���·� ǥ���Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			m_bTimerType = true;
	}
	

	CView::OnLButtonDown(nFlags, point);
}


void CMFC_C3_1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CTime timer;
	timer = CTime::GetCurrentTime();

	if (m_bTimerType)
		m_strTimer.Format(_T("����� %d�� %d�� %d�� %d�� %d�� %d��"), timer.GetYear(), timer.GetMonth(), timer.GetDay(),
			timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	else
	{
		if (timer.GetHour() >= 12)
			m_strTimer.Format(_T("������ PM %d�� %d�� %d��"), (timer.GetHour() - 12), timer.GetMinute(), timer.GetSecond());
		else
			m_strTimer.Format(_T("������ AM %d�� %d�� %d��"), timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	}
	Invalidate();

	CView::OnTimer(nIDEvent);
}


int CMFC_C3_1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	SetTimer(0, 1000, NULL);
	m_bTimerRun = TRUE;
	return 0;
}


void CMFC_C3_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bTimerRun)
	{
		if (AfxMessageBox(_T("������ ������ �ð� ������ ���߰ڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);
			m_bTimerRun = FALSE;
		}
	}
	else
	{
		if (AfxMessageBox(_T("�����нð踦 ���۽�Ű�ڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_bTimerRun)
		KillTimer(0);
}
