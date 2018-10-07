
// 챕5과제View.h : C챕5과제View 클래스의 인터페이스
//

#pragma once
#include "m_ClockTable.h"
#include "챕5과제Doc.h"


class C챕5과제View : public CView
{
protected: // serialization에서만 만들어집니다.
	C챕5과제View();
	DECLARE_DYNCREATE(C챕5과제View)

// 특성입니다.
public:
	C챕5과제Doc* GetDocument() const;

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
	virtual ~C챕5과제View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // 챕5과제View.cpp의 디버그 버전
inline C챕5과제Doc* C챕5과제View::GetDocument() const
   { return reinterpret_cast<C챕5과제Doc*>(m_pDocument); }
#endif

