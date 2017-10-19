
// SpiritualDlg.cpp : 实现文件
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
** 全局变量
*/
//Title
SpiritualWindow g_NowWindow;//Window标题背景

//Panel
SpiritualPanel g_PanelBottom = SpiritualPanel(0, 432, 640, 80);//PanelSchedule播放底板(Undefine)
SpiritualPanel g_PanelScheduleUp = SpiritualPanel(80, 450, 0, 3);//PanelScheduleUp播放进度
SpiritualPanel g_PanelScheduleDown = SpiritualPanel(80, 450, 464, 3);//PanelScheduleDown播放进度

SpiritualPanel g_PanelVolumeBottom = SpiritualPanel(412, 335, 32, 132);//PanelVolumeBottom音量底板
SpiritualPanel g_PanelVolumeUp = SpiritualPanel(426, 460, 3, -100);//PanelVolumeUp播放音量
SpiritualPanel g_PanelVolumeDown = SpiritualPanel(426, 460, 3, -100);//PanelVolumeDown播放音量

SpiritualPanel g_PanelTitleImageBottom = SpiritualPanel(222, 322, 172, 140);//TitleImage设置背景底板
SpiritualPanel g_PanelTitleImage[4] =
{
	SpiritualPanel(225, 325, 80, 64),//Image1
	SpiritualPanel(311, 325, 80, 64),//Image2
	SpiritualPanel(225, 395, 80, 64),//Image3
	SpiritualPanel(311, 395, 80, 64),//Image4
};//TitleImage设置背景图片

//Button
SpiritualButton g_ButtonLast = SpiritualButton(30, 468, 32, 32);//ButtonLast(上一首)
SpiritualButton g_ButtonPlayStatusCheck = SpiritualButton(80, 468, 32, 32);//ButtonPlayStatus(播放状态)
SpiritualButton g_ButtonNext = SpiritualButton(130, 468, 32, 32);//ButtonNext(下一首)
SpiritualButton g_ButtonConfig = SpiritualButton(262, 468, 32, 32);//ButtonConfig(设置背景)
SpiritualButton g_ButtonList = SpiritualButton(312, 468, 32, 32);//ButtonList(播放列表)
SpiritualButton g_ButtonHome = SpiritualButton(362, 468, 32, 32);//ButtonHome(主菜单)
SpiritualButton g_ButtonPlayVolumeCheck = SpiritualButton(412, 468, 32, 32);//ButtonPlayVolume(播放音量)
SpiritualButton g_ButtonPlayModeCheck = SpiritualButton(462, 468, 32, 32);//ButtonPlayMode(播放模式)
SpiritualButton g_ButtonLove = SpiritualButton(512, 468, 32, 32);//ButtonLove(喜爱音乐)
SpiritualButton g_ButtonAdd = SpiritualButton(562, 468, 32, 32);//ButtonAdd(添加音乐)

SpiritualButton g_ButtonPlayStatus[PlayStatus_Max] = { SpiritualButton(80, 468, 32, 32),SpiritualButton(80, 468, 32, 32) };//ButtonPlayStatus(播放状态(播放/暂停))
SpiritualButton g_ButtonPlayVolume[PlayVolume_Max] = { SpiritualButton(412, 468, 32, 32),SpiritualButton(412, 468, 32, 32) };//ButtonPlayVolume(播放音量(Max/Min))
SpiritualButton g_ButtonPlayMode[PlayMode_Max] = { SpiritualButton(462, 468, 32, 32) ,SpiritualButton(462, 468, 32, 32) ,SpiritualButton(462, 468, 32, 32) ,SpiritualButton(462, 468, 32, 32) };//ButtonPlayMode(播放模式(4))

SpiritualButton g_ButtonScheduleBar = SpiritualButton(72, 444, 16, 16);//ButtonScheduleBar(音乐进度条按钮)
SpiritualButton g_ButtonVolumeBar = SpiritualButton(428, 360, 16, 16);//ButtonVolumeBar(音乐音量条按钮)

SpiritualButton g_ButtonMusicListPageLast = SpiritualButton(80, 382, 32, 32);//ButtonMusicListPageLast(音乐列表上一页)
SpiritualButton g_ButtonMusicListPageNext = SpiritualButton(512, 382, 32, 32);//g_ButtonMusicListPageNext(音乐列表下一页)

//Text
SpiritualText g_TextMusicName = SpiritualText(255, 68, 131, 25, 200, "等线 Light");//MusicName音乐名称
SpiritualText g_TextMusicAuthor = SpiritualText(283, 101, 74, 23, 160, "等线 Light");//MusicAuthor音乐作者

SpiritualText g_TextPlayNowTime = SpiritualText(30, 445, 38, 14, 100, "等线 Light");//PlayNowTime播放当前进度时间
SpiritualText g_TextPlayEndTime = SpiritualText(559, 445, 38, 14, 100, "等线 Light");//PlayEndTime播放结束进度时间

SpiritualText g_TextVolumeValue = SpiritualText(412, 337, 38, 14, 100, "等线 Light");//VolumeValue当前音量大小(0~100)

SpiritualText g_TextMusicListPage = SpiritualText(112, 379, 400, 35, 160, "等线 Light");//MusicList页数
SpiritualText g_TextMusicListLine[7] =
{
	SpiritualText(80, 134, 464, 35, 160, "等线 Light"),//Line1
	SpiritualText(80, 169, 464, 35, 160, "等线 Light"),//Line2
	SpiritualText(80, 204, 464, 35, 160, "等线 Light"),//Line3
	SpiritualText(80, 239, 464, 35, 160, "等线 Light"),//Line4
	SpiritualText(80, 274, 464, 35, 160, "等线 Light"),//Line5
	SpiritualText(80, 309, 464, 35, 160, "等线 Light"),//Line6
	SpiritualText(80, 344, 464, 35, 160, "等线 Light"),//Line7
};//MusicList音乐名称

//MCI
SpiritualMCI SpiritualMCINow;//MCI播放设备

//Music
int g_nMusicNumber = 0;//音乐标号
CStringArray g_MusicList;//音乐列表
CStringArray g_MusicNameList;//音乐名称列表
int g_nMusicName_StepCount = 0;//音乐名称移步数量
int g_nMusicName_StepFlag = 0;//音乐名称移步方向

//MusicList
int g_nMusicListNowPage = 0;//音乐页数(当前)
int g_nMusicListAllPage = 0;//音乐页数(总数)
CString g_MusicListPageNumber = "0/0";

//Volume
CString g_VolumeValue = "100";

//Time
CString g_sPlayNowTime = "00:00";
CString g_sPlayEndTime = "00:00";
DWORD g_nPlayNowTime = 0;//当前播放时间长度
DWORD g_nPlayEndTime = 0;//音乐总时间长度
int g_nPlayNowTime_Min = 0;
int g_nPlayNowTime_Sec = 0;
int g_nPlayEndTime_Min = 0;
int g_nPlayEndTime_Sec = 0;

//Flag标志
bool g_bPlayStatus = false;//播放状态(0:Stop,1:Play)
bool g_bPlayVolume = true;//播放音量(0:Max,1:Min)
SpiritualButtonPlayMode g_ePlayMode = PlayMode_Single;//播放模式

