
// testDlg.h : ͷ�ļ�
//

#pragma once
#include "MainChild.h"

#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")


// CtestDlg �Ի���
class CtestDlg : public CDialogEx
{
// ����
public:
	CtestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CtestDlg();
// �Ի�������
	enum { IDD = IDD_Main };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
public:
	HICON m_hIcon;
	CMainChild *pmainChild;
	UINT32 m_nCnt;
	MMRESULT m_TimerID;
	bool m_bHasAdd;
public:
	bool OnStartTimer();
	void OnSotpTimer();
	static void CALLBACK TimerFun(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void PrintCnt();
	void DealSomething();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
