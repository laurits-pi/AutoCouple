// TestMPC07Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPC08d.h"
#include "TestMPC07.h"
#include "TestMPC07Dlg.h"
#include "EditDlg.h"

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
// CTestMPC07Dlg dialog

CTestMPC07Dlg::CTestMPC07Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMPC07Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestMPC07Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iIndex = 0;
	int i;
	for(i=0;i<10;i++)
	{
		m_lPara[i]=0;
	}
}

void CTestMPC07Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestMPC07Dlg)
	DDX_Control(pDX, IDC_LIST_MPC07_FUNCTION, m_ListFunction);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestMPC07Dlg, CDialog)
	//{{AFX_MSG_MAP(CTestMPC07Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST_MPC07_FUNCTION, OnClickListMpc07Function)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MPC07_FUNCTION, OnDblclkListMpc07Function)
	ON_BN_CLICKED(IDC_BTN_START_MOVE, OnBtnStartMove)
	ON_BN_CLICKED(IDC_BTN_DECEL_STOP, OnBtnDecelStop)
	ON_BN_CLICKED(IDC_BTN_SUDDEN_STOP, OnBtnSuddenStop)
	ON_COMMAND(IDC_CARDINFO, OnCardinfo)
	ON_COMMAND(IDC_EXIT, OnExit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMPC07Dlg message handlers

BOOL CTestMPC07Dlg::OnInitDialog()
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
	InitMPC07();
	SetTimer(1,100,NULL);
	
	InitListCtrl();
	
	return TRUE;  // return TRUE  unless you set the focus to a control

}

