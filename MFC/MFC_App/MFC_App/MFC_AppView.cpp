
// MFC_AppView.cpp : CMFC_AppView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC_AppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFC_AppView 构造/析构

CMFC_AppView::CMFC_AppView()
{
	// TODO: 在此处添加构造代码

}

CMFC_AppView::~CMFC_AppView()
{
}

BOOL CMFC_AppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC_AppView 绘制

void CMFC_AppView::OnDraw(CDC* /*pDC*/)
{
	CMFC_AppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFC_AppView 打印


void CMFC_AppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC_AppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC_AppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC_AppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMFC_AppView 诊断

#ifdef _DEBUG
void CMFC_AppView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_AppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_AppDoc* CMFC_AppView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_AppDoc)));
	return (CMFC_AppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_AppView 消息处理程序
