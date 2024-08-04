// Demo4.h : main header file for the DEMO4 application
//

#if !defined(AFX_DEMO4_H__70AE11B5_7250_4E0E_AF43_62FB3F52ABBA__INCLUDED_)
#define AFX_DEMO4_H__70AE11B5_7250_4E0E_AF43_62FB3F52ABBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemo4App:
// See Demo4.cpp for the implementation of this class
//

class CDemo4App : public CWinApp
{
public:
	CDemo4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemo4App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO4_H__70AE11B5_7250_4E0E_AF43_62FB3F52ABBA__INCLUDED_)
