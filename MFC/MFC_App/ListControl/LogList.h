#pragma once
#include "afxcmn.h"


// CLogList �Ի���

class CLogList : public CDialogEx
{
	DECLARE_DYNAMIC(CLogList)

public:
	CLogList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogList();

// �Ի�������
	enum { IDD = IDD_LOG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_loglist;

	afx_msg void OnBnClickedOk();
};
