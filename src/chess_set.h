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
		int x;				//x�y��
		int y;				//y�y��
		bool is_dead;		//�ͩΦ�
	};

	bool check_rule(int &index, int x, int y); //�ˬd�W�h

	bool player_1;			//�C����
	chess chesses[32];		//�s��Ѥl
	int record_index;       //�s�񪺬O��Ѥl
	bool selected;			//�O�_�w����Ѥl
	chess record_chess;		//�w�Q������Ѥl
};
