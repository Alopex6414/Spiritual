#include "stdafx.h"
#include "Common.h"
#include "SpiritualText.h"

/*
** SpiritualText���캯��
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
	m_sFontType = "���� Light";
}

/*
** SpiritualText��������
** ~SpiritualText()
*/
SpiritualText::~SpiritualText()
{
}

/*
** SpiritualText���캯��(����+1)
** SpiritualText()
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
** Para: int FontSize(�����С)
** Para:CString FontType(��������)
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
** SpiritualText��ȡ������
** int SpiritualTextGetWidth(void)
** Return: m_nWidth(������)
*/
int SpiritualText::SpiritualTextGetWidth(void)
{
	return m_nWidth;
}

/*
** SpiritualText����ַ�
** void SpiritualTextDrawOut(CDC &MemDC, CString Text)
** Para: CDC &MemDC(DC���)
** Para: CString Text(����ַ�)
*/
void SpiritualText::SpiritualTextDrawOut(CDC &MemDC, CString Text)
{
	CFont Font;
	MemDC.SetBkMode(TRANSPARENT);//͸������
	MemDC.SetTextColor(RGB(0, 0, 0));//��ɫ����
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);
	MemDC.TextOut(m_nPosX, m_nPosY, Text);
	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText��������ַ�(Center)
** void SpiritualTextDrawOutCenter(CDC &MemDC, CString Text)
** Para: CDC &MemDC(DC���)
** Para: CString Text(����ַ�)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, CString Text)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//͸������
	MemDC.SetTextColor(RGB(0, 0, 0));//��ɫ����
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);

	if(Size.cx <= m_nWidth && Size.cy <= m_nHeight)//�����Ⱥ͸߶Ⱦ�С��Panel
	{
		MemDC.TextOut((m_nPosX + (m_nWidth - Size.cx) / 2), (m_nPosY + (m_nHeight - Size.cy) / 2), Text);
	}
	else//�����Ⱥ͸߶�֮һ����Panel
	{
		MemDC.TextOut(m_nPosX, m_nPosY, Text);
	}

	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText��������ַ�(Center)(����+1)
** void SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, CString Text)
** Para: CDC &MemDC(DC���)
** Para: COLORREF PenColor(������ɫ/������ɫ)
** Para: CString Text(����ַ�)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, CString Text)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//͸������
	MemDC.SetTextColor(PenColor);//����
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);

	if(Size.cx <= m_nWidth && Size.cy <= m_nHeight)//�����Ⱥ͸߶Ⱦ�С��Panel
	{
		MemDC.TextOut((m_nPosX + (m_nWidth - Size.cx) / 2), (m_nPosY + (m_nHeight - Size.cy) / 2), Text);
	}
	else//�����Ⱥ͸߶�֮һ����Panel
	{
		MemDC.TextOut(m_nPosX, m_nPosY, Text);
	}

	Font.~CFont();
	DeleteObject(&Font);
}

/*
** SpiritualText��������ַ�(Center)(����+2)
** void SpiritualTextDrawOutCenter(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CString Text)
** Para: CDC &MemDC(DC���)
** Para: COLORREF PenColor(������ɫ/������ɫ)
** Para: COLORREF BrushColor(��ˢ��ɫ/������ɫ)
** Para: CString Text(����ַ�)
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
	MemDC.SetBkMode(TRANSPARENT);//͸������
	MemDC.SetTextColor(PenColor);//����
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);

	Size = MemDC.GetTextExtent(Text);

	if(Size.cx <= m_nWidth && Size.cy <= m_nHeight)//�����Ⱥ͸߶Ⱦ�С��Panel
	{
		MemDC.TextOut((m_nPosX + (m_nWidth - Size.cx) / 2), (m_nPosY + (m_nHeight - Size.cy) / 2), Text);
	}
	else//�����Ⱥ͸߶�֮һ����Panel
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
** SpiritualText��������ַ�(Center)(����+3)
** void SpiritualTextDrawOutCenter(CDC &MemDC, CString Text, int Width)
** Para: CDC &MemDC(DC���)
** Para: CString Text(����ַ�)
** Para: int Width(�ƶ����)
*/
void SpiritualText::SpiritualTextDrawOutCenter(CDC &MemDC, CString Text, int PosX, int Width)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//͸������
	MemDC.SetTextColor(RGB(0, 0, 0));//��ɫ����
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
** SpiritualText����ƶ��ַ�(Center)(����+1)
** void SpiritualTextDrawOutMove(CDC &MemDC, CString Text, int Width)
** Para: CDC &MemDC(DC���)
** Para: CString Text(����ַ�)
** Para: int Width(�ƶ����)
*/
void SpiritualText::SpiritualTextDrawOutMove(CDC &MemDC, CString Text, int PosX, int Width)
{
	CFont Font;
	CSize Size;

	MemDC.SetBkMode(TRANSPARENT);//͸������
	MemDC.SetTextColor(RGB(0, 0, 0));//��ɫ����
	Font.CreatePointFont(m_nFontSize, m_sFontType);
	MemDC.SelectObject(&Font);
	
	Size = MemDC.GetTextExtent(Text);
	m_nWidth = Size.cx;
	m_nHeight = Size.cy;

	if(Size.cx <= Width)//������С��Panel���
	{
		m_nPosX = USER_SCREENWIDTH / 2 - Size.cx / 2;//Center
	}
	else//�����ȴ���Panel���
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
** SpiritualText�������
** void SpiritualTextDrawBackGround(CDC &MemDC, COLORREF PenColor, COLORREF BrushColor, CPoint MousePoint)
** Para: CDC &MemDC(DC���)
** Para: COLORREF PenColor(������ɫ)
** Para: COLORREF BrushColor(��ˢ��ɫ)
** Para: CPoint MousePoint(�������)
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
** SpiritualText�����¼�
** void SpiritualTextIsClick(CPoint MousePoint)
** Para: CPoint MousePoint(�������)
** return: bool(�Ƿ񵥻�)
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