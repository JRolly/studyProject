// TipDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Addtion.h"
#include "TipDialog.h"
#include "afxdialogex.h"


// CTipDialog 对话框

IMPLEMENT_DYNAMIC(CTipDialog, CDialogEx)

CTipDialog::CTipDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTipDialog::IDD, pParent)
{

}

CTipDialog::~CTipDialog()
{
}

void CTipDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTipDialog, CDialogEx)
END_MESSAGE_MAP()


// CTipDialog 消息处理程序