void CTestMPC07Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestMPC07Dlg::OnPaint() 
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
HCURSOR CTestMPC07Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CTestMPC07Dlg::InitMPC07()
{
	int Rtn;//,i;
	CString str;

	//初始化板卡
	Rtn=auto_set();			//自动设置
	if(Rtn<=0 )
	{   
		if(Rtn==-1)
		::AfxMessageBox("检测不到卡!",MB_OK);
		if(Rtn==-10)
		::AfxMessageBox("使用多卡搭配不当!",MB_OK);
	}
	else
	{
		str.Format("轴数=%d",Rtn);
		::AfxMessageBox(str);
	}
	glTotalAxes = Rtn;

	Rtn=init_board();		//初始化
	if(Rtn<=0)
	{
		if(Rtn == -5)
		{
			::AfxMessageBox("动态链接库或驱动程序的版本错误",MB_OK);
		}
		else if(Rtn == -6)
		{
			::AfxMessageBox("硬件版本错误",MB_OK);
		}
		else
		{
			::AfxMessageBox("初始化错误!",MB_OK);
		}
	}
	else
	{
		str.Format("卡数=%d",Rtn);
		::AfxMessageBox(str);
	}
	glTotalCards = Rtn;
	return 0;
}
/*
void CTestMPC07Dlg::OnBtnWrite() 
{
	// TODO: Add your control notification handler code here
	CString str;
	sscanf(m_sOffset,"%x",&m_iOffset);
	//m_iOffset=atoi(m_sOffset);
	if(m_iOffset<0 || m_iOffset>511)
	{
		str.Format("寄存器偏移量范围只能在“0x0～0x200”之间！,%d",m_iOffset);
		MessageBox(str);
		m_iOffset=1;
		return;
	}
	sscanf(m_sIndata,"%x",&m_iIndata);
	if(m_iIndata<0 || m_iIndata>0x7fffffff)
	{
		str.Format("写入值只能在“0～0x7fffffff”之间！,%d",m_iIndata);
		MessageBox(str);
		m_iIndata=0;
		return;
	}
//	write_reg(1,m_iOffset,m_iIndata);
}

void CTestMPC07Dlg::OnBtnRead() 
{
	// TODO: Add your control notification handler code here
	CString str;
	long data=0;
	sscanf(m_sOffset,"%x",&m_iOffset);
	//m_iOffset=atoi(m_sOffset);
	if(m_iOffset<0 || m_iOffset>511)
	{
		str.Format("寄存器偏移量范围只能在“0x0～0x200”之间！,%d",m_iOffset);
		MessageBox(str);
		m_iOffset=1;
		return;
	}
//	read_reg(1,m_iOffset,&data);
	m_iOutdata=data;
	str.Format("%lx",m_iOutdata);
	GetDlgItem(IDC_EDIT_OUTDATA)->SetWindowText(str);
}

void CTestMPC07Dlg::OnChangeEditIndata() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CTestMPC07Dlg::OnChangeEditOffset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
*/
int CTestMPC07Dlg::InitListCtrl()
{
	if(m_ListFunction.GetHeaderCtrl()->GetItemCount()==0)
	{
		LV_COLUMN lvColumn;
		lvColumn.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt=LVCFMT_LEFT;
		lvColumn.cx=300;
		
		lvColumn.iSubItem=0;
		lvColumn.pszText="函数";
		m_ListFunction.InsertColumn(0,&lvColumn);

		lvColumn.cx=80;

		lvColumn.iSubItem=1;
		lvColumn.pszText="参数1";
		m_ListFunction.InsertColumn(1,&lvColumn);

		lvColumn.iSubItem=2;
		lvColumn.pszText="参数2";
		m_ListFunction.InsertColumn(2,&lvColumn);

		lvColumn.iSubItem=3;
		lvColumn.pszText="参数3";
		m_ListFunction.InsertColumn(3,&lvColumn);

		lvColumn.iSubItem=4;
		lvColumn.pszText="参数4";
		m_ListFunction.InsertColumn(4,&lvColumn);

		lvColumn.iSubItem=5;
		lvColumn.pszText="参数5";
		m_ListFunction.InsertColumn(5,&lvColumn);

		lvColumn.iSubItem=6;
		lvColumn.pszText="参数6";
		m_ListFunction.InsertColumn(6,&lvColumn);

		lvColumn.iSubItem=7;
		lvColumn.pszText="参数7";
		m_ListFunction.InsertColumn(7,&lvColumn);

		lvColumn.iSubItem=8;
		lvColumn.pszText="参数8";
		m_ListFunction.InsertColumn(8,&lvColumn);
	}

	LV_ITEM curItem;
	curItem.mask=LVIF_TEXT | LVIF_STATE;
	curItem.state=0;
	curItem.stateMask=0;

	curItem.iItem=GET_MAX_AXE;
	curItem.iSubItem=0;
	curItem.pszText="get_max_axe()";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_BOARD_NUM;
	curItem.iSubItem=0;
	curItem.pszText="get_board_num()";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_AXE;
	curItem.iSubItem=0;
	curItem.pszText="get_axe(int board_no)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_OUTMODE;
	curItem.iSubItem=0;
	curItem.pszText="set_outmode(int ch,int mode,int outlogic)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_HOME_MODE;
	curItem.iSubItem=0;
	curItem.pszText="set_home_mode(int ch,int home_mode)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_MAXSPEED;
	curItem.iSubItem=0;
	curItem.pszText="set_maxspeed(int ch,double speed)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_CONSPEED;
	curItem.iSubItem=0;
	curItem.pszText="set_conspeed(int ch,double conspeed)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_CONSPEED;
	curItem.iSubItem=0;
	curItem.pszText="get_conspeed(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_PROFILE;
	curItem.iSubItem=0;
	curItem.pszText="set_profile(int ch,double ls,double hs,double accel)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_PROFILE;
	curItem.iSubItem=0;
	curItem.pszText="get_profile(int ch,int *ls,int *hs,long *accel)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_RATE;
	curItem.iSubItem=0;
	curItem.pszText="get_rate(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_PMOVE;
	curItem.iSubItem=0;
	curItem.pszText="con_pmove(int ch,long step)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_PMOVE;
	curItem.iSubItem=0;
	curItem.pszText="fast_pmove(int ch,long step)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_PMOVE2;
	curItem.iSubItem=0;
	curItem.pszText="con_pmove2(int ch1,long step1,int ch2,long step2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_PMOVE2;
	curItem.iSubItem=0;
	curItem.pszText="fast_pmove2(int ch1,long step1,int ch2,long step2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_PMOVE3;
	curItem.iSubItem=0;
	curItem.pszText="con_pmove3(int ch1,long step1,int ch2,long step2,int ch3,long step3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_PMOVE3;
	curItem.iSubItem=0;
	curItem.pszText="fast_pmove3(int ch1,long step1,int ch2,long step2,int ch3,long step3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_PMOVE4;
	curItem.iSubItem=0;
	curItem.pszText="con_pmove4(int ch1,long step1,int ch2,long step2,int ch3,long step3,int ch4,long step4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_PMOVE4;
	curItem.iSubItem=0;
	curItem.pszText="fast_pmove4(int ch1,long step1,int ch2,long step2,int ch3,long step3,int ch4,long step4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_VMOVE;
	curItem.iSubItem=0;
	curItem.pszText="con_vmove(int ch,int dir)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_VMOVE;
	curItem.iSubItem=0;
	curItem.pszText="fast_vmove(int ch,int dir)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_VMOVE2;
	curItem.iSubItem=0;
	curItem.pszText="con_vmove2(int ch1,int dir1,int ch2,int dir2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_VMOVE2;
	curItem.iSubItem=0;
	curItem.pszText="fast_vmove2(int ch1,int dir1,int ch2,int dir2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_VMOVE3;
	curItem.iSubItem=0;
	curItem.pszText="con_vmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_VMOVE3;
	curItem.iSubItem=0;
	curItem.pszText="fast_vmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_VMOVE4;
	curItem.iSubItem=0;
	curItem.pszText="con_vmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_VMOVE4;
	curItem.iSubItem=0;
	curItem.pszText="fast_vmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_HMOVE;
	curItem.iSubItem=0;
	curItem.pszText="con_hmove(int ch,int dir)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_HMOVE;
	curItem.iSubItem=0;
	curItem.pszText="fast_hmove(int ch,int dir)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_HMOVE2;
	curItem.iSubItem=0;
	curItem.pszText="con_hmove2(int ch1,int dir1,int ch2,int dir2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_HMOVE2;
	curItem.iSubItem=0;
	curItem.pszText="fast_hmove2(int ch1,int dir1,int ch2,int dir2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_HMOVE3;
	curItem.iSubItem=0;
	curItem.pszText="con_hmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_HMOVE3;
	curItem.iSubItem=0;
	curItem.pszText="fast_hmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_HMOVE4;
	curItem.iSubItem=0;
	curItem.pszText="con_hmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_HMOVE4;
	curItem.iSubItem=0;
	curItem.pszText="fast_hmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_VECTOR_CONSPEED;
	curItem.iSubItem=0;
	curItem.pszText="set_vector_conspeed(double conspeed)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_VECTOR_PROFILE;
	curItem.iSubItem=0;
	curItem.pszText="set_vector_profile(double vec_vl , double vec_vh ,double vec_ad)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_VECTOR_CONSPEED;
	curItem.iSubItem=0;
	curItem.pszText="get_vector_conspeed()";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_VECTOR_PROFILE;
	curItem.iSubItem=0;
	curItem.pszText="get_vector_profile(double *vec_vl , double *vec_vh ,double *vec_ad)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_LINE2;
	curItem.iSubItem=0;
	curItem.pszText="con_line2(int CHx,long pos1,int CHy, long pos2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_LINE3;
	curItem.iSubItem=0;
	curItem.pszText="con_line3(int CHx,long pos1,int CHy,long pos2,int CHz,long pos3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CON_LINE4;
	curItem.iSubItem=0;
	curItem.pszText="con_line4(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3,int ch4,long pos4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_LINE2;
	curItem.iSubItem=0;
	curItem.pszText="fast_line2(int ch1,long pos1,int ch2,long pos2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_LINE3;
	curItem.iSubItem=0;
	curItem.pszText="fast_line3(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=FAST_LINE4;
	curItem.iSubItem=0;
	curItem.pszText="fast_line4(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3,int ch4,long pos4)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHANGE_POS;
	curItem.iSubItem=0;
	curItem.pszText="change_pos(int ch,long pos)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_ABS_POS;
	curItem.iSubItem=0;
	curItem.pszText="set_abs_pos(int ch,long pos)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=RESET_POS;
	curItem.iSubItem=0;
	curItem.pszText="reset_pos(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_DIR;
	curItem.iSubItem=0;
	curItem.pszText="set_dir(int ch,int dir)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=ENABLE_CARD_ALM;
	curItem.iSubItem=0;
	curItem.pszText="enable_card_alm(int cardno,int flag)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=ENABLE_EL;
	curItem.iSubItem=0;
	curItem.pszText="enable_el(int ch,int flag)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=ENABLE_ORG;
	curItem.iSubItem=0;
	curItem.pszText="enable_org(int ch,int flag)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_CARD_ALM_LOGIC;
	curItem.iSubItem=0;
	curItem.pszText="set_card_alm_logic(int cardno,int mode)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_EL_LOGIC;
	curItem.iSubItem=0;
	curItem.pszText="set_el_logic(int ch,int flag)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_ORG_LOGIC;
	curItem.iSubItem=0;
	curItem.pszText="set_org_logic(int ch,int flag)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_ALM_LOGIC;
	curItem.iSubItem=0;
	curItem.pszText="set_alm_logci(int ch,int flag)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_ABS_POS;
	curItem.iSubItem=0;
	curItem.pszText="get_abs_pos(int ch,long *abs_pos)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CLEAR_PASSWORD_FLASH;
	curItem.iSubItem=0;
	curItem.pszText="clear_password_flash(int cardno, long password)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=WRITE_PASSWORD_FLASH;
	curItem.iSubItem=0;
	curItem.pszText="write_password_flash(int cardno, int no, long data,long password)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=READ_PASSWORD_FLASH;
	curItem.iSubItem=0;
	curItem.pszText="read_password_flash(int cardno, int no, long *data,long password)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CLEAR_FLASH;
	curItem.iSubItem=0;
	curItem.pszText="clear_flash(int cardno, int piece)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=WRITE_FLASH;
	curItem.iSubItem=0;
	curItem.pszText="write_flash(int cardno,int piece, int no, long data)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=READ_FLASH;
	curItem.iSubItem=0;
	curItem.pszText="read_flash(int cardno,int piece,int no,long *data )";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_CUR_DIR;
	curItem.iSubItem=0;
	curItem.pszText="get_cur_dir(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_STATUS;
	curItem.iSubItem=0;
	curItem.pszText="check_status(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_DONE;
	curItem.iSubItem=0;
	curItem.pszText="check_done(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_LIMIT;
	curItem.iSubItem=0;
	curItem.pszText="check_limit(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_HOME;
	curItem.iSubItem=0;
	curItem.pszText="check_home(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_CARD_ALARM;
	curItem.iSubItem=0;
	curItem.pszText="check_card_alarm(int cardno)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_ALARM;
	curItem.iSubItem=0;
	curItem.pszText="check_alarm(int ch)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECKIN_BYTE;
	curItem.iSubItem=0;
	curItem.pszText="checkin_byte(int cardno)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECKIN_BIT;
	curItem.iSubItem=0;
	curItem.pszText="checkin_bit(int cardno,int bitno)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=OUTPORT_BIT;
	curItem.iSubItem=0;
	curItem.pszText="outport_bit(int cardno,int bitno,int status)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=OUTPORT_BYTE;
	curItem.iSubItem=0;
	curItem.pszText="outport_byte(int cardno,int bytedata)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=CHECK_SFR;
	curItem.iSubItem=0;
	curItem.pszText="check_SFR(int cardno)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=SET_BACKLASH;
	curItem.iSubItem=0;
	curItem.pszText="set_backlash(int ch,int backlash)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=START_BACKLASH;
	curItem.iSubItem=0;
	curItem.pszText="start_backlash(int ch)";//
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=END_BACKLASH;
	curItem.iSubItem=0;
	curItem.pszText="end_backlash(int ch)";//
	m_ListFunction.InsertItem(&curItem);


	curItem.iItem=GET_LIB_VER;
	curItem.iSubItem=0;
	curItem.pszText="get_lib_ver(int* major,int *minor1,int *minor2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_SYS_VER;
	curItem.iSubItem=0;
	curItem.pszText="get_sys_ver(int* major,int *minor1,int *minor2)";
	m_ListFunction.InsertItem(&curItem);

	curItem.iItem=GET_CARD_VER;
	curItem.iSubItem=0;
	curItem.pszText="get_card_ver(long cardno,long *type,long* major,long *minor1,long *minor2)";
	m_ListFunction.InsertItem(&curItem);
	
/*"其它函数"尚未包含
	curItem.iItem=1;
	curItem.iSubItem=0;
	curItem.pszText="";
	m_ListFunction.InsertItem(&curItem);
*/
	return 0;
}

