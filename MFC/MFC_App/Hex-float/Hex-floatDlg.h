
// Hex-floatDlg.h : ͷ�ļ�
//

#pragma once


#include <math.h>


// CHexfloatDlg �Ի���
class CHexfloatDlg : public CDialogEx
{
// ����
public:
	CHexfloatDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HEXFLOAT_DIALOG };

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
	CString m_strHex;
	CString m_strFloat;
	UINT64 HexStr2int(const char* str);
	afx_msg void OnBnClickedHex2float();
	afx_msg void OnBnClickedFloat2hex();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
