#include "stdafx.h"
#include "Common.h"
#include "SpiritualWindow.h"

/*
** SpiritualWindow���캯��
** SpiritualWindow()
*/
SpiritualWindow::SpiritualWindow()
{
	m_nUserScreenWidth = USER_SCREENWIDTH;		//�û�������
	m_nUserScreenHeight = USER_SCREENHEIGHT;	//�û�����߶�
	m_nBitmapWidth = 0;		//BitmapͼƬ���
	m_nBitmapHeight = 0;	//BitmapͼƬ�߶�
}

/*
** SpiritualWindow��������
** ~SpiritualWindow()
*/
SpiritualWindow::~SpiritualWindow()
{
}

/*
** SpiritualWindow�ػ汳��
** void SpiritualWindowDrawBitmap(CDC &MemDC, UINT nIDResource)
** Para: CDC &MemDC(DC���)
** Para: UINT nIDResource(Bitmap��ԴID)
*/
void SpiritualWindow::SpiritualWindowDrawBitmap(CDC &MemDC, UINT nIDResource)
{
	CBitmap Bitmap;
	BITMAPINFO BitmapInfo;

	Bitmap.LoadBitmap(nIDResource);//Bitmap������ԴͼƬID
	Bitmap.GetObject(sizeof(BitmapInfo), &BitmapInfo);//BitmapInfo��ȡ��ԴͼƬ��Ϣ
	m_nBitmapWidth = BitmapInfo.bmiHeader.biWidth;//��ȡBitmapͼƬ���
	m_nBitmapHeight = BitmapInfo.bmiHeader.biHeight;//��ȡBitmapͼƬ�߶�
	MemDC.SelectObject(&Bitmap);//����Bitmap��MemDC������
	Bitmap.~CBitmap();
	DeleteObject(&Bitmap);//�ͷ�Bitmap
	DeleteObject(&BitmapInfo);//�ͷ�BitmapInfo
}

/*
** SpiritualWindow�ػ�����
** void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC)
** Para: CDC* pDC(pDC���ھ��ָ��)
** Para: CDC &MemDC(DC���)
*/
void SpiritualWindow::SpiritualWindowReDraw(CDC* pDC, CDC &MemDC)
{
	pDC->StretchBlt(0, 0, m_nUserScreenWidth, m_nUserScreenHeight, &MemDC, 0, 0, m_nBitmapWidth, m_nBitmapHeight, SRCCOPY);
}

/*
** SpiritualWindow�ػ�����(Alpha͸��)
** void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC, unsigned char Alpha)
** Para: CDC* pDC(pDC���ھ��ָ��)
** Para: CDC &MemDC(DC���)
** Para: unsigned char Alpha(Alphaͨ��͸����ֵ(0~255))
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
