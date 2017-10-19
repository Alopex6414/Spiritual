#include "stdafx.h"
#include "Common.h"
#include "SpiritualMCI.h"

/*
** SpiritualMCI构造函数
** SpiritualMCI()
*/
SpiritualMCI::SpiritualMCI()
{
}

/*
** SpiritualMCI析构函数
** ~SpiritualMCI()
*/
SpiritualMCI::~SpiritualMCI()
{
}

/*
** SpiritualMCI构造函数(重载+1)
** SpiritualMCI(HWND hWnd)
*/
SpiritualMCI::SpiritualMCI(HWND hWnd)
{
	m_hWnd = hWnd;
}

/*
** SpiritualMCI获取窗口句柄
** void SpiritualMCIGetHWND(HWND hWnd)
** Para: HWND hWnd(窗口句柄)
*/
void SpiritualMCI::SpiritualMCIGetHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}

/*
** SpiritualMCI打开
** void SpiritualMCIOpen(CString Path)
** Para: CString Path(Mp3文件路径)
** Return: bool(true:OK,false:NO)
*/
bool SpiritualMCI::SpiritualMCIOpen(CString Path)
{
	DWORD ReturnValue;

	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0, 0);//关闭设备
	m_MCIOpenParms.lpstrElementName = Path;//音乐路径
	if(ReturnValue = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&m_MCIOpenParms))
	{
		char Buff[256];
		mciGetErrorString(ReturnValue, Buff, 256);//获取错误
		AfxMessageBox(Buff);//窗体显示
		return false;
	}
	m_MCIDeviceID = m_MCIOpenParms.wDeviceID;//设备ID
	return true;
}

/*
** SpiritualMCI保存音乐列表
** void SpiritualMCIWrite(CStringArray &MusicList)
** Para: CStringArray &MusicList(音乐列表)
*/
void SpiritualMCI::SpiritualMCIWrite(CStringArray &MusicList)
{
	CStdioFile *File = new CStdioFile;
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\MusicList\\MusicNameList.txt";
	
	File->Open(NowPath, CFile::modeCreate | CFile::modeWrite);
	for(int i = 0; i < MusicList.GetCount(); i++)
	{
		File->WriteString(MusicList.GetAt(i));
		File->WriteString("\n");
	}
	File->Close();

	delete File;
}

/*
** SpiritualMCI保存音乐列表(重载+1)
** void SpiritualMCIWrite(CStringArray &MusicList, int &MusicNumber)
** Para: CStringArray &MusicList(音乐列表)
** Para: int &MusicNumber(音乐序号)
*/
void SpiritualMCI::SpiritualMCIWrite(CStringArray &MusicList, int &MusicNumber)
{
	CStdioFile *File = new CStdioFile;
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\MusicList\\MusicList.txt";

	File->Open(NowPath, CFile::modeCreate | CFile::modeWrite);
	for(int i = 0; i < MusicList.GetCount(); i++)
	{
		File->WriteString(MusicList.GetAt(i));
		File->WriteString("\n");
	}
	MusicNumber = MusicList.GetCount() - 1;//更新当前音乐序号
	File->Close();

	delete File;
}

/*
** SpiritualMCI读取音乐列表
** void SpiritualMCIRead(CStringArray &MusicList)
** Para: CStringArray &MusicList(音乐列表)
*/
void SpiritualMCI::SpiritualMCIRead(CStringArray &MusicList)
{
	CStdioFile *File = new CStdioFile;
	CString RString;
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\MusicList\\MusicNameList.txt";

	if(PathFileExists(NowPath))//音乐列表文件存在
	{
		File->Open(NowPath, CFile::modeRead);
		while(File->ReadString(RString))
		{
			MusicList.Add(RString);
		}
		File->Close();
	}

	delete File;
}

/*
** SpiritualMCI读取音乐列表(重载+1)
** void SpiritualMCIRead(CStringArray &MusicList, int &MusicNumber)
** Para: CStringArray &MusicList(音乐列表)
** Para: int &MusicNumber(音乐序号)
*/
void SpiritualMCI::SpiritualMCIRead(CStringArray &MusicList, int &MusicNumber)
{
	CStdioFile *File = new CStdioFile;
	CString RString;
	CString NowPath;
	int nPos;

	GetModuleFileName(AfxGetInstanceHandle(), NowPath.GetBufferSetLength(_MAX_PATH + 1), _MAX_PATH);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	nPos = NowPath.ReverseFind('\\');
	NowPath = NowPath.Left(nPos);
	NowPath += "\\Spiritual\\MusicList\\MusicList.txt";

	if(PathFileExists(NowPath))//音乐列表文件存在
	{
		File->Open(NowPath, CFile::modeRead);
		while(File->ReadString(RString))
		{
			MusicList.Add(RString);
		}
		MusicNumber = MusicList.GetCount() - 1;//更新当前音乐序号
		File->Close();
	}

	delete File;
}

