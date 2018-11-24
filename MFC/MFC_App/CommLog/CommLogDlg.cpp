
// CommLogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommLog.h"
#include "CommLogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCommLogDlg �Ի���




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


// CCommLogDlg ��Ϣ�������

BOOL CCommLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ������
	if (!m_port.InitPort(this, 1))
	{
		MessageBox("Init Serial Port1 Failed!", MB_OK);
		return FALSE;
	}
	m_port.StartMonitoring();

	//������־�ļ�·��
	char workdir[_MAX_PATH] = {0};
	GetCurrentDirectory(_MAX_PATH, workdir);
	//MessageBox(workdir, MB_OK);
	m_strLogPath += workdir;
	m_strLogPath += "\\log";
	//����·��
	if (!PathFileExists(m_strLogPath))
	{
		if (!CreateDirectory(m_strLogPath, NULL))
		{
			MessageBox("������־�ļ�·��ʧ�ܣ�", MB_OK);
			return FALSE;
		}
	}

	//��xxʱxx��xx��ת��Ϊ64λ�޷�������
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


	//��ȡ��ǰʱ���ַ���������������־�ļ�
	CString strTime = GetTimeToStrName();

	//������־�ļ���
	m_strSendLog = m_strLogPath + "\\" + strTime + "_send.log";
	m_strRcvLog = m_strLogPath + "\\" + strTime + "_rcv.log";

	//������־�ļ�
	if (!m_fSendfile.Open(m_strSendLog, CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::shareDenyNone))
	{
		MessageBox("����������־�ļ�ʧ�ܣ�", MB_OK);
		return FALSE;
	}
	else
		m_bSendFile = TRUE;
	if (!m_fRcvFile.Open(m_strRcvLog, CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::shareDenyNone))
	{
		MessageBox("����������־�ļ�ʧ�ܣ�", MB_OK);
		return FALSE;
	}
	else
		m_bRcvFile = TRUE;


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCommLogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCommLogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ȡ��ǰʱ�䣬ת��Ϊ�ַ���,���ڴ����ļ���
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

//��ȡ��ǰʱ�䣬ת��Ϊ�ַ���,����д����־�ļ�
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


//д��־�ļ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�ؼ����ݲ�����
	GetDlgItemText(IDC_SEND_EDIT, m_strSendData);
	char *strSendData = m_strSendData.GetBuffer(0);
	m_port.WriteToPort(strSendData);	

	//����������д����־,������ǰ����ʱ��
	if (!m_bSendFile)
	{
		if (!m_fSendfile.Open(m_strSendLog, CStdioFile::modeReadWrite | CStdioFile::shareDenyNone))
		{
			MessageBox("д����־������־�ļ�ʧ�ܣ�", MB_OK);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_fSendfile.Close();
	m_bSendFile = FALSE;
	CString strOpen("notepad.exe ");
	strOpen += m_strSendLog;
	WinExec(strOpen, SW_SHOW);
}
