
// SpiritualDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Spiritual.h"
#include "SpiritualDlg.h"
#include "afxdialogex.h"

#include "Common.h"
#include "Include.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
** ȫ�ֱ���
*/
//Title
SpiritualWindow g_NowWindow;//Window���ⱳ��

//Panel
SpiritualPanel g_PanelBottom = SpiritualPanel(0, 432, 640, 80);//PanelSchedule���ŵװ�(Undefine)
SpiritualPanel g_PanelScheduleUp = SpiritualPanel(80, 450, 0, 3);//PanelScheduleUp���Ž���
SpiritualPanel g_PanelScheduleDown = SpiritualPanel(80, 450, 464, 3);//PanelScheduleDown���Ž���

SpiritualPanel g_PanelVolumeBottom = SpiritualPanel(412, 335, 32, 132);//PanelVolumeBottom�����װ�
SpiritualPanel g_PanelVolumeUp = SpiritualPanel(426, 460, 3, -100);//PanelVolumeUp��������
SpiritualPanel g_PanelVolumeDown = SpiritualPanel(426, 460, 3, -100);//PanelVolumeDown��������

SpiritualPanel g_PanelTitleImageBottom = SpiritualPanel(222, 322, 172, 140);//TitleImage���ñ����װ�
SpiritualPanel g_PanelTitleImage[4] =
{
	SpiritualPanel(225, 325, 80, 64),//Image1
	SpiritualPanel(311, 325, 80, 64),//Image2
	SpiritualPanel(225, 395, 80, 64),//Image3
	SpiritualPanel(311, 395, 80, 64),//Image4
};//TitleImage���ñ���ͼƬ

//Button
SpiritualButton g_ButtonLast = SpiritualButton(30, 468, 32, 32);//ButtonLast(��һ��)
SpiritualButton g_ButtonPlayStatusCheck = SpiritualButton(80, 468, 32, 32);//ButtonPlayStatus(����״̬)
SpiritualButton g_ButtonNext = SpiritualButton(130, 468, 32, 32);//ButtonNext(��һ��)
SpiritualButton g_ButtonConfig = SpiritualButton(262, 468, 32, 32);//ButtonConfig(���ñ���)
SpiritualButton g_ButtonList = SpiritualButton(312, 468, 32, 32);//ButtonList(�����б�)
SpiritualButton g_ButtonHome = SpiritualButton(362, 468, 32, 32);//ButtonHome(���˵�)
SpiritualButton g_ButtonPlayVolumeCheck = SpiritualButton(412, 468, 32, 32);//ButtonPlayVolume(��������)
SpiritualButton g_ButtonPlayModeCheck = SpiritualButton(462, 468, 32, 32);//ButtonPlayMode(����ģʽ)
SpiritualButton g_ButtonLove = SpiritualButton(512, 468, 32, 32);//ButtonLove(ϲ������)
SpiritualButton g_ButtonAdd = SpiritualButton(562, 468, 32, 32);//ButtonAdd(�������)

SpiritualButton g_ButtonPlayStatus[PlayStatus_Max] = { SpiritualButton(80, 468, 32, 32),SpiritualButton(80, 468, 32, 32) };//ButtonPlayStatus(����״̬(����/��ͣ))
SpiritualButton g_ButtonPlayVolume[PlayVolume_Max] = { SpiritualButton(412, 468, 32, 32),SpiritualButton(412, 468, 32, 32) };//ButtonPlayVolume(��������(Max/Min))
SpiritualButton g_ButtonPlayMode[PlayMode_Max] = { SpiritualButton(462, 468, 32, 32) ,SpiritualButton(462, 468, 32, 32) ,SpiritualButton(462, 468, 32, 32) ,SpiritualButton(462, 468, 32, 32) };//ButtonPlayMode(����ģʽ(4))

SpiritualButton g_ButtonScheduleBar = SpiritualButton(72, 444, 16, 16);//ButtonScheduleBar(���ֽ�������ť)
SpiritualButton g_ButtonVolumeBar = SpiritualButton(428, 360, 16, 16);//ButtonVolumeBar(������������ť)

SpiritualButton g_ButtonMusicListPageLast = SpiritualButton(80, 382, 32, 32);//ButtonMusicListPageLast(�����б���һҳ)
SpiritualButton g_ButtonMusicListPageNext = SpiritualButton(512, 382, 32, 32);//g_ButtonMusicListPageNext(�����б���һҳ)

//Text
SpiritualText g_TextMusicName = SpiritualText(255, 68, 131, 25, 200, "���� Light");//MusicName��������
SpiritualText g_TextMusicAuthor = SpiritualText(283, 101, 74, 23, 160, "���� Light");//MusicAuthor��������

SpiritualText g_TextPlayNowTime = SpiritualText(30, 445, 38, 14, 100, "���� Light");//PlayNowTime���ŵ�ǰ����ʱ��
SpiritualText g_TextPlayEndTime = SpiritualText(559, 445, 38, 14, 100, "���� Light");//PlayEndTime���Ž�������ʱ��

SpiritualText g_TextVolumeValue = SpiritualText(412, 337, 38, 14, 100, "���� Light");//VolumeValue��ǰ������С(0~100)

SpiritualText g_TextMusicListPage = SpiritualText(112, 379, 400, 35, 160, "���� Light");//MusicListҳ��
SpiritualText g_TextMusicListLine[7] =
{
	SpiritualText(80, 134, 464, 35, 160, "���� Light"),//Line1
	SpiritualText(80, 169, 464, 35, 160, "���� Light"),//Line2
	SpiritualText(80, 204, 464, 35, 160, "���� Light"),//Line3
	SpiritualText(80, 239, 464, 35, 160, "���� Light"),//Line4
	SpiritualText(80, 274, 464, 35, 160, "���� Light"),//Line5
	SpiritualText(80, 309, 464, 35, 160, "���� Light"),//Line6
	SpiritualText(80, 344, 464, 35, 160, "���� Light"),//Line7
};//MusicList��������

//MCI
SpiritualMCI SpiritualMCINow;//MCI�����豸

//Music
int g_nMusicNumber = 0;//���ֱ��
CStringArray g_MusicList;//�����б�
CStringArray g_MusicNameList;//���������б�
int g_nMusicName_StepCount = 0;//���������Ʋ�����
int g_nMusicName_StepFlag = 0;//���������Ʋ�����

//MusicList
int g_nMusicListNowPage = 0;//����ҳ��(��ǰ)
int g_nMusicListAllPage = 0;//����ҳ��(����)
CString g_MusicListPageNumber = "0/0";

//Volume
CString g_VolumeValue = "100";

//Time
CString g_sPlayNowTime = "00:00";
CString g_sPlayEndTime = "00:00";
DWORD g_nPlayNowTime = 0;//��ǰ����ʱ�䳤��
DWORD g_nPlayEndTime = 0;//������ʱ�䳤��
int g_nPlayNowTime_Min = 0;
int g_nPlayNowTime_Sec = 0;
int g_nPlayEndTime_Min = 0;
int g_nPlayEndTime_Sec = 0;

//Flag��־
bool g_bPlayStatus = false;//����״̬(0:Stop,1:Play)
bool g_bPlayVolume = true;//��������(0:Max,1:Min)
SpiritualButtonPlayMode g_ePlayMode = PlayMode_Single;//����ģʽ

bool g_bVolumeControlFlag = false;//����������־
bool g_bButtonVolumeBarClickFlag = false;//����������ť���±�־
int g_PanelVolumeUpNowPosY = 360;//��ǰ�������ڸ߶�

bool g_bButtonScheduleBarClickFlag = false;//���ֽ��Ȱ�ť���±�־
int g_PanelScheduleUpNowPosX = 80;//��ǰ���Ž��ȿ��

bool g_bMusicListClickFlag = false;//�����б��±�־(MusicListҳ��)
bool g_bConfigClickFlag = false;//����Title������־
bool g_bConfigClickFlagLast = false;//����Title������־(ǰ��)
bool g_bConfigClickConvertFinish = true;//ת����־
bool g_bConfigConvertDirect = false;//ת������
int g_nConfigAlphaValue = 0;//����Title����Alphaͨ��ֵ

int g_nTitleImageNumber = 0;//��ǰ(TitleImageͼƬ���)
int g_nTitleImageNumberLast = 0;//�ϴ�(TitleImageͼƬ���)<RePaint����>
int g_nTitleImageLast = 0;
int g_nTitleAlphaValue = 0;//�±���Alphaͨ��ֵ
bool g_bTitleImageChange = false;//�����任��־
bool g_bTitleImageConvertFinish = true;//����ת�����

//Mouse���
bool g_bMouseTrack = true;
bool g_bMouseClick = false;//��굥��
bool g_bMouseDoubleClick = false;//���˫��
CPoint g_MousePoint;//�������

// CSpiritualDlg �Ի���

#pragma region CSpiritualDlg(���캯��)
CSpiritualDlg::CSpiritualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPIRITUAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TITLE);
	m_hbrush = CreateSolidBrush(RGB(255, 255, 255));
}
#pragma endregion

#pragma region DoDataExchange(���ݽ�������)
void CSpiritualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
#pragma endregion

BEGIN_MESSAGE_MAP(CSpiritualDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CSpiritualDlg ��Ϣ�������

#pragma region OnCreate(���ڴ�������)
/*
**���ڴ�������(Create Window)
*/
int CSpiritualDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ModifyStyleEx(0, WS_EX_LAYERED);
	m_Close = false;
	m_Closing = false;
	m_WindowStatus = true;
	m_WindowAlphaValue = 0;
	SetTimer(0, USER_TIMER0_INTERVAL, NULL);

	return 0;
}
#pragma endregion

#pragma region OnInitDialog(���ڳ�ʼ��)
/*
** ���ڳ�ʼ��
*/
BOOL CSpiritualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);			// ����Сͼ��

	//Window DropShadow

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	RECT Rect;//������������

	SetRect(&Rect, 0, 0, USER_SCREENWIDTH, USER_SCREENHEIGHT);
	AdjustWindowRect(&Rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
	SetWindowPos(NULL, 0, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_NOMOVE);
	ModifyStyle(WS_THICKFRAME, DS_MODALFRAME);

	InitializeWindow();//���ڳ�ʼ��
	RePaintWindow();//�ػ洰��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
#pragma endregion

#pragma region PreCreateWindow(Window���ڴ���֮ǰ)
/*
**Window���ڴ���֮ǰ
*/
BOOL CSpiritualDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreCreateWindow(cs);
}
#pragma endregion

#pragma region OnPaint(�����ػ�)
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

