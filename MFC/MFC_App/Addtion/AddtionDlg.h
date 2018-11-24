
// AddtionDlg.h : 头文件
//

#pragma once

#include "TipDialog.h"

// CAddtionDlg 对话框
class CAddtionDlg : public CDialogEx
{
// 构造
public:
	CAddtionDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CAddtionDlg();	//析构函数

// 对话框数据
	enum { IDD = IDD_ADDTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedSummandStatic();
	afx_msg void OnEnChangeSummandEdit();
	// 被加数
	double m_editSumand;
	// 加数
	double m_editAddend;
	// 和
	double m_editSum;
	afx_msg void OnClickedAddButton();

private:
	CTipDialog *m_tipDlg;	//提示框指针对象
public:
	afx_msg void OnBnClickedInstruceButton();
};
