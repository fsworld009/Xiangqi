// XiangqiGameCtrl.cpp : 實作檔
//

#include "stdafx.h"
#include "Xiangqi.h"
#include "MainFrm.h"
#include "XiangqiGameCtrl.h"
#include "XiangqiView.h"
#include "XiangqiRecordView.h"
#include "XiangqiDoc.h"
#include "BitMap.h"


// CXiangqiGameCtrl

IMPLEMENT_DYNCREATE(CXiangqiGameCtrl, CFormView)

CXiangqiGameCtrl::CXiangqiGameCtrl()
	: CFormView(CXiangqiGameCtrl::IDD), m_TimerRefreshRect(36,50,164,71), m_player(true)
{
	m_TimerRefreshRect.NormalizeRect();
	m_TimerRefreshRect.InflateRect(5,5);
}

CXiangqiGameCtrl::~CXiangqiGameCtrl()
{
}

void CXiangqiGameCtrl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXiangqiGameCtrl, CFormView)

	ON_BN_CLICKED(IDC_UNDO, &CXiangqiGameCtrl::OnBnClickedUndo)
	ON_WM_PAINT()


	ON_BN_CLICKED(IDC_START, &CXiangqiGameCtrl::OnBnClickedStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_QUIT, &CXiangqiGameCtrl::OnBnClickedQuit)
	ON_BN_CLICKED(IDC_NEXT_STEP, &CXiangqiGameCtrl::OnBnClickedNextStep)
	ON_BN_CLICKED(IDC_PRE_STEP, &CXiangqiGameCtrl::OnBnClickedPreStep)
END_MESSAGE_MAP()


// CXiangqiGameCtrl 診斷

#ifdef _DEBUG
void CXiangqiGameCtrl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CXiangqiGameCtrl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXiangqiGameCtrl 訊息處理常式

void CXiangqiGameCtrl::OnBnClickedUndo()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	MessageBox(_T("起手無回大丈夫"),_T("\\(^o^)/"));
}

void CXiangqiGameCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CFormView::OnPaint()
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此加入描繪程式碼
	int remain_time = pDoc->GetRemainTime();
	int timer_digit=0;
	int timer_resource_id=60000;
	for(int i=0;i<3;i++){
		if(remain_time >0){
			timer_digit = remain_time%10;
			remain_time = remain_time/10;
		}else{
			timer_digit=0;
		}
		DrawBitMap((CDC *)&dc,timer_resource_id+timer_digit,(108-i*16),50,16,21,0,0,SRCCOPY);
		//TRACE("Digit = %d\n", timer_digit);
	}
	//Timer Bitmap Resource Basis: 60000
	//0~9 60000~60009
	CString M1, M2;
	if(m_player){	//red
		M1 = "●";
		M2 = "";
	}else{
		M1 = "";
		M2 = "●";
	}
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOutW(30,55,M1);
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOutW(148,55,M2);
}

void CXiangqiGameCtrl::OnBnClickedStart()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CMainFrame* pFrame = (CMainFrame*) GetParentFrame();
	SetTimer(IDE_GAME_TIMER,1000,0);

	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
	//Game Start
	pDoc->SetGameState(true);
	//Enable/Disable Buttons & Game Set Menu
	this->GetDlgItem(IDC_UNDO)->EnableWindow(true);
	this->GetDlgItem(IDC_QUIT)->EnableWindow(true);
	this->GetDlgItem(IDC_START)->EnableWindow(false);

	//Before this, Put CFrameWnd::m_bAutoMenuEnable = false; in CMainFrame::CMainFrame()
	pFrame->GetMenu()->EnableMenuItem(ID_GAMESETTING,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);

}

void CXiangqiGameCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if(nIDEvent == IDE_GAME_TIMER){
		CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
		pDoc->ReduceTime();
		InvalidateRect(&m_TimerRefreshRect);
	}
	CFormView::OnTimer(nIDEvent);
}

void CXiangqiGameCtrl::NewGame(int mode)
{
	//0 = play,1 = record
	KillTimer(IDE_GAME_TIMER);
	m_player = true;
	if(mode==0){
		this->GetDlgItem(IDC_UNDO)->EnableWindow(false);
		this->GetDlgItem(IDC_QUIT)->EnableWindow(false);
		this->GetDlgItem(IDC_START)->EnableWindow(true);
		this->GetDlgItem(IDC_NEXT_STEP)->EnableWindow(false);
		this->GetDlgItem(IDC_PRE_STEP)->EnableWindow(false);
	}
	else{
		this->GetDlgItem(IDC_UNDO)->EnableWindow(false);
		this->GetDlgItem(IDC_QUIT)->EnableWindow(false);
		this->GetDlgItem(IDC_START)->EnableWindow(false);
		this->GetDlgItem(IDC_NEXT_STEP)->EnableWindow(true);
		this->GetDlgItem(IDC_PRE_STEP)->EnableWindow(true);
	}
	InvalidateRect(&m_TimerRefreshRect);
}

void CXiangqiGameCtrl::GameOver()
{
	KillTimer(IDE_GAME_TIMER);
	this->GetDlgItem(IDC_UNDO)->EnableWindow(false);
	this->GetDlgItem(IDC_QUIT)->EnableWindow(false);
}

void CXiangqiGameCtrl::ChangePlayer()
{
	KillTimer(IDE_GAME_TIMER);
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
	pDoc->ResetTime();
	SetTimer(IDE_GAME_TIMER,1000,0);
	InvalidateRect(&m_TimerRefreshRect);
	m_player = !m_player;
}
void CXiangqiGameCtrl::OnBnClickedQuit()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();
	pDoc->GameOver(m_player);
	this->GameOver();
}

void CXiangqiGameCtrl::OnBnClickedNextStep()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
	pMain->SetActiveViewByID(0);
	CXiangqiView* pView = (CXiangqiView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(2);
	CXiangqiRecordView* pRecord = (CXiangqiRecordView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(0);
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();


	GameController* pGame = pDoc->GetGameController();
	pGame->NextStep();
	pRecord->PrintRecord();
	pView->Invalidate(false);


}

void CXiangqiGameCtrl::OnBnClickedPreStep()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
	pMain->SetActiveViewByID(0);
	CXiangqiView* pView = (CXiangqiView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(2);
	CXiangqiRecordView* pRecord = (CXiangqiRecordView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(0);
	CXiangqiDoc* pDoc = (CXiangqiDoc*) GetDocument();


	GameController* pGame = pDoc->GetGameController();

	pGame->PreviousStep();
	pRecord->DeleteRecord();
	pView->Invalidate(false);
}
