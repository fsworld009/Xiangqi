#pragma once


// CXiangqiRecordView 檢視

class CXiangqiRecordView : public CEditView
{
	DECLARE_DYNCREATE(CXiangqiRecordView)

protected:
	CXiangqiRecordView();           // 動態建立所使用的保護建構函式
	virtual ~CXiangqiRecordView();
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void PrintRecord();
	void DeleteRecord();
	void NewGame();
	//void LoadRecord
};


