// NxMasterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "NxMasterDlg.h"
#include "HyperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define MAIN_TAB_BORDER 3
#define MAIN_TAB_LEFT 500
#define MAIN_TAB_WEIGHT 450
#define MAIN_TAB_TOP 130
#define MAIN_TAB_BOTTOM 200
#define REV_BUF_LEN    1024
#define IDC_COLOR_PICKER_MST 1111
#define TEXT_NX_MST "国标(3-1) 能效通信协议测试工具 主(子)站 "
#define TEXT_NX_SLV "国标(3-1) 能效通信协议测试工具 集中与交互终端 "


#define  MASTER_AUTO_RES_TIMER  1001
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	CHyperLink		m_EMailLink;
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
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
//	m_EMailLink.SetURL("")
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_STATIC_EMAIL, m_EMailLink);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNxMasterDlg dialog

CNxMasterDlg::CNxMasterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNxMasterDlg::IDD, pParent)
{
	m_sev_port = 8888;
	m_bMaster  = true;    // 默认是主站
	m_bServerRun = false; // 服务器没有开启
    m_bClientLink = false;
	m_sendBuferAutoResponseMaster = (char*)malloc(MT_USER_MAX);
	m_imagelist = NULL;

	//{{AFX_DATA_INIT(CNxMasterDlg)

	//m_rich_edit.LimitText(35535);
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNxMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNxMasterDlg)
	DDX_Control(pDX, IDC_BTN_STOP, m_btn_stop_link);
	DDX_Control(pDX, IDC_BTN_START, m_btn_start_link);
	DDX_Control(pDX, IDC_CHECK_AUTO_RESPONE, m_check_auto_respone);
	DDX_Control(pDX, IDC_CHECK_OMIT_HEART_BEAT, m_check_omit_heart);
	DDX_Control(pDX, IDC_CHECK_AUTO_UNPACK, m_check_auto_unpack);
	DDX_Control(pDX, IDC_BTN_CLR_INFO, m_btn_clr_info);
	DDX_Control(pDX, IDC_BTN_CLR_UNPACK, m_btn_clr_unpack);
	DDX_Control(pDX, IDC_BTN_CLR_TML, m_btn_clr_terminal);
	DDX_Control(pDX, IDC_BTN_CLR_MST, m_btn_clr_master);
	DDX_Control(pDX, IDC_STATIC_CMD_CACH, m_static_cmd_cach);
	DDX_Control(pDX, IDC_EDIT_CMD_SAVER, m_cmd_cach);
	DDX_Control(pDX, IDC_BTN_SEND_CMD, m_btn_send_cmd);
	DDX_Control(pDX, IDC_EDIT_SEND_MSG, m_edit_send);
	DDX_Control(pDX, IDC_RICHEDIT_MAIN, m_rich_edit);
	DDX_Control(pDX, IDC_LIST_TML, m_list_tml);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
	DDX_Control(pDX, IDC_IP_ADDR, m_ctrl_ip);
	DDX_Text(pDX, IDC_EDIT_PORT, m_sev_port);
	//}}AFX_DATA_MAP
	
}

BEGIN_MESSAGE_MAP(CNxMasterDlg, CDialog)
	//{{AFX_MSG_MAP(CNxMasterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_MASTER, OnRadioMaster)
	ON_BN_CLICKED(IDC_RADIO_TERMINAL, OnRadioTerminal)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_ADDR, OnFieldchangedIpAddr)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_SEND_CMD, OnBtnSendCmd)
	ON_NOTIFY(HDN_ITEMCHANGED, IDC_LIST_TML, OnItemchangedListTml)
	ON_WM_SIZE()
	ON_COMMAND(AFX_SET_CLR_MASTER_MSG, OnSetClrMasterMsg)
	ON_COMMAND(AFX_SET_TML_CF, OnSetTmlCf)
	ON_COMMAND(AFX_SET_UNPACK_CF, OnSetUnpackCf)
	ON_BN_CLICKED(IDC_BTN_AS_CLIENT, OnBtnAsClient)
	ON_BN_CLICKED(IDC_CHECK_AUTO_UNPACK, OnCheckAutoUnpack)
	ON_COMMAND(AFX_ABOUT, OnAbout)
	ON_COMMAND(AFX_SET_INFO_CF, OnSetInfoCf)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
	ON_COMMAND(AFX_CLEAR_RICH_EDIT, OnClearRichEdit)
	ON_EN_CHANGE(IDC_EDIT_PORT, OnChangeEditPort)
	ON_BN_CLICKED(IDC_CHECK_AUTO_RESPONE, OnCheckAutoRespone)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(AFX_DATA_PRE_SET, OnDataPreSet)
	ON_NOTIFY(NM_RCLICK, IDC_RICHEDIT_MAIN, OnRclickRicheditMain)
	ON_WM_RBUTTONUP()
	ON_NOTIFY(NM_CLICK, IDC_RICHEDIT_MAIN, OnClickRicheditMain)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(AFX_RICH_CLR, OnRichClr)
	ON_COMMAND(AFX_RICH_TRANS, OnRichTrans)
	ON_COMMAND(AFX_RICH_COPY, OnRichCopy)
	ON_COMMAND(AFX_RICH_ADDT, OnRichAddt)
	ON_COMMAND(AFX_ID_TK_SET, OnIdTkSet)
	ON_COMMAND(AFX_RICH_INSET_LEN, OnRichInsetLen)
	//}}AFX_MSG_MAP
	ON_MESSAGE( CPN_SELENDOK,  OnSelEndOK )
    ON_MESSAGE( CPN_SELCHANGE, OnSelEndOK )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNxMasterDlg message handlers



// TCP 服务器监听线程
UINT threadTcpListen(LPVOID lparam)
{	
	int nRet = 0;
	CNxMasterDlg *pDlg = (CNxMasterDlg*)lparam;
	if(pDlg->m_bSevStop == true)
	{
		return -1;
	}
	
	CSocket sockSev;
	nRet = sockSev.Create(pDlg->m_nSerPort);
	if(nRet == 0)
	{
		AfxMessageBox("网络监听创建失败");
		return -1;
	}

	// start listen;
	nRet = sockSev.Listen();
	if(nRet == 0)
	{
		AfxMessageBox("网络监听");
		return -1;
	}

	
	// 接收
	CSocket sockRec;
	SOCKADDR_IN client;
	int iAddrSize=sizeof(client);
	
	nRet = sockSev.Accept(sockRec,(SOCKADDR *)&client,&iAddrSize);	//接受连接并取得对方IP
	if(nRet == 0)
	{
		AfxMessageBox("服务器接收失败");
		return -1;
	}

	sockSev.Close();
	


	
	return 0;
}








BOOL CNxMasterDlg::OnInitDialog()
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
    // 获取本机的IP
	CString strLocalName;
	
	GetLocalHostName(strLocalName);
	GetIpAddress(strLocalName,m_strLocalIP);
	m_ctrl_ip.SetWindowText(m_strLocalIP);
	SetWindowText(TEXT_NX_MST + m_strLocalIP);
	// 
	((CButton*)GetDlgItem(IDC_RADIO_MASTER))->SetCheck(BST_CHECKED);//默认为主站
	GetDlgItem(IDC_STATIC_STATE)->SetWindowText("");
	
	
	// 默认端口号
	m_nSerPort = 8888;
	
	
    // 控件位置初始化
	SetListTmlCtrlPos();
	setMsgRichEditPos();
	draw_main_tab();
	
	
	//m_rich_edit.
	// 初始化主界面tabctrl
	InitTabCtrl();
	
	// 初始化在线终端列表
	m_list_tml.initListCtrl();
	
	
	//m_list_tml.SetHeadings(_T("地址,80;终端IP,150;命令计数,100;状态,50"));
	
	// 初始化 主站不可以设置服务器IP
	//GetDlgItem(IDC_IP_ADDR)->EnableWindow(false);
	if (m_bServerRun == false)
	{
	   GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);	
	}
	
	// 初始化消息的默认颜色
	COLORREF crMaster,crTerminal,crInfor,crUnPack;
	crMaster    = RGB(0xFF,0x68,0x32);
	crTerminal  = RGB(0x00,0x66,0xcc);
	crInfor     = RGB(144,144,144);
	crUnPack    = RGB(0x00,0x99,0xcc);


	m_rich_edit.setCfColor(CF_MSATER, crMaster);
	m_rich_edit.setCfColor(CF_TERMINAL, crTerminal);
	m_rich_edit.setCfColor(CF_INFO, crInfor);
	m_rich_edit.setCfColor(CF_UNPACK, crUnPack);

	m_btn_clr_master.SetBkColor(crMaster);
	m_btn_clr_terminal.SetBkColor(crTerminal);
	m_btn_clr_info.SetBkColor(crInfor);
	m_btn_clr_unpack.SetBkColor(crUnPack);
	
	m_btn_clr_master.SetBkColorDefault(crMaster);
	m_btn_clr_terminal.SetBkColorDefault(crTerminal);
	m_btn_clr_info.SetBkColorDefault(crInfor);
	m_btn_clr_unpack.SetBkColorDefault(crUnPack);
	

	// 隐藏 解析的颜色按钮
	m_btn_clr_unpack.ShowWindow(SW_HIDE);

		
	// 默认勾选
	m_check_auto_unpack.SetCheck(TRUE);
	m_bAutoResponse = TRUE;
	m_bAutoUnpack = TRUE;
	m_check_auto_respone.SetCheck(TRUE);
	//ShowWindow(SW_MAXIMIZE);

	// 设置发送的按钮的样式
	
	m_btn_send_cmd.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	//m_btn_send_cmd.SetIcon(IDI_ICON22, IDI_ICON6);
	m_btn_send_cmd.SetIcon(IDI_ICON26);
	m_btn_send_cmd.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_send_cmd.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));

	// 启动和停止按钮样式

	m_btn_start_link.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
//	m_btn_start_link.SetIcon(IDI_ICON_GO);
	//m_btn_start_link.SetIcon(IDI_ICON_RIGHT);
//m_btn_start_link.SetIcon(IDI_ICON_CLOCK);
	m_btn_start_link.SetIcon(IDI_ICON_RUN);
	m_btn_start_link.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_start_link.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));


	m_btn_stop_link.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	//m_btn_send_cmd.SetIcon(IDI_ICON22, IDI_ICON6);
//	m_btn_stop_link.SetIcon(IDI_ICON_RED_STOP);
	//m_btn_stop_link.SetIcon(IDI_ICON_X);
	m_btn_stop_link.SetIcon(IDI_ICON_STOP);

	m_btn_stop_link.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_stop_link.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));


// 	//CNxConfig cfg;
// 	//cfg.initConfig();
// 	BOOL bAdmin = IsAdministrator();
// 	if (bAdmin == FALSE)
// 	{
// 		MessageBox("需要以管理员身份运行该程序", "重要提示", MB_OK|MB_ICONWARNING);
// 	}
// 	else
// 	{
// 		SetRegAdmin();
// 	}

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNxMasterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNxMasterDlg::OnPaint() 
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
		draw_main_tab();
		SetListTmlCtrlPos();
		setMsgRichEditPos();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNxMasterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CNxMasterDlg::OnRadioMaster() 
{
	m_bMaster = true;
	
	GetDlgItem(IDC_BTN_START)->SetWindowText("启动");
	GetDlgItem(IDC_BTN_STOP)->SetWindowText("停止");
	/*
    GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
	GetDlgItem(IDC_IP_ADDR)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_PORT)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(true);
	*/
	//SetWindowText("能效测试工具 主站 " + m_strLocalIP);
	SetWindowText(TEXT_NX_MST + m_strLocalIP);
	GetDlgItem(IDC_STATIC_STATE)->SetWindowText("");
	GetDlgItem(IDC_LIST_TML)->EnableWindow(true);
	//GetDlgItem(IDC_IP_ADDR)->EnableWindow(false);
	m_ctrl_ip.SetWindowText(m_strLocalIP);


	// 切换规约生成
	m_tabDlgPack.showEcPwTp(m_bMaster);
	m_tabDlgPack.BuildFnTree();
	m_tabDlgPack.showCmdType();
	// 主动上报checkbox

	if (m_bServerRun == false)
	{
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);	
	}

}

void CNxMasterDlg::OnRadioTerminal() 
{
	m_bMaster = false;

	GetDlgItem(IDC_BTN_START)->SetWindowText("连接");
	GetDlgItem(IDC_BTN_STOP)->SetWindowText("断开");
	/*
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(false);
	GetDlgItem(IDC_EDIT_PORT)->ShowWindow(false);
	GetDlgItem(IDC_IP_ADDR)->EnableWindow(true);
	*/
	SetWindowText(TEXT_NX_SLV + m_strLocalIP);
	GetDlgItem(IDC_STATIC_STATE)->SetWindowText("");
	//GetDlgItem(IDC_LIST_TML)->ShowWindow(false);
	GetDlgItem(IDC_LIST_TML)->EnableWindow(false);
	//	GetDlgItem(IDC_IP_ADDR)->EnableWindow(true);
	//m_ctrl_ip.SetWindowText(m_strServerIP);


	m_tabDlgPack.BuildFnTree();
	m_tabDlgPack.showEcPwTp(m_bMaster);
	m_tabDlgPack.showCmdType();

	if (m_bServerRun == false)
	{
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);	
	}

}

/************************************************************************
 函数功能: 启动主站服务器                                               
 输入参数: port  端口号
		   strIp IP地址

************************************************************************/
bool CNxMasterDlg::bStartServer(int port,CString strIp)
{
	
	if(m_bMaster == false)
	{
		return false;
	}

	if(m_bServerRun == true)
	{
		//AfxMessageBox("服务器已经开启");
		return true;
	}
	else
	{
		BOOL bCreate = m_sockSev.Create(port,SOCK_STREAM,strIp);
		if(bCreate == false)
		{
			MessageBox("服务器创建失败", "错误", MB_OK|MB_ICONERROR);
			return false;
		}
		m_sockSev.setNxDlg(this);
		if(m_sockSev.Listen(100))
		{
			m_bServerRun = true;
			//AfxMessageBox("服务器开启");
			return true;
		}	
	}

	return false;
}

bool CNxMasterDlg::bConnectServer(int port,CString strIp)
{
	if (m_bMaster == true) 
	{
		return false;
	}

	m_sockTml.Create();
	m_sockTml.setNxDlg(this);
	if(m_sockTml.Connect(strIp,port))
	{
		// 连接成功
		return true;
	}
	else
	{
		MessageBox("连接服务器失败", "错误", MB_OK|MB_ICONERROR);
		m_sockTml.Close();
		return false;
	}

}



// 获取本地IP地址
int CNxMasterDlg::GetIpAddress(const CString &sHostName, CString &sIpAddress)
{
    struct hostent FAR * lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		//产生错误
		sIpAddress=_T("");
		return GetLastError();
	}
	//获取IP
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		//转换为标准格式
		sIpAddress=inet_ntoa(inAddr);
		if(sIpAddress.IsEmpty())
			sIpAddress=_T("没有取得");
	}
	return 0;
}

// 获取本机的主站名
int CNxMasterDlg::GetLocalHostName(CString &sHostName)
{	
    char szHostName[256];
	int nRetCode;
	nRetCode=gethostname(szHostName,sizeof(szHostName));
	//AfxMessageBox(nRetCode);
	if(nRetCode!=0)
	{
		//产生错误
		sHostName=_T("没有取得");
		return GetLastError();
	}
	sHostName=szHostName;
	return 0;

}

void CNxMasterDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	// 是主站的时候
	if(m_bMaster == true)
	{
		m_bServerRun = bStartServer(m_sev_port,m_strLocalIP);
	
		// 如果启动成功禁用相关的控件
		if(m_bServerRun == true)
		{
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(false);
			GetDlgItem(IDC_IP_ADDR)->EnableWindow(false);
			GetDlgItem(IDC_BTN_START)->EnableWindow(false);
			GetDlgItem(IDC_STATIC_STATE)->SetWindowText("服务器已启动.....");
		    
			GetDlgItem(IDC_RADIO_MASTER)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_TERMINAL)->EnableWindow(false);
			
			if (m_bServerRun == false)
			{
				GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
			}
			else
			{
				GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);	
			}
		}
		else
		{
			GetDlgItem(IDC_STATIC_STATE)->SetWindowText("服务器启动失败!");
		}
	}
	else
	{
		m_ctrl_ip.GetWindowText(m_strServerIP);



		// 从站连接服务器
		m_bClientLink  = bConnectServer(m_sev_port,m_strServerIP);
		if(m_bClientLink == true)
		{
			GetDlgItem(IDC_STATIC_STATE)->SetWindowText("已连接主站.....");
			GetDlgItem(IDC_BTN_START)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_MASTER)->EnableWindow(false);
			GetDlgItem(IDC_RADIO_TERMINAL)->EnableWindow(false);
			GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(false);
			GetDlgItem(IDC_IP_ADDR)->EnableWindow(false);
		}
		else
		{
			GetDlgItem(IDC_STATIC_STATE)->SetWindowText("连接主站失败!");
			GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
			GetDlgItem(IDC_IP_ADDR)->EnableWindow(true);
		}
	}

	
}

void CNxMasterDlg::OnFieldchangedIpAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_ctrl_ip.GetWindowText(m_strServerIP);
    m_ctrl_ip.GetWindowText(m_strLocalIP);
	*pResult = 0;
}

void CNxMasterDlg::OnBtnStop() 
{


	if(m_bMaster == true)
	{
		if(MessageBox("真的要关闭服务器吗","关闭服务器",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			m_sockSev.Close();
			//POSITION pos = m_sockListSev.GetHeadPosition();
		     POSITION pos = m_listTml.GetHeadPosition();
			while(pos != NULL)
			{
				
				CTerminal *pTml = (CTerminal*)m_listTml.GetNext(pos);
				CServerSock *pSock = pTml->m_pSevSocket;
				if(pSock != NULL)
				{

					pSock->Close();
					delete pSock;
				}
			}
			
			m_bServerRun = false;
			m_listTml.RemoveAll();
			m_list_tml.DeleteAllItems();
			m_list_tml.m_maxItem = 0;
			
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
			GetDlgItem(IDC_IP_ADDR)->EnableWindow(true);
			GetDlgItem(IDC_STATIC_STATE)->SetWindowText("服务器已停止");
			GetDlgItem(IDC_BTN_START)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_MASTER)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_TERMINAL)->EnableWindow(true);
			if (m_bServerRun == false)
			{
				GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
			}
			else
			{
				GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);	
			}
		}
	
	}
	else
	{
		if(MessageBox("真的要断开与主站的连接吗?","断开连接",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			m_bClientLink = false;
			m_sockTml.Close();
			
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
			GetDlgItem(IDC_IP_ADDR)->EnableWindow(true);
			GetDlgItem(IDC_STATIC_STATE)->SetWindowText("已断开主站.....");
        	GetDlgItem(IDC_BTN_START)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_MASTER)->EnableWindow(true);
			GetDlgItem(IDC_RADIO_TERMINAL)->EnableWindow(true);
			GetDlgItem(IDC_BTN_STOP)->EnableWindow(false);
		}
	

	
	}




}

void CNxMasterDlg::draw_main_tab()
{
	// 初始化tab页
	RECT rect,rect_tab;
	GetClientRect(&rect);
	const int pos_top = 110;

	rect_tab.left = MAIN_TAB_BORDER;
	rect_tab.top=pos_top;	
	rect_tab.bottom=rect.bottom-MAIN_TAB_BORDER;
    rect_tab.right=rect.left + MAIN_TAB_WEIGHT;
	if(m_tab.m_hWnd)
     m_tab.MoveWindow(&rect_tab);



	RECT rect_tab_dlg;
	const int top    = 23;
	const int border = 3;
	m_tab.GetClientRect(&rect_tab_dlg);
	rect_tab_dlg.left += border;
	rect_tab_dlg.right -= border;
	rect_tab_dlg.top  += top;
	rect_tab_dlg.bottom -= border;
	

	if(m_tabDlgPack.m_hWnd)
	{
		m_tabDlgPack.MoveWindow(&rect_tab_dlg);
	}
	
	if(m_tabDlgPreMst.m_hWnd)
	{
		m_tabDlgPreMst.MoveWindow(&rect_tab_dlg);
	}
	if(m_tabDlgUnpack.m_hWnd)
	{
		m_tabDlgUnpack.MoveWindow(&rect_tab_dlg);
	}
	
	if(m_tabDlgTask.m_hWnd)
	{
		m_tabDlgTask.MoveWindow(&rect_tab_dlg);
	}
	
	if(m_tabDlgPreTml.m_hWnd)
	{
		m_tabDlgPreTml.MoveWindow(&rect_tab_dlg);
	}	
}


//服务器接受连接
void CNxMasterDlg::SevAcceptConnect()
{
	


	CServerSock *pSocket = new CServerSock();
	CTerminal *pTerminal = new CTerminal();

	pSocket->setNxDlg(this);
	pTerminal->setSocket(pSocket);
	if(m_sockSev.Accept(*pSocket))
	{


		// 有新的从站进入
        //AfxMessageBox("从站进入");
		CString rPeerAddress;
		UINT rPeerPort;
		m_sockSev.GetSockName(rPeerAddress,rPeerPort);
		pTerminal->m_strTerminalIp = rPeerAddress;
		m_listTml.AddHead(pTerminal);
		m_list_tml.addItemTerminal(pTerminal);
				
	}
	else
	{
		pSocket->Close();
		delete pSocket;
	}

	





}

/************************************************************************/
/* 从站退出的应用                              */
/************************************************************************/
void CNxMasterDlg::SocketStop(CServerSock *pSevSock)
{
	
	CString str;
	POSITION pos;
	int i = 0;
	CTerminal   *pTml  = NULL;	
	CServerSock *pSock = NULL;	
	str.Format("从站下线");
	

	for(i = 0; i < m_listTml.GetCount(); i++)
	{
		pos = m_listTml.FindIndex(i);
		if(pos != NULL)
		{
			pTml = (CTerminal*)m_listTml.GetAt(pos);		
			pSock = pTml->m_pSevSocket;
			if(pSevSock == pSock)
			{
				//AfxMessageBox(pTml->m_strTerminalIp +str);
				
				pTml->m_pSevSocket->Close();          
				m_listTml.RemoveAt(pos);
				m_list_tml.delItemTerminal(pTml);
				
			}
		}
		
	}
}

//服务器关闭后的响应
void CNxMasterDlg::TmlOnClose(CTerminalSock *pSock)
{
	m_bClientLink = false;
	m_sockTml.Close();
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
	GetDlgItem(IDC_IP_ADDR)->EnableWindow(true);
	GetDlgItem(IDC_STATIC_STATE)->SetWindowText("服务器已关闭");
	GetDlgItem(IDC_BTN_START)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_MASTER)->EnableWindow(true);
    GetDlgItem(IDC_RADIO_TERMINAL)->EnableWindow(true);

}


// 集中器收到消息处理
void CNxMasterDlg::tmlReceveMsg(CTerminalSock *pSockTml)
{
	char rev_buf[REV_BUF_LEN] = {0};
	int  rev_len = pSockTml->Receive(rev_buf,REV_BUF_LEN);
	//MT_USER_MAX ruler;
	CQgdw3761api ruler;
	CString str;
	str = ruler.BufferToHex(rev_buf, rev_len);

	insertInfoTmlRecv(pSockTml,rev_len);
	str=str+"\r\n";
	//m_rich_edit.AppendColor((LPCTSTR)str,RGB(0,33,0));
	m_rich_edit.cfAppend(str, CF_MSATER);
	//m_rich_edit.cfAppend(str, CF_INFO);
	if(m_bAutoUnpack == TRUE)
	{
		AutoUnpack(rev_buf, rev_len);
	}
}



// 服务器接到消息处理
void CNxMasterDlg::sevReceveMsg(CServerSock  *pSockSev)
{
	char rev_buf[REV_BUF_LEN] = {0};
	int  rev_len = pSockSev->Receive(rev_buf,REV_BUF_LEN);
	CTerminal *pTml = GetCTerminal(pSockSev);

	InsertInfoMasterRecv(pTml,rev_len);

	MasterDealLink(pTml, rev_buf,rev_len);

	CQgdw3761api ruler;


	CString str;
	str = ruler.BufferToHex(rev_buf, rev_len);


	str=str+"\r\n";
    m_rich_edit.cfAppend(str, CF_TERMINAL);
	if(m_bAutoUnpack == TRUE)
	{
		AutoUnpack(rev_buf, rev_len);
	}

    // 是否自动回复
	if (m_bAutoResponse == TRUE)
	{
		AutoResponseMaster(pTml, rev_buf, rev_len);
	}

	
}

int CNxMasterDlg::sevSendMsg(CServerSock *pSock, CString strSend)
{
	
	if(pSock == NULL || strSend.GetLength() == 0)
	{
		return -1;
	}
	

	CQgdw3761api ruler;
    char rev_buf[REV_BUF_LEN] = {0};
	UINT16 usLen;
	BOOL bToBuffer = FALSE;
	
	bToBuffer = ruler.CStringToHexBuffer(strSend, rev_buf, &usLen);
	if(bToBuffer != TRUE)
	{
		AfxMessageBox("报文数据转换错误，请查看报文内容及长度是否正确!");

		return 0;
	}
	
	send(*pSock,rev_buf,usLen,0);
	return usLen;
	
}

int CNxMasterDlg::tmlSendMsg(CTerminalSock *pSock, CString strSend)
{
	
	if(pSock == NULL || strSend.GetLength() == 0)
	{
		return -1;
	}
	
	
	CQgdw3761api ruler;
    char rev_buf[REV_BUF_LEN] = {0};
	UINT16 usLen;
	BOOL bToBuffer = FALSE;
	
	bToBuffer = ruler.CStringToHexBuffer(strSend, rev_buf, &usLen);
	if(bToBuffer != TRUE)
	{
     	MessageBox("报文数据转换错误，请查看报文内容及长度是否正确", "错误", MB_OK|MB_ICONERROR);
		return 0;
	}
	
	send(*pSock,rev_buf,usLen,0);
	return usLen;
	
}

void CNxMasterDlg::OnBtnSendCmd() 
{
	// TODO: Add your control notification handler code here
	CString strSend;

	
	m_edit_send.GetWindowText(strSend);
	SendToList(strSend);


}

