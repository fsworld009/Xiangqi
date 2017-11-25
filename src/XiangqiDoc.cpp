// XiangqiDoc.cpp : CXiangqiDoc ���O����@
//

#include "stdafx.h"
#include "Xiangqi.h"

#include "XiangqiDoc.h"
#include "XiangqiView.h"
#include "XiangqiGameCtrl.h"
#include "XiangqiRecordView.h"
#include "XiangqiGameSetDialog.h"
#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXiangqiDoc

IMPLEMENT_DYNCREATE(CXiangqiDoc, CDocument)

BEGIN_MESSAGE_MAP(CXiangqiDoc, CDocument)
	ON_COMMAND(ID_GAMESETTING, &CXiangqiDoc::OnGamesetting)
	ON_COMMAND(ID_FILE_NEW, &CXiangqiDoc::OnFileNew)

END_MESSAGE_MAP()


// CXiangqiDoc �غc/�Ѻc

CXiangqiDoc::CXiangqiDoc():m_game(0), m_time(120), m_current_time(120), m_game_start(false)
{
	// TODO: �b���[�J�@���غc�{���X
	
}

CXiangqiDoc::~CXiangqiDoc()
{
}

BOOL CXiangqiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �b���[�J���s��l�Ƶ{���X
	// (SDI ���|���Φ����)
	m_game = new GameController();
	return TRUE;
}




// CXiangqiDoc �ǦC��

void CXiangqiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �b���[�J�x�s�{���X
		m_game->Save(ar);
	}
	else
	{
		// TODO: �b���[�J���J�{���X
		NewGame(1);
		m_game->Load(ar);
	}
}


// CXiangqiDoc �E�_

#ifdef _DEBUG
void CXiangqiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXiangqiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CXiangqiDoc �R�O

void CXiangqiDoc::OnGamesetting()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	CXiangqiGameSetDialog db;
	db.m_time = m_time;
	if(db.DoModal() == IDOK){
		m_time = db.m_time;
		m_current_time = m_time;
		//Invalidate GameCtrl's Timer
		CMainFrame* pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->SetActiveViewByID(1);
		pFrame->GetActiveView()->Invalidate();
		
	}
}

int CXiangqiDoc::GetRemainTime(void)
{
	return m_current_time;
}

void CXiangqiDoc::ReduceTime(void)
{
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
	pMain->SetActiveViewByID(0);
	CXiangqiView* pView = (CXiangqiView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(1);
	CXiangqiGameCtrl* pCtrl = (CXiangqiGameCtrl*) pMain->GetActiveView();
	pMain->SetActiveViewByID(0);
	if(m_current_time>0)
		m_current_time--;
	if(m_current_time==0){
		SetGameState(false);
		pCtrl->GameOver();
		bool player = m_game->GetPlayer();
		if(player)	//red time up
			pView->PrintMessage(2);
		else
			pView->PrintMessage(1);

	}
}

void CXiangqiDoc::ResetTime()
{
	m_current_time = m_time;
}

void CXiangqiDoc::GameOver(bool who_is_win)
{
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
	pMain->SetActiveViewByID(0);
	CXiangqiView* pView = (CXiangqiView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(1);
	CXiangqiGameCtrl* pCtrl = (CXiangqiGameCtrl*) pMain->GetActiveView();
	pMain->SetActiveViewByID(0);
	if(who_is_win==true)	//red win
		pView->PrintMessage(2);
	else
		pView->PrintMessage(1);


	pCtrl->GameOver();
	SetGameState(false);
	//�}���x�s���п��
	pMain->GetMenu()->EnableMenuItem(ID_FILE_SAVE,MF_BYCOMMAND);
}

GameController* CXiangqiDoc::GetGameController(void)
{
	return m_game;
}

void CXiangqiDoc::Action(int x, int y)
{
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
	pMain->SetActiveViewByID(0);
	CXiangqiView* pView = (CXiangqiView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(1);
	CXiangqiGameCtrl* pCtrl = (CXiangqiGameCtrl*) pMain->GetActiveView();
	pMain->SetActiveViewByID(2);
	CXiangqiRecordView* pRecord = (CXiangqiRecordView*) pMain->GetActiveView();
	pMain->SetActiveViewByID(0);
	switch(m_game->Action(x,y)){
		case 0:		//invalid move
			pView->PrintMessage(0);
			break;
		case 1:		//select/undo select chess
			break;
		case 2:		//valid move
			//Print Record
			pRecord->PrintRecord();
		//GameOver?
		if(m_game->IsGoal() == 1){
			GameOver(true);
		}else if(m_game->IsGoal() == -1){
			GameOver(false);
		}else{
			//Not Gameover, change player(reset timer)
			pCtrl->ChangePlayer();
		}
	}
}

bool CXiangqiDoc::GameStart(void)
{
	return m_game_start;
}

bool CXiangqiDoc::SetGameState(bool game_running)
{
	m_game_start = game_running;
	return false;
}

void CXiangqiDoc::OnFileNew()
{
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
	NewGame(0);
}

void CXiangqiDoc::NewGame(int mode)
{
	//0: play, 1: record
	if(m_game){
		delete m_game;
	}
	m_game = new GameController();
	m_current_time = m_time;
	m_game_start = false;

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CXiangqiGameCtrl* pCtrl;
	pMain->SetActiveViewByID(1);
	pCtrl = (CXiangqiGameCtrl *) pMain->GetActiveView();
	pCtrl->NewGame(mode);
	CXiangqiRecordView* pView;
	pMain->SetActiveViewByID(2);
	pView = (CXiangqiRecordView*) pMain->GetActiveView();
	pView->NewGame();
	//pMain->Invalidate(FALSE);
	pMain->SetActiveViewByID(0);
	pMain->GetActiveView()->Invalidate(false);
	pMain->GetMenu()->EnableMenuItem(ID_GAMESETTING,MF_BYCOMMAND);		//�}��"�]�w"���
	pMain->GetMenu()->EnableMenuItem(ID_FILE_SAVE,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);	//����"�x�s����"
}
