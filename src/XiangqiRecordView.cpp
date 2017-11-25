// XiangqiRecordView.cpp : 實作檔
//

#include "stdafx.h"
#include "Xiangqi.h"
#include "XiangqiRecordView.h"
#include "GameController.h"
#include "XiangqiDoc.h"



// CXiangqiRecordView

IMPLEMENT_DYNCREATE(CXiangqiRecordView, CEditView)

CXiangqiRecordView::CXiangqiRecordView()
{
	
}

CXiangqiRecordView::~CXiangqiRecordView()
{
}

BEGIN_MESSAGE_MAP(CXiangqiRecordView, CEditView)

	ON_WM_CREATE()
END_MESSAGE_MAP()


// CXiangqiRecordView 診斷

#ifdef _DEBUG
void CXiangqiRecordView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CXiangqiRecordView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXiangqiRecordView 訊息處理常式

BOOL CXiangqiRecordView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	//cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL|ES_AUTOVSCROLL|WS_VSCROLL);
	cs.style |= ES_READONLY|ES_MULTILINE;
	cs.style |= WS_VSCROLL;
	//cs.style |= ES_MULTILINE;

	return CEditView::PreCreateWindow(cs);
}

int CXiangqiRecordView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  在此加入特別建立的程式碼

	//CWnd::EnableWindow(false);
	return 0;
}

void CXiangqiRecordView::PrintRecord()
{
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
	CString current_s,new_s;
	GameController* pGame = pDoc->GetGameController();
	GetWindowTextW(current_s);
	new_s = pGame->printChessStep();
	if(new_s != ""){
		current_s += new_s;
		current_s += "\r\n";
	}
	//temp.Delete(temp.GetLength()-1,1);
	SetWindowTextW(current_s);
		//newline
}

void CXiangqiRecordView::DeleteRecord()
{
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
	CString temp;
	GetWindowTextW(temp);
	int a = temp.GetLength();
	temp.Delete(temp.GetLength()-6,6);	//4 Chi Words+\n
	//temp.Delete(temp.GetLength()-1,4);
	SetWindowTextW(temp);
		//newline
}

void CXiangqiRecordView::NewGame()
{
	SetWindowTextW(_T(""));
}


