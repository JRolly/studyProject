
// SerialCommDlg.cpp : 实现文件


#include "stdafx.h"
#include "SerialComm.h"
#include "SerialCommDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSerialCommDlg 对话框



//构造函数
CSerialCommDlg::CSerialCommDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialCommDlg::IDD, pParent)
	, m_sendData(_T(""))
	, m_recvData(_T(""))
	, m_strComm(_T("COM1"))
	, m_nRate(115200)
	, m_hCom(NULL)
	, m_bIsOpen(FALSE)
	, m_hthread(NULL)
	, m_pMainWnd(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


//析构函数
CSerialCommDlg::~CSerialCommDlg()
{
}


void CSerialCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEND_DATA_EDIT, m_sendData);
	DDX_Text(pDX, IDC_RECV_DATA_EDIT, m_recvData);
	DDX_Control(pDX, IDC_COM_COMBO, m_comm);
	DDX_Control(pDX, IDC_RATE_COMBO, m_rate);
	DDV_MaxChars(pDX, m_sendData, 2048);
}

BEGIN_MESSAGE_MAP(CSerialCommDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COM_COMBO, &CSerialCommDlg::OnCbnSelchangeComCombo)
	ON_CBN_SELCHANGE(IDC_RATE_COMBO, &CSerialCommDlg::OnCbnSelchangeRateCombo)
	ON_BN_CLICKED(IDC_OPEN_COM_BUTTON, &CSerialCommDlg::OnBnClickedOpenComButton)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CSerialCommDlg::OnBnClickedSendButton)
	ON_MESSAGE(WM_NOTIFYPROCESS, OnWmNotifyProcess)
END_MESSAGE_MAP()


// CSerialCommDlg 消息处理程序

LRESULT CSerialCommDlg::OnWmNotifyProcess(WPARAM wParam, LPARAM lParam)
{

	//UpdateData(FALSE);
	if (m_recvData == "")
	{
		SetDlgItemText(IDC_RECV_DATA_EDIT, "");
		return  0;
	}
	SetDlgItemText(IDC_RECV_DATA_EDIT, m_recvData);
	SetDlgItemText(IDC_STATUS_EDIT, "数据接收完成!");
	return 0;
}


BOOL CSerialCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//向选择串口下拉框组合框添加列表项
	addComm();
	//窗口默认选择COM1
	m_comm.SetCurSel(0);
	//向选择波特率下拉框组合框添加列表项
	addRate();
	//波特率默认选择115200
	m_rate.SetCurSel(11);

	int nSel;
	CString strText;
	//设置串口号成员
	nSel = m_comm.GetCurSel();
	m_comm.GetLBText(nSel, m_strComm);

	//设置波特率成员
	nSel = m_rate.GetCurSel();
	m_rate.GetLBText(nSel, strText);
	m_nRate = atoi((const char *)strText);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSerialCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSerialCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSerialCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//向选择串口下拉框组合框添加列表项
void CSerialCommDlg::addComm()
{
	for (int i = 0; i < sizeof(g_strComm)/sizeof(g_strComm[0]); i++)
	{
		m_comm.AddString(g_strComm[i]);
	}
}

//向选择波特率下拉框组合框添加列表项
void CSerialCommDlg::addRate()
{
	for (int i = 0; i < sizeof(g_nRate)/sizeof(g_nRate[0]); i++)
	{
		m_rate.AddString(g_nRate[i]);
	}
}


//将选中COM存入变量
void CSerialCommDlg::OnCbnSelchangeComCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	int nSel;

	//串口已打开，先关闭已打开的串口再修改，并修改打开串口按钮为“打开串口”
	if (m_bIsOpen)
	{
		Close(m_hCom);
		//修改按钮名字
		this->SetDlgItemText(IDC_OPEN_COM_BUTTON, _T("打开串口"));
	}
	
	//获取组合框中选中的列表项
	nSel = m_comm.GetCurSel();
	//根据选中索引获取选中项字符串
	m_comm.GetLBText(nSel, strText);
	//将数据存入变量
	m_strComm = strText;
}

