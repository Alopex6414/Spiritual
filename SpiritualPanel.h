#pragma once
class SpiritualPanel
{
private:
	bool m_bIsVisialbe;//控件可见性
	int m_nPosX;//控件X坐标
	int m_nPosY;//控件Y坐标
	int m_nWidth;//控件宽度
	int m_nHeight;//控件高度
	UCHAR m_ucRValue;//控件颜色R通道
	UCHAR m_ucGValue;//控件颜色G通道
	UCHAR m_ucBValue;//控件颜色B通道
	UCHAR m_ucAlphaValue;//控件颜色Alpha通道
	CImage m_IPanelImage;//控件图片

public:
	SpiritualPanel();
	~SpiritualPanel();
	SpiritualPanel(int PosX, int PosY, int Width, int Height);
	void SpiritualPanelLoadTitle(CString SpiritualPanelFileName);
	void SpiritualPanelLoadImage(CString SpiritualPanelFileName);
	void SpiritualPanelDrawImage(CDC &MemDC);
	void SpiritualPanelDrawImage(CDC &MemDC, int Alpha);
	void SpiritualPanelDrawImage(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor);
	void SpiritualPanelDrawImage(CDC &MemDC, int Width, int Height, COLORREF PenColor, COLORREF BrushColor);
	void SpiritualPanelDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, COLORREF PenColor, COLORREF BrushColor);
	void SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue);
	void SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue, UCHAR AlphaValue);
	bool SpiritualPanelIsClick(CPoint MousePoint);
	void SpiritualPanelReDrawAlpha(CDC* pDC, CDC &MemDC, int Alpha);
};

