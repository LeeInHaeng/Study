
// MFC_C3_2View.h : CMFC_C3_2View 클래스의 인터페이스
//

#pragma once
#include "atltypes.h"


class CMFC_C3_2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC_C3_2View();
	DECLARE_DYNCREATE(CMFC_C3_2View)

// 특성입니다.
public:
	CMFC_C3_2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFC_C3_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // MFC_C3_2View.cpp의 디버그 버전
inline CMFC_C3_2Doc* CMFC_C3_2View::GetDocument() const
   { return reinterpret_cast<CMFC_C3_2Doc*>(m_pDocument); }
#endif

