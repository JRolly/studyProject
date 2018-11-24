
#ifndef __CSerialPort_H__
#define	__CSerialPort_H__

#define WM_COMM_RXCHAR (WM_USER + 1)

class CSerialPort
{
public:
	CSerialPort(void);
	~CSerialPort(void);

	//��ʼ������
	bool InitPort(CWnd *pPortOwner,	UINT portnr = 1, UINT nRate = 115200, UINT parity = NOPARITY, UINT databits = 8, UINT stopbits = 1, DWORD dwCommEvent = EV_RXCHAR | EV_TXEMPTY, UINT nSendBuffersize = 1024, UINT nRecvBuffsize = 2048);

	//���ò�����
	bool SetRate(HANDLE &hCom, UINT nRate);

	//��������
	bool SendData(CSerialPort *port);
	void WriteToPort(const char *string);

	//��������
	bool RecvData(CSerialPort *port, COMSTAT &comstat);

	//���ݽ����߳�
	static UINT CommThread(LPVOID pParam);

	//�����������ݽ����߳�
	BOOL StartMonitoring();

	//ֹͣ�������ݽ����߳�
	void StopMonitoring();

	DWORD GetSendBufferSize() const;

	DWORD GetRecvBufferSize() const;

	DCB GetDcb() const;

	DWORD GetCommEvent() const;

protected:
	//���ھ��
	HANDLE m_hCom;

	//���ں�
	UINT m_nPortNr;

	//������
	int m_nRate;

	//�߳̾��
	CWinThread*	m_Thread;
	//�߳�ִ�б�־
	bool m_bThreadAlive;

	//�����ھ��
	CWnd *m_pMainWnd;

	// �������ݻ���
	char *m_szSendBuffer;
	// �������ݻ���
	char *m_szRecvBuffer;
	DWORD m_nSendBufferSize;
	DWORD m_nRecvBufferSize;

	//OVERLAPPED�ṹ
	OVERLAPPED m_ov;
	//DCB
	DCB m_dcb;
	//��ʱ
	COMMTIMEOUTS m_CommTimeOuts;

	//�����¼�
	DWORD m_dwCommEvent;

	//�ٽ���ͬ������
	CRITICAL_SECTION m_cs;
};




#endif	__CSerialPort_H__