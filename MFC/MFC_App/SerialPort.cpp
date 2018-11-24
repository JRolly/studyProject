

//������ʵ��

#include "stdafx.h"
#include "SerialPort.h"
#include <assert.h>

//���캯��
CSerialPort::CSerialPort(void)
	: m_hCom(NULL)
	, m_nRate(115200)
	, m_nPortNr(1)
	, m_Thread(NULL)
	, m_bThreadAlive(FALSE)
	, m_szRecvBuffer(NULL)
	, m_szSendBuffer(NULL)
	, m_nSendBufferSize(0)
	, m_nRecvBufferSize(0)
{

}


//��������
CSerialPort::~CSerialPort(void)
{
	m_bThreadAlive = FALSE;
	if(m_Thread)
		m_Thread = NULL;

	delete [] m_szRecvBuffer;
	m_szRecvBuffer = NULL;

	delete [] m_szSendBuffer;
	m_szSendBuffer = NULL;

}

DWORD CSerialPort::GetSendBufferSize() const
{
	return m_nSendBufferSize;
}

DWORD CSerialPort::GetRecvBufferSize() const
{
	return m_nRecvBufferSize;
}

DCB CSerialPort::GetDcb() const
{
	return m_dcb;
}

DWORD CSerialPort::GetCommEvent() const
{
	return m_dwCommEvent;
}


/************************************************************************/
// �������� init                                                         
// ���ܣ���ʼ������
// ������
// pPortOwner [in] �����ھ��
// portnr [in] ���ں�													
// nRate [in] ������
// parity [in] ��żУ��
// databits [in] ����λ
// stopbits [in] ����λ
// dwCommEvent [in] ���ڼ����¼�
// nBuffersize [in] д�����С
// return ���ڳ�ʼ�������TRUE-�ɹ���FALSE-ʧ��							
/************************************************************************/
bool CSerialPort::InitPort(CWnd *pPortOwner,										//�����ھ��
					  UINT portnr /* = 1 */,								//���ں�
					  UINT nRate /* = 115200 */,							//������
					  UINT parity /* = NOPARITY */,							//��żУ��
					  UINT databits /* = 8 */,								//����λ
					  UINT stopbits /* = 1 */,								//ֹͣλ
					  DWORD dwCommEvent /* = EV_RXCHAR | EV_TXEMPTY */,		//���ڼ����¼�
					  UINT nSendBuffersize /* = 1024 */,					//���ͻ����С
					  UINT nRecvBuffsize /*= 2048*/						//���ջ����С
					  )
{
	//assert(portnr > 0 && portnr < 10);
	assert(nRecvBuffsize > nSendBuffersize);

	//����߳�������������ֹͣ
	if (m_bThreadAlive)
	{
		m_bThreadAlive = FALSE;
	}

	//����Event
	//if (INVALID_HANDLE_VALUE != m_ov.hEvent)
	//{
	//	CloseHandle(m_ov.hEvent);
	//}
	memset(&m_ov, 0, sizeof(m_ov));
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == m_ov.hEvent)
	{
		return FALSE;
	}

	//��ʼ���ٽ���
	InitializeCriticalSection(&m_cs);

	//���������ھ��
	m_pMainWnd = pPortOwner;

	//���÷��ͺͽ��ջ�����
	if (NULL != m_szSendBuffer)
		delete [] m_szSendBuffer;
	m_szSendBuffer = new char[nSendBuffersize];
	m_nSendBufferSize = nSendBuffersize;
	if (NULL != m_szRecvBuffer)
		delete [] m_szRecvBuffer;
	m_szRecvBuffer = new char[nRecvBuffsize];
	m_nRecvBufferSize = nRecvBuffsize;

	//�����ٽ���
	EnterCriticalSection(&m_cs);

	//����
	m_nPortNr = portnr;
	char *szPort = new char[50];
	sprintf(szPort, "COM%d", portnr);

	if (NULL != m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
	}

	//�򿪴���
	m_hCom = CreateFile(szPort,							//���ں�
						GENERIC_READ | GENERIC_WRITE,	//��д
						0,								//��ռ
						NULL,
						OPEN_EXISTING,					//���Ѵ����ļ�
						FILE_FLAG_OVERLAPPED,			//�첽I/O
						0);
	if (INVALID_HANDLE_VALUE == m_hCom)
	{
		delete [] szPort;
		return FALSE;
	}

	//��ʱ����
	m_CommTimeOuts.ReadIntervalTimeout = 1000;
	m_CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	m_CommTimeOuts.ReadTotalTimeoutMultiplier = 1000;
	m_CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	m_CommTimeOuts.WriteTotalTimeoutMultiplier = 1000;

	if (!SetCommTimeouts(m_hCom, &m_CommTimeOuts))
	{//������
	}

	//DCB����
	if (!GetCommState(m_hCom, &m_dcb))
	{//������
	}
	m_dcb.BaudRate = nRate;
	m_dcb.Parity = parity;
	m_dcb.ByteSize = databits;
	m_dcb.StopBits = stopbits;

	if (!SetCommState(m_hCom, &m_dcb))
	{//������
	}

	//���ü���¼�
	if (!SetCommMask(m_hCom, dwCommEvent))
	{//������
	}

	delete [] szPort;

	//��ϴ���ڻ�����
	PurgeComm(m_hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

	//�뿪�ٽ���
	LeaveCriticalSection(&m_cs);

	return TRUE;
}


