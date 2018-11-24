
// CommLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommLog.h"
#include "CommLogDlg.h"
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


// CCommLogDlg 对话框




CCommLogDlg::CCommLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommLogDlg::IDD, pParent)
	, m_strSendData(_T(""))
	, m_strRcvData(_T(""))
	, m_bSendFile(FALSE)
	, m_bRcvFile(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCommLogDlg::~CCommLogDlg()
{
	if (m_bSendFile)
		m_fSendfile.Close();
	if (m_bRcvFile)
		m_fRcvFile.Close();
}

void CCommLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEND_EDIT, m_strSendData);
	DDX_Text(pDX, IDC_RCV_EDIT, m_strRcvData);
}

BEGIN_MESSAGE_MAP(CCommLogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CCommLogDlg::OnBnClickedSendButton)
	ON_BN_CLICKED(IDC_OPENLOG_BUTTON, &CCommLogDlg::OnBnClickedOpenlogButton)
	ON_MESSAGE(WM_COMM_RXCHAR, &CCommLogDlg::OnCommRecvData)
END_MESSAGE_MAP()


// CCommLogDlg 消息处理程序

BOOL CCommLogDlg::OnInitDialog()
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

	//初始化串口
	if (!m_port.InitPort(this, 1))
	{
		MessageBox("Init Serial Port1 Failed!", MB_OK);
		return FALSE;
	}
	m_port.StartMonitoring();

	//设置日志文件路径
	char workdir[_MAX_PATH] = {0};
	GetCurrentDirectory(_MAX_PATH, workdir);
	//MessageBox(workdir, MB_OK);
	m_strLogPath += workdir;
	m_strLogPath += "\\log";
	//创建路径
	if (!PathFileExists(m_strLogPath))
	{
		if (!CreateDirectory(m_strLogPath, NULL))
		{
			MessageBox("创建日志文件路径失败！", MB_OK);
			return FALSE;
		}
	}

	//将xx时xx分xx秒转换为64位无符号整数
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	CTime time(/*curTime.wYear, curTime.wMonth, curTime.wDay, */curTime.wHour, curTime.wMinute, curTime.wSecond);
	__time64_t t64 = time.GetTime();
	//struct tm tmTime;
	//tmTime.tm_year = curTime.wYear - 1900;
	//tmTime.tm_mon = curTime.wMonth;
	//tmTime.tm_mday = curTime.wDay;
	//tmTime.tm_hour = curTime.wHour;
	//tmTime.tm_min = curTime.wMinute;
	//tmTime.tm_sec = curTime.wSecond;
	//__time64_t tm64 = _mktime64(&tmTime); 

	CString stringtime;
	stringtime.Format("%02d/%02d/%02d", time.GetHour(), time.GetMinute(), time.GetSecond());


	//获取当前时间字符串，用于命名日志文件
	CString strTime = GetTimeToStrName();

	//设置日志文件名
	m_strSendLog = m_strLogPath + "\\" + strTime + "_send.log";
	m_strRcvLog = m_strLogPath + "\\" + strTime + "_rcv.log";

	//创建日志文件
	if (!m_fSendfile.Open(m_strSendLog, CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::shareDenyNone))
	{
		MessageBox("创建发送日志文件失败！", MB_OK);
		return FALSE;
	}
	else
		m_bSendFile = TRUE;
	if (!m_fRcvFile.Open(m_strRcvLog, CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::shareDenyNone))
	{
		MessageBox("创建接收日志文件失败！", MB_OK);
		return FALSE;
	}
	else
		m_bRcvFile = TRUE;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCommLogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCommLogDlg::OnPaint()
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
HCURSOR CCommLogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//获取当前时间，转换为字符串,用于创建文件名
CString CCommLogDlg::GetTimeToStrName()
{
	CString strTime;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	strTime.Format("%4d%02d%02d%02d%02d%02d", 
		systime.wYear, systime.wMonth, systime.wDay, 
		systime.wHour, systime.wMinute, systime.wSecond);
	return strTime;
}

//获取当前时间，转换为字符串,用于写入日志文件
CString CCommLogDlg::GetTimeToStrLog()
{
	CString strTime;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	strTime.Format("%4d/%02d/%02d %02d:%02d:%02d", 
		systime.wYear, systime.wMonth, systime.wDay, 
		systime.wHour, systime.wMinute, systime.wSecond);
	return strTime;
}


//写日志文件
void CCommLogDlg::WriteLog(CStdioFile &file, const char *strlog)
{
	file.WriteString(strlog);
	file.WriteString("\r\n");
}

LRESULT CCommLogDlg::OnCommRecvData(WPARAM wParam, LPARAM lParam)
{
	CString str = (LPCTSTR)wParam;
	SetDlgItemText(IDC_RCV_EDIT, str);
	return 0;
}

void CCommLogDlg::OnBnClickedSendButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件数据并发送
	GetDlgItemText(IDC_SEND_EDIT, m_strSendData);
	char *strSendData = m_strSendData.GetBuffer(0);
	m_port.WriteToPort(strSendData);	

	//将发送数据写入日志,包括当前发送时间
	if (!m_bSendFile)
	{
		if (!m_fSendfile.Open(m_strSendLog, CStdioFile::modeReadWrite | CStdioFile::shareDenyNone))
		{
			MessageBox("写入日志：打开日志文件失败！", MB_OK);
			return;
		}
		m_fSendfile.SeekToEnd();
		m_bSendFile = TRUE;
	}
	CString strlog = GetTimeToStrLog() + "    " + m_strSendData;
	WriteLog(m_fSendfile, strlog);
}

void CCommLogDlg::OnBnClickedOpenlogButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_fSendfile.Close();
	m_bSendFile = FALSE;
	CString strOpen("notepad.exe ");
	strOpen += m_strSendLog;
	WinExec(strOpen, SW_SHOW);
}
