// Record.cpp: implementation of the Record class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Record.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Record::Record():nThState(-1)
{

}

Record::~Record()
{

}

void Record::setChessStep(int x1,int y1, int x2, int y2, int chessType, int eat)
{
	nThState++;

	recordData chessRecord;
	chessRecord.x1 = x1;
	chessRecord.y1 = y1;
	chessRecord.x2 = x2;
	chessRecord.y2 = y2;
	chessRecord.chessType = chessType;
	chessRecord.eat = eat;

	allChessRecord.push_back(chessRecord);
}

CString Record::printChessStep()
{
	if(nThState == allChessRecord.size()){
		nThState--;
		return NULL;
	}
	vector<recordData>::iterator nextChessFind = allChessRecord.begin();	//load from vector
	for(int i = 0; i < nThState ; i++){
		nextChessFind++;
	}

	int x1 = nextChessFind -> x1;
	int y1 = nextChessFind -> y1;
	int x2 = nextChessFind -> x2;
	int y2 = nextChessFind -> y2;
	int chessType = nextChessFind -> chessType;
	int eat = nextChessFind -> eat;

	char *chessTypeInChinese;
	//(0~31   0~4兵  5.6炮 7.8口 9.10傌 11.12相 13.14仕 15帥 16~20卒 21.22包 23.24車 25.26馬 27.28象 29.30士 31將)
	switch(chessType){
	case 0: case 1: case 2: case 3: case 4: chessTypeInChinese = "兵" ;break;
	case 5: case 6: chessTypeInChinese = "炮" ;break;
	case 7: case 8: chessTypeInChinese = "硨" ;break;
	case 9: case 10: chessTypeInChinese = "傌" ;break;
	case 11: case 12: chessTypeInChinese = "相" ;break;
	case 13: case 14: chessTypeInChinese = "仕" ;break;
	case 15: chessTypeInChinese = "帥" ;break;

	case 16: case 17: case 18: case 19: case 20: chessTypeInChinese = "卒" ;break;
	case 21: case 22: chessTypeInChinese = "包"; break;
	case 23: case 24: chessTypeInChinese = "車"; break;
	case 25: case 26: chessTypeInChinese = "馬"; break;
	case 27: case 28: chessTypeInChinese = "象"; break;
	case 29: case 30: chessTypeInChinese = "士"; break;
	case 31: chessTypeInChinese = "將"; break;

	default:chessTypeInChinese = " ";
	}

	CString beforeMoveAddress;	//before move
	switch(x1){
	case 1: beforeMoveAddress = "一"; break;
	case 2: beforeMoveAddress = "二"; break;
	case 3: beforeMoveAddress = "三"; break;
	case 4: beforeMoveAddress = "四"; break;
	case 5: beforeMoveAddress = "五"; break;
	case 6: beforeMoveAddress = "六"; break;
	case 7: beforeMoveAddress = "七"; break;
	case 8: beforeMoveAddress = "八"; break;
	case 9: beforeMoveAddress = "九"; break;
	
	default: beforeMoveAddress  = " ";
	}
	CString chessMoveWay;		//move way
	if( chessType < 16 ){
		if(y1 == y2)
			chessMoveWay = "平";
		if(y1 > y2)
			chessMoveWay = "進";
		if(y1 < y2)
			chessMoveWay = "退";	
	}
	else{
		if(y1 == y2)
			chessMoveWay = "平";
		if(y1 < y2)
			chessMoveWay = "進";
		if(y1 > y2)
			chessMoveWay = "退";	
	}

	CString afterMoveAddress;		//after move
	if(chessTypeInChinese == "兵" || chessTypeInChinese == "卒" || chessTypeInChinese == "車" || chessTypeInChinese == "硨" || chessTypeInChinese == "包" || chessTypeInChinese == "炮" || chessTypeInChinese == "將" || chessTypeInChinese == "帥")
	{
		if(chessMoveWay == "進")
		{
			switch(y2 - y1){
				case 1: case -1: afterMoveAddress = "一"; break;
				case 2: case -2: afterMoveAddress = "二"; break;
				case 3: case -3: afterMoveAddress = "三"; break;
				case 4: case -4: afterMoveAddress = "四"; break;
				case 5: case -5: afterMoveAddress = "五"; break;
				case 6: case -6: afterMoveAddress = "六"; break;
				case 7: case -7: afterMoveAddress = "七"; break;
				case 8: case -8: afterMoveAddress = "八"; break;
				case 9: case -9: afterMoveAddress = "九"; break;

				default: afterMoveAddress = " ";
			}
		}
		else if(chessMoveWay == "退")
		{
			switch(y1 - y2){
				case 1:case -1: afterMoveAddress = "一"; break;
				case 2:case -2: afterMoveAddress = "二"; break;
				case 3:case -3: afterMoveAddress = "三"; break;
				case 4:case -4: afterMoveAddress = "四"; break;
				case 5:case -5: afterMoveAddress = "五"; break;
				case 6:case -6: afterMoveAddress = "六"; break;
				case 7:case -7: afterMoveAddress = "七"; break;
				case 8:case -8: afterMoveAddress = "八"; break;
				case 9:case -9: afterMoveAddress = "九"; break;

				default: afterMoveAddress = " ";
			}
		}
		else
		{
			switch(x2){
			case 1: afterMoveAddress = "一"; break;
			case 2: afterMoveAddress = "二"; break;
			case 3: afterMoveAddress = "三"; break;
			case 4: afterMoveAddress = "四"; break;
			case 5: afterMoveAddress = "五"; break;
			case 6: afterMoveAddress = "六"; break;
			case 7: afterMoveAddress = "七"; break;
			case 8: afterMoveAddress = "八"; break;
			case 9: afterMoveAddress = "九"; break;
		
			default: afterMoveAddress = " ";
			}
		}
	}
	else
	{
		switch(x2){
	case 1: afterMoveAddress = "一"; break;
	case 2: afterMoveAddress = "二"; break;
	case 3: afterMoveAddress = "三"; break;
	case 4: afterMoveAddress = "四"; break;
	case 5: afterMoveAddress = "五"; break;
	case 6: afterMoveAddress = "六"; break;
	case 7: afterMoveAddress = "七"; break;
	case 8: afterMoveAddress = "八"; break;
	case 9: afterMoveAddress = "九"; break;

	default: afterMoveAddress = " ";
		}
	}

	
	CString fourWordStep(chessTypeInChinese);
	fourWordStep = fourWordStep + beforeMoveAddress;
	fourWordStep = fourWordStep + chessMoveWay;
	fourWordStep = fourWordStep + afterMoveAddress;
	return fourWordStep;
}

