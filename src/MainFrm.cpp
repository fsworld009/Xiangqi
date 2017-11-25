// MainFrm.cpp : CMainFrame 類別的實作
//

#include "stdafx.h"
#include "Xiangqi.h"
#include "XiangqiRecordView.h"
#include "XiangqiGameCtrl.h"
#include "XiangqiDoc.h"
#include "XiangqiView.h"


#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 狀態列指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 建構/解構

CMainFrame::CMainFrame()
{
	// TODO: 在此加入成員初始化程式碼
	
	//不用處理ONCOMMAND or ON_UPDATE_COMMAND_UI 即可使用CMenu::EnableMenuItem()
	CFrameWnd::m_bAutoMenuEnable = false;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("無法建立工具列\n");
		return -1;      // 無法建立
	}*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("無法建立狀態列\n");
		return -1;      // 無法建立
	}

	// TODO: 如果您不要可以固定工具列，請刪除這三行
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的
	cs.cx = 813; cs.cy = 728; //cx=613+200
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_THICKFRAME;

	return TRUE;
}


// CMainFrame 診斷

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 訊息處理常式



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別

	m_StaticSplit.CreateStatic(this,1,2);
	m_StaticSplit.CreateView(0,0,RUNTIME_CLASS(CXiangqiView),CSize(601,728),pContext);
	//m_StaticSplit.CreateView(0,1,RUNTIME_CLASS(CXiangqiStateView),CSize(200,728),pContext);
	m_StaticSplit.SetActivePane(0,0);

	m_StaticSplitR.CreateStatic(&m_StaticSplit,2,1,WS_CHILD|WS_VISIBLE,m_StaticSplit.IdFromRowCol(0,1));
	m_StaticSplitR.CreateView(0,0,RUNTIME_CLASS(CXiangqiGameCtrl),CSize(0,300),pContext);
	m_StaticSplitR.CreateView(1,0,RUNTIME_CLASS(CXiangqiRecordView),CSize(0,428),pContext);
	m_StaticSplitR.SetActivePane(0,0);



	return true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}





bool CMainFrame::SetActiveViewByID(int ViewID=0)
{
	//ViewID 0: CXView, 1: CXGameCtrl, 2: CXRecordView
	switch(ViewID){
	case 0:
		SetActiveView((CView*)m_StaticSplit.GetPane(0,0));
		break;
	case 1:
		SetActiveView((CView*)m_StaticSplitR.GetPane(0,0));
		break;
	case 2:
		SetActiveView((CView*)m_StaticSplitR.GetPane(1,0));
		break;
	default:
		return false;
	}
	return true;
}