void CNxMasterDlg::OnItemchangedListTml(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

/************************************************************************/
/* 设置在线终端列表控件位置                                             */
/************************************************************************/
void CNxMasterDlg::SetListTmlCtrlPos()
{

	const int pos_left = 460;
	const int pos_top  = 4;
	const int border   = 4;
	//const int height   = 100; // 高度
	const int height   = 102; // 高度

    RECT rect_client,rect_list;
	GetClientRect(&rect_client);

	rect_list.left = pos_left;
	rect_list.top=pos_top;	
	rect_list.bottom=rect_client.top+height;
    rect_list.right=rect_client.right -border;
	if(m_list_tml.m_hWnd)
     m_list_tml.MoveWindow(&rect_list);

}

void CNxMasterDlg::setMsgRichEditPos()
{
	const int pos_left    = 460;
	const int pos_top     = 133;
	const int pos_bottom  = 80;
	const int border   = 4;
	const int height   = 100; // 高度

    RECT rect_client,rect_ctrl;
	GetClientRect(&rect_client);

	rect_ctrl.left = pos_left;
	rect_ctrl.top=pos_top;	
	rect_ctrl.bottom=rect_client.bottom-pos_bottom;
    rect_ctrl.right=rect_client.right -border;
	if(m_rich_edit.m_hWnd)
     m_rich_edit.MoveWindow(&rect_ctrl);


	// 调整master color btn
	RECT rect_btn_master_color;
	const int btn_top = 25;
	const int btn_height = 20;
	const int btn_weight = 65;
	rect_btn_master_color.left   = rect_ctrl.left + 5;
	rect_btn_master_color.top    = rect_ctrl.top - btn_top;
	rect_btn_master_color.bottom = rect_btn_master_color.top + btn_height;
	rect_btn_master_color.right  = rect_btn_master_color.left + btn_weight;
	if(m_btn_clr_master.m_hWnd)
     m_btn_clr_master.MoveWindow(&rect_btn_master_color);

	
	// 终端消息颜色
	RECT rect_btn_tml_color;
	const int btn_distance = 9;
	rect_btn_tml_color.left   = rect_btn_master_color.right + btn_distance;
	rect_btn_tml_color.right  = rect_btn_tml_color.left + btn_weight;
	rect_btn_tml_color.top    = rect_btn_master_color.top;
	rect_btn_tml_color.bottom = rect_btn_master_color.bottom;
	if(m_btn_clr_terminal.m_hWnd)
		m_btn_clr_terminal.MoveWindow(&rect_btn_tml_color);
	
	// 提示消息颜色
	RECT rect_btn_info;
	rect_btn_info.left   = rect_btn_tml_color.right + btn_distance;
	rect_btn_info.right  =  rect_btn_info.left + btn_weight;
	rect_btn_info.top    = rect_btn_master_color.top;
	rect_btn_info.bottom = rect_btn_master_color.bottom;
	if(m_btn_clr_info.m_hWnd)
		m_btn_clr_info.MoveWindow(&rect_btn_info);
		

	// 解析内容颜色
	RECT rect_btn_unpack;
	rect_btn_unpack.left   = rect_btn_info.right + btn_distance;
	rect_btn_unpack.right  = rect_btn_unpack.left + btn_weight;
	rect_btn_unpack.top    = rect_btn_info.top;
	rect_btn_unpack.bottom = rect_btn_info.bottom;
	if(m_btn_clr_unpack.m_hWnd)
		m_btn_clr_unpack.MoveWindow(&rect_btn_unpack);
	
	
	
	// auto unpack
	int static_weight = 70;
	int static_distance = 4;
	RECT  rect_check_unpack;
	//rect_check_unpack.left   = rect_btn_unpack.right + btn_distance;
	rect_check_unpack.left   = rect_btn_info.right + btn_distance + 10;
	rect_check_unpack.right  = rect_check_unpack.left + static_weight;
	rect_check_unpack.top    = rect_btn_info.top;
	rect_check_unpack.bottom = rect_btn_info.bottom;
	if(m_check_auto_unpack.m_hWnd)
		m_check_auto_unpack.MoveWindow(&rect_check_unpack);

	RECT  rect_check_heart;  // 忽略心跳
	rect_check_heart.left   = rect_check_unpack.right + static_distance;
	rect_check_heart.right  = rect_check_heart.left   + static_weight;
	rect_check_heart.top    = rect_btn_info.top;
	rect_check_heart.bottom = rect_btn_info.bottom;
	if(m_check_omit_heart.m_hWnd)
		m_check_omit_heart.MoveWindow(&rect_check_heart);
	
	// 自动应答 checkbox
	RECT rect_check_respone;
	rect_check_respone.left = rect_check_heart.right + static_distance;
	rect_check_respone.right = rect_check_respone.left + static_weight;
	rect_check_respone.top = rect_btn_info.top;
	rect_check_respone.bottom = rect_btn_info.bottom;
	if(m_check_auto_respone.m_hWnd)
		m_check_auto_respone.MoveWindow(&rect_check_respone);



	// 发送消息窗口调整
	RECT rect_send;
	const int pos_send_bottom = 10;
	const int pos_sned_top = 10;
	const int size_btn_send = 150;
	rect_send.left   = pos_left;
	rect_send.bottom = rect_client.bottom-pos_send_bottom;
	rect_send.right  = rect_client.right -size_btn_send + 25;
	rect_send.top  = rect_ctrl.bottom + pos_sned_top;
	if(m_edit_send.m_hWnd)
     m_edit_send.MoveWindow(&rect_send);

	// send btn

	RECT rect_btn_send;
	const int pos_btn_left = 10;
	const int height_btn = rect_send.bottom - rect_send.top;
	const int weight = height_btn + 45;
	const int btn_border = 5;
	rect_btn_send.top    = rect_send.top + btn_border;
	rect_btn_send.left   = rect_send.right + pos_btn_left;
	rect_btn_send.right  = rect_btn_send.left + weight;
	rect_btn_send.bottom = rect_send.bottom - btn_border;
	if(m_btn_send_cmd.m_hWnd)
     m_btn_send_cmd.MoveWindow(&rect_btn_send);

	// 命令缓存控件大小
	RECT rect_cmd_cach;
	const int cach_top = 50;
	const int cach_height = weight;
	rect_cmd_cach.left  = rect_send.left;
	rect_cmd_cach.top   = rect_send.bottom  + cach_top;
	rect_cmd_cach.right = rect_send.right;
	rect_cmd_cach.bottom = rect_cmd_cach.top + height_btn;
	if(m_cmd_cach.m_hWnd)
		m_cmd_cach.MoveWindow(&rect_cmd_cach);
	
	RECT rect_static_cach;
	
	rect_static_cach.left = rect_cmd_cach.left -  border;
	rect_static_cach.top = rect_cmd_cach.top -  border;
	rect_static_cach.right = rect_cmd_cach.right +  border;
	rect_static_cach.bottom  = rect_cmd_cach.top +  border;
	if (m_static_cmd_cach.m_hWnd)
	{
		m_static_cmd_cach.MoveWindow(&rect_static_cach);
	}

}

void CNxMasterDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	SetListTmlCtrlPos();
	setMsgRichEditPos();
}
// 设置主站消息颜色
void CNxMasterDlg::OnSetClrMasterMsg() 
{

	CHARFORMAT cf;
	LOGFONT lf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));
	m_rich_edit.GetDefaultCharFormat(cf);
	CFontDialog dlg(m_rich_edit.m_cf[CF_MSATER],CF_EFFECTS | CF_SCREENFONTS);
	//CFontDialog dlg(m_rich_edit.m_cf[CF_MSATER]);
	dlg.m_cf.rgbColors = cf.crTextColor;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCharFormat(cf);
		m_rich_edit.m_cf[CF_MSATER] = cf;
		m_btn_clr_master.SetBkColor(cf.crTextColor);
	}

}

void CNxMasterDlg::OnSetTmlCf() 
{
	// TODO: Add your command handler code here
	CHARFORMAT cf;
	LOGFONT lf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));
	m_rich_edit.GetDefaultCharFormat(cf);
	//CFontDialog dlg(&lf);
	CFontDialog dlg(m_rich_edit.m_cf[CF_TERMINAL],CF_EFFECTS | CF_SCREENFONTS);
	dlg.m_cf.rgbColors = cf.crTextColor;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCharFormat(cf);
		m_rich_edit.m_cf[CF_TERMINAL] = cf;
		m_btn_clr_terminal.SetBkColor(cf.crTextColor);
	}
}
void CNxMasterDlg::OnSetInfoCf() 
{
	// TODO: Add your command handler code here
	CHARFORMAT cf;
	LOGFONT lf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));
	m_rich_edit.GetDefaultCharFormat(cf);
	//	CFontDialog dlg(&lf);
	CFontDialog dlg(m_rich_edit.m_cf[CF_INFO],CF_EFFECTS | CF_SCREENFONTS);
	dlg.m_cf.rgbColors = cf.crTextColor;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCharFormat(m_rich_edit.m_cf[CF_INFO]);
		m_btn_clr_info.SetBkColor(cf.crTextColor);
	}
}

void CNxMasterDlg::OnSetUnpackCf() 
{
    CHARFORMAT cf;
	LOGFONT lf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));
	m_rich_edit.GetDefaultCharFormat(cf);
//	CFontDialog dlg(&lf);
	CFontDialog dlg(m_rich_edit.m_cf[CF_UNPACK],CF_EFFECTS | CF_SCREENFONTS);
	dlg.m_cf.rgbColors = cf.crTextColor;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCharFormat(m_rich_edit.m_cf[CF_UNPACK]);
    	m_btn_clr_unpack.SetBkColor(cf.crTextColor);
	}
	
}

void CNxMasterDlg::OnBtnAsClient() 
{
	CString str;


	int i = 0;
// 	for (i = 0;i < 10; i++)
// 	{
// 		//str = GetCurDate();
// 		//str+= " ";
// 		str += GetCurTime();
// 		str+="\r\n";
// 		m_rich_edit.cfAppend(str,CF_TERMINAL);
// 		Sleep(10);
// 	}

// 	eMtCmd eCmd; 
// 	eMtDir eDir; 
// 	sMtCmdInfors sInfors;
// 
// 	eCmd = CMD_AFN_4_FN_9_CFG_TML_MNT;
// 	eDir = MT_DIR_M2S;
// 
// 
// 	eMtErr eRet = m_nxRuler.eMtGetCmdInfor(eCmd, eDir,&sInfors);
// 	if(eRet != MT_OK)
// 	{
// 		str = "没有对应命令";
// 	}
// 	else
// 	{
// 		str.Format("CMD = 0x%04X\r\n", eCmd);
// 		str += sInfors.strName;
// 
// 	}
	

test_GetMstPreAfn04F1();

}


void CNxMasterDlg::OnSelEndOK(UINT lParam, LONG wParam)
{
	// a color selection was made, update the 
	// appropriate member data.
	COLORREF cr;
	BYTE r,g,b;
	switch (wParam)
	{
	case IDC_BTN_CLR_MST:
		cr = m_btn_clr_master.GetColor();
		m_rich_edit.setCfColor(CF_MSATER,cr);
		r = 255 - GetRValue(cr);
		g = 255 - GetGValue(cr);
		b = 255 - GetBValue(cr);
		m_btn_clr_master.SetTextColor(CLR_DEFAULT);
		break;
		
	case IDC_BTN_CLR_TML:
		cr = m_btn_clr_terminal.GetColor();

		m_rich_edit.setCfColor(CF_TERMINAL,cr);
		r = 255 - GetRValue(cr);
		g = 255 - GetGValue(cr);
		b = 255 - GetBValue(cr);
		m_btn_clr_terminal.SetTextColor(CLR_DEFAULT);
		break;
		
	case IDC_BTN_CLR_INFO:
		cr = m_btn_clr_info.GetColor();
		m_rich_edit.setCfColor(CF_INFO,cr);
		r = 255 - GetRValue(cr);
		g = 255 - GetGValue(cr);
		b = 255 - GetBValue(cr);
		m_btn_clr_info.SetTextColor(CLR_DEFAULT);
		break;
		
	case IDC_BTN_CLR_UNPACK:
		cr = m_btn_clr_unpack.GetColor();
		m_rich_edit.setCfColor(CF_INFO,cr);

		r = 255 - GetRValue(cr);
		g = 255 - GetGValue(cr);
		b = 255 - GetBValue(cr);
		m_btn_clr_unpack.SetTextColor(CLR_DEFAULT);
		break;

	default:
		break;
	}



	
    
}

void CNxMasterDlg::OnCheckAutoUnpack() 
{
	// TODO: Add your control notification handler code here
	m_bAutoUnpack = m_check_auto_unpack.GetCheck();
}

// 获取当前系统时间
CString CNxMasterDlg::GetCurTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strTime;
	strTime.Format("%02d:%02d:%02d %03d",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
    //strTime.Format("%02d:%02d:%02d %03d ms",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	//strTime.Format("%02d点%02d分%02d秒%03d毫秒",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	return strTime;
}

CString CNxMasterDlg::GetCurDate()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	CString strDate;
	strDate.Format("%4d/%d/%d",st.wYear,st.wMonth,st.wDay);

	return strDate;

}

void CNxMasterDlg::insertInfoTmlSend(CTerminalSock *pSock, int len)
{
	if (pSock == NULL)
	{
		return;
	}

	CString strMasterIP;
	CString strTime,strInsert;
	CString strMaster;
	CString strTerminal;
	
	CString strTmlID;
	CString strIp;
	CString strSendNum;
	UINT rPeerPort;

	strTime = GetCurTime();
	strMaster   = "主站";
	strTerminal = "终端";
	strSendNum.Format("[%d]字节:\r\n",len);
	pSock->GetSockName(strMasterIP,rPeerPort);
	strTmlID.Format("%d",m_terminalId);
	strIp = m_strLocalIP;
	//strInsert ="["+strTime +"] " +" [" + strMasterIP + "] " +strMaster+" <- "+ strTerminal+"[" +strTmlID+"]" + "["+strIp+"]" + " 应答 长度" + strSendNum;

	strInsert ="["+strTime +"] " +strTerminal+ " -> "+ strMaster+" [" + strMasterIP + "] " + " 回复" + strSendNum;
	m_rich_edit.cfAppend(strInsert,CF_INFO);
}

void CNxMasterDlg::insertInfoTmlRecv(CTerminalSock *pSock, int len)
{
	if (pSock == NULL)
	{
		return;
	}
	
	CString strMasterIP;
	CString strTime,strInsert;
	CString strMaster;
	CString strTerminal;
	
	CString strTmlID;
	CString strIp;
	CString strSendNum;
	UINT rPeerPort;
	
	strTime = GetCurTime();
	strMaster   = "主站";
	strTerminal = "终端";
	strSendNum.Format("[%d]字节:\r\n",len);
	pSock->GetSockName(strMasterIP,rPeerPort);
	strTmlID.Format("%d",m_terminalId);
	strIp = m_strLocalIP;
//	strInsert ="["+strTime +"] " +" [" + strMasterIP + "] " +strMaster+" -> "+ strTerminal+"[" +strTmlID+"]" + "["+strIp+"]" + " 命令 长度" + strSendNum;

	strInsert ="["+strTime +"] " +strTerminal+ " <- "+ strMaster+" [" + strMasterIP + "] " + " 命令" + strSendNum;

	m_rich_edit.cfAppend(strInsert,CF_INFO);
}


void CNxMasterDlg::InsertInfoMasterRecv(CTerminal *pTml, int len)
{
	if(pTml == NULL)
	{
		return;
	}
	
	CString strTime,strInsert;
	CString strMaster;
	CString strTerminal;
	CString strIP;
	CString strTmlID;
	CString strObjID;   // 终端对象ID
	CString strSendNum;
	strTime = GetCurTime();
	strMaster   = "主站";
	strTerminal = "终端";
	strIP = pTml->m_strTerminalIp;
	strTmlID.Format("%d",pTml->m_address);
	strObjID.Format("%X", (unsigned int)pTml);
	strSendNum.Format("[%d]字节:\r\n",len);
	
	
	
	strInsert ="["+strTime +"] " +strMaster+" <- "+ strTerminal+" [" +strTmlID+"]" +"[" +strIP+"]" + "["+strObjID+"]" + " 应答" + strSendNum;
    //strInsert ="["+strTime +"] " +strMaster+"收到"+ strTerminal+" [" +strTmlID+"]" +"[" +strIP+"]" + "["+strObjID+"]" + "发来" + strSendNum;
	
	
	m_rich_edit.cfAppend(strInsert,CF_INFO);
}
// 主站向某终端发送len命令的提示消息，将其插入richedit
void CNxMasterDlg::InsertInfoMasterSend(CTerminal *pTml, int len)
{
	// [time] 

	if(pTml == NULL)
	{
		return;
	}

	CString strTime,strInsert;
	CString strMaster;
	CString strTerminal;
	CString strIP;
	CString strTmlID;
	CString strObjID;   // 终端对象ID
	CString strSendNum;
	strMaster   = "主站";
	strTerminal = "终端";
	strIP = pTml->m_strTerminalIp;
	strTmlID.Format("%d",pTml->m_address);
	strObjID.Format("%X", (unsigned int)pTml);
	strSendNum.Format("[%d]字节:\r\n",len);
	
	strTime = GetCurTime();
	
	strInsert ="["+strTime +"] " + strMaster+" -> "+strTerminal+" [" +strTmlID+"]" +"[" +strIP+"]" + "["+strObjID+"]" + " 命令" + strSendNum;
	//strInsert ="["+strTime +"] " + strMaster+"发给"+strTerminal+" [" +strTmlID+"]" +"[" +strIP+"]" + "["+strObjID+"]" + "命令" + strSendNum;

	
	m_rich_edit.cfAppend(strInsert,CF_INFO);
}


// 通过socket指针获得对应的通信终端对象指针
CTerminal* CNxMasterDlg::GetCTerminal(CServerSock *pSock)
{

	if(pSock == NULL)
	{
		return NULL;
	}

	CTerminal *pTml;
	CServerSock *pSockTmp;

	POSITION pos = m_listTml.GetHeadPosition();
	while(pos != NULL)
	{
		
		pTml = (CTerminal*)m_listTml.GetNext(pos);
		pSockTmp = pTml->m_pSevSocket;
		if(pSockTmp == pSock)
		{
			return pTml;
		}
	}

	return NULL;
}

void CNxMasterDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}


// 初始化主界面tabctrl
void CNxMasterDlg::InitTabCtrl()
{
	if (m_imagelist == NULL)
	{
		m_imagelist = new CImageList;
	}
	
	
	m_imagelist->Create(16,16,ILC_COLOR32,0,0);
	m_imagelist->SetBkColor(GetSysColor(COLOR_MENU));
	HICON hicon[TAB_INDEX_MAX];//图标的句柄
	
	hicon[TAB_INDEX_PACK] = AfxGetApp()->LoadIcon(IDI_ICON14);
	hicon[TAB_INDEX_PRE_MASTER] = AfxGetApp()->LoadIcon(IDI_ICON9);
	hicon[TAB_INDEX_PRE_TERMINAL]= AfxGetApp()->LoadIcon(IDI_ICON12);
	hicon[TAB_INDEX_UNPACK] = AfxGetApp()->LoadIcon(IDI_ICON18);
	hicon[TAB_INDEX_TASK] = AfxGetApp()->LoadIcon(IDI_ICON22);
	
	
	//加入图标
	for (int i = 0; i < TAB_INDEX_MAX; i++)
	{
		m_imagelist->Add(hicon[i]);
	}
	
	m_tab.SetImageList(m_imagelist);



	m_tab.InsertItem(TAB_INDEX_PACK, TAB_NAME_PACK, TAB_INDEX_PACK);
	m_tab.InsertItem(TAB_INDEX_PRE_MASTER, TAB_NAME_PRE_MASTER, TAB_INDEX_PRE_MASTER);
	m_tab.InsertItem(TAB_INDEX_PRE_TERMINAL, TAB_NAME_PRE_TERMINAL,TAB_INDEX_PRE_TERMINAL);
	m_tab.InsertItem(TAB_INDEX_UNPACK, TAB_NAME_UNPACK,TAB_INDEX_UNPACK);
	m_tab.InsertItem(TAB_INDEX_TASK, TAB_NAME_TASK,TAB_INDEX_TASK);
	

	
	BOOL bXpStyle = TRUE;
	m_tab.SetExtended(bXpStyle);
	ETabOrientation eTabOrientation = e_tabTop;
	//ETabOrientation eTabOrientation = e_tabLeft;
	m_tab.ModifyStyle(TCS_VERTICAL|TCS_BOTTOM|TCS_MULTILINE,(eTabOrientation&1?TCS_BOTTOM:0) | 
		(eTabOrientation>e_tabBottom?(TCS_VERTICAL|(bXpStyle && IsThemeActiveXP()?0:TCS_MULTILINE)):0));

	m_tabDlgPreMst.Create(IDD_DLG_PRE_MST,&m_tab);
	m_tabDlgPreTml.Create(IDD_DLG_PRE_TML,&m_tab);
	m_tabDlgPack.Create(IDD_DLG_PACK,&m_tab);
	m_tabDlgPack.setMainDlg(this);
	m_tabDlgUnpack.Create(IDD_DLG_UNPACK,&m_tab);
	m_tabDlgUnpack.setMainDlg(this);
	m_tabDlgTask.Create(IDD_DLG_TASK,&m_tab);
	m_tabDlgTask.setMainDlg(this);

	showTabDlg(0);

	
}

void CNxMasterDlg::showTabDlg(int index)
{
	if(index >= TAB_INDEX_MAX)
	{
		return;
	}
	
	int nCmdShow = 0; 
	
	if(m_tabDlgPack.m_hWnd)
	{
		nCmdShow = (index == TAB_INDEX_PACK) ? SW_SHOW : SW_HIDE;
		m_tabDlgPack.ShowWindow(nCmdShow) ;
	}
	
	if(m_tabDlgPreMst.m_hWnd)
	{
		nCmdShow = (index == TAB_INDEX_PRE_MASTER) ? SW_SHOW : SW_HIDE;
		m_tabDlgPreMst.ShowWindow(nCmdShow);
	}

	if(m_tabDlgUnpack.m_hWnd)
	{
		nCmdShow = (index == TAB_INDEX_UNPACK) ? SW_SHOW : SW_HIDE;
		m_tabDlgUnpack.ShowWindow(nCmdShow);
	}
	
	if(m_tabDlgTask.m_hWnd)
	{
		nCmdShow = (index == TAB_INDEX_TASK) ? SW_SHOW : SW_HIDE;
		m_tabDlgTask.ShowWindow(nCmdShow);
	}
	
	if(m_tabDlgPreTml.m_hWnd)
	{
		nCmdShow = (index == TAB_INDEX_PRE_TERMINAL) ? SW_SHOW : SW_HIDE;
		m_tabDlgPreTml.ShowWindow(nCmdShow);
	}	

}


void CNxMasterDlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int index = 0;
	index = m_tab.GetCurSel();
	showTabDlg(index);
	*pResult = 0;
}


















































// 以下为调试部分，正式版本将 调试开关 NX_MASTER_DBG 关闭
#ifdef NX_MASTER_DBG
void CNxMasterDlg::test_GetMstPreAfn04F1()
{
	CString str;
	sMtAfn04F1 stCfg;
	m_preConfig.GetMstPreAfn04F1(&stCfg);
	
	str.Format("test_GetMstPreAfn04F1()\n"
		        "ucRTS = %X\n"
				"ucRTM = %X\n"
				"ucReSendTimes = %X\n"
				"ucHeartBeat = %d\n"
				"usTmWaitTimeoutS = %d\n"
				"bAutoReportAsk_1 = %s\n"
				"bAutoReportAsk_2 = %s\n"
				"bAutoReportAsk_3 = %s\n",
				stCfg.ucRTS,
				stCfg.ucRTM,
				stCfg.ucReSendTimes,
				stCfg.ucHeartBeat,
				stCfg.usTmWaitTimeoutS,
				stCfg.bAutoReportAsk_1 == TRUE ? "true" : "false",
				stCfg.bAutoReportAsk_2 == TRUE ? "true" : "false",
				stCfg.bAutoReportAsk_3 == TRUE ? "true" : "false");

	m_rich_edit.cfAppend(str, CF_TERMINAL);

}

#endif

void CNxMasterDlg::OnClearRichEdit() 
{
	// TODO: Add your command handler code here
	m_rich_edit.SetWindowText("");
 
}