void Record::nextChessStep(int &x1, int &y1, int &x2, int &y2, int &chessType, int &eat)
{
	nThState++;
	vector<recordData>::iterator nextChessFind = allChessRecord.begin();	//load from vector
	if(nThState < allChessRecord.size()){
		nextChessFind += nThState;
	}else{
		nextChessFind = allChessRecord.end()-1;
	}

	x1 = nextChessFind -> x1;
	y1 = nextChessFind -> y1;
	x2 = nextChessFind -> x2;
	y2 = nextChessFind -> y2;
	chessType = nextChessFind -> chessType;
	eat = nextChessFind -> eat;
}

void Record::lastChessStep(int &x1, int &y1, int &x2, int &y2, int &chessType, int &eat)
{	
	if(nThState == -1)
		nThState++;
	vector<recordData>::iterator lastChessFind = allChessRecord.begin();	//load from vector
	lastChessFind += nThState;
	if(nThState != -1)
		nThState--;
//	for(int i = 0; i < nThState-1 ; i++){
//		lastChessFind++;
//	}
	x1 = lastChessFind -> x1;
	y1 = lastChessFind -> y1;
	x2 = lastChessFind -> x2;
	y2 = lastChessFind -> y2;
	chessType = lastChessFind -> chessType;
	eat = lastChessFind -> eat;
}

void Record::save(CArchive &saveData)
{
	saveData << allChessRecord.size();
	vector<recordData>::iterator chessSave = allChessRecord.begin();	//load from vector
	for(int i = 0 ; i < allChessRecord.size() ; i++)
	{

		saveData << chessSave->x1;
		saveData << chessSave->y1;
		saveData << chessSave->x2;
		saveData << chessSave->y2;
		saveData << chessSave->chessType;
		saveData << chessSave->eat;
		chessSave++;
	}
}

void Record::load(CArchive &loadData)
{
	int record_size;
	loadData >> record_size;
	//vector<recordData>::iterator chessLoad = allChessRecord.begin();	//load from vector
	recordData chessLoad={0};
	for(int i = 0 ; i < record_size ; i++)
	{
		loadData >> chessLoad.x1;
		loadData >> chessLoad.y1;
		loadData >> chessLoad.x2;
		loadData >> chessLoad.y2;
		loadData >> chessLoad.chessType;
		loadData >> chessLoad.eat;
		allChessRecord.push_back(chessLoad);
		/*loadData >> chessLoad->x1;
		loadData >> chessLoad->y1;
		loadData >> chessLoad->x2;
		loadData >> chessLoad->y2;
		loadData >> chessLoad->chessType;
		loadData >> chessLoad->eat;
		chessLoad++;*/
	}
}