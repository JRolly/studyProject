
// ComboBoxDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComboBoxDialogApp:
// �йش����ʵ�֣������ ComboBoxDialog.cpp
//

class CComboBoxDialogApp : public CWinApp
{
public:
	CComboBoxDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CComboBoxDialogApp theApp;