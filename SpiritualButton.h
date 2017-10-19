#pragma once

enum SpiritualButtonStatus
{
	Status_Up,
	Status_Down,
};//按钮状态

enum SpiritualButtonPlayVolume
{
	PlayVolume_VolumeMax = 0,//最大音量
	PlayVolume_VolumeMin = 1,//最小音量
	PlayVolume_Max = 2,//(Max)
};//播放音量

enum SpiritualButtonPlayStatus
{
	PlayStatus_Play = 0,//播放
	PlayStatus_Pause = 1,//暂停
	PlayStatus_Max = 2,//(Max)
};//播放状态

enum SpiritualButtonPlayMode
{
	PlayMode_Single = 0,//单循环
	PlayMode_Circle = 1,//全循环
	PlayMode_Order = 2,//顺序播放
	PlayMode_Random = 3,//随机播放
	PlayMode_Max = 4,//(Max)
};//播放模式

class SpiritualButton
{
private:
	bool m_bIsVisiable;//控件可见性
	int m_nPosX;//控件X坐标
	int m_nPosY;//控件Y坐标
	int m_nWidth;//控件宽度(加载图片宽度)
	int m_nHeight;//控件高度(加载图片高度)
	CImage m_IButtonUp;//控件图片(获取焦点)
	CImage m_IButtonDown;//控件图片(失去焦点)

public:
	SpiritualButton();
	~SpiritualButton();
	SpiritualButton(int PosX, int PosY);
	SpiritualButton(int PosX, int PosY, int Width, int Height);
	void SpiritualButtonLoadImage(CString ButtonUpFileName, CString ButtonDownFileName);
	void SpiritualButtonDrawImage(CDC &MemDC, SpiritualButtonStatus ButtonStatus);
	void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, SpiritualButtonStatus ButtonStatus);
	void SpiritualButtonDrawImage(CDC &MemDC, CPoint MousePoint);
	void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, CPoint MousePoint);
	void SpiritualButtonDrawImage(CDC &MemDC, int PosX, int PosY, int Width, int Height, CPoint MousePoint);
	bool SpiritualButtonIsClick(CPoint MousePoint);
	bool SpiritualButtonIsClick(int PosX, int PosY, int Width, int Height, CPoint MousePoint);
};