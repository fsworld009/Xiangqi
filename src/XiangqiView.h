// XiangqiView.h : CXiangqiView ���O������
//

#include "XiangqiDoc.h"
#pragma once


class CXiangqiView : public CView
{
protected: // �ȱq�ǦC�ƫإ�
	CXiangqiView();
	DECLARE_DYNCREATE(CXiangqiView)

// �ݩ�
public:
	CXiangqiDoc* GetDocument() const;

// �@�~
public:

// �мg
public:
	virtual void OnDraw(CDC* pDC);  // �мg�H�yø���˵�
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �{���X��@
public:
	virtual ~CXiangqiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void PrintMessage(int message_id);
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
private:
	CDC* m_pDCMemDB ;
	CBitmap* m_pBmpDB ;
	CSize m_sizeDB;
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // XiangqiView.cpp ������������
inline CXiangqiDoc* CXiangqiView::GetDocument() const
   { return reinterpret_cast<CXiangqiDoc*>(m_pDocument); }
#endif

