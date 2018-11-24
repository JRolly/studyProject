// AddendPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Addtion.h"
#include "AddendPage.h"
#include "afxdialogex.h"


// CAddendPage 对话框

IMPLEMENT_DYNAMIC(CAddendPage, CPropertyPage)

CAddendPage::CAddendPage()
	: CPropertyPage(CAddendPage::IDD)
{

}

CAddendPage::~CAddendPage()
{
}

void CAddendPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddendPage, CPropertyPage)
END_MESSAGE_MAP()


// CAddendPage 消息处理程序




BOOL CAddendPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	//获取父窗口
	CPropertySheet *psheet = (CPropertySheet *)GetParent();

	//设置属性表有“上一步”和“下一步”按钮
	psheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);

	return CPropertyPage::OnSetActive();
}
