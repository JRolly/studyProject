
// AddtionDlg.h : ͷ�ļ�
//

#pragma once

#include "TipDialog.h"

// CAddtionDlg �Ի���
class CAddtionDlg : public CDialogEx
{
// ����
public:
	CAddtionDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CAddtionDlg();	//��������

// �Ի�������
	enum { IDD = IDD_ADDTION_DIALOG };

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
	afx_msg void OnStnClickedSummandStatic();
	afx_msg void OnEnChangeSummandEdit();
	// ������
	double m_editSumand;
	// ����
	double m_editAddend;
	// ��
	double m_editSum;
	afx_msg void OnClickedAddButton();

private:
	CTipDialog *m_tipDlg;	//��ʾ��ָ�����
public:
	afx_msg void OnBnClickedInstruceButton();
};
