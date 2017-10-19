#pragma once

#ifndef __COMMON_H_
#define __COMMON_H_

//用户定义宏
#define	USER_SCREENWIDTH	640//用户区域宽度
#define	USER_SCREENHEIGHT	512//用户区域高度

#define	USER_TIMER0_INTERVAL	10//Window窗口定时器
#define	USER_TIMER1_INTERVAL	10//重绘定时器
#define	USER_TIMER2_INTERVAL	100//进度定时器
#define	USER_TIMER3_INTERVAL	100//音乐名称移动定时器
#define	USER_TIMER4_INTERVAL	10//Window背景切换定时器
#define	USER_TIMER5_INTERVAL	10//Window设置背景定时器

#define	USER_VOLUME_MIN	0//最小音量
#define	USER_VOLUME_MAX	1000//最大音量

//包含C库文件
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

//包含MFC文件
#include "stdafx.h"
#include "afxdialogex.h"

//包含资源文件
#include "resource.h"

//包含库文件
#pragma comment(lib,"WinMM.lib")
#pragma comment(lib,"dwmapi.lib")

#endif // !__COMMON_H_
