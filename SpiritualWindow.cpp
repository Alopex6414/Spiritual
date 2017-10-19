#include "stdafx.h"
#include "Common.h"
#include "SpiritualWindow.h"

/*
** SpiritualWindow构造函数
** SpiritualWindow()
*/
SpiritualWindow::SpiritualWindow()
{
	m_nUserScreenWidth = USER_SCREENWIDTH;		//用户区域宽度
	m_nUserScreenHeight = USER_SCREENHEIGHT;	//用户区域高度
	m_nBitmapWidth = 0;		//Bitmap图片宽度
	m_nBitmapHeight = 0;	//Bitmap图片高度
}

/*
** SpiritualWindow析构函数
** ~SpiritualWindow()
*/
SpiritualWindow::~SpiritualWindow()
{
}

/*
** SpiritualWindow重绘背景
** void SpiritualWindowDrawBitmap(CDC &MemDC, UINT nIDResource)
** Para: CDC &MemDC(DC句柄)
** Para: UINT nIDResource(Bitmap资源ID)
*/
void SpiritualWindow::SpiritualWindowDrawBitmap(CDC &MemDC, UINT nIDResource)
{
	CBitmap Bitmap;
	BITMAPINFO BitmapInfo;

	Bitmap.LoadBitmap(nIDResource);//Bitmap加载资源图片ID
	Bitmap.GetObject(sizeof(BitmapInfo), &BitmapInfo);//BitmapInfo获取资源图片信息
	m_nBitmapWidth = BitmapInfo.bmiHeader.biWidth;//获取Bitmap图片宽度
	m_nBitmapHeight = BitmapInfo.bmiHeader.biHeight;//获取Bitmap图片高度
	MemDC.SelectObject(&Bitmap);//绘制Bitmap到MemDC缓冲区
	Bitmap.~CBitmap();
	DeleteObject(&Bitmap);//释放Bitmap
	DeleteObject(&BitmapInfo);//释放BitmapInfo
}

/*
** SpiritualWindow重绘桌面
** void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC)
** Para: CDC* pDC(pDC窗口句柄指针)
** Para: CDC &MemDC(DC句柄)
*/
void SpiritualWindow::SpiritualWindowReDraw(CDC* pDC, CDC &MemDC)
{
	pDC->StretchBlt(0, 0, m_nUserScreenWidth, m_nUserScreenHeight, &MemDC, 0, 0, m_nBitmapWidth, m_nBitmapHeight, SRCCOPY);
}

/*
** SpiritualWindow重绘桌面(Alpha透明)
** void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC, unsigned char Alpha)
** Para: CDC* pDC(pDC窗口句柄指针)
** Para: CDC &MemDC(DC句柄)
** Para: unsigned char Alpha(Alpha通道透明度值(0~255))
*/
void SpiritualWindow::SpiritualWindowReDraw(CDC* pDC, CDC &MemDC, unsigned char Alpha)
{
	BLENDFUNCTION Blendfunction;

	Blendfunction.BlendOp = AC_SRC_OVER;
	Blendfunction.BlendFlags = 0;
	Blendfunction.AlphaFormat = 0;
	Blendfunction.SourceConstantAlpha = Alpha;
	pDC->AlphaBlend(0, 0, m_nUserScreenWidth, m_nUserScreenHeight, &MemDC, 0, 0, m_nBitmapWidth, m_nBitmapHeight, Blendfunction);
}
