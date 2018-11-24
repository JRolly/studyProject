
// ComboBoxDialogDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CComboBoxDialogDlg 对话框
class CComboBoxDialogDlg : public CDialogEx
{
// 构造
public:
	CComboBoxDialogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMBOBOXDIALOG_DIALOG };

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
	// 下拉组合框对象
	CComboBox m_comboWeb;
	afx_msg void OnCbnSelchangeWebCombo();
};
