
// CommLogDlg.h : 头文件
//

#include "SerialPort.h"


#pragma once


// CCommLogDlg 对话框
class CCommLogDlg : public CDialogEx
{
// 构造
public:
	CCommLogDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CCommLogDlg();

// 对话框数据
	enum { IDD = IDD_COMMLOG_DIALOG };

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
	//串口参数
	CSerialPort m_port;
	CString m_strSendData;
	CString m_strRcvData;

	//日志文件参数
	CString m_strLogPath;
	CString m_strSendLog;
	CString m_strRcvLog;
	CStdioFile m_fSendfile;
	CStdioFile m_fRcvFile;
	bool m_bSendFile;
	bool m_bRcvFile;
	
	//获取当前时间，转换为字符串,用于创建文件名
	CString GetTimeToStrName();
	//获取当前时间，转换为字符串,用于写入日志文件
	CString GetTimeToStrLog();

	//写日志
	void WriteLog(CStdioFile &file, const char *strlog);

	afx_msg LRESULT OnCommRecvData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedSendButton();
	afx_msg void OnBnClickedOpenlogButton();
};
