// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testmpc07.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_sPara1 = _T("");
	m_sPara2 = _T("");
	m_sPara3 = _T("");
	m_sPara4 = _T("");
	m_sPara5 = _T("");
	m_sPara6 = _T("");
	m_sPara7 = _T("");
	m_sPara8 = _T("");
	//}}AFX_DATA_INIT
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Text(pDX, IDC_EDIT1, m_sPara1);
	DDX_Text(pDX, IDC_EDIT2, m_sPara2);
	DDX_Text(pDX, IDC_EDIT3, m_sPara3);
	DDX_Text(pDX, IDC_EDIT4, m_sPara4);
	DDX_Text(pDX, IDC_EDIT5, m_sPara5);
	DDX_Text(pDX, IDC_EDIT6, m_sPara6);
	DDX_Text(pDX, IDC_EDIT7, m_sPara7);
	DDX_Text(pDX, IDC_EDIT8, m_sPara8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers
