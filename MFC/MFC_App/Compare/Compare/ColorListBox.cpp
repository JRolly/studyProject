// ColorListBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColorListBox.h"


// CColorListBox

IMPLEMENT_DYNAMIC(CColorListBox, CListBox)

CColorListBox::CColorListBox()
{

}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CColorListBox ��Ϣ�������




void CColorListBox::DrawItem(LPDRAWITEMSTRUCT  lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����
	if (lpDrawItemStruct->itemID == -1) 
	{
		DrawFocusRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
		return;
	}

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	COLORREF clrOld;
	CString sText;

	// get color info from item data
	COLORREF clrNew = (COLORREF)(lpDrawItemStruct->itemData);

	// item selected ?
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush brush(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
	}

	// item deselected ?
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&	
		(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		CBrush brush(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
	}	 	

	// item has focus ?
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && 
		(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem); 
	}

	// lost focus ?
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) &&	
		!(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem); 
	}

	// set the background mode to TRANSPARENT
	int nBkMode = pDC->SetBkMode(TRANSPARENT);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		clrOld = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	else 
		if (lpDrawItemStruct->itemState & ODS_DISABLED)
			clrOld = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		else
			clrOld = pDC->SetTextColor(clrNew);

	// get item text
	GetText(lpDrawItemStruct->itemID, sText);
	CRect rect = lpDrawItemStruct->rcItem;

	// text format
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
		nFormat |= DT_EXPANDTABS;

	// draw the text
	pDC->DrawText(sText, -1, &rect, nFormat);

	// restore old values
	pDC->SetTextColor(clrOld); 
	pDC->SetBkMode(nBkMode);
}


void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT  lpMeasureItemStruct)
{

	// TODO:  ������Ĵ�����ȷ��ָ����Ĵ�С
	lpMeasureItemStruct->itemHeight = ::GetSystemMetrics(SM_CYMENUCHECK);
}

int CColorListBox::AddString(LPCTSTR lpszItem, COLORREF itemColor)
{
	// Add the string to the list box
	int nIndex = CListBox::AddString(lpszItem);

	// save color data
	if (nIndex >= 0)
		SetItemData(nIndex, itemColor);

	return nIndex;
}

void CColorListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{


	CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CColorListBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int x = pt.x;
	int y = pt.y;

	if (zDelta > 0) {
		int delta = zDelta;
	}

	TRACE("now the pos is x = %d y = %d  zDelta = %d\n", x, y, zDelta);

	return CListBox::OnMouseWheel(nFlags, zDelta, pt);
}