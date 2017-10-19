#pragma once

enum SpiritualButtonStatus
{
	Status_Up,
	Status_Down,
};//��ť״̬

enum SpiritualButtonPlayVolume
{
	PlayVolume_VolumeMax = 0,//�������
	PlayVolume_VolumeMin = 1,//��С����
	PlayVolume_Max = 2,//(Max)
};//��������

enum SpiritualButtonPlayStatus
{
	PlayStatus_Play = 0,//����
	PlayStatus_Pause = 1,//��ͣ
	PlayStatus_Max = 2,//(Max)
};//����״̬

enum SpiritualButtonPlayMode
{
	PlayMode_Single = 0,//��ѭ��
	PlayMode_Circle = 1,//ȫѭ��
	PlayMode_Order = 2,//˳�򲥷�
	PlayMode_Random = 3,//�������
	PlayMode_Max = 4,//(Max)
};//����ģʽ

class SpiritualButton
{
private:
	bool m_bIsVisiable;//�ؼ��ɼ���
	int m_nPosX;//�ؼ�X����
	int m_nPosY;//�ؼ�Y����
	int m_nWidth;//�ؼ����(����ͼƬ���)
	int m_nHeight;//�ؼ��߶�(����ͼƬ�߶�)
	CImage m_IButtonUp;//�ؼ�ͼƬ(��ȡ����)
	CImage m_IButtonDown;//�ؼ�ͼƬ(ʧȥ����)

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