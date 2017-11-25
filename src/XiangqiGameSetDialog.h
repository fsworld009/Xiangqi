#pragma once
#include "afxwin.h"


// CXiangqiGameSetDialog 對話方塊

class CXiangqiGameSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CXiangqiGameSetDialog)

public:
	CXiangqiGameSetDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CXiangqiGameSetDialog();

// 對話方塊資料
	enum { IDD = IDD_GAMESETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	int m_time;
};
