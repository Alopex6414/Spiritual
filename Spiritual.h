
// Spiritual.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpiritualApp: 
// �йش����ʵ�֣������ Spiritual.cpp
//

class CSpiritualApp : public CWinApp
{
public:
	CSpiritualApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpiritualApp theApp;
