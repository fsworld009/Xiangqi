#pragma once


// CXiangqiRecordView �˵�

class CXiangqiRecordView : public CEditView
{
	DECLARE_DYNCREATE(CXiangqiRecordView)

protected:
	CXiangqiRecordView();           // �ʺA�إߩҨϥΪ��O�@�غc�禡
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


