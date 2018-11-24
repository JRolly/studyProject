// AddPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Addtion.h"
#include "AddPage.h"
#include "afxdialogex.h"


// CAddPage 对话框

IMPLEMENT_DYNAMIC(CAddPage, CPropertyPage)

CAddPage::CAddPage()
	: CPropertyPage(CAddPage::IDD)
{

}

CAddPage::~CAddPage()
{
}

void CAddPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddPage, CPropertyPage)
END_MESSAGE_MAP()


// CAddPage 消息处理程序


BOOL CAddPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类

	//获取父窗口
	CPropertySheet *psheet = (CPropertySheet *)GetParent();

	//设置属性表只有完成按钮
	//psheet->SetFinishText(_T("完成"));

	//设置属性表有“上一步”和“完成”按钮
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

	return CPropertyPage::OnSetActive();
}


BOOL CAddPage::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类

	//提示向导完成
	MessageBox(_T("使用说明已阅读完！"));

	return CPropertyPage::OnWizardFinish();
}
