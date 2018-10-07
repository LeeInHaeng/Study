
// MFC_C3_1View.h : CMFC_C3_1View Ŭ������ �������̽�
//

#pragma once


class CMFC_C3_1View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFC_C3_1View();
	DECLARE_DYNCREATE(CMFC_C3_1View)

// Ư���Դϴ�.
public:
	CMFC_C3_1Doc* GetDocument() const;

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
	virtual ~CMFC_C3_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool m_bTimerType;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CString m_strTimer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	bool m_bTimerRun;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // MFC_C3_1View.cpp�� ����� ����
inline CMFC_C3_1Doc* CMFC_C3_1View::GetDocument() const
   { return reinterpret_cast<CMFC_C3_1Doc*>(m_pDocument); }
#endif

