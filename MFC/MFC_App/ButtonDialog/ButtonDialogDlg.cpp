
// ButtonDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ButtonDialog.h"
#include "ButtonDialogDlg.h"
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


// CButtonDialogDlg �Ի���




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


// CButtonDialogDlg ��Ϣ�������

BOOL CButtonDialogDlg::OnInitDialog()
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

	//Ĭ��ѡ���Ż�����ѡ��ť
	CheckDlgButton(IDC_PORTAL_RADIO, BST_CHECKED);
	OnBnClickedPortalRadio();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CButtonDialogDlg::OnPaint()
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
HCURSOR CButtonDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ʼ�����и�ѡ��״̬����ȫ�����ã���ȫ��ѡ��
void CButtonDialogDlg::InitAllCheckBoxStatus()
{
	//ȫ������
	m_check1.EnableWindow(FALSE);
	m_check2.EnableWindow(FALSE);
	m_check3.EnableWindow(FALSE);
	m_check4.EnableWindow(FALSE);
	m_check5.EnableWindow(FALSE);
	m_check6.EnableWindow(FALSE);

	//ȫ����ѡ��
	m_check1.SetCheck(BST_UNCHECKED);
	m_check2.SetCheck(BST_UNCHECKED);
	m_check3.SetCheck(BST_UNCHECKED);
	m_check4.SetCheck(BST_UNCHECKED);
	m_check5.SetCheck(BST_UNCHECKED);
	m_check6.SetCheck(BST_UNCHECKED);
}

//ѡ���Ż���վ
void CButtonDialogDlg::OnBnClickedPortalRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�����и�ѡ��״̬
	InitAllCheckBoxStatus();
	//������Ӧ��ѡ��
	m_check3.EnableWindow(TRUE);
	m_check4.EnableWindow(TRUE);
}

//ѡ����̳
void CButtonDialogDlg::OnBnClickedForumRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitAllCheckBoxStatus();
	//������Ӧ��ѡ��
	m_check1.EnableWindow(TRUE);
	m_check2.EnableWindow(TRUE);
}


void CButtonDialogDlg::OnBnClickedBlogRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitAllCheckBoxStatus();
	//������Ӧ��ѡ��
	m_check5.EnableWindow(TRUE);
	m_check6.EnableWindow(TRUE);
}


//�����ȷ�����󣬽�ѡ�����վ��ʾ�ڱ༭��
void CButtonDialogDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strWebsitSel;

	//��ѡ�����ġ�,��������ַ���
	if (BST_CHECKED == m_check1.GetCheck())
	{
		strWebsitSel += _T("���� "); 
	}

	//��ѡ�񡰿�����,��������ַ���
	if (BST_CHECKED == m_check2.GetCheck())
	{
		strWebsitSel += _T("���� "); 
	}

	//��ѡ�񡰰ٶȡ�,��������ַ���
	if (BST_CHECKED == m_check3.GetCheck())
	{
		strWebsitSel += _T("�ٶ� "); 
	}

	//��ѡ����Ѷ��,��������ַ���
	if (BST_CHECKED == m_check4.GetCheck())
	{
		strWebsitSel += _T("��Ѷ "); 
	}

	//��ѡ�����ˡ�,��������ַ���
	if (BST_CHECKED == m_check5.GetCheck())
	{
		strWebsitSel += _T("���� "); 
	}

	//��ѡ�񡰼����ס�,��������ַ���
	if (BST_CHECKED == m_check6.GetCheck())
	{
		strWebsitSel += _T("������ "); 
	}

	SetDlgItemText(IDC_WEBSIT_SEL_EDIT, strWebsitSel);

	//Ϊ������ȷ���˳������Բ���Ҫ����
	//CDialogEx::OnOK();
}
