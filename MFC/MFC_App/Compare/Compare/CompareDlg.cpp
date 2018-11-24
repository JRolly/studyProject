
// CompareDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Compare.h"
#include "CompareDlg.h"
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


// CCompareDlg �Ի���
DWORD WINAPI GetDiffPos(LPVOID);
DWORD WINAPI FindNextDiff(LPVOID);
DWORD WINAPI FindBackDiff(LPVOID);

CCompareDlg *pDlg;

CCompareDlg::CCompareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompareDlg::IDD, pParent)
	, m_iPage(0)
	, m_isFile2(false)
	, m_uFileLine1(0)
	, m_uFileLine2(0)
	, m_uLine(0)
	, m_uPages(0)
	, m_iDiffPos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hFile1 = INVALID_HANDLE_VALUE;   //��ʼ��File1���ļ����
	m_hFileMapping1 = INVALID_HANDLE_VALUE;
	m_uFileLength1 = 0;

	m_hFile2 = INVALID_HANDLE_VALUE;   //��ʼ��File2���ļ����
	m_hFileMapping2 = INVALID_HANDLE_VALUE;
	m_uFileLength2 = 0;

	SYSTEM_INFO si;  
	GetSystemInfo(&si);
	m_dwAllocGranularity = si.dwAllocationGranularity;  

	pDlg = this;
}

void CCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFile1, m_ListFile1);
	DDX_Control(pDX, IDC_LISTFile2, m_ListFile2);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_VScrollBar);
}

BEGIN_MESSAGE_MAP(CCompareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUT_OpenFile1, &CCompareDlg::OnBnClickedButOpenfile1)
	ON_BN_CLICKED(IDC_BUT_OpenFile2, &CCompareDlg::OnBnClickedButOpenfile2)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_LBN_SELCHANGE(IDC_LISTFile1, &CCompareDlg::OnLbnSelchangeListfile1)
	ON_LBN_SELCHANGE(IDC_LISTFile2, &CCompareDlg::OnLbnSelchangeListfile2)
	ON_BN_CLICKED(IDC_BUT_FindDiffNext, &CCompareDlg::OnBnClickedButFinddiffNext)
	ON_BN_CLICKED(IDC_BUT_FindDiffBack, &CCompareDlg::OnBnClickedButFinddiffBack)
	ON_BN_CLICKED(IDC_BUT_Release, &CCompareDlg::OnBnClickedButRelease)
END_MESSAGE_MAP()


// CCompareDlg ��Ϣ�������

BOOL CCompareDlg::OnInitDialog()
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

void CCompareDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCompareDlg::OnPaint()
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
HCURSOR CCompareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCompareDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	WCHAR wcStr[MAX_PATH];  
	int iDropFilesCnt = DragQueryFile(hDropInfo, -1, NULL, 0);
	if (iDropFilesCnt > 2) {
		MessageBox("�����Ƚ��ļ�����!", "��ʾ", MB_OK);
		return;
	}

	if (iDropFilesCnt == 1) {
		DragQueryFile(hDropInfo, 0, (LPSTR)wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ��� 
		if (!m_isFile2) { 
			SetDlgItemText(IDC_EDFile1, (LPCTSTR)wcStr);
			m_strFilePath1 = (LPCTSTR)wcStr;
			m_isFile2 = true;
		} else {
			SetDlgItemText(IDC_EDFile2, (LPCTSTR)wcStr);
			m_strFilePath2 = (LPCTSTR)wcStr;
			InitFile();
			DispCompare(m_iPage);
		}
	}

	if (iDropFilesCnt == 2) {
		for (int i = 0; i < iDropFilesCnt; i++) {
			DragQueryFile(hDropInfo, i, (LPSTR)wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ��� 
			SetDlgItemText(IDC_EDFile1 + i, (LPCTSTR)wcStr);
			if (i == 0) {
				m_strFilePath1 = (LPCTSTR)wcStr;
			}
			if (i == 1) {
				m_strFilePath2 = (LPCTSTR)wcStr;
			}
		}
		InitFile();
		HANDLE hPos = CreateThread(NULL, 0, GetDiffPos, NULL, 0, NULL);  

		//ULONG64 ipos = GetDiffLine(m_uLine);
		//TRACE("Current ipos = %d \n", ipos);

		//DispCompare(m_iPage);
	}
	

	DragFinish(hDropInfo); //finish, free memery

	CDialogEx::OnDropFiles(hDropInfo);
}


string CCompareDlg::GetFilePath(void)
{
	CString szFilename = "";
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL);

	if (dlg.DoModal() == IDOK) {
		szFilename = dlg.GetPathName();
	}

	string strFile(szFilename.GetBuffer());
	return strFile;
}


