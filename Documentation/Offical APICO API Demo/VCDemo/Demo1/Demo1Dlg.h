// Demo1Dlg.h : header file
//

#if !defined(AFX_DEMO1DLG_H__0BF34F4D_5441_11D5_B5A0_9B983C690D43__INCLUDED_)
#define AFX_DEMO1DLG_H__0BF34F4D_5441_11D5_B5A0_9B983C690D43__INCLUDED_

#include "Graph.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemo1Dlg dialog

class CDemo1Dlg : public CDialog
{
// Construction
public:
	CGraph m_cG;
	int InitBoard();
	void CreateTab();

	CDemo1Dlg(CWnd* pParent = NULL);	// standard constructor
	~CDemo1Dlg();
// Dialog Data
	//{{AFX_DATA(CDemo1Dlg)
	enum { IDD = IDD_DEMO1_DIALOG };
	CTabCtrl	m_cTabSet;
	CString	m_sXAxes;
	CString	m_sXAccel;
	CString	m_sXHighSpeed;
	CString	m_sXLowSpeed;
	CString	m_sXStep;
	CString	m_sYAccel;
	CString	m_sYAxes;
	CString	m_sYHighSpeed;
	CString	m_sYLowSpeed;
	CString	m_sYStep;
	CString	m_sArcR;
	CString	m_sArcVAccel;
	CString	m_sArcVHighSpeed;
	CString	m_sArcVLowSpeed;
	CString	m_sArcXAxes;
	CString	m_sArcXCen;
	CString	m_sArcYAxes;
	CString	m_sArcYCen;
	CString	m_sLAccel;
	CString	m_sLHighSpeed;
	CString	m_sLLowSpeed;
	CString	m_sLXAxes;
	CString	m_sLXStep;
	CString	m_sLYAxes;
	CString	m_sLYStep;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo1Dlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnShow();
	afx_msg void OnSelchangeTabSet(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioXaxes();
	afx_msg void OnRadioYaxes();
	afx_msg void OnRadioCon();
	afx_msg void OnRadioFast();
	afx_msg void OnRadioPmove();
	afx_msg void OnRadioVmove();
	afx_msg void OnRadioAxes1();
	afx_msg void OnRadioAxes2();
	afx_msg void OnBtnStartmove();
	afx_msg void OnBtnSuddenstop();
	afx_msg void OnBtnDescendstop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBtnReset();
	afx_msg void OnRadioArcCon();
	afx_msg void OnRadioArcFast();
	afx_msg void OnRadioLineCon();
	afx_msg void OnRadioLineFast();
	afx_msg void OnCardinfo();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitParam();
	void SetRadioButton();
	int m_iSelect;		//标签选择
	int m_iAxes;		//保存单轴为X或Y的单选按钮ID号
	int m_iConFast;		//保存常速或快速的单选按钮ID号
	int m_iPVMove;		//保存点位或连续的单选按钮ID号
	int m_iAxesNum;		//保存单轴或两轴的单选按钮ID号
	int m_iArcConFast;	//保存圆弧为常速或快速的单选按钮ID号
	int m_iLineConFast;	//保存直线插补为常速或快速的单选按钮ID号
	void SetTabContentStatus(int TabID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO1DLG_H__0BF34F4D_5441_11D5_B5A0_9B983C690D43__INCLUDED_)