/*
** �����ػ�
*/
void CSpiritualDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		RePaintWindow();//�ػ洰��
		CDialogEx::OnPaint();
	}
}
#pragma endregion

#pragma region OnQueryDragIcon(��С������)
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpiritualDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
#pragma endregion

#pragma region OnOK(��ֹEnter���˳�����)
/*
**��ֹEnter���˳�����
*/
void CSpiritualDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}
#pragma endregion

#pragma region WinHelp(��ֹF1����ȡ����)
/*
**��ֹF1����ȡ����
*/
void CSpiritualDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::WinHelp(dwData, nCmd);
}
#pragma endregion

#pragma region OnCtlColor(���ڰ�ɫ��ˢ)
/*
**���ڰ�ɫ��ˢ
*/
HBRUSH CSpiritualDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch(nCtlColor)
	{
	case CTLCOLOR_DLG:
		hbr = m_hbrush;
		break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
#pragma endregion

#pragma region OnEraseBkgnd(���ڲ�������)
/*
**���ڲ�������
*/
BOOL CSpiritualDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//RePaintWindow();

	return TRUE;//��ֹ����(TurnBack)
	//return CDialogEx::OnEraseBkgnd(pDC);
}
#pragma endregion

#pragma region OnClose(���ڹر�)
/*
**���ڹر�
*/
void CSpiritualDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!m_Close)
	{
		if(!m_Closing)//���ڹرղ���������
		{
			ModifyStyleEx(0, WS_EX_LAYERED);
			m_Close = false;
			m_Closing = true;
			m_WindowStatus = false;
			m_WindowAlphaValue = 255;
			SetTimer(0, USER_TIMER0_INTERVAL, NULL);
		}
	}
	else
	{
		SpiritualConfigWrite();//д�������ļ�
		CDialogEx::OnClose();
	}
}
#pragma endregion

#pragma region OnDestroy(��������)
/*
**��������
*/
void CSpiritualDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	
	SpiritualMCINow.SpiritualMCIStop();//ֹͣ����
	CleanUpWindow();//�ͷ��ڴ�
}
#pragma endregion

#pragma region OnTimer(��ʱ������)
/*
** ��ʱ������
*/
void CSpiritualDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int MusicNumberNow = g_MusicList.GetCount();//��ǰ�б�����������
	int MusicNameWidth = 0;//��������������

	switch(nIDEvent)
	{
	case 0:
		if(m_WindowStatus == true)
		{
			m_WindowAlphaValue++;
			if(m_WindowAlphaValue > 255)
			{
				m_WindowAlphaValue = 255;
				KillTimer(0);
			}
			SetLayeredWindowAttributes(0, m_WindowAlphaValue, LWA_ALPHA);
		}
		else
		{
			m_WindowAlphaValue--;
			if(m_WindowAlphaValue < 0)
			{
				m_WindowAlphaValue = 0;
				KillTimer(0);
				m_Close = true;
				SendMessage(WM_CLOSE);
			}
			SetLayeredWindowAttributes(0, m_WindowAlphaValue, LWA_ALPHA);
		}
		break;
	case 1:
		RePaintWindow();
		break;
	case 2:
		g_nPlayNowTime = SpiritualMCINow.SpiritualMCIGetInformation(MCI_STATUS_POSITION);
		g_nPlayEndTime = SpiritualMCINow.SpiritualMCIGetInformation(MCI_STATUS_LENGTH);

		g_nPlayNowTime /= 1000;//ת������
		g_nPlayEndTime /= 1000;//ת������

		g_nPlayNowTime_Min = g_nPlayNowTime / 60;//Min
		g_nPlayNowTime_Sec = g_nPlayNowTime % 60;//Sec
		g_nPlayEndTime_Min = g_nPlayEndTime / 60;//Min
		g_nPlayEndTime_Sec = g_nPlayEndTime % 60;//Sec

		g_sPlayNowTime.Format("%02d:%02d", g_nPlayNowTime_Min, g_nPlayNowTime_Sec);
		g_sPlayEndTime.Format("%02d:%02d", g_nPlayEndTime_Min, g_nPlayEndTime_Sec);

		if(!g_bButtonScheduleBarClickFlag)//ScheduleBar���½�ֹ�������ֽ���
		{
			g_PanelScheduleUpNowPosX = 80 + (int)((g_nPlayNowTime * 1.0 / g_nPlayEndTime) * 464);//���ò��Ž���

			if(g_PanelScheduleUpNowPosX < 80)//���Ʒ�Χ
			{
				g_PanelScheduleUpNowPosX = 80;
			}
			else if(g_PanelScheduleUpNowPosX > 544)
			{
				g_PanelScheduleUpNowPosX = 544;
			}
			else
			{
				g_PanelScheduleUpNowPosX = g_PanelScheduleUpNowPosX;
			}
		}

		if(MusicNumberNow > 0)
		{
			if(g_nPlayNowTime >= g_nPlayEndTime)
			{
				RePaintWindow();//�ػ�(������ʾ)

				switch(g_ePlayMode)
				{
				case PlayMode_Single://����ѭ��
					SpiritualMCINow.SpiritualMCISeekTo(0);//���²���
					SpiritualPlayMusic();//��������
					break;
				case PlayMode_Circle://�б�ѭ��
					SpiritualMCINow.SpiritualMCISeekTo(0);//���²���
					g_nMusicNumber++;
					if(g_nMusicNumber > g_MusicList.GetCount() - 1)
					{
						g_nMusicNumber = 0;
					}
					SpiritualPlayMusic();//��������
					break;
				case PlayMode_Order://˳�򲥷�
					SpiritualMCINow.SpiritualMCISeekTo(0);//���²���
					g_nMusicNumber++;
					if(g_nMusicNumber > g_MusicList.GetCount() - 1)
					{
						g_nMusicNumber = g_MusicList.GetCount() - 1;
						SpiritualPlayMusic();//��������
					}
					break;
				case PlayMode_Random://�������
					srand((unsigned int)time(NULL));//�������������
					g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

					if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
					{
						g_nMusicNumber = 0;
					}
					else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
					{
						g_nMusicNumber = g_MusicList.GetCount() - 1;
					}

					SpiritualPlayMusic();//��������
					break;
				case PlayMode_Max:
					break;
				default:
					break;
				}
			}
		}
		break;
	case 3:
		MusicNameWidth = g_TextMusicName.SpiritualTextGetWidth();
		if(MusicNameWidth > 320)
		{
			if(g_nMusicName_StepFlag == 0)
			{
				g_nMusicName_StepCount++;
				if((MusicNameWidth - 320) <= 30)//������������30����(�������)
				{
					if(g_nMusicName_StepCount >= (MusicNameWidth - 320))
					{
						g_nMusicName_StepCount = MusicNameWidth - 320;
						g_nMusicName_StepFlag = 1;
					}
				}
				else//������������30����(���30)
				{
					if(g_nMusicName_StepCount >= 30)
					{
						g_nMusicName_StepCount = 30;
						g_nMusicName_StepFlag = 1;
					}
				}
			}
			else if(g_nMusicName_StepFlag == 1)
			{
				g_nMusicName_StepCount--;
				if((MusicNameWidth - 320) <= 30)//������������30����(�������)
				{
					if(g_nMusicName_StepCount <= -(MusicNameWidth - 320))
					{
						g_nMusicName_StepCount = -(MusicNameWidth - 320);
						g_nMusicName_StepFlag = 0;
					}
				}
				else//������������30����(���30)
				{
					if(g_nMusicName_StepCount <= -30)
					{
						g_nMusicName_StepCount = -30;
						g_nMusicName_StepFlag = 0;
					}
				}
			}
		}
		break;
	case 4:
		g_nTitleAlphaValue += 5;
		if(g_nTitleAlphaValue > 255)
		{
			g_nTitleAlphaValue = 255;
			g_bTitleImageConvertFinish = true;
			KillTimer(4);
		}
		break;
	case 5:
		if(g_bConfigConvertDirect == false)
		{
			g_nConfigAlphaValue += 5;
			if(g_nConfigAlphaValue > 255)
			{
				g_nConfigAlphaValue = 255;
				g_bConfigClickConvertFinish = true;
				KillTimer(5);
			}
		}
		else
		{
			g_nConfigAlphaValue -= 5;
			if(g_nConfigAlphaValue < 0)
			{
				g_nConfigAlphaValue = 0;
				g_bConfigClickConvertFinish = true;
				KillTimer(5);
			}
		}
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
#pragma endregion

#pragma region OnMouseMove(����ƶ�)
/*
** ����ƶ�
*/
void CSpiritualDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_MousePoint.x = point.x;
	g_MousePoint.y = point.y;

	if(g_bMouseTrack)
	{
		TRACKMOUSEEVENT csTME;
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE;
		csTME.hwndTrack = m_hWnd;
		::_TrackMouseEvent(&csTME);

		g_bMouseTrack = false;
	}

	if(g_bButtonScheduleBarClickFlag)
	{
		g_PanelScheduleUpNowPosX = g_MousePoint.x;//��굱ǰ����

		if(g_PanelScheduleUpNowPosX < 80)//���Ʒ�Χ
		{
			g_PanelScheduleUpNowPosX = 80;
		}
		else if(g_PanelScheduleUpNowPosX > 544)
		{
			g_PanelScheduleUpNowPosX = 544;
		}
		else
		{
			g_PanelScheduleUpNowPosX = g_PanelScheduleUpNowPosX;
		}
	}

	if(g_bButtonVolumeBarClickFlag)
	{
		g_PanelVolumeUpNowPosY = g_MousePoint.y;//���Y����ֵ

		if(g_PanelVolumeUpNowPosY < 360)//���Ʒ�Χ(360~460)
		{
			g_PanelVolumeUpNowPosY = 360;
		}
		else if(g_PanelVolumeUpNowPosY > 460)
		{
			g_PanelVolumeUpNowPosY = 460;
		}
		else
		{
			g_PanelVolumeUpNowPosY = g_PanelVolumeUpNowPosY;
		}

		if(g_PanelVolumeUpNowPosY == 460)
		{
			g_bPlayVolume = false;//������С
		}
		else
		{
			g_bPlayVolume = true;//�������
		}

		g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));

	}

	CDialogEx::OnMouseMove(nFlags, point);
}
#pragma endregion

#pragma region OnMouseLeave(����뿪)
/*
** ����뿪
*/
void CSpiritualDlg::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_MousePoint.x = 0;
	g_MousePoint.y = 0;

	g_bMouseTrack = true;

	CDialogEx::OnMouseLeave();
}
#pragma endregion