bool g_bVolumeControlFlag = false;//调节音量标志
bool g_bButtonVolumeBarClickFlag = false;//调节音量按钮按下标志
int g_PanelVolumeUpNowPosY = 360;//当前音量调节高度

bool g_bButtonScheduleBarClickFlag = false;//音乐进度按钮按下标志
int g_PanelScheduleUpNowPosX = 80;//当前播放进度宽度

bool g_bMusicListClickFlag = false;//音乐列表按下标志(MusicList页面)
bool g_bConfigClickFlag = false;//设置Title背景标志
bool g_bConfigClickFlagLast = false;//设置Title背景标志(前次)
bool g_bConfigClickConvertFinish = true;//转换标志
bool g_bConfigConvertDirect = false;//转换方向
int g_nConfigAlphaValue = 0;//设置Title背景Alpha通道值

int g_nTitleImageNumber = 0;//当前(TitleImage图片序号)
int g_nTitleImageNumberLast = 0;//上次(TitleImage图片序号)<RePaint周期>
int g_nTitleImageLast = 0;
int g_nTitleAlphaValue = 0;//新背景Alpha通道值
bool g_bTitleImageChange = false;//背景变换标志
bool g_bTitleImageConvertFinish = true;//背景转换完成

//Mouse鼠标
bool g_bMouseTrack = true;
bool g_bMouseClick = false;//鼠标单击
bool g_bMouseDoubleClick = false;//鼠标双击
CPoint g_MousePoint;//鼠标坐标

// CSpiritualDlg 对话框

#pragma region CSpiritualDlg(构造函数)
CSpiritualDlg::CSpiritualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPIRITUAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TITLE);
	m_hbrush = CreateSolidBrush(RGB(255, 255, 255));
}
#pragma endregion

#pragma region DoDataExchange(数据交换函数)
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


// CSpiritualDlg 消息处理程序

#pragma region OnCreate(窗口创建窗体)
/*
**窗口创建窗体(Create Window)
*/
int CSpiritualDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ModifyStyleEx(0, WS_EX_LAYERED);
	m_Close = false;
	m_Closing = false;
	m_WindowStatus = true;
	m_WindowAlphaValue = 0;
	SetTimer(0, USER_TIMER0_INTERVAL, NULL);

	return 0;
}
#pragma endregion

#pragma region OnInitDialog(窗口初始化)
/*
** 窗口初始化
*/
BOOL CSpiritualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);			// 设置小图标

	//Window DropShadow

	// TODO: 在此添加额外的初始化代码
	RECT Rect;//创建矩形区域

	SetRect(&Rect, 0, 0, USER_SCREENWIDTH, USER_SCREENHEIGHT);
	AdjustWindowRect(&Rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
	SetWindowPos(NULL, 0, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), SWP_NOMOVE);
	ModifyStyle(WS_THICKFRAME, DS_MODALFRAME);

	InitializeWindow();//窗口初始化
	RePaintWindow();//重绘窗口

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
#pragma endregion

#pragma region PreCreateWindow(Window窗口创建之前)
/*
**Window窗口创建之前
*/
BOOL CSpiritualDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreCreateWindow(cs);
}
#pragma endregion

#pragma region OnPaint(窗口重绘)
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

/*
** 窗口重绘
*/
void CSpiritualDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		RePaintWindow();//重绘窗口
		CDialogEx::OnPaint();
	}
}
#pragma endregion

#pragma region OnQueryDragIcon(最小化窗口)
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSpiritualDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
#pragma endregion

#pragma region OnOK(禁止Enter键退出窗口)
/*
**禁止Enter键退出窗口
*/
void CSpiritualDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
#pragma endregion

#pragma region WinHelp(禁止F1键获取帮助)
/*
**禁止F1键获取帮助
*/
void CSpiritualDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::WinHelp(dwData, nCmd);
}
#pragma endregion

#pragma region OnCtlColor(窗口白色画刷)
/*
**窗口白色画刷
*/
HBRUSH CSpiritualDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch(nCtlColor)
	{
	case CTLCOLOR_DLG:
		hbr = m_hbrush;
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
#pragma endregion

#pragma region OnEraseBkgnd(窗口擦除背景)
/*
**窗口擦除背景
*/
BOOL CSpiritualDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//RePaintWindow();

	return TRUE;//禁止擦除(TurnBack)
	//return CDialogEx::OnEraseBkgnd(pDC);
}
#pragma endregion

#pragma region OnClose(窗口关闭)
/*
**窗口关闭
*/
void CSpiritualDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!m_Close)
	{
		if(!m_Closing)//正在关闭不进入条件
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
		SpiritualConfigWrite();//写入配置文件
		CDialogEx::OnClose();
	}
}
#pragma endregion

#pragma region OnDestroy(窗口销毁)
/*
**窗口销毁
*/
void CSpiritualDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	
	SpiritualMCINow.SpiritualMCIStop();//停止播放
	CleanUpWindow();//释放内存
}
#pragma endregion

#pragma region OnTimer(定时器触发)
/*
** 定时器触发
*/
void CSpiritualDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int MusicNumberNow = g_MusicList.GetCount();//当前列表中音乐数量
	int MusicNameWidth = 0;//音乐名称字体宽度

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

		g_nPlayNowTime /= 1000;//转换成秒
		g_nPlayEndTime /= 1000;//转换成秒

		g_nPlayNowTime_Min = g_nPlayNowTime / 60;//Min
		g_nPlayNowTime_Sec = g_nPlayNowTime % 60;//Sec
		g_nPlayEndTime_Min = g_nPlayEndTime / 60;//Min
		g_nPlayEndTime_Sec = g_nPlayEndTime % 60;//Sec

		g_sPlayNowTime.Format("%02d:%02d", g_nPlayNowTime_Min, g_nPlayNowTime_Sec);
		g_sPlayEndTime.Format("%02d:%02d", g_nPlayEndTime_Min, g_nPlayEndTime_Sec);

		if(!g_bButtonScheduleBarClickFlag)//ScheduleBar按下禁止更新音乐进度
		{
			g_PanelScheduleUpNowPosX = 80 + (int)((g_nPlayNowTime * 1.0 / g_nPlayEndTime) * 464);//设置播放进度

			if(g_PanelScheduleUpNowPosX < 80)//限制范围
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
				RePaintWindow();//重绘(进度显示)

				switch(g_ePlayMode)
				{
				case PlayMode_Single://单曲循环
					SpiritualMCINow.SpiritualMCISeekTo(0);//重新播放
					SpiritualPlayMusic();//播放音乐
					break;
				case PlayMode_Circle://列表循环
					SpiritualMCINow.SpiritualMCISeekTo(0);//重新播放
					g_nMusicNumber++;
					if(g_nMusicNumber > g_MusicList.GetCount() - 1)
					{
						g_nMusicNumber = 0;
					}
					SpiritualPlayMusic();//播放音乐
					break;
				case PlayMode_Order://顺序播放
					SpiritualMCINow.SpiritualMCISeekTo(0);//重新播放
					g_nMusicNumber++;
					if(g_nMusicNumber > g_MusicList.GetCount() - 1)
					{
						g_nMusicNumber = g_MusicList.GetCount() - 1;
						SpiritualPlayMusic();//播放音乐
					}
					break;
				case PlayMode_Random://随机播放
					srand((unsigned int)time(NULL));//产生随机数种子
					g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

					if(g_nMusicNumber < 0)//当前音乐标号小于0
					{
						g_nMusicNumber = 0;
					}
					else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
					{
						g_nMusicNumber = g_MusicList.GetCount() - 1;
					}

					SpiritualPlayMusic();//播放音乐
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
				if((MusicNameWidth - 320) <= 30)//如果超出宽度在30以下(超出宽度)
				{
					if(g_nMusicName_StepCount >= (MusicNameWidth - 320))
					{
						g_nMusicName_StepCount = MusicNameWidth - 320;
						g_nMusicName_StepFlag = 1;
					}
				}
				else//如果超出宽度在30以上(宽度30)
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
				if((MusicNameWidth - 320) <= 30)//如果超出宽度在30以下(超出宽度)
				{
					if(g_nMusicName_StepCount <= -(MusicNameWidth - 320))
					{
						g_nMusicName_StepCount = -(MusicNameWidth - 320);
						g_nMusicName_StepFlag = 0;
					}
				}
				else//如果超出宽度在30以上(宽度30)
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

#pragma region OnMouseMove(鼠标移动)
/*
** 鼠标移动
*/
void CSpiritualDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		g_PanelScheduleUpNowPosX = g_MousePoint.x;//鼠标当前坐标

		if(g_PanelScheduleUpNowPosX < 80)//限制范围
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
		g_PanelVolumeUpNowPosY = g_MousePoint.y;//鼠标Y坐标值

		if(g_PanelVolumeUpNowPosY < 360)//限制范围(360~460)
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
			g_bPlayVolume = false;//音量最小
		}
		else
		{
			g_bPlayVolume = true;//音量最大
		}

		g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));

	}

	CDialogEx::OnMouseMove(nFlags, point);
}
#pragma endregion

