// SubChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "SubChild.h"
#include "afxdialogex.h"


// CSubChild �Ի���

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


// CSubChild ��Ϣ�������
