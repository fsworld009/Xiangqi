#include "StdAfx.h"
#include "GameController.h"

GameController::GameController(void)
{
}

GameController::~GameController(void)
{
}

int GameController::Action(int x, int y)
{
	return m_chess_set.Action(x, y,m_record);
	
}

CString GameController::printChessStep()
{
	return m_record.printChessStep();
}

int GameController::IsGoal()
{
	return m_chess_set.IsGoal();
}

void GameController::GetAllPoint(int x[], int y[], int &light)
{
	m_chess_set.GetAllPoint(x, y, light);
}

void GameController::Save(CArchive &cs)
{
	//m_chess_set.Save(cs);
	m_record.save(cs);
}

void GameController::Load(CArchive &cs)
{
	//m_chess_set.Load(cs);
	m_record.load(cs);
}

bool GameController::GetPlayer()
{
	return m_chess_set.GetPlayer();
}

void GameController::NextStep()
{
	int x1, y1, x2, y2, type, eat;
	m_record.nextChessStep(x1, y1, x2, y2, type, eat);
	m_chess_set.NextStep(x1, y1, x2, y2, type, eat);
}

void GameController::PreviousStep()
{
	int x1, y1, x2, y2, type, eat;
	m_record.lastChessStep(x1, y1, x2, y2, type, eat);
	m_chess_set.PreviousStep(x1, y1, x2, y2, type, eat);
}