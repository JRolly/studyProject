
// Hex-floatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hex-float.h"
#include "Hex-floatDlg.h"
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


// CHexfloatDlg 对话框




CHexfloatDlg::CHexfloatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHexfloatDlg::IDD, pParent)
	, m_strHex(_T(""))
	, m_strFloat(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexfloatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HexIn, m_strHex);
	DDX_Text(pDX, IDC_FloatIn, m_strFloat);
}

BEGIN_MESSAGE_MAP(CHexfloatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Hex2Float, &CHexfloatDlg::OnBnClickedHex2float)
	ON_BN_CLICKED(IDC_Float2Hex, &CHexfloatDlg::OnBnClickedFloat2hex)
END_MESSAGE_MAP()


// CHexfloatDlg 消息处理程序

BOOL CHexfloatDlg::OnInitDialog()
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

void CHexfloatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHexfloatDlg::OnPaint()
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
HCURSOR CHexfloatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT64 CHexfloatDlg::HexStr2int(const char* str)
{
	INT64 ret = 0;
	int n = 0;
	if ((0 == strncmp(str, "0x", 2)) || (0 == strncmp(str, "0X", 2)))
	{
		str += 2;
	}

	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			ret += (UINT64)((*str - '0') * pow(16.0, n));
		}
		else if (*str >= 'a' && *str <= 'f')
		{
			ret += (UINT64)((*str - 'a' + 10) * pow(16.0, n));
		}
		else if (*str >= 'A' && *str <= 'F')
		{
			ret += (UINT64)((*str - 'A' + 10) * pow(16.0, n));
		}
		++str;
		++n;
	}

	return ret;
}



void CHexfloatDlg::OnBnClickedHex2float()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_HexIn, m_strHex);
	char str[_CVTBUFSIZE] = {0};
	char buf[_CVTBUFSIZE] = {0};
	int offset = 0;
	if (m_strHex.GetLength() >= _CVTBUFSIZE)
	{
		MessageBox("输入数据长度过长，请重新输入！",MB_OK);
		return;
	}
	strcpy(str, m_strHex);
	if ((0 == strncmp(str, "0x", 2)) || (0 == strncmp(str, "0X", 2)))
	{
		offset += 2;
	}
	while (str[offset])
	{
		if ((str[offset] >= '0' && str[offset] <= '9') || (str[offset] >='a' && str[offset] <= 'f') || (str[offset] >= 'A' && str[offset] <= 'F'))
		{	//检验字符合法性
			++offset;
		}
		else
		{
			MessageBox("输入格式错误，请重新输入！", MB_OK);
			return;
		}
	}

	union{float f; unsigned int i;};
	sprintf(buf, "%08x", HexStr2int(str));
	i = HexStr2int(buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%0.6f", f);
	SetDlgItemText(IDC_FloatOut, buf);
}


void CHexfloatDlg::OnBnClickedFloat2hex()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_FloatIn, m_strFloat);
	char str[_CVTBUFSIZE] = {0};
	char buf[_CVTBUFSIZE] = {0};
	int offset = 0;
	bool bHavePoint = FALSE;
	if (m_strFloat.GetLength() >= _CVTBUFSIZE)
	{
		MessageBox("输入数据长度过长，请重新输入！",MB_OK);
		return;
	}
	strcpy(str, m_strFloat);

	if (str[0] == '.')
	{
		MessageBox("输入格式错误，请重新输入！", MB_OK);
		return;
	}

	while (str[offset])
	{
		if ((str[offset] >= '0' && str[offset] <= '9') || (str[offset] == '.') )
		{	//检验字符合法性
			if (str[offset] == '.') 
			{
				if ( bHavePoint == FALSE)
				{
					bHavePoint = TRUE;
					++offset;
				}
				else
				{
					MessageBox("输入格式错误，请重新输入！", MB_OK);
					return;
				}
			}
			else 
			{
				++offset;
			}
			
		}
		else
		{
			MessageBox("输入格式错误，请重新输入！", MB_OK);
			return;
		}
	}

	union{float f; unsigned int i;};
	f = atof(str);
	sprintf(buf, "%08X", i);
	SetDlgItemText(IDC_HexOut, buf);
}


BOOL CHexfloatDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	//if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
	//	return TRUE; 
	//if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
	//	return TRUE;

	//完全屏蔽ESC键，捕获Enter键
	//if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN )     
	//{
	//	if(GetFocus()->GetDlgCtrlID()==IDC_Hex2Float)//按下回车，如果当前焦点是在自己期望的              控件上
	//	{                                           
	//		OnBnClickedHex2float();//添加自己的处理代码
	//	}

	//	if(GetFocus()->GetDlgCtrlID()==IDC_Float2Hex)//按下回车，如果当前焦点是在自己期望的              控件上
	//	{                                           
	//		OnBnClickedFloat2hex();//添加自己的处理代码
	//	}
	//	return TRUE;
	//}

	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)     
		return TRUE; 

	return CDialogEx::PreTranslateMessage(pMsg);
}