#pragma region OnMouseLeave(鼠标离开)
/*
** 鼠标离开
*/
void CSpiritualDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_MousePoint.x = 0;
	g_MousePoint.y = 0;

	g_bMouseTrack = true;

	CDialogEx::OnMouseLeave();
}
#pragma endregion

#pragma region OnLButtonUp(鼠标左键离开)
/*
** 鼠标左键离开
*/
void CSpiritualDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//g_bMouseClick = false;

	if(g_bButtonScheduleBarClickFlag)
	{
		DWORD ScheduleNow = 0;

		g_bButtonScheduleBarClickFlag = false;//ScheduleBar释放
		ScheduleNow = (DWORD)(((g_PanelScheduleUpNowPosX - 80) * 1.0 / 464) * SpiritualMCINow.SpiritualMCIGetInformation(MCI_STATUS_LENGTH));
		SpiritualMCINow.SpiritualMCISeekTo(ScheduleNow);
		g_bPlayStatus = true;//播放
		SpiritualMCINow.SpiritualMCIPlay();//开始播放
		SetTimer(2, USER_TIMER2_INTERVAL, NULL);//设置计时器
		SetTimer(3, USER_TIMER3_INTERVAL, NULL);//设置计时器
	}

	if(g_bButtonVolumeBarClickFlag)
	{
		DWORD VolumeNow = 0;

		g_bButtonVolumeBarClickFlag = false;//VolumeBar释放

		g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
		VolumeNow = (DWORD)((1.0 - ((g_PanelVolumeUpNowPosY - 360) * 1.0 / 100)) * (USER_VOLUME_MAX - USER_VOLUME_MIN));
		SpiritualMCINow.SpiritualMCISetVolume(VolumeNow);//设置音量
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
#pragma endregion

#pragma region OnLButtonDown(鼠标左键按下)
/*
** 鼠标左键按下
*/
void CSpiritualDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	**检测按钮按下
	*/

	//ButtonLast按下
	if(g_ButtonLast.SpiritualButtonIsClick(g_MousePoint))//上一首音乐
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//音乐数量大于0
		{
			if(g_ePlayMode == PlayMode_Random)//随机播放
			{
				srand((unsigned int)time(NULL));//产生随机数种子
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//当前音乐标号小于0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//播放音乐
			}
			else//其余模式
			{
				g_nMusicNumber--;

				if(g_nMusicNumber < 0)//当前音乐标号小于0
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;//循环
				}

				SpiritualPlayMusic();//播放音乐
			}
		}

	}

	//ButtonPlayStatus按下
	if(g_ButtonPlayStatusCheck.SpiritualButtonIsClick(g_MousePoint))//播放/暂停
	{
		if(g_bPlayStatus == false)
		{ 
			g_bPlayStatus = true;//播放
			SpiritualMCINow.SpiritualMCIResume();//重新播放
			SetTimer(2, USER_TIMER2_INTERVAL, NULL);//设置计时器
			SetTimer(3, USER_TIMER3_INTERVAL, NULL);//设置计时器
		}
		else
		{
			g_bPlayStatus = false;//暂停
			SpiritualMCINow.SpiritualMCIPause();//暂停播放
			KillTimer(2);//关闭计时器
			KillTimer(3);//关闭计时器
		}
	}

	//ButtonNext按下
	if(g_ButtonNext.SpiritualButtonIsClick(g_MousePoint))
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//音乐数量大于0
		{
			if(g_ePlayMode == PlayMode_Random)//随机播放
			{
				srand((unsigned int)time(NULL));//产生随机数种子
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//当前音乐标号小于0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//播放音乐
			}
			else
			{
				g_nMusicNumber++;
				
				if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
				{
					g_nMusicNumber = 0;//循环
				}

				SpiritualPlayMusic();//播放音乐
			}
		}
	}

	//g_ButtonConfig按下
	if(g_ButtonConfig.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bConfigClickFlag == false)
		{
			g_bConfigClickFlag = true;//Config单击标志
		}
		else
		{
			g_bConfigClickFlag = false;//Config未单击
		}
	}

	//g_ButtonList按下
	if(g_ButtonList.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bMusicListClickFlag == false)
		{
			g_bMusicListClickFlag = true;//音乐列表按钮按下
		}
		else
		{
			g_bMusicListClickFlag = false;//音乐列表按钮释放
		}
	}

	//g_ButtonHome按下
	if(g_ButtonHome.SpiritualButtonIsClick(g_MousePoint))
	{
		g_bConfigClickFlag = false;//Config未单击
		g_bMusicListClickFlag = false;//音乐列表按钮释放
	}

	//g_ButtonPlayVolume按下
	if(g_ButtonPlayVolumeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bVolumeControlFlag == false)
		{
			g_bVolumeControlFlag = true;//调节音量打开
		}
		else
		{
			g_bVolumeControlFlag = false;//调节音量关闭
		}
	}

	//g_ButtonPlayMode按下
	if(g_ButtonPlayModeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_ePlayMode == PlayMode_Single)
		{
			g_ePlayMode = PlayMode_Circle;//列表循环
		}
		else if(g_ePlayMode == PlayMode_Circle)
		{
			g_ePlayMode = PlayMode_Order;//顺序播放
		}
		else if(g_ePlayMode == PlayMode_Order)
		{
			g_ePlayMode = PlayMode_Random;//随机播放
		}
		else if(g_ePlayMode == PlayMode_Random)
		{
			g_ePlayMode = PlayMode_Single;//单曲循环
		}
	}

	//g_ButtonLove按下
	if(g_ButtonLove.SpiritualButtonIsClick(g_MousePoint))
	{

	}

	//g_ButtonAdd按下
	if(g_ButtonAdd.SpiritualButtonIsClick(g_MousePoint))
	{
		char FileFilter[] = "mp3文件(*.mp3)|*.mp3|"
			"wav文件(*.wav)|*.wav|"
			"wma文件(*.wma)|*.wma|";

		CFileDialog *dlg = new CFileDialog(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, FileFilter);

		g_bPlayStatus = false;//暂停
		SpiritualMCINow.SpiritualMCIPause();//暂停播放
		KillTimer(2);//关闭计时器
		KillTimer(3);//关闭计时器

		if(dlg->DoModal() == IDOK)
		{
			CString StrFilepath = dlg->GetPathName();
			CString StrFilename = dlg->GetFileName();
			CString StrFileTitle = dlg->GetFileTitle();

			if(SpiritualMCINow.SpiritualMCIOpen(StrFilepath))//MCI打开音乐
			{
				int Length = g_MusicList.GetCount();

				if(Length == 0)//音乐列表为空
				{
					g_MusicList.Add(StrFilepath);//音乐路径
					g_MusicNameList.Add(StrFileTitle);//音乐名称
				}
				else//音乐列表有音乐
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
						g_MusicList.Add(StrFilepath);//音乐路径
						g_MusicNameList.Add(StrFileTitle);//音乐名称
					}
				}

				SpiritualMCINow.SpiritualMCIWrite(g_MusicList, g_nMusicNumber);//音乐列表存储
				SpiritualMCINow.SpiritualMCIWrite(g_MusicNameList);//音乐名称列表存储
																			   
				SpiritualPlayMusic();//播放音乐
			}
		}

		delete dlg;
	}

	//ButtonScheduleBar按下
	if(g_ButtonScheduleBar.SpiritualButtonIsClick(g_MousePoint))
	{
		g_bButtonScheduleBarClickFlag = true;//ScheduleBar按下
	}
	
	//PanelScheduleDown按下
	if(g_PanelScheduleDown.SpiritualPanelIsClick(g_MousePoint))
	{
		if(g_bButtonScheduleBarClickFlag == false)//ScheduleBar未按下
		{
			DWORD ScheduleNow = 0;

			g_PanelScheduleUpNowPosX = g_MousePoint.x;

			if(g_PanelScheduleUpNowPosX < 80)//限制范围
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

	//MusicVolume音量调节相关
	if(g_bVolumeControlFlag == true)//音量调节按钮按下
	{
		//ButtonVolumeBar按下
		if(g_ButtonVolumeBar.SpiritualButtonIsClick(g_MousePoint))
		{
			g_bButtonVolumeBarClickFlag = true;//ButtonVolumeBar按下
		}

		//PanelVolumeDown按下
		if(g_PanelVolumeDown.SpiritualPanelIsClick(g_MousePoint))
		{
			DWORD VolumeNow = 0;

			g_PanelVolumeUpNowPosY = g_MousePoint.y;//鼠标Y坐标值

			if(g_PanelVolumeUpNowPosY < 360)//限制范围(360~460)
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
				g_bPlayVolume = false;//音量最小
			}
			else
			{
				g_bPlayVolume = true;//音量最大
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

	//MusicList音乐列表相关
	if(g_bMusicListClickFlag == true)
	{
		//MusicListPageLast(音乐列表上一页)
		if(g_ButtonMusicListPageLast.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//音乐列表页数大于0
			{
				g_nMusicListNowPage--;
				if(g_nMusicListNowPage < 1)//当前列表页数小于1
				{
					g_nMusicListNowPage = g_nMusicListAllPage;//当前列表页数最大
				}
			}
		}

		//MusicListPageNext(音乐列表下一页)
		if(g_ButtonMusicListPageNext.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//音乐列表页数大于0
			{
				g_nMusicListNowPage++;
				if(g_nMusicListNowPage > g_nMusicListAllPage)//当前列表页数大于总页数
				{
					g_nMusicListNowPage = 1;
				}
			}
		}
	}

	//SetTitle
	if(g_bConfigClickFlag == true)
	{
		if(g_PanelTitleImage[0].SpiritualPanelIsClick(g_MousePoint))//Title1按下
		{
			g_nTitleImageNumber = 1;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[1].SpiritualPanelIsClick(g_MousePoint))//Title2按下
		{
			g_nTitleImageNumber = 2;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[2].SpiritualPanelIsClick(g_MousePoint))//Title3按下
		{
			g_nTitleImageNumber = 3;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[3].SpiritualPanelIsClick(g_MousePoint))//Title4按下
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

#pragma region OnLButtonDblClk(鼠标左键双击)
/*
** 鼠标左键双击
*/
void CSpiritualDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	**检测按钮按下
	*/

	//ButtonLast按下
	if(g_ButtonLast.SpiritualButtonIsClick(g_MousePoint))//上一首音乐
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//音乐数量大于0
		{
			if(g_ePlayMode == PlayMode_Random)//随机播放
			{
				srand((unsigned int)time(NULL));//产生随机数种子
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//当前音乐标号小于0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//播放音乐
			}
			else//其余模式
			{
				g_nMusicNumber--;

				if(g_nMusicNumber < 0)//当前音乐标号小于0
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;//循环
				}

				SpiritualPlayMusic();//播放音乐
			}
		}

	}

	//ButtonPlayStatus按下
	if(g_ButtonPlayStatusCheck.SpiritualButtonIsClick(g_MousePoint))//播放/暂停
	{
		if(g_bPlayStatus == false)
		{
			g_bPlayStatus = true;//播放
			SpiritualMCINow.SpiritualMCIResume();//重新播放
			SetTimer(2, USER_TIMER2_INTERVAL, NULL);//设置计时器
			SetTimer(3, USER_TIMER3_INTERVAL, NULL);//设置计时器
		}
		else
		{
			g_bPlayStatus = false;//暂停
			SpiritualMCINow.SpiritualMCIPause();//暂停播放
			KillTimer(2);//关闭计时器
			KillTimer(3);//关闭计时器
		}
	}

	//ButtonNext按下
	if(g_ButtonNext.SpiritualButtonIsClick(g_MousePoint))
	{
		int MusicNumberNow = g_MusicList.GetCount();

		if(MusicNumberNow > 0)//音乐数量大于0
		{
			if(g_ePlayMode == PlayMode_Random)//随机播放
			{
				srand((unsigned int)time(NULL));//产生随机数种子
				g_nMusicNumber = (int)(rand() % g_MusicList.GetCount());//MusicNumber(0~g_MusicList.GetCount()-1)

				if(g_nMusicNumber < 0)//当前音乐标号小于0
				{
					g_nMusicNumber = 0;
				}
				else if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
				{
					g_nMusicNumber = g_MusicList.GetCount() - 1;
				}

				SpiritualPlayMusic();//播放音乐
			}
			else
			{
				g_nMusicNumber++;

				if(g_nMusicNumber > g_MusicList.GetCount() - 1)//当前音乐标号大于最大
				{
					g_nMusicNumber = 0;//循环
				}

				SpiritualPlayMusic();//播放音乐
			}
		}
	}

	//g_ButtonConfig按下
	if(g_ButtonConfig.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bConfigClickFlag == false)
		{
			g_bConfigClickFlag = true;//Config单击标志
		}
		else
		{
			g_bConfigClickFlag = false;//Config未单击
		}
	}

	//g_ButtonList按下
	if(g_ButtonList.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bMusicListClickFlag == false)
		{
			g_bMusicListClickFlag = true;//音乐列表按钮按下
		}
		else
		{
			g_bMusicListClickFlag = false;//音乐列表按钮释放
		}
	}

	//g_ButtonHome按下
	if(g_ButtonHome.SpiritualButtonIsClick(g_MousePoint))
	{
		g_bConfigClickFlag = false;//Config未单击
		g_bMusicListClickFlag = false;//音乐列表按钮释放
	}

	//g_ButtonPlayVolume按下
	if(g_ButtonPlayVolumeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_bPlayVolume == false)
		{
			g_bPlayVolume = true;//音量最大
			g_PanelVolumeUpNowPosY = 360;
			g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
			SpiritualMCINow.SpiritualMCISetVolume(USER_VOLUME_MAX);//音量最大
		}
		else
		{
			g_bPlayVolume = false;//音量最小
			g_PanelVolumeUpNowPosY = 460;
			g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
			SpiritualMCINow.SpiritualMCISetVolume(USER_VOLUME_MIN);//音量最小
		}

		if(g_bVolumeControlFlag == false)
		{
			g_bVolumeControlFlag = true;//调节音量打开
		}
		else
		{
			g_bVolumeControlFlag = false;//调节音量关闭
		}
	}

	//g_ButtonPlayMode按下
	if(g_ButtonPlayModeCheck.SpiritualButtonIsClick(g_MousePoint))
	{
		if(g_ePlayMode == PlayMode_Single)
		{
			g_ePlayMode = PlayMode_Circle;//列表循环
		}
		else if(g_ePlayMode == PlayMode_Circle)
		{
			g_ePlayMode = PlayMode_Order;//顺序播放
		}
		else if(g_ePlayMode == PlayMode_Order)
		{
			g_ePlayMode = PlayMode_Random;//随机播放
		}
		else if(g_ePlayMode == PlayMode_Random)
		{
			g_ePlayMode = PlayMode_Single;//单曲循环
		}
	}



	//MusicList音乐列表相关
	if(g_bMusicListClickFlag == true)
	{
		//MusicListPageLast(音乐列表上一页)
		if(g_ButtonMusicListPageLast.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//音乐列表页数大于0
			{
				g_nMusicListNowPage--;
				if(g_nMusicListNowPage < 1)//当前列表页数小于1
				{
					g_nMusicListNowPage = g_nMusicListAllPage;//当前列表页数最大
				}
			}
		}

		//MusicListPageNext(音乐列表下一页)
		if(g_ButtonMusicListPageNext.SpiritualButtonIsClick(g_MousePoint))
		{
			if(g_nMusicListAllPage > 0)//音乐列表页数大于0
			{
				g_nMusicListNowPage++;
				if(g_nMusicListNowPage > g_nMusicListAllPage)//当前列表页数大于总页数
				{
					g_nMusicListNowPage = 1;
				}
			}
		}

		//MusicListPanelClick(音乐名称双击)
		if(g_TextMusicListLine[0].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 0) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 0;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}
		else if(g_TextMusicListLine[1].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 1) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 1;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}
		else if(g_TextMusicListLine[2].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 2) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 2;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}
		else if(g_TextMusicListLine[3].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 3) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 3;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}
		else if(g_TextMusicListLine[4].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 4) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 4;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}
		else if(g_TextMusicListLine[5].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 5) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 5;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}
		else if(g_TextMusicListLine[6].SpiritualTextIsClick(g_MousePoint))
		{
			if(g_nMusicListNowPage > 0)//存在音乐列表
			{
				if(((g_nMusicListNowPage - 1) * 7 + 6) < g_MusicList.GetCount())//音乐路径存在
				{
					g_nMusicNumber = (g_nMusicListNowPage - 1) * 7 + 6;
					SpiritualPlayMusic();//播放音乐
				}
			}
		}

	}

	//SetTitle
	if(g_bConfigClickFlag == true)
	{
		if(g_PanelTitleImage[0].SpiritualPanelIsClick(g_MousePoint))//Title1按下
		{
			g_nTitleImageNumber = 1;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[1].SpiritualPanelIsClick(g_MousePoint))//Title2按下
		{
			g_nTitleImageNumber = 2;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[2].SpiritualPanelIsClick(g_MousePoint))//Title3按下
		{
			g_nTitleImageNumber = 3;
			g_bConfigClickFlag = false;
		}
		else if(g_PanelTitleImage[3].SpiritualPanelIsClick(g_MousePoint))//Title4按下
		{
			g_nTitleImageNumber = 4;
			g_bConfigClickFlag = false;
		}
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}
#pragma endregion

