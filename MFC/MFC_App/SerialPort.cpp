

//串口类实现

#include "stdafx.h"
#include "SerialPort.h"
#include <assert.h>

//构造函数
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


//析构函数
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
// 函数名： init                                                         
// 功能：初始化串口
// 参数：
// pPortOwner [in] 主窗口句柄
// portnr [in] 串口号													
// nRate [in] 波特率
// parity [in] 奇偶校验
// databits [in] 数据位
// stopbits [in] 数据位
// dwCommEvent [in] 串口监听事件
// nBuffersize [in] 写缓冲大小
// return 串口初始化结果，TRUE-成功，FALSE-失败							
/************************************************************************/
bool CSerialPort::InitPort(CWnd *pPortOwner,										//主窗口句柄
					  UINT portnr /* = 1 */,								//串口号
					  UINT nRate /* = 115200 */,							//波特率
					  UINT parity /* = NOPARITY */,							//奇偶校验
					  UINT databits /* = 8 */,								//数据位
					  UINT stopbits /* = 1 */,								//停止位
					  DWORD dwCommEvent /* = EV_RXCHAR | EV_TXEMPTY */,		//串口监听事件
					  UINT nSendBuffersize /* = 1024 */,					//发送缓冲大小
					  UINT nRecvBuffsize /*= 2048*/						//接收缓冲大小
					  )
{
	//assert(portnr > 0 && portnr < 10);
	assert(nRecvBuffsize > nSendBuffersize);

	//如果线程已启动，则先停止
	if (m_bThreadAlive)
	{
		m_bThreadAlive = FALSE;
	}

	//创建Event
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

	//初始化临界区
	InitializeCriticalSection(&m_cs);

	//设置主窗口句柄
	m_pMainWnd = pPortOwner;

	//设置发送和接收缓冲区
	if (NULL != m_szSendBuffer)
		delete [] m_szSendBuffer;
	m_szSendBuffer = new char[nSendBuffersize];
	m_nSendBufferSize = nSendBuffersize;
	if (NULL != m_szRecvBuffer)
		delete [] m_szRecvBuffer;
	m_szRecvBuffer = new char[nRecvBuffsize];
	m_nRecvBufferSize = nRecvBuffsize;

	//进入临界区
	EnterCriticalSection(&m_cs);

	//串口
	m_nPortNr = portnr;
	char *szPort = new char[50];
	sprintf(szPort, "COM%d", portnr);

	if (NULL != m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
	}

	//打开串口
	m_hCom = CreateFile(szPort,							//串口号
						GENERIC_READ | GENERIC_WRITE,	//读写
						0,								//独占
						NULL,
						OPEN_EXISTING,					//打开已存在文件
						FILE_FLAG_OVERLAPPED,			//异步I/O
						0);
	if (INVALID_HANDLE_VALUE == m_hCom)
	{
		delete [] szPort;
		return FALSE;
	}

	//超时设置
	m_CommTimeOuts.ReadIntervalTimeout = 1000;
	m_CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	m_CommTimeOuts.ReadTotalTimeoutMultiplier = 1000;
	m_CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	m_CommTimeOuts.WriteTotalTimeoutMultiplier = 1000;

	if (!SetCommTimeouts(m_hCom, &m_CommTimeOuts))
	{//出错处理
	}

	//DCB设置
	if (!GetCommState(m_hCom, &m_dcb))
	{//出错处理
	}
	m_dcb.BaudRate = nRate;
	m_dcb.Parity = parity;
	m_dcb.ByteSize = databits;
	m_dcb.StopBits = stopbits;

	if (!SetCommState(m_hCom, &m_dcb))
	{//出错处理
	}

	//设置监控事件
	if (!SetCommMask(m_hCom, dwCommEvent))
	{//出错处理
	}

	delete [] szPort;

	//冲洗串口缓冲区
	PurgeComm(m_hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

	//离开临界区
	LeaveCriticalSection(&m_cs);

	return TRUE;
}


/************************************************************************/
// 函数名： SetRate                                                    
// 功能：设置波特率  													
// hCom [in] 串口句柄												
// nRate [in] 波特率													
// return 波特率设置结果，TRUE-成功，FALSE-失败							
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
// 函数名： SendData                                                    
// 功能：发送数据  													    
// port [in][out] 串口对象																												
// return 发送结果，TRUE-成功，FALSE-失败								
/************************************************************************/
bool CSerialPort::SendData(CSerialPort *port)
{
	DWORD dwBytesWriten = 0, dwLength = 0;

	//获取发送数据长度
	dwLength = strlen(port->m_szSendBuffer);

	//进入临界区
	EnterCriticalSection(&port->m_cs);

	port->m_ov.Offset = 0;
	port->m_ov.OffsetHigh = 0;

	//发送数据
	if (!WriteFile(port->m_hCom,				//串口句柄
				   port->m_szSendBuffer,		//数据
				   dwLength,				//数据长度
				   &dwBytesWriten,			//实际发送数据长度
				   &port->m_ov 				//OVERLAPPED结构
				   ))
	{
		if (ERROR_IO_PENDING != GetLastError())
		{	//操作出错,离开临界区
			LeaveCriticalSection(&port->m_cs);
			return FALSE;
		}
		else
		{	//I/O处于Pending状态，等待操作完成
			if (!GetOverlappedResult(port->m_hCom, &port->m_ov, &dwBytesWriten, TRUE))
			{	//操作失败,离开临界区
				LeaveCriticalSection(&port->m_cs);
				return FALSE;
			}
		}
	}

	//操作成功，离开临界区
	LeaveCriticalSection(&port->m_cs);
	return TRUE;
}

/************************************************************************/
// 函数名： WriteToPort                                                    
// 功能：发送数据  													    
// string [in] 发送字符串										
/************************************************************************/
void CSerialPort::WriteToPort(const char* string)
{
	assert(m_hCom != 0);
	memset(m_szSendBuffer, 0, sizeof(m_szSendBuffer));
	strcpy(m_szSendBuffer, string);
	SendData(this);
}





/************************************************************************/
// 函数名： RecvData                                                    
// 功能：接收数据  													    
// port [in][out] 串口对象												
// comstat [in][out] 串口状态							
// return 接收数据结果，TRUE-成功，FALSE-失败									
/************************************************************************/
bool CSerialPort::RecvData(CSerialPort *port, COMSTAT &comstat)
{
	DWORD dwBytesRead = 0;
	DWORD dwErr = 0;
	//char *buf = new char[port->m_nRecvBufferSize];
	//memset(buf, 0, port->m_nRecvBufferSize);
	char rxbuf[256]= {0};

	//循环接收数据
	while (1)
	{
		Sleep(1);

		//读取串口状态
		EnterCriticalSection(&port->m_cs);
		ClearCommError(port->m_hCom, &dwErr, &comstat);
		LeaveCriticalSection(&port->m_cs);

		//串口数据已接收完，退出
		if (0 == comstat.cbInQue)
			break;

		//进入临界区
		EnterCriticalSection(&port->m_cs);

		//接收数据
		if (!ReadFile(port->m_hCom, rxbuf, 512, &dwBytesRead, &port->m_ov))
		{			
			dwErr = GetLastError();
			if (ERROR_IO_PENDING != dwErr)
			{	//操作出错,离开临界区
				//delete [] buf;
				//buf = NULL;
				LeaveCriticalSection(&port->m_cs);
				return FALSE;
			}
			else
			{
				//等待操作完成
				if (!GetOverlappedResult(port->m_hCom, &port->m_ov, &dwBytesRead, TRUE))
				{	//操作出错,离开临界区
					//delete [] buf;
					//buf = NULL;
					LeaveCriticalSection(&port->m_cs);
					return FALSE;
				}
			}
		}
		
		//拼接已接收字符
		//strcat(buf, rxbuf);

		::PostMessage(port->m_pMainWnd->m_hWnd, WM_COMM_RXCHAR, (WPARAM)rxbuf, (LPARAM)port->m_nPortNr);

		//离开临界区
		LeaveCriticalSection(&port->m_cs);
	}	//end while (1)

	//if (NULL != buf)
	//{
	//	if ('\0' != buf[0])
	//	{
	//		//进入临界区
	//		EnterCriticalSection(&port->m_cs);
	//		strcpy(port->m_szRecvBuffer, buf);
	//		::PostMessage(port->m_pMainWnd->m_hWnd, WM_COMM_RXCHAR, (WPARAM)port->m_szRecvBuffer, (LPARAM)port->m_nPortNr);
	//		//delete [] rxbuf;
	//		delete [] buf;
	//		buf = NULL;
	//		//离开临界区
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
// 函数名： CommThread											
// 功能：数据接收线程		 										
// lpParam [in] 线程传入参数，串口对象							
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
		//等待串口事件
		bResult = WaitCommEvent(port->m_hCom, &dwEvtMask, &port->m_ov);
		if (!bResult)
		{	
			dwErr = GetLastError();
			switch(dwErr)
			{
				case ERROR_IO_PENDING:	//串口缓冲区没有数据
					break;
				case ERROR_INVALID_PARAMETER:	//错误87
					break;
				default:
					//错误处理
					break;
			}
		}
		else
		{
			ClearCommError(port->m_hCom, &dwErr, &comstat);
			//串口缓冲区没有数据
			if (0 == comstat.cbInQue)
				continue;
		}

		//串口缓冲区有数据，接收数据
		GetCommMask(port->m_hCom, &dwEvtMask);
		if (dwEvtMask | EV_RXCHAR)
			port->RecvData(port, comstat);

		Sleep(1);
	}

	return 0;
}


/************************************************************************/
// 函数名： StartMonitoring											
// 功能：启动数据接收线程		 																
// return	TRUE-成功，FALSE-失败													
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
// 函数名： StopMonitoring											
// 功能：停止数据接收线程		 																
// return												
/************************************************************************/
void CSerialPort::StopMonitoring()
{
	m_bThreadAlive = FALSE;
}