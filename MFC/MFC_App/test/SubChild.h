#pragma once


// CSubChild �Ի���

class CSubChild : public CDialogEx
{
	DECLARE_DYNAMIC(CSubChild)

public:
	CSubChild(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubChild();

// �Ի�������
	enum { IDD = IDD_SubChild };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
