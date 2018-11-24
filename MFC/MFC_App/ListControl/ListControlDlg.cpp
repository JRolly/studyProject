
// ListControlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListControl.h"
#include "ListControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CListControlDlg �Ի���




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


// CListControlDlg ��Ϣ�������

BOOL CListControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_mapItem.insert(make_pair("C++", "1"));
	m_mapItem.insert(make_pair("Java", "2"));
	m_mapItem.insert(make_pair("C#", "3"));

	CRect rect;
	//��ȡ�б���ͼ�ؼ���λ�úʹ�С
	m_listCtrl.GetClientRect(&rect);

	//Ϊ�б���ͼ��ؼ����ȫѡ�к�դ����
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//�������
	m_listCtrl.InsertColumn(0, "����", LVCFMT_CENTER, rect.Width()/3, 0);
	m_listCtrl.InsertColumn(1, "����1", LVCFMT_CENTER, rect.Width()/3, 1);
	m_listCtrl.InsertColumn(2, "����2", LVCFMT_CENTER, rect.Width()/3, 2);

	//�����б�������б������ı�
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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CListControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListControlDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	m_plogList = new CLogList();
	m_plogList->Create(IDD_LOG_DIALOG, this);
	m_plogList->ShowWindow(SW_SHOW);
	//CLogList loglist;
	//loglist.DoModal();
	*pResult = 0;
}
