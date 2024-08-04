// TestMPC07Dlg.h : header file
//

#if !defined(AFX_TESTMPC07DLG_H__CB70BB4E_BC63_4BF2_8E75_C439F250CE06__INCLUDED_)
#define AFX_TESTMPC07DLG_H__CB70BB4E_BC63_4BF2_8E75_C439F250CE06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestMPC07Dlg dialog

class CTestMPC07Dlg : public CDialog
{
// Construction
public:
	int m_iIndex;
	long m_lPara[10];
	double m_dbPara[10];
	CString m_sFunction;
	int InitListCtrl();
	int m_iOffset;
	int m_iOutdata;
	int m_iIndata;
	int InitMPC07();
	CTestMPC07Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestMPC07Dlg)
	enum { IDD = IDD_TESTMPC07_DIALOG };
	CListCtrl	m_ListFunction;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMPC07Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestMPC07Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickListMpc07Function(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListMpc07Function(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnStartMove();
	afx_msg void OnBtnDecelStop();
	afx_msg void OnBtnSuddenStop();
	afx_msg void OnCardinfo();
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMPC07DLG_H__CB70BB4E_BC63_4BF2_8E75_C439F250CE06__INCLUDED_)