#pragma region SpiritualConfigWrite(配置文件写入函数)
/*
**Spiritual配置文件写入函数
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

	WriteString.Format("%d", g_nTitleImageNumber);//Title背景
	WritePrivateProfileString("Spiritual Config", "Title", WriteString, NowPath);
	WriteString.Format("%d", g_nMusicNumber);//Music序号
	WritePrivateProfileString("Spiritual Config", "MusicNumber", WriteString, NowPath);
	WriteString.Format("%d", g_ePlayMode);//PlayMode播放模式
	WritePrivateProfileString("Spiritual Config", "PlayMode", WriteString, NowPath);
	WriteString.Format("%d", g_PanelVolumeUpNowPosY);//Volume音量大小
	WritePrivateProfileString("Spiritual Config", "VolumePosY", WriteString, NowPath);
}

#pragma endregion

#pragma region SpiritualConfigRead(配置文件读取函数)
/*
**Spiritual配置文件读取函数
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

	if(PathFileExists(NowPath))//配置文件存在
	{
		//获取Title背景
		GetPrivateProfileString("Spiritual Config", "Title", "0", ReadString, 127, NowPath);
		g_nTitleImageNumberLast = g_nTitleImageNumber = atoi(ReadString);//Title背景
		if(g_nTitleImageNumber < 0 || g_nTitleImageNumber > 4)//特殊情况
		{
			g_nTitleImageNumberLast = g_nTitleImageNumber = 0;
		}

		//获取Music序号
		if(g_MusicList.GetCount() > 0)//存在音乐列表
		{
			GetPrivateProfileString("Spiritual Config", "MusicNumber", "0", ReadString, 127, NowPath);
			g_nMusicNumber = atoi(ReadString);//Music序号
			if(g_nMusicNumber < 0 || g_nMusicNumber >= g_MusicList.GetCount())//特殊情况
			{
				g_nMusicNumber = g_MusicList.GetCount() - 1;
			}
		}

		//获取PlayMode播放模式
		GetPrivateProfileString("Spiritual Config", "PlayMode", "0", ReadString, 127, NowPath);
		switch(atoi(ReadString))//PlayMode播放模式
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

		//获取Volume音量大小
		GetPrivateProfileString("Spiritual Config", "VolumePosY", "0", ReadString, 127, NowPath);
		g_PanelVolumeUpNowPosY = atoi(ReadString);//Volume音量大小
		if(g_PanelVolumeUpNowPosY < 360 || g_PanelVolumeUpNowPosY > 460)//特殊情况
		{
			g_PanelVolumeUpNowPosY = 360;
		}
		g_VolumeValue.Format("%d", (100 - (g_PanelVolumeUpNowPosY - 360)));
	}

}

#pragma endregion

#pragma region SpiritualCaculateMusicList(计算音乐列表页数函数)
/*
**Spiritual计算音乐列表函数
*/
void CSpiritualDlg::SpiritualCaculateMusicList()
{
	//计算当前音乐列表页数
	if(g_MusicList.GetCount() > 0)//音乐列表存在音乐
	{
		if(g_MusicList.GetCount() % 7 == 0)//音乐数量为7整数倍(0,7,14,21,...)
		{
			if((g_nMusicNumber + 1) % 7 == 0)//整数页
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7;//当前页数
			}
			else//非整数页
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7 + 1;//当前页数
			}
			g_nMusicListAllPage = g_MusicList.GetCount() / 7;//总页数
		}
		else//音乐数量非7整数倍
		{
			if((g_nMusicNumber + 1) % 7 == 0)//整数页
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7;//当前页数
			}
			else//非整数页
			{
				g_nMusicListNowPage = (g_nMusicNumber + 1) / 7 + 1;//当前页数
			}
			g_nMusicListAllPage = g_MusicList.GetCount() / 7 + 1;//总页数
		}
	}
	else//音乐列表中不存在音乐
	{
		g_nMusicListNowPage = 0;
		g_nMusicListAllPage = 0;
	}
}
#pragma endregion

