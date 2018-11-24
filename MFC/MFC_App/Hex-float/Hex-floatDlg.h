
// Hex-floatDlg.h : 头文件
//

#pragma once


#include <math.h>


// CHexfloatDlg 对话框
class CHexfloatDlg : public CDialogEx
{
// 构造
public:
	CHexfloatDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HEXFLOAT_DIALOG };

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
	CString m_strHex;
	CString m_strFloat;
	UINT64 HexStr2int(const char* str);
	afx_msg void OnBnClickedHex2float();
	afx_msg void OnBnClickedFloat2hex();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
