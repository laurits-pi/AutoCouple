#if !defined(AFX_EDITDLG_H__C725243F_A73D_435A_AF17_DD8C1A9AACB7__INCLUDED_)
#define AFX_EDITDLG_H__C725243F_A73D_435A_AF17_DD8C1A9AACB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	CEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_DLG_EDIT };
	CString	m_sPara1;
	CString	m_sPara2;
	CString	m_sPara3;
	CString	m_sPara4;
	CString	m_sPara5;
	CString	m_sPara6;
	CString	m_sPara7;
	CString	m_sPara8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__C725243F_A73D_435A_AF17_DD8C1A9AACB7__INCLUDED_)