void CTestMPC07Dlg::OnClickListMpc07Function(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_ListFunction.GetFirstSelectedItemPosition();
	m_iIndex = m_ListFunction.GetNextSelectedItem(pos); // 得到项目索引
	
	m_sFunction=m_ListFunction.GetItemText(m_iIndex,0);
	m_lPara[0]=atoi(m_ListFunction.GetItemText(m_iIndex,1));
	m_lPara[1]=atoi(m_ListFunction.GetItemText(m_iIndex,2));
	m_lPara[2]=atoi(m_ListFunction.GetItemText(m_iIndex,3));
	m_lPara[3]=atoi(m_ListFunction.GetItemText(m_iIndex,4));
	m_lPara[4]=atoi(m_ListFunction.GetItemText(m_iIndex,5));
	m_lPara[5]=atoi(m_ListFunction.GetItemText(m_iIndex,6));
	m_lPara[6]=atoi(m_ListFunction.GetItemText(m_iIndex,7));
	m_lPara[7]=atoi(m_ListFunction.GetItemText(m_iIndex,8));
	
	*pResult = 0;
}

void CTestMPC07Dlg::OnDblclkListMpc07Function(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_ListFunction.GetFirstSelectedItemPosition();
	m_iIndex = m_ListFunction.GetNextSelectedItem(pos); // 得到项目索引

	m_sFunction=m_ListFunction.GetItemText(m_iIndex,0);

	CEditDlg ed;
	ed.m_sPara1=m_ListFunction.GetItemText(m_iIndex,1);
	ed.m_sPara2=m_ListFunction.GetItemText(m_iIndex,2);
	ed.m_sPara3=m_ListFunction.GetItemText(m_iIndex,3);
	ed.m_sPara4=m_ListFunction.GetItemText(m_iIndex,4);
	ed.m_sPara5=m_ListFunction.GetItemText(m_iIndex,5);
	ed.m_sPara6=m_ListFunction.GetItemText(m_iIndex,6);
	ed.m_sPara7=m_ListFunction.GetItemText(m_iIndex,7);
	ed.m_sPara8=m_ListFunction.GetItemText(m_iIndex,8);
	
	if(ed.DoModal()==IDOK)
	{ 
		m_ListFunction.SetItemText(m_iIndex,1,ed.m_sPara1);
		m_ListFunction.SetItemText(m_iIndex,2,ed.m_sPara2);
		m_ListFunction.SetItemText(m_iIndex,3,ed.m_sPara3);
		m_ListFunction.SetItemText(m_iIndex,4,ed.m_sPara4);
		m_ListFunction.SetItemText(m_iIndex,5,ed.m_sPara5);
		m_ListFunction.SetItemText(m_iIndex,6,ed.m_sPara6);
		m_ListFunction.SetItemText(m_iIndex,7,ed.m_sPara7);
		m_ListFunction.SetItemText(m_iIndex,8,ed.m_sPara8);

		m_lPara[0] = atoi(ed.m_sPara1);
		m_lPara[1] = atoi(ed.m_sPara2);
		m_lPara[2] = atoi(ed.m_sPara3);
		m_lPara[3] = atoi(ed.m_sPara4);
		m_lPara[4] = atoi(ed.m_sPara5);
		m_lPara[5] = atoi(ed.m_sPara6);
		m_lPara[6] = atoi(ed.m_sPara7);
		m_lPara[7] = atoi(ed.m_sPara8);
	}

	*pResult = 0;
}

