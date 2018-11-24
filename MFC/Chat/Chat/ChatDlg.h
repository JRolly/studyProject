
// ChatDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_RECVDATA		WM_USER+1
#define PORT			6000

typedef struct 
{
	SOCKET sock;
	HWND hWnd;
}RECVPARAM;

// CChatDlg �Ի���
class CChatDlg : public CDialogEx
{
// ����
public:
	CChatDlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL InitSock();
	static DWORD WINAPI RecvProc(LPVOID lpParameter);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
#endif

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
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnSend();
	DECLARE_MESSAGE_MAP()
private:
	CString m_strSendData;
	CEdit m_edRecv;
	CIPAddressCtrl m_IPAddr;
	SOCKET m_Sock;
};
