// XiangqiDoc.h : CXiangqiDoc 類別的介面
//
#include "GameController.h"

#pragma once


class CXiangqiDoc : public CDocument
{
protected: // 僅從序列化建立
	CXiangqiDoc();
	DECLARE_DYNCREATE(CXiangqiDoc)

// 屬性
public:

// 作業
public:

// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 程式碼實作
public:
	virtual ~CXiangqiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
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


