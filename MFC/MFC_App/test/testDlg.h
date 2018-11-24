
// testDlg.h : 头文件
//

#pragma once
#include "MainChild.h"

#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")


// CtestDlg 对话框
class CtestDlg : public CDialogEx
{
// 构造
public:
	CtestDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CtestDlg();
// 对话框数据
	enum { IDD = IDD_Main };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
public:
	HICON m_hIcon;
	CMainChild *pmainChild;
	UINT32 m_nCnt;
	MMRESULT m_TimerID;
	bool m_bHasAdd;
public:
	bool OnStartTimer();
	void OnSotpTimer();
	static void CALLBACK TimerFun(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void PrintCnt();
	void DealSomething();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
