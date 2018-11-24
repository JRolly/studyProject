
// PaintInWindowsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PaintInWindows.h"
#include "PaintInWindowsDlg.h"
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


// CPaintInWindowsDlg 对话框




CPaintInWindowsDlg::CPaintInWindowsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaintInWindowsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);
}

void CPaintInWindowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);
}

BEGIN_MESSAGE_MAP(CPaintInWindowsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPaintInWindowsDlg 消息处理程序

BOOL CPaintInWindowsDlg::OnInitDialog()
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

	srand((unsigned)time(NULL));
	SetTimer(1, 200, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPaintInWindowsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPaintInWindowsDlg::OnPaint()
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
HCURSOR CPaintInWindowsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPaintInWindowsDlg::DrawWave(CDC *pDC, CRect &rectPicture)
{
	float fDeltaX; // x 轴相邻两个绘图点的坐标距离
	float fDeltaY; // y 轴每个逻辑单位对应的坐标值
	int nX; // 在连线时用于存储绘图点的横坐标
	int nY; // 在连线时用于存储绘图点的纵坐标
	CPen newPen; // 用于创建新画笔
	CPen *pOldPen; // 用于存放旧画笔
	CBrush newBrush; // 用于创建新画刷
	CBrush *pOldBrush; // 用于存放旧画刷

	// 计算 fDeltaX 和 fDeltaY
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// 创建黑色新画刷
	newBrush.CreateSolidBrush(RGB(0,0,0));
	// 选择新画刷，并将旧画刷的指针保存到 pOldBrush
	pOldBrush = pDC->SelectObject(&newBrush);
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景
	pDC->Rectangle(rectPicture);
	// 恢复旧画刷
	pDC->SelectObject(pOldBrush);
	// 删除新画刷
	newBrush.DeleteObject();

	// 创建实心画笔，粗度为 1，颜色为绿色
	newPen.CreatePen(PS_SOLID, 1, RGB(0,255,0));
	// 选择新画笔，并将旧画笔的指针保存到 pOldPen
	pOldPen = pDC->SelectObject(&newPen);

	// 将当前点移动到绘图控件窗口的左下角，以此为波形的起始点
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	// 计算 m_nzValues 数组中每个点对应的坐标位置，并依次连接，最终形成曲线
	for (int i=0; i<POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);
		pDC->LineTo(nX, nY);
	}

	// 恢复旧画笔
	pDC->SelectObject(pOldPen);
	// 删除新画笔
	newPen.DeleteObject();
}


void CPaintInWindowsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rectPicture;

	// 将数组中的所有元素前移一个单位，第一个元素丢弃
	for (int i=0; i<POINT_COUNT-1; i++)
	{
		m_nzValues[i] = m_nzValues[i+1];
	}
	// 为最后一个元素赋一个 80 以内的随机数值（整型）
	m_nzValues[POINT_COUNT-1] = rand() % 80;
	
	// 获取绘图控件的客户区坐标
	// （客户区坐标以窗口的左上角为原点，这区别于以屏幕左上角为原点的屏幕坐标）
	m_picDraw.GetClientRect(&rectPicture);
	
	// 绘制波形图
	DrawWave(m_picDraw.GetDC(), rectPicture);
	
	CDialogEx::OnTimer(nIDEvent);
}


void CPaintInWindowsDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码

	// 关闭定时器
	KillTimer(1);	
}
