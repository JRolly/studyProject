#pragma once
#include "afxcmn.h"


// CLogList 对话框

class CLogList : public CDialogEx
{
	DECLARE_DYNAMIC(CLogList)

public:
	CLogList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogList();

// 对话框数据
	enum { IDD = IDD_LOG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_loglist;

	afx_msg void OnBnClickedOk();
};
