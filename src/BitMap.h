#include "stdafx.h"

#pragma once

void DrawBitMap(CDC* pDC, UINT BITMAP_RESOURCE_NAME,int x,int y,int nWidth,int nHeight,int xSrc,int ySrc,DWORD dwRop);
void DrawSprite(CDC* pDC, UINT BITMAP_RESOURCE_NAME,int x,int y,int nWidth,int nHeight,int xSrc,int ySrc, COLORREF rgbMask);