void CTestMPC07Dlg::OnBtnStartMove() 
{
	// TODO: Add your control notification handler code here
	int iRtn;
	int para;
	double dbRtn;
	CString str;
	switch(m_iIndex)
	{
	case GET_MAX_AXE:
		iRtn=get_max_axe();
		str.Format("板卡总轴数--%d",iRtn);
		MessageBox(str);
		break;
	case GET_BOARD_NUM:
		iRtn = get_board_num();
		str.Format("板卡数--%d",iRtn);
		MessageBox(str);
		break;
	case GET_AXE:
		iRtn = get_axe(m_lPara[0]);
		str.Format("板卡 %d 轴数--%d",m_lPara[0],iRtn);
		MessageBox(str);
		break;
	case SET_OUTMODE:
		str.Format("set_outmode(%d,%d,%d)",m_lPara[0],m_lPara[1],m_lPara[2]);
		MessageBox(str);
		set_outmode(m_lPara[0],m_lPara[1],m_lPara[2]);
		break;
	case SET_HOME_MODE:
		str.Format("set_home_mode(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_home_mode(m_lPara[0],m_lPara[1]);
		break;
	case SET_MAXSPEED:
		str.Format("执行set_maxspeed(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_maxspeed(m_lPara[0],(double)m_lPara[1]);
		break;
	case SET_CONSPEED:
		str.Format("执行set_conspeed(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_conspeed(m_lPara[0],(double)m_lPara[1]);
		break;
	case GET_CONSPEED:
		iRtn=(int)get_conspeed(m_lPara[0]);
		str.Format("设置的常速度=%ld",iRtn);
		MessageBox(str);
		break;
	case SET_PROFILE:
		str.Format("执行set_profile(%d,%d,%d,%d)",m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4]);
		MessageBox(str);
		set_profile(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4]);
		break;
	case GET_PROFILE:
		get_profile(m_lPara[0],&(m_dbPara[1]),&(m_dbPara[2]),&(m_dbPara[3]),&(m_dbPara[4]));
		para=(int)m_dbPara[1];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,1,str);
		para=(int)m_dbPara[2];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		para=(int)m_dbPara[3];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		para=(int)m_dbPara[4];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,4,str);
		break;
	case GET_RATE://获得正在运行的某个轴的速度
		dbRtn=get_rate(m_lPara[0]);
		str.Format("轴%d当前运行速度=%f",m_lPara[0],dbRtn);
		MessageBox(str);
		break;
	case CON_PMOVE:
		con_pmove(m_lPara[0],m_lPara[1]);
		break;
	case FAST_PMOVE:
		fast_pmove(m_lPara[0],m_lPara[1]);
		break;
	case CON_PMOVE2:
		con_pmove2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case FAST_PMOVE2:
		fast_pmove2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case CON_PMOVE3:
		con_pmove3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case FAST_PMOVE3:
		fast_pmove3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case CON_PMOVE4:
		con_pmove4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case FAST_PMOVE4:
		fast_pmove4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case CON_VMOVE:
		con_vmove(m_lPara[0],m_lPara[1]);
		break;
	case FAST_VMOVE:
		fast_vmove(m_lPara[0],m_lPara[1]);
		break;
	case CON_VMOVE2:
		con_vmove2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case FAST_VMOVE2:
		fast_vmove2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case CON_VMOVE3:
		con_vmove3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case FAST_VMOVE3:
		fast_vmove3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case CON_VMOVE4:
		con_vmove4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case FAST_VMOVE4:
		fast_vmove4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case CON_HMOVE:
		con_hmove(m_lPara[0],m_lPara[1]);
		break;
	case FAST_HMOVE:
		fast_hmove(m_lPara[0],m_lPara[1]);
		break;
	case CON_HMOVE2:
		con_hmove2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case FAST_HMOVE2:
		fast_hmove2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case CON_HMOVE3:
		con_hmove3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case FAST_HMOVE3:
		fast_hmove3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case CON_HMOVE4:
		con_hmove4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case FAST_HMOVE4:
		fast_hmove4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case SET_VECTOR_CONSPEED:
		str.Format("执行set_vector_conspeed(%d)",m_lPara[0]);
		MessageBox(str);
		set_vector_conspeed(m_lPara[0]);
		break;
	case SET_VECTOR_PROFILE:
		str.Format("执行set_vector_profile(%d,%d,%d)",m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		MessageBox(str);
		set_vector_profile(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case GET_VECTOR_CONSPEED:
		dbRtn=get_vector_conspeed();
		str.Format("设置的矢量速度=%f",dbRtn);
		MessageBox(str);
		break;
	case GET_VECTOR_PROFILE:
		get_vector_profile(&m_dbPara[0],&m_dbPara[1],&m_dbPara[2],&m_dbPara[3]);
		para=(int)m_dbPara[0];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,1,str);
		para=(int)m_dbPara[1];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		para=(int)m_dbPara[2];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		para=(int)m_dbPara[3];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,4,str);
		break;
	case CON_LINE2:
		con_line2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case CON_LINE3:
		con_line3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case CON_LINE4:
		con_line4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case FAST_LINE2:
		fast_line2(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case FAST_LINE3:
		fast_line3(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5]);
		break;
	case FAST_LINE4:
		fast_line4(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3],m_lPara[4],m_lPara[5],m_lPara[6],m_lPara[7]);
		break;
	case CHANGE_POS:
		change_pos(m_lPara[0],m_lPara[1]);
		break;
	case SET_ABS_POS:
		set_abs_pos(m_lPara[0],m_lPara[1]);
		break;
	case RESET_POS:
		reset_pos(m_lPara[0]);
		break;
	case WRITE_PASSWORD_FLASH:
		write_password_flash(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case CLEAR_PASSWORD_FLASH:
		clear_password_flash(m_lPara[0],m_lPara[1]);
		break;
	case WRITE_FLASH:
		write_flash(m_lPara[0],m_lPara[1],m_lPara[2],m_lPara[3]);
		break;
	case CLEAR_FLASH:
		clear_flash(m_lPara[0],m_lPara[1]);
		break;
	case READ_PASSWORD_FLASH:
		read_password_flash(m_lPara[0],m_lPara[1], &m_lPara[2],m_lPara[3]);
		para=(int)m_lPara[0];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,1,str);
		para=(int)m_lPara[1];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		para=(int)m_lPara[2];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		para=(int)m_lPara[3];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,4,str);
		break;
	case READ_FLASH:
		read_flash(m_lPara[0],m_lPara[1],m_lPara[2],&m_lPara[3]);
        para=(int)m_lPara[0];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,1,str);
		para=(int)m_lPara[1];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		para=(int)m_lPara[2];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		para=(int)m_lPara[3];
		str.Format("%d",para);
		m_ListFunction.SetItemText(m_iIndex,4,str);
		break;
	case SET_DIR:
		set_dir(m_lPara[0],m_lPara[1]);
		break;
	case ENABLE_CARD_ALM:
		enable_card_alm(m_lPara[0],m_lPara[1]);
		break;
	case ENABLE_EL:
		enable_el(m_lPara[0],m_lPara[1]);
		break;
	case ENABLE_ORG:
		enable_org(m_lPara[0],m_lPara[1]);
		break;
	case SET_CARD_ALM_LOGIC:
		str.Format("执行set_card_alm_logic(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_card_alm_logic(m_lPara[0],m_lPara[1]);
		break;
	case SET_EL_LOGIC:
		str.Format("执行set_el_logic(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_el_logic(m_lPara[0],m_lPara[1]);
		break;
	case SET_ORG_LOGIC:
		str.Format("执行set_org_logic(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_org_logic(m_lPara[0],m_lPara[1]);
		break;
	case SET_ALM_LOGIC:
		str.Format("执行set_alm_logic(%d,%d)",m_lPara[0],m_lPara[1]);
		MessageBox(str);
		set_alm_logic(m_lPara[0],m_lPara[1]);
		break;
	case GET_ABS_POS:
		get_abs_pos(m_lPara[0],&m_dbPara[1]);
		str.Format("%d",m_dbPara[1]);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		break;
	case GET_CUR_DIR:
		//返回值:1--正向; -1--负向; 0--运动停止时; 其它--失败
		iRtn=get_cur_dir(m_lPara[0]);
		str.Format("当前运动方向=%d",iRtn);
		MessageBox(str);
		break;
	case CHECK_STATUS:
		iRtn=check_status(m_lPara[0]);
		str.Format("status=%x",iRtn);
		MessageBox(str);
		break;
	case CHECK_DONE:
		iRtn=check_done(m_lPara[0]);
		if(iRtn==1)
		{
			str.Format("轴%d正在运动",m_lPara[0]);
		}
		else if(iRtn==0)
		{
			str.Format("轴%d停止运动",m_lPara[0]);
		}
		MessageBox(str);
		break;
//	case CHECK_BOARD:
//		iRtn=check_board();
//		str.Format("iRtn=%d",iRtn);//iRtn=0,MPC07工作正常
//		MessageBox(str);
		break;
	case CHECK_LIMIT:
		iRtn=check_limit(m_lPara[0]);
		str.Format("iRtn=%d",iRtn);//2--both EL- and EL+; 1--EL+; -1--EL-; -3--错误
		MessageBox(str);
		break;
	case CHECK_HOME:
		iRtn=check_home(m_lPara[0]);
		str.Format("iRtn=%d",iRtn);//1--ORG; -3--错误
		MessageBox(str);
		break;
	case CHECK_CARD_ALARM:
		iRtn=check_card_alarm(m_lPara[0]);
		str.Format("iRtn=%d",iRtn);//2--both SD- and SD+; 1--SD+; -1--SD-; -3--错误
		MessageBox(str);
		break;
	case CHECK_ALARM:
		iRtn=check_alarm(m_lPara[0]);
		str.Format("iRtn=%d",iRtn);//1--ALM; -3--错误
		MessageBox(str);
		break;
	case CHECKIN_BYTE:
		iRtn=checkin_byte(m_lPara[0]);
		str.Format("0x%x",iRtn);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		break;
	case CHECKIN_BIT:
		iRtn=checkin_bit(m_lPara[0],m_lPara[1]);
		str.Format("%d",iRtn);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		break;
	case OUTPORT_BIT:
		iRtn=outport_bit(m_lPara[0],m_lPara[1],m_lPara[2]);
		break;
	case OUTPORT_BYTE:
		iRtn=outport_byte(m_lPara[0],m_lPara[1]);
		break;
	case CHECK_SFR:
		iRtn=check_sfr(m_lPara[0]);
		str.Format("0x%x",iRtn);
		m_ListFunction.SetItemText(m_iIndex,2,str);
	case SET_BACKLASH:
		set_backlash(m_lPara[0],m_lPara[1]);
		break;
	case START_BACKLASH:
		start_backlash(m_lPara[0]);
		break;
	case END_BACKLASH:
		end_backlash(m_lPara[0]);
		break;
	case GET_LIB_VER:
		get_lib_ver(&m_lPara[0],&m_lPara[1],&m_lPara[2]);
		str.Format("%d",m_lPara[0]);
		m_ListFunction.SetItemText(m_iIndex,1,str);
		str.Format("%d",m_lPara[1]);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		str.Format("%d",m_lPara[2]);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		//MessageBox("Ok");
		break;
	case GET_SYS_VER:
		get_sys_ver(&m_lPara[0],&m_lPara[1],&m_lPara[2]);
		str.Format("%d",m_lPara[0]);
		m_ListFunction.SetItemText(m_iIndex,1,str);
		str.Format("%d",m_lPara[1]);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		str.Format("%d",m_lPara[2]);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		
		break;
	case GET_CARD_VER:
		get_card_ver(m_lPara[0],&m_lPara[1],&m_lPara[2],&m_lPara[3],&m_lPara[4]);
		str.Format("%d",m_lPara[1]);
		m_ListFunction.SetItemText(m_iIndex,2,str);
		str.Format("%d",m_lPara[2]);
		m_ListFunction.SetItemText(m_iIndex,3,str);
		str.Format("%d",m_lPara[3]);
		m_ListFunction.SetItemText(m_iIndex,4,str);
		str.Format("%d",m_lPara[4]);
		m_ListFunction.SetItemText(m_iIndex,5,str);
		//MessageBox("Ok");
		break;
	default:
		break;
	}
}

void CTestMPC07Dlg::OnBtnDecelStop() 
{
	// TODO: Add your control notification handler code here
	int iRtn;
	int i;
	iRtn=get_max_axe();
	for(i=0;i<iRtn;i++) decel_stop(i+1);
}

void CTestMPC07Dlg::OnBtnSuddenStop() 
{
	// TODO: Add your control notification handler code here
	int iRtn;
	int i;
	iRtn=get_max_axe();
	for(i=0;i<iRtn;i++) sudden_stop(i+1);
	
}

void CTestMPC07Dlg::OnCardinfo() 
{
	// TODO: Add your command handler code here
	CString sInfo,str;
	long nType,ma[3],mi1[3],mi2[3],Rtn;
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
    
	dlgAbout.m_sCardInfo = sInfo;//.GetDlgItem(IDC_CARDINFO)->SetWindowText(sInfo);
	dlgAbout.DoModal();
}

void CTestMPC07Dlg::OnExit() 
{
	// TODO: Add your command handler code here
	SendMessage(WM_CLOSE,0,0);
}

void CTestMPC07Dlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	double dbSpeed[4];
	double lPos[4];
	CString str;
	for(int i = 0;i<4;i++)
	{
		get_abs_pos(i+1,&lPos[i]);
		dbSpeed[i] = get_rate(i+1);
	}
	str.Format("%d          %d          %d          %d",lPos[0],lPos[1],lPos[2],lPos[3]);
	GetDlgItem(IDC_STATIC_POS)->SetWindowText(str);
	str.Format("%.2f          %.2f          %.2f          %.2f",dbSpeed[0],dbSpeed[1],dbSpeed[2],dbSpeed[3]);
	GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(str);
	CDialog::OnTimer(nIDEvent);
}
