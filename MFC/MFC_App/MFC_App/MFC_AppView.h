
// MFC_AppView.h : CMFC_AppView ��Ľӿ�
//

#pragma once


class CMFC_AppView : public CView
{
protected: // �������л�����
	CMFC_AppView();
	DECLARE_DYNCREATE(CMFC_AppView)

// ����
public:
	CMFC_AppDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFC_AppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFC_AppView.cpp �еĵ��԰汾
inline CMFC_AppDoc* CMFC_AppView::GetDocument() const
   { return reinterpret_cast<CMFC_AppDoc*>(m_pDocument); }
#endif

