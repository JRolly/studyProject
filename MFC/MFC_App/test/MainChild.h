#pragma once
#include "SubChild.h"

// CMainChild 对话框

class CMainChild : public CDialogEx
{
	DECLARE_DYNAMIC(CMainChild)

public:
	CMainChild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainChild();

// 对话框数据
	enum { IDD = IDD_MainChild };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CSubChild *pSubChild;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
