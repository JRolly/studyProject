#if !defined(AFX_GAMEWND_H__203AE730_C544_4616_B4C4_036BD1B5C546__INCLUDED_)
#define AFX_GAMEWND_H__203AE730_C544_4616_B4C4_036BD1B5C546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GameWnd frame

class GameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(GameWnd)
public:
	GameWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GameWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~GameWnd();

	// Generated message map functions
	//{{AFX_MSG(GameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEWND_H__203AE730_C544_4616_B4C4_036BD1B5C546__INCLUDED_)
