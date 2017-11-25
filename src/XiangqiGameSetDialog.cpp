// XiangqiGameSetDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "Xiangqi.h"
#include "XiangqiGameSetDialog.h"


// CXiangqiGameSetDialog 對話方塊

IMPLEMENT_DYNAMIC(CXiangqiGameSetDialog, CDialog)

CXiangqiGameSetDialog::CXiangqiGameSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CXiangqiGameSetDialog::IDD, pParent), m_time(120)
{

}

CXiangqiGameSetDialog::~CXiangqiGameSetDialog()
{
}

void CXiangqiGameSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDV_MinMaxInt(pDX, m_time, 10, 180);
}


BEGIN_MESSAGE_MAP(CXiangqiGameSetDialog, CDialog)
END_MESSAGE_MAP()


// CXiangqiGameSetDialog 訊息處理常式
