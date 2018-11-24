
#ifndef __CSerialPort_H__
#define	__CSerialPort_H__

#define WM_COMM_RXCHAR (WM_USER + 1)

class CSerialPort
{
public:
	CSerialPort(void);
	~CSerialPort(void);

	//初始化串口
	bool InitPort(CWnd *pPortOwner,	UINT portnr = 1, UINT nRate = 115200, UINT parity = NOPARITY, UINT databits = 8, UINT stopbits = 1, DWORD dwCommEvent = EV_RXCHAR | EV_TXEMPTY, UINT nSendBuffersize = 1024, UINT nRecvBuffsize = 2048);

	//设置波特率
	bool SetRate(HANDLE &hCom, UINT nRate);

	//发送数据
	bool SendData(CSerialPort *port);
	void WriteToPort(const char *string);

	//接收数据
	bool RecvData(CSerialPort *port, COMSTAT &comstat);

	//数据接收线程
	static UINT CommThread(LPVOID pParam);

	//启动串口数据接收线程
	BOOL StartMonitoring();

	//停止串口数据接收线程
	void StopMonitoring();

	DWORD GetSendBufferSize() const;

	DWORD GetRecvBufferSize() const;

	DCB GetDcb() const;

	DWORD GetCommEvent() const;

protected:
	//串口句柄
	HANDLE m_hCom;

	//串口号
	UINT m_nPortNr;

	//波特率
	int m_nRate;

	//线程句柄
	CWinThread*	m_Thread;
	//线程执行标志
	bool m_bThreadAlive;

	//主窗口句柄
	CWnd *m_pMainWnd;

	// 发送数据缓冲
	char *m_szSendBuffer;
	// 接收数据缓冲
	char *m_szRecvBuffer;
	DWORD m_nSendBufferSize;
	DWORD m_nRecvBufferSize;

	//OVERLAPPED结构
	OVERLAPPED m_ov;
	//DCB
	DCB m_dcb;
	//超时
	COMMTIMEOUTS m_CommTimeOuts;

	//监听事件
	DWORD m_dwCommEvent;

	//临界区同步对象
	CRITICAL_SECTION m_cs;
};




#endif	__CSerialPort_H__