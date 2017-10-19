#include "stdafx.h"
#include "Common.h"
#include "SpiritualText.h"

/*
** SpiritualText构造函数
** SpiritualText()
*/
SpiritualText::SpiritualText()
{
	m_bIsVisialbe = true;
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nFontSize = 100;
	m_sFontType = "等线 Light";
}

/*
** SpiritualText析构函数
** ~SpiritualText()
*/
SpiritualText::~SpiritualText()
{
}

/*
** SpiritualText构造函数(重载+1)
** SpiritualText()
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
** Para: int FontSize(字体大小)
** Para:CString FontType(字体类型)
*/
SpiritualText::SpiritualText(int PosX, int PosY, int Width, int Height, int FontSize, CString FontType)
{
	m_bIsVisialbe = true;
	m_nPosX = PosX;
	m_nPosY = PosY;
	m_nWidth = Width;
	m_nHeight = Height;
	m_nFontSize = FontSize;
	m_sFontType = FontType;
}

/*
** SpiritualText获取字体宽度
** int SpiritualTextGetWidth(void)
** Return: m_nWidth(字体宽度)
*/
int SpiritualText::SpiritualTextGetWidth(void)
{
	return m_nWidth;
}

/*
** SpiritualText输出字符
** void SpiritualTextDrawOut(CDC &MemDC, CString Text)
** Para: CDC &MemDC(DC句柄)
** Para: CString Text(输出字符)
*/
void SpiritualText::SpiritualTextDrawOut(CDC &MemDC, CString Text)
{
	CFont Font;
	MemDC.SetBkMode(TRANSPARENT);//透明背景
	MemDC.SetTextColor(RGB(0, 0, 0));//黑色画笔
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);
	MemDC.TextOut(m_nPosX, m_nPosY, Text);
	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText输出中心字符(Center)
** void SpiritualTextDrawOutCenter(CDC &MemDC, CString Text)
** Para: CDC &MemDC(DC句柄)
** Para: CString Text(输出字符)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, CString Text)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//透明背景
	MemDC.SetTextColor(RGB(0, 0, 0));//黑色画笔
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);

	if(Size.cx <= m_nWidth && Size.cy <= m_nHeight)//字体宽度和高度均小于Panel
	{
		MemDC.TextOut((m_nPosX + (m_nWidth - Size.cx) / 2), (m_nPosY + (m_nHeight - Size.cy) / 2), Text);
	}
	else//字体宽度和高度之一超出Panel
	{
		MemDC.TextOut(m_nPosX, m_nPosY, Text);
	}

	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText输出中心字符(Center)(重载+1)
** void SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, CString Text)
** Para: CDC &MemDC(DC句柄)
** Para: COLORREF PenColor(画笔颜色/字体颜色)
** Para: CString Text(输出字符)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, CString Text)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//透明背景
	MemDC.SetTextColor(PenColor);//画笔
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);

	if(Size.cx <= m_nWidth && Size.cy <= m_nHeight)//字体宽度和高度均小于Panel
	{
		MemDC.TextOut((m_nPosX + (m_nWidth - Size.cx) / 2), (m_nPosY + (m_nHeight - Size.cy) / 2), Text);
	}
	else//字体宽度和高度之一超出Panel
	{
		MemDC.TextOut(m_nPosX, m_nPosY, Text);
	}

	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText输出中心字符(Center)(重载+2)
** void SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CString Text)
** Para: CDC &MemDC(DC句柄)
** Para: COLORREF PenColor(画笔颜色/字体颜色)
** Para: COLORREF BrushColor(画刷颜色/背景颜色)
** Para: CString Text(输出字符)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CString Text)
{
	CFont Font;
	CSize Size;
	CPen Pen;
	CBrush Brush;

	Pen.CreatePen(PS_SOLID, 1, BrushColor);
	Brush.CreateSolidBrush(BrushColor);
	MemDC.SelectObject(&Pen);
	MemDC.SelectObject(&Brush);
	MemDC.Rectangle(m_nPosX, m_nPosY, (m_nPosX + m_nWidth), (m_nPosY + m_nHeight));
	MemDC.SetBkMode(TRANSPARENT);//透明背景
	MemDC.SetTextColor(PenColor);//画笔
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);

	if(Size.cx <= m_nWidth && Size.cy <= m_nHeight)//字体宽度和高度均小于Panel
	{
		MemDC.TextOut((m_nPosX + (m_nWidth - Size.cx) / 2), (m_nPosY + (m_nHeight - Size.cy) / 2), Text);
	}
	else//字体宽度和高度之一超出Panel
	{
		MemDC.TextOut(m_nPosX, m_nPosY, Text);
	}

	Font.~CFont();
	Pen.~CPen();
	Brush.~CBrush();
	DeleteObject(&Font);
	DeleteObject(&Pen);
	DeleteObject(&Brush);
}

/*
** SpiritualText输出中心字符(Center)(重载+3)
** void SpiritualTextDrawOutCenter(CDC &MemDC, CString Text, int Width)
** Para: CDC &MemDC(DC句柄)
** Para: CString Text(输出字符)
** Para: int Width(移动宽度)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, CString Text, int PosX, int Width)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//透明背景
	MemDC.SetTextColor(RGB(0, 0, 0));//黑色画笔
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);
	m_nWidth = Size.cx;
	m_nHeight = Size.cy;

	if(Size.cx <= Width)
	{
		m_nPosX = PosX + (Width - Size.cx) / 2;
	}
	else
	{
		m_nPosX = PosX;
	}

	MemDC.TextOut(m_nPosX, m_nPosY, Text);

	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText输出移动字符(Center)(重载+1)
** void SpiritualTextDrawOutMove(CDC &MemDC, CString Text, int Width)
** Para: CDC &MemDC(DC句柄)
** Para: CString Text(输出字符)
** Para: int Width(移动宽度)
*/
void SpiritualText::SpiritualTextDrawOutMove(CDC &MemDC, CString Text, int PosX, int Width)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//透明背景
	MemDC.SetTextColor(RGB(0, 0, 0));//黑色画笔
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);
	
	Size = MemDC.GetTextExtent(Text);
	m_nWidth = Size.cx;
	m_nHeight = Size.cy;

	if(Size.cx <= Width)//字体宽度小于Panel宽度
	{
		m_nPosX = USER_SCREENWIDTH / 2 - Size.cx / 2;//Center
	}
	else//字体宽度大于Panel宽度
	{
		if(USER_SCREENWIDTH >= Size.cx)
		{
			m_nPosX = USER_SCREENWIDTH / 2 - Size.cx / 2 - PosX;
		}
		else
		{
			m_nPosX = 0 - PosX;
		}
	}
	
	MemDC.TextOut(m_nPosX, m_nPosY, Text);

	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText输出背景
** void SpiritualTextDrawBackGround(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CPoint MousePoint)
** Para: CDC &MemDC(DC句柄)
** Para: COLORREF PenColor(画笔颜色)
** Para: COLORREF BrushColor(画刷颜色)
** Para: CPoint MousePoint(鼠标坐标)
*/
void SpiritualText::SpiritualTextDrawBackGround(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CPoint MousePoint)
{
	if(MousePoint.x > m_nPosX && MousePoint.x < (m_nPosX + m_nWidth)
		&& MousePoint.y > m_nPosY && MousePoint.y < (m_nPosY + m_nHeight))
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
}

/*
** SpiritualText单击事件
** void SpiritualTextIsClick(CPoint MousePoint)
** Para: CPoint MousePoint(鼠标坐标)
** return: bool(是否单击)
*/
bool SpiritualText::SpiritualTextIsClick(CPoint MousePoint)
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