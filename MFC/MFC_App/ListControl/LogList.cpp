// LogList.cpp : 实现文件
//

#include "stdafx.h"
#include "ListControl.h"
#include "LogList.h"
#include "afxdialogex.h"


// CLogList 对话框

IMPLEMENT_DYNAMIC(CLogList, CDialogEx)

CLogList::CLogList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogList::IDD, pParent)
{

}

CLogList::~CLogList()
{
}

void CLogList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC__LOG_LIST, m_loglist);
}


BEGIN_MESSAGE_MAP(CLogList, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogList::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogList 消息处理程序





void CLogList::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_loglist.InsertColumn(0, "语言", LVCFMT_CENTER, 200, 0);
	//m_loglist.InsertColumn(1, "排名", LVCFMT_CENTER, 200, 1);
	//map<CString, CString>::iterator it = m_mapItem.begin();
	//int index = 0;
	//for (; it != m_mapItem.end(); ++it)
	//{
	//	m_loglist.InsertItem(index, it->first);
	//	m_loglist.SetItemText(index, index, it->second);
	//	index++;
	//}

	CDialogEx::OnOK();
}
