#include "stdafx.h"
#include "Common.h"
#include "SpiritualPanel.h"

/*
** SpiritualPanel���캯��
** SpiritualPanel()
*/
SpiritualPanel::SpiritualPanel()
{
	m_bIsVisialbe = true;
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_ucRValue = 255;
	m_ucGValue = 255;
	m_ucBValue = 255;
	m_ucAlphaValue = 255;
}

/*
** SpiritualPanel��������
** ~SpiritualPanel()
*/
SpiritualPanel::~SpiritualPanel()
{
	m_IPanelImage.Destroy();
}

/*
** SpiritualPanel���캯��(����+1)
** SpiritualPanel()
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
*/
SpiritualPanel::SpiritualPanel(int PosX, int PosY, int Width, int Height)
{
	m_bIsVisialbe = true;
	m_nPosX = PosX;
	m_nPosY = PosY;
	m_nWidth = Width;
	m_nHeight = Height;
	m_ucRValue = 255;
	m_ucGValue = 255;
	m_ucBValue = 255;
	m_ucAlphaValue = 255;
}

/*
** SpiritualPanel���ر���ͼƬ(Small)
** void SpiritualPanelLoadTitle(CString SpiritualPanelFileName)
** Para: CString SpiritualPanelFileName(ͼƬ·��)
*/
void SpiritualPanel::SpiritualPanelLoadTitle(CString SpiritualPanelFileName)
{
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\Resource\\Title\\";
	NowPath += SpiritualPanelFileName;
	m_IPanelImage.Load(NowPath);

	if(m_IPanelImage.GetBPP() == 32)//����Alphaͨ��
	{
		for(int i = 0; i < m_IPanelImage.GetWidth(); i++)
		{
			for(int j = 0; j < m_IPanelImage.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_IPanelImage.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
}

/*
** SpiritualPanel����ͼƬ
** void SpiritualPanelLoadImage(CString SpiritualPanelFileName)
** Para: CString SpiritualPanelFileName(ͼƬ·��)
*/
void SpiritualPanel::SpiritualPanelLoadImage(CString SpiritualPanelFileName)
{
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\Resource\\Panel\\";
	NowPath += SpiritualPanelFileName;
	m_IPanelImage.Load(NowPath);

	if(m_IPanelImage.GetBPP() == 32)//����Alphaͨ��
	{
		for(int i = 0; i < m_IPanelImage.GetWidth(); i++)
		{
			for(int j = 0; j < m_IPanelImage.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_IPanelImage.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
}

/*
** SpiritualPanel�ػ�ͼƬ
** void SpiritualPanelDrawImage(CDC &MemDC)
** Para: CDC &MemDC(DC���)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC)
{
	m_IPanelImage.Draw(MemDC.m_hDC, m_nPosX, m_nPosY);
}

/*
** SpiritualPanel�ػ�ͼƬ(����+1)
** void SpiritualPanelDrawImage(CDC &MemDC, int Alpha)
** Para: CDC &MemDC(DC���)
** Para: int Alpha(Alpha͸����)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, int Alpha)
{
	m_IPanelImage.AlphaBlend(MemDC.m_hDC, m_nPosX, m_nPosY, Alpha);
}

/*
** SpiritualPanel�ػ�ͼƬ(����+2)
** void SpiritualPanelDrawImage(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor)
** Para: CDC &MemDC(DC���)
** Para: COLORREF PenColor(������ɫ)
** Para: COLORREF BrushColor(��ˢ��ɫ)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor)
{
	CPen Pen;
	CBrush Brush;

	Pen.CreatePen(PS_SOLID, 1, PenColor);
	Brush.CreateSolidBrush(BrushColor);
	MemDC.SelectObject(&Pen);
	MemDC.SelectObject(&Brush);
	MemDC.Rectangle(m_nPosX, m_nPosY, (m_nPosX + m_nWidth), (m_nPosY + m_nHeight));
	Pen.~CPen();
	Brush.~CBrush();
	DeleteObject(&Pen);
	DeleteObject(&Brush);
}

/*
** SpiritualPanel�ػ�ͼƬ(����+3)
** void SpiritualPanelDrawImage(CDC &MemDC, int Width, int Height, COLORREF PenColor, COLORREF BrushColor)
** Para: CDC &MemDC(DC���)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
** Para: COLORREF PenColor(������ɫ)
** Para: COLORREF BrushColor(��ˢ��ɫ)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, int Width, int Height, COLORREF PenColor, COLORREF BrushColor)
{
	CPen Pen;
	CBrush Brush;

	m_nWidth = Width;
	m_nHeight = Height;
	Pen.CreatePen(PS_SOLID, 1, PenColor);
	Brush.CreateSolidBrush(BrushColor);
	MemDC.SelectObject(&Pen);
	MemDC.SelectObject(&Brush);
	MemDC.Rectangle(m_nPosX, m_nPosY, (m_nPosX + m_nWidth), (m_nPosY + m_nHeight));
	Pen.~CPen();
	Brush.~CBrush();
	DeleteObject(&Pen);
	DeleteObject(&Brush);
}

/*
** SpiritualPanel�ػ�ͼƬ(����+4)
** void SpiritualPanelDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, COLORREF PenColor, COLORREF BrushColor)
** Para: CDC &MemDC(DC���)
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
** Para: COLORREF PenColor(������ɫ)
** Para: COLORREF BrushColor(��ˢ��ɫ)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, COLORREF PenColor, COLORREF BrushColor)
{
	CPen Pen;
	CBrush Brush;

	Pen.CreatePen(PS_SOLID, 1, PenColor);
	Brush.CreateSolidBrush(BrushColor);
	MemDC.SelectObject(&Pen);
	MemDC.SelectObject(&Brush);
	MemDC.Rectangle((PosX - Width), (PosY - Height), PosX, PosY);
	Pen.~CPen();
	Brush.~CBrush();
	DeleteObject(&Pen);
	DeleteObject(&Brush);
}

/*
** SpiritualPanel�ػ�ͼƬ(����+5)
** void SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue)
** Para: CDC &MemDC(DC���)
** Para: UCHAR RValue(Rͨ����ɫ)
** Para: UCHAR GValue(Gͨ����ɫ)
** Para: UCHAR BValue(Bͨ����ɫ)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue)
{
	CPen Pen;
	CBrush Brush;

	m_ucRValue = RValue;//Rͨ����ɫ
	m_ucGValue = GValue;//Gͨ����ɫ
	m_ucBValue = BValue;//Bͨ����ɫ
	Pen.CreatePen(PS_SOLID, 1, RGB(m_ucRValue, m_ucGValue, m_ucBValue));
	Brush.CreateSolidBrush(RGB(m_ucRValue, m_ucGValue, m_ucBValue));
	MemDC.SelectObject(&Pen);
	MemDC.SelectObject(&Brush);
	MemDC.Rectangle(m_nPosX, m_nPosY, (m_nPosX + m_nWidth), (m_nPosY + m_nHeight));
	Pen.~CPen();
	Brush.~CBrush();
	DeleteObject(&Pen);
	DeleteObject(&Brush);
}

/*
** SpiritualPanel�ػ�ͼƬ(Alpha͸��)(����+6)
** void SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue)
** Para: CDC &MemDC(DC���)
** Para: UCHAR RValue(Rͨ����ɫ)
** Para: UCHAR GValue(Gͨ����ɫ)
** Para: UCHAR BValue(Bͨ����ɫ)
** Para: UCHAR AlphaValue(Alphaͨ����ɫ)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue, UCHAR AlphaValue)
{
	CPen Pen;
	CBrush Brush;
	BLENDFUNCTION Blendfunction;

	m_ucRValue = RValue;//Rͨ����ɫ
	m_ucGValue = GValue;//Gͨ����ɫ
	m_ucBValue = BValue;//Bͨ����ɫ
	m_ucAlphaValue = AlphaValue;//Alphaͨ����ɫ
	Pen.CreatePen(PS_SOLID, 1, RGB(m_ucRValue, m_ucGValue, m_ucBValue));
	Brush.CreateSolidBrush(RGB(m_ucRValue, m_ucGValue, m_ucBValue));
	MemDC.SelectObject(&Pen);
	MemDC.SelectObject(&Brush);
	Blendfunction.BlendOp = AC_SRC_OVER;
	Blendfunction.BlendFlags = 0;
	Blendfunction.AlphaFormat = 0;
	Blendfunction.SourceConstantAlpha = m_ucAlphaValue;
	MemDC.AlphaBlend(m_nPosX, m_nPosY, (m_nPosX + m_nWidth), (m_nPosY + m_nHeight), &MemDC, m_nPosX, m_nPosY, (m_nPosX + m_nWidth), (m_nPosY + m_nHeight), Blendfunction);
	Pen.~CPen();
	Brush.~CBrush();
	DeleteObject(&Pen);
	DeleteObject(&Brush);
}

/*
** SpiritualPanel�����¼�
** bool SpiritualPanelIsClick(CPoint MousePoint)
** Para: CPoint MousePoint(�������)
*/
bool SpiritualPanel::SpiritualPanelIsClick(CPoint MousePoint)
{
	if(m_nWidth > 0 && m_nHeight > 0)
	{
		if(MousePoint.x > m_nPosX && MousePoint.x < (m_nPosX + m_nWidth)
			&& MousePoint.y > m_nPosY && MousePoint.y < (m_nPosY + m_nHeight))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(m_nWidth < 0 && m_nHeight > 0)
	{
		if(MousePoint.x > (m_nPosX + m_nWidth) && MousePoint.x < m_nPosX
			&& MousePoint.y > m_nPosY && MousePoint.y < (m_nPosY + m_nHeight))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(m_nWidth > 0 && m_nHeight < 0)
	{
		if(MousePoint.x > m_nPosX && MousePoint.x < (m_nPosX + m_nWidth)
			&& MousePoint.y >(m_nPosY + m_nHeight) && MousePoint.y < m_nPosY)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(m_nWidth < 0 && m_nHeight < 0)
	{
		if(MousePoint.x >(m_nPosX + m_nWidth) && MousePoint.x < m_nPosX
			&& MousePoint.y >(m_nPosY + m_nHeight) && MousePoint.y < m_nPosY)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/*
** SpiritualPanel�ػ�(Alpha)
** bool SpiritualPanelReDrawAlpha(CDC* pDC, CDC &MemDC, int Alpha)
** Para: CDC* pDC(pDC���ھ��ָ��)
** Para: CDC &MemDC(DC���)
** int Alpha(Alphaͨ��͸����ֵ(0~255))
*/
void SpiritualPanel::SpiritualPanelReDrawAlpha(CDC* pDC, CDC &MemDC, int Alpha)
{
	BLENDFUNCTION Blendfunction;

	Blendfunction.BlendOp = AC_SRC_OVER;
	Blendfunction.BlendFlags = 0;
	Blendfunction.AlphaFormat = 0;
	Blendfunction.SourceConstantAlpha = Alpha;
	pDC->AlphaBlend(m_nPosX, m_nPosY, m_nWidth, m_nHeight, &MemDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight, Blendfunction);
}