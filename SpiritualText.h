#pragma once
class SpiritualText
{
private:
	bool m_bIsVisialbe;//�ؼ��ɼ���
	int m_nPosX;//�ؼ�X����
	int m_nPosY;//�ؼ�Y����
	int m_nWidth;//�ؼ����
	int m_nHeight;//�ؼ��߶�
	int m_nFontSize;//Text�����С
	CString m_sFontType;//Text��������

public:
	SpiritualText();
	~SpiritualText();
	SpiritualText(int PosX, int PosY, int Width, int Height, int FontSize, CString FontType);
	int SpiritualTextGetWidth(void);
	void SpiritualTextDrawOut(CDC &MemDC, CString Text);
	void SpiritualTextDrawOutCenter(CDC &MemDC, CString Text);
	void SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, CString Text);
	void SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CString Text);
	void SpiritualTextDrawOutCenter(CDC &MemDC, CString Text, int PosX, int Width);
	void SpiritualTextDrawOutMove(CDC &MemDC, CString Text, int PosX, int Width);
	void SpiritualTextDrawBackGround(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CPoint MousePoint);
	bool SpiritualTextIsClick(CPoint MousePoint);
};

