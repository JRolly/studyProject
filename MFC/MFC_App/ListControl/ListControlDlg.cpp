
// ListControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ListControl.h"
#include "ListControlDlg.h"
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


// CListControlDlg 对话框




CListControlDlg::CListControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CListControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CListControlDlg::OnNMClickList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CListControlDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CListControlDlg 消息处理程序

BOOL CListControlDlg::OnInitDialog()
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

	m_mapItem.insert(make_pair("C++", "1"));
	m_mapItem.insert(make_pair("Java", "2"));
	m_mapItem.insert(make_pair("C#", "3"));

	CRect rect;
	//获取列表视图控件的位置和大小
	m_listCtrl.GetClientRect(&rect);

	//为列表视图框控件添加全选中和栅格风格
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//添加三列
	m_listCtrl.InsertColumn(0, "语言", LVCFMT_CENTER, rect.Width()/3, 0);
	m_listCtrl.InsertColumn(1, "排名1", LVCFMT_CENTER, rect.Width()/3, 1);
	m_listCtrl.InsertColumn(2, "排名2", LVCFMT_CENTER, rect.Width()/3, 2);

	//插入列表项并设置列表子项文本
	//m_listCtrl.InsertItem(0, "C++");
	//m_listCtrl.SetItemText(0, 1, "1");
	//m_listCtrl.SetItemText(0, 2, "1");

	//m_listCtrl.InsertItem(1, "Java");
	//m_listCtrl.SetItemText(1, 1, "2");
	//m_listCtrl.SetItemText(1, 2, "3");

	//m_listCtrl.InsertItem(2, "C#");
	//m_listCtrl.SetItemText(2, 1, "3");
	//m_listCtrl.SetItemText(2, 2, "2");
	map<CString, CString>::iterator it = m_mapItem.begin();
	for (int i = 0; i < 3; i++)
	{
		m_listCtrl.InsertItem(i, it->first);
		m_listCtrl.SetItemText(i, 1, it->second);
		m_listCtrl.SetItemText(i, 2, it->second);
		++it;
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CListControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListControlDlg::OnPaint()
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
HCURSOR CListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListControlDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CString strLangName;
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)
	{
		strLangName = m_listCtrl.GetItemText(pNMListView->iItem, 0);
		SetDlgItemText(IDC_LANG_EDIT, strLangName);
	}

	*pResult = 0;
}


void CListControlDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	m_plogList = new CLogList();
	m_plogList->Create(IDD_LOG_DIALOG, this);
	m_plogList->ShowWindow(SW_SHOW);
	//CLogList loglist;
	//loglist.DoModal();
	*pResult = 0;
}
