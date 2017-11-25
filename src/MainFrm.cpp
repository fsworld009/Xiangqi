// MainFrm.cpp : CMainFrame ���O����@
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
	ID_SEPARATOR,           // ���A�C���ܾ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame �غc/�Ѻc

CMainFrame::CMainFrame()
{
	// TODO: �b���[�J������l�Ƶ{���X
	
	//���γB�zONCOMMAND or ON_UPDATE_COMMAND_UI �Y�i�ϥ�CMenu::EnableMenuItem()
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
		TRACE0("�L�k�إߤu��C\n");
		return -1;      // �L�k�إ�
	}*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("�L�k�إߪ��A�C\n");
		return -1;      // �L�k�إ�
	}

	// TODO: �p�G�z���n�i�H�T�w�u��C�A�ЧR���o�T��
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�
	cs.cx = 813; cs.cy = 728; //cx=613+200
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_THICKFRAME;

	return TRUE;
}


// CMainFrame �E�_

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


// CMainFrame �T���B�z�`��



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O

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
