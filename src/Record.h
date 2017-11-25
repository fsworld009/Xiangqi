// Record.h: interface for the Record class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORD_H__5088D2DA_6CAD_40C3_AE78_612B955ECA4E__INCLUDED_)
#define AFX_RECORD_H__5088D2DA_6CAD_40C3_AE78_612B955ECA4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<afxwin.h>
#include<vector>

using namespace std;

struct recordData{
	int x1;
	int y1;
	int x2;
	int y2;
	int chessType;
	int eat;
};
class Record  
{
public:
	void lastChessStep(int &x1, int &y1, int &x2, int &y2, int &chessType, int &eat);
	void nextChessStep(int &x1, int &y1, int &x2, int &y2, int &chessType, int &eat);
	CString printChessStep();
	void setChessStep(int x1,int y1, int x2, int y2, int chessType, int eat);
	Record();
	virtual ~Record();
	void save(CArchive &saveData);
	void load(CArchive &loadData);
private:
	vector<recordData>allChessRecord;
	int nThState;
	void save(void);
};

#endif // !defined(AFX_RECORD_H__5088D2DA_6CAD_40C3_AE78_612B955ECA4E__INCLUDED_)
