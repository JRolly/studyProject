// MainChild.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "MainChild.h"
#include "afxdialogex.h"


// CMainChild 对话框

IMPLEMENT_DYNAMIC(CMainChild, CDialogEx)

CMainChild::CMainChild(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainChild::IDD, pParent)
{
	pSubChild = NULL;
}

CMainChild::~CMainChild()
{
}

void CMainChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainChild, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainChild::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMainChild 消息处理程序


void CMainChild::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pSubChild == NULL)
	{
		pSubChild = new CSubChild();
		//pSubChild->Create(IDD_SubChild);
		//pSubChild->ShowWindow(SW_SHOW);
		pSubChild->DoModal();
	}
}
