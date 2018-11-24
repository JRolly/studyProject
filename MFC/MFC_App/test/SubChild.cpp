// SubChild.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "SubChild.h"
#include "afxdialogex.h"


// CSubChild 对话框

IMPLEMENT_DYNAMIC(CSubChild, CDialogEx)

CSubChild::CSubChild(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubChild::IDD, pParent)
{

}

CSubChild::~CSubChild()
{
}

void CSubChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubChild, CDialogEx)
END_MESSAGE_MAP()


// CSubChild 消息处理程序
