#if !defined(AFX_GRAPH_H__0BF34F55_5441_11D5_B5A0_9B983C690D43__INCLUDED_)
#define AFX_GRAPH_H__0BF34F55_5441_11D5_B5A0_9B983C690D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Graph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraph dialog

class CGraph : public CDialog
{
// Construction
public:
	CGraph(CWnd* pParent = NULL);   // standard constructor
	~CGraph();
// Dialog Data
	//{{AFX_DATA(CGraph)
	enum { IDD = IDD_G };
	CString	m_sMsgPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraph)
	afx_msg void OnPaint();
	afx_msg void OnCancel();
	afx_msg void OnBtnClear();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bShowGraph;	//ͼ�δ����Ƿ���ʾ
	int m_bInitOK;		//��ʼ���Ƿ����
	double m_lfFactor;	//��ͼ����
private:
	int m_iLastPosX;	//��һ��λ��
	int m_iLastPosY;

	int m_CenX;			//����ԭ��
	int m_CenY;
public:
	void ClearAll();
	void DrawAxes();
	void MoveToPos(long x,long y);
	void LineToPos(long x,long y);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__0BF34F55_5441_11D5_B5A0_9B983C690D43__INCLUDED_)
