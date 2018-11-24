
// SerialCommDlg.cpp : ʵ���ļ�


#include "stdafx.h"
#include "SerialComm.h"
#include "SerialCommDlg.h"
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


// CSerialCommDlg �Ի���



//���캯��
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


//��������
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


// CSerialCommDlg ��Ϣ�������

LRESULT CSerialCommDlg::OnWmNotifyProcess(WPARAM wParam, LPARAM lParam)
{

	//UpdateData(FALSE);
	if (m_recvData == "")
	{
		SetDlgItemText(IDC_RECV_DATA_EDIT, "");
		return  0;
	}
	SetDlgItemText(IDC_RECV_DATA_EDIT, m_recvData);
	SetDlgItemText(IDC_STATUS_EDIT, "���ݽ������!");
	return 0;
}


BOOL CSerialCommDlg::OnInitDialog()
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

	//��ѡ�񴮿���������Ͽ�����б���
	addComm();
	//����Ĭ��ѡ��COM1
	m_comm.SetCurSel(0);
	//��ѡ��������������Ͽ�����б���
	addRate();
	//������Ĭ��ѡ��115200
	m_rate.SetCurSel(11);

	int nSel;
	CString strText;
	//���ô��ںų�Ա
	nSel = m_comm.GetCurSel();
	m_comm.GetLBText(nSel, m_strComm);

	//���ò����ʳ�Ա
	nSel = m_rate.GetCurSel();
	m_rate.GetLBText(nSel, strText);
	m_nRate = atoi((const char *)strText);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialCommDlg::OnPaint()
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
HCURSOR CSerialCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ѡ�񴮿���������Ͽ�����б���
void CSerialCommDlg::addComm()
{
	for (int i = 0; i < sizeof(g_strComm)/sizeof(g_strComm[0]); i++)
	{
		m_comm.AddString(g_strComm[i]);
	}
}

//��ѡ��������������Ͽ�����б���
void CSerialCommDlg::addRate()
{
	for (int i = 0; i < sizeof(g_nRate)/sizeof(g_nRate[0]); i++)
	{
		m_rate.AddString(g_nRate[i]);
	}
}


//��ѡ��COM�������
void CSerialCommDlg::OnCbnSelchangeComCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	int nSel;

	//�����Ѵ򿪣��ȹر��Ѵ򿪵Ĵ������޸ģ����޸Ĵ򿪴��ڰ�ťΪ���򿪴��ڡ�
	if (m_bIsOpen)
	{
		Close(m_hCom);
		//�޸İ�ť����
		this->SetDlgItemText(IDC_OPEN_COM_BUTTON, _T("�򿪴���"));
	}
	
	//��ȡ��Ͽ���ѡ�е��б���
	nSel = m_comm.GetCurSel();
	//����ѡ��������ȡѡ�����ַ���
	m_comm.GetLBText(nSel, strText);
	//�����ݴ������
	m_strComm = strText;
}