/*
** SpiritualMCI读取音乐信息
** DWORD SpiritualMCIGetInformation(DWORD Item)
** Para: DWORD Item(音乐信息)
** Return: DWORD
*/
DWORD SpiritualMCI::SpiritualMCIGetInformation(DWORD Item)
{
	MCI_STATUS_PARMS MCIStatusParms;

	MCIStatusParms.dwCallback = NULL;
	MCIStatusParms.dwItem = Item;
	MCIStatusParms.dwReturn = 0;
	mciSendCommand(m_MCIDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&MCIStatusParms);

	return MCIStatusParms.dwReturn;
}

/*
** SpiritualMCI音乐播放
** void SpiritualMCIPlay(void)
*/
void SpiritualMCI::SpiritualMCIPlay(void)
{
	MCI_PLAY_PARMS *pMCIPlayParms = new MCI_PLAY_PARMS();

	pMCIPlayParms->dwCallback = (DWORD)m_hWnd;
	pMCIPlayParms->dwFrom = 0;
	mciSendCommand(m_MCIDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)pMCIPlayParms);

	delete pMCIPlayParms;
}

/*
** SpiritualMCI音乐播放(重载+1)
** void SpiritualMCIPlay(CString Path)
** Para: CString Path(音乐路径)
*/
void SpiritualMCI::SpiritualMCIPlay(CString Path)
{
	MCI_PLAY_PARMS *pMCIPlayParms = new MCI_PLAY_PARMS();

	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0, 0);//关闭设备
	m_MCIOpenParms.lpstrElementName = Path;//音乐路径
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&m_MCIOpenParms);
	m_MCIDeviceID = m_MCIOpenParms.wDeviceID;//设备ID
	pMCIPlayParms->dwCallback = (DWORD)m_hWnd;
	pMCIPlayParms->dwFrom = 0;
	mciSendCommand(m_MCIDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)pMCIPlayParms);

	delete pMCIPlayParms;
}

/*
** SpiritualMCI音乐暂停
** void SpiritualMCIPause(void)
*/
void SpiritualMCI::SpiritualMCIPause(void)
{
	mciSendCommand(m_MCIDeviceID, MCI_PAUSE, 0, 0);
}

/*
** SpiritualMCI音乐重新开始
** void SpiritualMCIResume(void)
*/
void SpiritualMCI::SpiritualMCIResume(void)
{
	mciSendCommand(m_MCIDeviceID, MCI_RESUME, 0, 0);
}

/*
** SpiritualMCI音乐停止
** void SpiritualMCIStop(void)
*/
void SpiritualMCI::SpiritualMCIStop(void)
{
	mciSendCommand(m_MCIDeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0, 0);
}

/*
** SpiritualMCI音乐设置音量
** void SpiritualMCISetVolume(DWORD Volume)
** Para: DWORD Volume(音量大小)
*/
void SpiritualMCI::SpiritualMCISetVolume(DWORD Volume)
{
	MCI_DGV_SETAUDIO_PARMS *pMCISetAudioParms = new MCI_DGV_SETAUDIO_PARMS();

	pMCISetAudioParms->dwItem = MCI_DGV_SETAUDIO_VOLUME;
	pMCISetAudioParms->dwValue = Volume;
	mciSendCommand(m_MCIDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)pMCISetAudioParms);

	delete pMCISetAudioParms;
}

/*
** SpiritualMCI音乐设置进度
** void SpiritualMCISeekTo(DWORD Item)
*/
void SpiritualMCI::SpiritualMCISeekTo(DWORD Item)
{
	MCI_SEEK_PARMS *pMCISeekParms = new MCI_SEEK_PARMS();

	pMCISeekParms->dwTo = Item;
	mciSendCommand(m_MCIDeviceID, MCI_SEEK, MCI_TO, (DWORD)pMCISeekParms);

	delete pMCISeekParms;
}