#pragma region SpiritualPlayMusic(播放音乐函数)
/*
**Spiritual播放音乐函数
*/
void CSpiritualDlg::SpiritualPlayMusic()
{
	DWORD VolumeNow = 0;

	//MusicList
	SpiritualCaculateMusicList();//计算音乐列表

	//MusicPlay
	SpiritualMCINow.SpiritualMCIPlay(g_MusicList.GetAt(g_nMusicNumber));//播放音乐
	VolumeNow = (DWORD)((1.0 - ((g_PanelVolumeUpNowPosY - 360) * 1.0 / 100)) * (USER_VOLUME_MAX - USER_VOLUME_MIN));
	SpiritualMCINow.SpiritualMCISetVolume(VolumeNow);//设置音量
	g_bPlayStatus = true;//播放
	KillTimer(2);//关闭计时器
	SetTimer(2, USER_TIMER2_INTERVAL, NULL);//设置计时器
	KillTimer(3);//关闭计时器
	SetTimer(3, USER_TIMER3_INTERVAL, NULL);//设置计时器
	g_nMusicName_StepCount = 0;
	g_nMusicName_StepFlag = 0;
}
#pragma endregion

#pragma region InitializeWindow(窗口初始化函数)
/*
**窗口初始化函数
*/
void CSpiritualDlg::InitializeWindow()
{
	CString NowPathUp;
	CString NowPathDown;
	CString NowNumber;
	SpiritualButton *pButtonTemp;

	/*
	** Panel图片加载
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
	** Button图片加载
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
	** 读取音乐列表
	*/
	SpiritualMCINow.SpiritualMCIGetHWND(m_hWnd);
	SpiritualMCINow.SpiritualMCISetVolume(USER_VOLUME_MAX);//设置音量最大
	SpiritualMCINow.SpiritualMCIRead(g_MusicList, g_nMusicNumber);//读取音乐路径列表
	SpiritualMCINow.SpiritualMCIRead(g_MusicNameList);//读取音乐名称列表
	
	/*
	** 读取配置文件
	*/
	SpiritualConfigRead();//读取配置文件

	if(g_MusicList.GetCount() > 0)//音乐列表存在
	{
		SpiritualPlayMusic();//播放音乐
	}
	else
	{
		g_bPlayStatus = false;//暂停
		SpiritualMCINow.SpiritualMCIStop();//停止播放
		KillTimer(2);//关闭计时器
		KillTimer(3);//关闭计时器
	}

	SetTimer(1, USER_TIMER1_INTERVAL, NULL);//设置定时刷新(10ms)
}
#pragma endregion

