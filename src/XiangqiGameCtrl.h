#pragma once
#include "afxwin.h"



// CXiangqiGameCtrl ����˵�

class CXiangqiGameCtrl : public CFormView
{
	DECLARE_DYNCREATE(CXiangqiGameCtrl)

protected:
	CXiangqiGameCtrl();           // �ʺA�إߩҨϥΪ��O�@�غc�禡
	virtual ~CXiangqiGameCtrl();

public:
	enum { IDD = IDD_XIANGQIGAMECTRL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	void NewGame(int mode);
	void ChangePlayer();
	void GameOver();
	afx_msg void OnBnClickedUndo();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	CRect m_TimerRefreshRect;
	bool m_player;			//true=red,false=black.
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedNextStep();
	afx_msg void OnBnClickedPreStep();
};