/************************************************************************/
/* 文本方式显示解析结果(gb31)                                          */
/************************************************************************/
void CNxMasterDlg::showUnpackText31( smcPack *psmcPack )
{
	if(!psmcPack)
	{
		return;
	}

	// 地址信息
	// 显示命令生成结果
	COLORREF crNormal, crValue, crText;
	UINT8   crR, crG, crB;
	char *pstr = NULL;
	
	CString strValue;
	CString strTmp;
	int i = 0;
	int nCmdNum = 0;
	eMcDir eDir;


	crNormal = RGB(0,0,0);
	crValue  = RGB(0,0,255);
	crText = RGB(255,128,255);

    //m_rich_edit.AppendColor("\n报文解析成功!:\n",RGB(255,0,0));
	// 方向
	eDir = psmcPack->sCtrl.eDir;
	strValue.Format("%s\n", eDir == MC_DIR_S2M ? "从站到主站" :  "主站到从站");
	m_rich_edit.AppendColor("报文方向:",crNormal);
	m_rich_edit.AppendColor(strValue,RGB(255,0,0));
	
	// 地址信息		
	m_rich_edit.AppendColor("主站地址:",crNormal);
	strValue.Format("%d\n", psmcPack->sAddress.ucMstAddress);
	m_rich_edit.AppendColor(strValue,crValue);
	

	m_rich_edit.AppendColor("行政区码:",crNormal);
	strValue.Format("%c%c%c%c%c%c\n", 
					psmcPack->sAddress.acRegionCode[0],
					psmcPack->sAddress.acRegionCode[1],
					psmcPack->sAddress.acRegionCode[2],
					psmcPack->sAddress.acRegionCode[3],
					psmcPack->sAddress.acRegionCode[4],
					psmcPack->sAddress.acRegionCode[5]);

	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("终端地址:",crNormal);
	strValue.Format("%d\n", psmcPack->sAddress.ulConAddress);
	m_rich_edit.AppendColor(strValue,RGB(255,0,0));

	
	m_rich_edit.AppendColor("是组地址:",crNormal);
	strValue.Format("%s\n", psmcPack->sAddress.bTeam == TRUE ? "是": "否");
	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("组帧类型:",crNormal);
	strValue.Format("%s\n", psmcPack->bFixed  == TRUE ? "固定帧": "可变帧");
	m_rich_edit.AppendColor(strValue,crValue);


	m_rich_edit.AppendColor("主动从动:",crNormal);
	strValue.Format("%s\n", psmcPack->sCtrl.ePRM == MC_PRM_A2P ? "来自主动站": "来自从动站");
	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("启动序列:",crNormal);
	strValue.Format("%d\n", psmcPack->sCtrl.ucPSEQ);
	m_rich_edit.AppendColor(strValue,crValue);

	m_rich_edit.AppendColor("响应序列:",crNormal);
	strValue.Format("%d\n", psmcPack->sCtrl.ucRSEQ);
	m_rich_edit.AppendColor(strValue,crValue);

	// 固定帧
	if (psmcPack->bFixed == TRUE)
	{
		switch(psmcPack->sCtrl.eFcode)
        {
		case MC_FCD_LINK_OK:
            pstr = "链路确认";
            break;
			
		case MC_FCD_LOG_IN:
            pstr = "建立链路、登录系统";
            break;
			
		case MC_FCD_LOG_OUT:
            pstr = "拆除链路、退出系统";
            break;
			
		case MC_FCD_HEART_BEAT:
            pstr = "保持链路、在线心跳";
            break;
			
		default:
            pstr = "错误的功能码";
            break;			
        }
	}
	else
	{
		switch(psmcPack->sCtrl.eFcode)
        {
		case MC_FCD_OK:  
            //case MC_FCD_NOTI:
			if(psmcPack->sCtrl.ePRM == MC_PRM_A2P)
			{
				pstr = "发送/无回答";
			}
			else
			{
				pstr = "链路用户确认";
			}
			
            break;
			
		case MC_FCD_ANSWER:
            //case MC_FCD_CONF:
			if(psmcPack->sCtrl.ePRM == MC_PRM_A2P)
			{
				pstr = "以用户数据响应请求";
			}
			else
			{
				pstr = "发送/确认";
			}
			
            break;
            
		case MC_FCD_ASK:
            pstr = "请求/响应";
            break;
			
		default:
            pstr = "错误的功能码";
            break;
        }
	}

	m_rich_edit.AppendColor("功能码值:",crNormal);
	strValue.Format("%d  ", psmcPack->sCtrl.eFcode);
	m_rich_edit.AppendColor(strValue, crValue);

	strValue.Format("%s\n", pstr);
	m_rich_edit.AppendColor(strValue, RGB(255,0,0));
	
	if (psmcPack->bFixed == FALSE)
	{
		
		m_rich_edit.AppendColor("时间标签:",crNormal);
		strValue.Format("%s", psmcPack->sAc.bTp == TRUE ? "有 ": "无\n");
		m_rich_edit.AppendColor(strValue, crValue);
		if(psmcPack->sAc.bTp == TRUE)
		{
			strValue.Format("%d日 %d:%d:%d\n",
				psmcPack->sTp.sTime.ucDD,
				psmcPack->sTp.sTime.ucHH,
				psmcPack->sTp.sTime.ucmm,
				psmcPack->sTp.sTime.ucss);
			m_rich_edit.AppendColor(strValue, RGB(255,0,0));
		}

		// ec
		m_rich_edit.AppendColor("事件计数:",crNormal);
		strValue.Format("%s", psmcPack->sAc.bEc == TRUE ? "有 ": "无\n");
		m_rich_edit.AppendColor(strValue, crValue);
		if(psmcPack->sAc.bEc == TRUE)
		{
			strValue.Format("EC1 = %d EC2 = %d\n", psmcPack->sEc.usEC1, psmcPack->sEc.usEC1);
			m_rich_edit.AppendColor(strValue,RGB(255,0,0));
		}

		// pw
		m_rich_edit.AppendColor("验证密码:",crNormal);
		strValue.Format("%s", psmcPack->bPw == TRUE ? "有": "无\n");
		m_rich_edit.AppendColor(strValue,crValue);		
		if (psmcPack->bPw)
		{
			char cPw[17] = {0};
			memcpy(cPw, psmcPack->aPw, 16);
			strValue.Format(" %s\n", cPw);
			m_rich_edit.AppendColor(strValue,RGB(255,0,0));
			
		}

		// afn
		m_rich_edit.AppendColor("应用功能:",crNormal);
		strValue.Format("%d  ", psmcPack->sAc.eAfn);
		m_rich_edit.AppendColor(strValue,crValue);

		switch(psmcPack->sAc.eAfn)
        {
		case MC_AFN_00_CONF:
			pstr = "确认否认";
			break;      
			
		case MC_AFN_01_RSET:
			pstr = "复位";
			break;   
			
		case MC_AFN_04_SETP:
			pstr = "设置参数";
			break;  
			
		case MC_AFN_05_CTRL:
			pstr = "控制命令";
			break;          
			
		case MC_AFN_06_AUTH:
			pstr = "身份认证及密钥协商";
			break;      
			
		case MC_AFN_08_CASC:
			pstr = "请求被级联终端主动上报";
			break;
			
		case MC_AFN_10_GETP:
			pstr = "查询参数";
			break;   
			
		case MC_AFN_12_ASKT:
			pstr = "请求（定时上报）任务数据";
			break;  
			
		case MC_AFN_13_ASKR:
			pstr = "请求实时数据";
			break;          
			
		case MC_AFN_14_ASKE:
			pstr= "请求（主动上报）事件记录";
			break;      
			
		case MC_AFN_15_FILE:
			pstr= "文件传输";
			break;
			
		case MC_AFN_16_DATA:
			pstr = "数据转发";
			break;
			
		default:
			pstr = "未知AFN";
			break;
			
        }

		strValue.Format("%s\n", pstr);
	    m_rich_edit.AppendColor(strValue,RGB(255,0,0));

		// 显示命令数据
		// 子命令个数
		nCmdNum = psmcPack->usNum;
		m_rich_edit.AppendColor("命令个数:",crNormal);
		strValue.Format("%d\n", nCmdNum);
     	m_rich_edit.AppendColor(strValue,RGB(255,0,0));
	
		// subcmd infor
		for (i = 0; i < nCmdNum; i++)
		{	
			crR = rand() % 255;
			crG = rand() % 255;
			crB = rand() % 255;
			crText = RGB(crR,crG,crB);

			
			if (nCmdNum != 1)
			{	
			
				
				m_rich_edit.AppendColor("\n命令序号:",RGB(0,0,0));
				//m_rich_edit.AppendColor("命令数据:",crText);

				m_rich_edit.AppendColor("━━━━━━━━━━━━━",crText);
				strValue.Format(" %d ", i+1);
				m_rich_edit.AppendColor(strValue, RGB(0,0,0));
				m_rich_edit.AppendColor("━━━━━━━━━━━━━\n",crText);

	/*
				m_rich_edit.AppendColor("┏━━━━━━━━━━━━━",crText);
				strValue.Format(" %d ", i+1);
				m_rich_edit.AppendColor(strValue, RGB(0,0,0));
				m_rich_edit.AppendColor("━━━━━━━━━━━━━┓\n",crText);


				m_rich_edit.AppendColor("\n命令序号:",RGB(0,0,0));
				//m_rich_edit.AppendColor("命令数据:",crText);
				m_rich_edit.AppendColor("╭──────────",crText);
				strValue.Format(" %d ", i+1);
				m_rich_edit.AppendColor(strValue, RGB(0,0,0));
				m_rich_edit.AppendColor("──────────╮\n",crText);
				*/
			}
			
			//showSubData31(psmcPack->sData + i, eDir,crText);
			showSubData31(psmcPack->sData + i, eDir,RGB(0,0,0));
		}
	}


	
#if 0



	


#endif
}


/************************************************************************/
/* 文本方式显示解析结果(3761)                                            */
/************************************************************************/
void CNxMasterDlg::showUnpackText( smtPack *psmtPack )
{
	
	if(!psmtPack)
	{
		return;
	}

	psmtPack->sAddress.acRegionCode;
	

	// 地址信息
	// 显示命令生成结果
	COLORREF crNormal, crValue, crText;
	UINT8   crR, crG, crB;
	crText = RGB(255,128,255);

	CString strValue;
	CString strTmp;
	char *pStr = NULL;
	int i = 0;
	int nCmdNum = 0;
	eMtDir eDir;

	crNormal = RGB(0,0,0);
	crValue  = RGB(0,0,255);
	
    //m_rich_edit.AppendColor("\n报文解析成功!:\n",RGB(255,0,0));
	// 方向
	eDir = psmtPack->eDir;
	strValue.Format("%s\n", eDir == MT_DIR_S2M ? "从站到主站" :  "主站到从站");
	m_rich_edit.AppendColor("报文方向:",crNormal);
	m_rich_edit.AppendColor(strValue,RGB(255,0,0));
	
	// 地址信息
	
	//m_pNxMstDlg->m_rich_edit.AppendColor("地址信息:\n",crNormal);
	
	m_rich_edit.AppendColor("主站地址:",crNormal);
	strValue.Format("%d\n", psmtPack->sAddress.ucMAddress);
	m_rich_edit.AppendColor(strValue,crValue);
	

	m_rich_edit.AppendColor("行政区码:",crNormal);
	strValue.Format("%c%c%c%c\n", 
					psmtPack->sAddress.acRegionCode[0],
					psmtPack->sAddress.acRegionCode[1],
					psmtPack->sAddress.acRegionCode[2],
					psmtPack->sAddress.acRegionCode[3]);
	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("终端地址:",crNormal);
	strValue.Format("%d\n", psmtPack->sAddress.usTAddress);
	m_rich_edit.AppendColor(strValue,RGB(255,0,0));


	m_rich_edit.AppendColor("是组地址:",crNormal);
	strValue.Format("%s\n", psmtPack->sAddress.bTeamAddr == TRUE ? "是": "否");
	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("主动从动:",crNormal);
	strValue.Format("%s\n", psmtPack->ePRM == MT_PRM_ACTIVE ? "来自主动站": "来自从动站");
	m_rich_edit.AppendColor(strValue,crValue);
	

/*
	m_rich_edit.AppendColor("功能码值:",crNormal);
	strValue.Format("%d ", psmtPack->ePRM);
	m_rich_edit.AppendColor(strValue,crValue);
	

	if(psmtPack->ePRM == MT_PRM_ACTIVE)
	{
		switch(psmtPack->sCtrl.uFCode.eFcdPrm1)
		{
		case FCD_PRM_1_RESET:
			strValue = "FCD_PRM_1_RESET 复位命令";		
			break;
		case FCD_PRM_1_USER:
			strValue = "FCD_PRM_1_USER 用户数据";		
			break;
		case FCD_PRM_1_LINK:
			strValue = "FCD_PRM_1_LINK 链路测试";		
			break;
		case FCD_PRM_1_ASK_1:
			strValue = "FCD_PRM_1_ASK_1 请求1级数据";		
			break;
		case FCD_PRM_1_ASK_2:
			strValue = "FCD_PRM_1_ASK_2 请求2级数据";		
			break;
		default:
			strValue = "FCD_PRM_1_UNKOWN";		
			break;
		}
	}
	else if(psmtPack->sCtrl.ePRM == MT_PRM_PASIVE)
	{
		switch(psmtPack->sCtrl.uFCode.eFcdPrm0)
		{
		case FCD_PRM_0_OK:
			strValue = "FCD_PRM_0_OK 认可";		
			break;
		case FCD_PRM_0_USER:
			strValue = "FCD_PRM_0_USER 用户数据";		
			break;
		case FCD_PRM_0_NONE:
			strValue = "FCD_PRM_0_NONE 否认:无所召唤的数据";		
			break;
		case FCD_PRM_0_LINK:
			strValue = "FCD_PRM_0_LINK 链路状态";		
			break;
		default:
			strValue = "FCD_PRM_1_UNKOWN 未知功能码";		
			break;
		}

	}
	strValue += "\n";
	m_rich_edit.AppendColor(strValue,crValue);
*/

	m_rich_edit.AppendColor("帧计数器:",crNormal);
	if (psmtPack->ePRM == MT_PRM_ACTIVE)
	{
		strValue.Format("PRES = %d\n", psmtPack->ucSeq);
	}
	else
	{
		strValue.Format("RSEQ = %d\n", psmtPack->ucSeq);
	}

	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("需要确认:",crNormal);
	strValue.Format("%s\n", psmtPack->bCon == TRUE ? "需要" : "不需要");
	m_rich_edit.AppendColor(strValue,crValue);

	m_rich_edit.AppendColor("事件计数:",crNormal);
	if(psmtPack->bEC == TRUE)
	{
		strValue.Format("EC1 = %d EC2 = %d\n", psmtPack->sEC.ucEC1, psmtPack->sEC.ucEC2);
	}
	else
	{
		strValue = "无\n";
	}

	m_rich_edit.AppendColor(strValue,crValue);

	//tp
	m_rich_edit.AppendColor("封装时间:",crNormal);
	if(psmtPack->bTP == TRUE)
	{
		strValue.Format("%d日 %02d:%02d:%02d\n", 
			psmtPack->sTP.sDDHHmmss.ucDD,
			psmtPack->sTP.sDDHHmmss.ucHH,
			psmtPack->sTP.sDDHHmmss.ucmm,
			psmtPack->sTP.sDDHHmmss.ucss);
	}
	else
	{
		strValue = "无\n";
	}
	
	m_rich_edit.AppendColor(strValue,crValue);
	
	// 允许时延
	m_rich_edit.AppendColor("允许时延:",crNormal);
	strValue.Format("%d分钟\n", psmtPack->sTP.ucPermitDelayMinutes);
	m_rich_edit.AppendColor(strValue,crValue);

	//pw 
	m_rich_edit.AppendColor("登录密码:",crNormal);
	if (psmtPack->bPW == TRUE)
	{		
		strValue.Format("%s\n",psmtPack->acPW);
	}
	else
	{
		strValue = "无\n";
	}

	m_rich_edit.AppendColor(strValue,crValue);

	// main cmd
	m_rich_edit.AppendColor("主命令值:",crNormal);
	CQgdw3761api ruler;
	strValue = ruler.GetAfnName(psmtPack->eAFN);
		strValue += "\n";
	m_rich_edit.AppendColor(strValue,crValue);

	// 子命令个数
	nCmdNum = psmtPack->usDataNum;
	m_rich_edit.AppendColor("命令个数:",crNormal);
	strValue.Format("%d\n", nCmdNum);
	m_rich_edit.AppendColor(strValue,RGB(255,0,0));
	
	// subcmd infor
	for (i = 0; i < nCmdNum; i++)
	{	
		crR = rand() % 255;
		crG = rand() % 255;
		crB = rand() % 255;
		crText = RGB(crR,crG,crB);

		if (nCmdNum != 1)
		{	
			
			//m_rich_edit.AppendColor("命令数据:",RGB(0,0,0));
			m_rich_edit.AppendColor("命令数据:",crText);
			m_rich_edit.AppendColor("---------------------",crText);
			strValue.Format(" %d ", i+1);
			m_rich_edit.AppendColor(strValue,RGB(0,0,0));
			m_rich_edit.AppendColor("---------------------\n",crText);
		}
			
		showSubData(psmtPack->sData + i, eDir,crText);
		//showSubData(psmtPack->sData + i, eDir,RGB(0,0,0));
	}

}

// 获得事件对应的名称
char * CNxMasterDlg::pStrGetErcName( UINT8 ucErc )
{
	char *pStr = NULL;

	switch(ucErc)
	{
	case MC_ERC_1_RESET:
		pStr = "ERC1: 复位事件";
		break;
		
	case MC_ERC_2_DATA_CLEAR:
		pStr = "ERC2: 指定数据清零事件";
		break;
		
	case MC_ERC_3_SOFT_CHANGE:
		pStr = "ERC3: 软件版本变更事件";
		break;
		
	case MC_ERC_4_PARA_CHANGE:
		pStr = "ERC4: 参数变更事件";
		break;
		
	case MC_ERC_5_CHECK_TIME:
		pStr = "ERC5: 校时事件";
		break;
		
	case MC_ERC_6_STATE_CHANGE:
		pStr = "ERC6: 状态量变位事件";
		break;
		
	case MC_ERC_7_REMOTE_SWITCH:
		pStr = "ERC7: 遥控跳闸事件";
		break;
	case MC_ERC_8_POWER_ON_OFF:
		pStr = "ERC8: 停/上电事件";
		break;
		
	case MC_ERC_9_FACTOR_OVER:
		pStr = "ERC9: 总功率因素越限事件";
		break;
		
	case MC_ERC_10_VOLT_EXCP:
		pStr = "ERC10: 电压偏差越限事件";
		break;
		
	case MC_ERC_11_VOLT_CIRCLE:
		pStr = "ERC11: 电压回路异常事件";
		break;
	case MC_ERC_12_ELEC_CRICLE:
		pStr = "ERC12: 电流回路异常事件";
		break;
	case MC_ERC_13_VOLT_OVER:
		pStr = "ERC13: 电压越限事件";
		break;
		
	case MC_ERC_14_ELEC_OVER:
		pStr = "ERC14: 电流越限事件";
		break;
		
	case MC_ERC_15_UNBL_OVER_V:
		pStr = "ERC15: 电压不平衡度越限事件";
		break;

	case MC_ERC_16_UNBL_OVER_I:
		pStr = "ERC16: 电流不平衡度越限事件";
		break;
		
	case MC_ERC_17_HUNBL_OVER_V:
		pStr = "ERC17: 谐波电压畸变率越限事件";
		break;
	case MC_ERC_18_HUNBL_OVER_I:
		pStr = "ERC18: 谐波电流畸变率越限事件";
		break;
	case MC_ERC_19_FLASH_OVER:
		pStr = "ERC19: 闪变越限事件";
		break;
		
	case MC_ERC_20_NELC_OVER:
		pStr = "ERC20: 非电气量越限事件";
		break;
		
	case MC_ERC_UNKOWN:
		pStr = "ERC0: 未知事件记录类型";
		break;
		
	default:
		pStr = "未知事件";
		break;
	}

	return pStr;
}

void CNxMasterDlg::insertLine()
{
	m_rich_edit.AppendColor("\n",RGB(0,0,0));
	//OnRichInsetLen();
}

