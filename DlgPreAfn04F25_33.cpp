// DlgPreAfn04F25_33.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F25_33.h"
#include "NxConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F25_33 dialog


CDlgPreAfn04F25_33::CDlgPreAfn04F25_33(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F25_33::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F25_33)
	m_edit_usID = 0;
	m_edit_ucPort = 0;
	m_edit_ucAddr = _T("");
	m_edit_pwd = _T("");
	m_edit_acs_port = 0;
	m_edit_usAcsPort = 0;
	m_edit_zigbee_mac = _T("");
	//}}AFX_DATA_INIT
	m_bF25Elec = TRUE;
	m_protoName[PROT_GBNX_32]    = "GB/TXXXX.3.2";
	m_protoName[RROT_DLT645_97]  = "DL/T645 1997";
	m_protoName[PROT_DLT645_07]  = "DL/T645 2007";
	m_protoName[PROT_MODBUS]     = "Modus";
	m_protoName[PROT_USER]       = "用户自定义";
	
	// port type
	m_portName[PORT_DC] = "直流模拟量";
	m_portName[PORT_AC] = "交流模拟量";
	m_portName[PORT_SER] = "串口(RS232/485)";
	m_portName[PORT_ETH] = "以太网";
	m_portName[PORT_ZIGB] = "zigbee";
	m_portName[PORT_USER] = "用户自定义";
	
	// baud name
	m_BaudName[INDEX_BAUD_1200] = "1200";
	m_BaudName[INDEX_BAUD_2400] = "2400";
	m_BaudName[INDEX_BAUD_4800] = "4800";
	m_BaudName[INDEX_BAUD_9600] = "9600";
	m_BaudName[INDEX_BAUD_19200] = "19200";
	m_BaudName[INDEX_BAUD_38400] = "38400";
	m_BaudName[INDEX_BAUD_76800] = "76800";

	// check
	m_checkName[CHECK_NONE] = "无校验";
	m_checkName[CHECK_ODD]  = "奇校验";
	m_checkName[CHECK_EVEN] = "偶校验";

	// stop
	m_stopName[STOP_1] = "1";
	m_stopName[STOP_2] = "2";
	
	// data bit
	m_DBitName[DBIT_5] = "5";
	m_DBitName[DBIT_6] = "6";
	m_DBitName[DBIT_7] = "7";
	m_DBitName[DBIT_8] = "8";
}


