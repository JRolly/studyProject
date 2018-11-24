// MainChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "MainChild.h"
#include "afxdialogex.h"


// CMainChild �Ի���

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


// CMainChild ��Ϣ�������


void CMainChild::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (pSubChild == NULL)
	{
		pSubChild = new CSubChild();
		//pSubChild->Create(IDD_SubChild);
		//pSubChild->ShowWindow(SW_SHOW);
		pSubChild->DoModal();
	}
}
