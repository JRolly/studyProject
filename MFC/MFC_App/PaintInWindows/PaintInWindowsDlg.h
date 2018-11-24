
// PaintInWindowsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


#define POINT_COUNT 100

// CPaintInWindowsDlg 对话框
class CPaintInWindowsDlg : public CDialogEx
{
// 构造
public:
	CPaintInWindowsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PAINTINWINDOWS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	int m_nzValues[POINT_COUNT];

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picDraw;

	void DrawWave(CDC *pDC, CRect &rectPicture);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
