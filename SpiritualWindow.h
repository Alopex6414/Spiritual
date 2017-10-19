#pragma once
class SpiritualWindow
{
private:
	int m_nUserScreenWidth;		//�û�������
	int m_nUserScreenHeight;		//�û�����߶�
	int m_nBitmapWidth;				//BitmapͼƬ���
	int m_nBitmapHeight;				//BitmapͼƬ�߶�

public:
	SpiritualWindow();
	~SpiritualWindow();
	void SpiritualWindowDrawBitmap(CDC &MemDC, UINT nIDResource);
	void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC);
	void SpiritualWindowReDraw(CDC* pDC, CDC &MemDC, unsigned char Alpha);
};