//��ѡ�еĲ����ʴ������
void CSerialCommDlg::OnCbnSelchangeRateCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText;
	int nSel;
	//��ȡ��Ͽ���ѡ�е��б���
	nSel = m_rate.GetCurSel();
	//����������ȡѡ�����ַ���
	m_rate.GetLBText(nSel, strText);
	//�����ݴ������
	m_nRate = atoi((const char *)((LPCTSTR)strText));

	//�����Ѵ򿪣����������ò�����
	if (m_bIsOpen)
	{
		DCB dcb;
		GetCommState(m_hCom, &dcb);
		dcb.BaudRate = m_nRate;

		if (!SetCommState(m_hCom, &dcb))
		{
			MessageBox(_T("����������ʧ��!"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
		}
	}
}


//�򿪴��ڣ������ô��ڲ���
bool CSerialCommDlg::Open(HANDLE &hCom)
{
	InitializeCriticalSection(&m_cs);

	EnterCriticalSection(&m_cs);

	//�򿪴���
	hCom = CreateFile(m_strComm,	//�򿪵Ĵ���
		GENERIC_READ | GENERIC_WRITE,	//��д
		0,	//��ռ
		NULL,
		OPEN_EXISTING, //���Ѵ��ڶ�������
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	//�첽I/O
		0
		);

	//��ʧ������ʾ����
	if (INVALID_HANDLE_VALUE == hCom)
	{
		//dwErr = GetLastError();	//�������
		MessageBox(_T("���ڴ�ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
		LeaveCriticalSection(&m_cs);
		return FALSE;
	}
	
	//�����¼���������
	SetCommMask(hCom, EV_RXCHAR | EV_TXEMPTY);

	//���OverlappedRead��OverlappedWrite��������Event
	//memset(&m_OverlappedRead1, 0, sizeof(m_OverlappedRead1));
	//memset(&m_OverlappedWrite1, 0, sizeof(m_OverlappedWrite1));
	//m_OverlappedRead1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//m_OverlappedWrite1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	memset(&m_ov, 0, sizeof(m_ov));
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//����Eventʧ��
	//�ر��Ѵ򿪵Ĵ���
	//if (NULL == m_OverlappedRead1.hEvent)
	//{
	//	CloseHandle(m_OverlappedRead1.hEvent);
	//	CloseHandle(hCom);
	//	MessageBox(_T("���ڴ�ʧ�ܣ�Error:Failed to create readEvent!"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
	//	LeaveCriticalSection(&m_cs);
	//	return FALSE;
	//}
	//if (NULL == m_OverlappedWrite1.hEvent)
	//{
	//	CloseHandle(m_OverlappedWrite1.hEvent);
	//	CloseHandle(hCom);
	//	MessageBox(_T("���ڴ�ʧ�ܣ�Error:Failed to create writeEvent!"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
	//	LeaveCriticalSection(&m_cs);
	//	return FALSE;
	//}


	//���ô����������������
	SetupComm(hCom, SENDBUFFSIZE, RECVBUFFSIZE);

	//��ϴ�ɾ����롢���������
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	//���峬ʱ�ṹ������д
	COMMTIMEOUTS ComTimeOuts;
	ComTimeOuts.WriteTotalTimeoutMultiplier = 1000;
	ComTimeOuts.WriteTotalTimeoutConstant = 1000;
	ComTimeOuts.ReadIntervalTimeout = MAXDWORD;
	ComTimeOuts.ReadTotalTimeoutMultiplier = 1000;
	ComTimeOuts.ReadTotalTimeoutConstant = 1000;
	//���ö�д����������ĳ�ʱ
	SetCommTimeouts(hCom, &ComTimeOuts);

	SetCommMask(hCom, EV_RXCHAR | EV_TXEMPTY);

	//�������ݿ��ƿ�ṹ DCB
	DCB dcb;
	//��ȡ����ԭ����������
	GetCommState(hCom, &dcb);

	//���ô��ڲ���
	dcb.BaudRate = m_nRate;	//������
	dcb.fBinary = TRUE;		//�����ƴ���
	dcb.fParity = FALSE;	//������żУ��
	dcb.ByteSize = 8;		//8λ
	dcb.Parity = NOPARITY;	//��żУ�鷽��
	dcb.StopBits = ONESTOPBIT;	//ֹͣλ

	if (!SetCommState(hCom, &dcb))
	{
		CloseHandle(hCom);
		MessageBox(_T("���ڴ�ʧ�ܣ�Error:Failed to set CommState!"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
		LeaveCriticalSection(&m_cs);
		return FALSE;
	}

	//���ñ�־ΪTRUE
	m_bIsOpen = TRUE;

	LeaveCriticalSection(&m_cs);

	//MessageBox(_T("�򿪳ɹ���"));

	return TRUE;
}


//�رմ���
bool CSerialCommDlg::Close(HANDLE &hCom)
{
	//�����Ѿ��򿪣���ر�
	if (INVALID_HANDLE_VALUE != hCom)
	{
		CloseHandle(m_hCom);
		hCom = INVALID_HANDLE_VALUE;

		//����־����ΪFALSE
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


//��������
//BOOL CSerialCommDlg::sendData(HANDLE &hCom)
//{
//	DWORD dwBytesWriten=0, dwErr = -1;
//
//	//�����ݴӿؼ���������
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
//	//��������
//	//����մ��ڷ��ͻ���
//	PurgeComm(m_hCom1, PURGE_TXCLEAR | PURGE_TXABORT);
//
//	//��������ʱ������������̣߳��ѱ�֤�������ݷ�������ٻ��ѽ����߳�
//	//SuspendThread(m_hthread);
//
//	if (!WriteFile(hCom, sendbuf, len, &dwBytesWriten, &m_OverlappedWrite1))
//	{
//		//���ͳ���
//		if (ERROR_IO_PENDING != (dwErr = GetLastError()))
//		{
//			MessageBox(_T("���ݷ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
//			return FALSE;
//		}
//		else
//		{	//I/O����δ��ɣ��ȴ��������
//			if (WAIT_OBJECT_0 == WaitForSingleObject(m_OverlappedWrite1.hEvent, INFINITE))	
//			{	//д������ɣ�����ȷ���ɹ����			
//				if (!GetOverlappedResult(hCom, &m_OverlappedWrite1, &dwBytesWriten, TRUE))
//				{	//д����ʧ��
//					MessageBox(_T("���ݷ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
//					return FALSE;
//				}
//			}
//			else
//			{	//д����ʧ��
//				MessageBox(_T("���ݷ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
//				return FALSE;
//			}	
//		}
//	}
//
//	//������ɣ����ѽ����߳�
//	//ResumeThread(m_hthread);
//
//	return TRUE;
//}


BOOL CSerialCommDlg::sendData(CSerialCommDlg *port)
{
	DWORD dwBytesWriten=0, dwErr = -1;

	//�����ݴӿؼ���������
	UpdateData(TRUE);

	DWORD len = (port->m_sendData).GetLength();

	if (len >SENDBUFFSIZE)
	{
		//MessageBox(_T("���ݳ��Ȳ��ܳ���2048�ֽڣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
		return FALSE;
	}

	char sendbuf[SENDBUFFSIZE] = {0};
	memcpy(sendbuf, (port->m_sendData).GetBuffer(0), (port->m_sendData).GetLength());
	//��������
	//����մ��ڷ��ͻ���
	PurgeComm(port->m_hCom, PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT | PURGE_RXCLEAR);

//	ResetEvent((port->m_ov).hEvent);

	EnterCriticalSection(&m_cs);

	if (!WriteFile(port->m_hCom, sendbuf, len, &dwBytesWriten, &(port->m_ov)))
	{
		//��������
		if (ERROR_IO_PENDING != GetLastError())
		{
			MessageBox(_T("���ݷ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
			LeaveCriticalSection(&(port->m_cs));
			return FALSE;
		}
		else
		{
			//dwErr = WaitForSingleObject(port->m_hCom, 100);
			//switch (dwErr)
			//{
			//	case WAIT_OBJECT_0:	//д������ɣ�����ȷ���ɹ����
					if (!GetOverlappedResult(port->m_hCom, &(port->m_ov), &dwBytesWriten, TRUE))
					{		//�����ǰ�
						MessageBox(_T("���ݷ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
						LeaveCriticalSection(&(port->m_cs));
						return FALSE;
					}
			//		else	//�����ɹ�
			//			break;
			//	case WAIT_TIMEOUT:	//��ʱ,��������
			//		break;
			//	default:	//����ʧ��
			//		MessageBox(_T("���ݷ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
			//		LeaveCriticalSection(&(port->m_cs));
			//		return FALSE;
			//}
		}
	}	// end WriteFile()
	LeaveCriticalSection(&(port->m_cs));
	return TRUE;
}


//��������
BOOL CSerialCommDlg::readData(CSerialCommDlg *port, COMSTAT &comstat, CString &recvBuf)
{
	DWORD dwBytesRead = 0, dwTotalBytesRead = 0; 
	DWORD dwErr = -1;
	DWORD bResult = 0;
	char str[RECVBUFFSIZE] = {0};

	while (1)
	{
		Sleep(1);
		//��ȡ����״̬
		EnterCriticalSection(&port->m_cs);
		bResult	= ClearCommError(port->m_hCom, &dwErr, &comstat);
		LeaveCriticalSection(&port->m_cs);

		//���������Ѿ�������
		if (0 == comstat.cbInQue)
			break;
	
		EnterCriticalSection(&port->m_cs);
		
		if (!ReadFile(port->m_hCom, str, RECVBUFFSIZE, &dwBytesRead, &port->m_ov))
		{
			//��������
			if (ERROR_IO_PENDING != GetLastError())
			{
				MessageBox(_T("���ݽ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
				LeaveCriticalSection(&port->m_cs);
				return FALSE;
			}
			else
			{
				//dwErr = WaitForSingleObject(port->m_hCom, INFINITE);
				//switch (dwErr)
				//{
				//case WAIT_OBJECT_0:	//������ɣ�����ȷ���ɹ����
						if (!GetOverlappedResult(port->m_hCom, &port->m_ov, &dwBytesRead, TRUE))
						{	//����ʧ��
							MessageBox(_T("���ݽ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
							LeaveCriticalSection(&port->m_cs);
							return FALSE;
						}
				//		else	//�����ɹ�
				//			break;
				//	default:
				//		MessageBox(_T("���ݽ���ʧ�ܣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
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



//�򿪴��ڣ������ò���
void CSerialCommDlg::OnBnClickedOpenComButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�����Ѿ��򿪣�������رմ���
	//����ť�����޸�Ϊ���򿪴��ڡ�
	if (m_bIsOpen)
	{	
		//ֹͣ�����߳�
		g_bIsThreadRun = FALSE;
		if (NULL != m_hthread)
		{
			CloseHandle(m_hthread);
		}

		//�رմ���
		Close(m_hCom);

		//�޸İ�ť����
		this->SetDlgItemText(IDC_OPEN_COM_BUTTON, _T("�򿪴���"));
	}
	else	//����δ�򿪣�������򿪴���
			//����ť�����޸�Ϊ���رմ��ڡ�
	{
		//�򿪴���
		if (Open(m_hCom))
		{
			g_bIsThreadRun = TRUE;
			//�����Ѵ򿪣����������߳�
			m_hthread = CreateThread(NULL,	//��ȫ��ΪĬ��
									 0,	//ջ��СĬ��
									 ReadThread,	//�����߳�
									 AfxGetMainWnd(),
									 0,//CREATE_SUSPENDED,	//�̴߳���ʱ����
									 NULL
									 );

			if (!m_hthread)
			{
				MessageBox(_T("�����̴߳���ʧ��"));
				return;
			}

			//�޸İ�ť����
			this->SetDlgItemText(IDC_OPEN_COM_BUTTON, _T("�رմ���"));

			//��ȡ�����ھ�������ڸ��½��ձ༭������
			m_pMainWnd = AfxGetMainWnd();
		}
	}
}


//��������
void CSerialCommDlg::OnBnClickedSendButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����δ��
	if (!m_bIsOpen)
	{
		MessageBox(_T("���ڻ�δ�򿪣����ȴ򿪴����ٷ������ݣ�"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
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

	//��ȡ����������
	CSerialCommDlg *serCom = (CSerialCommDlg *)pParam;  

	//�Ƚ����ջ������
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
			case ERROR_IO_PENDING:	//���ڻ���û������
				break;
			case ERROR_INVALID_PARAMETER:	//�Դ���ERROR_IO_PENDING״̬����������
				break;	
			default:
				MessageBox(_T("WaitCommEvent() Error��"), _T("����ͨѶ����"), MB_ICONERROR | MB_OK);
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


//���ݽ����߳�
DWORD WINAPI ReadThread(LPVOID lpParam)
{
	CSerialCommDlg *sercomm = (CSerialCommDlg *)lpParam;
	sercomm->CommThread(lpParam);
	return 0;
}

