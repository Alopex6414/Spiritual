#pragma once

#ifndef __COMMON_H_
#define __COMMON_H_

//�û������
#define	USER_SCREENWIDTH	640//�û�������
#define	USER_SCREENHEIGHT	512//�û�����߶�

#define	USER_TIMER0_INTERVAL	10//Window���ڶ�ʱ��
#define	USER_TIMER1_INTERVAL	10//�ػ涨ʱ��
#define	USER_TIMER2_INTERVAL	100//���ȶ�ʱ��
#define	USER_TIMER3_INTERVAL	100//���������ƶ���ʱ��
#define	USER_TIMER4_INTERVAL	10//Window�����л���ʱ��
#define	USER_TIMER5_INTERVAL	10//Window���ñ�����ʱ��

#define	USER_VOLUME_MIN	0//��С����
#define	USER_VOLUME_MAX	1000//�������

//����C���ļ�
#include <mmsystem.h>
#include <ctime>
#include <array>
#include <vector>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string.h>
#include <dwmapi.h>
#include <Digitalv.h>
#include <WinUser.h>
#include <Windows.h>

//����MFC�ļ�
#include "stdafx.h"
#include "afxdialogex.h"

//������Դ�ļ�
#include "resource.h"

//�������ļ�
#pragma comment(lib,"WinMM.lib")
#pragma comment(lib,"dwmapi.lib")

#endif // !__COMMON_H_