void CDlgPreAfn04F25_33::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F25_33)
	DDX_Control(pDX, IDC_IP_sAccess, m_ip_sAccess);
	DDX_Control(pDX, IDC_IP_ACS, m_ip_acs);
	DDX_Control(pDX, IDC_COMB_STOP, m_comb_stop);
	DDX_Control(pDX, IDC_COMB_DATABIT, m_comb_databit);
	DDX_Control(pDX, IDC_COMB_CHECK, m_comb_check);
	DDX_Control(pDX, IDC_COMB_BAUD, m_comb_baud);
	DDX_Control(pDX, IDC_COMB_PORT, m_comb_port);
	DDX_Control(pDX, IDC_COMB_PROTO, m_comb_proto);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_ID, m_edit_usID);
	DDX_Text(pDX, IDC_EDIT_PORT, m_edit_ucPort);
	DDX_Text(pDX, IDC_EDIT_ucAddr, m_edit_ucAddr);
	DDX_Text(pDX, IDC_EDIT_PWD, m_edit_pwd);
	DDX_Text(pDX, IDC_EDIT_ACS_PORT, m_edit_acs_port);
	DDX_Text(pDX, IDC_EDIT_usAcsPort, m_edit_usAcsPort);
	DDX_Text(pDX, IDC_EDIT_ZIGBEE_MAC, m_edit_zigbee_mac);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F25_33, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F25_33)
	ON_CBN_SELENDOK(IDC_COMB_PORT, OnSelendokCombPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F25_33 message handlers

void CDlgPreAfn04F25_33::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F25_33::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	// set title
	if(m_bF25Elec == TRUE)
	{
		SetWindowText("AFN04 F25 电气测量点配置参数");
	}
	else
	{
		SetWindowText("AFN04 F33 非电气测量点配置参数");
	}

	
	// init comb
	int i = 0;
	for (i = 0; i < PROT_NUM_MAX; i++)
	{
		m_comb_proto.InsertString(i, m_protoName[i]);
	}

	m_comb_proto.SetCurSel(PROT_GBNX_32);
	
	// port
	for (i = 0; i < PORT_NUM_MAX; i++)
	{
		m_comb_port.InsertString(i, m_portName[i]);
	}

	m_comb_port.SetCurSel(PORT_SER);
	ShowPortSet(PORT_SER);

	// baud 
	for (i = 0; i < BAUD_NUM_MAX; i++)
	{
		m_comb_baud.InsertString(i, m_BaudName[i]);
	}

	m_comb_baud.SetCurSel(INDEX_BAUD_9600);
	
	// check
	for (i = 0; i < CHECK_NUM_MAX; i++)
	{
		m_comb_check.InsertString(i, m_checkName[i]);
	}

	m_comb_check.SetCurSel(CHECK_NONE);

	// stop
	for (i = 0; i < STOP_NUM_MAX; i++)
	{
		m_comb_stop.InsertString(i, m_stopName[i]);
	}

	m_comb_stop.SetCurSel(0);

	// data bit
	for (i = 0; i < DBIT_NUM_MAX; i++)
	{
		m_comb_databit.InsertString(i, m_DBitName[i]);
	}

	m_comb_databit.SetCurSel(DBIT_5);


	// TODO: Add extra initialization here
	m_btn_ok.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_ok.SetIcon(IDI_ICON_RIGHT);
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	m_btn_no.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_no.SetIcon(IDI_ICON_X);
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));


	GetCurValues();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F25_33::OnSelendokCombPort() 
{
	// TODO: Add your control notification handler code here
	int iSel = 0;
	iSel = m_comb_port.GetCurSel();
	ShowPortSet((ePortType)iSel);
}


// 根据不同的端口属性显示内容控件
void CDlgPreAfn04F25_33::ShowPortSet( ePortType eType )
{
	((CButton*)GetDlgItem(IDC_STATIC_ACS_IP))->ShowWindow(SW_HIDE);
	((CButton*)GetDlgItem(IDC_STATIC_ACS_PORT))->ShowWindow(SW_HIDE);
	m_ip_acs.ShowWindow(SW_HIDE);
	((CButton*)GetDlgItem(IDC_EDIT_ACS_PORT))->ShowWindow(SW_HIDE);

	((CButton*)GetDlgItem(IDC_STATIC_BAUD))->ShowWindow(SW_HIDE);
	((CButton*)GetDlgItem(IDC_STATIC_STOP))->ShowWindow(SW_HIDE);
	((CButton*)GetDlgItem(IDC_STATIC_CHECK))->ShowWindow(SW_HIDE);
	((CButton*)GetDlgItem(IDC_STATIC_DATABIT))->ShowWindow(SW_HIDE);
	m_comb_baud.ShowWindow(SW_HIDE);
	m_comb_stop.ShowWindow(SW_HIDE);
	m_comb_check.ShowWindow(SW_HIDE);
	m_comb_databit.ShowWindow(SW_HIDE);

	// zigbee_mac
	((CButton*)GetDlgItem(IDC_EDIT_ZIGBEE_MAC))->ShowWindow(SW_HIDE);
		((CButton*)GetDlgItem(IDC_STATIC_ZIGBEE_MAC))->ShowWindow(SW_HIDE);
	
	switch (eType)
	{
	case PORT_SER:
		((CButton*)GetDlgItem(IDC_STATIC_BAUD))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_STATIC_STOP))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_STATIC_CHECK))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_STATIC_DATABIT))->ShowWindow(SW_SHOW);
		m_comb_baud.ShowWindow(SW_SHOW);
		m_comb_stop.ShowWindow(SW_SHOW);
		m_comb_check.ShowWindow(SW_SHOW);
		m_comb_databit.ShowWindow(SW_SHOW);
		break;
		
	case PORT_ETH:
		((CButton*)GetDlgItem(IDC_STATIC_ACS_IP))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_STATIC_ACS_PORT))->ShowWindow(SW_SHOW);
		m_ip_acs.ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_EDIT_ACS_PORT))->ShowWindow(SW_SHOW);
		
		break;
		
	case PORT_ZIGB:
		((CButton*)GetDlgItem(IDC_EDIT_ZIGBEE_MAC))->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_STATIC_ZIGBEE_MAC))->ShowWindow(SW_SHOW);
		
		break;
		
	default:
		break;
		
	}
}

