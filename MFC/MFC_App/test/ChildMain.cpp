// ChildMain.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "ChildMain.h"
#include "afxdialogex.h"


// CChildMain 对话框

IMPLEMENT_DYNAMIC(CChildMain, CDialogEx)

CChildMain::CChildMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildMain::IDD, pParent)
{

}

CChildMain::~CChildMain()
{
}

void CChildMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChildMain, CDialogEx)
END_MESSAGE_MAP()


// CChildMain 消息处理程序