void CCompareDlg::OnBnClickedButOpenfile1()
{
	m_strFilePath1 = GetFilePath();
	SetDlgItemText(IDC_EDFile1, m_strFilePath1.c_str());

	if (!OpenFile1()) {
		MessageBox("OpenFile1() Error!");
		return;
	}
}


void CCompareDlg::OnBnClickedButOpenfile2()
{
	m_strFilePath2 = GetFilePath();
	SetDlgItemText(IDC_EDFile2, m_strFilePath2.c_str());

	if (!OpenFile2()) {
		MessageBox("OpenFile2() Error!");
		return;
	}
}


BOOL CCompareDlg::OpenFile1(void)
{
	m_hFile1 = CreateFile(m_strFilePath1.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if(m_hFile1 == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	m_hFileMapping1 = CreateFileMapping(m_hFile1, 0, PAGE_READONLY, 0, 0, 0);
	if (m_hFileMapping1 == INVALID_HANDLE_VALUE) {
		return FALSE; 
	}

	return TRUE;
}


BOOL CCompareDlg::OpenFile2(void)
{
	m_hFile2 = CreateFile(m_strFilePath2.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if(m_hFile2 == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	m_hFileMapping2 = CreateFileMapping(m_hFile2, 0, PAGE_READONLY, 0, 0, 0);
	if (m_hFileMapping2 == INVALID_HANDLE_VALUE) {
		return FALSE; 
	}

	return TRUE;
}


CString CCompareDlg::GetFilePtr(DWORD dwOffset, DWORD dwLength, std::map<DWORD, LPBYTE> vFile, HANDLE hFileMapping)
{
	DWORD dwThreadId = GetCurrentThreadId();
	DWORD dwBaseOffs = dwOffset - dwOffset % m_dwAllocGranularity;
	DWORD dwDiff = dwOffset-dwBaseOffs;
	LPBYTE pPtr = NULL;

	std::map<DWORD, LPBYTE>::iterator it = vFile.find(dwThreadId);
	if(it != vFile.end()) {
		UnmapViewOfFile(it->second);
	}

	pPtr = (LPBYTE)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, dwBaseOffs, dwLength + dwDiff);

	if(it != vFile.end()) {
		it->second = pPtr;
	} else {
		vFile[dwThreadId] = pPtr;
	}
	pPtr = pPtr + dwDiff;
	CString str = FormatHexLine(pPtr, 10, dwOffset / 10);
	if (dwOffset != 0) {
		UnmapViewOfFile(pPtr - dwDiff);
	}

	return str;
}


CString CCompareDlg::FormatHexLine(LPBYTE pData, int nBytesInLine, ULONG64 uLineOffset)
{
	CString sResult;
	CString str;
	int i;

	str.Format(_T("%08X  "), uLineOffset);  //print the hex address
	sResult += str;

	for(i = 0; i < nBytesInLine; i++) {  //print hex data
		str.Format(_T("%02X "), pData[i]);
		sResult += str;
	}

	for(; i < 10; i++) {  //print some blanks if this isn't a full line
		str.Format(_T("   "));
		sResult += str;
	}

	sResult += _T(" ");  //print a gap between the hex and ascii

	for(i = 0; i < nBytesInLine; i++) {   //print the ascii
		BYTE c = pData[i];
		if(c < 32 || c > 128) c = '.';
		str.Format( _T("%c"), c);
		sResult += str;
	}

	for(; i < 10; i++) {   //print some blanks if this isn't a full line
		sResult += _T(" ");
	}

	return sResult;
}


void CCompareDlg::DispCompare(int cnt)
{
	m_ListFile1.ResetContent();
	m_ListFile2.ResetContent();

	if (cnt > m_uPages) {
		return;
	}
	
	LPBYTE lptr1 = NULL, lptr2 = NULL;
	CString str1 = "", str2 = "";
	for (ULONG64 i = cnt * 31; i < (cnt + 1) * 31; i++) {
		str1 = GetFilePtr(i * 10, 10, m_aViewStartPtrs1, m_hFileMapping1);
		str2 = GetFilePtr(i * 10, 10, m_aViewStartPtrs2, m_hFileMapping2);

		if (str1 == str2) {
			m_ListFile1.AddString(str1, RGB(0, 0, 0));
 			m_ListFile2.AddString(str2, RGB(0, 0, 0));
 		}
 		if (str1 != str2) {
 			m_ListFile1.AddString(str1, RGB(255, 0, 0));
 			m_ListFile2.AddString(str2, RGB(255, 0, 0));
 		}
	}
}


void CCompareDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int ipos = m_VScrollBar.GetScrollPos();
	if (m_ListFile1.GetCount() == 0 || m_ListFile2.GetCount() == 0) {
		return;
	}

	switch(nSBCode)
	{
// 	case SB_BOTTOM:  //�������ײ�
// 		ipos = 0;
// 		m_VScrollBar.SetScrollPos(0);
// 		break;
// 	case SB_TOP:   //����������
// 		ipos = 100;
// 		m_VScrollBar.SetScrollPos(100);
// 		break;
	case SB_LINEDOWN:  //���¹���һ��
		ipos++;
		m_iPage++;
		m_VScrollBar.SetScrollPos(ipos);
		DispCompare(m_iPage);
		TRACE("Now, the pos is %d  m_ipage = %d\n", ipos, m_iPage);
		break;
	case SB_LINEUP:  //���Ϲ���һ��
		ipos--;
		m_iPage--;
		m_VScrollBar.SetScrollPos(ipos);
		DispCompare(m_iPage);
		TRACE("Now, the pos is %d  m_ipage = %d\n", ipos, m_iPage);
		break;
	case SB_PAGEDOWN:  //���¹���һҳ
		break;
	case SB_PAGEUP:   //���Ϲ���һҳ
		break;
	case SB_THUMBPOSITION:    //����������λ��
		m_VScrollBar.SetScrollPos(nPos);
		DispCompare(nPos);
		TRACE("Now, the pos is %d ipage = %d\n", nPos, ipos);
		break;
	case SB_THUMBTRACK:
		break;
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CCompareDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_ListFile1.GetCount() == 0 || m_ListFile2.GetCount() == 0) {
		return FALSE;
	}

	if (zDelta == -120) {
		if (m_uPages <= m_iPage) {
			MessageBox("�����ļ���󳤶�", MB_OK);
			return FALSE;
		}

		//m_VScrollBar.SetScrollPos(ipos++);
		m_iPage = m_iPage + 5;
		DispCompare(m_iPage);
		TRACE("m_ipage = %d\n", m_iPage);
	}

	if (zDelta == 120) {
		if (m_iPage < 0) {
			MessageBox("�����ļ���С����", MB_OK);
			return FALSE;
		}
		//m_VScrollBar.SetScrollPos(ipos--);
		m_iPage = m_iPage - 5;
		DispCompare(m_iPage);
		TRACE("m_ipage = %d\n", m_iPage);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CCompareDlg::OnLbnSelchangeListfile1()
{
	int ipos1 = m_ListFile1.GetCurSel();
	m_ListFile2.SetCurSel(ipos1);
}


void CCompareDlg::OnLbnSelchangeListfile2()
{
	int ipos2 = m_ListFile2.GetCurSel();
	m_ListFile1.SetCurSel(ipos2);
}


void CCompareDlg::OnBnClickedButFinddiffNext()
{
	HANDLE hFindNext = CreateThread(NULL, 0, FindNextDiff, NULL, 0 ,NULL);
}


void CCompareDlg::OnBnClickedButFinddiffBack()
{
	HANDLE hFindBack = CreateThread(NULL, 0, FindBackDiff, NULL, 0 ,NULL);
}


void CCompareDlg::OnBnClickedButRelease()
{
	m_ListFile1.ResetContent();
	m_ListFile2.ResetContent();

	SetDlgItemText(IDC_EDFile1, _T(""));
	SetDlgItemText(IDC_EDFile2, _T(""));


	std::map<DWORD, LPBYTE>::iterator it1;
	for(it1 = m_aViewStartPtrs1.begin(); it1 != m_aViewStartPtrs1.end(); it1++) {
		if(it1->second != NULL)
			UnmapViewOfFile(it1->second);    
	}
	m_aViewStartPtrs1.clear();

	std::map<DWORD, LPBYTE>::iterator it2;
	for(it2 = m_aViewStartPtrs2.begin(); it2 != m_aViewStartPtrs2.end(); it2++) {
		if(it2->second != NULL)
			UnmapViewOfFile(it2->second);    
	}
	m_aViewStartPtrs2.clear();

	CloseHandle(m_hFileMapping1);
	CloseHandle(m_hFileMapping2);
	CloseHandle(m_hFile1);
	CloseHandle(m_hFile2);

	m_hFile1 = INVALID_HANDLE_VALUE;
	m_hFile2= INVALID_HANDLE_VALUE;
	m_hFileMapping1 = INVALID_HANDLE_VALUE;
	m_hFileMapping2 = INVALID_HANDLE_VALUE;

	m_isFile2 = false;
	m_iPage = 0;
	m_uLine = 0;
}


void CCompareDlg::InitFile(void)
{
	if (!OpenFile1()) {
		return;
	}
	if (!OpenFile2()) {
		return;
	}

	LARGE_INTEGER size;
	GetFileSizeEx(m_hFile1, &size);	
	m_uFileLength1 = size.QuadPart; 
	GetFileSizeEx(m_hFile2, &size);
	m_uFileLength2 = size.QuadPart;

	if (m_uFileLength1 % 10 == 0) {
		m_uFileLine1 = m_uFileLength1 / 10;
	} else {
		m_uFileLine1 = m_uFileLength1 / 10;
	}

	if (m_uFileLength2 % 10 == 0) {
		m_uFileLine2 = m_uFileLength2 / 10;
	} else {
		m_uFileLine2 = m_uFileLength2 / 10;
	}

	m_uFileLine1--;
	m_uFileLine2--;

	m_uLine = m_uFileLine1 < m_uFileLine2 ? m_uFileLine1 : m_uFileLine2;

	int ipage = 0;
	if (m_uFileLength1 > m_uFileLength2) {
		if (m_uFileLength1 % 310 == 0) {
			ipage = m_uFileLength2 / 310;
		} else {
			ipage = m_uFileLength2 / 310 + 1;
		}
	}
	if (m_uFileLength2 > m_uFileLength1) {
		if (m_uFileLength2 % 310 == 0) {
			ipage = m_uFileLength1 / 310;
		} else {
			ipage = m_uFileLength1 / 310 + 1;
		}
	}

	if (m_uFileLength1 == m_uFileLength2) {
		if (m_uFileLength1 % 310 == 0) {
			ipage = m_uFileLength1 / 310;
		} else {
			ipage = m_uFileLength1 / 310 + 1;
		}
	}

	m_uPages = ipage - 2;

	if (ipage > 32000) {
		m_VScrollBar.SetScrollRange(0, 32000); //scrollbar���Χ0-32000
	} else {
		m_VScrollBar.SetScrollRange(0, m_uPages);
	}
}


DWORD WINAPI GetDiffPos(LPVOID)
{
	ULONG64 iLine = pDlg->m_uLine;
	LPBYTE lptr1 = NULL, lptr2 = NULL;
	CString str1 = "", str2 = "";

	for (ULONG64 i = 0; i < iLine; i++) {
		str1 = pDlg->GetFilePtr(i * 10, 10, pDlg->m_aViewStartPtrs1, pDlg->m_hFileMapping1);
		str2 = pDlg->GetFilePtr(i * 10, 10, pDlg->m_aViewStartPtrs2, pDlg->m_hFileMapping2);

		if (str1 != str2) {
			TRACE("Current line is %d\n", i);
			pDlg->m_iDiffPos = i;
			pDlg->m_iPage = i / 31;
			pDlg->DispCompare(pDlg->m_iPage);
			return 0;
		}
		TRACE("Current line is %d\n", i);
	}
	pDlg->m_iDiffPos = 0;
	return 0;
}

DWORD WINAPI FindNextDiff(LPVOID)
{
	LPBYTE lptr1 = NULL, lptr2 = NULL;
	CString str1 = "", str2 = "";
	for (ULONG64 i = (pDlg->m_iPage+1) * 31; i <= pDlg->m_uLine; i++) {
		str1 = pDlg->GetFilePtr(i * 10, 10, pDlg->m_aViewStartPtrs1, pDlg->m_hFileMapping1);
		str2 = pDlg->GetFilePtr(i * 10, 10, pDlg->m_aViewStartPtrs2, pDlg->m_hFileMapping2);

		if (str1 != str2) {
			pDlg->m_ListFile1.ResetContent();
			pDlg->m_ListFile2.ResetContent();

			pDlg->m_ListFile1.AddString(str1, RGB(255, 0, 0));
			pDlg->m_ListFile2.AddString(str2, RGB(255, 0, 0));

			pDlg->m_iPage = i / 31;
			pDlg->DispCompare(pDlg->m_iPage);

			return 0;
		}
	}
	return 0;
}


//������һ����ͬ
DWORD WINAPI FindBackDiff(LPVOID)
{
	LPBYTE lptr1 = NULL, lptr2 = NULL;
	CString str1 = "", str2 = "";
	for (INT i = (pDlg->m_iPage - 1) * 31; i >= 0; i--) {
		str1 = pDlg->GetFilePtr(i * 10, 10, pDlg->m_aViewStartPtrs1, pDlg->m_hFileMapping1);
		str2 = pDlg->GetFilePtr(i * 10, 10, pDlg->m_aViewStartPtrs2, pDlg->m_hFileMapping2);

		if (str1 != str2) {
			pDlg->m_ListFile1.ResetContent();
			pDlg->m_ListFile2.ResetContent();

			pDlg->m_ListFile1.AddString(str1, RGB(255, 0, 0));
			pDlg->m_ListFile2.AddString(str2, RGB(255, 0, 0));

			pDlg->m_iPage = i / 31;
			pDlg->DispCompare(pDlg->m_iPage);

			return 0;
		}
	}
	return 0;
}