void CDlgPreAfn04F25_33::GetCurValues()
{
	CString strIP;
	CNxConfig cfg;
	sMcAfn04f25 sAfn04f25;
	char buf[17] = {0};

	if (m_bF25Elec == TRUE)
	{
		cfg.GetPreAfn04F25(&sAfn04f25, TRUE);
	}
	else
	{
		cfg.GetPreAfn04F33(&sAfn04f25, TRUE);
	}
	
	
	m_edit_usID = sAfn04f25.usID;
	m_edit_ucPort = sAfn04f25.ucPort;
	
	// ucaddr
	memcpy(buf, sAfn04f25.ucAddr, 16);
	m_edit_ucAddr.Format("%s", buf);

	// eAcsProto
	eProType eProto;
	switch (sAfn04f25.eAcsProto)
	{
	case MC_ACS_PROT_GBNX_32:
		eProto = PROT_GBNX_32;
		break;

	case MC_ACS_PROT_DLT645_97:
		eProto = RROT_DLT645_97;
		break;

	case MC_ACS_PROT_DLT645_07:
		eProto = PROT_DLT645_07;
		break;

	case MC_ACS_PROT_MODBUS:
		eProto = PROT_MODBUS;
		break;

	case MC_ACS_PROT_USER:
		eProto = PROT_USER;
		break;

	default:
		eProto = PROT_GBNX_32;
		break;

	}

	m_comb_proto.SetCurSel(eProto);

	// ucaddr
	char pwd[7] = {0};
	memcpy(pwd, sAfn04f25.ucPwd, 6);
	m_edit_pwd.Format("%s", pwd);

	// eAcsPort
	ePortType ePort;
	switch(sAfn04f25.eAcsPort)
	{
	case MC_ACS_PORT_DC:
		ePort = PORT_DC;
		break;

	case MC_ACS_PORT_AC:
		ePort = PORT_AC;
		break;

	case MC_ACS_PORT_SER:
		ePort = PORT_SER;
		break;

	case MC_ACS_PORT_ETH:
		ePort = PORT_ETH;
		break;

	case MC_ACS_PORT_ZIGB:
		ePort = PORT_ZIGB;
		break;

	case MC_ACS_PORT_USER:
		ePort = PORT_USER;
		break;

	default:
		ePort = PORT_SER;
		break;
	}
	
	m_comb_port.SetCurSel(ePort);
	ShowPortSet(ePort);

	if(sAfn04f25.eAcsPort == MC_ACS_PORT_SER)
	{
		// eBaud
		eBaud ebaud;
	
		switch (sAfn04f25.uPortPara.sSer.eBaud)
		{
		case MC_BAUD_1200:   
			ebaud = INDEX_BAUD_1200;
			break;
		case	MC_BAUD_2400:
			ebaud = INDEX_BAUD_2400;
				break;
		case	MC_BAUD_4800:
			ebaud = INDEX_BAUD_4800;
			break;
		case	MC_BAUD_9600:
			ebaud = INDEX_BAUD_9600;
			break;
		case	MC_BAUD_19200:
			ebaud = INDEX_BAUD_19200;
			break;
		case	MC_BAUD_38400:  
			ebaud = INDEX_BAUD_38400;
			break;
		case MC_BAUD_76800:
			ebaud = INDEX_BAUD_76800;
			break;
			
		default:
			ebaud = INDEX_BAUD_9600;
			break;
		}

		m_comb_baud.SetCurSel(ebaud);

		// check
		eCheck check_index;

		if (sAfn04f25.uPortPara.sSer.bCheck == TRUE)
		{
			check_index = sAfn04f25.uPortPara.sSer.bOdd ? CHECK_ODD : CHECK_EVEN;
		}
		else
		{
			check_index = CHECK_NONE;
		}
		
		m_comb_check.SetCurSel(check_index);


		// databit
		eDataBit eDatabit;
		eDatabit = (eDataBit)sAfn04f25.uPortPara.sSer.eBit;
		m_comb_databit.SetCurSel(eDatabit);

		// stop
		eStopBit eStop;
		eStop = sAfn04f25.uPortPara.sSer.bStop1 == TRUE ? STOP_1:STOP_2;
		m_comb_stop.SetCurSel(eStop);
	
	}
	
	if(sAfn04f25.eAcsPort == MC_ACS_PORT_ETH)
	{
	
		strIP.Format("%d.%d.%d.%d", 
			sAfn04f25.uPortPara.sEth.sAccess.ip[0],
			sAfn04f25.uPortPara.sEth.sAccess.ip[1],
			sAfn04f25.uPortPara.sEth.sAccess.ip[2],
			sAfn04f25.uPortPara.sEth.sAccess.ip[3]);

			m_ip_acs.SetWindowText(strIP);


			m_edit_acs_port = sAfn04f25.uPortPara.sEth.usPort;
			
	}
	
	if(sAfn04f25.eAcsPort == MC_ACS_PORT_ZIGB)
	{
		CNxConfig cfg;
		cfg.trans_zigbee(false, m_edit_zigbee_mac, (char*)&sAfn04f25.uPortPara.mac[0]);
		
	}

	// sAccessIP
	strIP.Format("%d.%d.%d.%d", 
		sAfn04f25.sAccess.ip[0],
		sAfn04f25.sAccess.ip[1],
		sAfn04f25.sAccess.ip[2],
		sAfn04f25.sAccess.ip[3]);
	
	m_ip_sAccess.SetWindowText(strIP);

	// usAcsPort
	m_edit_usAcsPort = sAfn04f25.usAcsPort;

	UpdateData(FALSE);
}

