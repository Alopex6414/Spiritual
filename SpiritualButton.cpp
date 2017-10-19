#include "stdafx.h"
#include "Common.h"
#include "SpiritualButton.h"

/*
** SpiritualButton构造函数
** SpiritualButton()
*/
SpiritualButton::SpiritualButton()
{
	m_bIsVisiable = true;//控件可见
	m_nPosX = 0;//控件X坐标
	m_nPosY = 0;//控件Y坐标
	m_nWidth = 0;//控件宽度(加载图片宽度)
	m_nHeight = 0;//控件高度(加载图片高度)
}

/*
** SpiritualButton析构函数
** ~SpiritualButton()
*/
SpiritualButton::~SpiritualButton()
{
	m_IButtonUp.Destroy();
	m_IButtonDown.Destroy();
}

/*
** SpiritualButton构造函数(重载+1)
** SpiritualButton()
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
*/
SpiritualButton::SpiritualButton(int PosX, int PosY)
{
	m_bIsVisiable = true;//控件可见
	m_nPosX = PosX;//控件X坐标
	m_nPosY = PosY;//控件Y坐标
	m_nWidth = 0;//控件宽度(加载图片宽度)
	m_nHeight = 0;//控件高度(加载图片高度)
}

/*
** SpiritualButton构造函数(重载+2)
** SpiritualButton()
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
*/
SpiritualButton::SpiritualButton(int PosX, int PosY, int Width, int Height)
{
	m_bIsVisiable = true;//控件可见
	m_nPosX = PosX;//控件X坐标
	m_nPosY = PosY;//控件Y坐标
	m_nWidth = Width;//控件宽度(加载图片宽度)
	m_nHeight = Height;//控件高度(加载图片高度)
}

/*
** SpiritualButton加载图片
** void SpiritualButtonLoadImage(CString ButtonUpFileName, CString ButtonDownFileName)
** Para: CString ButtonUpFileName(Up图片路径)
** Para: CString ButtonDownFileName(Down图片路径)
*/
void SpiritualButton::SpiritualButtonLoadImage(CString ButtonUpFileName, CString ButtonDownFileName)
{
	CString NowPath;
	CString NowPathUp;
	CString NowPathDown;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\Resource\\Button\\";
	NowPathUp = NowPathDown = NowPath;

	NowPathUp += ButtonUpFileName;
	m_IButtonUp.Load(NowPathUp);
	if(m_IButtonUp.GetBPP() == 32)//包含Alpha通道
	{
		for(int i = 0; i < m_IButtonUp.GetWidth(); i++)
		{
			for(int j = 0; j < m_IButtonUp.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_IButtonUp.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	NowPathDown += ButtonDownFileName;
	m_IButtonDown.Load(NowPathDown);//包含Alpha通道
	if(m_IButtonDown.GetBPP() == 32)
	{
		for(int i = 0; i < m_IButtonDown.GetWidth(); i++)
		{
			for(int j = 0; j < m_IButtonDown.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_IButtonDown.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
}

/*
** SpiritualButton重绘图片
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
** Para: CDC &MemDC(DC句柄)
** Para: SpiritualButtonStatus ButtonStatus(Button状态)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, SpiritualButtonStatus ButtonStatus)
{
	switch(ButtonStatus)
	{
	case Status_Up:
		m_IButtonUp.Draw(MemDC.m_hDC, m_nPosX, m_nPosY);
		break;
	case Status_Down:
		m_IButtonDown.Draw(MemDC.m_hDC, m_nPosX, m_nPosY);
		break;
	default:
		break;
	}
}

/*
** SpiritualButton重绘图片(重载+1)
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
** Para: CDC &MemDC(DC句柄)
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: SpiritualButtonStatus ButtonStatus(Button状态)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
{
	m_nPosX = PosX;
	m_nPosY = PosY;

	switch(ButtonStatus)
	{
	case Status_Up:
		m_IButtonUp.Draw(MemDC.m_hDC, m_nPosX, m_nPosY);
		break;
	case Status_Down:
		m_IButtonDown.Draw(MemDC.m_hDC, m_nPosX, m_nPosY);
		break;
	default:
		break;
	}
}

/*
** SpiritualButton重绘图片(重载+2)
** void SpiritualButtonDrawImage(CDC &MemDC, CPoint MousePoint)
** Para: CDC &MemDC(DC句柄)
** Para: CPoint MousePoint(鼠标坐标)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, CPoint MousePoint)
{
	if(MousePoint.x > m_nPosX && MousePoint.x < (m_nPosX + m_nWidth)
		&& MousePoint.y > m_nPosY && MousePoint.y < (m_nPosY + m_nHeight))
	{
		SpiritualButtonDrawImage(MemDC, Status_Up);
	}
	else
	{
		SpiritualButtonDrawImage(MemDC, Status_Down);
	}
}

/*
** SpiritualButton重绘图片(重载+2)
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, CPoint MousePoint)
** Para: CDC &MemDC(DC句柄)
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: CPoint MousePoint(鼠标坐标)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, CPoint MousePoint)
{
	m_nPosX = PosX;//控件X坐标
	m_nPosY = PosY;//控件Y坐标

	if(MousePoint.x > m_nPosX && MousePoint.x < (m_nPosX + m_nWidth)
		&& MousePoint.y > m_nPosY && MousePoint.y < (m_nPosY + m_nHeight))
	{
		SpiritualButtonDrawImage(MemDC, Status_Up);
	}
	else
	{
		SpiritualButtonDrawImage(MemDC, Status_Down);
	}
}

/*
** SpiritualButton重绘图片(重载+4)
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
** Para: CDC &MemDC(DC句柄)
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
** Para: CPoint MousePoint(鼠标坐标)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, CPoint MousePoint)
{
	m_nPosX = PosX;//控件X坐标
	m_nPosY = PosY;//控件Y坐标
	m_nWidth = Width;//控件宽度
	m_nHeight = Height;//控件高度

	if(MousePoint.x > m_nPosX && MousePoint.x < (m_nPosX + m_nWidth)
		&& MousePoint.y > m_nPosY && MousePoint.y < (m_nPosY + m_nHeight))
	{
		SpiritualButtonDrawImage(MemDC, m_nPosX, m_nPosY, Status_Up);
	}
	else
	{
		SpiritualButtonDrawImage(MemDC, m_nPosX, m_nPosY, Status_Down);
	}
}

/*
** SpiritualButton单击事件
** void SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint)
** Para: CPoint MousePoint(鼠标坐标)
** return: bool(是否单击)
*/
bool SpiritualButton::SpiritualButtonIsClick(CPoint MousePoint)
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

/*
** SpiritualButton单击事件(重载+1)
** void SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint)
** Para: int PosX(控件X坐标)
** Para: int PosY(控件Y坐标)
** Para: int Width(控件宽度)
** Para: int Height(控件高度)
** Para: CPoint MousePoint(鼠标坐标)
** return: bool(是否单击)
*/
bool SpiritualButton::SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint)
{
	m_nPosX = PosX;//控件X坐标
	m_nPosY = PosY;//控件Y坐标
	m_nWidth = Width;//控件宽度
	m_nHeight = Height;//控件高度

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