#pragma region OnLButtonUp(�������뿪)
/*
** �������뿪
*/
void CSpiritualDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//g_bMouseClick = false;

	if(g_bButtonScheduleBarClickFlag)
	{
		DWORD ScheduleNow = 0;

		g_bButtonScheduleBarClickFlag = false;//ScheduleBar�ͷ�
		ScheduleNow = (DWORD)(((g_PanelScheduleUpNowPosX - 80) * 1.0 / 464) * SpiritualMCINow.SpiritualMCIGetInformation(MCI_STATUS_LENGTH));
		SpiritualMCINow.SpiritualMCISeekTo(ScheduleNow);
		g_bPlayStatus = true;//����
		SpiritualMCINow.SpiritualMCIPlay();//��ʼ����
		SetTimer(2, USER_TIMER2_INTERVAL, NULL);//���ü�ʱ��
		SetTimer(3, USER_TIMER3_INTERVAL, NULL);//���ü�ʱ��
	}

	if(g_bButtonVolumeBarClickFlag)
	{
		DWORD VolumeNow = 0;

		g_bButtonVolumeBarClickFlag = false;//VolumeBar�ͷ�

		g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
		VolumeNow = (DWORD)((1.0 - ((g_PanelVolumeUpNowPosY - 360) * 1.0 / 100)) * (USER_VOLUME_MAX - USER_VOLUME_MIN));
		SpiritualMCINow.SpiritualMCISetVolume(VolumeNow);//��������
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
#pragma endregion

#pragma region OnLButtonDown(����������)
/*
** ����������
*/
void CSpiritualDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//g_bMouseClick = true;

	if(g_bMouseClick == false)
	{
		g_bMouseClick = true;
	}
	else
	{
		g_bMouseClick = false;
	}

	/*
	**��ⰴť����
	*/

	//ButtonLast����
	if(g_ButtonLast.SpiritualButtonIsClick(g_MousePoint))//��һ������
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//������������0
		{
			if(g_ePlayMode == PlayMode_Random)//�������
			{
				srand((unsigned int)time(NULL));//�������������
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//��������
			}
			else//����ģʽ
			{
				g_nMusicNumber--;

				if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;//ѭ��
				}

				SpiritualPlayMusic();//��������
			}
		}

	}

	//ButtonPlayStatus����
	if(g_ButtonPlayStatusCheck.SpiritualButtonIsClick(g_MousePoint))//����/��ͣ
	{
		if(g_bPlayStatus == false)
		{ 
			g_bPlayStatus = true;//����
			SpiritualMCINow.SpiritualMCIResume();//���²���
			SetTimer(2, USER_TIMER2_INTERVAL, NULL);//���ü�ʱ��
			SetTimer(3, USER_TIMER3_INTERVAL, NULL);//���ü�ʱ��
		}
		else
		{
			g_bPlayStatus = false;//��ͣ
			SpiritualMCINow.SpiritualMCIPause();//��ͣ����
			KillTimer(2);//�رռ�ʱ��
			KillTimer(3);//�رռ�ʱ��
		}
	}

	//ButtonNext����
	if(g_ButtonNext.SpiritualButtonIsClick(g_MousePoint))
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//������������0
		{
			if(g_ePlayMode == PlayMode_Random)//�������
			{
				srand((unsigned int)time(NULL));//�������������
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//��������
			}
			else
			{
				g_nMusicNumber++;
				
				if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
				{
					g_nMusicNumber = 0;//ѭ��
				}

				SpiritualPlayMusic();//��������
			}
		}
	}

	//g_ButtonConfig����
	if(g_ButtonConfig.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bConfigClickFlag == false)
		{
			g_bConfigClickFlag = true;//Config������־
		}
		else
		{
			g_bConfigClickFlag = false;//Configδ����
		}
	}

	//g_ButtonList����
	if(g_ButtonList.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bMusicListClickFlag == false)
		{
			g_bMusicListClickFlag = true;//�����б�ť����
		}
		else
		{
			g_bMusicListClickFlag = false;//�����б�ť�ͷ�
		}
	}

	//g_ButtonHome����
	if(g_ButtonHome.SpiritualButtonIsClick(g_MousePoint))
	{
		g_bConfigClickFlag = false;//Configδ����
		g_bMusicListClickFlag = false;//�����б�ť�ͷ�
	}

	//g_ButtonPlayVolume����
	if(g_ButtonPlayVolumeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bVolumeControlFlag == false)
		{
			g_bVolumeControlFlag = true;//����������
		}
		else
		{
			g_bVolumeControlFlag = false;//���������ر�
		}
	}

	//g_ButtonPlayMode����
	if(g_ButtonPlayModeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_ePlayMode == PlayMode_Single)
		{
			g_ePlayMode = PlayMode_Circle;//�б�ѭ��
		}
		else if(g_ePlayMode == PlayMode_Circle)
		{
			g_ePlayMode = PlayMode_Order;//˳�򲥷�
		}
		else if(g_ePlayMode == PlayMode_Order)
		{
			g_ePlayMode = PlayMode_Random;//�������
		}
		else if(g_ePlayMode == PlayMode_Random)
		{
			g_ePlayMode = PlayMode_Single;//����ѭ��
		}
	}

	//g_ButtonLove����
	if(g_ButtonLove.SpiritualButtonIsClick(g_MousePoint))
	{

	}

	//g_ButtonAdd����
	if(g_ButtonAdd.SpiritualButtonIsClick(g_MousePoint))
	{
		char FileFilter[] = "mp3�ļ�(*.mp3)|*.mp3|"
			"wav�ļ�(*.wav)|*.wav|"
			"wma�ļ�(*.wma)|*.wma|";

		CFileDialog *dlg = new CFileDialog(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, FileFilter);

		g_bPlayStatus = false;//��ͣ
		SpiritualMCINow.SpiritualMCIPause();//��ͣ����
		KillTimer(2);//�رռ�ʱ��
		KillTimer(3);//�رռ�ʱ��

		if(dlg->DoModal() == IDOK)
		{
			CString StrFilepath = dlg->GetPathName();
			CString StrFilename = dlg->GetFileName();
			CString StrFileTitle = dlg->GetFileTitle();

			if(SpiritualMCINow.SpiritualMCIOpen(StrFilepath))//MCI������
			{
				int Length = g_MusicList.GetCount();

				if(Length == 0)//�����б�Ϊ��
				{
					g_MusicList.Add(StrFilepath);//����·��
					g_MusicNameList.Add(StrFileTitle);//��������
				}
				else//�����б�������
				{
					int SameMusic = 0;
					for(int i = 0; i < Length; i++)
					{
						if(g_MusicList.GetAt(i) == StrFilepath)
						{
							SameMusic = 1;
							break;
						}
					}
					if(SameMusic == 0)
					{
						g_MusicList.Add(StrFilepath);//����·��
						g_MusicNameList.Add(StrFileTitle);//��������
					}
				}

				SpiritualMCINow.SpiritualMCIWrite(g_MusicList, g_nMusicNumber);//�����б�洢
				SpiritualMCINow.SpiritualMCIWrite(g_MusicNameList);//���������б�洢
																			   
				SpiritualPlayMusic();//��������
			}
		}

		delete dlg;
	}

	//ButtonScheduleBar����
	if(g_ButtonScheduleBar.SpiritualButtonIsClick(g_MousePoint))
	{
		g_bButtonScheduleBarClickFlag = true;//ScheduleBar����
	}
	
	//PanelScheduleDown����
	if(g_PanelScheduleDown.SpiritualPanelIsClick(g_MousePoint))
	{
		if(g_bButtonScheduleBarClickFlag == false)//ScheduleBarδ����
		{
			DWORD ScheduleNow = 0;

			g_PanelScheduleUpNowPosX = g_MousePoint.x;

			if(g_PanelScheduleUpNowPosX < 80)//���Ʒ�Χ
			{
				g_PanelScheduleUpNowPosX = 80;
			}
			else if(g_PanelScheduleUpNowPosX > 544)
			{
				g_PanelScheduleUpNowPosX = 544;
			}
			else
			{
				g_PanelScheduleUpNowPosX = g_PanelScheduleUpNowPosX;
			}

			ScheduleNow = (DWORD)(((g_PanelScheduleUpNowPosX - 80) * 1.0 / 464) * SpiritualMCINow.SpiritualMCIGetInformation(MCI_STATUS_LENGTH));
			SpiritualMCINow.SpiritualMCISeekTo(ScheduleNow);
			SpiritualMCINow.SpiritualMCIPlay();
		}
	}

	//MusicVolume�����������
	if(g_bVolumeControlFlag == true)//�������ڰ�ť����
	{
		//ButtonVolumeBar����
		if(g_ButtonVolumeBar.SpiritualButtonIsClick(g_MousePoint))
		{
			g_bButtonVolumeBarClickFlag = true;//ButtonVolumeBar����
		}

		//PanelVolumeDown����
		if(g_PanelVolumeDown.SpiritualPanelIsClick(g_MousePoint))
		{
			DWORD VolumeNow = 0;

			g_PanelVolumeUpNowPosY = g_MousePoint.y;//���Y����ֵ

			if(g_PanelVolumeUpNowPosY < 360)//���Ʒ�Χ(360~460)
			{
				g_PanelVolumeUpNowPosY = 360;
			}
			else if(g_PanelVolumeUpNowPosY > 460)
			{
				g_PanelVolumeUpNowPosY = 460;
			}
			else
			{
				g_PanelVolumeUpNowPosY = g_PanelVolumeUpNowPosY;
			}

			if(g_PanelVolumeUpNowPosY == 460)
			{
				g_bPlayVolume = false;//������С
			}
			else
			{
				g_bPlayVolume = true;//�������
			}

			g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
			VolumeNow = (DWORD)((1.0 - ((g_PanelVolumeUpNowPosY - 360) * 1.0 / 100)) * (USER_VOLUME_MAX - USER_VOLUME_MIN));
			SpiritualMCINow.SpiritualMCISetVolume(VolumeNow);
		}

		if(!g_ButtonPlayVolumeCheck.SpiritualButtonIsClick(g_MousePoint)
			&& !g_ButtonVolumeBar.SpiritualButtonIsClick(g_MousePoint)
			&& !g_PanelVolumeDown.SpiritualPanelIsClick(g_MousePoint))
		{
			g_bVolumeControlFlag = false;
		}
	}

	//MusicList�����б����
	if(g_bMusicListClickFlag == true)
	{
		//MusicListPageLast(�����б���һҳ)
		if(g_ButtonMusicListPageLast.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//�����б�ҳ������0
			{
				g_nMusicListNowPage--;
				if(g_nMusicListNowPage < 1)//��ǰ�б�ҳ��С��1
				{
					g_nMusicListNowPage = g_nMusicListAllPage;//��ǰ�б�ҳ�����
				}
			}
		}

		//MusicListPageNext(�����б���һҳ)
		if(g_ButtonMusicListPageNext.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//�����б�ҳ������0
			{
				g_nMusicListNowPage++;
				if(g_nMusicListNowPage > g_nMusicListAllPage)//��ǰ�б�ҳ��������ҳ��
				{
					g_nMusicListNowPage = 1;
				}
			}
		}
	}

	//SetTitle
	if(g_bConfigClickFlag == true)
	{
		if(g_PanelTitleImage[0].SpiritualPanelIsClick(g_MousePoint))//Title1����
		{
			g_nTitleImageNumber = 1;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[1].SpiritualPanelIsClick(g_MousePoint))//Title2����
		{
			g_nTitleImageNumber = 2;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[2].SpiritualPanelIsClick(g_MousePoint))//Title3����
		{
			g_nTitleImageNumber = 3;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[3].SpiritualPanelIsClick(g_MousePoint))//Title4����
		{
			g_nTitleImageNumber = 4;
			g_bConfigClickFlag = false;
		}

		if(!g_ButtonConfig.SpiritualButtonIsClick(g_MousePoint)
			&& !g_PanelTitleImage[0].SpiritualPanelIsClick(g_MousePoint)
			&& !g_PanelTitleImage[1].SpiritualPanelIsClick(g_MousePoint)
			&& !g_PanelTitleImage[2].SpiritualPanelIsClick(g_MousePoint)
			&& !g_PanelTitleImage[3].SpiritualPanelIsClick(g_MousePoint))
		{
			g_bConfigClickFlag = false;
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
#pragma endregion

#pragma region OnLButtonDblClk(������˫��)
/*
** ������˫��
*/
void CSpiritualDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//g_bMouseDoubleClick

	if(g_bMouseDoubleClick == false)
	{
		g_bMouseDoubleClick = true;
	}
	else
	{
		g_bMouseDoubleClick = false;
	}

	/*
	**��ⰴť����
	*/

	//ButtonLast����
	if(g_ButtonLast.SpiritualButtonIsClick(g_MousePoint))//��һ������
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//������������0
		{
			if(g_ePlayMode == PlayMode_Random)//�������
			{
				srand((unsigned int)time(NULL));//�������������
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//��������
			}
			else//����ģʽ
			{
				g_nMusicNumber--;

				if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;//ѭ��
				}

				SpiritualPlayMusic();//��������
			}
		}

	}

	//ButtonPlayStatus����
	if(g_ButtonPlayStatusCheck.SpiritualButtonIsClick(g_MousePoint))//����/��ͣ
	{
		if(g_bPlayStatus == false)
		{
			g_bPlayStatus = true;//����
			SpiritualMCINow.SpiritualMCIResume();//���²���
			SetTimer(2, USER_TIMER2_INTERVAL, NULL);//���ü�ʱ��
			SetTimer(3, USER_TIMER3_INTERVAL, NULL);//���ü�ʱ��
		}
		else
		{
			g_bPlayStatus = false;//��ͣ
			SpiritualMCINow.SpiritualMCIPause();//��ͣ����
			KillTimer(2);//�رռ�ʱ��
			KillTimer(3);//�رռ�ʱ��
		}
	}

	//ButtonNext����
	if(g_ButtonNext.SpiritualButtonIsClick(g_MousePoint))
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//������������0
		{
			if(g_ePlayMode == PlayMode_Random)//�������
			{
				srand((unsigned int)time(NULL));//�������������
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//��ǰ���ֱ��С��0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//��������
			}
			else
			{
				g_nMusicNumber++;

				if(g_nMusicNumber > g_MusicList.GetCount() - 1)//��ǰ���ֱ�Ŵ������
				{
					g_nMusicNumber = 0;//ѭ��
				}

				SpiritualPlayMusic();//��������
			}
		}
	}

	//g_ButtonConfig����
	if(g_ButtonConfig.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bConfigClickFlag == false)
		{
			g_bConfigClickFlag = true;//Config������־
		}
		else
		{
			g_bConfigClickFlag = false;//Configδ����
		}
	}

	//g_ButtonList����
	if(g_ButtonList.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bMusicListClickFlag == false)
		{
			g_bMusicListClickFlag = true;//�����б�ť����
		}
		else
		{
			g_bMusicListClickFlag = false;//�����б�ť�ͷ�
		}
	}

	//g_ButtonHome����
	if(g_ButtonHome.SpiritualButtonIsClick(g_MousePoint))
	{
		g_bConfigClickFlag = false;//Configδ����
		g_bMusicListClickFlag = false;//�����б�ť�ͷ�
	}

	//g_ButtonPlayVolume����
	if(g_ButtonPlayVolumeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bPlayVolume == false)
		{
			g_bPlayVolume = true;//�������
			g_PanelVolumeUpNowPosY = 360;
			g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
			SpiritualMCINow.SpiritualMCISetVolume(USER_VOLUME_MAX);//�������
		}
		else
		{
			g_bPlayVolume = false;//������С
			g_PanelVolumeUpNowPosY = 460;
			g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
			SpiritualMCINow.SpiritualMCISetVolume(USER_VOLUME_MIN);//������С
		}

		if(g_bVolumeControlFlag == false)
		{
			g_bVolumeControlFlag = true;//����������
		}
		else
		{
			g_bVolumeControlFlag = false;//���������ر�
		}
	}

	//g_ButtonPlayMode����
	if(g_ButtonPlayModeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_ePlayMode == PlayMode_Single)
		{
			g_ePlayMode = PlayMode_Circle;//�б�ѭ��
		}
		else if(g_ePlayMode == PlayMode_Circle)
		{
			g_ePlayMode = PlayMode_Order;//˳�򲥷�
		}
		else if(g_ePlayMode == PlayMode_Order)
		{
			g_ePlayMode = PlayMode_Random;//�������
		}
		else if(g_ePlayMode == PlayMode_Random)
		{
			g_ePlayMode = PlayMode_Single;//����ѭ��
		}
	}



	//MusicList�����б����
	if(g_bMusicListClickFlag == true)
	{
		//MusicListPageLast(�����б���һҳ)
		if(g_ButtonMusicListPageLast.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//�����б�ҳ������0
			{
				g_nMusicListNowPage--;
				if(g_nMusicListNowPage < 1)//��ǰ�б�ҳ��С��1
				{
					g_nMusicListNowPage = g_nMusicListAllPage;//��ǰ�б�ҳ�����
				}
			}
		}

		//MusicListPageNext(�����б���һҳ)
		if(g_ButtonMusicListPageNext.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//�����б�ҳ������0
			{
				g_nMusicListNowPage++;
				if(g_nMusicListNowPage > g_nMusicListAllPage)//��ǰ�б�ҳ��������ҳ��
				{
					g_nMusicListNowPage = 1;
				}
			}
		}

		//MusicListPanelClick(��������˫��)
		if(g_TextMusicListLine[0].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 0) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 0;
					SpiritualPlayMusic();//��������
				}
			}
		}
		else if(g_TextMusicListLine[1].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 1) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 1;
					SpiritualPlayMusic();//��������
				}
			}
		}
		else if(g_TextMusicListLine[2].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 2) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 2;
					SpiritualPlayMusic();//��������
				}
			}
		}
		else if(g_TextMusicListLine[3].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 3) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 3;
					SpiritualPlayMusic();//��������
				}
			}
		}
		else if(g_TextMusicListLine[4].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 4) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 4;
					SpiritualPlayMusic();//��������
				}
			}
		}
		else if(g_TextMusicListLine[5].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 5) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 5;
					SpiritualPlayMusic();//��������
				}
			}
		}
		else if(g_TextMusicListLine[6].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//���������б�
			{
				if(((g_nMusicListNowPage - 1) * 7 + 6) < g_MusicList.GetCount())//����·������
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 6;
					SpiritualPlayMusic();//��������
				}
			}
		}

	}

	//SetTitle
	if(g_bConfigClickFlag == true)
	{
		if(g_PanelTitleImage[0].SpiritualPanelIsClick(g_MousePoint))//Title1����
		{
			g_nTitleImageNumber = 1;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[1].SpiritualPanelIsClick(g_MousePoint))//Title2����
		{
			g_nTitleImageNumber = 2;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[2].SpiritualPanelIsClick(g_MousePoint))//Title3����
		{
			g_nTitleImageNumber = 3;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[3].SpiritualPanelIsClick(g_MousePoint))//Title4����
		{
			g_nTitleImageNumber = 4;
			g_bConfigClickFlag = false;
		}
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}
#pragma endregion

