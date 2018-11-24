
// CompareDlg.h : ͷ�ļ�
//
#include <string>
#include <map>
#include "ColorListBox.h"
#include "afxwin.h"

using namespace std;

#pragma once

//typedef std::map<DWORD, LPBYTE> ViewStartFile;

// CCompareDlg �Ի���
class CCompareDlg : public CDialogEx
{
// ����
public:
	CCompareDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMPARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	string GetFilePath(void);

	string m_strFilePath1;
	string m_strFilePath2;

	HANDLE m_hFile1;
	HANDLE m_hFile2;
	HANDLE m_hFileMapping1;		  // Memory mapped object
	HANDLE m_hFileMapping2;
	DWORD m_dwAllocGranularity; // System allocation granularity  	  
	ULONG64 m_uFileLength1;		  // Size of the file.
	ULONG64 m_uFileLength2;
	std::map<DWORD, LPBYTE> m_aViewStartPtrs1; // Base of the view of the file.  
	std::map<DWORD, LPBYTE> m_aViewStartPtrs2; // Base of the view of the file.  

	afx_msg void OnBnClickedButOpenfile1();
	afx_msg void OnBnClickedButOpenfile2();

	CColorListBox m_ListFile1;
	CColorListBox m_ListFile2;

	BOOL OpenFile1(void);
	BOOL OpenFile2(void);
	CString GetFilePtr(DWORD dwOffset, DWORD dwLength, std::map<DWORD, LPBYTE> vFile, HANDLE hFileMapping);
	CString FormatHexLine(LPBYTE pData, int nBytesInLine, ULONG64 uLineOffset);
	void DispCompare(int cnt);
	CScrollBar m_VScrollBar;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLbnSelchangeListfile1();
	afx_msg void OnLbnSelchangeListfile2();
	int m_iPage;
	afx_msg void OnBnClickedButFinddiffNext();
	afx_msg void OnBnClickedButFinddiffBack();
	afx_msg void OnBnClickedButRelease();
	bool m_isFile2;
	void InitFile(void);
	//ULONG64 GetDiffLine(ULONG64 iLine);
	ULONG64 m_uFileLine1;
	ULONG64 m_uFileLine2;
	ULONG64 m_uLine;
	ULONG64 m_uPages;
	ULONG64 m_iDiffPos;
};
