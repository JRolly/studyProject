
// PaintInWindows.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPaintInWindowsApp:
// �йش����ʵ�֣������ PaintInWindows.cpp
//

class CPaintInWindowsApp : public CWinApp
{
public:
	CPaintInWindowsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPaintInWindowsApp theApp;