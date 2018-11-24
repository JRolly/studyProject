
// SerialCommDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define SENDBUFFSIZE	2048
#define RECVBUFFSIZE	4096

#define WM_NOTIFYPROCESS (WM_USER + 100)

//COM选择数组
const CString g_strComm[] = {_T("COM1"), _T("COM2"), _T("COM3"), _T("COM4")
							,_T("COM5"), _T("COM6"), _T("COM7"), _T("COM8")};

//波特率选择数组
const CString g_nRate[] = {_T("300"),  _T("600"),   _T("1200"),  _T("2400") , _T("4800")
						 , _T("9600"), _T("19200"), _T("38400"), _T("43000"), _T("56000") 
						 , _T("57600"), _T("115200")};

// CSerialCommDlg 对话框
class CSerialCommDlg : public CDialogEx
{
// 构造
public:
	CSerialCommDlg(CWnd* pParent = NULL);	// 标准构造函数

	//析构函数
	~CSerialCommDlg();

// 对话框数据
	enum { IDD = IDD_SERIALCOMM_DIALOG };

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
	//接收消息，更新编辑框数据
	afx_msg LRESULT OnWmNotifyProcess(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


public:
	//向选择串口下拉框组合框添加列表项
	void addComm();

	//向选择波特率下拉框组合框添加列表项
	void addRate();

	//打开串口，并配置串口参数
	bool Open(HANDLE &hCom);

	//关闭串口
	bool Close(HANDLE &hCom);
	
	//发送数据
	BOOL sendData(CSerialCommDlg *port);

	//接收数据
	BOOL readData(CSerialCommDlg *port, COMSTAT &comstat, CString &recvBuf);

	//获取m_recvData1
	CString getRecvData() const
	{
		return m_recvData;
	}

	//设置m_recvData
	void setRecvData(CString recvData)
	{
		m_recvData = recvData;
	}

	CWnd* getMainWnd()
	{
		return m_pMainWnd;
	}

	DWORD CommThread(LPVOID pParam);


private:
	// 需要发送的数据
	CString m_sendData;
	// 接收的数据
	CString m_recvData;
	
protected:
	// 选择COM控件对象
	CComboBox m_comm;
	//选中的COM
	CString m_strComm;
	// 选择波特率控件对象
	CComboBox m_rate;
	//选中的波特率
	int m_nRate;

	//打开的串口句柄
	HANDLE m_hCom;

	//OVERLAPPED结构
	OVERLAPPED m_ov;

	//串口打开标志
	bool m_bIsOpen;

	//读取数据线程句柄
	HANDLE m_hthread;

	//主窗口句柄
	CWnd *m_pMainWnd;

	//临界区
	CRITICAL_SECTION m_cs;

public:
	//将选中COM存入变量
	afx_msg void OnCbnSelchangeComCombo();
	//将选中的波特率存入变量
	afx_msg void OnCbnSelchangeRateCombo();
	//打开串口消息处理
	afx_msg void OnBnClickedOpenComButton();
	//发送数据消息处理
	afx_msg void OnBnClickedSendButton();
};


//线程执行标志
static bool g_bIsThreadRun = TRUE;

//接收数据线程
DWORD WINAPI ReadThread(LPVOID lpParam);