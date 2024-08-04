// TestMPC07.h : main header file for the TESTMPC07 application
//

#if !defined(AFX_TESTMPC07_H__0540C707_5D2B_4CD0_BFCC_67099E353808__INCLUDED_)
#define AFX_TESTMPC07_H__0540C707_5D2B_4CD0_BFCC_67099E353808__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestMPC07App:
// See TestMPC07.cpp for the implementation of this class
//

class CTestMPC07App : public CWinApp
{
public:
	CTestMPC07App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMPC07App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestMPC07App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMPC07_H__0540C707_5D2B_4CD0_BFCC_67099E353808__INCLUDED_)
