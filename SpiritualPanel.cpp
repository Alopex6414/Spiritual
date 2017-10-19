#include "stdafx.h"
#include "Common.h"
#include "SpiritualPanel.h"

/*
** SpiritualPanel构造函数
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
** SpiritualPanel析构函数
** ~SpiritualPanel()
*/
SpiritualPanel::~SpiritualPanel()
{
	m_IPanelImage.Destroy();
}

/*
** SpiritualPanel构造函数(重载+1)
** SpiritualPanel()
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
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
** SpiritualPanel加载背景图片(Small)
** void SpiritualPanelLoadTitle(CString SpiritualPanelFileName)
** Para: CString SpiritualPanelFileName(图片路径)
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

	if(m_IPanelImage.GetBPP() == 32)//包含Alpha通道
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
** SpiritualPanel加载图片
** void SpiritualPanelLoadImage(CString SpiritualPanelFileName)
** Para: CString SpiritualPanelFileName(图片路径)
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

	if(m_IPanelImage.GetBPP() == 32)//包含Alpha通道
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
** SpiritualPanel重绘图片
** void SpiritualPanelDrawImage(CDC &MemDC)
** Para: CDC &MemDC(DC句柄)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC)
{
	m_IPanelImage.Draw(MemDC.m_hDC, m_nPosX, m_nPosY);
}

/*
** SpiritualPanel重绘图片(重载+1)
** void SpiritualPanelDrawImage(CDC &MemDC, int Alpha)
** Para: CDC &MemDC(DC句柄)
** Para: int Alpha(Alpha透明度)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, int Alpha)
{
	m_IPanelImage.AlphaBlend(MemDC.m_hDC, m_nPosX, m_nPosY, Alpha);
}

/*
** SpiritualPanel重绘图片(重载+2)
** void SpiritualPanelDrawImage(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor)
** Para: CDC &MemDC(DC句柄)
** Para: COLORREF PenColor(画笔颜色)
** Para: COLORREF BrushColor(画刷颜色)
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
** SpiritualPanel重绘图片(重载+3)
** void SpiritualPanelDrawImage(CDC &MemDC, int Width, int Height, COLORREF PenColor, COLORREF BrushColor)
** Para: CDC &MemDC(DC句柄)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
** Para: COLORREF PenColor(画笔颜色)
** Para: COLORREF BrushColor(画刷颜色)
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
** SpiritualPanel重绘图片(重载+4)
** void SpiritualPanelDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, COLORREF PenColor, COLORREF BrushColor)
** Para: CDC &MemDC(DC句柄)
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
** Para: COLORREF PenColor(画笔颜色)
** Para: COLORREF BrushColor(画刷颜色)
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
** SpiritualPanel重绘图片(重载+5)
** void SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue)
** Para: CDC &MemDC(DC句柄)
** Para: UCHAR RValue(R通道颜色)
** Para: UCHAR GValue(G通道颜色)
** Para: UCHAR BValue(B通道颜色)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue)
{
	CPen Pen;
	CBrush Brush;

	m_ucRValue = RValue;//R通道颜色
	m_ucGValue = GValue;//G通道颜色
	m_ucBValue = BValue;//B通道颜色
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
** SpiritualPanel重绘图片(Alpha透明)(重载+6)
** void SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue)
** Para: CDC &MemDC(DC句柄)
** Para: UCHAR RValue(R通道颜色)
** Para: UCHAR GValue(G通道颜色)
** Para: UCHAR BValue(B通道颜色)
** Para: UCHAR AlphaValue(Alpha通道颜色)
*/
void SpiritualPanel::SpiritualPanelDrawImage(CDC &MemDC, UCHAR RValue, UCHAR GValue, UCHAR BValue, UCHAR AlphaValue)
{
	CPen Pen;
	CBrush Brush;
	BLENDFUNCTION Blendfunction;

	m_ucRValue = RValue;//R通道颜色
	m_ucGValue = GValue;//G通道颜色
	m_ucBValue = BValue;//B通道颜色
	m_ucAlphaValue = AlphaValue;//Alpha通道颜色
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
** SpiritualPanel单击事件
** bool SpiritualPanelIsClick(CPoint MousePoint)
** Para: CPoint MousePoint(鼠标坐标)
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
** SpiritualPanel重绘(Alpha)
** bool SpiritualPanelReDrawAlpha(CDC* pDC, CDC &MemDC, int Alpha)
** Para: CDC* pDC(pDC窗口句柄指针)
** Para: CDC &MemDC(DC句柄)
** int Alpha(Alpha通道透明度值(0~255))
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