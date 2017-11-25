#include "StdAfx.h"
#include "BitMap.h"

void DrawBitMap(CDC* pDC, UINT BITMAP_RESOURCE_NAME,int x,int y,int nWidth,int nHeight,int xSrc,int ySrc,DWORD dwRop)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap BM_Board, *BM_Board_old;
	BM_Board.LoadBitmapW(BITMAP_RESOURCE_NAME);
	BM_Board_old = dcMem.SelectObject(&BM_Board);
	pDC->BitBlt(x,y,nWidth,nHeight,&dcMem,xSrc,ySrc,dwRop);
	dcMem.SelectObject(BM_Board_old);
}

void DrawSprite(CDC* pDC, UINT BITMAP_RESOURCE_NAME,int x,int y,int nWidth,int nHeight,int xSrc,int ySrc, COLORREF rgbMask=RGB(0,0,0))
{
	CDC dcMem, dcMask;
	CBitmap BM_Board, *pBM_Board_old, BM_Mask, *pBM_Mask_old;
		
	BM_Board.LoadBitmap(BITMAP_RESOURCE_NAME);
	dcMem.CreateCompatibleDC(pDC);
	pBM_Board_old = dcMem.SelectObject(&BM_Board);

	BM_Mask.CreateBitmap(nWidth,nHeight,1,1,NULL);
	dcMask.CreateCompatibleDC(pDC); 
	pBM_Mask_old = dcMask.SelectObject(&BM_Mask);

	//???
	dcMem.SetBkColor(rgbMask); 
	dcMask.BitBlt(0, 0, nWidth, nHeight, &dcMem, 0,0, SRCCOPY ); 

	dcMem.SetBkColor(RGB(0,0,0)); 
	dcMem.SetTextColor(RGB(255,255,255)); 
	dcMem.BitBlt(0, 0, nWidth, nHeight, &dcMask, 0,0, SRCAND); 
	//???

	pDC->BitBlt(x,y,nWidth,nHeight, &dcMask, xSrc,ySrc, SRCAND); 
	pDC->BitBlt(x,y,nWidth,nHeight, &dcMem, xSrc,ySrc,SRCPAINT); 

	dcMask.SelectObject(pBM_Board_old);
	dcMem.SelectObject(pBM_Mask_old);

}