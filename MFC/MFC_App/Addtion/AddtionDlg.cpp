
// AddtionDlg.cpp : ʵ���ļ�
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


// CAddtionDlg �Ի���



//���캯��
CAddtionDlg::CAddtionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddtionDlg::IDD, pParent)
	, m_editSumand(0)
	, m_editAddend(0)
	, m_editSum(0)
	, m_tipDlg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//��������
CAddtionDlg::~CAddtionDlg()
{
	//�����ģ̬��ʾ�Ի����Ѿ���������ɾ��
	if (NULL != m_tipDlg)
	{
		delete m_tipDlg;
		m_tipDlg = NULL;
	}
}



//����MFCĬ�ϵ����ݽ���
void CAddtionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//����ؼ� IDC_SUMMAND_EDIT �ͱ��� m_editSummand ֮������ݽ���
	DDX_Text(pDX, IDC_SUMMAND_EDIT, m_editSumand);
	// ����ؼ� IDC_ADDEND_EDIT �ͱ��� m_editAddend ֮������ݽ���
	DDX_Text(pDX, IDC_ADDEND_EDIT, m_editAddend);
	// ����ؼ� IDC_SUM_EDIT �ͱ��� m_editSum ֮������ݽ���
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


// CAddtionDlg ��Ϣ�������

BOOL CAddtionDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAddtionDlg::OnPaint()
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
HCURSOR CAddtionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAddtionDlg::OnStnClickedSummandStatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CAddtionDlg::OnEnChangeSummandEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

//���������㰴ť
//����ִ�м��㣬����ʾ���
void CAddtionDlg::OnClickedAddButton()
{
	//ģ̬�Ի���ʹ�÷�ʽ
	//INT_PTR nRes;
	//CTipDialog tipDlg;	//����Ի�����CTipDialog��ʵ��

	//nRes = tipDlg.DoModal();	//������ʾ�Ի���
	//if (IDCANCEL == nRes)	//�ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL,���򷵻�
	//{
	//	return;
	//}
	

	//��ģ̬�Ի���ʹ��
	//if (NULL == m_tipDlg)
	//{
	//	//������ģ̬�Ի���
	//	m_tipDlg = new CTipDialog();
	//	m_tipDlg->Create(IDD_TIP_DIALOG, this);
	//}

	////��ʾ��ģ̬�Ի���
	//m_tipDlg->ShowWindow(SW_SHOW);


	//ʹ����Ϣ�Ի��� //ģ̬�Ի���
	INT_PTR n_Res;
	n_Res = MessageBox(_T("�Ƿ�Ҫ���мӷ����㣿"), _T("�ӷ�������"), MB_OKCANCEL | MB_ICONQUESTION);
	if (IDCANCEL == n_Res)
		return;





	//�����ؼ��е����ݱ��浽����
	UpdateData(TRUE);

	//�������뱻�����ĺ͸�ֵ��m_editSum
	m_editSum = m_editSumand + m_editAddend;

	//���������е����ݱ��浽�ؼ�

	UpdateData(FALSE);
}


//������������ť
//�����������ԶԻ��򵯳�
void CAddtionDlg::OnBnClickedInstruceButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	////����Ϊ��ģʽ������ҳ�Ի���
	////�������Ա����
	//CAddSheet sheet(_T(""));

	////�������ԶԻ���Ϊ�򵼶Ի���
	//sheet.SetWizardMode();

	////��ģ̬�򵼶Ի���
	//sheet.DoModal();


	//����Ϊһ������ҳ�ĶԻ���
	//�������Ա����
	CAddSheet sheet(_T("ʹ��˵��"));

	//��ģ̬һ������ҳ�Ի���
	sheet.DoModal();
}
