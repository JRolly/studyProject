// AddPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Addtion.h"
#include "AddPage.h"
#include "afxdialogex.h"


// CAddPage �Ի���

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


// CAddPage ��Ϣ�������


BOOL CAddPage::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���

	//��ȡ������
	CPropertySheet *psheet = (CPropertySheet *)GetParent();

	//�������Ա�ֻ����ɰ�ť
	//psheet->SetFinishText(_T("���"));

	//�������Ա��С���һ�����͡���ɡ���ť
	psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

	return CPropertyPage::OnSetActive();
}


BOOL CAddPage::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���

	//��ʾ�����
	MessageBox(_T("ʹ��˵�����Ķ��꣡"));

	return CPropertyPage::OnWizardFinish();
}
