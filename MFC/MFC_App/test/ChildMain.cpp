// ChildMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "ChildMain.h"
#include "afxdialogex.h"


// CChildMain �Ի���

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


// CChildMain ��Ϣ�������
