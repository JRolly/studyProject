
// ButtonDialogDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CButtonDialogDlg �Ի���
class CButtonDialogDlg : public CDialogEx
{
// ����
public:
	CButtonDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

	//��ʼ�����и�ѡ��״̬����ȫ�����ã���ȫ��ѡ��
	void InitAllCheckBoxStatus();

// �Ի�������
	enum { IDD = IDD_BUTTONDIALOG_DIALOG };

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
	// ����
	CButton m_check1;
	// ����
	CButton m_check2;
	// �ٶ�
	CButton m_check3;
	// ��Ѷ
	CButton m_check4;
	// ����
	CButton m_check5;
	// ������
	CButton m_check6;
	afx_msg void OnBnClickedPortalRadio();
	afx_msg void OnBnClickedForumRadio();
	afx_msg void OnBnClickedBlogRadio();
	afx_msg void OnBnClickedOk();
};
