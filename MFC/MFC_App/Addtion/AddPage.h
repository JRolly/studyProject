#pragma once


// CAddPage 对话框

class CAddPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAddPage)

public:
	CAddPage();
	virtual ~CAddPage();

// 对话框数据
	enum { IDD = IDD_ADD_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
