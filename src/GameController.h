#include "chess_set.h"
#include "Record.h"

#pragma once

class GameController
{
public:
	GameController(void);
	int Action(int x, int y);
	void setChessStep(int x1,int y1, int x2, int y2, int chessType, int eat);
	CString printChessStep();
	void GetAllPoint(int x[], int y[], int &light);
	int IsGoal();
	void Save(CArchive &);
	void Load(CArchive &);
	bool GetPlayer();
	void NextStep();
	void PreviousStep();

public:
	virtual ~GameController(void);
private:
	chess_set m_chess_set;
	Record m_record;
};
