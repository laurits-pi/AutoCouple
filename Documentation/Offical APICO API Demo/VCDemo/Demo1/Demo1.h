// Demo1.h : main header file for the DEMO1 application
//

#if !defined(AFX_DEMO1_H__0BF34F4B_5441_11D5_B5A0_9B983C690D43__INCLUDED_)
#define AFX_DEMO1_H__0BF34F4B_5441_11D5_B5A0_9B983C690D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Demo1Dlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDemo1App:
// See Demo1.cpp for the implementation of this class
//

class CDemo1App : public CWinApp
{
public:
	CDemo1App();
	CDemo1Dlg *m_pMainDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO1_H__0BF34F4B_5441_11D5_B5A0_9B983C690D43__INCLUDED_)
