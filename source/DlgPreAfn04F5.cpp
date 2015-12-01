// DlgPreAfn04F5.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F5 dialog

CDlgPreAfn04F5::CDlgPreAfn04F5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F5)
	m_edit_usPort = 0;
	m_edit_usDelgPort = 0;
	//}}AFX_DATA_INIT
	
	// eDelegate
	m_strDelegate[DELG_NULL] = "不使用";
	m_strDelegate[DELG_HTTP] = "http";
	m_strDelegate[DELG_SOCK4] = "sock4";
	m_strDelegate[DELG_SOCK5] = "sock5";

	m_strDelgLink[DELK_ANYONE] = "不需要验证";
	m_strDelgLink[DELK_USRPWD] = "需要用户名和密码";
}


void CDlgPreAfn04F5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F5)
	DDX_Control(pDX, IDC_IP_sMask, m_ip_sMask);
	DDX_Control(pDX, IDC_IP_sGateIp, m_ip_sGateIp);
	DDX_Control(pDX, IDC_IP_sDelgIp, m_ip_sDelgIp);
	DDX_Control(pDX, IDC_IP_sConIp, m_ip_sConIP);
	DDX_Control(pDX, IDC_COMBO_eDelegate, m_comb_eDelegate);
	DDX_Control(pDX, IDC_EDIT_ucDlegPwd, m_edit_pwd);
	DDX_Control(pDX, IDC_EDIT_ucDlegUsr, m_edit_usr);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_usPort, m_edit_usPort);
	DDX_Text(pDX, IDC_EDIT_usDelgPort, m_edit_usDelgPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F5, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F5)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_CBN_SELENDOK(IDC_COMBO_eDelegate, OnSelendokCOMBOeDelegate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F5 message handlers

BOOL CDlgPreAfn04F5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init ctrls
	int i = 0;
	for (i = 0; i < DELG_MAX; i++)
	{
		m_comb_eDelegate.InsertString(i, m_strDelegate[i]);
	}

	m_comb_eDelegate.SetCurSel(0);



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

void CDlgPreAfn04F5::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

// 需要
void CDlgPreAfn04F5::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_edit_usr.EnableWindow(TRUE);
	m_edit_pwd.EnableWindow(TRUE);
}

// 不需要
void CDlgPreAfn04F5::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_edit_usr.EnableWindow(FALSE);
	m_edit_pwd.EnableWindow(FALSE);
	m_edit_usr.SetWindowText("");
	m_edit_pwd.SetWindowText("");
}

void CDlgPreAfn04F5::OnSelendokCOMBOeDelegate() 
{
	// TODO: Add your control notification handler code here
	int nSel = 0;
	nSel = m_comb_eDelegate.GetCurSel();
	if (DELG_NULL == nSel)
	{
		// 不使用代理禁用代理相关控件
		m_ip_sDelgIp.EnableWindow(FALSE);
		m_edit_pwd.EnableWindow(FALSE);
		m_edit_usr.EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_EDIT_usDelgPort))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO1))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO2))->EnableWindow(FALSE);


	}
	else
	{
		m_ip_sDelgIp.EnableWindow(TRUE);
		m_edit_usr.EnableWindow(TRUE);
		m_edit_pwd.EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_EDIT_usDelgPort))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO2))->EnableWindow(TRUE);

		BOOL bNeed;
		bNeed = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
		
		if (bNeed == TRUE)
		{
			m_edit_pwd.EnableWindow(TRUE);
			m_edit_usr.EnableWindow(TRUE);
			
		}
		else
		{
			m_edit_pwd.EnableWindow(FALSE);
			m_edit_usr.EnableWindow(FALSE);
		
		}


	}



}

