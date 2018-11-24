// GameWnd.cpp : implementation file
//

//#include "stdafx.h"
#include "mazegame.h"
#include "GameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GameWnd

IMPLEMENT_DYNCREATE(GameWnd, CFrameWnd)

GameWnd::GameWnd()
{
	Create(NULL,"´´½¨´°¿Ú");
}

GameWnd::~GameWnd()
{
}


BEGIN_MESSAGE_MAP(GameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(GameWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GameWnd message handlers
