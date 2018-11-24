
// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatDlg �Ի���



CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
	, m_strSendData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSendData);
	DDX_Control(pDX, IDC_EDIT_RECV, m_edRecv);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddr);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RECVDATA, &CChatDlg::OnRecvData)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CChatDlg ��Ϣ�������

BOOL CChatDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (!InitSock())
	{
		return FALSE;
	}

	RECVPARAM *pRaramRecv = new RECVPARAM;
	pRaramRecv->sock = m_Sock;
	pRaramRecv->hWnd = m_hWnd;

	HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRaramRecv, 0, NULL);
	//CloseHandle(hThread);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatDlg::OnPaint()
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CChatDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	CString strRecvMsg = (char *)lParam;
	CString strMsgShow;
	m_edRecv.GetWindowText(strMsgShow);
	strMsgShow += "\r\n";
	strMsgShow += strRecvMsg;
	TRACE("OnRecvData:%s\n", strRecvMsg);
	m_edRecv.SetWindowText(strMsgShow);

	return 0;
}



BOOL CChatDlg::InitSock()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return FALSE;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup();
		return FALSE;
	}

	m_Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_Sock)
	{
		AfxMessageBox(_T("�׽��ִ���ʧ��!"));
		return FALSE;
	}

	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(PORT);

	int iRet = bind(m_Sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));
	if (SOCKET_ERROR == iRet)
	{
		AfxMessageBox(_T("���׽���ʧ��!"));
		closesocket(m_Sock);
		return FALSE;
	}

	return TRUE;
}


DWORD WINAPI CChatDlg::RecvProc(LPVOID lpParameter)
{
	char szRecvBuf[MAX_BUF_LEN] = { 0 };
	char szTempBuf[MAX_BUF_LEN] = { 0 };
	int iRecv = 0;

	SOCKET sock = ((RECVPARAM *)lpParameter)->sock;
	HWND hwnd = ((RECVPARAM *)lpParameter)->hWnd;
	delete lpParameter;

	SOCKET rcvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN sockRecvAddr;
	int sockLen = sizeof(SOCKADDR_IN);
	sockRecvAddr.sin_family = AF_INET;
	sockRecvAddr.sin_port = htons(PORT);
	sockRecvAddr.sin_addr.s_addr = inet_addr(INADDR_ANY);

	while (1)
	{
		Sleep(100);
		memset(szRecvBuf, 0, MAX_BUF_LEN);
		memset(szTempBuf, 0, MAX_BUF_LEN);

		iRecv = recvfrom(sock, szRecvBuf, MAX_BUF_LEN, 0, (SOCKADDR *)&sockRecvAddr, &sockLen);
		int iErr = WSAGetLastError();

		if (SOCKET_ERROR == iRecv)
		{
			TRACE("recvfrom fail");
			//AfxMessageBox("recvfrom fail");
			//break;
		}
		sprintf_s(szTempBuf, "%s say: %s", inet_ntoa(sockRecvAddr.sin_addr), szRecvBuf);
		::PostMessage(hwnd, WM_RECVDATA, 100, (LPARAM)szTempBuf);

	}
	return 0;
}


void CChatDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	DWORD dwIP = 0;
	m_IPAddr.GetAddress(dwIP);

	SOCKADDR_IN sockTo;
	sockTo.sin_family = AF_INET;
	sockTo.sin_port = htons(PORT);
	sockTo.sin_addr.S_un.S_addr = dwIP;

	int iRet = sendto(m_Sock, m_strSendData, m_strSendData.GetLength(), 0, (SOCKADDR *)&sockTo, sizeof(SOCKADDR));
	if (SOCKET_ERROR == iRet)
	{
		AfxMessageBox("������Ϣʧ��");
		return;
	}

	m_strSendData = "";
	UpdateData(FALSE);
}
