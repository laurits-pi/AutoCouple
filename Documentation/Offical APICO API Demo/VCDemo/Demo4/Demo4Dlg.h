// Demo4Dlg.h : header file
//

#if !defined(AFX_DEMO4DLG_H__F842D20E_A4F7_43AD_84F9_A464C38D1614__INCLUDED_)
#define AFX_DEMO4DLG_H__F842D20E_A4F7_43AD_84F9_A464C38D1614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemo4Dlg dialog

class CDemo4Dlg : public CDialog
{
// Construction
public:
	int OnCardinfo();
	int InitBoard();
	CDemo4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemo4Dlg)
	enum { IDD = IDD_DEMO4_DIALOG };
	CListBox	m_ListShow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemo4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO4DLG_H__F842D20E_A4F7_43AD_84F9_A464C38D1614__INCLUDED_)
