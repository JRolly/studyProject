
// ButtonDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CButtonDialogApp:
// �йش����ʵ�֣������ ButtonDialog.cpp
//

class CButtonDialogApp : public CWinApp
{
public:
	CButtonDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CButtonDialogApp theApp;