#pragma region SpiritualConfigWrite(�����ļ�д�뺯��)
/*
**Spiritual�����ļ�д�뺯��
*/
void CSpiritualDlg::SpiritualConfigWrite()
{
	CString WriteString;
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\Config\\SpiritualConfig.ini";

	WriteString.Format("%d", g_nTitleImageNumber);//Title����
	WritePrivateProfileString("Spiritual Config", "Title", WriteString, NowPath);
	WriteString.Format("%d", g_nMusicNumber);//Music���
	WritePrivateProfileString("Spiritual Config", "MusicNumber", WriteString, NowPath);
	WriteString.Format("%d", g_ePlayMode);//PlayMode����ģʽ
	WritePrivateProfileString("Spiritual Config", "PlayMode", WriteString, NowPath);
	WriteString.Format("%d", g_PanelVolumeUpNowPosY);//Volume������С
	WritePrivateProfileString("Spiritual Config", "VolumePosY", WriteString, NowPath);
}

#pragma endregion

#pragma region SpiritualConfigRead(�����ļ���ȡ����)
/*
**Spiritual�����ļ���ȡ����
*/
void CSpiritualDlg::SpiritualConfigRead()
{
	char ReadString[128] = { 0 };
	CString NowPath;
	int nPos;
	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\Config\\SpiritualConfig.ini";

	if(PathFileExists(NowPath))//�����ļ�����
	{
		//��ȡTitle����
		GetPrivateProfileString("Spiritual Config", "Title", "0", ReadString, 127, NowPath);
		g_nTitleImageNumberLast = g_nTitleImageNumber = atoi(ReadString);//Title����
		if(g_nTitleImageNumber < 0 || g_nTitleImageNumber > 4)//�������
		{
			g_nTitleImageNumberLast = g_nTitleImageNumber = 0;
		}

		//��ȡMusic���
		if(g_MusicList.GetCount() > 0)//���������б�
		{
			GetPrivateProfileString("Spiritual Config", "MusicNumber", "0", ReadString, 127, NowPath);
			g_nMusicNumber = atoi(ReadString);//Music���
			if(g_nMusicNumber < 0 || g_nMusicNumber >= g_MusicList.GetCount())//�������
			{
				g_nMusicNumber = g_MusicList.GetCount() - 1;
			}
		}

		//��ȡPlayMode����ģʽ
		GetPrivateProfileString("Spiritual Config", "PlayMode", "0", ReadString, 127, NowPath);
		switch(atoi(ReadString))//PlayMode����ģʽ
		{
		case 0:
			g_ePlayMode = PlayMode_Single;
			break;
		case 1:
			g_ePlayMode = PlayMode_Circle;
			break;
		case 2:
			g_ePlayMode = PlayMode_Order;
			break;
		case 3:
			g_ePlayMode = PlayMode_Random;
			break;
		default:
			g_ePlayMode = PlayMode_Single;
			break;
		}

		//��ȡVolume������С
		GetPrivateProfileString("Spiritual Config", "VolumePosY", "0", ReadString, 127, NowPath);
		g_PanelVolumeUpNowPosY = atoi(ReadString);//Volume������С
		if(g_PanelVolumeUpNowPosY < 360 || g_PanelVolumeUpNowPosY > 460)//�������
		{
			g_PanelVolumeUpNowPosY = 360;
		}
		g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
	}

}

