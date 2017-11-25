// XiangqiDoc.h : CXiangqiDoc ���O������
//
#include "GameController.h"

#pragma once


class CXiangqiDoc : public CDocument
{
protected: // �ȱq�ǦC�ƫإ�
	CXiangqiDoc();
	DECLARE_DYNCREATE(CXiangqiDoc)

// �ݩ�
public:

// �@�~
public:

// �мg
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �{���X��@
public:
	virtual ~CXiangqiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGamesetting();
public:
	int GetRemainTime();
	void ReduceTime();
	void ResetTime();
	void GameOver(bool who_is_win);
	GameController* GetGameController();
	bool SetGameState(bool game_running);
	bool GameStart();
	void Action(int x,int y);
	void NewGame(int mode);
	
public:
	afx_msg void OnFileNew();


private:
	int m_time;
	int m_current_time;
	GameController* m_game;
	bool m_game_start;
};


