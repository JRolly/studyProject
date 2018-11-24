
// ListControlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "LogList.h"

// CListControlDlg �Ի���
class CListControlDlg : public CDialogEx
{
// ����
public:
	CListControlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LISTCONTROL_DIALOG };

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
	// �б�����
	CListCtrl m_listCtrl;
	CLogList *m_plogList;
	map<CString, CString> m_mapItem;
	map<CString, CString>& getmap()
	{
		return m_mapItem;
	}
	void setmap(map<CString, CString> &m)
	{
		m_mapItem = m;
	}
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
