
// AddtionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Addtion.h"
#include "AddtionDlg.h"
#include "afxdialogex.h"

//#include "TipDialog.h"
#include "AddSheet.h"

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


// CAddtionDlg 对话框



//构造函数
CAddtionDlg::CAddtionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddtionDlg::IDD, pParent)
	, m_editSumand(0)
	, m_editAddend(0)
	, m_editSum(0)
	, m_tipDlg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//析构函数
CAddtionDlg::~CAddtionDlg()
{
	//如果非模态提示对话框已经创建，则删除
	if (NULL != m_tipDlg)
	{
		delete m_tipDlg;
		m_tipDlg = NULL;
	}
}



//处理MFC默认的数据交换
void CAddtionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//处理控件 IDC_SUMMAND_EDIT 和变量 m_editSummand 之间的数据交换
	DDX_Text(pDX, IDC_SUMMAND_EDIT, m_editSumand);
	// 处理控件 IDC_ADDEND_EDIT 和变量 m_editAddend 之间的数据交换
	DDX_Text(pDX, IDC_ADDEND_EDIT, m_editAddend);
	// 处理控件 IDC_SUM_EDIT 和变量 m_editSum 之间的数据交换
	DDX_Text(pDX, IDC_SUM_EDIT, m_editSum);
}

BEGIN_MESSAGE_MAP(CAddtionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_SUMMAND_STATIC, &CAddtionDlg::OnStnClickedSummandStatic)
	ON_EN_CHANGE(IDC_SUMMAND_EDIT, &CAddtionDlg::OnEnChangeSummandEdit)
	ON_BN_CLICKED(IDC__ADD_BUTTON, &CAddtionDlg::OnClickedAddButton)
	ON_BN_CLICKED(IDC_INSTRUCE_BUTTON, &CAddtionDlg::OnBnClickedInstruceButton)
END_MESSAGE_MAP()


// CAddtionDlg 消息处理程序

BOOL CAddtionDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAddtionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAddtionDlg::OnPaint()
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
HCURSOR CAddtionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAddtionDlg::OnStnClickedSummandStatic()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAddtionDlg::OnEnChangeSummandEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//计算器计算按钮
//触发执行计算，并显示结果
void CAddtionDlg::OnClickedAddButton()
{
	//模态对话框使用方式
	//INT_PTR nRes;
	//CTipDialog tipDlg;	//构造对话框类CTipDialog的实例

	//nRes = tipDlg.DoModal();	//弹出提示对话框
	//if (IDCANCEL == nRes)	//判断对话框退出后返回值是否为IDCANCEL,是则返回
	//{
	//	return;
	//}
	

	//非模态对话框使用
	//if (NULL == m_tipDlg)
	//{
	//	//创建非模态对话框
	//	m_tipDlg = new CTipDialog();
	//	m_tipDlg->Create(IDD_TIP_DIALOG, this);
	//}

	////显示非模态对话框
	//m_tipDlg->ShowWindow(SW_SHOW);


	//使用消息对话框 //模态对话框
	INT_PTR n_Res;
	n_Res = MessageBox(_T("是否要进行加法计算？"), _T("加法计算器"), MB_OKCANCEL | MB_ICONQUESTION);
	if (IDCANCEL == n_Res)
		return;





	//将各控件中的数据保存到变量
	UpdateData(TRUE);

	//将加数与被加数的和赋值给m_editSum
	m_editSum = m_editSumand + m_editAddend;

	//将各变量中的数据保存到控件

	UpdateData(FALSE);
}


//计算器帮助按钮
//触发帮助属性对话框弹出
void CAddtionDlg::OnBnClickedInstruceButton()
{
	// TODO: 在此添加控件通知处理程序代码

	////设置为向导模式的属性页对话框
	////创建属性表对象
	//CAddSheet sheet(_T(""));

	////设置属性对话框为向导对话框
	//sheet.SetWizardMode();

	////打开模态向导对话框
	//sheet.DoModal();


	//设置为一般属性页的对话框
	//创建属性表对象
	CAddSheet sheet(_T("使用说明"));

	//打开模态一般属性页对话框
	sheet.DoModal();
}