#pragma endregion

#pragma region SpiritualCaculateMusicList(���������б�ҳ������)
/*
**Spiritual���������б���
*/
void CSpiritualDlg::SpiritualCaculateMusicList()
{
	//���㵱ǰ�����б�ҳ��
	if(g_MusicList.GetCount() > 0)//�����б��������
	{
		if(g_MusicList.GetCount() % 7 == 0)//��������Ϊ7������(0,7,14,21,...)
		{
			if((g_nMusicNumber + 1) % 7 == 0)//����ҳ
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7;//��ǰҳ��
			}
			else//������ҳ
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7 + 1;//��ǰҳ��
			}
			g_nMusicListAllPage = g_MusicList.GetCount() / 7;//��ҳ��
		}
		else//����������7������
		{
			if((g_nMusicNumber + 1) % 7 == 0)//����ҳ
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7;//��ǰҳ��
			}
			else//������ҳ
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7 + 1;//��ǰҳ��
			}
			g_nMusicListAllPage = g_MusicList.GetCount() / 7 + 1;//��ҳ��
		}
	}
	else//�����б��в���������
	{
		g_nMusicListNowPage = 0;
		g_nMusicListAllPage = 0;
	}
}
#pragma endregion

#pragma region SpiritualPlayMusic(�������ֺ���)
/*
**Spiritual�������ֺ���
*/
void CSpiritualDlg::SpiritualPlayMusic()
{
	DWORD VolumeNow = 0;

	//MusicList
	SpiritualCaculateMusicList();//���������б�

	//MusicPlay
	SpiritualMCINow.SpiritualMCIPlay(g_MusicList.GetAt(g_nMusicNumber));//��������
	VolumeNow = (DWORD)((1.0 - ((g_PanelVolumeUpNowPosY - 360) * 1.0 / 100)) * (USER_VOLUME_MAX - USER_VOLUME_MIN));
	SpiritualMCINow.SpiritualMCISetVolume(VolumeNow);//��������
	g_bPlayStatus = true;//����
	KillTimer(2);//�رռ�ʱ��
	SetTimer(2, USER_TIMER2_INTERVAL, NULL);//���ü�ʱ��
	KillTimer(3);//�رռ�ʱ��
	SetTimer(3, USER_TIMER3_INTERVAL, NULL);//���ü�ʱ��
	g_nMusicName_StepCount = 0;
	g_nMusicName_StepFlag = 0;
}
#pragma endregion

#pragma region InitializeWindow(���ڳ�ʼ������)
/*
**���ڳ�ʼ������
*/
void CSpiritualDlg::InitializeWindow()
{
	CString NowPathUp;
	CString NowPathDown;
	CString NowNumber;
	SpiritualButton *pButtonTemp;

	/*
	** PanelͼƬ����
	*/
	NowPathDown = "Panel_Bottom.png";
	g_PanelBottom.SpiritualPanelLoadImage(NowPathDown);

	NowPathDown = "Panel_TitleSet.png";
	g_PanelTitleImageBottom.SpiritualPanelLoadImage(NowPathDown);

	for(int i = 0; i < 4; i++)
	{
		NowPathDown.Format("Title%d.png", i);
		g_PanelTitleImage[i].SpiritualPanelLoadTitle(NowPathDown);
	}

	/*
	** ButtonͼƬ����
	*/

	//ButtonLast
	NowPathUp = "Button_Last_Up.png";
	NowPathDown = "Button_Last_Down.png";
	g_ButtonLast.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonPlayStatus
	pButtonTemp = &g_ButtonPlayStatus[PlayStatus_Play];
	for(int i = PlayStatus_Play; i < PlayStatus_Max; i++)
	{
		NowNumber.Format("%d", i);
		NowPathUp = "Button_PlayStatus_Up" + NowNumber + ".png";
		NowPathDown = "Button_PlayStatus_Down" + NowNumber + ".png";
		(pButtonTemp++)->SpiritualButtonLoadImage(NowPathUp, NowPathDown);
	}

	//ButtonNext
	NowPathUp = "Button_Next_Up.png";
	NowPathDown = "Button_Next_Down.png";
	g_ButtonNext.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonConfig
	NowPathUp = "Button_Config_Up.png";
	NowPathDown = "Button_Config_Down.png";
	g_ButtonConfig.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonList
	NowPathUp = "Button_List_Up.png";
	NowPathDown = "Button_List_Down.png";
	g_ButtonList.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonHome
	NowPathUp = "Button_Home_Up.png";
	NowPathDown = "Button_Home_Down.png";
	g_ButtonHome.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonVolume
	pButtonTemp = &g_ButtonPlayVolume[PlayVolume_VolumeMax];
	for(int i = PlayVolume_VolumeMax; i < PlayVolume_Max; i++)
	{
		NowNumber.Format("%d", i);
		NowPathUp = "Button_PlayVolume_Up" + NowNumber + ".png";
		NowPathDown = "Button_PlayVolume_Down" + NowNumber + ".png";
		(pButtonTemp++)->SpiritualButtonLoadImage(NowPathUp, NowPathDown);
	}

	//ButtonRunMode
	pButtonTemp = &g_ButtonPlayMode[PlayMode_Single];
	for(int i = PlayMode_Single; i < PlayMode_Max; i++)
	{
		NowNumber.Format("%d", i);
		NowPathUp = "Button_PlayMode_Up" + NowNumber + ".png";
		NowPathDown = "Button_PlayMode_Down" + NowNumber + ".png";
		(pButtonTemp++)->SpiritualButtonLoadImage(NowPathUp, NowPathDown);
	}

	//ButtonLove
	NowPathUp = "Button_Love_Up.png";
	NowPathDown = "Button_Love_Down.png";
	g_ButtonLove.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonAdd
	NowPathUp = "Button_Add_Up.png";
	NowPathDown = "Button_Add_Down.png";
	g_ButtonAdd.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonScheduleBar
	NowPathUp = "Button_Bar_Up.png";
	NowPathDown = "Button_Bar_Down.png";
	g_ButtonScheduleBar.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonVolumeBar
	NowPathUp = "Button_Bar_Up.png";
	NowPathDown = "Button_Bar_Down.png";
	g_ButtonVolumeBar.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	//ButtonMusicListPageLast
	NowPathUp = "Button_Last_Up.png";
	NowPathDown = "Button_Last_Down.png";
	g_ButtonMusicListPageLast.SpiritualButtonLoadImage(NowPathUp, NowPathDown);
	
	//ButtonMusicListPageNext
	NowPathUp = "Button_Next_Up.png";
	NowPathDown = "Button_Next_Down.png";
	g_ButtonMusicListPageNext.SpiritualButtonLoadImage(NowPathUp, NowPathDown);

	/*
	** ��ȡ�����б�
	*/
	SpiritualMCINow.SpiritualMCIGetHWND(m_hWnd);
	SpiritualMCINow.SpiritualMCISetVolume(USER_VOLUME_MAX);//�����������
	SpiritualMCINow.SpiritualMCIRead(g_MusicList, g_nMusicNumber);//��ȡ����·���б�
	SpiritualMCINow.SpiritualMCIRead(g_MusicNameList);//��ȡ���������б�
	
	/*
	** ��ȡ�����ļ�
	*/
	SpiritualConfigRead();//��ȡ�����ļ�

	if(g_MusicList.GetCount() > 0)//�����б����
	{
		SpiritualPlayMusic();//��������
	}
	else
	{
		g_bPlayStatus = false;//��ͣ
		SpiritualMCINow.SpiritualMCIStop();//ֹͣ����
		KillTimer(2);//�رռ�ʱ��
		KillTimer(3);//�رռ�ʱ��
	}

	SetTimer(1, USER_TIMER1_INTERVAL, NULL);//���ö�ʱˢ��(10ms)
}
#pragma endregion