void CDlgPreAfn04F5::SetNewValues()
{
	UpdateData(TRUE);
	CNxConfig cfg;
	sMcAfn04f5 sAfn04f5;
	
	
	
	sAfn04f5.usPort     = m_edit_usPort;
	sAfn04f5.usDelgPort = m_edit_usDelgPort;
	
	CString strIP;
	m_ip_sConIP.GetWindowText(strIP);
	sAfn04f5.sConIp.ip[0] = cfg.GetIpNum(strIP, 0);
	sAfn04f5.sConIp.ip[1] = cfg.GetIpNum(strIP, 1);
	sAfn04f5.sConIp.ip[2] = cfg.GetIpNum(strIP, 2);
	sAfn04f5.sConIp.ip[3] = cfg.GetIpNum(strIP, 3);
	
	// smask	
	m_ip_sMask.GetWindowText(strIP);
	sAfn04f5.sMask.ip[0] = cfg.GetIpNum(strIP, 0);
	sAfn04f5.sMask.ip[1] = cfg.GetIpNum(strIP, 1);
	sAfn04f5.sMask.ip[2] = cfg.GetIpNum(strIP, 2);
	sAfn04f5.sMask.ip[3] = cfg.GetIpNum(strIP, 3);
	
	// sGateIp
	m_ip_sGateIp.GetWindowText(strIP);
	sAfn04f5.sGateIp.ip[0] = cfg.GetIpNum(strIP, 0);
	sAfn04f5.sGateIp.ip[1] = cfg.GetIpNum(strIP, 1);
	sAfn04f5.sGateIp.ip[2] = cfg.GetIpNum(strIP, 2);
	sAfn04f5.sGateIp.ip[3] = cfg.GetIpNum(strIP, 3);
	
	// sDelgIp
	m_ip_sDelgIp.GetWindowText(strIP);
	sAfn04f5.sDelgIp.ip[0] = cfg.GetIpNum(strIP, 0);
	sAfn04f5.sDelgIp.ip[1] = cfg.GetIpNum(strIP, 1);
	sAfn04f5.sDelgIp.ip[2] = cfg.GetIpNum(strIP, 2);
	sAfn04f5.sDelgIp.ip[3] = cfg.GetIpNum(strIP, 3);
	
	// eDelegate
	eDelegate_index eDelegate;
	eDelegate =	(eDelegate_index)m_comb_eDelegate.GetCurSel();
	switch (eDelegate)
	{
	case DELG_NULL:
		sAfn04f5.eDelegate = MC_DELG_NULL;
		break;
		
	case DELG_HTTP:
		sAfn04f5.eDelegate = MC_DELG_HTTP;
		break;
		
	case DELG_SOCK4:
		sAfn04f5.eDelegate = MC_DELG_SOCK4;
		break;
		
	case DELG_SOCK5:
		sAfn04f5.eDelegate = MC_DELG_SOCK5;
		break;
		
	default:
		sAfn04f5.eDelegate = MC_DELG_HTTP;
		break;		
	}
	

	BOOL bNeed;
	bNeed = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();

	if (bNeed == TRUE)
	{
		sAfn04f5.eDelgLink = MC_DELK_USRPWD;
	
	}
	else
	{
	     sAfn04f5.eDelgLink = MC_DELK_ANYONE;
	}
	
	CString strValue;
	m_edit_usr.GetWindowText(strValue);
	
	sAfn04f5.ucDlegUsrLen = strValue.GetLength();
	sAfn04f5.bDlegUsr = sAfn04f5.ucDlegUsrLen > 0 ? TRUE :FALSE;
	memcpy(sAfn04f5.ucDlegUsr, strValue.GetBuffer(sAfn04f5.ucDlegUsrLen), sAfn04f5.ucDlegUsrLen);
	strValue.ReleaseBuffer();
	
	m_edit_pwd.GetWindowText(strValue);
	sAfn04f5.ucDlegPwdLen = strValue.GetLength();
	sAfn04f5.bDlegPwd = sAfn04f5.ucDlegPwdLen > 0 ? TRUE :FALSE;
	memcpy(sAfn04f5.ucDlegPwd, strValue.GetBuffer(sAfn04f5.ucDlegPwdLen), sAfn04f5.ucDlegPwdLen);
	strValue.ReleaseBuffer();

	cfg.SetPreAfn04F5(&sAfn04f5, TRUE, TRUE);
}

void CDlgPreAfn04F5::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f5 sAfn04f5;

	cfg.GetPreAfn04F5(&sAfn04f5, TRUE);

	m_edit_usPort = sAfn04f5.usPort;
	m_edit_usDelgPort = sAfn04f5.usDelgPort;
	
	CString strIP;
	strIP.Format("%d.%d.%d.%d", 
		sAfn04f5.sConIp.ip[0],
		sAfn04f5.sConIp.ip[1],
		sAfn04f5.sConIp.ip[2],
		sAfn04f5.sConIp.ip[3]);

	m_ip_sConIP.SetWindowText(strIP);


	// smask
	strIP.Format("%d.%d.%d.%d", 
		sAfn04f5.sMask.ip[0],
		sAfn04f5.sMask.ip[1],
		sAfn04f5.sMask.ip[2],
		sAfn04f5.sMask.ip[3]);
	
	m_ip_sMask.SetWindowText(strIP);

	// sGateIp
	strIP.Format("%d.%d.%d.%d", 
		sAfn04f5.sGateIp.ip[0],
		sAfn04f5.sGateIp.ip[1],
		sAfn04f5.sGateIp.ip[2],
		sAfn04f5.sGateIp.ip[3]);
	
	m_ip_sGateIp.SetWindowText(strIP);
	
	// sDelgIp
	strIP.Format("%d.%d.%d.%d", 
		sAfn04f5.sDelgIp.ip[0],
		sAfn04f5.sDelgIp.ip[1],
		sAfn04f5.sDelgIp.ip[2],
		sAfn04f5.sDelgIp.ip[3]);
	
	m_ip_sDelgIp.SetWindowText(strIP);
	
	// eDelegate
	eDelegate_index eDelegate;
	switch (sAfn04f5.eDelegate)
	{
	case MC_DELG_NULL:
		eDelegate = DELG_NULL;
		break;

	case MC_DELG_HTTP:
		eDelegate = DELG_HTTP;
		break;

	case MC_DELG_SOCK4:
		eDelegate = DELG_SOCK4;
		break;

	case MC_DELG_SOCK5:
		eDelegate = DELG_SOCK5;
		break;

	default:
		eDelegate = DELG_NULL;
		break;		
	}

	m_comb_eDelegate.SetCurSel(eDelegate);
	
	if (sAfn04f5.eDelgLink == MC_DELK_USRPWD)
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
		m_edit_pwd.EnableWindow(TRUE);
		m_edit_usr.EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
		m_edit_pwd.EnableWindow(FALSE);
		m_edit_usr.EnableWindow(FALSE);

	}

	char usr[21] = {0};
	char pwd[21] = {0};

	memcpy(usr, sAfn04f5.ucDlegUsr, sAfn04f5.ucDlegUsrLen);
	memcpy(pwd, sAfn04f5.ucDlegPwd, sAfn04f5.ucDlegPwdLen);
	
	CString strValue;
	strValue.Format("%s", usr);
	m_edit_usr.SetWindowText(strValue);

	strValue.Format("%s", pwd);
	m_edit_pwd.SetWindowText(strValue);

	OnSelendokCOMBOeDelegate() ;
	UpdateData(FALSE);
}