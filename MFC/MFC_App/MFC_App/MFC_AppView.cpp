
// MFC_AppView.cpp : CMFC_AppView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFC_App.h"
#endif

#include "MFC_AppDoc.h"
#include "MFC_AppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_AppView

IMPLEMENT_DYNCREATE(CMFC_AppView, CView)

BEGIN_MESSAGE_MAP(CMFC_AppView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC_AppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFC_AppView ����/����

CMFC_AppView::CMFC_AppView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFC_AppView::~CMFC_AppView()
{
}

BOOL CMFC_AppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFC_AppView ����

void CMFC_AppView::OnDraw(CDC* /*pDC*/)
{
	CMFC_AppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFC_AppView ��ӡ


void CMFC_AppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC_AppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFC_AppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFC_AppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMFC_AppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC_AppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC_AppView ���

#ifdef _DEBUG
void CMFC_AppView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_AppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_AppDoc* CMFC_AppView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_AppDoc)));
	return (CMFC_AppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_AppView ��Ϣ�������
