
// ButtonDialogDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CButtonDialogDlg 对话框
class CButtonDialogDlg : public CDialogEx
{
// 构造
public:
	CButtonDialogDlg(CWnd* pParent = NULL);	// 标准构造函数

	//初始化所有复选框状态，即全部禁用，非全部选中
	void InitAllCheckBoxStatus();

// 对话框数据
	enum { IDD = IDD_BUTTONDIALOG_DIALOG };

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
	// 天涯
	CButton m_check1;
	// 卡饭
	CButton m_check2;
	// 百度
	CButton m_check3;
	// 腾讯
	CButton m_check4;
	// 新浪
	CButton m_check5;
	// 鸡啄米
	CButton m_check6;
	afx_msg void OnBnClickedPortalRadio();
	afx_msg void OnBnClickedForumRadio();
	afx_msg void OnBnClickedBlogRadio();
	afx_msg void OnBnClickedOk();
};