#pragma region RePaintWindow(窗口重绘函数)
/*
**窗口重绘函数
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

	//标志记录
	if(g_nTitleImageNumber != g_nTitleImageNumberLast)
	{
		g_bTitleImageChange = true;
		g_bTitleImageConvertFinish = false;//转换未完成
		g_nTitleAlphaValue = 0;
		g_nTitleImageLast = g_nTitleImageNumberLast;
		SetTimer(4, USER_TIMER4_INTERVAL, NULL);//定时
	}

	//Title标题重绘
	//g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//最底层标题背景

	if(g_bTitleImageConvertFinish)//转换完成
	{
		if(g_nTitleImageNumber == 1)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//最底层标题背景
		}
		else if(g_nTitleImageNumber == 2)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE1);//最底层标题背景
		}
		else if(g_nTitleImageNumber == 3)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE2);//最底层标题背景
		}
		else if(g_nTitleImageNumber == 4)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE4);//最底层标题背景
		}
		else
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//最底层标题背景
		}

		//Panel框架重绘

		//Schedule音乐播放进度调节
		if(g_PanelScheduleUpNowPosX > 537)//消除播放进度按钮遮挡区域
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, 0, 3, RGB(176, 94, 94), RGB(176, 94, 94));//音乐播放进度(下层)
		}
		else
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, (450 - (g_PanelScheduleUpNowPosX - 87)), 3, RGB(176, 94, 94), RGB(176, 94, 94));//音乐播放进度(下层)
		}

		if(g_PanelScheduleUpNowPosX < 87)//消除播放进度按钮遮挡区域
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, 0, 3, RGB(240, 128, 128), RGB(240, 128, 128));//音乐播放进度(上层)
		}
		else
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, (g_PanelScheduleUpNowPosX - 87), 3, RGB(240, 128, 128), RGB(240, 128, 128));//音乐播放进度(上层)
		}

		g_ButtonScheduleBar.SpiritualButtonDrawImage(MemDC, (72 + g_PanelScheduleUpNowPosX - 80), 444, g_MousePoint);//Schedule

		//MusicList音乐列表
		if(g_bMusicListClickFlag == true)
		{
			//Text
			g_MusicListPageNumber.Format("%d/%d", g_nMusicListNowPage, g_nMusicListAllPage);//MusicListPage
			g_TextMusicListPage.SpiritualTextDrawOutCenter(MemDC, g_MusicListPageNumber);//MusicListPage输出

			for(int i = 0; i < 7; i++)
			{
				g_TextMusicListLine[i].SpiritualTextDrawBackGround(MemDC, RGB(249, 208, 208), RGB(249, 208, 208), g_MousePoint);//MusicList背景输出
			}

			if(g_nMusicListNowPage >= 1 && g_nMusicListNowPage <= g_nMusicListAllPage)//当前存在音乐
			{
				//MusicLine1
				if(((g_nMusicListNowPage - 1) * 7 + 0) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 1) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 2) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 3) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 4) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 5) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 6) < g_MusicList.GetCount())//音乐存在
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
			g_ButtonMusicListPageLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageLast(音乐列表上一页)
			g_ButtonMusicListPageNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageNext(音乐列表下一页)
		}

		//Volume音量调节
		if(g_bVolumeControlFlag == true)//单击调节音量
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

		//SetTitle设置背景
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
				g_bConfigClickConvertFinish = false;//转换未完成
				g_bConfigConvertDirect = false;
				g_nConfigAlphaValue = 0;

				g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
				
				for(int i = 0; i < 4; i++)
				{
					g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
				}
				SetTimer(5, USER_TIMER5_INTERVAL, NULL);//定时
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
				g_bConfigClickConvertFinish = false;//转换未完成
				g_bConfigConvertDirect = true;
				g_nConfigAlphaValue = 255;

				g_PanelTitleImageBottom.SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);

				for(int i = 0; i < 4; i++)
				{
					g_PanelTitleImage[i].SpiritualPanelDrawImage(MemDC, g_nConfigAlphaValue);
				}
				SetTimer(5, USER_TIMER5_INTERVAL, NULL);//定时
			}
		}

		//Button按键重绘
		g_ButtonLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLast(上一首)
		g_ButtonNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonNext(下一首)
		g_ButtonConfig.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonConfig(背景设置)
		g_ButtonList.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonList(播放列表)
		g_ButtonHome.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonHome(主菜单)
		g_ButtonLove.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLove(喜爱音乐)
		g_ButtonAdd.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonAdd(添加音乐)

		if(g_bPlayStatus == false)//播放状态
		{
			g_ButtonPlayStatus[PlayStatus_Play].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayStatus[PlayStatus_Pause].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}

		if(g_bPlayVolume == false)//播放音量
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMin].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMax].SpiritualButtonDrawImage(MemDC, g_MousePoint);
		}

		if(g_ePlayMode == PlayMode_Single)//播放模式
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

		//Text文本重绘
		if(g_MusicNameList.GetCount() > 0)//存在音乐列表
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, g_MusicNameList.GetAt(g_nMusicNumber), g_nMusicName_StepCount, 320);//MusicName音乐名称
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor音乐作者
		}
		else
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, "MusicName", 0, 320);//MusicName音乐名称
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor音乐作者
		}
		g_TextPlayNowTime.SpiritualTextDrawOut(MemDC, g_sPlayNowTime);//PlayNowTime播放当前进度时间
		g_TextPlayEndTime.SpiritualTextDrawOut(MemDC, g_sPlayEndTime);//PlayEndTime播放结束进度时间

		//鼠标坐标
		/*CString Mouse;
		CFont Font;
		MemDC.SetBkMode(TRANSPARENT);
		MemDC.SetTextColor(RGB(0, 0, 0));
		Font.CreatePointFont(100, "等线 Light");
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

		//窗口重绘
		g_NowWindow.SpiritualWindowReDraw(pDC, MemDC);
	}
	else//转换未完成
	{
		if(g_nTitleImageNumber == 1)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//最底层标题背景
		}
		else if(g_nTitleImageNumber == 2)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE1);//最底层标题背景
		}
		else if(g_nTitleImageNumber == 3)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE2);//最底层标题背景
		}
		else if(g_nTitleImageNumber == 4)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE4);//最底层标题背景
		}
		else
		{
			g_NowWindow.SpiritualWindowDrawBitmap(MemDC, IDB_BITMAP_TITLE);//最底层标题背景
		}

		if(g_nTitleImageLast == 1)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE);//最底层标题背景
		}
		else if(g_nTitleImageLast == 2)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE1);//最底层标题背景
		}
		else if(g_nTitleImageLast == 3)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE2);//最底层标题背景
		}
		else if(g_nTitleImageLast == 4)
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE4);//最底层标题背景
		}
		else
		{
			g_NowWindow.SpiritualWindowDrawBitmap(NewDC, IDB_BITMAP_TITLE);//最底层标题背景
		}

		//Panel框架重绘

		//Schedule音乐播放进度调节
		if(g_PanelScheduleUpNowPosX > 537)//消除播放进度按钮遮挡区域
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, 0, 3, RGB(176, 94, 94), RGB(176, 94, 94));//音乐播放进度(下层)
			g_PanelScheduleDown.SpiritualPanelDrawImage(NewDC, 544, 453, 0, 3, RGB(176, 94, 94), RGB(176, 94, 94));//音乐播放进度(下层)
		}
		else
		{
			g_PanelScheduleDown.SpiritualPanelDrawImage(MemDC, 544, 453, (450 - (g_PanelScheduleUpNowPosX - 87)), 3, RGB(176, 94, 94), RGB(176, 94, 94));//音乐播放进度(下层)
			g_PanelScheduleDown.SpiritualPanelDrawImage(NewDC, 544, 453, (450 - (g_PanelScheduleUpNowPosX - 87)), 3, RGB(176, 94, 94), RGB(176, 94, 94));//音乐播放进度(下层)
		}

		if(g_PanelScheduleUpNowPosX < 87)//消除播放进度按钮遮挡区域
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, 0, 3, RGB(240, 128, 128), RGB(240, 128, 128));//音乐播放进度(上层)
			g_PanelScheduleUp.SpiritualPanelDrawImage(NewDC, 0, 3, RGB(240, 128, 128), RGB(240, 128, 128));//音乐播放进度(上层)
		}
		else
		{
			g_PanelScheduleUp.SpiritualPanelDrawImage(MemDC, (g_PanelScheduleUpNowPosX - 87), 3, RGB(240, 128, 128), RGB(240, 128, 128));//音乐播放进度(上层)
			g_PanelScheduleUp.SpiritualPanelDrawImage(NewDC, (g_PanelScheduleUpNowPosX - 87), 3, RGB(240, 128, 128), RGB(240, 128, 128));//音乐播放进度(上层)
		}

		g_ButtonScheduleBar.SpiritualButtonDrawImage(MemDC, (72 + g_PanelScheduleUpNowPosX - 80), 444, g_MousePoint);//Schedule
		g_ButtonScheduleBar.SpiritualButtonDrawImage(NewDC, (72 + g_PanelScheduleUpNowPosX - 80), 444, g_MousePoint);//Schedule

		//MusicList音乐列表
		if(g_bMusicListClickFlag == true)
		{
			//Text
			g_MusicListPageNumber.Format("%d/%d", g_nMusicListNowPage, g_nMusicListAllPage);//MusicListPage
			g_TextMusicListPage.SpiritualTextDrawOutCenter(MemDC, g_MusicListPageNumber);//MusicListPage输出
			g_TextMusicListPage.SpiritualTextDrawOutCenter(NewDC, g_MusicListPageNumber);//MusicListPage输出

			for(int i = 0; i < 7; i++)
			{
				g_TextMusicListLine[i].SpiritualTextDrawBackGround(MemDC, RGB(249, 208, 208), RGB(249, 208, 208), g_MousePoint);//MusicList背景输出
				g_TextMusicListLine[i].SpiritualTextDrawBackGround(NewDC, RGB(249, 208, 208), RGB(249, 208, 208), g_MousePoint);//MusicList背景输出
			}

			if(g_nMusicListNowPage >= 1 && g_nMusicListNowPage <= g_nMusicListAllPage)//当前存在音乐
			{
				//MusicLine1
				if(((g_nMusicListNowPage - 1) * 7 + 0) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 1) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 2) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 3) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 4) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 5) < g_MusicList.GetCount())//音乐存在
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
				if(((g_nMusicListNowPage - 1) * 7 + 6) < g_MusicList.GetCount())//音乐存在
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
			g_ButtonMusicListPageLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageLast(音乐列表上一页)
			g_ButtonMusicListPageNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//MusicListPageNext(音乐列表下一页)
			g_ButtonMusicListPageLast.SpiritualButtonDrawImage(NewDC, g_MousePoint);//MusicListPageLast(音乐列表上一页)
			g_ButtonMusicListPageNext.SpiritualButtonDrawImage(NewDC, g_MousePoint);//MusicListPageNext(音乐列表下一页)
		}

		//Volume音量调节
		if(g_bVolumeControlFlag == true)//单击调节音量
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

		//SetTitle设置背景
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

		//Button按键重绘
		g_ButtonLast.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLast(上一首)
		g_ButtonNext.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonNext(下一首)
		g_ButtonConfig.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonConfig(背景设置)
		g_ButtonList.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonList(播放列表)
		g_ButtonHome.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonHome(主菜单)
		g_ButtonLove.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonLove(喜爱音乐)
		g_ButtonAdd.SpiritualButtonDrawImage(MemDC, g_MousePoint);//ButtonAdd(添加音乐)
		g_ButtonLast.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonLast(上一首)
		g_ButtonNext.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonNext(下一首)
		g_ButtonConfig.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonConfig(背景设置)
		g_ButtonList.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonList(播放列表)
		g_ButtonHome.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonHome(主菜单)
		g_ButtonLove.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonLove(喜爱音乐)
		g_ButtonAdd.SpiritualButtonDrawImage(NewDC, g_MousePoint);//ButtonAdd(添加音乐)

		if(g_bPlayStatus == false)//播放状态
		{
			g_ButtonPlayStatus[PlayStatus_Play].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayStatus[PlayStatus_Play].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayStatus[PlayStatus_Pause].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayStatus[PlayStatus_Pause].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}

		if(g_bPlayVolume == false)//播放音量
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMin].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayVolume[PlayVolume_VolumeMin].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}
		else
		{
			g_ButtonPlayVolume[PlayVolume_VolumeMax].SpiritualButtonDrawImage(MemDC, g_MousePoint);
			g_ButtonPlayVolume[PlayVolume_VolumeMax].SpiritualButtonDrawImage(NewDC, g_MousePoint);
		}

		if(g_ePlayMode == PlayMode_Single)//播放模式
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

		//Text文本重绘
		if(g_MusicNameList.GetCount() > 0)//存在音乐列表
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, g_MusicNameList.GetAt(g_nMusicNumber), g_nMusicName_StepCount, 320);//MusicName音乐名称
			g_TextMusicName.SpiritualTextDrawOutMove(NewDC, g_MusicNameList.GetAt(g_nMusicNumber), g_nMusicName_StepCount, 320);//MusicName音乐名称
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor音乐作者
		}
		else
		{
			g_TextMusicName.SpiritualTextDrawOutMove(MemDC, "MusicName", 0, 320);//MusicName音乐名称
			g_TextMusicName.SpiritualTextDrawOutMove(NewDC, "MusicName", 0, 320);//MusicName音乐名称
			//g_TextMusicAuthor.SpiritualTextDrawOutMove(MemDC, "Author", 0, 320);//MusicAuthor音乐作者
		}
		g_TextPlayNowTime.SpiritualTextDrawOut(MemDC, g_sPlayNowTime);//PlayNowTime播放当前进度时间
		g_TextPlayEndTime.SpiritualTextDrawOut(MemDC, g_sPlayEndTime);//PlayEndTime播放结束进度时间
		g_TextPlayNowTime.SpiritualTextDrawOut(NewDC, g_sPlayNowTime);//PlayNowTime播放当前进度时间
		g_TextPlayEndTime.SpiritualTextDrawOut(NewDC, g_sPlayEndTime);//PlayEndTime播放结束进度时间

		//鼠标坐标
		/*CString Mouse;
		CFont Font;
		MemDC.SetBkMode(TRANSPARENT);
		MemDC.SetTextColor(RGB(0, 0, 0));
		Font.CreatePointFont(100, "等线 Light");
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

		//窗口重绘
		g_NowWindow.SpiritualWindowReDraw(pDC, MemDC, g_nTitleAlphaValue);
	}

	//记录TitleImageNumber值
	g_nTitleImageNumberLast = g_nTitleImageNumber;
	g_bConfigClickFlagLast = g_bConfigClickFlag;

	DeleteDC(MemDC);
	DeleteDC(NewDC);
	ReleaseDC(pDC);
}
#pragma endregion

#pragma region CleanUpWindow(窗口清理函数)
/*
**窗口清理函数
*/
void CSpiritualDlg::CleanUpWindow()
{
	//清理释放内存

	//Window
	g_NowWindow.~SpiritualWindow();//析构函数

	//Panel
	g_PanelBottom.~SpiritualPanel();//析构函数
	g_PanelScheduleUp.~SpiritualPanel();//析构函数
	g_PanelScheduleDown.~SpiritualPanel();//析构函数
	g_PanelVolumeBottom.~SpiritualPanel();//析构函数
	g_PanelVolumeUp.~SpiritualPanel();//析构函数
	g_PanelVolumeDown.~SpiritualPanel();//析构函数
	g_PanelTitleImageBottom.~SpiritualPanel();//析构函数

	for(int i = 0; i < 4; i++)
	{
		g_PanelTitleImage[i].~SpiritualPanel();//析构函数
	}

	//Button
	g_ButtonLast.~SpiritualButton();//析构函数
	g_ButtonPlayStatusCheck.~SpiritualButton();//析构函数
	g_ButtonNext.~SpiritualButton();//析构函数
	g_ButtonConfig.~SpiritualButton();//析构函数
	g_ButtonList.~SpiritualButton();//析构函数
	g_ButtonHome.~SpiritualButton();//析构函数
	g_ButtonPlayVolumeCheck.~SpiritualButton();//析构函数
	g_ButtonPlayModeCheck.~SpiritualButton();//析构函数
	g_ButtonLove.~SpiritualButton();//析构函数
	g_ButtonAdd.~SpiritualButton();//析构函数
	g_ButtonScheduleBar.~SpiritualButton();//析构函数
	g_ButtonVolumeBar.~SpiritualButton();//析构函数
	g_ButtonMusicListPageLast.~SpiritualButton();//析构函数
	g_ButtonMusicListPageNext.~SpiritualButton();//析构函数

	for(int i = 0; i < PlayStatus_Max; i++)
	{
		g_ButtonPlayStatus[i].~SpiritualButton();//析构函数
	}
	for(int i = 0; i < PlayVolume_Max; i++)
	{
		g_ButtonPlayVolume[i].~SpiritualButton();//析构函数
	}
	for(int i = 0; i < PlayMode_Max; i++)
	{
		g_ButtonPlayMode[i].~SpiritualButton();//析构函数
	}

	//Text
	//g_TextMusicName.~SpiritualText();//析构函数
	//g_TextMusicAuthor.~SpiritualText();//析构函数
	//g_TextPlayNowTime.~SpiritualText();//析构函数
	//g_TextPlayEndTime.~SpiritualText();//析构函数

	//MCI
	//SpiritualMCINow.~SpiritualMCI();//析构函数

	//Music
	//g_MusicList.~CStringArray();//析构函数

	//Timer
	//g_sPlayNowTime.~CStringT();
	//g_sPlayEndTime.~CStringT();

}
#pragma endregion
