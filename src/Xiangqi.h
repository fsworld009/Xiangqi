// Xiangqi.h : Xiangqi ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CXiangqiApp:
// �аѾ\��@�����O�� Xiangqi.cpp
//

class CXiangqiApp : public CWinApp
{
public:
	CXiangqiApp();


// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CXiangqiApp theApp;