/************************************************************************/
// �������� SetRate                                                    
// ���ܣ����ò�����  													
// hCom [in] ���ھ��												
// nRate [in] ������													
// return ���������ý����TRUE-�ɹ���FALSE-ʧ��							
/************************************************************************/
bool CSerialPort::SetRate(HANDLE &hCom, UINT nRate)
{
	if (NULL != hCom)
	{
		DCB dcb;
		GetCommState(hCom, &dcb);
		dcb.BaudRate = nRate;
		if (SetCommState(hCom, &dcb))
			return TRUE;
	}
	return FALSE;
}


/************************************************************************/
// �������� SendData                                                    
// ���ܣ���������  													    
// port [in][out] ���ڶ���																												
// return ���ͽ����TRUE-�ɹ���FALSE-ʧ��								
/************************************************************************/
bool CSerialPort::SendData(CSerialPort *port)
{
	DWORD dwBytesWriten = 0, dwLength = 0;

	//��ȡ�������ݳ���
	dwLength = strlen(port->m_szSendBuffer);

	//�����ٽ���
	EnterCriticalSection(&port->m_cs);

	port->m_ov.Offset = 0;
	port->m_ov.OffsetHigh = 0;

	//��������
	if (!WriteFile(port->m_hCom,				//���ھ��
				   port->m_szSendBuffer,		//����
				   dwLength,				//���ݳ���
				   &dwBytesWriten,			//ʵ�ʷ������ݳ���
				   &port->m_ov 				//OVERLAPPED�ṹ
				   ))
	{
		if (ERROR_IO_PENDING != GetLastError())
		{	//��������,�뿪�ٽ���
			LeaveCriticalSection(&port->m_cs);
			return FALSE;
		}
		else
		{	//I/O����Pending״̬���ȴ��������
			if (!GetOverlappedResult(port->m_hCom, &port->m_ov, &dwBytesWriten, TRUE))
			{	//����ʧ��,�뿪�ٽ���
				LeaveCriticalSection(&port->m_cs);
				return FALSE;
			}
		}
	}

	//�����ɹ����뿪�ٽ���
	LeaveCriticalSection(&port->m_cs);
	return TRUE;
}

/************************************************************************/
// �������� WriteToPort                                                    
// ���ܣ���������  													    
// string [in] �����ַ���										
/************************************************************************/
void CSerialPort::WriteToPort(const char* string)
{
	assert(m_hCom != 0);
	memset(m_szSendBuffer, 0, sizeof(m_szSendBuffer));
	strcpy(m_szSendBuffer, string);
	SendData(this);
}





