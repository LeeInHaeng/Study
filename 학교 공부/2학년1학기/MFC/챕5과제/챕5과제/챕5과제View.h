
// é5����View.h : Cé5����View Ŭ������ �������̽�
//

#pragma once
#include "m_ClockTable.h"
#include "é5����Doc.h"


class Cé5����View : public CView
{
protected: // serialization������ ��������ϴ�.
	Cé5����View();
	DECLARE_DYNCREATE(Cé5����View)

// Ư���Դϴ�.
public:
	Cé5����Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~Cé5����View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewtime();
	m_ClockTable m_ClockTable2;
	CString m_strYMD;
	CString m_strHMS;
};

#ifndef _DEBUG  // é5����View.cpp�� ����� ����
inline Cé5����Doc* Cé5����View::GetDocument() const
   { return reinterpret_cast<Cé5����Doc*>(m_pDocument); }
#endif

