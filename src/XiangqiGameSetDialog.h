#pragma once
#include "afxwin.h"


// CXiangqiGameSetDialog ��ܤ��

class CXiangqiGameSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CXiangqiGameSetDialog)

public:
	CXiangqiGameSetDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CXiangqiGameSetDialog();

// ��ܤ�����
	enum { IDD = IDD_GAMESETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	int m_time;
};
