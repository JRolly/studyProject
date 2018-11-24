
// ButtonDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ButtonDialog.h"
#include "ButtonDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CButtonDialogDlg 对话框




CButtonDialogDlg::CButtonDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CButtonDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CButtonDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_check5);
	DDX_Control(pDX, IDC_CHECK6, m_check6);
}

BEGIN_MESSAGE_MAP(CButtonDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PORTAL_RADIO, &CButtonDialogDlg::OnBnClickedPortalRadio)
	ON_BN_CLICKED(IDC_FORUM_RADIO, &CButtonDialogDlg::OnBnClickedForumRadio)
	ON_BN_CLICKED(IDC_BLOG_RADIO, &CButtonDialogDlg::OnBnClickedBlogRadio)
	ON_BN_CLICKED(IDOK, &CButtonDialogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CButtonDialogDlg 消息处理程序

BOOL CButtonDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//默认选择“门户”单选按钮
	CheckDlgButton(IDC_PORTAL_RADIO, BST_CHECKED);
	OnBnClickedPortalRadio();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CButtonDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CButtonDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CButtonDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初始化所有复选框状态，即全部禁用，非全部选中
void CButtonDialogDlg::InitAllCheckBoxStatus()
{
	//全部禁用
	m_check1.EnableWindow(FALSE);
	m_check2.EnableWindow(FALSE);
	m_check3.EnableWindow(FALSE);
	m_check4.EnableWindow(FALSE);
	m_check5.EnableWindow(FALSE);
	m_check6.EnableWindow(FALSE);

	//全部非选中
	m_check1.SetCheck(BST_UNCHECKED);
	m_check2.SetCheck(BST_UNCHECKED);
	m_check3.SetCheck(BST_UNCHECKED);
	m_check4.SetCheck(BST_UNCHECKED);
	m_check5.SetCheck(BST_UNCHECKED);
	m_check6.SetCheck(BST_UNCHECKED);
}

//选中门户网站
void CButtonDialogDlg::OnBnClickedPortalRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化所有复选框状态
	InitAllCheckBoxStatus();
	//启用相应复选框
	m_check3.EnableWindow(TRUE);
	m_check4.EnableWindow(TRUE);
}

//选中论坛
void CButtonDialogDlg::OnBnClickedForumRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	InitAllCheckBoxStatus();
	//启用相应复选框
	m_check1.EnableWindow(TRUE);
	m_check2.EnableWindow(TRUE);
}


void CButtonDialogDlg::OnBnClickedBlogRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	InitAllCheckBoxStatus();
	//启用相应复选框
	m_check5.EnableWindow(TRUE);
	m_check6.EnableWindow(TRUE);
}


//点击“确定”后，将选择的网站显示在编辑框
void CButtonDialogDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWebsitSel;

	//若选择“天涯”,则将其加入字符串
	if (BST_CHECKED == m_check1.GetCheck())
	{
		strWebsitSel += _T("天涯 "); 
	}

	//若选择“卡饭”,则将其加入字符串
	if (BST_CHECKED == m_check2.GetCheck())
	{
		strWebsitSel += _T("卡饭 "); 
	}

	//若选择“百度”,则将其加入字符串
	if (BST_CHECKED == m_check3.GetCheck())
	{
		strWebsitSel += _T("百度 "); 
	}

	//若选择“腾讯”,则将其加入字符串
	if (BST_CHECKED == m_check4.GetCheck())
	{
		strWebsitSel += _T("腾讯 "); 
	}

	//若选择“新浪”,则将其加入字符串
	if (BST_CHECKED == m_check5.GetCheck())
	{
		strWebsitSel += _T("新浪 "); 
	}

	//若选择“鸡啄米”,则将其加入字符串
	if (BST_CHECKED == m_check6.GetCheck())
	{
		strWebsitSel += _T("鸡啄米 "); 
	}

	SetDlgItemText(IDC_WEBSIT_SEL_EDIT, strWebsitSel);

	//为避免点击确定退出，所以不需要此行
	//CDialogEx::OnOK();
}