#pragma region RePaintWindow(�����ػ溯��)
/*
**�����ػ溯��
*/
void CSpiritualDlg::RePaintWindow()
{
	CDC *pDC;
	CDC MemDC;
	CDC NewDC;
	CString MusicListNumber;

	pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	NewDC.CreateCompatibleDC(pDC);

	//��־��¼
	if(g_nTitleImageNumber != g_nTitleImageNumberLast)
	{
		g_bTitleImageChange = true;
		g_bTitleImageConvertFinish = false;//ת��δ���
		g_nTitleAlphaValue = 0;
		g_nTitleImageLast = g_nTitleImageNumberLast;
		SetTimer(4, USER_TIMER4_INTERVAL, NULL);//��ʱ
	}

	//Title�����ػ�
	//g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��

	if(g_bTitleImageConvertFinish)//ת�����
	{
		if(g_nTitleImageNumber == 1)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��
		}
		else if(g_nTitleImageNumber == 2)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE1);//��ײ���ⱳ��
		}
		else if(g_nTitleImageNumber == 3)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE2);//��ײ���ⱳ��
		}
		else if(g_nTitleImageNumber == 4)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE4);//��ײ���ⱳ��
		}
		else
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��
		}

		//Panel����ػ�

		//Schedule���ֲ��Ž��ȵ���
		if(g_PanelScheduleUpNowPosX > 537)//�������Ž��Ȱ�ť�ڵ�����
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, 0, 3, RGB(176, 94, 94), RGB(176, 94, 94));//���ֲ��Ž���(�²�)
		}
		else
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, (450 - (g_PanelScheduleUpNowPosX - 87)), 3, RGB(176, 94, 94), RGB(176, 94, 94));//���ֲ��Ž���(�²�)
		}

		if(g_PanelScheduleUpNowPosX < 87)//�������Ž��Ȱ�ť�ڵ�����
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, 0, 3, RGB(240, 128, 128), RGB(240, 128, 128));//���ֲ��Ž���(�ϲ�)
		}
		else
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, (g_PanelScheduleUpNowPosX - 87), 3, RGB(240, 128, 128), RGB(240, 128, 128));//���ֲ��Ž���(�ϲ�)
		}

		g_ButtonScheduleBar.SpiritualButtonDrawImage(MemDC, (72 + g_PanelScheduleUpNowPosX - 80), 444, g_MousePoint);//Schedule

		//MusicList�����б�
		if(g_bMusicListClickFlag == true)
		{
			//Text
			g_MusicListPageNumber.Format("%d/%d", g_nMusicListNowPage, g_nMusicListAllPage);//MusicListPage
			g_TextMusicListPage.SpiritualTextDrawOutCenter(MemDC, g_MusicListPageNumber);//MusicListPage���

			for(int i = 0; i < 7; i++)
			{
				g_TextMusicListLine[i].SpiritualTextDrawBackGround(MemDC, RGB(249, 208, 208), RGB(249, 208, 208), g_MousePoint);//MusicList�������
			}

			if(g_nMusicListNowPage >= 1 && g_nMusicListNowPage <= g_nMusicListAllPage)//��ǰ��������
			{
				//MusicLine1
				if(((g_nMusicListNowPage - 1) * 7 + 0) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 1));

					if(((g_nMusicListNowPage - 1) * 7 + 0) == g_nMusicNumber)
					{
						g_TextMusicListLine[0].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 0));
					}
					else
					{
						g_TextMusicListLine[0].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 0));
					}
				}
				else
				{
					g_TextMusicListLine[0].SpiritualTextDrawOutCenter(MemDC, "");
				}

				//MusicLine2
				if(((g_nMusicListNowPage - 1) * 7 + 1) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 2));

					if(((g_nMusicListNowPage - 1) * 7 + 1) == g_nMusicNumber)
					{
						g_TextMusicListLine[1].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 1));
					}
					else
					{
						g_TextMusicListLine[1].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 1));
					}
				}
				else
				{
					g_TextMusicListLine[1].SpiritualTextDrawOutCenter(MemDC, "");
				}

				//MusicLine3
				if(((g_nMusicListNowPage - 1) * 7 + 2) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 3));

					if(((g_nMusicListNowPage - 1) * 7 + 2) == g_nMusicNumber)
					{
						g_TextMusicListLine[2].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 2));
					}
					else
					{
						g_TextMusicListLine[2].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 2));
					}
				}
				else
				{
					g_TextMusicListLine[2].SpiritualTextDrawOutCenter(MemDC, "");
				}

				//MusicLine4
				if(((g_nMusicListNowPage - 1) * 7 + 3) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 4));

					if(((g_nMusicListNowPage - 1) * 7 + 3) == g_nMusicNumber)
					{
						g_TextMusicListLine[3].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 3));
					}
					else
					{
						g_TextMusicListLine[3].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 3));
					}
				}
				else
				{
					g_TextMusicListLine[3].SpiritualTextDrawOutCenter(MemDC, "");
				}

				//MusicLine5
				if(((g_nMusicListNowPage - 1) * 7 + 4) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 5));

					if(((g_nMusicListNowPage - 1) * 7 + 4) == g_nMusicNumber)
					{
						g_TextMusicListLine[4].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 4));
					}
					else
					{
						g_TextMusicListLine[4].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 4));
					}
				}
				else
				{
					g_TextMusicListLine[4].SpiritualTextDrawOutCenter(MemDC, "");
				}

				//MusicLine6
				if(((g_nMusicListNowPage - 1) * 7 + 5) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 6));

					if(((g_nMusicListNowPage - 1) * 7 + 5) == g_nMusicNumber)
					{
						g_TextMusicListLine[5].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 5));
					}
					else
					{
						g_TextMusicListLine[5].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 5));
					}
				}
				else
				{
					g_TextMusicListLine[5].SpiritualTextDrawOutCenter(MemDC, "");
				}

				//MusicLine7
				if(((g_nMusicListNowPage - 1) * 7 + 6) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 7));

					if(((g_nMusicListNowPage - 1) * 7 + 6) == g_nMusicNumber)
					{
						g_TextMusicListLine[6].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 6));
					}
					else
					{
						g_TextMusicListLine[6].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 6));
					}
				}
				else
				{
					g_TextMusicListLine[6].SpiritualTextDrawOutCenter(MemDC, "");
				}

			}

			//Button
			g_ButtonMusicListPageLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageLast(�����б���һҳ)
			g_ButtonMusicListPageNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageNext(�����б���һҳ)
		}

		//Volume��������
		if(g_bVolumeControlFlag == true)//������������
		{
			g_PanelVolumeBottom.SpiritualPanelDrawImage(MemDC, RGB(249, 208, 208), RGB(249, 208, 208));

			if(g_PanelVolumeUpNowPosY > 453)
			{
				g_PanelVolumeUp.SpiritualPanelDrawImage(MemDC, 3, 0, RGB(240, 128, 128), RGB(240, 128, 128));
			}
			else
			{
				g_PanelVolumeUp.SpiritualPanelDrawImage(MemDC, 3, (g_PanelVolumeUpNowPosY - 453), RGB(240, 128, 128), RGB(240, 128, 128));
			}

			if(g_PanelVolumeUpNowPosY < 367)
			{
				g_PanelVolumeDown.SpiritualPanelDrawImage(MemDC, 426, 360, -3, 0, RGB(176, 94, 94), RGB(176, 94, 94));
			}
			else
			{
				g_PanelVolumeDown.SpiritualPanelDrawImage(MemDC, 426, 360, -3, (367 - g_PanelVolumeUpNowPosY), RGB(176, 94, 94), RGB(176, 94, 94));
			}

			g_TextVolumeValue.SpiritualTextDrawOutCenter(MemDC, g_VolumeValue, 412, 32);
			g_ButtonVolumeBar.SpiritualButtonDrawImage(MemDC, 420, (352 + g_PanelVolumeUpNowPosY - 360), g_MousePoint);//Volume
		}

		//SetTitle���ñ���
		if(g_bConfigClickFlag == true)
		{
			if(g_bConfigClickFlagLast == true)
			{
				if(g_bConfigClickConvertFinish == true)
				{
					g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC);

					for(int i = 0; i < 4; i++)
					{
						g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC);
					}
				}
				else
				{
					g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);

					for(int i = 0; i < 4; i++)
					{
						g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
					}
				}
			}
			else
			{
				g_bConfigClickConvertFinish = false;//ת��δ���
				g_bConfigConvertDirect = false;
				g_nConfigAlphaValue = 0;

				g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
				
				for(int i = 0; i < 4; i++)
				{
					g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
				}
				SetTimer(5, USER_TIMER5_INTERVAL, NULL);//��ʱ
			}
		}
		else
		{
			if(g_bConfigClickFlagLast == false)
			{
				if(g_bConfigClickConvertFinish == false)
				{
					g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);

					for(int i = 0; i < 4; i++)
					{
						g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
					}
				}
			}
			else
			{
				g_bConfigClickConvertFinish = false;//ת��δ���
				g_bConfigConvertDirect = true;
				g_nConfigAlphaValue = 255;

				g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);

				for(int i = 0; i < 4; i++)
				{
					g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
				}
				SetTimer(5, USER_TIMER5_INTERVAL, NULL);//��ʱ
			}
		}

		//Button�����ػ�
		g_ButtonLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLast(��һ��)
		g_ButtonNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonNext(��һ��)
		g_ButtonConfig.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonConfig(��������)
		g_ButtonList.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonList(�����б�)
		g_ButtonHome.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonHome(���˵�)
		g_ButtonLove.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLove(ϲ������)
		g_ButtonAdd.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonAdd(�������)

		if(g_bPlayStatus == false)//����״̬
		{
			g_ButtonPlayStatus[PlayStatus_Play].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayStatus[PlayStatus_Pause].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}

		if(g_bPlayVolume == false)//��������
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMin].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMax].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}

		if(g_ePlayMode == PlayMode_Single)//����ģʽ
		{
			g_ButtonPlayMode[PlayMode_Single].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else if(g_ePlayMode == PlayMode_Circle)
		{
			g_ButtonPlayMode[PlayMode_Circle].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else if(g_ePlayMode == PlayMode_Order)
		{
			g_ButtonPlayMode[PlayMode_Order].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else if(g_ePlayMode == PlayMode_Random)
		{
			g_ButtonPlayMode[PlayMode_Random].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}

		//Text�ı��ػ�
		if(g_MusicNameList.GetCount() > 0)//���������б�
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, g_MusicNameList.GetAt(g_nMusicNumber), g_nMusicName_StepCount, 320);//MusicName��������
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor��������
		}
		else
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, "MusicName", 0, 320);//MusicName��������
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor��������
		}
		g_TextPlayNowTime.SpiritualTextDrawOut(MemDC, g_sPlayNowTime);//PlayNowTime���ŵ�ǰ����ʱ��
		g_TextPlayEndTime.SpiritualTextDrawOut(MemDC, g_sPlayEndTime);//PlayEndTime���Ž�������ʱ��

		//�������
		/*CString Mouse;
		CFont Font;
		MemDC.SetBkMode(TRANSPARENT);
		MemDC.SetTextColor(RGB(0, 0, 0));
		Font.CreatePointFont(100, "���� Light");
		MemDC.SelectObject(&Font);
		Mouse.Format("X:%d,Y:%d", g_MousePoint.x, g_MousePoint.y);
		MemDC.TextOut(0, 0, Mouse);
		Mouse.Format("Mouse Click:%d", g_bMouseClick);
		MemDC.TextOut(0, 12, Mouse);
		Mouse.Format("Mouse DoubleClick:%d", g_bMouseDoubleClick);
		MemDC.TextOut(0, 24, Mouse);
		Mouse.Format("ScheduleBar Click:%d", g_bButtonScheduleBarClickFlag);
		MemDC.TextOut(0, 36, Mouse);
		Mouse.Format("StepFlag:%d", g_nMusicName_StepFlag);
		MemDC.TextOut(0, 48, Mouse);
		Mouse.Format("StepCount:%d", g_nMusicName_StepCount);
		MemDC.TextOut(0, 60, Mouse);
		Mouse.Format("MusicList:%d", g_bMusicListClickFlag);
		MemDC.TextOut(0, 72, Mouse);
		Mouse.Format("TitleNumber:%d", g_nTitleImageNumber);
		MemDC.TextOut(0, 84, Mouse);
		Mouse.Format("TitleNumberLast:%d", g_nTitleImageNumberLast);
		MemDC.TextOut(0, 96, Mouse);
		Mouse.Format("ChangeFlag:%d", g_bTitleImageChange);
		MemDC.TextOut(0, 108, Mouse);
		DeleteObject(&Font);*/

		//�����ػ�
		g_NowWindow.SpiritualWindowReDraw(pDC, MemDC);
	}
	else//ת��δ���
	{
		if(g_nTitleImageNumber == 1)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��
		}
		else if(g_nTitleImageNumber == 2)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE1);//��ײ���ⱳ��
		}
		else if(g_nTitleImageNumber == 3)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE2);//��ײ���ⱳ��
		}
		else if(g_nTitleImageNumber == 4)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE4);//��ײ���ⱳ��
		}
		else
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��
		}

		if(g_nTitleImageLast == 1)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��
		}
		else if(g_nTitleImageLast == 2)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE1);//��ײ���ⱳ��
		}
		else if(g_nTitleImageLast == 3)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE2);//��ײ���ⱳ��
		}
		else if(g_nTitleImageLast == 4)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE4);//��ײ���ⱳ��
		}
		else
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE);//��ײ���ⱳ��
		}

		//Panel����ػ�

		//Schedule���ֲ��Ž��ȵ���
		if(g_PanelScheduleUpNowPosX > 537)//�������Ž��Ȱ�ť�ڵ�����
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, 0, 3, RGB(176, 94, 94), RGB(176, 94, 94));//���ֲ��Ž���(�²�)
			g_PanelScheduleDown.SpiritualPanelDrawImage(NewDC, 544, 453, 0, 3, RGB(176, 94, 94), RGB(176, 94, 94));//���ֲ��Ž���(�²�)
		}
		else
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, (450 - (g_PanelScheduleUpNowPosX - 87)), 3, RGB(176, 94, 94), RGB(176, 94, 94));//���ֲ��Ž���(�²�)
			g_PanelScheduleDown.SpiritualPanelDrawImage(NewDC, 544, 453, (450 - (g_PanelScheduleUpNowPosX - 87)), 3, RGB(176, 94, 94), RGB(176, 94, 94));//���ֲ��Ž���(�²�)
		}

		if(g_PanelScheduleUpNowPosX < 87)//�������Ž��Ȱ�ť�ڵ�����
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, 0, 3, RGB(240, 128, 128), RGB(240, 128, 128));//���ֲ��Ž���(�ϲ�)
			g_PanelScheduleUp.SpiritualPanelDrawImage(NewDC, 0, 3, RGB(240, 128, 128), RGB(240, 128, 128));//���ֲ��Ž���(�ϲ�)
		}
		else
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, (g_PanelScheduleUpNowPosX - 87), 3, RGB(240, 128, 128), RGB(240, 128, 128));//���ֲ��Ž���(�ϲ�)
			g_PanelScheduleUp.SpiritualPanelDrawImage(NewDC, (g_PanelScheduleUpNowPosX - 87), 3, RGB(240, 128, 128), RGB(240, 128, 128));//���ֲ��Ž���(�ϲ�)
		}

		g_ButtonScheduleBar.SpiritualButtonDrawImage(MemDC, (72 + g_PanelScheduleUpNowPosX - 80), 444, g_MousePoint);//Schedule
		g_ButtonScheduleBar.SpiritualButtonDrawImage(NewDC, (72 + g_PanelScheduleUpNowPosX - 80), 444, g_MousePoint);//Schedule

		//MusicList�����б�
		if(g_bMusicListClickFlag == true)
		{
			//Text
			g_MusicListPageNumber.Format("%d/%d", g_nMusicListNowPage, g_nMusicListAllPage);//MusicListPage
			g_TextMusicListPage.SpiritualTextDrawOutCenter(MemDC, g_MusicListPageNumber);//MusicListPage���
			g_TextMusicListPage.SpiritualTextDrawOutCenter(NewDC, g_MusicListPageNumber);//MusicListPage���

			for(int i = 0; i < 7; i++)
			{
				g_TextMusicListLine[i].SpiritualTextDrawBackGround(MemDC, RGB(249, 208, 208), RGB(249, 208, 208), g_MousePoint);//MusicList�������
				g_TextMusicListLine[i].SpiritualTextDrawBackGround(NewDC, RGB(249, 208, 208), RGB(249, 208, 208), g_MousePoint);//MusicList�������
			}

			if(g_nMusicListNowPage >= 1 && g_nMusicListNowPage <= g_nMusicListAllPage)//��ǰ��������
			{
				//MusicLine1
				if(((g_nMusicListNowPage - 1) * 7 + 0) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 1));

					if(((g_nMusicListNowPage - 1) * 7 + 0) == g_nMusicNumber)
					{
						g_TextMusicListLine[0].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 0));
						g_TextMusicListLine[0].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 0));
					}
					else
					{
						g_TextMusicListLine[0].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 0));
						g_TextMusicListLine[0].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 0));
					}
				}
				else
				{
					g_TextMusicListLine[0].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[0].SpiritualTextDrawOutCenter(NewDC, "");
				}

				//MusicLine2
				if(((g_nMusicListNowPage - 1) * 7 + 1) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 2));

					if(((g_nMusicListNowPage - 1) * 7 + 1) == g_nMusicNumber)
					{
						g_TextMusicListLine[1].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 1));
						g_TextMusicListLine[1].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 1));
					}
					else
					{
						g_TextMusicListLine[1].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 1));
						g_TextMusicListLine[1].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 1));
					}
				}
				else
				{
					g_TextMusicListLine[1].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[1].SpiritualTextDrawOutCenter(NewDC, "");
				}

				//MusicLine3
				if(((g_nMusicListNowPage - 1) * 7 + 2) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 3));

					if(((g_nMusicListNowPage - 1) * 7 + 2) == g_nMusicNumber)
					{
						g_TextMusicListLine[2].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 2));
						g_TextMusicListLine[2].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 2));
					}
					else
					{
						g_TextMusicListLine[2].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 2));
						g_TextMusicListLine[2].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 2));
					}
				}
				else
				{
					g_TextMusicListLine[2].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[2].SpiritualTextDrawOutCenter(NewDC, "");
				}

				//MusicLine4
				if(((g_nMusicListNowPage - 1) * 7 + 3) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 4));

					if(((g_nMusicListNowPage - 1) * 7 + 3) == g_nMusicNumber)
					{
						g_TextMusicListLine[3].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 3));
						g_TextMusicListLine[3].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 3));
					}
					else
					{
						g_TextMusicListLine[3].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 3));
						g_TextMusicListLine[3].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 3));
					}
				}
				else
				{
					g_TextMusicListLine[3].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[3].SpiritualTextDrawOutCenter(NewDC, "");
				}

				//MusicLine5
				if(((g_nMusicListNowPage - 1) * 7 + 4) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 5));

					if(((g_nMusicListNowPage - 1) * 7 + 4) == g_nMusicNumber)
					{
						g_TextMusicListLine[4].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 4));
						g_TextMusicListLine[4].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 4));
					}
					else
					{
						g_TextMusicListLine[4].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 4));
						g_TextMusicListLine[4].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 4));
					}
				}
				else
				{
					g_TextMusicListLine[4].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[4].SpiritualTextDrawOutCenter(NewDC, "");
				}

				//MusicLine6
				if(((g_nMusicListNowPage - 1) * 7 + 5) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 6));

					if(((g_nMusicListNowPage - 1) * 7 + 5) == g_nMusicNumber)
					{
						g_TextMusicListLine[5].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 5));
						g_TextMusicListLine[5].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 5));
					}
					else
					{
						g_TextMusicListLine[5].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 5));
						g_TextMusicListLine[5].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 5));
					}
				}
				else
				{
					g_TextMusicListLine[5].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[5].SpiritualTextDrawOutCenter(NewDC, "");
				}

				//MusicLine7
				if(((g_nMusicListNowPage - 1) * 7 + 6) < g_MusicList.GetCount())//���ִ���
				{
					MusicListNumber.Format("No. %d   ", ((g_nMusicListNowPage - 1) * 7 + 7));

					if(((g_nMusicListNowPage - 1) * 7 + 6) == g_nMusicNumber)
					{
						g_TextMusicListLine[6].SpiritualTextDrawOutCenter(MemDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 6));
						g_TextMusicListLine[6].SpiritualTextDrawOutCenter(NewDC, RGB(176, 94, 94), MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 6));
					}
					else
					{
						g_TextMusicListLine[6].SpiritualTextDrawOutCenter(MemDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 6));
						g_TextMusicListLine[6].SpiritualTextDrawOutCenter(NewDC, MusicListNumber + g_MusicNameList.GetAt((g_nMusicListNowPage - 1) * 7 + 6));
					}
				}
				else
				{
					g_TextMusicListLine[6].SpiritualTextDrawOutCenter(MemDC, "");
					g_TextMusicListLine[6].SpiritualTextDrawOutCenter(NewDC, "");
				}

			}

			//Button
			g_ButtonMusicListPageLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageLast(�����б���һҳ)
			g_ButtonMusicListPageNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageNext(�����б���һҳ)
			g_ButtonMusicListPageLast.SpiritualButtonDrawImage(NewDC, g_MousePoint);//MusicListPageLast(�����б���һҳ)
			g_ButtonMusicListPageNext.SpiritualButtonDrawImage(NewDC, g_MousePoint);//MusicListPageNext(�����б���һҳ)
		}

		//Volume��������
		if(g_bVolumeControlFlag == true)//������������
		{
			g_PanelVolumeBottom.SpiritualPanelDrawImage(MemDC, RGB(249, 208, 208), RGB(249, 208, 208));
			g_PanelVolumeBottom.SpiritualPanelDrawImage(NewDC, RGB(249, 208, 208), RGB(249, 208, 208));

			if(g_PanelVolumeUpNowPosY > 453)
			{
				g_PanelVolumeUp.SpiritualPanelDrawImage(MemDC, 3, 0, RGB(240, 128, 128), RGB(240, 128, 128));
				g_PanelVolumeUp.SpiritualPanelDrawImage(NewDC, 3, 0, RGB(240, 128, 128), RGB(240, 128, 128));
			}
			else
			{
				g_PanelVolumeUp.SpiritualPanelDrawImage(MemDC, 3, (g_PanelVolumeUpNowPosY - 453), RGB(240, 128, 128), RGB(240, 128, 128));
				g_PanelVolumeUp.SpiritualPanelDrawImage(NewDC, 3, (g_PanelVolumeUpNowPosY - 453), RGB(240, 128, 128), RGB(240, 128, 128));
			}

			if(g_PanelVolumeUpNowPosY < 367)
			{
				g_PanelVolumeDown.SpiritualPanelDrawImage(MemDC, 426, 360, -3, 0, RGB(176, 94, 94), RGB(176, 94, 94));
				g_PanelVolumeDown.SpiritualPanelDrawImage(NewDC, 426, 360, -3, 0, RGB(176, 94, 94), RGB(176, 94, 94));
			}
			else
			{
				g_PanelVolumeDown.SpiritualPanelDrawImage(MemDC, 426, 360, -3, (367 - g_PanelVolumeUpNowPosY), RGB(176, 94, 94), RGB(176, 94, 94));
				g_PanelVolumeDown.SpiritualPanelDrawImage(NewDC, 426, 360, -3, (367 - g_PanelVolumeUpNowPosY), RGB(176, 94, 94), RGB(176, 94, 94));
			}

			g_TextVolumeValue.SpiritualTextDrawOutCenter(MemDC, g_VolumeValue, 412, 32);
			g_ButtonVolumeBar.SpiritualButtonDrawImage(MemDC, 420, (352 + g_PanelVolumeUpNowPosY - 360), g_MousePoint);//Volume
			g_TextVolumeValue.SpiritualTextDrawOutCenter(NewDC, g_VolumeValue, 412, 32);
			g_ButtonVolumeBar.SpiritualButtonDrawImage(NewDC, 420, (352 + g_PanelVolumeUpNowPosY - 360), g_MousePoint);//Volume
		}

		//SetTitle���ñ���
		if(g_bConfigClickFlag == true)
		{
			g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC);
			g_PanelTitleImageBottom.SpiritualPanelDrawImage(NewDC);

			for(int i = 0; i < 4; i++)
			{
				g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC);
				g_PanelTitleImage[i].SpiritualPanelDrawImage(NewDC);
			}
		}

		//Button�����ػ�
		g_ButtonLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLast(��һ��)
		g_ButtonNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonNext(��һ��)
		g_ButtonConfig.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonConfig(��������)
		g_ButtonList.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonList(�����б�)
		g_ButtonHome.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonHome(���˵�)
		g_ButtonLove.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLove(ϲ������)
		g_ButtonAdd.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonAdd(�������)
		g_ButtonLast.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonLast(��һ��)
		g_ButtonNext.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonNext(��һ��)
		g_ButtonConfig.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonConfig(��������)
		g_ButtonList.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonList(�����б�)
		g_ButtonHome.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonHome(���˵�)
		g_ButtonLove.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonLove(ϲ������)
		g_ButtonAdd.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonAdd(�������)

		if(g_bPlayStatus == false)//����״̬
		{
			g_ButtonPlayStatus[PlayStatus_Play].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayStatus[PlayStatus_Play].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayStatus[PlayStatus_Pause].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayStatus[PlayStatus_Pause].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}

		if(g_bPlayVolume == false)//��������
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMin].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayVolume[PlayVolume_VolumeMin].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMax].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayVolume[PlayVolume_VolumeMax].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}

		if(g_ePlayMode == PlayMode_Single)//����ģʽ
		{
			g_ButtonPlayMode[PlayMode_Single].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayMode[PlayMode_Single].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else if(g_ePlayMode == PlayMode_Circle)
		{
			g_ButtonPlayMode[PlayMode_Circle].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayMode[PlayMode_Circle].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else if(g_ePlayMode == PlayMode_Order)
		{
			g_ButtonPlayMode[PlayMode_Order].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayMode[PlayMode_Order].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else if(g_ePlayMode == PlayMode_Random)
		{
			g_ButtonPlayMode[PlayMode_Random].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayMode[PlayMode_Random].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}

		//Text�ı��ػ�
		if(g_MusicNameList.GetCount() > 0)//���������б�
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, g_MusicNameList.GetAt(g_nMusicNumber), g_nMusicName_StepCount, 320);//MusicName��������
			g_TextMusicName.SpiritualTextDrawOutMove(NewDC, g_MusicNameList.GetAt(g_nMusicNumber), g_nMusicName_StepCount, 320);//MusicName��������
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor��������
		}
		else
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, "MusicName", 0, 320);//MusicName��������
			g_TextMusicName.SpiritualTextDrawOutMove(NewDC, "MusicName", 0, 320);//MusicName��������
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor��������
		}
		g_TextPlayNowTime.SpiritualTextDrawOut(MemDC, g_sPlayNowTime);//PlayNowTime���ŵ�ǰ����ʱ��
		g_TextPlayEndTime.SpiritualTextDrawOut(MemDC, g_sPlayEndTime);//PlayEndTime���Ž�������ʱ��
		g_TextPlayNowTime.SpiritualTextDrawOut(NewDC, g_sPlayNowTime);//PlayNowTime���ŵ�ǰ����ʱ��
		g_TextPlayEndTime.SpiritualTextDrawOut(NewDC, g_sPlayEndTime);//PlayEndTime���Ž�������ʱ��

		//�������
		/*CString Mouse;
		CFont Font;
		MemDC.SetBkMode(TRANSPARENT);
		MemDC.SetTextColor(RGB(0, 0, 0));
		Font.CreatePointFont(100, "���� Light");
		MemDC.SelectObject(&Font);
		Mouse.Format("X:%d,Y:%d", g_MousePoint.x, g_MousePoint.y);
		MemDC.TextOut(0, 0, Mouse);
		Mouse.Format("Mouse Click:%d", g_bMouseClick);
		MemDC.TextOut(0, 12, Mouse);
		Mouse.Format("Mouse DoubleClick:%d", g_bMouseDoubleClick);
		MemDC.TextOut(0, 24, Mouse);
		Mouse.Format("ScheduleBar Click:%d", g_bButtonScheduleBarClickFlag);
		MemDC.TextOut(0, 36, Mouse);
		Mouse.Format("StepFlag:%d", g_nMusicName_StepFlag);
		MemDC.TextOut(0, 48, Mouse);
		Mouse.Format("StepCount:%d", g_nMusicName_StepCount);
		MemDC.TextOut(0, 60, Mouse);
		Mouse.Format("MusicList:%d", g_bMusicListClickFlag);
		MemDC.TextOut(0, 72, Mouse);
		Mouse.Format("TitleNumber:%d", g_nTitleImageNumber);
		MemDC.TextOut(0, 84, Mouse);
		Mouse.Format("TitleNumberLast:%d", g_nTitleImageNumberLast);
		MemDC.TextOut(0, 96, Mouse);
		Mouse.Format("ChangeFlag:%d", g_bTitleImageChange);
		MemDC.TextOut(0, 108, Mouse);
		DeleteObject(&Font);*/

		//�����ػ�
		g_NowWindow.SpiritualWindowReDraw(pDC, MemDC, g_nTitleAlphaValue);
	}

	//��¼TitleImageNumberֵ
	g_nTitleImageNumberLast = g_nTitleImageNumber;
	g_bConfigClickFlagLast = g_bConfigClickFlag;

	DeleteDC(MemDC);
	DeleteDC(NewDC);
	ReleaseDC(pDC);
}
#pragma endregion