//将选中的波特率存入变量
void CSerialCommDlg::OnCbnSelchangeRateCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	int nSel;
	//获取组合框中选中的列表项
	nSel = m_rate.GetCurSel();
	//根据索引获取选中项字符串
	m_rate.GetLBText(nSel, strText);
	//将数据存入变量
	m_nRate = atoi((const char *)((LPCTSTR)strText));

	//串口已打开，则重新配置波特率
	if (m_bIsOpen)
	{
		DCB dcb;
		GetCommState(m_hCom, &dcb);
		dcb.BaudRate = m_nRate;

		if (!SetCommState(m_hCom, &dcb))
		{
			MessageBox(_T("波特率设置失败!"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
		}
	}
}


//打开串口，并配置串口参数
bool CSerialCommDlg::Open(HANDLE &hCom)
{
	InitializeCriticalSection(&m_cs);

	EnterCriticalSection(&m_cs);

	//打开串口
	hCom = CreateFile(m_strComm,	//打开的串口
		GENERIC_READ | GENERIC_WRITE,	//读写
		0,	//独占
		NULL,
		OPEN_EXISTING, //打开已存在而不创建
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	//异步I/O
		0
		);

	//打开失败则提示错误
	if (INVALID_HANDLE_VALUE == hCom)
	{
		//dwErr = GetLastError();	//处理错误
		MessageBox(_T("串口打开失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
		LeaveCriticalSection(&m_cs);
		return FALSE;
	}
	
	//设置事件驱动类型
	SetCommMask(hCom, EV_RXCHAR | EV_TXEMPTY);

	//清空OverlappedRead和OverlappedWrite，并创建Event
	//memset(&m_OverlappedRead1, 0, sizeof(m_OverlappedRead1));
	//memset(&m_OverlappedWrite1, 0, sizeof(m_OverlappedWrite1));
	//m_OverlappedRead1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//m_OverlappedWrite1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	memset(&m_ov, 0, sizeof(m_ov));
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//创建Event失败
	//关闭已打开的串口
	//if (NULL == m_OverlappedRead1.hEvent)
	//{
	//	CloseHandle(m_OverlappedRead1.hEvent);
	//	CloseHandle(hCom);
	//	MessageBox(_T("串口打开失败！Error:Failed to create readEvent!"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
	//	LeaveCriticalSection(&m_cs);
	//	return FALSE;
	//}
	//if (NULL == m_OverlappedWrite1.hEvent)
	//{
	//	CloseHandle(m_OverlappedWrite1.hEvent);
	//	CloseHandle(hCom);
	//	MessageBox(_T("串口打开失败！Error:Failed to create writeEvent!"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
	//	LeaveCriticalSection(&m_cs);
	//	return FALSE;
	//}


	//设置串口输入输出缓冲区
	SetupComm(hCom, SENDBUFFSIZE, RECVBUFFSIZE);

	//清洗干净输入、输出缓冲区
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	//定义超时结构，并填写
	COMMTIMEOUTS ComTimeOuts;
	ComTimeOuts.WriteTotalTimeoutMultiplier = 1000;
	ComTimeOuts.WriteTotalTimeoutConstant = 1000;
	ComTimeOuts.ReadIntervalTimeout = MAXDWORD;
	ComTimeOuts.ReadTotalTimeoutMultiplier = 1000;
	ComTimeOuts.ReadTotalTimeoutConstant = 1000;
	//设置读写操作所允许的超时
	SetCommTimeouts(hCom, &ComTimeOuts);

	SetCommMask(hCom, EV_RXCHAR | EV_TXEMPTY);

	//定义数据控制块结构 DCB
	DCB dcb;
	//读取串口原来参数设置
	GetCommState(hCom, &dcb);

	//配置串口参数
	dcb.BaudRate = m_nRate;	//波特率
	dcb.fBinary = TRUE;		//二进制传输
	dcb.fParity = FALSE;	//不做奇偶校验
	dcb.ByteSize = 8;		//8位
	dcb.Parity = NOPARITY;	//奇偶校验方法
	dcb.StopBits = ONESTOPBIT;	//停止位

	if (!SetCommState(hCom, &dcb))
	{
		CloseHandle(hCom);
		MessageBox(_T("串口打开失败！Error:Failed to set CommState!"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
		LeaveCriticalSection(&m_cs);
		return FALSE;
	}

	//设置标志为TRUE
	m_bIsOpen = TRUE;

	LeaveCriticalSection(&m_cs);

	//MessageBox(_T("打开成功！"));

	return TRUE;
}


//关闭串口
bool CSerialCommDlg::Close(HANDLE &hCom)
{
	//串口已经打开，则关闭
	if (INVALID_HANDLE_VALUE != hCom)
	{
		CloseHandle(m_hCom);
		hCom = INVALID_HANDLE_VALUE;

		//将标志设置为FALSE
		m_bIsOpen = FALSE;
	}

	//if (NULL != m_OverlappedRead1.hEvent)
	//	CloseHandle(m_OverlappedRead1.hEvent);
	//if (NULL != m_OverlappedWrite1.hEvent)
	//	CloseHandle(m_OverlappedWrite1.hEvent);
	if (NULL != m_ov.hEvent)
		CloseHandle(m_ov.hEvent);
	return TRUE;
}


//发送数据
//BOOL CSerialCommDlg::sendData(HANDLE &hCom)
//{
//	DWORD dwBytesWriten=0, dwErr = -1;
//
//	//将数据从控件传给变量
//	UpdateData(TRUE);
//
//	DWORD len = m_sendData1.GetLength();
//
//	if (len >SENDBUFFSIZE)
//	{
//		return FALSE;
//	}
//
//	char sendbuf[SENDBUFFSIZE] = {0};
//	memcpy(sendbuf, m_sendData1.GetBuffer(0), m_sendData1.GetLength());
//	//发送数据
//	//先清空串口发送缓冲
//	PurgeComm(m_hCom1, PURGE_TXCLEAR | PURGE_TXABORT);
//
//	//发送数据时挂起接收数据线程，已保证所有数据发送完成再唤醒接收线程
//	//SuspendThread(m_hthread);
//
//	if (!WriteFile(hCom, sendbuf, len, &dwBytesWriten, &m_OverlappedWrite1))
//	{
//		//发送出错
//		if (ERROR_IO_PENDING != (dwErr = GetLastError()))
//		{
//			MessageBox(_T("数据发送失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
//			return FALSE;
//		}
//		else
//		{	//I/O操作未完成，等待操作完成
//			if (WAIT_OBJECT_0 == WaitForSingleObject(m_OverlappedWrite1.hEvent, INFINITE))	
//			{	//写操作完成，但不确定成功与否			
//				if (!GetOverlappedResult(hCom, &m_OverlappedWrite1, &dwBytesWriten, TRUE))
//				{	//写操作失败
//					MessageBox(_T("数据发送失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
//					return FALSE;
//				}
//			}
//			else
//			{	//写操作失败
//				MessageBox(_T("数据发送失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
//				return FALSE;
//			}	
//		}
//	}
//
//	//发送完成，唤醒接收线程
//	//ResumeThread(m_hthread);
//
//	return TRUE;
//}


BOOL CSerialCommDlg::sendData(CSerialCommDlg *port)
{
	DWORD dwBytesWriten=0, dwErr = -1;

	//将数据从控件传给变量
	UpdateData(TRUE);

	DWORD len = (port->m_sendData).GetLength();

	if (len >SENDBUFFSIZE)
	{
		//MessageBox(_T("数据长度不能超过2048字节！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
		return FALSE;
	}

	char sendbuf[SENDBUFFSIZE] = {0};
	memcpy(sendbuf, (port->m_sendData).GetBuffer(0), (port->m_sendData).GetLength());
	//发送数据
	//先清空串口发送缓冲
	PurgeComm(port->m_hCom, PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT | PURGE_RXCLEAR);

//	ResetEvent((port->m_ov).hEvent);

	EnterCriticalSection(&m_cs);

	if (!WriteFile(port->m_hCom, sendbuf, len, &dwBytesWriten, &(port->m_ov)))
	{
		//操作出错
		if (ERROR_IO_PENDING != GetLastError())
		{
			MessageBox(_T("数据发送失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
			LeaveCriticalSection(&(port->m_cs));
			return FALSE;
		}
		else
		{
			//dwErr = WaitForSingleObject(port->m_hCom, 100);
			//switch (dwErr)
			//{
			//	case WAIT_OBJECT_0:	//写操作完成，但不确定成功与否
					if (!GetOverlappedResult(port->m_hCom, &(port->m_ov), &dwBytesWriten, TRUE))
					{		//操作是吧
						MessageBox(_T("数据发送失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
						LeaveCriticalSection(&(port->m_cs));
						return FALSE;
					}
			//		else	//操作成功
			//			break;
			//	case WAIT_TIMEOUT:	//超时,不作处理
			//		break;
			//	default:	//操作失败
			//		MessageBox(_T("数据发送失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
			//		LeaveCriticalSection(&(port->m_cs));
			//		return FALSE;
			//}
		}
	}	// end WriteFile()
	LeaveCriticalSection(&(port->m_cs));
	return TRUE;
}


//接收数据
BOOL CSerialCommDlg::readData(CSerialCommDlg *port, COMSTAT &comstat, CString &recvBuf)
{
	DWORD dwBytesRead = 0, dwTotalBytesRead = 0; 
	DWORD dwErr = -1;
	DWORD bResult = 0;
	char str[RECVBUFFSIZE] = {0};

	while (1)
	{
		Sleep(1);
		//获取串口状态
		EnterCriticalSection(&port->m_cs);
		bResult	= ClearCommError(port->m_hCom, &dwErr, &comstat);
		LeaveCriticalSection(&port->m_cs);

		//串口数据已经接收完
		if (0 == comstat.cbInQue)
			break;
	
		EnterCriticalSection(&port->m_cs);
		
		if (!ReadFile(port->m_hCom, str, RECVBUFFSIZE, &dwBytesRead, &port->m_ov))
		{
			//操作错误
			if (ERROR_IO_PENDING != GetLastError())
			{
				MessageBox(_T("数据接收失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
				LeaveCriticalSection(&port->m_cs);
				return FALSE;
			}
			else
			{
				//dwErr = WaitForSingleObject(port->m_hCom, INFINITE);
				//switch (dwErr)
				//{
				//case WAIT_OBJECT_0:	//操作完成，但不确定成功与否
						if (!GetOverlappedResult(port->m_hCom, &port->m_ov, &dwBytesRead, TRUE))
						{	//操作失败
							MessageBox(_T("数据接收失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
							LeaveCriticalSection(&port->m_cs);
							return FALSE;
						}
				//		else	//操作成功
				//			break;
				//	default:
				//		MessageBox(_T("数据接收失败！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
				//		LeaveCriticalSection(&port->m_cs);
				//		return FALSE;
				//}
			}
		}	// end ReadFile
		
		port->m_recvData = str;
		::PostMessage(port->m_pMainWnd->m_hWnd, WM_NOTIFYPROCESS, (WPARAM)str, 0);

		//recvBuf += str;
		LeaveCriticalSection(&port->m_cs);
	}	//end while (1)	
	
	//if ("" != recvBuf)
	//{
	//	EnterCriticalSection(&port->m_cs);
	//	port->m_recvData = recvBuf;
	//	::PostMessage(port->m_pMainWnd->m_hWnd, WM_NOTIFYPROCESS, 0, 0);
	//	LeaveCriticalSection(&port->m_cs);
	//	return TRUE;
	//}
	return FALSE;
}



//打开串口，并配置参数
void CSerialCommDlg::OnBnClickedOpenComButton()
{
	// TODO: 在此添加控件通知处理程序代码

	//串口已经打开，点击将关闭串口
	//将按钮名字修改为“打开串口”
	if (m_bIsOpen)
	{	
		//停止接收线程
		g_bIsThreadRun = FALSE;
		if (NULL != m_hthread)
		{
			CloseHandle(m_hthread);
		}

		//关闭串口
		Close(m_hCom);

		//修改按钮名字
		this->SetDlgItemText(IDC_OPEN_COM_BUTTON, _T("打开串口"));
	}
	else	//串口未打开，点击将打开串口
			//将按钮名字修改为“关闭串口”
	{
		//打开串口
		if (Open(m_hCom))
		{
			g_bIsThreadRun = TRUE;
			//串口已打开，创建接收线程
			m_hthread = CreateThread(NULL,	//安全性为默认
									 0,	//栈大小默认
									 ReadThread,	//启动线程
									 AfxGetMainWnd(),
									 0,//CREATE_SUSPENDED,	//线程创建时挂起
									 NULL
									 );

			if (!m_hthread)
			{
				MessageBox(_T("接收线程创建失败"));
				return;
			}

			//修改按钮名字
			this->SetDlgItemText(IDC_OPEN_COM_BUTTON, _T("关闭串口"));

			//获取主窗口句柄，用于更新接收编辑框内容
			m_pMainWnd = AfxGetMainWnd();
		}
	}
}


//发送数据
void CSerialCommDlg::OnBnClickedSendButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//串口未打开
	if (!m_bIsOpen)
	{
		MessageBox(_T("串口还未打开！请先打开串口再发送数据！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
		return;
	}

	sendData((CSerialCommDlg *)AfxGetMainWnd());
}


DWORD CSerialCommDlg::CommThread(LPVOID pParam)
{
	DWORD dwErr = -1;
	DWORD dwEvtMask = 0;
	COMSTAT comstat = {0};
	BOOL bResult = TRUE;
	DWORD CommEvent = 0;
	CString recvBuf = "";
	CString str = "";

	//获取主窗口类句柄
	CSerialCommDlg *serCom = (CSerialCommDlg *)pParam;  

	//先将接收缓冲清空
	serCom->m_recvData = "";

	PurgeComm(serCom->m_hCom, PURGE_RXABORT | PURGE_RXCLEAR |PURGE_TXABORT |PURGE_TXCLEAR);

	while (g_bIsThreadRun)
	{
		bResult = WaitCommEvent(serCom->m_hCom, &dwEvtMask, &serCom->m_ov);
		if (!bResult)
		{	
			dwErr = GetLastError();
			switch (dwErr)
			{
			case ERROR_IO_PENDING:	//串口缓冲没有数据
				break;
			case ERROR_INVALID_PARAMETER:	//仍处于ERROR_IO_PENDING状态，不作处理
				break;	
			default:
				MessageBox(_T("WaitCommEvent() Error！"), _T("串口通讯助手"), MB_ICONERROR | MB_OK);
				break;
			}
		}
		else
		{
			bResult = ClearCommError(serCom->m_hCom, &dwErr, &comstat);
			if (0 == comstat.cbInQue)
			{
				Sleep(1);
				continue;
			}
		}

		GetCommMask(serCom->m_hCom, &CommEvent);
		if (CommEvent | EV_RXCHAR)
		{
			bResult = serCom->readData(serCom, comstat, recvBuf);
			if (bResult)
			{
				recvBuf = "";
				//::PostMessage(serCom->getMainWnd()->m_hWnd, WM_NOTIFYPROCESS, 0, 0);
			}
		}	
		Sleep(1);
	}	// end while (g_bIsThreadRun)

	return 0;
}


//数据接收线程
DWORD WINAPI ReadThread(LPVOID lpParam)
{
	CSerialCommDlg *sercomm = (CSerialCommDlg *)lpParam;
	sercomm->CommThread(lpParam);
	return 0;
}

