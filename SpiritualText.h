#pragma once
class SpiritualText
{
private:
	bool m_bIsVisialbe;//控件可见性
	int m_nPosX;//控件X坐标
	int m_nPosY;//控件Y坐标
	int m_nWidth;//控件宽度
	int m_nHeight;//控件高度
	int m_nFontSize;//Text字体大小
	CString m_sFontType;//Text字体类型

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

