#pragma once

#include "Record.h"
class chess_set
{
public:
	chess_set(void);
	virtual ~chess_set(void);
	int Action(int x, int y,Record& m_record);
	void GetAllPoint(int x[], int y[], int &light);
	int IsGoal();
	void Save(CArchive &ar);
	void Load(CArchive &ar);
	bool GetPlayer();
	void NextStep(int x1, int y1, int x2, int y2, int chessType, int eat);
	void PreviousStep(int x1, int y1, int x2, int y2, int chessType, int eat);

private:

	typedef struct chess
	{
		int x;				//x座標
		int y;				//y座標
		bool is_dead;		//生或死
	};

	bool check_rule(int &index, int x, int y); //檢查規則

	bool player_1;			//遊戲者
	chess chesses[32];		//存放棋子
	int record_index;       //存放的是何棋子
	bool selected;			//是否已選取棋子
	chess record_chess;		//已被選取的棋子
};
