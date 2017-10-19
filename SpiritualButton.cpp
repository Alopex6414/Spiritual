#include "stdafx.h"
#include "Common.h"
#include "SpiritualButton.h"

/*
** SpiritualButton���캯��
** SpiritualButton()
*/
SpiritualButton::SpiritualButton()
{
	m_bIsVisiable = true;//�ؼ��ɼ�
	m_nPosX = 0;//�ؼ�X����
	m_nPosY = 0;//�ؼ�Y����
	m_nWidth = 0;//�ؼ����(����ͼƬ���)
	m_nHeight = 0;//�ؼ��߶�(����ͼƬ�߶�)
}

/*
** SpiritualButton��������
** ~SpiritualButton()
*/
SpiritualButton::~SpiritualButton()
{
	m_IButtonUp.Destroy();
	m_IButtonDown.Destroy();
}

/*
** SpiritualButton���캯��(����+1)
** SpiritualButton()
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
*/
SpiritualButton::SpiritualButton(int PosX, int PosY)
{
	m_bIsVisiable = true;//�ؼ��ɼ�
	m_nPosX = PosX;//�ؼ�X����
	m_nPosY = PosY;//�ؼ�Y����
	m_nWidth = 0;//�ؼ����(����ͼƬ���)
	m_nHeight = 0;//�ؼ��߶�(����ͼƬ�߶�)
}

/*
** SpiritualButton���캯��(����+2)
** SpiritualButton()
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
*/
SpiritualButton::SpiritualButton(int PosX, int PosY, int Width, int Height)
{
	m_bIsVisiable = true;//�ؼ��ɼ�
	m_nPosX = PosX;//�ؼ�X����
	m_nPosY = PosY;//�ؼ�Y����
	m_nWidth = Width;//�ؼ����(����ͼƬ���)
	m_nHeight = Height;//�ؼ��߶�(����ͼƬ�߶�)
}

/*
** SpiritualButton����ͼƬ
** void SpiritualButtonLoadImage(CString ButtonUpFileName, CString ButtonDownFileName)
** Para: CString ButtonUpFileName(UpͼƬ·��)
** Para: CString ButtonDownFileName(DownͼƬ·��)
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
	if(m_IButtonUp.GetBPP() == 32)//����Alphaͨ��
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
	m_IButtonDown.Load(NowPathDown);//����Alphaͨ��
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
** SpiritualButton�ػ�ͼƬ
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
** Para: CDC &MemDC(DC���)
** Para: SpiritualButtonStatus ButtonStatus(Button״̬)
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
** SpiritualButton�ػ�ͼƬ(����+1)
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
** Para: CDC &MemDC(DC���)
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: SpiritualButtonStatus ButtonStatus(Button״̬)
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
** SpiritualButton�ػ�ͼƬ(����+2)
** void SpiritualButtonDrawImage(CDC &MemDC, CPoint MousePoint)
** Para: CDC &MemDC(DC���)
** Para: CPoint MousePoint(�������)
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
** SpiritualButton�ػ�ͼƬ(����+2)
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, CPoint MousePoint)
** Para: CDC &MemDC(DC���)
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: CPoint MousePoint(�������)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, CPoint MousePoint)
{
	m_nPosX = PosX;//�ؼ�X����
	m_nPosY = PosY;//�ؼ�Y����

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
** SpiritualButton�ػ�ͼƬ(����+4)
** void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus)
** Para: CDC &MemDC(DC���)
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
** Para: CPoint MousePoint(�������)
*/
void SpiritualButton::SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, CPoint MousePoint)
{
	m_nPosX = PosX;//�ؼ�X����
	m_nPosY = PosY;//�ؼ�Y����
	m_nWidth = Width;//�ؼ����
	m_nHeight = Height;//�ؼ��߶�

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
** SpiritualButton�����¼�
** void SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint)
** Para: CPoint MousePoint(�������)
** return: bool(�Ƿ񵥻�)
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
** SpiritualButton�����¼�(����+1)
** void SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint)
** Para: int PosX(�ؼ�X����)
** Para: int PosY(�ؼ�Y����)
** Para: int Width(�ؼ����)
** Para: int Height(�ؼ��߶�)
** Para: CPoint MousePoint(�������)
** return: bool(�Ƿ񵥻�)
*/
bool SpiritualButton::SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint)
{
	m_nPosX = PosX;//�ؼ�X����
	m_nPosY = PosY;//�ؼ�Y����
	m_nWidth = Width;//�ؼ����
	m_nHeight = Height;//�ؼ��߶�

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
