#pragma once
class SpiritualWindow
{
private:
	int m_nUserScreenWidth;		//用户区域宽度
	int m_nUserScreenHeight;		//用户区域高度
	int m_nBitmapWidth;				//Bitmap图片宽度
	int m_nBitmapHeight;				//Bitmap图片高度

public:
	SpiritualWindow();
	~SpiritualWindow();
	void SpiritualWindowDrawBitmap(CDC &MemDC, UINT nIDResource);
	void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC);
	void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC, unsigned char Alpha);
};

