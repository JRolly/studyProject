
// CommLogDlg.h : ͷ�ļ�
//

#include "SerialPort.h"


#pragma once


// CCommLogDlg �Ի���
class CCommLogDlg : public CDialogEx
{
// ����
public:
	CCommLogDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCommLogDlg();

// �Ի�������
	enum { IDD = IDD_COMMLOG_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	//���ڲ���
	CSerialPort m_port;
	CString m_strSendData;
	CString m_strRcvData;

	//��־�ļ�����
	CString m_strLogPath;
	CString m_strSendLog;
	CString m_strRcvLog;
	CStdioFile m_fSendfile;
	CStdioFile m_fRcvFile;
	bool m_bSendFile;
	bool m_bRcvFile;
	
	//��ȡ��ǰʱ�䣬ת��Ϊ�ַ���,���ڴ����ļ���
	CString GetTimeToStrName();
	//��ȡ��ǰʱ�䣬ת��Ϊ�ַ���,����д����־�ļ�
	CString GetTimeToStrLog();

	//д��־
	void WriteLog(CStdioFile &file, const char *strlog);

	afx_msg LRESULT OnCommRecvData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedSendButton();
	afx_msg void OnBnClickedOpenlogButton();
};
