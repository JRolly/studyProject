#pragma once


// CSubChild 对话框

class CSubChild : public CDialogEx
{
	DECLARE_DYNAMIC(CSubChild)

public:
	CSubChild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubChild();

// 对话框数据
	enum { IDD = IDD_SubChild };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
