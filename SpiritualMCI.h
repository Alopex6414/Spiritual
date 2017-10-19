#pragma once

#include "Common.h"

class SpiritualMCI
{
private:
	MCI_OPEN_PARMS m_MCIOpenParms;
	DWORD m_MCIDeviceID;
	HWND m_hWnd;

public:
	SpiritualMCI();
	~SpiritualMCI();
	SpiritualMCI(HWND hWnd);
	void SpiritualMCIGetHWND(HWND hWnd);
	bool SpiritualMCIOpen(CString Path);
	void SpiritualMCIWrite(CStringArray &MusicList);
	void SpiritualMCIWrite(CStringArray &MusicList, int &MusicNumber);
	void SpiritualMCIRead(CStringArray &MusicList);
	void SpiritualMCIRead(CStringArray &MusicList, int &MusicNumber);
	DWORD SpiritualMCIGetInformation(DWORD Item);
	void SpiritualMCIPlay(void);
	void SpiritualMCIPlay(CString Path);
	void SpiritualMCIPause(void);
	void SpiritualMCIResume(void);
	void SpiritualMCIStop(void);
	void SpiritualMCISetVolume(DWORD Volume);
	void SpiritualMCISeekTo(DWORD Item);
};

