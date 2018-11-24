
// ListControlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "LogList.h"

// CListControlDlg 对话框
class CListControlDlg : public CDialogEx
{
// 构造
public:
	CListControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LISTCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 列表框对象
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
