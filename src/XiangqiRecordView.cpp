// XiangqiRecordView.cpp : ��@��
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


// CXiangqiRecordView �E�_

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


// CXiangqiRecordView �T���B�z�`��

BOOL CXiangqiRecordView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
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
	
	// TODO:  �b���[�J�S�O�إߪ��{���X

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