//
void CDlgPreAfn04F25_33::SetNewValues()
{
	CString strIP;
	CNxConfig cfg;
	sMcAfn04f25 sAfn04f25;
	int i = 0;

	UpdateData(TRUE);

	sAfn04f25.usID   = m_edit_usID;
	sAfn04f25.ucPort = m_edit_ucPort;

	// eAcsProto
	eProType eProto;
	eProto = (eProType)m_comb_proto.GetCurSel();
	switch (eProto)
	{
	case PROT_GBNX_32:
		sAfn04f25.eAcsProto = MC_ACS_PROT_GBNX_32;
		break;
		
	case RROT_DLT645_97:
		sAfn04f25.eAcsProto = MC_ACS_PROT_DLT645_97;
		break;
		
	case PROT_DLT645_07:
		sAfn04f25.eAcsProto = MC_ACS_PROT_DLT645_07;
		break;
		
	case PROT_MODBUS:
		sAfn04f25.eAcsProto = MC_ACS_PROT_MODBUS;
		
		break;
		
	case PROT_USER:
		sAfn04f25.eAcsProto = MC_ACS_PROT_USER;
		break;
		
	default:
		sAfn04f25.eAcsProto = MC_ACS_PROT_GBNX_32;
		break;
	
	}
	

	// ucaddr
	int len = 0;
	memset(sAfn04f25.ucAddr, 0, 16);
	len = m_edit_ucAddr.GetLength();
	memcpy(sAfn04f25.ucAddr, m_edit_ucAddr.GetBuffer(len), len > 16 ? 16 : len);
	
	// pwd
	memset(sAfn04f25.ucPwd, 0, 6);
	len = m_edit_pwd.GetLength();
	memcpy(sAfn04f25.ucPwd, m_edit_pwd.GetBuffer(len), len > 6 ? 6 : len);


	// eAcsPort
	ePortType ePort;
	ePort =	(ePortType)m_comb_port.GetCurSel();
	switch(ePort)
	{
	case PORT_DC:
		sAfn04f25.eAcsPort = MC_ACS_PORT_DC;
		break;
		
	case PORT_AC:
	    sAfn04f25.eAcsPort = MC_ACS_PORT_AC;
		break;
		
	case PORT_SER:
		{
			sAfn04f25.eAcsPort = MC_ACS_PORT_SER;

			eBaud ebaud;
			ebaud = (eBaud)m_comb_baud.GetCurSel();
			switch (ebaud)
			{
			case INDEX_BAUD_1200:  
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_1200;
				break;
				
			case INDEX_BAUD_2400:
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_2400;
				break;
				
			case INDEX_BAUD_4800:
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_4800;
				break;
				
			case INDEX_BAUD_9600:
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_9600;
				break;
				
			case INDEX_BAUD_19200:
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_19200;
				break;
				
			case INDEX_BAUD_38400:  
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_38400;
				break;
				
			case INDEX_BAUD_76800:
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_76800;
				break;
				
			default:
				sAfn04f25.uPortPara.sSer.eBaud = MC_BAUD_9600;
				break;
			}
						
			// check
			eCheck check_index;
			check_index = (eCheck)m_comb_check.GetCurSel();
			if ( check_index == CHECK_NONE)
			{
				sAfn04f25.uPortPara.sSer.bCheck = FALSE;

			}
			else
			{
				sAfn04f25.uPortPara.sSer.bCheck = TRUE;
				if (check_index == CHECK_ODD)
				{
					sAfn04f25.uPortPara.sSer.bOdd = TRUE;
				}
				else
				{
					sAfn04f25.uPortPara.sSer.bOdd = FALSE;
				}
			}
			
			// databit
			sAfn04f25.uPortPara.sSer.eBit = (eMcSerBit)m_comb_databit.GetCurSel();
		
			// stop
			eStopBit eStop;
			eStop = (eStopBit)m_comb_stop.GetCurSel();
			sAfn04f25.uPortPara.sSer.bStop1 = ((eStop == STOP_1 ) ? TRUE : FALSE) ;
		}
		
		break;
		
	case PORT_ETH:
		{
			sAfn04f25.eAcsPort = MC_ACS_PORT_ETH;
			CString strTmp;
			m_ip_acs.GetWindowText(strIP);
			sAfn04f25.uPortPara.sEth.sAccess.ip[0] = cfg.GetIpNum(strIP, 0);
			sAfn04f25.uPortPara.sEth.sAccess.ip[1] = cfg.GetIpNum(strIP, 1);
			sAfn04f25.uPortPara.sEth.sAccess.ip[2] = cfg.GetIpNum(strIP, 2);
			sAfn04f25.uPortPara.sEth.sAccess.ip[3] = cfg.GetIpNum(strIP, 3);
			
			sAfn04f25.uPortPara.sEth.sAccess.eVersion = MC_IP_V4;
			
			
			sAfn04f25.uPortPara.sEth.usPort = m_edit_acs_port;
		}
	
		break;
		
	case PORT_ZIGB:
		{
			sAfn04f25.eAcsPort = MC_ACS_PORT_ZIGB;
				
			CNxConfig cfg;
			cfg.trans_zigbee(true, m_edit_zigbee_mac, (char*)&sAfn04f25.uPortPara.mac[0]);
		}
		break;
		
	case PORT_USER:
		sAfn04f25.eAcsPort = MC_ACS_PORT_USER;
		break;
		
	default:
		sAfn04f25.eAcsPort = MC_ACS_PORT_SER;
		break;
	}
	
	// sAccessIP
	m_ip_sAccess.GetWindowText(strIP);
	sAfn04f25.sAccess.ip[0] = cfg.GetIpNum(strIP, 0);
	sAfn04f25.sAccess.ip[1] = cfg.GetIpNum(strIP, 1);
	sAfn04f25.sAccess.ip[2] = cfg.GetIpNum(strIP, 2);
	sAfn04f25.sAccess.ip[3] = cfg.GetIpNum(strIP, 3);
	sAfn04f25.sAccess.eVersion = MC_IP_V4;

	// usAcsPort
	sAfn04f25.usAcsPort = m_edit_usAcsPort;
	

	// 将界面上的设置保存起来 到注册表
	if(m_bF25Elec == TRUE)
	{
		cfg.SetPreAfn04F25(&sAfn04f25, TRUE, TRUE);
	}
	else
	{
		cfg.SetPreAfn04F33(&sAfn04f25, TRUE, TRUE);
	}
	
}
