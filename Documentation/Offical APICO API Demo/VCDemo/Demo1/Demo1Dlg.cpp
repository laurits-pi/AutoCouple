// Demo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo1.h"
#include "Demo1Dlg.h"

#include "mpc08D.h"
#include "Graph.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long glTotalCards;
long glTotalAxes;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_sCardInfo;
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
	m_sCardInfo = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_CARDINFO, m_sCardInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo1Dlg dialog

CDemo1Dlg::CDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemo1Dlg)
	m_sXAxes = _T("");
	m_sXAccel = _T("");
	m_sXHighSpeed = _T("");
	m_sXLowSpeed = _T("");
	m_sXStep = _T("");
	m_sYAccel = _T("");
	m_sYAxes = _T("");
	m_sYHighSpeed = _T("");
	m_sYLowSpeed = _T("");
	m_sYStep = _T("");
	m_sArcR = _T("");
	m_sArcVAccel = _T("");
	m_sArcVHighSpeed = _T("");
	m_sArcVLowSpeed = _T("");
	m_sArcXAxes = _T("");
	m_sArcXCen = _T("");
	m_sArcYAxes = _T("");
	m_sArcYCen = _T("");
	m_sLAccel = _T("");
	m_sLHighSpeed = _T("");
	m_sLLowSpeed = _T("");
	m_sLXAxes = _T("");
	m_sLXStep = _T("");
	m_sLYAxes = _T("");
	m_sLYStep = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iSelect=0;
}
CDemo1Dlg::~CDemo1Dlg()
{
}
void CDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemo1Dlg)
	DDX_Control(pDX, IDC_TAB_SET, m_cTabSet);
	DDX_Text(pDX, IDC_EDIT_XAXES, m_sXAxes);
	DDX_Text(pDX, IDC_EDIT_XACCEL, m_sXAccel);
	DDX_Text(pDX, IDC_EDIT_XHIGHSPEED, m_sXHighSpeed);
	DDX_Text(pDX, IDC_EDIT_XLOWSPEED, m_sXLowSpeed);
	DDX_Text(pDX, IDC_EDIT_XSTEP, m_sXStep);
	DDX_Text(pDX, IDC_EDIT_YACCEL, m_sYAccel);
	DDX_Text(pDX, IDC_EDIT_YAXES, m_sYAxes);
	DDX_Text(pDX, IDC_EDIT_YHIGHSPEED, m_sYHighSpeed);
	DDX_Text(pDX, IDC_EDIT_YLOWSPEED, m_sYLowSpeed);
	DDX_Text(pDX, IDC_EDIT_YSTEP, m_sYStep);
	DDX_Text(pDX, IDC_EDIT_ARC_R, m_sArcR);
	DDX_Text(pDX, IDC_EDIT_ARC_VACCEL, m_sArcVAccel);
	DDX_Text(pDX, IDC_EDIT_ARC_VHIGHSPEED, m_sArcVHighSpeed);
	DDX_Text(pDX, IDC_EDIT_ARC_VLOWSPEED, m_sArcVLowSpeed);
	DDX_Text(pDX, IDC_EDIT_ARC_XAXES, m_sArcXAxes);
	DDX_Text(pDX, IDC_EDIT_ARC_XCEN, m_sArcXCen);
	DDX_Text(pDX, IDC_EDIT_ARC_YAXES, m_sArcYAxes);
	DDX_Text(pDX, IDC_EDIT_ARC_YCEN, m_sArcYCen);
	DDX_Text(pDX, IDC_EDIT_LACCEL, m_sLAccel);
	DDX_Text(pDX, IDC_EDIT_LHIGHSPEED, m_sLHighSpeed);
	DDX_Text(pDX, IDC_EDIT_LLOWSPEED, m_sLLowSpeed);
	DDX_Text(pDX, IDC_EDIT_LXAXES, m_sLXAxes);
	DDX_Text(pDX, IDC_EDIT_LXSTEP, m_sLXStep);
	DDX_Text(pDX, IDC_EDIT_LYAXES, m_sLYAxes);
	DDX_Text(pDX, IDC_EDIT_LYSTEP, m_sLYStep);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CDemo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SHOW, OnBtnShow)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SET, OnSelchangeTabSet)
	ON_BN_CLICKED(IDC_RADIO_XAXES, OnRadioXaxes)
	ON_BN_CLICKED(IDC_RADIO_YAXES, OnRadioYaxes)
	ON_BN_CLICKED(IDC_RADIO_CON, OnRadioCon)
	ON_BN_CLICKED(IDC_RADIO_FAST, OnRadioFast)
	ON_BN_CLICKED(IDC_RADIO_PMOVE, OnRadioPmove)
	ON_BN_CLICKED(IDC_RADIO_VMOVE, OnRadioVmove)
	ON_BN_CLICKED(IDC_RADIO_AXES1, OnRadioAxes1)
	ON_BN_CLICKED(IDC_RADIO_AXES2, OnRadioAxes2)
	ON_BN_CLICKED(IDC_BTN_STARTMOVE, OnBtnStartmove)
	ON_BN_CLICKED(IDC_BTN_SUDDENSTOP, OnBtnSuddenstop)
	ON_BN_CLICKED(IDC_BTN_DESCENDSTOP, OnBtnDescendstop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_RADIO_ARC_CON, OnRadioArcCon)
	ON_BN_CLICKED(IDC_RADIO_ARC_FAST, OnRadioArcFast)
	ON_BN_CLICKED(IDC_RADIO_LINE_CON, OnRadioLineCon)
	ON_BN_CLICKED(IDC_RADIO_LINE_FAST, OnRadioLineFast)
	ON_COMMAND(IDC_CARDINFO, OnCardinfo)
	ON_COMMAND(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo1Dlg message handlers

BOOL CDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	////////////////////////
	//初始化设备
	InitBoard();
	////////////////////////
	//创建图形显示窗口
	m_cG.Create(IDD_G,NULL);
	m_cG.ShowWindow(SW_HIDE);
	m_cG.m_bShowGraph=FALSE;
	OnBtnShow();
	////////////////////////
	//初始化运动参数设置
	InitParam();
	SetRadioButton();
	CreateTab();
	SetTabContentStatus(0);

	////////////////////////
	//启动定时器准备画图
	SetTimer(1,200,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CString sInfo,str;
	long nType,ma[3],mi1[3],mi2[3],Rtn,i;
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		sInfo.Format("计算机内插有 %d 张板卡。共有 %d 根轴。\n",glTotalCards,glTotalAxes);
	    if (glTotalCards <= 0)
		{
	        nType = -1;
		    for(i=0;i<3;i++)
			{
			    ma[i] = -1;
				mi1[i] = -1;
				mi2[i] = -1;
			}
		}
	    else
		{
	        Rtn = get_lib_ver(&ma[0], &mi1[0], &mi2[0]);
		    Rtn = get_sys_ver(&ma[1], &mi1[1], &mi2[1]);
			Rtn = get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
		}
		str.Format("板卡类型号     ：%d\n",nType);
	    sInfo = sInfo + str;
		str.Format("函数库版本号   ：%d.%d.%d\n",ma[0], mi1[0], mi2[0]);
	    sInfo = sInfo + str;
		str.Format("驱动程序版本号 ：%d.%d.%d\n",ma[1], mi1[1], mi2[1]);
		sInfo = sInfo + str;
		str.Format("硬件版本号     ：%d.%d.%d\n",ma[2], mi1[2], mi2[2]);
		sInfo = sInfo + str;
    
		for(i = 1;i<=glTotalAxes;i++)
		{
			sudden_stop(i);
		}
		
		for(i = 1;i<= glTotalAxes;i++)
		{
			reset_pos(i);
		}
		
		dlgAbout.m_sCardInfo = sInfo;//.GetDlgItem(IDC_CARDINFO)->SetWindowText(sInfo);
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

void CDemo1Dlg::OnPaint() 
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
HCURSOR CDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////
//初始化板卡
int CDemo1Dlg::InitBoard()
{
	int i;
/*	int Rtn;
	//////////////////
	//初始化板卡
	Rtn=auto_set();			//自动设置
	if(Rtn<=0 )
	{
		MessageBox("检测不到卡!");
	}
	glTotalAxes = Rtn;

	Rtn=init_board();		//初始化
	if(Rtn<=0)
	{
		MessageBox("初始化错误!");
	}
	glTotalCards = Rtn;
	return 0;
*/
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
		AfxMessageBox(str);
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
		AfxMessageBox(str);
	}
	glTotalCards = Rtn;
	for ( i=0;i<glTotalCards;i++)
	{
       set_card_alm_logic(i+1,0);
	}
	for ( i=0;i<glTotalAxes;i++)
	{
		set_alm_logic(i+1,0);
        set_el_logic(i+1,0);
		set_org_logic(i+1,0);
	}
	return 0;
}
/////////////////////////////////
//添加选项卡
void CDemo1Dlg::CreateTab()
{
	TCITEM curItem;
	curItem.mask=TCIF_TEXT;
	curItem.cchTextMax =10;
	curItem.pszText ="直线运动设置";
	m_cTabSet.InsertItem(0,&curItem);
	curItem.pszText ="直线插补设置";
	m_cTabSet.InsertItem(1,&curItem);
}

void CDemo1Dlg::OnBtnShow() 
{
	// TODO: Add your control notification handler code here
	
	/////////////////////////////////
	//图形显示窗口定位
	RECT tRect;
	m_cG.GetWindowRect(&tRect);
	m_cG.MoveWindow(0,0,tRect.right-tRect.left ,tRect.bottom-tRect.top,TRUE);

	if(m_cG.m_bShowGraph)	//若图形窗口已经显示，则隐藏
	{
		m_cG.ShowWindow(SW_HIDE);
		m_cG.m_bShowGraph=FALSE;
	}
	else					//若图形窗口已经隐藏，则显示
	{
		m_cG.ShowWindow(SW_SHOW);
		m_cG.m_bShowGraph=TRUE;
	}
}

/////////////////////////////////////////////////
//点取选项卡
void CDemo1Dlg::OnSelchangeTabSet(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//int iSelect;
	m_iSelect=m_cTabSet.GetCurSel();
	if(m_iSelect==1)		//若选择直线插补运动参数设置选项卡
	{
		SetTabContentStatus(1);
		GetDlgItem(IDC_FRAME_LINE)->SetWindowText("直线插补设置");
	}
	else				//若选择直线运动参数设置选项卡
	{
		SetTabContentStatus(0);
		GetDlgItem(IDC_FRAME_LINE)->SetWindowText("直线运动设置");
	}
	*pResult = m_iSelect;
}

//////////////////////////////////////////////////
//根据选项卡的选择显示或隐藏相应的运动参数设置控件
void CDemo1Dlg::SetTabContentStatus(int TabID)
{
	int iStatus,iStatus1,iStatus2;
	if(TabID==1)			//直线插补
	{
		iStatus=SW_HIDE;
		iStatus1=SW_HIDE;
		iStatus2=SW_SHOW;
	}
	else					//直线运动,TabID=0
	{
		iStatus=SW_SHOW;
		iStatus1=SW_HIDE;
		iStatus2=SW_HIDE;
	}

	//////////////////////////////////////////////////
	//选择了Tab1（直线运动参数设定）
	GetDlgItem(IDC_EDIT_XAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_XLOWSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_XHIGHSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_XACCEL)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_XSTEP)->ShowWindow(iStatus);

	GetDlgItem(IDC_EDIT_YAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_YLOWSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_YHIGHSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_YACCEL)->ShowWindow(iStatus);
	GetDlgItem(IDC_EDIT_YSTEP)->ShowWindow(iStatus);

	GetDlgItem(IDC_STATIC_XAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_XLOWSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_XHIGHSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_XACCEL)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_XSTEP)->ShowWindow(iStatus);

	GetDlgItem(IDC_STATIC_YAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_YLOWSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_YHIGHSPEED)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_YACCEL)->ShowWindow(iStatus);
	GetDlgItem(IDC_STATIC_YSTEP)->ShowWindow(iStatus);

	GetDlgItem(IDC_RADIO_AXES1)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_AXES2)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_XAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_YAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_CON)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_FAST)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_PMOVE)->ShowWindow(iStatus);
	GetDlgItem(IDC_RADIO_VMOVE)->ShowWindow(iStatus);

	GetDlgItem(IDC_GROUP_XYAXES)->ShowWindow(iStatus);
	GetDlgItem(IDC_GROUP_AXESNUM)->ShowWindow(iStatus);
	GetDlgItem(IDC_GROUP_SPEEDTYPE)->ShowWindow(iStatus);
	GetDlgItem(IDC_GROUP_MOVETYPE)->ShowWindow(iStatus);

	////////////////////////////////////////////////////
	//选择了Tab2（圆弧运动参数设定）
	GetDlgItem(IDC_STATIC_ARC_XAXES)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_YAXES)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_VLOWSPEED)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_VHIGHSPEED)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_VACCEL)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_XCEN)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_YCEN)->ShowWindow(iStatus1);
	GetDlgItem(IDC_STATIC_ARC_R)->ShowWindow(iStatus1);

	GetDlgItem(IDC_EDIT_ARC_XAXES)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_YAXES)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_VLOWSPEED)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_VHIGHSPEED)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_VACCEL)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_XCEN)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_YCEN)->ShowWindow(iStatus1);
	GetDlgItem(IDC_EDIT_ARC_R)->ShowWindow(iStatus1);

	GetDlgItem(IDC_GROUP_ARC_SPEEDTYPE)->ShowWindow(iStatus1);
	GetDlgItem(IDC_RADIO_ARC_CON)->ShowWindow(iStatus1);
	GetDlgItem(IDC_RADIO_ARC_FAST)->ShowWindow(iStatus1);

	//////////////////////////////////////////////////
	//选择了Tab3（直线插补运动参数设定）
	GetDlgItem(IDC_EDIT_LXAXES)->ShowWindow(iStatus2);
	GetDlgItem(IDC_EDIT_LXSTEP)->ShowWindow(iStatus2);
	GetDlgItem(IDC_EDIT_LYAXES)->ShowWindow(iStatus2);
	GetDlgItem(IDC_EDIT_LYSTEP)->ShowWindow(iStatus2);

	GetDlgItem(IDC_EDIT_LLOWSPEED)->ShowWindow(iStatus2);
	GetDlgItem(IDC_EDIT_LHIGHSPEED)->ShowWindow(iStatus2);
	GetDlgItem(IDC_EDIT_LACCEL)->ShowWindow(iStatus2);

	GetDlgItem(IDC_STATIC_LXAXES)->ShowWindow(iStatus2);
	GetDlgItem(IDC_STATIC_LXSTEP)->ShowWindow(iStatus2);
	GetDlgItem(IDC_STATIC_LYAXES)->ShowWindow(iStatus2);
	GetDlgItem(IDC_STATIC_LYSTEP)->ShowWindow(iStatus2);

	GetDlgItem(IDC_STATIC_LLOWSPEED)->ShowWindow(iStatus2);
	GetDlgItem(IDC_STATIC_LHIGHSPEED)->ShowWindow(iStatus2);
	GetDlgItem(IDC_STATIC_LACCEL)->ShowWindow(iStatus2);

	GetDlgItem(IDC_RADIO_LINE_CON)->ShowWindow(iStatus2);
	GetDlgItem(IDC_RADIO_LINE_FAST)->ShowWindow(iStatus2);

	GetDlgItem(IDC_GROUP_LINE_SPEEDTYPE)->ShowWindow(iStatus2);
}

