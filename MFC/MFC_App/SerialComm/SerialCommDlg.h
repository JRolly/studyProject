
// SerialCommDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define SENDBUFFSIZE	2048
#define RECVBUFFSIZE	4096

#define WM_NOTIFYPROCESS (WM_USER + 100)

//COMѡ������
const CString g_strComm[] = {_T("COM1"), _T("COM2"), _T("COM3"), _T("COM4")
							,_T("COM5"), _T("COM6"), _T("COM7"), _T("COM8")};

//������ѡ������
const CString g_nRate[] = {_T("300"),  _T("600"),   _T("1200"),  _T("2400") , _T("4800")
						 , _T("9600"), _T("19200"), _T("38400"), _T("43000"), _T("56000") 
						 , _T("57600"), _T("115200")};

// CSerialCommDlg �Ի���
class CSerialCommDlg : public CDialogEx
{
// ����
public:
	CSerialCommDlg(CWnd* pParent = NULL);	// ��׼���캯��

	//��������
	~CSerialCommDlg();

// �Ի�������
	enum { IDD = IDD_SERIALCOMM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//������Ϣ�����±༭������
	afx_msg LRESULT OnWmNotifyProcess(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


public:
	//��ѡ�񴮿���������Ͽ�����б���
	void addComm();

	//��ѡ��������������Ͽ�����б���
	void addRate();

	//�򿪴��ڣ������ô��ڲ���
	bool Open(HANDLE &hCom);

	//�رմ���
	bool Close(HANDLE &hCom);
	
	//��������
	BOOL sendData(CSerialCommDlg *port);

	//��������
	BOOL readData(CSerialCommDlg *port, COMSTAT &comstat, CString &recvBuf);

	//��ȡm_recvData1
	CString getRecvData() const
	{
		return m_recvData;
	}

	//����m_recvData
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
	// ��Ҫ���͵�����
	CString m_sendData;
	// ���յ�����
	CString m_recvData;
	
protected:
	// ѡ��COM�ؼ�����
	CComboBox m_comm;
	//ѡ�е�COM
	CString m_strComm;
	// ѡ�����ʿؼ�����
	CComboBox m_rate;
	//ѡ�еĲ�����
	int m_nRate;

	//�򿪵Ĵ��ھ��
	HANDLE m_hCom;

	//OVERLAPPED�ṹ
	OVERLAPPED m_ov;

	//���ڴ򿪱�־
	bool m_bIsOpen;

	//��ȡ�����߳̾��
	HANDLE m_hthread;

	//�����ھ��
	CWnd *m_pMainWnd;

	//�ٽ���
	CRITICAL_SECTION m_cs;

public:
	//��ѡ��COM�������
	afx_msg void OnCbnSelchangeComCombo();
	//��ѡ�еĲ����ʴ������
	afx_msg void OnCbnSelchangeRateCombo();
	//�򿪴�����Ϣ����
	afx_msg void OnBnClickedOpenComButton();
	//����������Ϣ����
	afx_msg void OnBnClickedSendButton();
};


//�߳�ִ�б�־
static bool g_bIsThreadRun = TRUE;

//���������߳�
DWORD WINAPI ReadThread(LPVOID lpParam);