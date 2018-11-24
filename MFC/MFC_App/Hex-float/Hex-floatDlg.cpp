
// Hex-floatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hex-float.h"
#include "Hex-floatDlg.h"
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


// CHexfloatDlg �Ի���




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


// CHexfloatDlg ��Ϣ�������

BOOL CHexfloatDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHexfloatDlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_HexIn, m_strHex);
	char str[_CVTBUFSIZE] = {0};
	char buf[_CVTBUFSIZE] = {0};
	int offset = 0;
	if (m_strHex.GetLength() >= _CVTBUFSIZE)
	{
		MessageBox("�������ݳ��ȹ��������������룡",MB_OK);
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
		{	//�����ַ��Ϸ���
			++offset;
		}
		else
		{
			MessageBox("�����ʽ�������������룡", MB_OK);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_FloatIn, m_strFloat);
	char str[_CVTBUFSIZE] = {0};
	char buf[_CVTBUFSIZE] = {0};
	int offset = 0;
	bool bHavePoint = FALSE;
	if (m_strFloat.GetLength() >= _CVTBUFSIZE)
	{
		MessageBox("�������ݳ��ȹ��������������룡",MB_OK);
		return;
	}
	strcpy(str, m_strFloat);

	if (str[0] == '.')
	{
		MessageBox("�����ʽ�������������룡", MB_OK);
		return;
	}

	while (str[offset])
	{
		if ((str[offset] >= '0' && str[offset] <= '9') || (str[offset] == '.') )
		{	//�����ַ��Ϸ���
			if (str[offset] == '.') 
			{
				if ( bHavePoint == FALSE)
				{
					bHavePoint = TRUE;
					++offset;
				}
				else
				{
					MessageBox("�����ʽ�������������룡", MB_OK);
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
			MessageBox("�����ʽ�������������룡", MB_OK);
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
	// TODO: �ڴ����ר�ô����/����û���
	
	//if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
	//	return TRUE; 
	//if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
	//	return TRUE;

	//��ȫ����ESC��������Enter��
	//if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN )     
	//{
	//	if(GetFocus()->GetDlgCtrlID()==IDC_Hex2Float)//���»س��������ǰ���������Լ�������              �ؼ���
	//	{                                           
	//		OnBnClickedHex2float();//����Լ��Ĵ������
	//	}

	//	if(GetFocus()->GetDlgCtrlID()==IDC_Float2Hex)//���»س��������ǰ���������Լ�������              �ؼ���
	//	{                                           
	//		OnBnClickedFloat2hex();//����Լ��Ĵ������
	//	}
	//	return TRUE;
	//}

	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)     
		return TRUE; 

	return CDialogEx::PreTranslateMessage(pMsg);
}