void CDemo1Dlg::OnRadioXaxes() 
{
	// TODO: Add your control notification handler code here
	m_iAxes=IDC_RADIO_XAXES;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioYaxes() 
{
	// TODO: Add your control notification handler code here
	m_iAxes=IDC_RADIO_YAXES;
	SetRadioButton();
}

///////////////////////////////////
//设置单选按钮状态
void CDemo1Dlg::SetRadioButton()
{
	CheckRadioButton(IDC_RADIO_XAXES,IDC_RADIO_YAXES,m_iAxes);
	CheckRadioButton(IDC_RADIO_CON,IDC_RADIO_FAST,m_iConFast);
	CheckRadioButton(IDC_RADIO_PMOVE,IDC_RADIO_VMOVE,m_iPVMove);
	CheckRadioButton(IDC_RADIO_AXES1,IDC_RADIO_AXES2,m_iAxesNum);
	CheckRadioButton(IDC_RADIO_ARC_CON,IDC_RADIO_ARC_FAST,m_iArcConFast);
	CheckRadioButton(IDC_RADIO_LINE_CON,IDC_RADIO_LINE_FAST,m_iLineConFast);
}

void CDemo1Dlg::OnRadioCon() 
{
	// TODO: Add your control notification handler code here
	m_iConFast=IDC_RADIO_CON;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioFast() 
{
	// TODO: Add your control notification handler code here
	m_iConFast=IDC_RADIO_FAST;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioPmove() 
{
	// TODO: Add your control notification handler code here
	m_iPVMove=IDC_RADIO_PMOVE;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioVmove() 
{
	// TODO: Add your control notification handler code here
	m_iPVMove=IDC_RADIO_VMOVE;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioAxes1() 
{
	// TODO: Add your control notification handler code here
	m_iAxesNum=IDC_RADIO_AXES1;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioAxes2() 
{
	// TODO: Add your control notification handler code here
	m_iAxesNum=IDC_RADIO_AXES2;
	SetRadioButton();
}

////////////////////////////////
//初始化运动参数设定
void CDemo1Dlg::InitParam()
{
	m_iAxes=IDC_RADIO_XAXES;	//以X轴为单轴
	m_iConFast=IDC_RADIO_CON;	//直线运动常速运动
	m_iPVMove=IDC_RADIO_PMOVE;	//直线运动为点位运动
	m_iAxesNum=IDC_RADIO_AXES1;	//直线运动为单轴运动
	
	m_iArcConFast=IDC_RADIO_ARC_CON;	//圆弧运动为常速运动

	m_iLineConFast=IDC_RADIO_LINE_CON;	//直线插补为常速运动

	//////////////////////////////////////////////
	//直线运动
	m_sXAxes="1";				//X轴参数
	m_sXLowSpeed="2000";
	m_sXHighSpeed="4000";
	m_sXAccel="2000";
	m_sXStep="4000";

	m_sYAxes="2";				//Y轴参数
	m_sYLowSpeed="2000";
	m_sYHighSpeed="4000";
	m_sYAccel="2000";
	m_sYStep="4000";

	//////////////////////////////////////////////
	//直线插补
	m_sLXAxes="3";				//X轴轴号
	m_sLXStep="4000";			//X轴运动距离
	m_sLYAxes="4";				//Y轴轴号
	m_sLYStep="4000";			//Y轴运动距离
	m_sLLowSpeed="2000";
	m_sLHighSpeed="4000";
	m_sLAccel="2000";

	UpdateData(FALSE);
}

void CDemo1Dlg::OnBtnStartmove() 
{
	// TODO: Add your control notification handler code here
	int ChX,ChY;
	int StepX,StepY;
	int DirX,DirY;
//	int iSelect;

//	long CenX,CenY;
//	float Angle;

	//////////////////////////////////////////
	//设置绘图比例
	CString cStr="1";
	m_cG.GetDlgItemText(IDC_EDIT_FACTOR,cStr);
	m_cG.m_lfFactor=atof(cStr);

	//////////////////////////////////////////
	//读取运动参数
	UpdateData(TRUE);

//	if(m_bBatch) set_batch_flag(1);	//批处理模式
//	else set_batch_flag(0);
//	set_maxspeed(1,8191);
	
	m_iSelect=m_cTabSet.GetCurSel();
	if(m_iSelect==0)	//直线运动
	{
		ChX=atoi(m_sXAxes);	ChY=atoi(m_sYAxes);
		StepX=atoi(m_sXStep);	StepY=atoi(m_sYStep);
		if(StepX>=0)DirX=1;
			else DirX=-1;
		if(StepY>=0)DirY=1;
			else DirY=-1;

		set_maxspeed(ChX,atoi(m_sXHighSpeed));
		set_maxspeed(ChY,atoi(m_sYHighSpeed));

		set_conspeed(ChX,atoi(m_sXLowSpeed));
		set_conspeed(ChY,atoi(m_sYLowSpeed));

		set_profile(ChX,atoi(m_sXLowSpeed),atoi(m_sXHighSpeed),atoi(m_sXAccel),atoi(m_sXAccel));
		set_profile(ChY,atoi(m_sYLowSpeed),atoi(m_sYHighSpeed),atoi(m_sYAccel),atoi(m_sYAccel));

		if(m_iConFast==IDC_RADIO_CON)
		{
			if(m_iPVMove==IDC_RADIO_PMOVE)
			{
				if(m_iAxesNum==IDC_RADIO_AXES1)
				{
					if(m_iAxes==IDC_RADIO_XAXES)
						con_pmove(ChX,StepX);
					else
						con_pmove(ChY,StepY);
				}
				else
				{
					con_pmove2(ChX,StepX,ChY,StepY);
				}
			}
			else
			{
				if(m_iAxesNum==IDC_RADIO_AXES1)
				{
					if(m_iAxes==IDC_RADIO_XAXES)
						con_vmove(ChX,DirX);
					else
						con_vmove(ChY,DirY);
				}
				else
				{
					con_vmove2(ChX,DirX,ChY,DirY);
				}
			}
		}
		else
		{
			if(m_iPVMove==IDC_RADIO_PMOVE)
			{
				if(m_iAxesNum==IDC_RADIO_AXES1)
				{
					if(m_iAxes==IDC_RADIO_XAXES)
						fast_pmove(ChX,StepX);
					else
						fast_pmove(ChY,StepY);
				}
				else
				{
					fast_pmove2(ChX,StepX,ChY,StepY);
				}
			}
			else
			{
				if(m_iAxesNum==IDC_RADIO_AXES1)
				{
					if(m_iAxes==IDC_RADIO_XAXES)
						fast_vmove(ChX,DirX);
					else
					{
						fast_vmove(ChY,DirY);
					}
				}
				else
				{
					fast_vmove2(ChX,DirX,ChY,DirY);
				}
			}
		}
	}
	else	//直线插补运动
	{
		StepX=atoi(m_sLXStep);	StepY=atoi(m_sLYStep);
		ChX=atoi(m_sLXAxes);	ChY=atoi(m_sLYAxes);

		set_vector_conspeed(atof(m_sLLowSpeed));
		set_vector_profile(atof(m_sLLowSpeed),atof(m_sLHighSpeed),atof(m_sLAccel),atof(m_sLAccel));

		ChX=atoi(m_sLXAxes);	ChY=atoi(m_sLYAxes);

		if(m_iLineConFast==IDC_RADIO_LINE_CON)
		{
			con_line2(ChX,StepX,ChY,StepY);
		}
		else
		{
			fast_line2(ChX,StepX,ChY,StepY);
		}
	}
}

void CDemo1Dlg::OnBtnSuddenstop() 
{
	// TODO: Add your control notification handler code here
	CString strx,stry;
	
	if(m_iSelect==0)
	{
		strx=m_sXAxes;
		stry=m_sYAxes;
	}
	else//m_iSelect=1
	{
		strx=m_sLXAxes;
		stry=m_sLYAxes;
	}
	sudden_stop(atoi(strx));
	sudden_stop(atoi(stry));
}

void CDemo1Dlg::OnBtnDescendstop() 
{
	// TODO: Add your control notification handler code here
	CString strx,stry;
	
	if(m_iSelect==0)
	{
		strx=m_sXAxes;
		stry=m_sYAxes;
	}
	else//m_iSelect=1
	{
		strx=m_sLXAxes;
		stry=m_sLYAxes;
	}
	decel_stop(atoi(strx));
	decel_stop(atoi(stry));
}

BOOL CDemo1Dlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);
	return CDialog::DestroyWindow();
}

void CDemo1Dlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	double PosX,PosY;
	CString sMsg,strx,stry;
//	int iErr[10];
	int i;
	
	if(m_iSelect==0)
	{
		strx=m_sXAxes;
		stry=m_sYAxes;
	}
	else//m_iSelect=1
	{
		strx=m_sLXAxes;
		stry=m_sLYAxes;
	}
	i=get_abs_pos(atoi(strx),&PosX);	//获取X轴位置
	i=get_abs_pos(atoi(stry),&PosY);	//获取Y轴位置
	sMsg.Format("%d,%d",atoi(strx),atoi(stry));
	m_cG.LineToPos(PosX,PosY);			//画线
	
//	for(i=1;i<11;i++)
//		iErr[i-1]=get_err(i);		//读取错误代码
//	sMsg.Format("Err: %d  %d  %d  %d  %d  %d  %d  %d  %d  %d"
//		,iErr[0],iErr[1],iErr[2],iErr[3],iErr[4]
//		,iErr[5],iErr[6],iErr[7],iErr[8],iErr[9]);
	GetDlgItem(IDC_STATIC_MSG)->SetWindowText(sMsg);
										//显示错误代码

	CDialog::OnTimer(nIDEvent);
}

void CDemo1Dlg::OnBtnReset() 
{
	// TODO: Add your control notification handler code here
	CString strx,stry;
	
	if(m_iSelect==0)
	{
		strx=m_sXAxes;
		stry=m_sYAxes;
	}
	else//m_iSelect=1
	{
		strx=m_sLXAxes;
		stry=m_sLYAxes;
	}
	reset_pos(atoi(strx));
	reset_pos(atoi(stry));
}

void CDemo1Dlg::OnRadioArcCon() 
{
	// TODO: Add your control notification handler code here
	m_iArcConFast=IDC_RADIO_ARC_CON;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioArcFast() 
{
	// TODO: Add your control notification handler code here
	m_iArcConFast=IDC_RADIO_ARC_FAST;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioLineCon() 
{
	// TODO: Add your control notification handler code here
	m_iLineConFast=IDC_RADIO_LINE_CON;
	SetRadioButton();
}

void CDemo1Dlg::OnRadioLineFast() 
{
	// TODO: Add your control notification handler code here
	m_iLineConFast=IDC_RADIO_LINE_FAST;
	SetRadioButton();
}

void CDemo1Dlg::OnCardinfo() 
{
	// TODO: Add your command handler code here
	CString sInfo,str;
	long nType,ma[3],mi1[3],mi2[3],Rtn,i;
	CAboutDlg dlgAbout;
	sInfo.Format("计算机内插有 %d 张板卡。共有 %d 根轴。\n",glTotalCards,glTotalAxes);
	Rtn = get_lib_ver(&ma[0], &mi1[0], &mi2[0]);
	Rtn = get_sys_ver(&ma[1], &mi1[1], &mi2[1]);
	Rtn = get_card_ver(1, &nType, &ma[2], &mi1[2], &mi2[2]);
	str.Format("板卡类型号     ：%d\n",nType);
	sInfo = sInfo + str;
	str.Format("函数库版本号   ：%d.%d.%d\n",ma[0], mi1[0], mi2[0]);
	sInfo = sInfo + str;
	str.Format("驱动程序版本号 ：%d.%d.%d\n",ma[1], mi1[1], mi2[1]);
	sInfo = sInfo + str;
	str.Format("硬件版本号     ：%d.%d.%d\n",ma[2], mi1[2], mi2[2]);
	sInfo = sInfo + str;
    
	for(i = 1;i<=glTotalAxes;i++)
	{
		sudden_stop(i);
	}
	
	for(i = 1;i<= glTotalAxes;i++)
	{
		reset_pos(i);
	}
	
	dlgAbout.m_sCardInfo = sInfo;//.GetDlgItem(IDC_CARDINFO)->SetWindowText(sInfo);
	dlgAbout.DoModal();	
}

void CDemo1Dlg::OnExit() 
{
	// TODO: Add your command handler code here
	SendMessage(WM_CLOSE,0,0);
}