// 显示gb31数据内容
void CNxMasterDlg::showSubData31( sMcData *psData, eMcDir eDir,COLORREF crText )
{
	if (!psData)
	{
		return;
	}
	
	COLORREF crNormal, crValue, crRed;
	CString strValue;
	CString strCmdName;
	char *pStr = NULL;
	sMcmdInfor cmdInfor;
	crNormal = RGB(0,0,0);
	int i, j;
	crValue  = RGB(0,0,255);
	crRed = RGB(255,0,0);
	eMcmd eCmd;
	UINT8 ucFn = 0;
	
	eMcErr eRet = eMcGetCmdInfor(psData->eCmd, eDir, &cmdInfor);
	if(eRet == MC_OK)
	{

		ucFn = (UINT16)psData->eCmd & 0xFF;
		strCmdName.Format("F%d ", ucFn);
		strCmdName += cmdInfor.pName;
		strCmdName += "\n";
	}
	else
	{
		strCmdName = "未知命令类型\n";
	}
	
	m_rich_edit.AppendColor("命令类型:",crText);
	strValue.Format("%04X ", (UINT16)psData->eCmd);
	m_rich_edit.AppendColor(strValue,crValue);

	m_rich_edit.AppendColor(strCmdName,RGB(255,0,0));
	
	// pn
	m_rich_edit.AppendColor("测量点号:",crText);
	strValue.Format("%-4d ", (UINT16)psData->usPN);
	m_rich_edit.AppendColor(strValue,crValue);
	


	


	switch (cmdInfor.ePn)
	{
	case MC_PN_P0:
		pStr = "集中器";
		break;

	case MC_PN_MP:
		pStr = "测量点号";
		break;
		
	case MC_PN_TK:
		pStr = "任务号";
		break;
		
	case MC_PN_TM:
		pStr = "终端号";
		break;

	default:
		pStr = "未知类型";
		break;
	}
	strValue.Format("%s\n", pStr);
    m_rich_edit.AppendColor(strValue, RGB(255,0,0));

	m_rich_edit.AppendColor("有无数据:",crText);
	strValue.Format("%s\n", psData->bApp == TRUE ? "有" : "无");
	m_rich_edit.AppendColor(strValue,crValue);
	
    // 没有数据
	if (psData->bApp == FALSE)
	{
		return;
	}

    m_rich_edit.AppendColor("数据内容:",crText);
	m_rich_edit.AppendColor("---",crValue);

	switch(psData->eCmd)
	{
	case MCMD_AFN_0_F1_ALL_OK_DENY:
		insertLine();
		m_rich_edit.AppendColor("\n确认或出错信息: ",crNormal);
		switch(psData->uApp.eResCode)
		{
			
		case MC_RES_OK:
			pStr = "0 确认";
			break;
			
		case MC_RES_NONE:
			pStr = "1 无请求的数据、无设置的参数、无要执行的功能";
			break;
			
		case MC_RES_NOT_READY:
			pStr = "2 请求的数据未产生、功能执行未满足";
			break;
			
		case MC_RES_REMOVE:
			pStr = "3 请求的数据已经被移出保存窗口";
			break;
			
		case MC_RES_DATA_OTRNG:
			pStr = "4 请求的数据超出支持的信息点范围";
			break;
			
		case MC_RES_PARA_OTRNG:
			pStr = "5 设置的参数超出支持的信息点范围";
			break;
			
		case MC_RES_NOT_SAME:
			pStr = "6 设置的接入端口号及属性与实际不符";
			break;
			
		case MC_RES_NOT_SUPT:
			pStr = "7 指定接口不支持转发";
			break;
			
		case MC_RES_DENY:
			pStr = "255 否认";
			break;
			
		default:
			pStr = "未知确认";
			break;
			
		}
		
		strValue.Format("%s\n", pStr);
		m_rich_edit.AppendColor(strValue, crRed);
		insertLine();
		break;
		
		case MCMD_AFN_0_F2_ONE_BY_ONE:
			{
				m_rich_edit.AppendColor("\n需要确认的AFN:",crNormal);
				strValue.Format("%d (", psData->uApp.sOneByOne.eAFN);
				switch(psData->uApp.sOneByOne.eAFN)
				{
				case MC_AFN_00_CONF:
					strValue += "确认否认";
					break;
					
				case MC_AFN_01_RSET:
					eDir = MC_DIR_M2S;
					strValue += "复位操作";
					break;
					
				case MC_AFN_02_LINK:
					eDir = MC_DIR_S2M;
					strValue += "登录、退出、心跳";
					break;
					
				case MC_AFN_04_SETP:
					eDir = MC_DIR_M2S;
					strValue += "设置参数";
					break;

				case MC_AFN_05_CTRL:
					eDir = MC_DIR_M2S;
					strValue += "控制命令";
					break;
				case MC_AFN_06_AUTH:
					strValue += "MC_AFN_00_CONF";
					break;
					
				case MC_AFN_08_CASC:
					strValue += "MC_AFN_08_CASC";
					break;
					
				case MC_AFN_10_GETP:
					strValue += "MC_AFN_10_GETP";
					break;
					
				case MC_AFN_12_ASKT:
					strValue += "MC_AFN_12_ASKT";
					break;
					
				case MC_AFN_13_ASKR:
					strValue += "MC_AFN_13_ASKR";
					break;
					
				case MC_AFN_14_ASKE:
					strValue += "MC_AFN_14_ASKE";
					break;
					
				case MC_AFN_15_FILE:
					strValue += "MC_AFN_15_FILE";
					break;
					
				case MC_AFN_16_DATA:
					strValue += "MC_AFN_16_DATA";
					break;							
				default:
					break;
				}

				strValue+= ")";
				m_rich_edit.AppendColor(strValue,crValue);

				
				m_rich_edit.AppendColor("\n需要确认个数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sOneByOne.ucNum);				
				m_rich_edit.AppendColor(strValue,crValue);

				for(i = 0; i < psData->uApp.sOneByOne.ucNum; i++)
				{
					strValue.Format("---------%d----------\n", i+1);
					
					m_rich_edit.AppendColor(strValue,crValue);
					
					eCmd = psData->uApp.sOneByOne.sOne[i].eCmd;
					
					eRet = eMcGetCmdInfor(eCmd, eDir, &cmdInfor);
					if(eRet == MC_OK)
					{
						strCmdName = cmdInfor.pName;
						
					}
					else
					{
						strCmdName = "未知命令类型";
					}
					
					strValue.Format("CMD = %04X  %s\n",eCmd, strCmdName);
					m_rich_edit.AppendColor(strValue,crValue);
					
					strValue.Format("PN  = %d\n", psData->uApp.sOneByOne.sOne[i].usPn);
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("结果: ",crNormal);
					switch(psData->uApp.sOneByOne.sOne[i].eResCode)
					{
						
					case MC_RES_OK:
						pStr = "0 确认";
						break;
						
					case MC_RES_NONE:
						pStr = "1 无请求的数据、无设置的参数、无要执行的功能";
						break;
						
					case MC_RES_NOT_READY:
						pStr = "2 请求的数据未产生、功能执行未满足";
						break;
						
					case MC_RES_REMOVE:
						pStr = "3 请求的数据已经被移出保存窗口";
						break;
						
					case MC_RES_DATA_OTRNG:
						pStr = "4 请求的数据超出支持的信息点范围";
						break;
						
					case MC_RES_PARA_OTRNG:
						pStr = "5 设置的参数超出支持的信息点范围";
						break;
						
					case MC_RES_NOT_SAME:
						pStr = "6 设置的接入端口号及属性与实际不符";
						break;
						
					case MC_RES_NOT_SUPT:
						pStr = "7 指定接口不支持转发";
						break;
						
					case MC_RES_DENY:
						pStr = "255 否认";
						break;
						
					default:
						pStr = "未知确认";
						break;
						
					}
					
					strValue.Format("%s\n", pStr);
					m_rich_edit.AppendColor(strValue, crRed);

				}

			}
			break;

		
		case MCMD_AFN_4_F1_CON_UP_CFG:
		case MCMD_AFN_A_F1_CON_UP_CFG:
			{
				insertLine();
				
				//UINT8  ucPermitDelayM;    //  (单位:分钟 0~255)
				m_rich_edit.AppendColor("\n集中器允许传输时延时间:", crNormal);
				strValue.Format("%d\n", psData->uApp.sConUpCfg.ucPermitDelayM);
				m_rich_edit.AppendColor(strValue,crValue);
				
				//UINT8  ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
				m_rich_edit.AppendColor("              重发次数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sConUpCfg.ucReSendTimes);
				m_rich_edit.AppendColor(strValue,crValue);
				
				//UINT8  ucHeartBeat;       // 心跳周期
				m_rich_edit.AppendColor("              心跳周期:",crNormal);
				strValue.Format("%d\n", psData->uApp.sConUpCfg.ucHeartBeat);
				m_rich_edit.AppendColor(strValue,crValue);
				
				//UINT16 usWaitTimeoutS;    // 信息集中与交互终端作为启动站等待应答的超时时间 (秒数 0~4095)
				m_rich_edit.AppendColor("集中器等待应答超时时间:",crNormal);
				strValue.Format("%d\n", psData->uApp.sConUpCfg.usWaitTimeoutS);
				m_rich_edit.AppendColor(strValue,crValue);
				
	
				m_rich_edit.AppendColor("允许主站确认，实时数据:",crNormal);
				strValue.Format("%s\n", psData->uApp.sConUpCfg.bPermitRt == TRUE ? "允许":"禁止");
				m_rich_edit.AppendColor(strValue,crValue);
				
	
				m_rich_edit.AppendColor("允许主站确认，任务数据:",crNormal);
				strValue.Format("%s\n", psData->uApp.sConUpCfg.bPermitTk == TRUE ? "允许":"禁止");
				m_rich_edit.AppendColor(strValue,crValue);
				
	
				m_rich_edit.AppendColor("允许主站确认，事件数据:",crNormal);
				strValue.Format("%s\n", psData->uApp.sConUpCfg.bPermitEv == TRUE ? "允许":"禁止");
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
				
			}
			break;

	

		case MCMD_AFN_4_F2_MST_PARA:
			{

				// ucNeed
				m_rich_edit.AppendColor("\n本次设置的主(子)站数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sMstPara.ucN);
				m_rich_edit.AppendColor(strValue,crValue);
				
				// aNeed
				for (i = 0; i < psData->uApp.sMstPara.ucN; i++)
				{
					//m_rich_edit.AppendColor("-----------------------------",RGB(0,255,0));
					strValue.Format("        -------第%d个主站参数-------\n", i + 1);
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("          主站编号:",crNormal);
					strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].ucID);
					m_rich_edit.AppendColor(strValue,crValue);
					
					
					m_rich_edit.AppendColor("        参数有效性:",crNormal);
					strValue.Format("%s\n", psData->uApp.sMstPara.sOne[i].bValid == TRUE ? "有效": "无效");
					m_rich_edit.AppendColor(strValue,crValue);
					
					
					m_rich_edit.AppendColor("排他性数据单元个数:",crNormal);
					strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].ucNoNum);
					m_rich_edit.AppendColor(strValue,crValue);
					
					for(j = 0; j < psData->uApp.sMstPara.sOne[i].ucNoNum; j++)
					{
						strValue.Format("     第%d个排他标识:",j+1);
						m_rich_edit.AppendColor(strValue,crText);
						
						eCmd = psData->uApp.sMstPara.sOne[i].sCmdPn[j].eCmd;
						eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &cmdInfor);
						if (eRet == MC_OK)
						{
							strValue.Format("F%-2d %s", eCmd&0xFF, cmdInfor.pName);
						}
						else
						{
							strValue = "未知命令";
						}
						m_rich_edit.AppendColor(strValue,crValue);
						
						strValue.Format("\n   第%d个排他测量点:",j+1);
						m_rich_edit.AppendColor(strValue,crText);
						strValue.Format("%d\n",j, psData->uApp.sMstPara.sOne[i].sCmdPn[j].usPn);
						m_rich_edit.AppendColor(strValue,crValue);
					}
					
					m_rich_edit.AppendColor("            主用IP:",crNormal);
					strValue.Format("%s %d.%d.%d.%d\n",
						psData->uApp.sMstPara.sOne[i].sMainIP.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
						psData->uApp.sMstPara.sOne[i].sMainIP.ip[0],
						psData->uApp.sMstPara.sOne[i].sMainIP.ip[1],
						psData->uApp.sMstPara.sOne[i].sMainIP.ip[2],
						psData->uApp.sMstPara.sOne[i].sMainIP.ip[3]);
					m_rich_edit.AppendColor(strValue,crValue);
					
					
					m_rich_edit.AppendColor("          主用端口:",crNormal);
					strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].usMainPort);
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("            备用IP:",crNormal);
					strValue.Format("%s %d.%d.%d.%d\n",
						psData->uApp.sMstPara.sOne[i].sBackIP.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
						psData->uApp.sMstPara.sOne[i].sBackIP.ip[0],
						psData->uApp.sMstPara.sOne[i].sBackIP.ip[1],
						psData->uApp.sMstPara.sOne[i].sBackIP.ip[2],
						psData->uApp.sMstPara.sOne[i].sBackIP.ip[3]);
					m_rich_edit.AppendColor(strValue,crValue);
					
					
					m_rich_edit.AppendColor("          备用端口:",crNormal);
					strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].usBackPort);
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("               APN:",crNormal);
					strValue = charToCString((char*)&psData->uApp.sMstPara.sOne[i].ucascAPN[0], 16);
					strValue+="\n";
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("            用户名:",crNormal);
					strValue = charToCString((char*)&psData->uApp.sMstPara.sOne[i].usr[0], 32);
					strValue+="\n";
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("              密码:",crNormal);
					strValue = charToCString((char*)&psData->uApp.sMstPara.sOne[i].pwd[0], 32);
					strValue+="\n";
					m_rich_edit.AppendColor(strValue,crValue);
				}
				
			}
			break;

		case MCMD_AFN_A_F2_MST_PARA:
			{
				insertLine();

				if (eDir == MC_DIR_M2S )
				{
					// ucNeed
					m_rich_edit.AppendColor("\n本次查询的主(子)站数:",crNormal);
					strValue.Format("%d\n", psData->uApp.sMstParaQ.ucN);
					m_rich_edit.AppendColor(strValue,crValue);
					for (i = 0; i < psData->uApp.sMstParaQ.ucN; i++)
					{
						strValue.Format("   第%d个主(子)站编号:", i + 1);
						m_rich_edit.AppendColor(strValue,crText);
						strValue.Format("%d\n", psData->uApp.sMstParaQ.ucID[i]);
						m_rich_edit.AppendColor(strValue,crValue);
					 }
				}
				else
				{
					// ucNeed
					m_rich_edit.AppendColor("\n本次设置的主(子)站数:",crNormal);
					strValue.Format("%d\n", psData->uApp.sMstPara.ucN);
					m_rich_edit.AppendColor(strValue,crValue);
					
					// aNeed
					for (i = 0; i < psData->uApp.sMstPara.ucN; i++)
					{
						//m_rich_edit.AppendColor("-----------------------------",RGB(0,255,0));
						strValue.Format("        -------第%d个主站参数-------\n", i + 1);
						m_rich_edit.AppendColor(strValue,crValue);
						
						m_rich_edit.AppendColor("          主站编号:",crNormal);
						strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].ucID);
						m_rich_edit.AppendColor(strValue,crValue);
						
						
						m_rich_edit.AppendColor("        参数有效性:",crNormal);
						strValue.Format("%s\n", psData->uApp.sMstPara.sOne[i].bValid == TRUE ? "有效": "无效");
						m_rich_edit.AppendColor(strValue,crValue);
						
						
						m_rich_edit.AppendColor("排他性数据单元个数:",crNormal);
						strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].ucNoNum);
						m_rich_edit.AppendColor(strValue,crValue);
						
						for(j = 0; j < psData->uApp.sMstPara.sOne[i].ucNoNum; j++)
						{
							strValue.Format("     第%d个排他标识:",j+1);
							m_rich_edit.AppendColor(strValue,crText);
							
							eCmd = psData->uApp.sMstPara.sOne[i].sCmdPn[j].eCmd;
							eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &cmdInfor);
							if (eRet == MC_OK)
							{
								strValue.Format("F%-2d %s", eCmd&0xFF, cmdInfor.pName);
							}
							else
							{
								strValue = "未知命令";
							}
							m_rich_edit.AppendColor(strValue,crValue);
							
							strValue.Format("\n   第%d个排他测量点:",j+1);
							m_rich_edit.AppendColor(strValue,crText);
							strValue.Format("%d\n",j, psData->uApp.sMstPara.sOne[i].sCmdPn[j].usPn);
							m_rich_edit.AppendColor(strValue,crValue);
						}
						
						m_rich_edit.AppendColor("            主用IP:",crNormal);
						strValue.Format("%s %d.%d.%d.%d\n",
							psData->uApp.sMstPara.sOne[i].sMainIP.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
							psData->uApp.sMstPara.sOne[i].sMainIP.ip[0],
							psData->uApp.sMstPara.sOne[i].sMainIP.ip[1],
							psData->uApp.sMstPara.sOne[i].sMainIP.ip[2],
							psData->uApp.sMstPara.sOne[i].sMainIP.ip[3]);
						m_rich_edit.AppendColor(strValue,crValue);
						
						
						m_rich_edit.AppendColor("          主用端口:",crNormal);
						strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].usMainPort);
						m_rich_edit.AppendColor(strValue,crValue);
						
						m_rich_edit.AppendColor("            备用IP:",crNormal);
						strValue.Format("%s %d.%d.%d.%d\n",
							psData->uApp.sMstPara.sOne[i].sBackIP.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
							psData->uApp.sMstPara.sOne[i].sBackIP.ip[0],
							psData->uApp.sMstPara.sOne[i].sBackIP.ip[1],
							psData->uApp.sMstPara.sOne[i].sBackIP.ip[2],
							psData->uApp.sMstPara.sOne[i].sBackIP.ip[3]);
						m_rich_edit.AppendColor(strValue,crValue);
						
						
						m_rich_edit.AppendColor("          备用端口:",crNormal);
						strValue.Format("%d\n", psData->uApp.sMstPara.sOne[i].usBackPort);
						m_rich_edit.AppendColor(strValue,crValue);
						
						m_rich_edit.AppendColor("               APN:",crNormal);
						strValue = charToCString((char*)&psData->uApp.sMstPara.sOne[i].ucascAPN[0], 16);
						strValue+="\n";
						m_rich_edit.AppendColor(strValue,crValue);
						
						m_rich_edit.AppendColor("            用户名:",crNormal);
						strValue = charToCString((char*)&psData->uApp.sMstPara.sOne[i].usr[0], 32);
						strValue+="\n";
						m_rich_edit.AppendColor(strValue,crValue);
						
						m_rich_edit.AppendColor("              密码:",crNormal);
						strValue = charToCString((char*)&psData->uApp.sMstPara.sOne[i].pwd[0], 32);
						strValue+="\n";
						m_rich_edit.AppendColor(strValue,crValue);
					}
				

				}
			
			
				insertLine();
				
			}
			break;

		case MCMD_AFN_4_F3_CON_AUTH_PARA:
		case MCMD_AFN_A_F3_CON_AUTH_PARA:
			{
				insertLine();
				// ucNeed
				m_rich_edit.AppendColor("\n认证方案:",crNormal);
				strValue.Format("%d ", psData->uApp.sAuthPara.ucTypeID);
				m_rich_edit.AppendColor(strValue,crValue);
				CString strInfo;
				if ( psData->uApp.sAuthPara.ucTypeID == 0)
				{
					strInfo = "不认证";
				}
				else if (psData->uApp.sAuthPara.ucTypeID == 255)
				{
					strInfo = "硬件认证方案";
				}
				else
				{
					strInfo = "软件认证方案";
				}
				m_rich_edit.AppendColor(strInfo,RGB(255,0,0));
				
				// usAuthPara
				m_rich_edit.AppendColor("\n认证参数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sAuthPara.usAuthPara);
				m_rich_edit.AppendColor(strValue,crValue);				
		
				insertLine();				
			}
			break;	

		case MCMD_AFN_4_F5_CON_IP_PORT:
		case MCMD_AFN_A_F5_CON_IP_PORT:
			{
				insertLine();
				
				m_rich_edit.AppendColor("\n信息集中与交互终端侦听端口:",crNormal);
				strValue.Format("%d\n", psData->uApp.sIpPort.usPort);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("   信息集中与交互终端IP地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
								psData->uApp.sIpPort.sConIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
								psData->uApp.sIpPort.sConIp.ip[0],
								psData->uApp.sIpPort.sConIp.ip[1],
								psData->uApp.sIpPort.sConIp.ip[2],
								psData->uApp.sIpPort.sConIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);

				
					
				m_rich_edit.AppendColor("               子网掩码地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sIpPort.sMask.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sIpPort.sMask.ip[0],
					psData->uApp.sIpPort.sMask.ip[1],
					psData->uApp.sIpPort.sMask.ip[2],
					psData->uApp.sIpPort.sMask.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				m_rich_edit.AppendColor("                   网关地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sIpPort.sGateIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sIpPort.sGateIp.ip[0],
					psData->uApp.sIpPort.sGateIp.ip[1],
					psData->uApp.sIpPort.sGateIp.ip[2],
					psData->uApp.sIpPort.sGateIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("                   代理类型:",crNormal);
				strValue.Format("%d\t", psData->uApp.sIpPort.eDelegate);
				
				switch(psData->uApp.sIpPort.eDelegate)
				{
                case MC_DELG_NULL:
                    strValue += "不使用代理\n";
                    break;
					
                case MC_DELG_HTTP:
                    strValue += "使用http connect代理\n";
                    break;
                    
                case MC_DELG_SOCK4:
                    strValue += "使用sock4代理\n";
                    break;
                    
                case MC_DELG_SOCK5:
                    strValue += "使用sock5代理\n";
                    break;
                    
                default:
                    strValue += "未知代理\n";
                    break;
				}
				m_rich_edit.AppendColor(strValue,crValue);


				m_rich_edit.AppendColor("         代理服务地址IP地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sIpPort.sDelgIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sIpPort.sDelgIp.ip[0],
					psData->uApp.sIpPort.sDelgIp.ip[1],
					psData->uApp.sIpPort.sDelgIp.ip[2],
					psData->uApp.sIpPort.sDelgIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				m_rich_edit.AppendColor("               代理服务端口:",crNormal);
				strValue.Format("%d\n", psData->uApp.sIpPort.usDelgPort);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("         代理服务器连接方式:",crNormal);
				strValue.Format("%d\t", psData->uApp.sIpPort.eDelgLink);
				
				switch(psData->uApp.sIpPort.eDelgLink)
				{
                case MC_DELK_ANYONE:
                    strValue+= "无需要验证\n";
                    break;
					
                case MC_DELK_USRPWD:
                    strValue+= "需要用户名和密码\n";
                    break;
					
                default:
                    strValue+= "未知方式\n";
                    break;
				}
				m_rich_edit.AppendColor(strValue,crValue);

				
				m_rich_edit.AppendColor("   是否需要代理服务器用户名:",crNormal);
				strValue.Format("%s", psData->uApp.sIpPort.bDlegUsr == TRUE ? "需要(":"不需要\n");
				m_rich_edit.AppendColor(strValue,crValue);
				
				if(psData->uApp.sIpPort.bDlegUsr == TRUE)
				{
					strValue = charToCString((char*)&psData->uApp.sIpPort.ucDlegUsr[0], psData->uApp.sIpPort.ucDlegUsrLen);
					strValue+=")\n";
					m_rich_edit.AppendColor(strValue,crValue);
				}
			
				
				m_rich_edit.AppendColor("     是否需要代理服务器密码:",crNormal);
				strValue.Format("%s", psData->uApp.sIpPort.bDlegPwd == TRUE ? "需要(":"不需要\n");
				m_rich_edit.AppendColor(strValue,crValue);
				
				if(psData->uApp.sIpPort.bDlegUsr == TRUE)
				{
					strValue = charToCString((char*)&psData->uApp.sIpPort.ucDlegPwd[0], psData->uApp.sIpPort.ucDlegPwdLen);
					strValue+=")\n";
					m_rich_edit.AppendColor(strValue,crValue);
				}

				insertLine();				
			}
			break;	

		case MCMD_AFN_4_F4_TEAM_ADDR:
		case MCMD_AFN_A_F4_TEAM_ADDR:

			{
				insertLine();
				// ucNeed
				m_rich_edit.AppendColor("\n信息集中与交互终端组地址:\n",crNormal);
				for (i = 0; i < 8; i++)
				{	
					strValue.Format("组地址 %d: ",i + 1, psData->uApp.sTeamAddr.ulAddr[i]);					
					m_rich_edit.AppendColor(strValue,crNormal);	
					strValue.Format("%d\n",psData->uApp.sTeamAddr.ulAddr[i]);	
					m_rich_edit.AppendColor(strValue,crValue);	
				}
				
				insertLine();				
			}
			break;	

		case MCMD_AFN_4_F6_CON_CASC:
		case MCMD_AFN_A_F6_CON_CASC:			
			{
				insertLine();
			
				m_rich_edit.AppendColor("\n  集中器级联接入方式:",crNormal);
				strValue.Format("%d ", psData->uApp.sCasc.eType);	
				m_rich_edit.AppendColor(strValue,crValue);	

            switch(psData->uApp.sCasc.eType)
            {
                case MC_CASC_NULL:
                    strValue = "不启用级联功能\n";
                    break;
                    
                case MC_CASC_RS485:
                    strValue = "RS485级联\n";
                    break;
                    
                case MC_CASC_ETH:
                    strValue = "以太网级联\n";
                    break;
                    
                default:
                    strValue ="未知级联方式\n";
                    break;
            }
			m_rich_edit.AppendColor(strValue,crValue);	

			
			m_rich_edit.AppendColor("              波特率:",crText);
			switch(psData->uApp.sCasc.sSer.eBaud)
			{
			case MC_BAUD_DEFAULT:
				strValue = "无须设置或使用默认";
				break;
			case MC_BAUD_1200:
				strValue = "1200";
				break;
				
			case MC_BAUD_2400:
				strValue = "2400";
				break;
				
			case MC_BAUD_4800:
				strValue = "4800";
				break;			
				
			case MC_BAUD_9600:
				strValue = "9600";
				break;
				
			case MC_BAUD_19200:
				strValue = "19200";
				break;
				
			case MC_BAUD_38400:
				strValue = "38400";
				break;
				
			case MC_BAUD_76800:
				strValue = "76800";
				break;
				
			case MC_BAUD_UNKOWN:
				strValue = "未知";
				break;
			default:
				break;
				
			}
			m_rich_edit.AppendColor(strValue,crValue);
			 
			m_rich_edit.AppendColor("\n              停止位:",crText);
			strValue.Format("%s\n",psData->uApp.sCasc.sSer.bStop1 == TRUE ? "1":"2");
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("                校验:",crText);
			strValue.Format("%s\n",psData->uApp.sCasc.sSer.bCheck == TRUE ? "有":"无");
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("            奇偶校验:",crText);
			strValue.Format("%s\n",psData->uApp.sCasc.sSer.bOdd == TRUE ? "奇":"偶");
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("                位数:",crText);
			switch(psData->uApp.sCasc.sSer.eBit)
			{
			case MC_SBIT_5:
				strValue = "5";
				break;
			case MC_SBIT_6:
				strValue = "6";
				break;
				
			case MC_SBIT_7:
				strValue = "7";
				break;
				
			case MC_SBIT_8:
				strValue = "8";
				break;			
				
			default:
				break;
				
			}
			strValue+= "\n";
			m_rich_edit.AppendColor(strValue,crValue);
			
            m_rich_edit.AppendColor("接收等待报文超时时间:",crText);
			
            strValue.Format("%d (单位 100ms)\n", psData->uApp.sCasc.ucWaitP);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("接收等待字节超时时间:",crText);
            strValue.Format("%d(单位 10ms)\n", psData->uApp.sCasc.ucWaitC);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("    接收失败重发次数:",crText);
            strValue.Format("%d\n", psData->uApp.sCasc.ucReTry);
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("        级联巡测周期:",crText);
            strValue.Format("%d 分\n", psData->uApp.sCasc.ucPeriod);
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("   被级联/级联方个数:",crText);
            strValue.Format("%d\n", psData->uApp.sCasc.ucN);
			m_rich_edit.AppendColor(strValue,crValue);

            
            for(i = 0; i < psData->uApp.sCasc.ucN; i++)
            {   
                strValue.Format("           第%d个参数:----\n", i+1);
				m_rich_edit.AppendColor(strValue,crValue);
                
				// acRegionCode
				m_rich_edit.AppendColor("          行政区划码:",crText);
                char buf[8] = {0};
				memcpy(buf, psData->uApp.sCasc.sOne[i].acRegionCode, MC_REGN_LEN);
				strValue.Format("%s\n", buf);
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				
				m_rich_edit.AppendColor("                地址:",crText);
				
                strValue.Format("%d\n", psData->uApp.sCasc.sOne[i].ulConAddr);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("            通信地址:",crText);
             
				// sIp                
                strValue.Format("%s %d.%d.%d.%d\n", psData->uApp.sCasc.sOne[i].sIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sCasc.sOne[i].sIp.ip[0],
					psData->uApp.sCasc.sOne[i].sIp.ip[1],
					psData->uApp.sCasc.sOne[i].sIp.ip[2],
					psData->uApp.sCasc.sOne[i].sIp.ip[3]);

				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("            端口地址:",crText);
                strValue.Format("%d\n", psData->uApp.sCasc.sOne[i].usPort);
				m_rich_edit.AppendColor(strValue,crValue);
				
            }
		
		   	insertLine();				
			}
			break;	
			case MCMD_AFN_A_F7_CON_DOWN_CFG:
				{
					insertLine();
	
					if (eDir == MC_DIR_M2S)
					{
						// ucNeed
						m_rich_edit.AppendColor("\n 本次查询数:",crNormal);
						strValue.Format("%d\n", psData->uApp.sDownCfgQ.usN);
						m_rich_edit.AppendColor(strValue,crValue);
						for (i = 0; i < psData->uApp.sDownCfgQ.usN; i++)
						{
							strValue.Format("第%d个端口号:", i + 1);
							m_rich_edit.AppendColor(strValue,crText);
							strValue.Format("%d\n", psData->uApp.sDownCfgQ.usPort[i]);
							m_rich_edit.AppendColor(strValue,crValue);
						}
					}
					else
					{
						
					}
			
				
				}
				break;
				

		case MCMD_AFN_4_F7_CON_DOWN_CFG:
		
			{
				insertLine();
				
			
				m_rich_edit.AppendColor("\n 集中器下行端口号:",crNormal);
				strValue.Format("%d\n", psData->uApp.sDownCfg.ucPort);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("       主用IP地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sDownCfg.sMainIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sDownCfg.sMainIp.ip[0],
					psData->uApp.sDownCfg.sMainIp.ip[1],
					psData->uApp.sDownCfg.sMainIp.ip[2],
					psData->uApp.sDownCfg.sMainIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("         主用端口:",crNormal);
				strValue.Format("%d\n", psData->uApp.sDownCfg.usMainPort);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("       备用IP地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d",
					psData->uApp.sDownCfg.sBackIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sDownCfg.sBackIp.ip[0],
					psData->uApp.sDownCfg.sBackIp.ip[1],
					psData->uApp.sDownCfg.sBackIp.ip[2],
					psData->uApp.sDownCfg.sBackIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("\n         备用端口:",crNormal);
				strValue.Format("%d\n", psData->uApp.sDownCfg.usBackPort);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("              APN:",crNormal);
				strValue = charToCString((char*)&psData->uApp.sDownCfg.ucAPN[0], MC_APN_LEN);			
				m_rich_edit.AppendColor(strValue,crValue);
			
				m_rich_edit.AppendColor("\n           用户名:",crNormal);
				strValue = charToCString((char*)&psData->uApp.sDownCfg.ucUsr[0], 32);			
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("\n             密码:",crNormal);
				strValue = charToCString((char*)&psData->uApp.sDownCfg.ucPwd[0], 32);			
				m_rich_edit.AppendColor(strValue,crValue);


				insertLine();				
			}
			break;	


		case MCMD_AFN_4_F9_CON_EVENT_CFG:
		case MCMD_AFN_A_F9_CON_EVENT_CFG:
			{
				insertLine();
				// ucNeed
				m_rich_edit.AppendColor("\n需要记录的事件记录的类型个数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sEventCfg.ucNeed);
				m_rich_edit.AppendColor(strValue,crValue);
				
				// aNeed
				for (i = 0; i < psData->uApp.sEventCfg.ucNeed; i++)
				{
					pStr = pStrGetErcName(psData->uApp.sEventCfg.aNeed[i]);
					strValue.Format("%d - %s\n", i + 1, pStr);
					m_rich_edit.AppendColor(strValue,crValue);
				}
				
				// ucImpt
				m_rich_edit.AppendColor("\n设置为重要事件的个数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sEventCfg.ucImpt);
				m_rich_edit.AppendColor(strValue,crValue);
				
				// aImpt
				for (i = 0; i < psData->uApp.sEventCfg.ucImpt; i++)
				{
					pStr = pStrGetErcName(psData->uApp.sEventCfg.aImpt[i]);
					strValue.Format("%d - %s\n", i + 1, pStr);
					m_rich_edit.AppendColor(strValue,crValue);
				}
				
				// ucImpRecNum
				m_rich_edit.AppendColor("\n需要记录的重要事件条数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sEventCfg.usImpRecNum);
				m_rich_edit.AppendColor(strValue,crValue);
				
				// ucNmlRecNum
				m_rich_edit.AppendColor("需要记录的一般事件条数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sEventCfg.usNmlRecNum);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
				
			}
			break;
			
		case MCMD_AFN_4_F10_CON_STATE_INPUT:
		case MCMD_AFN_A_F10_CON_STATE_INPUT:
			{
				insertLine();
				m_rich_edit.AppendColor("\n状态量接入标志位:\n",crNormal);
		
				for (i = 0; i < 8; i++)
				{
					strValue.Format("触点[%d]:%s\n", i, psData->uApp.sStateInput.bIn[i] == TRUE ? "接入":"未接入");
					m_rich_edit.AppendColor(strValue,crValue);
				}

				m_rich_edit.AppendColor("\n状态量属性标志位:\n",crNormal);
				
				for (i = 0; i < 8; i++)
				{
					strValue.Format("触点[%d]:%s\n", i, psData->uApp.sStateInput.bOn[i] == TRUE ? "常开触点":"常闭触点");
					m_rich_edit.AppendColor(strValue,crValue);
				}
			
				insertLine();
				
			}
			break;

		case MCMD_AFN_A_F12_CON_VERSION:
			{
				insertLine();
				#define BUF_LEN 16
				char buf[BUF_LEN] = {0};
				m_rich_edit.AppendColor("\n      厂商代号:",crNormal);	
				memcpy(buf, psData->uApp.sVersion.strFactory, 4);
				strValue.Format("%d", buf);
				m_rich_edit.AppendColor(strValue,crValue);
				
				// ucDevId
				m_rich_edit.AppendColor("\n      设备编号:",crNormal);	
				memset(buf, 0, BUF_LEN);
				memcpy(buf, psData->uApp.sVersion.ucDevId, 12);
				strValue.Format("%d", buf);
				m_rich_edit.AppendColor(strValue,crValue);

				// strCap
				m_rich_edit.AppendColor("\n配置容量信息码:",crNormal);	
				memset(buf, 0, BUF_LEN);
				memcpy(buf, psData->uApp.sVersion.strCap, 11);
				strValue.Format("%d", buf);
				m_rich_edit.AppendColor(strValue,crValue);
			
				// strSoft
				m_rich_edit.AppendColor("\n      软件版本:",crNormal);	
				memset(buf, 0, BUF_LEN);
				memcpy(buf, psData->uApp.sVersion.strSoft, 4);
				strValue.Format("%d", buf);
				m_rich_edit.AppendColor(strValue,crValue);

				// strSoft
				m_rich_edit.AppendColor("\n      软件版本:",crNormal);	
				memset(buf, 0, BUF_LEN);
				memcpy(buf, psData->uApp.sVersion.strHard, 4);
				strValue.Format("%d", buf);
				m_rich_edit.AppendColor(strValue,crValue);

				
				// sTime
				m_rich_edit.AppendColor("\n  软件发布日期:",crNormal);	
				strValue.Format("%d年%d月%d日%d时",
					psData->uApp.sVersion.sTime.ucYY,
					psData->uApp.sVersion.sTime.ucMM,
					psData->uApp.sVersion.sTime.ucDD,
					psData->uApp.sVersion.sTime.ucHH,
					psData->uApp.sVersion.sTime.ucmm);
				m_rich_edit.AppendColor(strValue,crValue);
				
				// ucN
				m_rich_edit.AppendColor("\n        模块数:",crNormal);	
				strValue.Format("%d", psData->uApp.sVersion.ucN);
				m_rich_edit.AppendColor(strValue,crValue);

				for (i = 0; i < psData->uApp.sVersion.ucN; i++)
				{
					strValue.Format("--------第%d个模块------\n", i+1);
					m_rich_edit.AppendColor(strValue,crValue);
					// 模块编号
					m_rich_edit.AppendColor("\n     模块编号:",crNormal);	
					strValue.Format("%d", psData->uApp.sVersion.sOne[i].ucID);
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("\n     软件版本:",crNormal);	
					memset(buf, 0, BUF_LEN);
					memcpy(buf, psData->uApp.sVersion.sOne[i].strVersion, 4);
					strValue.Format("%d", buf);
					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("\n     发布日期:",crNormal);	
					strValue.Format("%d年%d月%d日%d时\n",
					psData->uApp.sVersion.sOne[i].sTime.ucYY,
						psData->uApp.sVersion.sOne[i].sTime.ucMM,
						psData->uApp.sVersion.sOne[i].sTime.ucDD,
						psData->uApp.sVersion.sOne[i].sTime.ucHH,
						psData->uApp.sVersion.sOne[i].sTime.ucmm);
					m_rich_edit.AppendColor(strValue,crValue);
					
				}

				insertLine();
			}
			break;
			
		case MCMD_AFN_A_F15_SUPT_EVENT:
			{
					insertLine();
					for (i = 0; i < MC_ERC_NUM_MAX; i++)
					{
						strValue.Format("\n%-2d: ", i+1);
						m_rich_edit.AppendColor(strValue,crNormal);
					
						strValue.Format("%s\t", psData->uApp.sSuptEvent.bSuprt[i] == TRUE ? "支持":"不支持" );
						m_rich_edit.AppendColor(strValue,RGB(255,0,0));

						// 

						eMcErc eErc = (eMcErc)(i);
						switch(eErc)
						{
						case MC_ERC_1_RESET:
							strValue =  "ERC1: 复位事件";
							break;
							
						case MC_ERC_2_DATA_CLEAR:
							strValue =  "ERC2: 指定数据清零事件";
							break;
							
						case MC_ERC_3_SOFT_CHANGE:
							strValue =  "ERC3: 软件版本变更事件";
							break;
							
						case MC_ERC_4_PARA_CHANGE:
							strValue =  "ERC4: 参数变更事件";
							break;
							
						case MC_ERC_5_CHECK_TIME:
							strValue =  "ERC5: 校时事件";
							break;
							
						case MC_ERC_6_STATE_CHANGE:
							strValue =  "ERC6: 状态量变位事件";
							break;
							
						case MC_ERC_7_REMOTE_SWITCH:
							strValue =  "ERC7: 遥控跳闸事件";
							break;
							
						case MC_ERC_8_POWER_ON_OFF:
							strValue =  "ERC8: 停/上电事件";
							break;
							
						case MC_ERC_9_FACTOR_OVER:
							strValue =  "ERC9: 总功率因素越限事件";
							break;
							
						case MC_ERC_10_VOLT_EXCP:
							strValue =  "ERC10: 电压偏差越限事件";
							break;
							
						case MC_ERC_11_VOLT_CIRCLE:
							strValue =  "ERC11: 电压回路异常事件";
							break;
							
						case MC_ERC_12_ELEC_CRICLE:
							strValue =  "ERC12: 电流回路异常事件";
							break;
							
						case MC_ERC_13_VOLT_OVER:
							strValue =  "ERC13: 电压越限事件";
							break;
							
						case MC_ERC_14_ELEC_OVER:
							strValue =  "ERC14: 电流越限事件";
							break;
							
						case MC_ERC_15_UNBL_OVER_V:
							strValue =  "ERC15: 电压不平衡度越限事件";
							break;
							
						case MC_ERC_16_UNBL_OVER_I:
							strValue =  "ERC16: 电流不平衡度越限事件";
							break;
							
						case MC_ERC_17_HUNBL_OVER_V:
							strValue =  "ERC17: 谐波电压畸变率越限事件";
							break;
							
						case MC_ERC_18_HUNBL_OVER_I:
							strValue =  "ERC18: 谐波电流畸变率越限事件";
							break;
							
						case MC_ERC_19_FLASH_OVER:
							strValue =  "ERC19: 闪变越限事件";
							break;
							
						case MC_ERC_20_NELC_OVER:
							strValue =  "ERC20: 非电气量越限事件";
							break;
							
						default:
							strValue =  "ERC0: 未知事件记录类型";
							break;
						}
						
						//strValue+= "\n";
						m_rich_edit.AppendColor(strValue,crValue);
					}
					insertLine();
			}

			break;
			
		case MCMD_AFN_4_F17_TML_UP_CFG:
		case MCMD_AFN_A_F17_TML_UP_CFG:
			{
				insertLine();
				m_rich_edit.AppendColor("\n     信息集中与交互终端的下行通信端口号:",crNormal);
				strValue.Format("%d", psData->uApp.sTmlUpCfg.ucDownPort);
				m_rich_edit.AppendColor(strValue,crValue);
			
				m_rich_edit.AppendColor("\n                   监测终端侦听信端口号:",crNormal);
				strValue.Format("%d", psData->uApp.sTmlUpCfg.usListenPort);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("\n               监测终端上行通信端口属性:",crNormal);
				strValue.Format("%d", psData->uApp.sTmlUpCfg.eUpPara);

				switch(psData->uApp.sTmlUpCfg.eUpPara)
				{
				case MC_TUPP_DEL:
					strValue += "删除该监测终端号的配置参数";
					break;

				case MC_TUPP_SER:
					strValue += "串口";
					break;

				case MC_TUPP_ETH:
					strValue += "以太网";
					break;
					
				default:
					strValue += "未知属性";
					break;
				}
				
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				m_rich_edit.AppendColor("\n                   监测终端上行通信地址:",crNormal);
				m_rich_edit.AppendColor("\n                              ---------",crValue);
				
				m_rich_edit.AppendColor("\n                                 区域码:",crNormal);
				strValue = charToCString((char*)&psData->uApp.sTmlUpCfg.sUpAddr.acRegionCode[0], MC_REGN_LEN);	
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("\n                               主站地址:",crNormal);
				strValue.Format("%d\n", psData->uApp.sTmlUpCfg.sUpAddr.ucMstAddress);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("                               终端地址:",crNormal);
				strValue.Format("%d\n", psData->uApp.sTmlUpCfg.sUpAddr.ulConAddress);
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				m_rich_edit.AppendColor("                               是组地址:",crNormal);
				strValue.Format("%s\n", psData->uApp.sTmlUpCfg.sUpAddr.bTeam  == TRUE ? "是": "否");
				m_rich_edit.AppendColor(strValue,crValue);
				m_rich_edit.AppendColor("                              ---------\n",crValue);

				m_rich_edit.AppendColor("               监测终端上行通信协议类型:",crNormal);
				strValue.Format("%d :", psData->uApp.sTmlUpCfg.ucUpProto);
				if (1 == psData->uApp.sTmlUpCfg.ucUpProto)
				{
					strValue += "GBT_32";
				}
				else
				{
					strValue += "其他协议";
				}
				m_rich_edit.AppendColor(strValue,crValue);


				m_rich_edit.AppendColor("\n                     监测终端上行IP地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
								psData->uApp.sTmlUpCfg.sUpIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
								psData->uApp.sTmlUpCfg.sUpIp.ip[0],
								psData->uApp.sTmlUpCfg.sUpIp.ip[1],
								psData->uApp.sTmlUpCfg.sUpIp.ip[2],
								psData->uApp.sTmlUpCfg.sUpIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);

				
					
				m_rich_edit.AppendColor("                   监测终端子网掩码地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sTmlUpCfg.sUpMask.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sTmlUpCfg.sUpMask.ip[0],
					psData->uApp.sTmlUpCfg.sUpMask.ip[1],
					psData->uApp.sTmlUpCfg.sUpMask.ip[2],
					psData->uApp.sTmlUpCfg.sUpMask.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				m_rich_edit.AppendColor("                               网关地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sTmlUpCfg.sGateIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sTmlUpCfg.sGateIp.ip[0],
					psData->uApp.sTmlUpCfg.sGateIp.ip[1],
					psData->uApp.sTmlUpCfg.sGateIp.ip[2],
					psData->uApp.sTmlUpCfg.sGateIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("                               代理类型:",crNormal);
				strValue.Format("%d\t", psData->uApp.sTmlUpCfg.eDelegate);
				
				switch(psData->uApp.sTmlUpCfg.eDelegate)
				{
                case MC_DELG_NULL:
                    strValue += "不使用代理\n";
                    break;
					
                case MC_DELG_HTTP:
                    strValue += "使用http connect代理\n";
                    break;
                    
                case MC_DELG_SOCK4:
                    strValue += "使用sock4代理\n";
                    break;
                    
                case MC_DELG_SOCK5:
                    strValue += "使用sock5代理\n";
                    break;
                    
                default:
                    strValue += "未知代理\n";
                    break;
				}
				m_rich_edit.AppendColor(strValue,crValue);


				m_rich_edit.AppendColor("                     代理服务地址IP地址:",crNormal);
				strValue.Format("%s %d.%d.%d.%d\n",
					psData->uApp.sTmlUpCfg.sDelgIp.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
					psData->uApp.sTmlUpCfg.sDelgIp.ip[0],
					psData->uApp.sTmlUpCfg.sDelgIp.ip[1],
					psData->uApp.sTmlUpCfg.sDelgIp.ip[2],
					psData->uApp.sTmlUpCfg.sDelgIp.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				
				m_rich_edit.AppendColor("                           代理服务端口:",crNormal);
				strValue.Format(" %d\n", psData->uApp.sTmlUpCfg.usDelgPort);
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("                         服务器连接方式:",crNormal);
				strValue.Format("%d\t", psData->uApp.sTmlUpCfg.eDelgLink);
				
				switch(psData->uApp.sTmlUpCfg.eDelgLink)
				{
                case MC_DELK_ANYONE:
                    strValue+= "无需要验证\n";
                    break;
					
                case MC_DELK_USRPWD:
                    strValue+= "需要用户名和密码\n";
                    break;
					
                default:
                    strValue+= "未知方式\n";
                    break;
				}
				m_rich_edit.AppendColor(strValue,crValue);

				
				m_rich_edit.AppendColor("               是否需要代理服务器用户名:",crNormal);
				strValue.Format("%s", psData->uApp.sTmlUpCfg.bDlegUsr == TRUE ? "需要(":"不需要\n");
				m_rich_edit.AppendColor(strValue,crValue);
				
				if(psData->uApp.sTmlUpCfg.bDlegUsr == TRUE)
				{
					strValue = charToCString((char*)&psData->uApp.sTmlUpCfg.ucDlegUsr[0], psData->uApp.sTmlUpCfg.ucDlegUsrLen);
					strValue+=")\n";
					m_rich_edit.AppendColor(strValue,crValue);
				}
			
				
				m_rich_edit.AppendColor("                 是否需要代理服务器密码:",crNormal);
				strValue.Format("%s", psData->uApp.sTmlUpCfg.bDlegPwd == TRUE ? "需要(":"不需要\n");
				m_rich_edit.AppendColor(strValue,crValue);
				
				if(psData->uApp.sTmlUpCfg.bDlegUsr == TRUE)
				{
					strValue = charToCString((char*)&psData->uApp.sTmlUpCfg.ucDlegPwd[0], psData->uApp.sTmlUpCfg.ucDlegPwdLen);
					strValue+=")\n";
					m_rich_edit.AppendColor(strValue,crValue);
				}


				//UINT8  ucPermitDelayM;    //  (单位:分钟 0~255)
				m_rich_edit.AppendColor("     监测终端作为启动站允许传输延时时间:",crNormal);
				strValue.Format("%d\n", psData->uApp.sTmlUpCfg.ucPermitDelayM);
				m_rich_edit.AppendColor(strValue,crValue);
				
				//UINT8  ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
				m_rich_edit.AppendColor("                               重发次数:",crNormal);
				strValue.Format("%d\n", psData->uApp.sTmlUpCfg.ucReSendTimes);
				m_rich_edit.AppendColor(strValue,crValue);
				
				//UINT8  ucHeartBeat;       // 心跳周期
				m_rich_edit.AppendColor("                               心跳周期:",crNormal);
				strValue.Format("%d\n", psData->uApp.sTmlUpCfg.ucHeartBeat);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("   监测终端作为启动站等待应答的超时时间:",crNormal);
				strValue.Format("%d\n", psData->uApp.sTmlUpCfg.usWaitTimeoutS);
				m_rich_edit.AppendColor(strValue,crValue);
				
				//BOOL   bPermitRt;         // 实时数据 是否允许信息集中与交互终端需要主(子)站确认
				m_rich_edit.AppendColor("实时数据 是否允许监测终端需要集中器确认:",crNormal);
				strValue.Format("%s\n", psData->uApp.sTmlUpCfg.bPermitRt == TRUE ? "允许":"禁止");
				m_rich_edit.AppendColor(strValue,crValue);
				
				//BOOL   bPermitTk;         // 任务数据 是否允许信息集中与交互终端需要主(子)站确认
				m_rich_edit.AppendColor("任务数据 是否允许监测终端需要集中器确认:",crNormal);
				strValue.Format("%s\n", psData->uApp.sTmlUpCfg.bPermitTk == TRUE ? "允许":"禁止");
				m_rich_edit.AppendColor(strValue,crValue);
				
				//BOOL   bPermitEv;         // 事件数据 是否允许信息集中与交互终端需要主(子)站确认
				m_rich_edit.AppendColor("事件数据 是否允许监测终端需要集中器确认:",crNormal);
				strValue.Format("%s\n", psData->uApp.sTmlUpCfg.bPermitEv == TRUE ? "允许":"禁止");
				m_rich_edit.AppendColor(strValue,crValue);


				insertLine();
				
			}
			break;
			
	case MCMD_AFN_4_F25_ELEC_MP_CFG:
	case MCMD_AFN_A_F25_ELEC_MP_CFG:
	case MCMD_AFN_4_F33_NELC_MP_CFG:
	case MCMD_AFN_A_F33_NELC_MP_CFG:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\n    所属集中器/终端号:",crNormal);
			strValue.Format("%d", psData->uApp.sElecMpCfg.usID);
			if (psData->uApp.sElecMpCfg.usID == 0)
			{
				strValue += "(是0 表示电气测量点接入集中器)";			
			}
			else
			{
				strValue += "(非0 表示电气测量点接入终端)";
			}
			m_rich_edit.AppendColor(strValue,crValue);
			
		
			m_rich_edit.AppendColor("\n集中器/终端接入端口号:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecMpCfg.ucPort);
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("     接入设备通信地址:",crNormal);
		    strValue = charToCString((char*)&psData->uApp.sElecMpCfg.ucAddr[0], 16);
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("\n 接入设备通信协议类型:",crNormal);
			strValue.Format("%d\t", psData->uApp.sElecMpCfg.eAcsProto);
			
			switch(psData->uApp.sElecMpCfg.eAcsProto)
			{
			case MC_ACS_PROT_GBNX_32:
				strValue += "GBT_32\n";
				break;
				
			case MC_ACS_PROT_DLT645_97:
				strValue += "DLT645_1997代理\n";
				break;
				
			case MC_ACS_PROT_DLT645_07:
				strValue += "DLT645_2007\n";
				break;

			case MC_ACS_PROT_UNKOWN:
				strValue += "未知通信协议类型\n";
				break;
						
			case MC_ACS_PROT_MODBUS:
				strValue += "Modbus\n";
				break;
				
			default:
				strValue += "用户自定义\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("             通信密码:",crNormal);
			strValue = charToCString((char*)&psData->uApp.sElecMpCfg.ucPwd[0], 6);
			m_rich_edit.AppendColor(strValue,crValue);
		
			
			m_rich_edit.AppendColor("\n         接入终端属性:",crNormal);
			strValue.Format("%d\t", psData->uApp.sElecMpCfg.eAcsPort);
					
			switch(psData->uApp.sElecMpCfg.eAcsPort)
			{
			case MC_ACS_PORT_UNKOWN:
				strValue += "未知接口属性\n";
				break;
				
			case MC_ACS_PORT_DC:
				strValue += "直流模拟量\n";
				break;
				
			case MC_ACS_PORT_AC:
				strValue += "交流模拟量\n";
				break;
				
			case MC_ACS_PORT_SER:
				strValue += "串口\n";
				break;
				
			case MC_ACS_PORT_ETH:
				strValue += "以太网\n";
				break;

			case MC_ACS_PORT_ZIGB:
				strValue += "zigbee\n";
				break;
				
			default:
				strValue += "用户自定义\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);
			
		//	m_rich_edit.AppendColor("接入终端参数\n",crValue);	
			//m_rich_edit.AppendColor("---------\n",crValue);
			switch(psData->uApp.sElecMpCfg.eAcsPort)
			{
				
			case MC_ACS_PORT_SER:
				{
					m_rich_edit.AppendColor("               波特率:",crText);
					switch(psData->uApp.sElecMpCfg.uPortPara.sSer.eBaud)
					{
					case MC_BAUD_DEFAULT:
						strValue = "无须设置或使用默认";
						break;
					case MC_BAUD_1200:
						strValue = "1200";
						break;
						
					case MC_BAUD_2400:
						strValue = "2400";
						break;
						
					case MC_BAUD_4800:
						strValue = "4800";
						break;			
						
					case MC_BAUD_9600:
						strValue = "9600";
						break;
						
					case MC_BAUD_19200:
						strValue = "19200";
						break;
						
					case MC_BAUD_38400:
						strValue = "38400";
						break;
						
					case MC_BAUD_76800:
						strValue = "76800";
						break;
						
					case MC_BAUD_UNKOWN:
						strValue = "未知";
						break;
					default:
						break;
						
					}
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("\n               停止位:",crText);
					strValue.Format("%s\n",psData->uApp.sElecMpCfg.uPortPara.sSer.bStop1 == TRUE ? "1":"2");
					m_rich_edit.AppendColor(strValue,crValue);
				
					m_rich_edit.AppendColor("                 校验:",crText);
					strValue.Format("%s\n",psData->uApp.sElecMpCfg.uPortPara.sSer.bCheck == TRUE ? "有":"无");
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("             奇偶校验:",crText);
					strValue.Format("%s\n",psData->uApp.sElecMpCfg.uPortPara.sSer.bOdd == TRUE ? "奇":"偶");
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("                 位数:",crText);
					switch(psData->uApp.sElecMpCfg.uPortPara.sSer.eBit)
					{
					case MC_SBIT_5:
						strValue = "5";
						break;
					case MC_SBIT_6:
						strValue = "6";
						break;
						
					case MC_SBIT_7:
						strValue = "7";
						break;
						
					case MC_SBIT_8:
						strValue = "8";
						break;			
				
					default:
						break;
						
					}
					strValue+= "\n";
					m_rich_edit.AppendColor(strValue,crValue);

				}
				
				break;
				
			case MC_ACS_PORT_ETH:
				{
					m_rich_edit.AppendColor("   接入设备侦听端口号:",crNormal);
					strValue.Format("%d\n",psData->uApp.sElecMpCfg.uPortPara.sEth.usPort );
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("               IP地址:",crNormal);
					strValue.Format("%s %d.%d.%d.%d\n",
						psData->uApp.sElecMpCfg.uPortPara.sEth.sAccess.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
						psData->uApp.sElecMpCfg.uPortPara.sEth.sAccess.ip[0],
						psData->uApp.sElecMpCfg.uPortPara.sEth.sAccess.ip[1],
						psData->uApp.sElecMpCfg.uPortPara.sEth.sAccess.ip[2],
						psData->uApp.sElecMpCfg.uPortPara.sEth.sAccess.ip[3]);
				m_rich_edit.AppendColor(strValue,crValue);
				
				}
				break;
				
			case MC_ACS_PORT_ZIGB:
				{
					CNxConfig cfg;
					char zigbee[17] = {0};
					
					
					m_rich_edit.AppendColor("           Zigbee地址:",crNormal);
					cfg.trans_zigbee(false, strValue, (char*)&psData->uApp.sElecMpCfg.uPortPara.mac[0]);
					strValue+="\n";
					m_rich_edit.AppendColor(strValue,crValue);
				}
				break;
				
			default:
				//strValue += "用户自定义\n";
				break;
			}
		//	m_rich_edit.AppendColor("\n---------\n",crValue);
			
			m_rich_edit.AppendColor("   接入设备侦听端口号:",crText);
			strValue.Format("%d\n",psData->uApp.sElecMpCfg.usAcsPort );
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor(" 接入设备务地址IP地址:",crNormal);
			strValue.Format("%s %d.%d.%d.%d\n",
				psData->uApp.sElecMpCfg.sAccess.eVersion == MC_IP_V4 ? "ipv4":"ipv6",
				psData->uApp.sElecMpCfg.sAccess.ip[0],
				psData->uApp.sElecMpCfg.sAccess.ip[1],
				psData->uApp.sElecMpCfg.sAccess.ip[2],
				psData->uApp.sElecMpCfg.sAccess.ip[3]);
			m_rich_edit.AppendColor(strValue,crValue);
			
			insertLine();
			
		}
		break;

	case MCMD_AFN_4_F26_ELEC_MP_BASE:
	case MCMD_AFN_A_F26_ELEC_MP_BASE:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\n有功电能示值整数位个数:",crNormal);

			strValue.Format("%d", psData->uApp.sElecMpBase.sDigit.ucInteger);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("\n有功电能示值小数位个数:",crNormal);
			strValue.Format("%d", psData->uApp.sElecMpBase.sDigit.ucDecimal);
			m_rich_edit.AppendColor(strValue,crValue);
			

			m_rich_edit.AppendColor("\n        电压互感器倍率:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecMpBase.usTimesU);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("        电流互感器倍率:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecMpBase.usTimesI);
			m_rich_edit.AppendColor(strValue,crValue);
				

			m_rich_edit.AppendColor("              额定电压:",crNormal);
			strValue.Format("%4.1f V\n", psData->uApp.sElecMpBase.fU);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("              额定电流:",crNormal);
			strValue.Format("%6.3f A\n", psData->uApp.sElecMpBase.fI);
			m_rich_edit.AppendColor(strValue,crValue);
				
			
			m_rich_edit.AppendColor("          电源接线方式:",crNormal);
			strValue.Format("%d ", psData->uApp.sElecMpBase.sLinkWay.eLink);
			switch(psData->uApp.sElecMpBase.sLinkWay.eLink)
			{
			case MC_LINK_P3_L3:
				strValue += "三相三线";
				break;
				
			case MC_LINK_P3_L4:
				strValue += "三相四线";
				break;
				
			case MC_LINK_P1:
				strValue += "单相表";
				break;

			default:
				strValue += "未知";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);
			
		m_rich_edit.AppendColor("\n              相位方式:",crNormal);
			strValue.Format("%d ", psData->uApp.sElecMpBase.sLinkWay.ePhase);
			switch(psData->uApp.sElecMpBase.sLinkWay.ePhase)
			{
			case MC_PHASE_A:
				strValue += "A 相\n";
				break;
				
			case MC_PHASE_B:
				strValue += "B 相\n";
				break;
				
			case MC_PHASE_C:
				strValue += "C 相\n";
				break;
				
			default:
				strValue += "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);
			
			insertLine();
			
		}
		break;

	case MCMD_AFN_4_F27_ELEC_LMIT_POWER:
	case MCMD_AFN_A_F27_ELEC_LMIT_POWER:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\n电压断相判别参数:",crNormal);			
			strValue.Format("%4.1f\n", psData->uApp.sElecLimitPower.fDropV);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);
			
			m_rich_edit.AppendColor("电压失压时间判别参数:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.ucTimeLossV);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);

			// sOverV
			m_rich_edit.AppendColor("过压判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("电压上上限:",crNormal);	
			strValue.Format("%4.1f\n", psData->uApp.sElecLimitPower.sOverV.fUpUp);
			m_rich_edit.AppendColor(strValue,crValue);
		
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sOverV.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sOverV.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);
			
			// sLossV
			m_rich_edit.AppendColor("---------\n",crValue);
			m_rich_edit.AppendColor("欠压判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("电压下下限:",crNormal);	
			strValue.Format("%4.1f\n", psData->uApp.sElecLimitPower.sLossV.fDownDown);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sLossV.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sLossV.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);

			// sOverI
				m_rich_edit.AppendColor("---------\n",crValue);
			m_rich_edit.AppendColor("过流判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("电流上上限:",crNormal);	
			strValue.Format("%6.3f\n", psData->uApp.sElecLimitPower.sOverI.fUpUp);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sOverI.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sOverI.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);
			
			// sMcSuperI
			m_rich_edit.AppendColor("---------\n",crValue);
			m_rich_edit.AppendColor("超额定电流判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("电流上限:",crNormal);	
			strValue.Format("%6.3f\n", psData->uApp.sElecLimitPower.sOverI.fUpUp);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sOverI.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sOverI.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);
			
			
			// sMcZeroI
			m_rich_edit.AppendColor("---------\n",crValue);
			m_rich_edit.AppendColor("零序电流超限判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("0序电流上限:",crNormal);	
			strValue.Format("%6.3f\n", psData->uApp.sElecLimitPower.sOverI.fUpUp);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sOverI.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sOverI.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);
			
			
			// sMcUnblnV
			m_rich_edit.AppendColor("---------\n",crValue);
			m_rich_edit.AppendColor("三相电压不平衡超限判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("三相电压不平衡度限值:",crNormal);	
			strValue.Format("%6.4f\n", psData->uApp.sElecLimitPower.sUblV.fLimit);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sUblV.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sUblV.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);
			
			// sUblI
			m_rich_edit.AppendColor("---------\n",crValue);
			m_rich_edit.AppendColor("三相电流不平衡超限判别参数:\n",crNormal);	
			m_rich_edit.AppendColor("三相电流不平衡度限值:",crNormal);	
			strValue.Format("%6.4f\n", psData->uApp.sElecLimitPower.sUblI.fLimit);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("持续时间:",crNormal);
			strValue.Format("%d\n", psData->uApp.sElecLimitPower.sUblI.ucTime);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("越限恢复系数:",crNormal);
			strValue.Format("%4.2f\n", psData->uApp.sElecLimitPower.sUblI.fFactor);
			m_rich_edit.AppendColor(strValue,crValue);
		
			
			insertLine();
			
		}
		break;
		
	case MCMD_AFN_4_F28_ELEC_LMIT_FACTR:
	case MCMD_AFN_A_F28_ELEC_LMIT_FACTR:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\n   总功率因数分段参数1: ",crNormal);			
			strValue.Format("%4.2f\n", psData->uApp.sFactorLimit.fPara1);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("   总功率因数分段参数2: ",crNormal);			
			strValue.Format("%4.2f\n", psData->uApp.sFactorLimit.fPara2);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("总功率因数越限告警定值: ",crNormal);			
			strValue.Format("%4.2f\n", psData->uApp.sFactorLimit.fWarning);
			m_rich_edit.AppendColor(strValue,crValue);



			insertLine();
			
		}
		break;
		
	case MCMD_AFN_4_F29_ELEC_FIX_HARM:
	case MCMD_AFN_A_F29_ELEC_FIX_HARM:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\nA相电压畸变率越限定值:\n",crNormal);	
			m_rich_edit.AppendColor("  总畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVa.fTotal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("奇次畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVa.fOdd);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("偶次畸变率超限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVa.fEven);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);

			
			m_rich_edit.AppendColor("B相电压畸变率越限定值:\n",crNormal);	
			m_rich_edit.AppendColor("  总畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVb.fTotal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("奇次畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVb.fOdd);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("偶次畸变率超限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVb.fEven);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);
			
			m_rich_edit.AppendColor("C相电压畸变率越限定值:\n",crNormal);	
			m_rich_edit.AppendColor("  总畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVc.fTotal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("奇次畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVc.fOdd);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("偶次畸变率超限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sVc.fEven);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);
		
			m_rich_edit.AppendColor("A相电流畸变率越限定值:\n",crNormal);	
			m_rich_edit.AppendColor("  总畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIa.fTotal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("奇次畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIa.fOdd);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("偶次畸变率超限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIa.fEven);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);
			
			
			m_rich_edit.AppendColor("B相电流畸变率越限定值:\n",crNormal);	
			m_rich_edit.AppendColor("  总畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIb.fTotal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("奇次畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIb.fOdd);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("偶次畸变率超限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIb.fEven);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);
			
			m_rich_edit.AppendColor("C相电流畸变率越限定值:\n",crNormal);	
			m_rich_edit.AppendColor("  总畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIc.fTotal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("奇次畸变率越限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIc.fOdd);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("偶次畸变率超限定值:",crNormal);	
			strValue.Format("%4.2f\n", psData->uApp.sElecFixHarm.sIc.fEven);
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("---------\n",crValue);



			insertLine();
			
		}
		break;
		
	case MCMD_AFN_4_F30_ELEC_FLASH:
	case MCMD_AFN_A_F30_ELEC_FLASH:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\n短时闪变越限值: ",crNormal);			
			strValue.Format("%4.2f\n", psData->uApp.sElecFlash.fLong);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("长时闪变越限值: ",crNormal);			
			strValue.Format("%4.2f\n", psData->uApp.sElecFlash.fShort);
			m_rich_edit.AppendColor(strValue,crValue);
			
			
			insertLine();
			
		}
		break;


	case MCMD_AFN_4_F34_NELC_MP_PARA:
	case MCMD_AFN_A_F34_NELC_MP_PARA:
		{
			insertLine();
			
			m_rich_edit.AppendColor("\n非电气量:",crNormal);
			
			switch(psData->uApp.sNelcMpPara.eType)
			{
			case MC_NELC_TEMP:
				strValue = "温度\n";
				break;
				
			case MC_NELC_FLOW:
				strValue = "流量\n";
				break;
				
			case MC_NELC_FV:
				strValue = "流速\n";
				break;

			case MC_NELC_PRESS:
				strValue = "压力\n";
				break;
				
			case MC_NELC_HUMI:
				strValue = "湿度\n";
				break;
				
			case MC_NELC_LIGHT:
				strValue = "照度\n";
			
			break;				

			case MC_NELC_RV:
				strValue = "转速\n";
				break;
				
			case MC_NELC_420MA:
				strValue = "4~20MA\n";
				break;	

			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);


			
			m_rich_edit.AppendColor("量程上限:",crNormal);		
			
			switch(psData->uApp.sNelcMpPara.sUp.ePrec)
			{
			case MC_PREC_P4:			
			case MC_PREC_P3:			
			case MC_PREC_P2:				
			case MC_PREC_P1:			
			case MC_PREC_P0:
				strValue.Format("%0.0f\t", psData->uApp.sNelcMpPara.sUp.dValue);
				break;
				
			case MC_PREC_N1:
				strValue.Format("%0.1f\t", psData->uApp.sNelcMpPara.sUp.dValue);
				
				break;				
				
			case MC_PREC_N2:
				strValue.Format("%0.2f\t", psData->uApp.sNelcMpPara.sUp.dValue);
				break;
				
			case MC_PREC_N3:
				strValue.Format("%0.3f\t", psData->uApp.sNelcMpPara.sUp.dValue);
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
		
			m_rich_edit.AppendColor(strValue,crValue);



			// 精度
			m_rich_edit.AppendColor("精度:",crNormal);
			
			switch(psData->uApp.sNelcMpPara.sUp.ePrec)
			{
			case MC_PREC_P4:
				strValue = "(0, (+/-)10000~99999990000)\n";
				break;
				
			case MC_PREC_P3:
				strValue = "(0, (+/-)1000~9999999000)\n";
				break;		
				
			case MC_PREC_P2:
				strValue = "(0, (+/-)100~999999900)\n";
				break;
				
			case MC_PREC_P1:
				strValue = "(0, (+/-)10~99999990)\n";
				break;
				
			case MC_PREC_P0:
				strValue = "(0, (+/-)1~9999999)\n";
				break;
				
			case MC_PREC_N1:
				strValue = "(0, (+/-)0.1~999999.9)\n";
				
				break;				
				
			case MC_PREC_N2:
				strValue = "(0, (+/-)0.01~99999.99)\n";
				break;
				
			case MC_PREC_N3:
				strValue = "(0, (+/-)0.001~9999.999)\n";
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("量程下限:",crNormal);		
			
			switch(psData->uApp.sNelcMpPara.sDown.ePrec)
			{
			case MC_PREC_P4:			
			case MC_PREC_P3:			
			case MC_PREC_P2:				
			case MC_PREC_P1:			
			case MC_PREC_P0:
				strValue.Format("%0.0f\t", psData->uApp.sNelcMpPara.sDown.dValue);
				break;
				
			case MC_PREC_N1:
				strValue.Format("%0.1f\t", psData->uApp.sNelcMpPara.sDown.dValue);
				
				break;				
				
			case MC_PREC_N2:
				strValue.Format("%0.2f\t", psData->uApp.sNelcMpPara.sDown.dValue);
				break;
				
			case MC_PREC_N3:
				strValue.Format("%0.3f\t", psData->uApp.sNelcMpPara.sDown.dValue);
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
	
			
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("精度:",crNormal);
			
			switch(psData->uApp.sNelcMpPara.sDown.ePrec)
			{
			case MC_PREC_P4:
				strValue = "(0, (+/-)10000~99999990000)\n";
				break;
				
			case MC_PREC_P3:
				strValue = "(0, (+/-)1000~9999999000)\n";
				break;
				
			case MC_PREC_P2:
				strValue = "(0, (+/-)100~999999900)\n";
				break;
				
			case MC_PREC_P1:
				strValue = "(0, (+/-)10~99999990)\n";
				break;
				
			case MC_PREC_P0:
				strValue = "(0, (+/-)1~9999999)\n";
				break;
				
			case MC_PREC_N1:
				strValue = "(0, (+/-)0.1~999999.9)\n";
				
				break;				
				
			case MC_PREC_N2:
				strValue = "(0, (+/-)0.01~99999.99)\n";
				break;
				
			case MC_PREC_N3:
				strValue = "(0, (+/-)0.001~9999.999)\n";
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);
		

			insertLine();
			
		}
		break;
		
		case MCMD_AFN_4_F35_NELC_MP_LMIT:
	    case MCMD_AFN_A_F35_NELC_MP_LMIT:
				{
			insertLine();
			
			m_rich_edit.AppendColor("\n非电气量:",crNormal);
			
			switch(psData->uApp.sNelcMpPara.eType)
			{
			case MC_NELC_TEMP:
				strValue = "温度\n";
				break;
				
			case MC_NELC_FLOW:
				strValue = "流量\n";
				break;
				
			case MC_NELC_FV:
				strValue = "流速\n";
				break;

			case MC_NELC_PRESS:
				strValue = "压力\n";
				break;
				
			case MC_NELC_HUMI:
				strValue = "湿度\n";
				break;
				
			case MC_NELC_LIGHT:
				strValue = "照度\n";
			
			break;				

			case MC_NELC_RV:
				strValue = "转速\n";
				break;
				
			case MC_NELC_420MA:
				strValue = "4~20MA\n";
				break;	

			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);


			
			m_rich_edit.AppendColor("越限上限:",crNormal);		
			
			
			switch(psData->uApp.sNelcMpPara.sUp.ePrec)
			{
			case MC_PREC_P4:			
			case MC_PREC_P3:			
			case MC_PREC_P2:				
			case MC_PREC_P1:			
			case MC_PREC_P0:
				strValue.Format("%0.0f\t", psData->uApp.sNelcMpLimit.sUp.dValue);
				break;
				
			case MC_PREC_N1:
				strValue.Format("%0.1f\t", psData->uApp.sNelcMpLimit.sUp.dValue);
				
				break;				
				
			case MC_PREC_N2:
				strValue.Format("%0.2f\t", psData->uApp.sNelcMpLimit.sUp.dValue);
				break;
				
			case MC_PREC_N3:
				strValue.Format("%0.3f\t", psData->uApp.sNelcMpLimit.sUp.dValue);
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
			
			
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("精度:",crNormal);
			
			switch(psData->uApp.sNelcMpPara.sUp.ePrec)
			{
			case MC_PREC_P4:
				strValue = "(0, (+/-)10000~99999990000)\n";
				break;
				
			case MC_PREC_P3:
				strValue = "(0, (+/-)1000~9999999000)\n";
				break;		
				
			case MC_PREC_P2:
				strValue = "(0, (+/-)100~999999900)\n";
				break;
				
			case MC_PREC_P1:
				strValue = "(0, (+/-)10~99999990)\n";
				break;
				
			case MC_PREC_P0:
				strValue = "(0, (+/-)1~9999999)\n";
				break;
				
			case MC_PREC_N1:
				strValue = "(0, (+/-)0.1~999999.9)\n";
				
				break;				
				
			case MC_PREC_N2:
				strValue = "(0, (+/-)0.01~99999.99)\n";
				break;
				
			case MC_PREC_N3:
				strValue = "(0, (+/-)0.001~9999.999)\n";
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("越限下限:",crNormal);		
		
			
			switch(psData->uApp.sNelcMpPara.sDown.ePrec)
			{
			case MC_PREC_P4:			
			case MC_PREC_P3:			
			case MC_PREC_P2:				
			case MC_PREC_P1:			
			case MC_PREC_P0:
				strValue.Format("%0.0f\t", psData->uApp.sNelcMpLimit.sDown.dValue);
				break;
				
			case MC_PREC_N1:
				strValue.Format("%0.1f\t", psData->uApp.sNelcMpLimit.sDown.dValue);
				
				break;				
				
			case MC_PREC_N2:
				strValue.Format("%0.2f\t", psData->uApp.sNelcMpLimit.sDown.dValue);
				break;
				
			case MC_PREC_N3:
				strValue.Format("%0.3f\t", psData->uApp.sNelcMpLimit.sDown.dValue);
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
			
			
			m_rich_edit.AppendColor(strValue,crValue);
			m_rich_edit.AppendColor("精度:",crNormal);
			
			switch(psData->uApp.sNelcMpPara.sDown.ePrec)
			{
			case MC_PREC_P4:
				strValue = "(0, (+/-)10000~99999990000)\n";
				break;
				
			case MC_PREC_P3:
				strValue = "(0, (+/-)1000~9999999000)\n";
				break;		
				
			case MC_PREC_P2:
				strValue = "(0, (+/-)100~999999900)\n";
				break;
				
			case MC_PREC_P1:
				strValue = "(0, (+/-)10~99999990)\n";
				break;
				
			case MC_PREC_P0:
				strValue = "(0, (+/-)1~9999999)\n";
				break;
				
			case MC_PREC_N1:
				strValue = "(0, (+/-)0.1~999999.9)\n";
				
				break;				
				
			case MC_PREC_N2:
				strValue = "(0, (+/-)0.01~99999.99)\n";
				break;
				
			case MC_PREC_N3:
				strValue = "(0, (+/-)0.001~9999.999)\n";
				break;	
				
			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);
		

			insertLine();
			
		}
		break;
		
	case MCMD_AFN_4_F49_FREZ_TASK_PARA:
    case MCMD_AFN_A_F49_FREZ_TASK_PARA:
		{
			m_rich_edit.AppendColor("\n              冻结基准时间:",crNormal);		
			                           
			strValue.Format("%02d年%d月%d日 星期%2d %02d:%02d:%02d", 
				psData->uApp.sFrezTaskPara.sTimeFrez.ucYY,
				psData->uApp.sFrezTaskPara.sTimeFrez.ucMM,			
				psData->uApp.sFrezTaskPara.sTimeFrez.ucDD,
				psData->uApp.sFrezTaskPara.sTimeFrez.ucWW,
				psData->uApp.sFrezTaskPara.sTimeFrez.ucHH,
				psData->uApp.sFrezTaskPara.sTimeFrez.ucmm,
				psData->uApp.sFrezTaskPara.sTimeFrez.ucss);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("\n              上报基准时间:",crNormal);		
			
			strValue.Format("%02d年%d月%d日 星期%2d %02d:%02d:%02d", 
				psData->uApp.sFrezTaskPara.sTimeRprt.ucYY,
				psData->uApp.sFrezTaskPara.sTimeRprt.ucMM,
				psData->uApp.sFrezTaskPara.sTimeRprt.ucDD,
				psData->uApp.sFrezTaskPara.sTimeRprt.ucWW,
				psData->uApp.sFrezTaskPara.sTimeRprt.ucHH,
				psData->uApp.sFrezTaskPara.sTimeRprt.ucmm,
				psData->uApp.sFrezTaskPara.sTimeRprt.ucss);
			m_rich_edit.AppendColor(strValue,crValue);

		
		
			m_rich_edit.AppendColor("\n                  冻结周期:",crNormal);	
			strValue.Format("%d", psData->uApp.sFrezTaskPara.sFreez.usPeriod);
			if(psData->uApp.sFrezTaskPara.sFreez.usPeriod == 0)
			{
				strValue += "(为0表示删除本项冻结任务)";
			}
			else
			{
				strValue += "(为定时冻结的时间间隔)";
			}
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("\n              冻结周期单位:",crNormal);	

			switch(psData->uApp.sFrezTaskPara.sFreez.eUnit)
			{
			case MC_PUNT_MONTH:
				strValue = "月\n";
				break;
				
			case MC_PUNT_DAY:
				strValue = "小日\n";
				break;
							
			case MC_PUNT_HOUR:
				strValue = "时\n";
				break;

			case MC_PUNT_MIN:
				strValue = "分钟\n";
				break;
				
				
			case MC_PUNT_SEC:
				strValue = "秒\n";
				break;
				
			case MC_PUNT_MS:
				strValue = "毫秒\n";
				break;
					

			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);
		
			m_rich_edit.AppendColor("              定时上报周期:",crNormal);	
			strValue.Format("%d", psData->uApp.sFrezTaskPara.ucPeriodRpt);
			if(psData->uApp.sFrezTaskPara.ucPeriodRpt == 0)
			{
				strValue += "(0为本项冻结任务内容无需定时上报)";
			}
			else
			{
				strValue += "(为定时上报数据的时间间隔)";
			}
			m_rich_edit.AppendColor(strValue,crValue);
		
			
			m_rich_edit.AppendColor("\n          定时上报周期单位:",crNormal);	
			
			switch(psData->uApp.sFrezTaskPara.eUnitRpt)
			{
			case MC_PUNT_MONTH:
				strValue = "月\n";
				break;
				
			case MC_PUNT_DAY:
				strValue = "小日\n";
				break;
				
			case MC_PUNT_HOUR:
				strValue = "时\n";
				break;
				
			case MC_PUNT_MIN:
				strValue = "分钟\n";
				break;
				
				
			case MC_PUNT_SEC:
				strValue = "秒\n";
				break;
				
			case MC_PUNT_MS:
				strValue = "毫秒\n";
				break;
				
				
			default:
				strValue = "未知\n";
				break;
			}
			m_rich_edit.AppendColor(strValue,crValue);

			m_rich_edit.AppendColor("需要冻结的数据单元标识个数:",crNormal);	
			strValue.Format("%d\n", psData->uApp.sFrezTaskPara.uCmdPnNum);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("            序号 ",RGB(128,128,128));
			m_rich_edit.AppendColor("测量点号 ",RGB(255,0,255));
			m_rich_edit.AppendColor(" 数据单元标识\n",crValue);

			for (i = 0; i < psData->uApp.sFrezTaskPara.uCmdPnNum; i++)
			{
				strValue.Format("            %-3d      ", i+1);
			
		        m_rich_edit.AppendColor(strValue,RGB(128,128,128));

			    strValue.Format("%-4d  ", psData->uApp.sFrezTaskPara.sCmdPn[i].usPn);
				m_rich_edit.AppendColor(strValue,RGB(255,0,255));

				eCmd = psData->uApp.sFrezTaskPara.sCmdPn[i].eCmd;
				
				eRet = eMcGetCmdInfor(eCmd, eDir, &cmdInfor);
				if(eRet == MC_OK)
				{
					strCmdName = cmdInfor.pName;
					
				}
				else
				{
					strCmdName = "未知命令类型";
				}
				
				//strValue.Format("%04X  F%-3d %s\n", eCmd, eCmd &0xFF, strCmdName);
				strValue.Format("F%-3d %s\n", eCmd &0xFF, strCmdName);
				m_rich_edit.AppendColor(strValue,crValue);

			
			}
			
			
			
			insertLine();
		}
		break;
		case MCMD_AFN_A_F57_TML_CFG_INFO:
			{
				
				insertLine();
				m_rich_edit.AppendColor("\n支持的测量点信息点组数据:",crNormal);	
				strValue.Format("%d\n" ,psData->uApp.sTmlCfgInfor.ucSprt);
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("    已经配置的测量点个数:",crNormal);	
				strValue.Format("%d\n" ,psData->uApp.sTmlCfgInfor.usNum);
				m_rich_edit.AppendColor(strValue,crValue);
				for (i = 0; i < psData->uApp.sTmlCfgInfor.usNum; i++)
				{
			       m_rich_edit.AppendColor("支持的测量点信息点组数据:\n",crNormal);	
					       strValue.Format("                         PN[%d] = %d\n" ,i, psData->uApp.sTmlCfgInfor.usPn[i]);
					m_rich_edit.AppendColor(strValue,crValue);
				}
				

				insertLine();
			}
			break;
		case MCMD_AFN_5_F1_CHECK_TIME:
		case MCMD_AFN_D_F1_CLOCK:
		{
				insertLine();
				m_rich_edit.AppendColor("\n对时命令:",crNormal);
				strValue.Format("%d年%d月%d日 星期%d %d:%d:%d\n",
					psData->uApp.sCheckClock.ucYY,
					psData->uApp.sCheckClock.ucMM,
					psData->uApp.sCheckClock.ucDD,
					psData->uApp.sCheckClock.ucWW,
					
					psData->uApp.sCheckClock.ucHH,
					psData->uApp.sCheckClock.ucmm,
					psData->uApp.sCheckClock.ucss);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;
			
		case MCMD_AFN_D_F3_EVENT_1:
			{
				insertLine();
				m_rich_edit.AppendColor("\n重要事件:",crNormal);
				strValue.Format("%d\n" ,psData->uApp.usEc1);
					
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;

		case MCMD_AFN_D_F4_EVENT_2:
			{
				insertLine();
				m_rich_edit.AppendColor("\n一般事件:",crNormal);
				strValue.Format("%d\n" ,psData->uApp.usEc2);
				
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;
			
		case MCMD_AFN_D_F5_EVENT_STATE:
			{
				insertLine();
				m_rich_edit.AppendColor("\n事件状态标志:\n",crNormal);
				for (i = 1; i < MC_ERC_NUM_MAX; i++)
				{
					eMcErc eErc = (eMcErc)(i);
					switch(eErc)
					{
					case MC_ERC_1_RESET:
						strValue =  "ERC1: 复位事件";
						break;

					case MC_ERC_2_DATA_CLEAR:
						strValue =  "ERC2: 指定数据清零事件";
						break;

					case MC_ERC_3_SOFT_CHANGE:
						strValue =  "ERC3: 软件版本变更事件";
						break;

					case MC_ERC_4_PARA_CHANGE:
						strValue =  "ERC4: 参数变更事件";
						break;

					case MC_ERC_5_CHECK_TIME:
						strValue =  "ERC5: 校时事件";
						break;

					case MC_ERC_6_STATE_CHANGE:
						strValue =  "ERC6: 状态量变位事件";
						break;

					case MC_ERC_7_REMOTE_SWITCH:
						strValue =  "ERC7: 遥控跳闸事件";
						break;

					case MC_ERC_8_POWER_ON_OFF:
						strValue =  "ERC8: 停/上电事件";
						break;

					case MC_ERC_9_FACTOR_OVER:
						strValue =  "ERC9: 总功率因素越限事件";
						break;

					case MC_ERC_10_VOLT_EXCP:
						strValue =  "ERC10: 电压偏差越限事件";
						break;

					case MC_ERC_11_VOLT_CIRCLE:
						strValue =  "ERC11: 电压回路异常事件";
						break;

					case MC_ERC_12_ELEC_CRICLE:
						strValue =  "ERC12: 电流回路异常事件";
						break;

					case MC_ERC_13_VOLT_OVER:
						strValue =  "ERC13: 电压越限事件";
						break;

					case MC_ERC_14_ELEC_OVER:
						strValue =  "ERC14: 电流越限事件";
						break;

					case MC_ERC_15_UNBL_OVER_V:
						strValue =  "ERC15: 电压不平衡度越限事件";
						break;

					case MC_ERC_16_UNBL_OVER_I:
						strValue =  "ERC16: 电流不平衡度越限事件";
						break;

					case MC_ERC_17_HUNBL_OVER_V:
						strValue =  "ERC17: 谐波电压畸变率越限事件";
						break;

					case MC_ERC_18_HUNBL_OVER_I:
						strValue =  "ERC18: 谐波电流畸变率越限事件";
						break;

					case MC_ERC_19_FLASH_OVER:
						strValue =  "ERC19: 闪变越限事件";
						break;

					case MC_ERC_20_NELC_OVER:
						strValue =  "ERC20: 非电气量越限事件";
						break;
						
					default:
						strValue =  "ERC0: 未知事件记录类型";
						break;
					}
					m_rich_edit.AppendColor(strValue,crValue);

					strValue.Format(":%s\n", psData->uApp.sEventState.bHave[i] == TRUE ? "有":"无");
					
					m_rich_edit.AppendColor(strValue,RGB(255,0,0));
				}
				
			
				insertLine();
			}
			break;

		case MCMD_AFN_D_F6_POWR_TIMES:
		case MCMD_AFN_D_F105_VMPP_TIME_A:
		case MCMD_AFN_D_F106_VMPP_TIME_B:
		case MCMD_AFN_D_F107_VMPP_TIME_C:
		case MCMD_AFN_D_F108_VMNN_TIME_A:
		case MCMD_AFN_D_F109_VMNN_TIME_B:
			{
				insertLine();
				m_rich_edit.AppendColor("\n(+)NNNNNN:  ",crNormal);
				strValue.Format("%d", psData->uApp.sPowerTimes.ulTimes);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;
			
        case MCMD_AFN_D_F25_POWR_HAVE_T:
        case MCMD_AFN_D_F26_POWR_NONE_T:
        case MCMD_AFN_D_F33_DEMAND:
        case MCMD_AFN_D_F34_DEMAND_MAX:
        case MCMD_AFN_D_F64_CIRCLE_V:
		case MCMD_AFN_D_F89_TFW_HAVE:
		case MCMD_AFN_D_F90_TFW_NONE:
		case MCMD_AFN_D_F91_THW_HAVE:
		case MCMD_AFN_D_F92_THW_NONE:
			{
				insertLine();
				m_rich_edit.AppendColor("\n(+)XX.XXXX:  ",crNormal);
				strValue.Format("%6.4f", psData->uApp.sPowerHaveT.fXX_XXXX);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;

		case MCMD_AFN_D_F27_FACTR_T:
        case MCMD_AFN_D_F28_FACTR_A:
        case MCMD_AFN_D_F29_FACTR_B:
        case MCMD_AFN_D_F30_FACTR_C:
		case MCMD_AFN_D_F41_POWR_HAVE_A:
        case MCMD_AFN_D_F42_POWR_HAVE_B:
        case MCMD_AFN_D_F43_POWR_HAVE_C:
        case MCMD_AFN_D_F44_POWR_NONE_A:
        case MCMD_AFN_D_F45_POWR_NONE_B:
        case MCMD_AFN_D_F46_POWR_NONE_C:   
        case MCMD_AFN_D_F63_VOLT_UBL:
		case MCMD_AFN_D_F113_VABR_TOTL_A:
		case MCMD_AFN_D_F114_VABR_TOTL_B:
		case MCMD_AFN_D_F115_VABR_TOTL_C:
		case MCMD_AFN_D_F116_EABR_TOTL_A:
		case MCMD_AFN_D_F117_EABR_TOTL_B:
		case MCMD_AFN_D_F118_EABR_TOTL_C:
		case MCMD_AFN_D_F121_VABR_ODD_A:
		case MCMD_AFN_D_F122_VABR_EVN_A:
		case MCMD_AFN_D_F123_VABR_ODD_B:
		case MCMD_AFN_D_F124_VABR_EVN_B:
		case MCMD_AFN_D_F125_VABR_ODD_C:
		case MCMD_AFN_D_F126_VABR_EVN_C:
		case MCMD_AFN_D_F128_EABR_OOD_A:
		case MCMD_AFN_D_F129_EABR_EVN_A:
		case MCMD_AFN_D_F130_EABR_OOD_B:
		case MCMD_AFN_D_F131_EABR_EVN_B:
		case MCMD_AFN_D_F132_EABR_OOD_C:
		case MCMD_AFN_D_F133_EABR_EVN_C:
		case MCMD_AFN_D_F137_FLS_SHRT_A:
		case MCMD_AFN_D_F138_FLS_SHRT_B:
		case MCMD_AFN_D_F139_FLS_SHRT_C:
		case MCMD_AFN_D_F140_FLS_LONG_A:
		case MCMD_AFN_D_F141_FLS_LONG_B:
		case MCMD_AFN_D_F142_FLS_LONG_C:			
			{
				insertLine();
				m_rich_edit.AppendColor("\n(+)XX.XX:  ",crNormal);
				strValue.Format("%4.2f", psData->uApp.sPowerHaveT.fXX_XXXX);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;

		case MCMD_AFN_D_F60_VANGL_A:
        case MCMD_AFN_D_F61_VANGL_B:
        case MCMD_AFN_D_F62_VANGL_C:
			{
				insertLine();
				m_rich_edit.AppendColor("\n(+/-)XXX.X:  ",crNormal);
				strValue.Format("%4.2f", psData->uApp.sVAngleA.fsXXX_X);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();

			}
        break;


		case MCMD_AFN_D_F153_HARM_VINC_A:
        case MCMD_AFN_D_F154_HARM_VINC_B:
        case MCMD_AFN_D_F155_HARM_VINC_C:
        case MCMD_AFN_D_F156_HARM_EINC_A:
        case MCMD_AFN_D_F157_HARM_EINC_B:
        case MCMD_AFN_D_F158_HARM_EINC_C:
			{
				insertLine();
				m_rich_edit.AppendColor("\n谐波次数:  ",crNormal);
				strValue.Format("2次 - %d次", psData->uApp.sHarmVincA.ucN);
				m_rich_edit.AppendColor(strValue,crValue);
			
				for(i = 0; i < psData->uApp.sHarmVincA.ucN -1; i++)
				{
					strValue.Format("%d次\t(+)XX_XX: ", i+2);
					m_rich_edit.AppendColor(strValue,crNormal);
					strValue.Format("%4.2f\n",  psData->uApp.sHarmVincA.fXX_XX[i]);
					m_rich_edit.AppendColor(strValue,crValue);
				}

				insertLine();	
			}
        break;  

        case MCMD_AFN_D_F145_HARM_VOLT_A:
        case MCMD_AFN_D_F146_HARM_VOLT_B:
        case MCMD_AFN_D_F147_HARM_VOLT_C:
			{
				insertLine();
				m_rich_edit.AppendColor("\n谐波次数:  ",crNormal);
				strValue.Format("2次 - %d次\n", psData->uApp.sHarmVoltA.ucN);
				m_rich_edit.AppendColor(strValue,crValue);
				
				for(i = 0; i < psData->uApp.sHarmVoltA.ucN - 1; i++)
				{
					strValue.Format("%d次\t(+)XXX_X: ", i+2);
					m_rich_edit.AppendColor(strValue,crNormal);
					strValue.Format("%4.1f\n",  psData->uApp.sHarmVoltA.fXXX_X[i]);
					m_rich_edit.AppendColor(strValue,crValue);
				}
				
				insertLine();	
			}
        break;  

        case MCMD_AFN_D_F148_HARM_ELEC_A:
        case MCMD_AFN_D_F149_HARM_ELEC_B:
        case MCMD_AFN_D_F150_HARM_ELEC_C:
			{
				insertLine();
				m_rich_edit.AppendColor("\n谐波次数:  ",crNormal);
				strValue.Format("%4.2f", psData->uApp.sHarmElecA.ucN);
				m_rich_edit.AppendColor(strValue,crValue);
				
				for(i = 0; i < psData->uApp.sHarmElecA.ucN; i++)
				{
					strValue.Format("(+/-)XXX_XXX[%d]: ", i);
					m_rich_edit.AppendColor(strValue,crNormal);
					strValue.Format("%6.3f\n",  psData->uApp.sHarmElecA.fsXXX_XXX[i]);
					m_rich_edit.AppendColor(strValue,crValue);
				}
				
				insertLine();	
			}
        break;  


        case MCMD_AFN_D_F35_DEMAND_TIME:
		case MCMD_AFN_D_F74_VDMAX_A_TIME:
		case MCMD_AFN_D_F76_VDMAX_B_TIME:
		case MCMD_AFN_D_F78_VDMAX_C_TIME:
		case MCMD_AFN_D_F82_IDMAX_A_TIME:
		case MCMD_AFN_D_F84_IDMAX_B_TIME:
		case MCMD_AFN_D_F86_IDMAX_C_TIME:
			{
				insertLine();
				m_rich_edit.AppendColor("\nYYMMDDhhmm:  ",crNormal);
				strValue.Format("%02d年%02d月%02d日 %02d点%02d分",
					psData->uApp.sDemandTime.sTime.ucYY,
					psData->uApp.sDemandTime.sTime.ucMM,
					psData->uApp.sDemandTime.sTime.ucDD,
					psData->uApp.sDemandTime.sTime.ucHH,
					psData->uApp.sDemandTime.sTime.ucmm);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
        break;

		case MCMD_AFN_D_F57_VOLT_A:
		case MCMD_AFN_D_F58_VOLT_B:
		case MCMD_AFN_D_F59_VOLT_C:
		case MCMD_AFN_D_F73_VDMAX_A:
		case MCMD_AFN_D_F75_VDMAX_B:
		case MCMD_AFN_D_F77_VDMAX_C:
			{
				insertLine();
				m_rich_edit.AppendColor("\n(+)XXX.X:  ",crNormal);
				strValue.Format("%4.1f\n", psData->uApp.sVoltA.fXXX_X);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
			break;

		case MCMD_AFN_D_F65_ELEC_A:
        case MCMD_AFN_D_F66_ELEC_B:
        case MCMD_AFN_D_F67_ELEC_C:
        case MCMD_AFN_D_F68_ELEC_M:
        case MCMD_AFN_D_F81_IDMAX_A:
        case MCMD_AFN_D_F83_IDMAX_B:
        case MCMD_AFN_D_F85_IDMAX_C:
			{
				insertLine();
				m_rich_edit.AppendColor("\n(+/-)XXX.XXX:  ",crNormal);
				strValue.Format("%6.3f", psData->uApp.sElecA.fsXXX_XXX);
				m_rich_edit.AppendColor(strValue,crValue);
				insertLine();
			}
        break;  

		case MCMD_AFN_D_F233_NELC_VALUE:
			{
				insertLine();
				CString strTmp;
				m_rich_edit.AppendColor("\n非电气量:",crNormal);

				strValue.Format("%d ", psData->uApp.sNelcValue.eType);
				switch ( psData->uApp.sNelcValue.eType)
				{
				case MC_NELC_TEMP:
					strValue += "温度";
					break;

				case MC_NELC_FLOW:
					strValue += "流量";
					break;

				case MC_NELC_FV:
					strValue += "流速";
					break;

				case MC_NELC_PRESS:
					strValue += "压力";
					break;

				case MC_NELC_HUMI:
					strValue += "湿度";
					break;
					
				case MC_NELC_LIGHT:
					strValue += "照度";
					break;
					
				case MC_NELC_RV:
					strValue += "转速";
					break;

				case MC_NELC_420MA:
					strValue += "4~20MA";
					break;

				default:
					strValue += "未知类型";
					break;
				}
				m_rich_edit.AppendColor(strValue,crValue);

				m_rich_edit.AppendColor("\n精度:",crNormal);
				switch(psData->uApp.sNelcValue.sDouble.ePrec)
				{

				case MC_PREC_P4:
					strTmp.Format("%f", psData->uApp.sNelcValue.sDouble.dValue);

					strValue += "MC_PREC_P4 范围 0, (+/-)10000~99999990000";
					break;

				case MC_PREC_P3:
					strTmp.Format("%f", psData->uApp.sNelcValue.sDouble.dValue);

					strValue += "MC_PREC_P3 范围 0, (+/-)1000~9999999000";
					break;

				case MC_PREC_P2:
					strTmp.Format("%f", psData->uApp.sNelcValue.sDouble.dValue);

					strValue += "MC_PREC_P2 范围 0, (+/-)100~999999900 MC_PREC_P2";
					break;

				case MC_PREC_P1:
					strTmp.Format("%f", psData->uApp.sNelcValue.sDouble.dValue);

					strValue += "MC_PREC_P1 范围 0, (+/-)10~99999990";
					break;

				case MC_PREC_P0:
					strTmp.Format("%f", psData->uApp.sNelcValue.sDouble.dValue);

					strValue += "MC_PREC_P0 范围 0, (+/-)1~9999999";
					break;

					
				case MC_PREC_N1:
					strTmp.Format("%7.1f", psData->uApp.sNelcValue.sDouble.dValue);
					strValue += "MC_PREC_N1 范围 0, (+/-)0.1~999999.9";
					break;

				case MC_PREC_N2:
					strValue += "MC_PREC_N2 范围 0, (+/-)0.01~99999.99";
					strTmp.Format("%7.2f", psData->uApp.sNelcValue.sDouble.dValue);

					break;
					
				case MC_PREC_N3:
					strValue += "MC_PREC_N3 范围 0, (+/-)0.001~9999.999";
					strTmp.Format("%7.3f", psData->uApp.sNelcValue.sDouble.dValue);					
					break;
					
				default:
					strValue += "MC_PREC_UNKOWN 未知范围";
					strTmp.Format("%f", psData->uApp.sNelcValue.sDouble.dValue);
					break;
					
				}
				
				m_rich_edit.AppendColor(strValue,crValue);
				
				m_rich_edit.AppendColor("\n数值:",crNormal);
				m_rich_edit.AppendColor(strTmp,crValue);
				
				insertLine();
			}
			break;

			case MCMD_AFN_C_F9_FREZ_AUTO:
				{
					insertLine();
					CString strTmp;
					m_rich_edit.AppendColor("\n请求冻结数据任务中的数据的起始时间ts:",crNormal);
					

				    strValue.Format("%d年%d月%d日 %d时%d分", 
						psData->uApp.sFrezAutoA.sTs.ucYY,
						psData->uApp.sFrezAutoA.sTs.ucMM,
						psData->uApp.sFrezAutoA.sTs.ucDD,
						psData->uApp.sFrezAutoA.sTs.ucHH,
						psData->uApp.sFrezAutoA.sTs.ucmm);
					m_rich_edit.AppendColor(strValue,crValue);


					m_rich_edit.AppendColor("\n冻结周期:",crNormal);
					strValue.Format("%d", psData->uApp.sFrezAutoA.usPeriod);
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("\n冻结周期单位:",crNormal);
					strValue.Format("%d ", psData->uApp.sFrezAutoA.eUnit);

					switch(psData->uApp.sFrezAutoA.eUnit)
					{
					case MC_PUNT_MONTH:
						strValue += "月";
						break;

					case MC_PUNT_DAY:
						strValue += "日";
						break;

					case MC_PUNT_HOUR:
						strValue += "时";
						break;

					case MC_PUNT_MIN:
						strValue += "分钟";
						break;
					case MC_PUNT_SEC:
						strValue += "秒";
						break;
						
					case MC_PUNT_MS:
						strValue += "毫秒";
						break;
						
					default :
						strValue += "未知的周期单位";
						break;


					}

					m_rich_edit.AppendColor(strValue,crValue);
					
					m_rich_edit.AppendColor("\n冻结周期数:",crNormal);
					strValue.Format("%d", psData->uApp.sFrezAutoA.ucN);
					m_rich_edit.AppendColor(strValue,crValue);

					m_rich_edit.AppendColor("\n上报数据单元数:",crNormal);
					strValue.Format("%d", psData->uApp.sFrezAutoA.ucM);
					m_rich_edit.AppendColor(strValue,crValue);

					for (i = 0; i < psData->uApp.sFrezAutoA.ucM; i++)
					{
						
						strValue.Format("\n--------第%d个数据单元----------", i+1);
				    	m_rich_edit.AppendColor(strValue,crValue);
							
						m_rich_edit.AppendColor("\n命令标识:",crNormal);
						
					
					    eRet = eMcGetCmdInfor(psData->uApp.sFrezAutoA.sOne[i].sCmdPn.eCmd, eDir, &cmdInfor);
						if(eRet == MC_OK)
						{
							strCmdName = cmdInfor.pName;
							strCmdName += "\n";
						}
						else
						{
							strCmdName = "不识别的命令类型\n";
						}
						
						strValue.Format("%04X %s", psData->uApp.sFrezAutoA.sOne[i].sCmdPn.eCmd, strCmdName);
				    	m_rich_edit.AppendColor(strValue,crValue);

						
						m_rich_edit.AppendColor("测量点号:",crNormal);
						strValue.Format("%d", psData->uApp.sFrezAutoA.sOne[i].sCmdPn.usPn);
						m_rich_edit.AppendColor(strValue,crValue);

						for (j = 0; j < psData->uApp.sFrezAutoA.ucN; j++)
						{
							strValue.Format("\n第%d个点数据项-----", j+1);
							m_rich_edit.AppendColor(strValue,crValue);
							
							switch(psData->uApp.sFrezAutoA.sOne[i].sCmdPn.eCmd)
							{
							case MCMD_AFN_D_F233_NELC_VALUE:
								{
									CString strTmp;
									m_rich_edit.AppendColor("\n非电气量:",crNormal);
									
									strValue.Format("%d ", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.eType);
									switch ( psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.eType)
									{
									case MC_NELC_TEMP:
										strValue += "温度";
										break;
										
									case MC_NELC_FLOW:
										strValue += "流量";
										break;
										
									case MC_NELC_FV:
										strValue += "流速";
										break;
										
									case MC_NELC_PRESS:
										strValue += "压力";
										break;
										
									case MC_NELC_HUMI:
										strValue += "湿度";
										break;
										
									case MC_NELC_LIGHT:
										strValue += "照度";
										break;
										
									case MC_NELC_RV:
										strValue += "转速";
										break;
										
									case MC_NELC_420MA:
										strValue += "4~20MA";
										break;
										
									default:
										strValue += "未知类型";
										break;
									}
									m_rich_edit.AppendColor(strValue,crValue);
									
									m_rich_edit.AppendColor("\n精度:",crNormal);
									switch(psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.ePrec)
									{
										
									case MC_PREC_P4:
										strTmp.Format("%f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										
										strValue += "MC_PREC_P4 范围 0, (+/-)10000~99999990000";
										break;
										
									case MC_PREC_P3:
										strTmp.Format("%f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										
										strValue += "MC_PREC_P3 范围 0, (+/-)1000~9999999000";
										break;
										
									case MC_PREC_P2:
										strTmp.Format("%f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										
										strValue += "MC_PREC_P2 范围 0, (+/-)100~999999900 MC_PREC_P2";
										break;
										
									case MC_PREC_P1:
										strTmp.Format("%f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										
										strValue += "MC_PREC_P1 范围 0, (+/-)10~99999990";
										break;
										
									case MC_PREC_P0:
										strTmp.Format("%f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										
										strValue += "MC_PREC_P0 范围 0, (+/-)1~9999999";
										break;
										
										
									case MC_PREC_N1:
										strTmp.Format("%7.1f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										strValue += "MC_PREC_N1 范围 0, (+/-)0.1~999999.9";
										break;
										
									case MC_PREC_N2:
										strValue += "MC_PREC_N2 范围 0, (+/-)0.01~99999.99";
										strTmp.Format("%7.2f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										
										break;
										
									case MC_PREC_N3:
										strValue += "MC_PREC_N3 范围 0, (+/-)0.001~9999.999";
										strTmp.Format("%7.3f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);					
										break;
										
									default:
										strValue += "MC_PREC_UNKOWN 未知范围";
										strTmp.Format("%f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
										break;
										
									}
									
									m_rich_edit.AppendColor(strValue,crValue);
									
									m_rich_edit.AppendColor("\n数值:",crNormal);
									m_rich_edit.AppendColor(strTmp,crValue);
								}
								break;
								
							case MCMD_AFN_D_F57_VOLT_A:
								{

									m_rich_edit.AppendColor("\nA相电压:",crNormal);
									strValue.Format("%4.1f", psData->uApp.sFrezAutoA.sOne[i].uApp[j].sVoltA.fXXX_X);
									m_rich_edit.AppendColor(strValue,crValue);

								}
								break;
							default:
								{

								}
								break;
							}

						}

					}

				    insertLine();
				}
				break;

		default:
			m_rich_edit.AppendColor("未添加内容显示, 如需要请联系作者添加\n", RGB(128,0,255));
			break;
			
	}
}


// 显示子命令信息 及应用层数据
void CNxMasterDlg::showSubData( sMtData *psMtData, eMtDir eDir ,COLORREF crText)
{
	if (!psMtData)
	{
		return;
	}
	
	COLORREF crNormal, crValue;
	CString strValue;
	CString strCmdName;
	CQgdw3761api ruler;
	sMtCmdInfor cmdInfor;
	crNormal = RGB(0,0,0);
	int i, Num;
	// 		UINT8   crR, crG, crB;
	// 		
	// 		crR = rand() % 255;
	// 		crG = rand() % 255;
	// 		crB = rand() % 255;
	// 		crNormal = RGB(crR,crG,crB);
	crValue  = RGB(0,0,255);
	
	eMtErr eRet = eMtGetCmdInfor(psMtData->eCmd, eDir, &cmdInfor);
	if(eRet == MT_OK)
	{
		strCmdName = cmdInfor.pName;
		strCmdName += "\n";
	}
	else
	{
		strCmdName = "不识别的命令类型\n";
	}
	
	m_rich_edit.AppendColor("命令类型:",crText);
	strValue.Format("%04X ", (UINT16)psMtData->eCmd);
	strValue += strCmdName;
	m_rich_edit.AppendColor(strValue,RGB(255,0,0));
	
	m_rich_edit.AppendColor("测量点号:",crText);
	strValue.Format("%d\n", (UINT16)psMtData->usPN);
	m_rich_edit.AppendColor(strValue,crValue);
	
	m_rich_edit.AppendColor("有无数据:",crText);
	strValue.Format("%s\n", psMtData->bApp == TRUE ? "有" : "无");
	m_rich_edit.AppendColor(strValue,crValue);
	
	
	m_rich_edit.AppendColor("数据内容:",crText);
	
	
	switch(psMtData->eCmd)
	{
	case CMD_AFN_0_F1_ALL_OK:
	case CMD_AFN_0_F2_ALL_DENY:
	case CMD_AFN_1_F1_HARD_INIT:
	case CMD_AFN_1_F2_DATA_INIT:
	case CMD_AFN_1_F3_FACTORY_RESET:
	case CMD_AFN_1_F4_PARA_INIT:
	case CMD_AFN_2_F1_LOG_IN:
	case CMD_AFN_2_F2_LOG_OUT:
	case CMD_AFN_2_F3_HEART_BEAT:
		strValue = "无\n";
		// m_rich_edit.AppendColor(strValue,crValue);
		break;
		
	case CMD_AFN_0_F3_ONE_BY_ONE:
		m_rich_edit.AppendColor("\n确认AFN:\t",crNormal);
		strValue.Format("%d\t", psMtData->uApp.sOneByOne.eAFN);
		m_rich_edit.AppendColor(strValue,crValue);
		
		strValue = ruler.GetAfnName(psMtData->uApp.sOneByOne.eAFN);
		strValue += "\n";
		m_rich_edit.AppendColor(strValue,crValue);
		
		m_rich_edit.AppendColor("确认个数:\t",crNormal);
		Num = psMtData->uApp.sOneByOne.ucNum;
		strValue.Format("%d\n", Num);
		m_rich_edit.AppendColor(strValue,crValue);
		
		for (i = 0; i < Num; i++)
		{
			eMtCmd eCmd = psMtData->uApp.sOneByOne.sOne[i].eCmd;
			BOOL   bOk = psMtData->uApp.sOneByOne.sOne[i].bOk;
			UINT16 usPn = psMtData->uApp.sOneByOne.sOne[i].usPn;
			
			m_rich_edit.AppendColor("确认序号:\t",crNormal);
			strValue.Format("%d\n", i+1);
			m_rich_edit.AppendColor(strValue,crValue);
			
			switch (eCmd)
			{
			case CMD_AFN_2_F1_LOG_IN:
				strValue.Format("登录");
				break;
				
			case CMD_AFN_2_F2_LOG_OUT:
				strValue.Format("退出");
				break;
				
			case CMD_AFN_2_F3_HEART_BEAT:
				strValue.Format("心跳");
				break;
			default:
				break;
			}
			
			
			m_rich_edit.AppendColor("确认内容:\t",crNormal);
			m_rich_edit.AppendColor(strValue,crValue);
			
			m_rich_edit.AppendColor("\n确认结果:\t",crNormal);
			strValue.Format("%s\n", bOk == TRUE ? "确认": "否认");
			m_rich_edit.AppendColor(strValue,crValue);
			
			
		}

		break;
		
	case CMD_AFN_4_F1_TML_UP_CFG:
		
		m_rich_edit.AppendColor("\n\t\t终端数传机延时时间RTS:\t",crNormal);
		strValue.Format("%d\n", psMtData->uApp.sTmlUpCfg.ucRTS);
		m_rich_edit.AppendColor(strValue,crValue);
		
		
		m_rich_edit.AppendColor("   终端作为启动站允许发送传输延时时间:\t",crNormal);
		strValue.Format("%d\n", psMtData->uApp.sTmlUpCfg.ucRTM);
		m_rich_edit.AppendColor(strValue,crValue);
		
		
		m_rich_edit.AppendColor("                             重发次数:\t",crNormal);
		strValue.Format("%d\n", psMtData->uApp.sTmlUpCfg.ucReSendTimes);
		m_rich_edit.AppendColor(strValue,crValue);
		
		m_rich_edit.AppendColor("                             心跳周期:\t",crNormal);
		strValue.Format("%d\n", psMtData->uApp.sTmlUpCfg.ucHeartBeat);
		m_rich_edit.AppendColor(strValue,crValue);
		
		m_rich_edit.AppendColor("       集中器等待从动站响应的超时时间:\t",crNormal);
		strValue.Format("%d\n", psMtData->uApp.sTmlUpCfg.usTmWaitTimeoutS);
		m_rich_edit.AppendColor(strValue,crValue);
		
		m_rich_edit.AppendColor("允许自动上报1类数据，同时需要主站确认:\t",crNormal);
		strValue.Format("%s\n", psMtData->uApp.sTmlUpCfg.bAutoReportAsk_1 == TRUE ? "允许" : "禁止");
		m_rich_edit.AppendColor(strValue,crValue);
		
		m_rich_edit.AppendColor("允许自动上报2类数据，同时需要主站确认:\t",crNormal);
		strValue.Format("%s\n", psMtData->uApp.sTmlUpCfg.bAutoReportAsk_2 == TRUE ? "允许" : "禁止");
		m_rich_edit.AppendColor(strValue,crValue);
		
		m_rich_edit.AppendColor("允许自动上报3类数据，同时需要主站确认:\t",crNormal);
		strValue.Format("%s\n", psMtData->uApp.sTmlUpCfg.bAutoReportAsk_3 == TRUE ? "允许" : "禁止");
		m_rich_edit.AppendColor(strValue,crValue);
		
		break;
		
#if 0
		
	case CMD_AFN_4_FN_33_CFG_NOT_ELEC:
		m_rich_edit.AppendColor("\n非电气量:\t",crNormal);
		switch (psMtData->uApp.sCfgNotElec.eType)
		{
		case MT_NELEC_TEMP:
			strValue = "温度";
			break;
		case MT_NELEC_FLOW:
			strValue = "流量";
			break;
		case MT_NELEC_FLOW_V:
			strValue = "流速";
			break;
		case MT_NELEC_PRESS:
			strValue = "压力";
			break;
		case MT_NELEC_HUMID:
			strValue = "湿度";
			break;
		case MT_NELEC_ILLUM:
			strValue = "照度";
			break;
			
		case MT_NELEC_ROTATE:
			strValue = "转速";
			break;
			
		default:
			strValue = "未知非电气量";
			break;
		}
		strValue+= "\n";
		m_rich_edit.AppendColor(strValue,crValue);
		
		
		m_rich_edit.AppendColor("量程上限:\t",crNormal);
		strValue.Format("%0.3lf\n", psMtData->uApp.sCfgNotElec.dMax);
		m_rich_edit.AppendColor(strValue,crValue);
		
		
		m_rich_edit.AppendColor("量程下限:\t",crNormal);
		strValue.Format("%0.3lf\n", psMtData->uApp.sCfgNotElec.dMin);
		m_rich_edit.AppendColor(strValue,crValue);
		
		
		break;
		
		
		case CMD_AFN_C_FN_90_NOT_ELEC:
			m_rich_edit.AppendColor("\n数值类型:\t",crNormal);
			switch (psMtData->uApp.sNotElec.eType)
			{
			case MT_NELEC_TEMP:
				strValue = "温度";
				break;
			case MT_NELEC_FLOW:
				strValue = "流量";
				break;
			case MT_NELEC_FLOW_V:
				strValue = "流速";
				break;
			case MT_NELEC_PRESS:
				strValue = "压力";
				break;
			case MT_NELEC_HUMID:
				strValue = "湿度";
				break;
			case MT_NELEC_ILLUM:
				strValue = "照度";
				break;
				
			case MT_NELEC_ROTATE:
				strValue = "转速";
				break;
				
			default:
				strValue = "未知非电气量";
				break;
			}
			strValue+= "\n";
			m_rich_edit.AppendColor(strValue,crValue);
			
			
			m_rich_edit.AppendColor("非电气量:\t",crNormal);
			strValue.Format("%0.3lf\n", psMtData->uApp.sNotElec.dValue);
			m_rich_edit.AppendColor(strValue,crValue);
			
			
			break;
			
#endif
			default:
				strValue = "暂不支持的命令\n\n";
				break;
		}
		
		if(psMtData->bApp == FALSE)
		{
			strValue = "无\n\n";
			m_rich_edit.AppendColor(strValue,crValue);
		}
		
		
		
}




void CNxMasterDlg::AutoUnpack( char *buf, UINT16 usLen )
{
	if (!buf)
	{
		return;
	}

	CGbnx_31 ruler;
	sMcInit sInit;
	sInit.eRole = MC_ROLE_MASTER ;
	sInit.ucPermitDelayMinutes = 255;
	eMcInit(&sInit);
	CString strLen;
	m_rich_edit.AppendColor("\n报文长度:", RGB(0,0,0));
	strLen.Format("%d\n", usLen);
	m_rich_edit.AppendColor(strLen, RGB(255,0,255));


	char *pUnpackBuf = (char*)malloc(MT_USER_MAX);
	if(!pUnpackBuf)
	{
		m_rich_edit.AppendColor("unpack3761buffer 内存申请失败\n", RGB(255,0,0));
		return;
	}
	
	memset(pUnpackBuf, 0,MT_USER_MAX);
	
	smcPack *psmtPack = (smcPack *)pUnpackBuf;
	eMcErr  eRet;
	
	eRet = emcUnPack(psmtPack, (UINT8*)buf, usLen);

	
	if(eRet == MT_OK)
	{
		// 文本显示
		showUnpackText31(psmtPack);
	}
	else
	{
		CString str = "解析失败\n";
		str+= ruler.getErrMessage(eRet);
		m_rich_edit.AppendColor(str, RGB(255,0,0));
		
	}
	
	m_rich_edit.AppendColor("------------------------------------------------------------------\n\n",RGB(128,128,128));
	free(pUnpackBuf);
	pUnpackBuf = NULL;
}


// 点击发送按钮

void CNxMasterDlg::ClickSendBtn()
{
	OnBtnSendCmd();
}

void CNxMasterDlg::OnChangeEditPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}


// 终端处理链路接口 三个命令  登录 心跳 链路
void CNxMasterDlg::MasterDealLink( CTerminal *pTml, char *pBuf, UINT16 usLen )
{
	if (!pTml || !pBuf || usLen == 0)
	{
		return;
	}

	
	
//	CQgdw3761api ruler;

	UINT32 ulTAddress = 0;
	
	char *pUnpackBuf = (char*)malloc(MT_USER_MAX);
	if(!pUnpackBuf)
	{
		m_rich_edit.AppendColor("unpack3761buffer 内存申请失败\n", RGB(255,0,0));
		return;
	}
	
	memset(pUnpackBuf, 0,MT_USER_MAX);
	
	smcPack *psmtPack = (smcPack *)pUnpackBuf;
	eMcErr  eRet;

	sMcInit sInit;
	sInit.eRole = MC_ROLE_MASTER ;
	sInit.ucPermitDelayMinutes = 255;
	eMcInit(&sInit);

	eRet = emcUnPack(psmtPack, (UINT8*)pBuf, usLen);


	if (eRet == MC_OK)
	{
		if (TRUE == psmtPack->bFixed)
		{
			ulTAddress = psmtPack->sAddress.ulConAddress;

			// 登录 
			if(psmtPack->sCtrl.eFcode == MC_FCD_LOG_IN)
			{
				m_list_tml.setItemLogIn(pTml, ulTAddress);
				
			}
	
			// 退出 
			if(psmtPack->sCtrl.eFcode == MC_FCD_LOG_OUT)
			{
				m_list_tml.setItemLogOut(pTml);
			}


			// 心跳 
			if(psmtPack->sCtrl.eFcode == MC_FCD_HEART_BEAT)
			{
				m_list_tml.setItemHeartBeat(pTml);
			}


		}
		
	}


	free(pUnpackBuf);
	pUnpackBuf = NULL;
}

// 将报文发送给列表中勾选的每一个集中器
BOOL CNxMasterDlg::SendToList( CString strSend)
{	
	CString str;
	if(m_bMaster)
	{
		if (m_bServerRun == false)
		{
			return FALSE;
		}
		//sevSendMsg(m_psockSev1,strSend);
		
		//向当前在线的的列表框架选中的发送
		int i = 0;
		CString strpTml;
		unsigned long ulAddTml;
		CTerminal   *pTml  = NULL;	
		int nListNum = 0;
		nListNum = m_list_tml.GetItemCount();
		
		if (nListNum == 0)
		{
			return FALSE;
		}
		for(i = 0; i < nListNum;i++)
		{
			if(m_list_tml.GetCheck(i))
			{
				strpTml = m_list_tml.GetItemText(i,5);
				sscanf(strpTml.GetBuffer(0),"%x",&ulAddTml);
				pTml = (CTerminal *)ulAddTml;
				
				if(pTml!= NULL)
				{
					sevSendMsg(pTml->m_pSevSocket,strSend);
					str = strSend +"\r\n";
					//m_rich_edit.AppendColor((LPCTSTR)str,RGB(0,255,0));
					strSend.Replace(" ","");
					InsertInfoMasterSend(pTml,strSend.GetLength()/2);
					m_rich_edit.cfAppend(str, CF_MSATER);
					//m_rich_edit.cfAppend(str, CF_INFO);
				}
				
			}
		}
		
	}
	else
	{
		if (m_bClientLink == false)
		{
			return FALSE;
		}

		tmlSendMsg(&m_sockTml,strSend);

		str = strSend +"\r\n";
		strSend.Replace(" ","");
		insertInfoTmlSend(&m_sockTml,strSend.GetLength()/2);
		m_rich_edit.cfAppend(str, CF_TERMINAL);
	
	}

	return TRUE;
}

void CNxMasterDlg::OnCheckAutoRespone() 
{
	// TODO: Add your control notification handler code here
	m_bAutoResponse = m_check_auto_respone.GetCheck();
	
}

// 实现主站对接收报文的自动应答
void CNxMasterDlg::AutoResponseMaster( CTerminal *pTml, char *buf, UINT16 usLen )
{
	if (!buf || !pTml)
	{
		return;
	}


	// 先解析报文	
	//CQgdw3761api ruler;
	CGbnx_31      ruler;
	//sMtInit sInit;
	sMcInit sInit;
	sInit.eRole = MC_ROLE_MASTER ;
	sInit.ucPermitDelayMinutes = 255;
	eMcInit(&sInit);

	//char pUnpackBuf[MT_USER_MAX] = {0};
	char* pUnpackBuf = (char*)malloc(MC_USER_MAX);
	if(!pUnpackBuf)
	{
	   MessageBox("内存申请失败", "错误", MB_OK|MB_ICONERROR);
	   return;
	}
	
	//smtPack *psmtUnPack = (smtPack *)pUnpackBuf;
	smcPack *psmtUnPack = (smcPack *)pUnpackBuf;
	eMcErr  eRet;
	
	eRet = emcUnPack(psmtUnPack, (UINT8*)buf, usLen);
	
	if(eRet != MT_OK)
	{
		CString str = "解析失败\n";
		str+= ruler.getErrMessage(eRet);
		m_rich_edit.AppendColor(str, RGB(255,0,0));
		free(pUnpackBuf);
		return;
	}
	
	// 构建应答报文
	//UINT8 ucOutBuffer[MT_USER_MAX] = {0};
	//char pPackBuf[MT_USER_MAX] = {0};	
	
	UINT8 *ucOutBuffer = (UINT8*)malloc(MC_USER_MAX);
	if(!ucOutBuffer)
	{
		free(pUnpackBuf);
		MessageBox("内存申请失败", "错误", MB_OK|MB_ICONERROR);
	   return;
	}
	
	char *pPackBuf = (char*)malloc(MC_USER_MAX);
	if(!pPackBuf)
	{
		free(pUnpackBuf);
		free(ucOutBuffer);
	   MessageBox("内存申请失败", "错误", MB_OK|MB_ICONERROR);
		return;
	}

	CGbnx_31 ruler_response;
	eMcDir	eDir =  MC_DIR_M2S;
	sMcPackMst * psmtPack = (sMcPackMst *)pPackBuf;
	
	BOOL     bAuto = FALSE;
	CString  strPw,strPack;
	char *pOutBuf = (char*)ucOutBuffer;
	psmtPack->sAddress = psmtUnPack->sAddress;
	
    // 附加域

	m_tabDlgPack.GetCtrlPw((char*)psmtPack->aPw);
	
	psmtPack->ucPSEQ = 0;

	if (psmtUnPack->bFixed == TRUE)
	{
		if(psmtUnPack->sData[0].eCmd == MCMD_AFN_2_F1_LOG_IN || 
			psmtUnPack->sData[0].eCmd == MCMD_AFN_2_F2_LOG_OUT ||
			psmtUnPack->sData[0].eCmd == MCMD_AFN_2_F3_HEART_BEAT)
		{
			//AfxMessageBox("登录 ");
			psmtPack->sData[0].eCmd = MCMD_AFN_2_F4_LINK_OK;
			psmtPack->sData[0].usPN = 0;
			psmtPack->sData[0].bApp = FALSE;
			
			}
	}
	else
	{
		switch(psmtUnPack->sAc.eAfn)
		{
		case MC_AFN_02_LINK:
			
			// 登录 
			if(psmtUnPack->sData[0].eCmd == MCMD_AFN_2_F1_LOG_IN || 
				psmtUnPack->sData[0].eCmd == MCMD_AFN_2_F2_LOG_OUT ||
				psmtUnPack->sData[0].eCmd == MCMD_AFN_2_F3_HEART_BEAT)
			{
				//AfxMessageBox("登录 ");
				psmtPack->sData[0].eCmd = MCMD_AFN_2_F4_LINK_OK;
				psmtPack->sData[0].usPN = 0;
				psmtPack->sData[0].bApp = FALSE;
				
			}
			
			// 退出 
			
			
			break;
			
		default:
			free(pUnpackBuf);
			free(ucOutBuffer);
			free(pPackBuf);
			return;
			//break;
		}

	}





	// 调用封装函数
	UINT16 usLenOut = 0;
	eRet = emcPackMst(psmtPack,(UINT8*)ucOutBuffer ,&usLenOut);
	if(eRet != MT_OK)
	{
	
		if (eRet == MT_ERR_NONE)
		{
			MessageBox("该方向没有对应的命令", "错误", MB_OK|MB_ICONERROR);
		}
		else
		{
			strPack.Format("error %d %s", eRet , ruler_response.getErrMessage(eRet));
			AfxMessageBox(strPack);

		}
		
		free(pUnpackBuf);
		free(ucOutBuffer);
		free(pPackBuf);
		return;
	}
	else
	{
		CString str;
		int     i = 0;
		m_AutoResponseMasterSeconds = m_tabDlgPack.GetAutoResponseDelaySecond();
			
		if (m_AutoResponseMasterSeconds > 0)
		{
			str.Format("自动应答延时 %d 秒\n", m_AutoResponseMasterSeconds);
			m_rich_edit.cfAppend(str, CF_MSATER);

			m_pTmlAutoResponseMaster = pTml;
			memcpy(m_sendBuferAutoResponseMaster, pOutBuf, usLenOut);
			m_usSendBufLenMaster = usLenOut;			
			SetTimer(MASTER_AUTO_RES_TIMER, 1000, NULL);
		}
		else
		{
			strPack = ruler.BufferToHex((char*)pOutBuf, usLenOut);		
			str = strPack +"\r\n";
			send(*(pTml->m_pSevSocket),(char*)pOutBuf,usLenOut,0);

			strPack.Replace(" ", "");
			InsertInfoMasterSend(pTml,strPack.GetLength()/2);
			m_rich_edit.cfAppend(str, CF_MSATER);
		}
	}
	
	free(pUnpackBuf);
	free(ucOutBuffer);
    free(pPackBuf);
}

// 实现从站对接收报文的自动应答
void CNxMasterDlg::AutoResponseTerminal( char *buf, UINT16 usLen )
{
	
}

void CNxMasterDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	switch(nIDEvent)
	{
	case MASTER_AUTO_RES_TIMER:
		AutoResponseMasterTimer();
		
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

// 主站自动回复延时显示
void CNxMasterDlg::AutoResponseMasterTimer(  )
{
	CString str, strPack;
	CQgdw3761api ruler;

	m_AutoResponseMasterSeconds--;
	
	if (m_AutoResponseMasterSeconds <= 0)
	{
		strPack = ruler.BufferToHex((char*)m_sendBuferAutoResponseMaster, m_usSendBufLenMaster);		
		str = strPack +"\r\n";
		send(*(m_pTmlAutoResponseMaster->m_pSevSocket),(char*)m_sendBuferAutoResponseMaster,m_usSendBufLenMaster,0);
		InsertInfoMasterSend(m_pTmlAutoResponseMaster,strPack.GetLength()/2);
		m_rich_edit.cfAppend(str, CF_MSATER);
		KillTimer(MASTER_AUTO_RES_TIMER);
		return;
	}
	else
	{
		str.Format("剩余时间 %d 秒\n", m_AutoResponseMasterSeconds);
		m_rich_edit.cfAppend(str, CF_MSATER);
		
	}


	
}

void CNxMasterDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CNxMasterDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	free(m_sendBuferAutoResponseMaster);

	if (NULL != m_imagelist && m_imagelist->DeleteImageList())
	{
		delete m_imagelist;      
	}
}


void CNxMasterDlg::OnDataPreSet() 
{
	// TODO: Add your command handler code here
	
}

CString CNxMasterDlg::charToCString( char *pStr, int n )
{
	CString str;
	CString strTmp;
	int i = 0;
	if (pStr)
	{
		for (i = 0; i < n; i++)
		{
			strTmp.Format("%c", (char)pStr[i]);
			str+=strTmp;
		}
	}

	return str;
}

void CNxMasterDlg::OnRclickRicheditMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu popMenu;
	
	popMenu.LoadMenu(IDR_MENU_RICHEDIT);
	CMenu *pMu = popMenu.GetSubMenu(1); 
	POINT pt; 
	::GetCursorPos(&pt); 






	pMu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTALIGN, pt.x, pt.y, this);
	*pResult = 0;


	
	
}

void CNxMasterDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

}

void CNxMasterDlg::OnClickRicheditMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CNxMasterDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	if (pWnd->m_hWnd == m_rich_edit.m_hWnd)
	{
		CMenu popMenu;	
		popMenu.LoadMenu(IDR_MENU_RICHEDIT);
		CMenu *pMu = popMenu.GetSubMenu(1); 
		CString strSel = m_rich_edit.GetSelText();
		int n = m_rich_edit.GetTextLength();
		if (n == 0)
		{
	       pMu->EnableMenuItem(AFX_RICH_CLR, MF_DISABLED|MF_GRAYED);
		}
	
		
		if (strSel == "")
		{
			pMu->EnableMenuItem(AFX_RICH_COPY, MF_DISABLED|MF_GRAYED);
			pMu->EnableMenuItem(AFX_RICH_TRANS, MF_DISABLED|MF_GRAYED);
			
			pMu->EnableMenuItem(AFX_RICH_ADDT, MF_DISABLED|MF_GRAYED);
		}
		else
		{
			
			strSel.Replace("\n", "");
			strSel.Replace("\t", "");
			strSel.Replace("\r", "");
			strSel.Replace(" ", "");
			
			UINT8 buffer[1024] = {0};
			UINT16 usLen = 0;
			
			CGbnx_31     ruler;
			sMcInit      sInit;
			sInit.eRole = MC_ROLE_MASTER;
			sInit.ucPermitDelayMinutes = 255;
			
			eMcInit(&sInit);
			
			
			BOOL bOk = ruler.CStringToHexBuffer(strSel, (char *)buffer, &usLen);
			BOOL bFixed;
			
			eMcErr eRet = emcIsValidPack(buffer, usLen, &bFixed);
			if (eRet == MC_OK)
			{
				pMu->EnableMenuItem(AFX_RICH_TRANS,  MF_ENABLED);
				pMu->EnableMenuItem(AFX_RICH_ADDT,  MF_ENABLED);
			}
			else
			{
				pMu->EnableMenuItem(AFX_RICH_TRANS, MF_DISABLED|MF_GRAYED);
				pMu->EnableMenuItem(AFX_RICH_ADDT, MF_DISABLED|MF_GRAYED);
			}
		}
		


	
		




		pMu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_LEFTALIGN, point.x, point.y, this);
	}
}

void CNxMasterDlg::OnRichClr() 
{
	// TODO: Add your command handler code here
	m_rich_edit.SetWindowText("");
}

void CNxMasterDlg::OnRichTrans() 
{
	// TODO: Add your command handler code here
	
	CString str = m_rich_edit.GetSelText();
	if(str != "")
	{
		//m_tab.SetCurFocus(3);
		str.Replace("\n", "");
		str.Replace("\t", "");
		str.Replace("\r", "");
		//str.Replace(" ", "");
		m_tabDlgUnpack.unpack(str);
	
		//AfxMessageBox(str);
	}
	
	
}

void CNxMasterDlg::OnRichCopy() 
{
	// TODO: Add your command handler code here
	if(OpenClipboard())    //打开剪切板
	{
		EmptyClipboard(); //清空剪切板
		CString str;       //从控件中取出字符
		HANDLE hclip;      //GlobalAlloc分配内存的句柄
		char *buf;         //返回的内存地址
		str = m_rich_edit.GetSelText();
		hclip=GlobalAlloc(GMEM_MOVEABLE,str.GetLength()+1);//在堆上分配制定数目的字节
		buf=(char*)GlobalLock(hclip);//对内存块加锁,并返回它的内存地址
		strcpy(buf,str);        //将字符拷贝到内存中
		GlobalUnlock(hclip);     //解锁
		SetClipboardData(CF_TEXT,hclip);//向剪切板上放置内存中的数据
		CloseClipboard();        //关闭剪切板
	}
}

void CNxMasterDlg::OnRichAddt() 
{
	// TODO: Add your command handler code here
	CString str = m_rich_edit.GetSelText();
	if(str != "")
	{
		m_tab.SetCurFocus(3);
		str.Replace("\n", "");
		str.Replace("\t", "");
		str.Replace("\r", "");

		m_tab.SetCurFocus(4);
		m_tabDlgTask.setOneText(str);
		//AfxMessageBox(str);
	}
}

void CNxMasterDlg::OnIdTkSet() 
{
	// TODO: Add your command handler code here
    m_tab.SetCurFocus(4);
}

void CNxMasterDlg::OnRichInsetLen() 
{
	// TODO: Add your command handler code here
	
	insetLineStype();
	
}

void CNxMasterDlg::insetLineStype()
{
		COLORREF crText;
	UINT8   crR, crG, crB;
	int i;
	CString strText;
	CString str;
	CString strT;

	crR = rand() % 255;
	crG = rand() % 255;
	crB = rand() % 255;
	i = rand() % 255;
	crText = RGB(crR,crG,crB);
	i = i%32;
	
	switch(i)
	{
	case 0:
		strT = "..";
		break;
	case 1:
		strT = "㊣";
		break;
	case 2:
		strT = "**";
		break;
		
	case 3:
		strT = "~~";
		break;
		
	case 4:
		strT = "!!";
		break;
		
		
	case 5:
		strT = "##";
		break;
		
	case 6:
		strT = "&&";
		break;
		
	case 7:
		strT = "<<";
		break;
		
	case 8:
		strT = ">>";
		break;
		
		
	case 9:
		strT = "??";
		break;
		
	case 10:
		strT = "^^";
		break;		
		
	case 11:
		strT = "※";
		break;
	case 12:
		strT = "卍";
		break;
		
	case 13:
		strT = "卐";
		break;
		
	case 14:
		strT = "♂";
		break;
		
		
	case 15:
		strT = "♀";
		break;
		
	case 16:
		strT = "☆";
		break;
	
	case 17:
		strT = "▽";
		break;
		
	case 18:
		strT = "⊙";
		break;
		
		
	case 19:
		strT = "⌒";
		break;
		
	case 20:
		strT = "§";
		break;		
		
	case 21:
		strT = "∷";
		break;
		
	case 22:
		strT = "＊";
		break;	
		
	case 23:
		strT = "▓";
		break;	
		
	case 24:
		strT = "≡";
		break;		

	case 25:
		strT = "﹌";
		break;		

		
	case 26:
		strT = "⊥";
		break;
		
	case 27:
		strT = "±";
		break;
		
	case 28:
		strT = "∴";
		break;
		
		
	case 29:
		strT = "∵";
		break;
		
	case 30:
		strT = "∮";
		break;	

	case 31:
		strT = "¤";
		break;
	case 32:
		strT = "Ω";
		break;
	case 33:
		strT = "Φ";
		break;

	default:
		strT = "--";
		break;
	}
	

	for (i = 0; i < 36; i++)
	{
		str += strT;
	}
	
	strText = "\n" + str + "\n";
	m_rich_edit.AppendColor(strText, crText);
}



void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_EMailLink.SetURL(_T("mailto:vliming@126.com"));
	m_EMailLink.SetUnderline(CHyperLink::ulAlways);
	return TRUE;
}

BOOL CNxMasterDlg::IsAdministrator()
{
	BOOL bIsElevated = FALSE;
	HANDLE hToken = NULL;
	UINT16 uWinVer = LOWORD(GetVersion());
	uWinVer = MAKEWORD(HIBYTE(uWinVer),LOBYTE(uWinVer));
	
	if (uWinVer < 0x0600)//不是VISTA、Windows7
		return(TRUE);
	
	if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {
		
		struct {
			DWORD TokenIsElevated;
		} /*TOKEN_ELEVATION*/te;
		DWORD dwReturnLength = 0;
		
		if (GetTokenInformation(hToken,/*TokenElevation*/(_TOKEN_INFORMATION_CLASS)20,&te,sizeof(te),&dwReturnLength)) {
			if (dwReturnLength == sizeof(te))
				bIsElevated = te.TokenIsElevated;
		}
		CloseHandle( hToken );
	}
	return bIsElevated;

}

// 将路径信息写入注册表，打开时以提示是否用管理员身份打开
void CNxMasterDlg::SetRegAdmin()
{
	CString strPath = ReturnPath();
	/*
	HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers]
		"C:\\Program Files\\win7test2.exe"="RUNASADMIN"
		*/

	CRegistry reg;
	CString strSubKey = "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
	reg.SetRootKey(HKEY_CURRENT_USER);
	
	if(reg.bKeyExists(strSubKey, NULL) == FALSE)
	{
		reg.CreateKey(strSubKey);
	}
	else
	{
		
		reg.Open(strSubKey);
	}
	reg.Write(strPath, "RUNASADMIN");
}

CString CNxMasterDlg::ReturnPath()
{
	
	
	CString    sPath;   
	// 	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	// 	sPath.ReleaseBuffer    ();   
	// 	int    nPos;   
	// 	nPos=sPath.ReverseFind('\\');   
	// 	sPath=sPath.Left(nPos);   
	// 	return    sPath;   
	
	   char pBuf[MAX_PATH];                                               //存放路径的变量
	   GetCurrentDirectory(MAX_PATH,pBuf);                   //获取程序的当前目录
	   strcat(pBuf,"\\");
	   strcat(pBuf,AfxGetApp()->m_pszExeName);   
	   strcat(pBuf,".exe"); 
	   sPath.Format("%s", pBuf);
	   
	   return    sPath;   

}
