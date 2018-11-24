// GameApp.cpp: implementation of the GameApp class.
//
//////////////////////////////////////////////////////////////////////

#include "mazeGame.h"
#include "mazegame.h"
#include "GameApp.h"
#include "GameWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
GameApp myApp;
BOOL GameApp::InitInstance()
{
	m_pMainWnd = new GAmeWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
}
GameApp::GameApp()
{

}

GameApp::~GameApp()
{

}
