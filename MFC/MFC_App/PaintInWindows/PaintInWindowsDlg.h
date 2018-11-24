
// PaintInWindowsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


#define POINT_COUNT 100

// CPaintInWindowsDlg �Ի���
class CPaintInWindowsDlg : public CDialogEx
{
// ����
public:
	CPaintInWindowsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PAINTINWINDOWS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	int m_nzValues[POINT_COUNT];

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picDraw;

	void DrawWave(CDC *pDC, CRect &rectPicture);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
