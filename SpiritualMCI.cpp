#include "stdafx.h"
#include "Common.h"
#include "SpiritualMCI.h"

/*
** SpiritualMCI���캯��
** SpiritualMCI()
*/
SpiritualMCI::SpiritualMCI()
{
}

/*
** SpiritualMCI��������
** ~SpiritualMCI()
*/
SpiritualMCI::~SpiritualMCI()
{
}

/*
** SpiritualMCI���캯��(����+1)
** SpiritualMCI(HWND hWnd)
*/
SpiritualMCI::SpiritualMCI(HWND hWnd)
{
	m_hWnd = hWnd;
}

/*
** SpiritualMCI��ȡ���ھ��
** void SpiritualMCIGetHWND(HWND hWnd)
** Para: HWND hWnd(���ھ��)
*/
void SpiritualMCI::SpiritualMCIGetHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}

/*
** SpiritualMCI��
** void SpiritualMCIOpen(CString Path)
** Para: CString Path(Mp3�ļ�·��)
** Return: bool(true:OK,false:NO)
*/
bool SpiritualMCI::SpiritualMCIOpen(CString Path)
{
	DWORD ReturnValue;

	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0, 0);//�ر��豸
	m_MCIOpenParms.lpstrElementName = Path;//����·��
	if(ReturnValue = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&m_MCIOpenParms))
	{
		char Buff[256];
		mciGetErrorString(ReturnValue, Buff, 256);//��ȡ����
		AfxMessageBox(Buff);//������ʾ
		return false;
	}
	m_MCIDeviceID = m_MCIOpenParms.wDeviceID;//�豸ID
	return true;
}

/*
** SpiritualMCI���������б�
** void SpiritualMCIWrite(CStringArray &MusicList)
** Para: CStringArray &MusicList(�����б�)
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
** SpiritualMCI���������б�(����+1)
** void SpiritualMCIWrite(CStringArray &MusicList, int &MusicNumber)
** Para: CStringArray &MusicList(�����б�)
** Para: int &MusicNumber(�������)
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
	MusicNumber = MusicList.GetCount() - 1;//���µ�ǰ�������
	File->Close();

	delete File;
}

/*
** SpiritualMCI��ȡ�����б�
** void SpiritualMCIRead(CStringArray &MusicList)
** Para: CStringArray &MusicList(�����б�)
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

	if(PathFileExists(NowPath))//�����б��ļ�����
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
** SpiritualMCI��ȡ�����б�(����+1)
** void SpiritualMCIRead(CStringArray &MusicList, int &MusicNumber)
** Para: CStringArray &MusicList(�����б�)
** Para: int &MusicNumber(�������)
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

	if(PathFileExists(NowPath))//�����б��ļ�����
	{
		File->Open(NowPath, CFile::modeRead);
		while(File->ReadString(RString))
		{
			MusicList.Add(RString);
		}
		MusicNumber = MusicList.GetCount() - 1;//���µ�ǰ�������
		File->Close();
	}

	delete File;
}

/*
** SpiritualMCI��ȡ������Ϣ
** DWORD SpiritualMCIGetInformation(DWORD Item)
** Para: DWORD Item(������Ϣ)
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
** SpiritualMCI���ֲ���
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
** SpiritualMCI���ֲ���(����+1)
** void SpiritualMCIPlay(CString Path)
** Para: CString Path(����·��)
*/
void SpiritualMCI::SpiritualMCIPlay(CString Path)
{
	MCI_PLAY_PARMS *pMCIPlayParms = new MCI_PLAY_PARMS();

	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0, 0);//�ر��豸
	m_MCIOpenParms.lpstrElementName = Path;//����·��
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&m_MCIOpenParms);
	m_MCIDeviceID = m_MCIOpenParms.wDeviceID;//�豸ID
	pMCIPlayParms->dwCallback = (DWORD)m_hWnd;
	pMCIPlayParms->dwFrom = 0;
	mciSendCommand(m_MCIDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)pMCIPlayParms);

	delete pMCIPlayParms;
}

/*
** SpiritualMCI������ͣ
** void SpiritualMCIPause(void)
*/
void SpiritualMCI::SpiritualMCIPause(void)
{
	mciSendCommand(m_MCIDeviceID, MCI_PAUSE, 0, 0);
}

/*
** SpiritualMCI�������¿�ʼ
** void SpiritualMCIResume(void)
*/
void SpiritualMCI::SpiritualMCIResume(void)
{
	mciSendCommand(m_MCIDeviceID, MCI_RESUME, 0, 0);
}

/*
** SpiritualMCI����ֹͣ
** void SpiritualMCIStop(void)
*/
void SpiritualMCI::SpiritualMCIStop(void)
{
	mciSendCommand(m_MCIDeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0, 0);
}

/*
** SpiritualMCI������������
** void SpiritualMCISetVolume(DWORD Volume)
** Para: DWORD Volume(������С)
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
** SpiritualMCI�������ý���
** void SpiritualMCISeekTo(DWORD Item)
*/
void SpiritualMCI::SpiritualMCISeekTo(DWORD Item)
{
	MCI_SEEK_PARMS *pMCISeekParms = new MCI_SEEK_PARMS();

	pMCISeekParms->dwTo = Item;
	mciSendCommand(m_MCIDeviceID, MCI_SEEK, MCI_TO, (DWORD)pMCISeekParms);

	delete pMCISeekParms;
}