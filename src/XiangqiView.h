// XiangqiView.h : CXiangqiView 類別的介面
//

#include "XiangqiDoc.h"
#pragma once


class CXiangqiView : public CView
{
protected: // 僅從序列化建立
	CXiangqiView();
	DECLARE_DYNCREATE(CXiangqiView)

// 屬性
public:
	CXiangqiDoc* GetDocument() const;

// 作業
public:

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CXiangqiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
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

#ifndef _DEBUG  // XiangqiView.cpp 中的偵錯版本
inline CXiangqiDoc* CXiangqiView::GetDocument() const
   { return reinterpret_cast<CXiangqiDoc*>(m_pDocument); }
#endif