/************************************************************************/
// �������� RecvData                                                    
// ���ܣ���������  													    
// port [in][out] ���ڶ���												
// comstat [in][out] ����״̬							
// return �������ݽ����TRUE-�ɹ���FALSE-ʧ��									
/************************************************************************/
bool CSerialPort::RecvData(CSerialPort *port, COMSTAT &comstat)
{
	DWORD dwBytesRead = 0;
	DWORD dwErr = 0;
	//char *buf = new char[port->m_nRecvBufferSize];
	//memset(buf, 0, port->m_nRecvBufferSize);
	char rxbuf[256]= {0};

	//ѭ����������
	while (1)
	{
		Sleep(1);

		//��ȡ����״̬
		EnterCriticalSection(&port->m_cs);
		ClearCommError(port->m_hCom, &dwErr, &comstat);
		LeaveCriticalSection(&port->m_cs);

		//���������ѽ����꣬�˳�
		if (0 == comstat.cbInQue)
			break;

		//�����ٽ���
		EnterCriticalSection(&port->m_cs);

		//��������
		if (!ReadFile(port->m_hCom, rxbuf, 512, &dwBytesRead, &port->m_ov))
		{			
			dwErr = GetLastError();
			if (ERROR_IO_PENDING != dwErr)
			{	//��������,�뿪�ٽ���
				//delete [] buf;
				//buf = NULL;
				LeaveCriticalSection(&port->m_cs);
				return FALSE;
			}
			else
			{
				//�ȴ��������
				if (!GetOverlappedResult(port->m_hCom, &port->m_ov, &dwBytesRead, TRUE))
				{	//��������,�뿪�ٽ���
					//delete [] buf;
					//buf = NULL;
					LeaveCriticalSection(&port->m_cs);
					return FALSE;
				}
			}
		}
		
		//ƴ���ѽ����ַ�
		//strcat(buf, rxbuf);

		::PostMessage(port->m_pMainWnd->m_hWnd, WM_COMM_RXCHAR, (WPARAM)rxbuf, (LPARAM)port->m_nPortNr);

		//�뿪�ٽ���
		LeaveCriticalSection(&port->m_cs);
	}	//end while (1)

	//if (NULL != buf)
	//{
	//	if ('\0' != buf[0])
	//	{
	//		//�����ٽ���
	//		EnterCriticalSection(&port->m_cs);
	//		strcpy(port->m_szRecvBuffer, buf);
	//		::PostMessage(port->m_pMainWnd->m_hWnd, WM_COMM_RXCHAR, (WPARAM)port->m_szRecvBuffer, (LPARAM)port->m_nPortNr);
	//		//delete [] rxbuf;
	//		delete [] buf;
	//		buf = NULL;
	//		//�뿪�ٽ���
	//		LeaveCriticalSection(&port->m_cs);
	//	}
	//	else
	//	{
	//		delete [] buf;
	//		buf = NULL;
	//	}
	//}

	return FALSE;
}


/************************************************************************/
// �������� CommThread											
// ���ܣ����ݽ����߳�		 										
// lpParam [in] �̴߳�����������ڶ���							
// return														
/************************************************************************/
UINT CSerialPort::CommThread(LPVOID pParam)
{
	DWORD dwErr = -1;
	DWORD dwEvtMask = 0;
	COMSTAT comstat = {0};
	BOOL bResult = TRUE;

	CSerialPort *port = (CSerialPort *)pParam;

	if (port->m_hCom)
		PurgeComm(port->m_hCom, PURGE_RXABORT | PURGE_RXCLEAR |PURGE_TXABORT |PURGE_TXCLEAR);

	while (port->m_bThreadAlive)
	{
		//�ȴ������¼�
		bResult = WaitCommEvent(port->m_hCom, &dwEvtMask, &port->m_ov);
		if (!bResult)
		{	
			dwErr = GetLastError();
			switch(dwErr)
			{
				case ERROR_IO_PENDING:	//���ڻ�����û������
					break;
				case ERROR_INVALID_PARAMETER:	//����87
					break;
				default:
					//������
					break;
			}
		}
		else
		{
			ClearCommError(port->m_hCom, &dwErr, &comstat);
			//���ڻ�����û������
			if (0 == comstat.cbInQue)
				continue;
		}

		//���ڻ����������ݣ���������
		GetCommMask(port->m_hCom, &dwEvtMask);
		if (dwEvtMask | EV_RXCHAR)
			port->RecvData(port, comstat);

		Sleep(1);
	}

	return 0;
}


/************************************************************************/
// �������� StartMonitoring											
// ���ܣ��������ݽ����߳�		 																
// return	TRUE-�ɹ���FALSE-ʧ��													
/************************************************************************/
BOOL CSerialPort::StartMonitoring()
{
	m_bThreadAlive = TRUE;
	m_Thread = AfxBeginThread(CommThread, this);
	if (!m_Thread)
		return FALSE;
	return TRUE;
}


/************************************************************************/
// �������� StopMonitoring											
// ���ܣ�ֹͣ���ݽ����߳�		 																
// return												
/************************************************************************/
void CSerialPort::StopMonitoring()
{
	m_bThreadAlive = FALSE;
}