
// ListDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CListDialogApp:
// �йش����ʵ�֣������ ListDialog.cpp
//

class CListDialogApp : public CWinApp
{
public:
	CListDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CListDialogApp theApp;