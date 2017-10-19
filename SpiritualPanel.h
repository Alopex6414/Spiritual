#pragma once
class SpiritualPanel
{
private:
	bool m_bIsVisialbe;//�ؼ��ɼ���
	int m_nPosX;//�ؼ�X����
	int m_nPosY;//�ؼ�Y����
	int m_nWidth;//�ؼ����
	int m_nHeight;//�ؼ��߶�
	UCHAR m_ucRValue;//�ؼ���ɫRͨ��
	UCHAR m_ucGValue;//�ؼ���ɫGͨ��
	UCHAR m_ucBValue;//�ؼ���ɫBͨ��
	UCHAR m_ucAlphaValue;//�ؼ���ɫAlphaͨ��
	CImage m_IPanelImage;//�ؼ�ͼƬ

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

