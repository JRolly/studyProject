#pragma once
#include "SubChild.h"

// CMainChild �Ի���

class CMainChild : public CDialogEx
{
	DECLARE_DYNAMIC(CMainChild)

public:
	CMainChild(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainChild();

// �Ի�������
	enum { IDD = IDD_MainChild };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CSubChild *pSubChild;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
