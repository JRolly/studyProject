#pragma once
#include "SubChild.h"

// CChildMain 对话框

class CChildMain : public CDialogEx
{
	DECLARE_DYNAMIC(CChildMain)

public:
	CChildMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChildMain();

// 对话框数据
	enum { IDD = IDD_MainChild };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
