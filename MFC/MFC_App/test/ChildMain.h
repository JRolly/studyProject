#pragma once
#include "SubChild.h"

// CChildMain �Ի���

class CChildMain : public CDialogEx
{
	DECLARE_DYNAMIC(CChildMain)

public:
	CChildMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChildMain();

// �Ի�������
	enum { IDD = IDD_MainChild };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
