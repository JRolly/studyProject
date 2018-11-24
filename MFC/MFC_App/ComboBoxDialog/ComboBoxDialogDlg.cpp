
// ComboBoxDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComboBoxDialog.h"
#include "ComboBoxDialogDlg.h"
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


// CComboBoxDialogDlg �Ի���




CComboBoxDialogDlg::CComboBoxDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComboBoxDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComboBoxDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WEB_COMBO, m_comboWeb);
}

BEGIN_MESSAGE_MAP(CComboBoxDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_WEB_COMBO, &CComboBoxDialogDlg::OnCbnSelchangeWebCombo)
	ON_CBN_SELCHANGE(IDC_WEB_COMBO, &CComboBoxDialogDlg::OnCbnSelchangeWebCombo)
END_MESSAGE_MAP()


// CComboBoxDialogDlg ��Ϣ�������

BOOL CComboBoxDialogDlg::OnInitDialog()
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

	// Ϊ��Ͽ�ؼ����б������б���
	m_comboWeb.AddString(_T("�ٶ�"));
	m_comboWeb.AddString(_T("����"));
	m_comboWeb.AddString(_T("��Ѷ"));

	//Ĭ��ѡ���һ��
	m_comboWeb.SetCurSel(0);

	//�༭����Ĭ����ʾ��һ�������
	SetDlgItemText(IDC_SEL_WEB_EDIT, _T("�ٶ�"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CComboBoxDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CComboBoxDialogDlg::OnPaint()
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
HCURSOR CComboBoxDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//�ı���Ͽ����б���ʱ���������б�������ʵʱ��ʾ�ڱ༭��
void CComboBoxDialogDlg::OnCbnSelchangeWebCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strWeb;
	int nSel;

	nSel = m_comboWeb.GetCurSel();	//��ȡѡ�е���Ͽ���б�������
	m_comboWeb.GetLBText(nSel, strWeb);	//����������ȡ�����ַ���
	SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb);	//����ȡ���ַ�����ʾ���б��

}
