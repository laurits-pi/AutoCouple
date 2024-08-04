// Demo4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo4.h"
#include "Demo4Dlg.h"
#include "Mpc08D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


long glTotalCards;
long glTotalAxes;
CString glLibCString;
CString glSysCString;
CString glCardver1;
CString glCardver2;
CString glCardver3;
CString glCardver4;
CString glCardver5;
CString glCardver6;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo4Dlg dialog

CDemo4Dlg::CDemo4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemo4Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemo4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemo4Dlg)
	DDX_Control(pDX, IDC_LIST_SHOW, m_ListShow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemo4Dlg, CDialog)
	//{{AFX_MSG_MAP(CDemo4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo4Dlg message handlers

BOOL CDemo4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	


	// TODO: Add extra initialization here
	int Rtn,BoardNum;
	CString str,Text1,Text2;

	InitBoard();
	Rtn=OnCardinfo();
	BoardNum=get_board_num();
	if(Rtn==1)
		AfxMessageBox("硬件版本不兼容,卡号不存在!");

	m_ListShow.AddString(glLibCString);
	m_ListShow.AddString(glSysCString);

	Text1="卡号: ";
	Text2="     版本号: ";
	if(BoardNum==1)
	{	
		str=Text1+Text2+glCardver1;
		m_ListShow.AddString(str);
	}
	else if(BoardNum==2)
	{
		str=Text1+Text2+glCardver1;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver2;
	    m_ListShow.AddString(str);
	}
	else if(BoardNum==3)
	{
		str=Text1+Text2+glCardver1;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver2;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver3;
	    m_ListShow.AddString(str);
	}
	else if(BoardNum==4)
	{
		str=Text1+Text2+glCardver1;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver2;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver3;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver4;
	    m_ListShow.AddString(str);
	}
	else if(BoardNum==5)
	{
		str=Text1+Text2+glCardver1;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver2;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver3;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver4;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver5;
	    m_ListShow.AddString(str);
	}
	else if(BoardNum==6)
	{
		str=Text1+Text2+glCardver1;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver2;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver3;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver4;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver5;
	    m_ListShow.AddString(str);
		str=Text1+Text2+glCardver6;
	    m_ListShow.AddString(str);
	}
	else
		m_ListShow.AddString("检查不到卡或多于六张卡");

	

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemo4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemo4Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemo4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CDemo4Dlg::InitBoard()
{
	int Rtn;//,i;
	CString str;

	//初始化板卡
	Rtn=auto_set();		//自动设置
	if(Rtn<=0 )
	{   
		if(Rtn==-1)
		AfxMessageBox("检测不到卡!",MB_OK);
		if(Rtn==-10)
		AfxMessageBox("使用多卡搭配不当!",MB_OK);
	}
	else
	{
		str.Format("轴数=%d",Rtn);
//		AfxMessageBox(str);
	}
	glTotalAxes = Rtn;

	Rtn=init_board();		//初始化
	if(Rtn<=0)
	{
		if(Rtn == -5)
		{
			AfxMessageBox("动态链接库或驱动程序的版本错误",MB_OK);
		}
		else if(Rtn == -6)
		{
			AfxMessageBox("硬件版本错误",MB_OK);
		}
		else
		{
			AfxMessageBox("初始化错误!",MB_OK);
		}
	}
	else
	{
		str.Format("卡数=%d",Rtn);
//		AfxMessageBox(str);
	}
	glTotalCards = Rtn;
	return 0;

}

int CDemo4Dlg::OnCardinfo()
{

	CString sInfo,str,str1,str2,str3,str4;
	long nType,ma[3],mi1[3],mi2[3],Rtn,i;
	long cardno1,cardno2,cardno3,cardno4;
	sInfo.Format("计算机内插有 %d 张板卡。共有 %d 根轴。\n",glTotalCards,glTotalAxes);
	Rtn = get_lib_ver(&ma[0], &mi1[0], &mi2[0]);
	Rtn = get_sys_ver(&ma[1], &mi1[1], &mi2[1]);
	Rtn = get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
	str.Format("板卡类型号     ：%d\n",nType);
	sInfo = sInfo + str;
	str.Format("函数库版本号   ：%d.%d.%d\n",ma[0], mi1[0], mi2[0]);
	glLibCString=str;
	sInfo = sInfo + str;
	str.Format("驱动程序版本号 ：%d.%d.%d\n",ma[1], mi1[1], mi2[1]);
	glSysCString=str;
	
	sInfo = sInfo + str;
	str.Format("硬件版本号     ：%d.%d.%d\n",ma[2], mi1[2], mi2[2]);
	sInfo = sInfo + str;
	if(ma[2]<2||ma[2]==255)
//		return 1;
//  
////	get_cardno(&cardno1,&cardno2,&cardno3,&cardno4);
//	
//	str1.Format("%d",cardno1);
//	str2.Format("%d",cardno2);
//	str3.Format("%d",cardno3);
//	str4.Format("%d",cardno4);
//	
//	glCardno1=str1;
//	glCardno2=str2;
//	glCardno3=str3;
 //  glCardno4=str4;
	Rtn=get_board_num();
	if(Rtn==1)
	{
		get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver1.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
	}
	else if(Rtn==2)
	{
		get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver1.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(2, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver2.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
	}
	else if(Rtn==3)
	{
		get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver1.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(2, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver2.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(3, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver3.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
	}
   else if(Rtn==4)
	{
		get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver1.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(2, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver2.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(3, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver3.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(4, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver4.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
	}

    else if(Rtn==5)
	{
		get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver1.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(2, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver2.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(3, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver3.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(4, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver4.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(5, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver5.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
	}
	 else if(Rtn==6)
	{
		get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver1.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(2, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver2.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(3, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver3.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(4, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver4.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(3, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver5.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
		get_card_ver(4, &nType, &ma[2], &mi1[2], &mi2[2]);
		glCardver6.Format("%d.%d.%d",ma[2], mi1[2], mi2[2]);
	}
	for(i = 1;i<=glTotalAxes;i++)
	{
		sudden_stop(i);
	}
	
	for(i = 1;i<= glTotalAxes;i++)
	{
		reset_pos(i);
	}

	return 0;

}
