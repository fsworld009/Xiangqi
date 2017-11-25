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
	//(0~31   0~4�L  5.6�� 7.8�f 9.10�X 11.12�� 13.14�K 15�� 16~20�� 21.22�] 23.24�� 25.26�� 27.28�H 29.30�h 31�N)
	switch(chessType){
	case 0: case 1: case 2: case 3: case 4: chessTypeInChinese = "�L" ;break;
	case 5: case 6: chessTypeInChinese = "��" ;break;
	case 7: case 8: chessTypeInChinese = "��" ;break;
	case 9: case 10: chessTypeInChinese = "�X" ;break;
	case 11: case 12: chessTypeInChinese = "��" ;break;
	case 13: case 14: chessTypeInChinese = "�K" ;break;
	case 15: chessTypeInChinese = "��" ;break;

	case 16: case 17: case 18: case 19: case 20: chessTypeInChinese = "��" ;break;
	case 21: case 22: chessTypeInChinese = "�]"; break;
	case 23: case 24: chessTypeInChinese = "��"; break;
	case 25: case 26: chessTypeInChinese = "��"; break;
	case 27: case 28: chessTypeInChinese = "�H"; break;
	case 29: case 30: chessTypeInChinese = "�h"; break;
	case 31: chessTypeInChinese = "�N"; break;

	default:chessTypeInChinese = " ";
	}

	CString beforeMoveAddress;	//before move
	switch(x1){
	case 1: beforeMoveAddress = "�@"; break;
	case 2: beforeMoveAddress = "�G"; break;
	case 3: beforeMoveAddress = "�T"; break;
	case 4: beforeMoveAddress = "�|"; break;
	case 5: beforeMoveAddress = "��"; break;
	case 6: beforeMoveAddress = "��"; break;
	case 7: beforeMoveAddress = "�C"; break;
	case 8: beforeMoveAddress = "�K"; break;
	case 9: beforeMoveAddress = "�E"; break;
	
	default: beforeMoveAddress  = " ";
	}
	CString chessMoveWay;		//move way
	if( chessType < 16 ){
		if(y1 == y2)
			chessMoveWay = "��";
		if(y1 > y2)
			chessMoveWay = "�i";
		if(y1 < y2)
			chessMoveWay = "�h";	
	}
	else{
		if(y1 == y2)
			chessMoveWay = "��";
		if(y1 < y2)
			chessMoveWay = "�i";
		if(y1 > y2)
			chessMoveWay = "�h";	
	}

	CString afterMoveAddress;		//after move
	if(chessTypeInChinese == "�L" || chessTypeInChinese == "��" || chessTypeInChinese == "��" || chessTypeInChinese == "��" || chessTypeInChinese == "�]" || chessTypeInChinese == "��" || chessTypeInChinese == "�N" || chessTypeInChinese == "��")
	{
		if(chessMoveWay == "�i")
		{
			switch(y2 - y1){
				case 1: case -1: afterMoveAddress = "�@"; break;
				case 2: case -2: afterMoveAddress = "�G"; break;
				case 3: case -3: afterMoveAddress = "�T"; break;
				case 4: case -4: afterMoveAddress = "�|"; break;
				case 5: case -5: afterMoveAddress = "��"; break;
				case 6: case -6: afterMoveAddress = "��"; break;
				case 7: case -7: afterMoveAddress = "�C"; break;
				case 8: case -8: afterMoveAddress = "�K"; break;
				case 9: case -9: afterMoveAddress = "�E"; break;

				default: afterMoveAddress = " ";
			}
		}
		else if(chessMoveWay == "�h")
		{
			switch(y1 - y2){
				case 1:case -1: afterMoveAddress = "�@"; break;
				case 2:case -2: afterMoveAddress = "�G"; break;
				case 3:case -3: afterMoveAddress = "�T"; break;
				case 4:case -4: afterMoveAddress = "�|"; break;
				case 5:case -5: afterMoveAddress = "��"; break;
				case 6:case -6: afterMoveAddress = "��"; break;
				case 7:case -7: afterMoveAddress = "�C"; break;
				case 8:case -8: afterMoveAddress = "�K"; break;
				case 9:case -9: afterMoveAddress = "�E"; break;

				default: afterMoveAddress = " ";
			}
		}
		else
		{
			switch(x2){
			case 1: afterMoveAddress = "�@"; break;
			case 2: afterMoveAddress = "�G"; break;
			case 3: afterMoveAddress = "�T"; break;
			case 4: afterMoveAddress = "�|"; break;
			case 5: afterMoveAddress = "��"; break;
			case 6: afterMoveAddress = "��"; break;
			case 7: afterMoveAddress = "�C"; break;
			case 8: afterMoveAddress = "�K"; break;
			case 9: afterMoveAddress = "�E"; break;
		
			default: afterMoveAddress = " ";
			}
		}
	}
	else
	{
		switch(x2){
	case 1: afterMoveAddress = "�@"; break;
	case 2: afterMoveAddress = "�G"; break;
	case 3: afterMoveAddress = "�T"; break;
	case 4: afterMoveAddress = "�|"; break;
	case 5: afterMoveAddress = "��"; break;
	case 6: afterMoveAddress = "��"; break;
	case 7: afterMoveAddress = "�C"; break;
	case 8: afterMoveAddress = "�K"; break;
	case 9: afterMoveAddress = "�E"; break;

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