#pragma region CleanUpWindow(����������)
/*
**����������
*/
void CSpiritualDlg::CleanUpWindow()
{
	//�����ͷ��ڴ�

	//Window
	g_NowWindow.~SpiritualWindow();//��������

	//Panel
	g_PanelBottom.~SpiritualPanel();//��������
	g_PanelScheduleUp.~SpiritualPanel();//��������
	g_PanelScheduleDown.~SpiritualPanel();//��������
	g_PanelVolumeBottom.~SpiritualPanel();//��������
	g_PanelVolumeUp.~SpiritualPanel();//��������
	g_PanelVolumeDown.~SpiritualPanel();//��������
	g_PanelTitleImageBottom.~SpiritualPanel();//��������

	for(int i = 0; i < 4; i++)
	{
		g_PanelTitleImage[i].~SpiritualPanel();//��������
	}

	//Button
	g_ButtonLast.~SpiritualButton();//��������
	g_ButtonPlayStatusCheck.~SpiritualButton();//��������
	g_ButtonNext.~SpiritualButton();//��������
	g_ButtonConfig.~SpiritualButton();//��������
	g_ButtonList.~SpiritualButton();//��������
	g_ButtonHome.~SpiritualButton();//��������
	g_ButtonPlayVolumeCheck.~SpiritualButton();//��������
	g_ButtonPlayModeCheck.~SpiritualButton();//��������
	g_ButtonLove.~SpiritualButton();//��������
	g_ButtonAdd.~SpiritualButton();//��������
	g_ButtonScheduleBar.~SpiritualButton();//��������
	g_ButtonVolumeBar.~SpiritualButton();//��������
	g_ButtonMusicListPageLast.~SpiritualButton();//��������
	g_ButtonMusicListPageNext.~SpiritualButton();//��������

	for(int i = 0; i < PlayStatus_Max; i++)
	{
		g_ButtonPlayStatus[i].~SpiritualButton();//��������
	}
	for(int i = 0; i < PlayVolume_Max; i++)
	{
		g_ButtonPlayVolume[i].~SpiritualButton();//��������
	}
	for(int i = 0; i < PlayMode_Max; i++)
	{
		g_ButtonPlayMode[i].~SpiritualButton();//��������
	}

	//Text
	//g_TextMusicName.~SpiritualText();//��������
	//g_TextMusicAuthor.~SpiritualText();//��������
	//g_TextPlayNowTime.~SpiritualText();//��������
	//g_TextPlayEndTime.~SpiritualText();//��������

	//MCI
	//SpiritualMCINow.~SpiritualMCI();//��������

	//Music
	//g_MusicList.~CStringArray();//��������

	//Timer
	//g_sPlayNowTime.~CStringT();
	//g_sPlayEndTime.~CStringT();

}
#pragma endregion
