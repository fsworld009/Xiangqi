// XiangqiView.cpp : CXiangqiView ���O����@
//

#include "stdafx.h"
#include "Xiangqi.h"

#include "XiangqiDoc.h"
#include "XiangqiView.h"
#include "XiangqiRecordView.h"
#include "MainFrm.h"

#include "BitMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXiangqiView

IMPLEMENT_DYNCREATE(CXiangqiView, CView)

BEGIN_MESSAGE_MAP(CXiangqiView, CView)
	// �зǦC�L�R�O
	//ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
//	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CXiangqiView �غc/�Ѻc

CXiangqiView::CXiangqiView()
{
	// TODO: �b���[�J�غc�{���X
	m_pDCMemDB = 0;
	m_pBmpDB = 0;
}

CXiangqiView::~CXiangqiView()
{
	if(m_pDCMemDB)
		delete m_pDCMemDB;
	if(m_pBmpDB)
		delete m_pBmpDB;
}

BOOL CXiangqiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CView::PreCreateWindow(cs);
}

// CXiangqiView �yø

void CXiangqiView::OnDraw(CDC* pDC)
{
	
	CXiangqiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawBitMap(pDC,IDC_BOARD,0,0,601,661,0,0,SRCCOPY);

	//DwarChess
	/*
	Resource ID
	Basis:50000, Black:+000 Red:+100
	             Catalogy:+00~60
				 Choose: +0 false +1 true
				 ChessSet ID: 0~15 Red, 16~31 Black
	*/
	int chess_pos_x[32], chess_pos_y[32];
	int choose_id;
	pDoc->GetGameController()->GetAllPoint(chess_pos_x,chess_pos_y,choose_id);
	TRACE("Choose ID: %d\n", choose_id);

	UINT resource_id;
	int chess_id;
	for(unsigned i=0;i<32;i++){
		//(x,y) -> pixel
		chess_pos_x[i] = (chess_pos_x[i])*60-15;
		chess_pos_y[i] = (chess_pos_y[i])*60-15;;
		if(i>=16){
			//black
			chess_id = i-16;
			resource_id=50100;
		}else{
			//red
			chess_id = i;
			resource_id=50000;
		}

		switch(chess_id){
		case 0: case 1: case 2: case 3: case 4:
			resource_id += 0;
			break;
		case 5: case 6:
			resource_id += 10;
			break;
		case 7: case 8:
			resource_id += 20;
			break;
		case 9: case 10:
			resource_id += 30;
			break;
		case 11: case 12:
			resource_id += 40;
			break;
		case 13: case 14:
			resource_id += 50;
			break;
		case 15:
			resource_id += 60;
			break;
		}
		if(i==choose_id)
			resource_id+=1;
		DrawSprite(pDC,resource_id,chess_pos_x[i],chess_pos_y[i],30,30,0,0,RGB(255,0,255));
		//TRACE("%d\n", resource_id);
	}
	// TODO: �b���[�J��͸�ƪ��yø�{���X

}


// CXiangqiView �C�L

BOOL CXiangqiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �w�]���ǳƦC�L�{���X
	return DoPreparePrinting(pInfo);
}

void CXiangqiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�e�B�~����l�]�w
}

void CXiangqiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �[�J�C�L�᪺�M���{���X
}


// CXiangqiView �E�_

#ifdef _DEBUG
void CXiangqiView::AssertValid() const
{
	CView::AssertValid();
}

void CXiangqiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXiangqiDoc* CXiangqiView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXiangqiDoc)));
	return (CXiangqiDoc*)m_pDocument;
}
#endif //_DEBUG


// CXiangqiView �T���B�z�`��

void CXiangqiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXiangqiDoc* pDoc = GetDocument();
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	if(pDoc->GameStart()){
		int i=point.x;
		int j=point.y;
		i=i+15;
		i=i/30;
		j=j-15;
		j=j/30;
		if(i%2==0 && j%2==1){	//in bound
			i = i/2;
			j = j/2+1;
			TRACE("(%d, %d)\n",i,j);
			pDoc->Action(i,j);
			//InvalidateRect()
			Invalidate(FALSE);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CXiangqiView::PrintMessage(int message_id)
{
	//0: invalid move 1:red win 2: black win
	switch(message_id){
		case 0:
			MessageBox(_T("���B�ǳW"),_T("���~"));
			break;
		case 1:
			MessageBox(_T("�����"),_T("Game Over"));
			MessageBox(_T("�i�� \"���С��x�s����\" �O�s����"),_T("Game Over"));
			break;
		case 2:
			MessageBox(_T("�¤��"),_T("Game Over"));
			MessageBox(_T("�i�� \"���С��x�s����\" �O�s����"),_T("Game Over"));
			break;
	}
}


void CXiangqiView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
	CClientDC dcClient(this);
	OnPrepareDC(&dcClient);

	m_pDCMemDB = new CDC;
	m_pDCMemDB->CreateCompatibleDC(&dcClient);
	m_pDCMemDB->SetMapMode(dcClient.GetMapMode());

}

void CXiangqiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �b���[�J�z���T���B�z�`���{���X
	// ���n�I�s�Ϥ��T���� CView::OnPaint()
	OnPrepareDC(&dc);

	CBitmap *pBmpOld = m_pDCMemDB->SelectObject(m_pBmpDB);

	CRect rectInvalid;
	dc.GetClipBox(&rectInvalid); // logical coordinate

	m_pDCMemDB->SelectClipRgn(NULL);
	m_pDCMemDB->IntersectClipRect(&rectInvalid);

	CBrush brBackground((COLORREF)::GetSysColor(COLOR_WINDOW));
	CBrush *pBrOld = m_pDCMemDB->SelectObject(&brBackground);
	m_pDCMemDB->PatBlt(rectInvalid.left, rectInvalid.top,
					   rectInvalid.Width(), rectInvalid.Height(),
					   PATCOPY);
	m_pDCMemDB->SelectObject(pBrOld);

	OnDraw(m_pDCMemDB);

	dc.BitBlt(rectInvalid.left, rectInvalid.top,
			  rectInvalid.Width(), rectInvalid.Height(),
			  m_pDCMemDB, // MM_TEXT mode
			  rectInvalid.left, rectInvalid.top,
			  SRCCOPY);

	m_pDCMemDB->SelectObject(pBmpOld);


}

void CXiangqiView::OnSize(UINT nType, int cx, int cy)
{
 	CView::OnSize(nType, cx, cy);

	// TODO: �b���[�J�z���T���B�z�`���{���X
	CRect rect;
	GetClientRect(&rect); // device coordinates
						  // API without DC as arguments, 
						  // always use device coordinates

	if ((rect.right <= m_sizeDB.cx) &&
		(rect.bottom <= m_sizeDB.cy)) return;

	if (rect.right > m_sizeDB.cx)
		m_sizeDB.cx = rect.right;

	if (rect.bottom > m_sizeDB.cy)
		m_sizeDB.cy = rect.bottom;

	CClientDC dcClient(this);
	OnPrepareDC(&dcClient); // order dependency: after adjustScrollSizes()

	if (m_pBmpDB) delete m_pBmpDB;
	m_pBmpDB = new CBitmap;
	m_pBmpDB->CreateCompatibleBitmap(&dcClient, m_sizeDB.cx, m_sizeDB.cy);
                        // always in pixels ^^^^^^^^^^^  ^^^^^^^^^^^


}
