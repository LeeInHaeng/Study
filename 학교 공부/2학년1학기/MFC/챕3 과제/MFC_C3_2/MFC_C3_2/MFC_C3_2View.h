
// MFC_C3_2View.h : CMFC_C3_2View Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CMFC_C3_2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFC_C3_2View();
	DECLARE_DYNCREATE(CMFC_C3_2View)

// Ư���Դϴ�.
public:
	CMFC_C3_2Doc* GetDocument() const;

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
	virtual ~CMFC_C3_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strOutText;
	CPoint m_ptNow;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CPoint m_ptClientSize;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	bool m_bDrag;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC_C3_2View.cpp�� ����� ����
inline CMFC_C3_2Doc* CMFC_C3_2View::GetDocument() const
   { return reinterpret_cast<CMFC_C3_2Doc*>(m_pDocument); }
#endif

