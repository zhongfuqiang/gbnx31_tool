// DlgPreAfn04F17.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F17.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F17 dialog


CDlgPreAfn04F17::CDlgPreAfn04F17(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F17::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F17)
	m_edit_heart_beat = 0;
	m_edit_resent_times = 0;
	m_edit_sUpAddr_ConAddr = 0;
	m_edit_sUpAddr_RegCode = _T("");
	m_edit_sUpAddr_TerAddr = 0;
	m_edit_wait_timeout = 0;
	m_edit_ucDlegPwd = _T("");
	m_edit_ucDlegUsr = _T("");
	m_edit_ucDownPort = 0;
	m_edit_ucPermitDelayM = 0;
	m_edit_usListenPort = 0;
	m_edit_usDelgPort = 0;
	//}}AFX_DATA_INIT
	
	m_strUpPara[TUPP_DEL] = "删除";
	m_strUpPara[TUPP_SER] = "串口";
	m_strUpPara[TUPP_ETH] = "以太网";

	m_strDelegate[INDEX_DELG_NULL] = "不使用";
	m_strDelegate[INDEX_DELG_HTTP] = "http";
	m_strDelegate[INDEX_DELG_SOCK4] = "sock4";
	m_strDelegate[INDEX_DELG_SOCK5] = "sock5";
}


void CDlgPreAfn04F17::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F17)
	DDX_Control(pDX, IDC_IP_sUpMask, m_ip_sUpMask);
	DDX_Control(pDX, IDC_IP_sUpIp, m_ip_sUpIp);
	DDX_Control(pDX, IDC_IP_sGateIp, m_ip_sGateIp);
	DDX_Control(pDX, IDC_IP_sDelgIp, m_ip_sDelgIp);
	DDX_Control(pDX, IDC_COMBO_eUpPara, m_cmb_eUpPara);
	DDX_Control(pDX, IDC_COMBO_eDelegate, m_cmb_eDelegate);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_HEART_BEAT, m_edit_heart_beat);
	DDV_MinMaxUInt(pDX, m_edit_heart_beat, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RESENDTIMES, m_edit_resent_times);
	DDV_MinMaxUInt(pDX, m_edit_resent_times, 0, 3);
	DDX_Text(pDX, IDC_EDIT_sUpAddr_ConAddr, m_edit_sUpAddr_ConAddr);
	DDV_MinMaxUInt(pDX, m_edit_sUpAddr_ConAddr, 0, 127);
	DDX_Text(pDX, IDC_EDIT_sUpAddr_RegCode, m_edit_sUpAddr_RegCode);
	DDX_Text(pDX, IDC_EDIT_sUpAddr_TerAddr, m_edit_sUpAddr_TerAddr);
	DDX_Text(pDX, IDC_EDIT_TM_WAIT_TIMEOUT, m_edit_wait_timeout);
	DDV_MinMaxUInt(pDX, m_edit_wait_timeout, 0, 255);
	DDX_Text(pDX, IDC_EDIT_ucDlegPwd, m_edit_ucDlegPwd);
	DDX_Text(pDX, IDC_EDIT_ucDlegUsr, m_edit_ucDlegUsr);
	DDX_Text(pDX, IDC_EDIT_ucDownPort, m_edit_ucDownPort);
	DDV_MinMaxUInt(pDX, m_edit_ucDownPort, 0, 255);
	DDX_Text(pDX, IDC_EDIT_ucPermitDelayM, m_edit_ucPermitDelayM);
	DDV_MinMaxUInt(pDX, m_edit_ucPermitDelayM, 0, 255);
	DDX_Text(pDX, IDC_EDIT_usListenPort, m_edit_usListenPort);
	DDV_MinMaxUInt(pDX, m_edit_usListenPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_usDelgPort, m_edit_usDelgPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F17, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F17)
	ON_EN_CHANGE(IDC_EDIT_ucDownPort, OnChangeEDITucDownPort)
	ON_EN_CHANGE(IDC_EDIT_sUpAddr_ConAddr, OnChangeEDITsUpAddrConAddr)
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()
	
	/////////////////////////////////////////////////////////////////////////////
	// CDlgPreAfn04F17 message handlers
	
	void CDlgPreAfn04F17::OnOK() 
{
	// TODO: Add extra validation here
	
	
	
	
	SetNewValues();
	
	
	
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F17::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btn_ok.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_ok.SetIcon(IDI_ICON_RIGHT);
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	m_btn_no.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_no.SetIcon(IDI_ICON_X);
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	int i = 0;
	for (i = 0; i < TUPP_MAX; i++)
	{
		m_cmb_eUpPara.InsertString(i, m_strUpPara[i]);

	}

	for (i = 0; i < INDEX_DELG_MAX; i++)
	{
		m_cmb_eDelegate.InsertString(i, m_strDelegate[i]);
	}


	GetCurValues();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F17::OnChangeEDITucDownPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CDlgPreAfn04F17::OnChangeEDITsUpAddrConAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgPreAfn04F17::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f17 sData;
	cfg.GetPreAfn04F17(&sData, TRUE);
	
	m_edit_ucDownPort    = sData.ucDownPort;
	m_edit_usListenPort  = sData.usListenPort;
	
	UINT8 acRegionCode[7] = {0};
	memcpy(acRegionCode, sData.sUpAddr.acRegionCode, 6);
	m_edit_sUpAddr_RegCode.Format("%s", acRegionCode);
	
	UINT8 ucDlegUsr[22] = {0};
	memcpy(ucDlegUsr, sData.ucDlegUsr, sData.ucDlegUsrLen);
	m_edit_ucDlegUsr.Format("%s", ucDlegUsr);

	UINT8 ucDlegPwd[22] = {0};
	memcpy(ucDlegPwd, sData.ucDlegPwd, sData.ucDlegPwdLen);
	m_edit_ucDlegPwd.Format("%s", ucDlegPwd);


	
	

	m_edit_sUpAddr_TerAddr = sData.sUpAddr.ulConAddress;
	m_edit_sUpAddr_ConAddr = sData.sUpAddr.ucMstAddress;

	if(sData.sUpAddr.bTeam == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO_sUpAddr_Team_Yes))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_sUpAddr_team_no))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_sUpAddr_Team_Yes))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_sUpAddr_team_no))->SetCheck(TRUE);
	}


	CString strIp;
	strIp.Format("%d.%d.%d.%d", 
	              sData.sUpIp.ip[0],
				  sData.sUpIp.ip[1],
				  sData.sUpIp.ip[2],
				  sData.sUpIp.ip[3]);

	m_ip_sUpIp.SetWindowText(strIp);


	strIp.Format("%d.%d.%d.%d", 
		sData.sUpMask.ip[0],
		sData.sUpMask.ip[1],
		sData.sUpMask.ip[2],
		sData.sUpMask.ip[3]);
	
	m_ip_sUpMask.SetWindowText(strIp);

	strIp.Format("%d.%d.%d.%d", 
		sData.sGateIp.ip[0],
		sData.sGateIp.ip[1],
		sData.sGateIp.ip[2],
		sData.sGateIp.ip[3]);
	
	m_ip_sGateIp.SetWindowText(strIp);
	
	strIp.Format("%d.%d.%d.%d", 
		sData.sDelgIp.ip[0],
		sData.sDelgIp.ip[1],
		sData.sDelgIp.ip[2],
		sData.sDelgIp.ip[3]);
	
	m_ip_sDelgIp.SetWindowText(strIp);

	
	//m_edit_ucDlegPwd


	eMcUpPara_index index_UpPara;
	switch (sData.eUpPara)
	{
	case MC_TUPP_DEL:
		index_UpPara = TUPP_DEL;
		break;

	case MC_TUPP_SER:
		index_UpPara = TUPP_SER;
		break;

	case MC_TUPP_ETH:
		index_UpPara = TUPP_ETH;
		break;


	default:
		index_UpPara = TUPP_SER;
		break;
	}
	
	m_cmb_eUpPara.SetCurSel(index_UpPara);


	index_eDelegate eDelegate;
	switch (sData.eDelegate)
	{
	case MC_DELG_NULL:
		eDelegate = INDEX_DELG_NULL;
		break;
		
	case MC_DELG_HTTP:
		eDelegate = INDEX_DELG_HTTP;
		break;
		
	case MC_DELG_SOCK4:
		eDelegate = INDEX_DELG_SOCK4;
		break;
		
	case MC_DELG_SOCK5:
		eDelegate = INDEX_DELG_SOCK5;
		break;
		
	default:
		eDelegate = INDEX_DELG_NULL;
		break;		
	}
	
	m_cmb_eDelegate.SetCurSel(eDelegate);

	
	if (sData.eDelgLink == MC_DELK_USRPWD)
	{
		((CButton*)GetDlgItem(IDC_RADIO_eDelgLink_yes))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_eDelgLink_NO))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_eDelgLink_yes))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_eDelgLink_NO))->SetCheck(TRUE);
	}
	
	m_edit_usDelgPort = sData.usDelgPort;
	m_edit_heart_beat = sData.ucHeartBeat;
	m_edit_resent_times = sData.ucReSendTimes;
	m_edit_wait_timeout = sData.usWaitTimeoutS;
	m_edit_ucPermitDelayM = sData.ucPermitDelayM;
	
	if (sData.bPermitRt == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO_ASK1_PERMIT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_ASK1_DENY))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_ASK1_PERMIT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_ASK1_DENY))->SetCheck(TRUE);
	}

	
	if (sData.bPermitTk == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO_ASK2_PERMIT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_ASK2_DENY))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_ASK2_PERMIT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_ASK2_DENY))->SetCheck(TRUE);
	}
	
	if (sData.bPermitEv == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO_ASK3_PERMIT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_ASK3_DENY))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_ASK3_PERMIT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_ASK3_DENY))->SetCheck(TRUE);
	}
	
	
	UpdateData(FALSE);
}

void CDlgPreAfn04F17::SetNewValues()
{
	
	UpdateData();
	CNxConfig cfg;
	sMcAfn04f17 sData;
	CString strValue;
	int len = 0;
	int i = 0;
	
	sData.ucDownPort  = m_edit_ucDownPort;
	sData.usListenPort= m_edit_usListenPort;

	// regcode
	m_edit_sUpAddr_RegCode;		
	len = m_edit_sUpAddr_RegCode.GetLength();
	
	// 后面补0
	if (len < 6)
	{
		for (i = 0; i < 6-len; i++)
		{
			m_edit_sUpAddr_RegCode += "0";
		}
	}

	memcpy(sData.sUpAddr.acRegionCode, m_edit_sUpAddr_RegCode.GetBuffer(6), 6);
	m_edit_sUpAddr_RegCode.ReleaseBuffer();

	// DlegUsr
	len = m_edit_ucDlegUsr.GetLength();
	len = len > 20 ? 20 :len;
	sData.ucDlegUsrLen = len;
	memcpy(sData.ucDlegUsr, m_edit_ucDlegUsr.GetBuffer(len), len);
	m_edit_ucDlegUsr.ReleaseBuffer();

	// pwd
	len = m_edit_ucDlegPwd.GetLength();
	len = len > 20 ? 20:len;
	sData.ucDlegPwdLen = len;

	memcpy(sData.ucDlegPwd, m_edit_ucDlegPwd.GetBuffer(len), len);
	m_edit_ucDlegPwd.ReleaseBuffer();

	

	sData.sUpAddr.ulConAddress = m_edit_sUpAddr_TerAddr;
	sData.sUpAddr.ucMstAddress = m_edit_sUpAddr_ConAddr;

	BOOL bCheck;
	sData.sUpAddr.bTeam = ((CButton*)GetDlgItem(IDC_RADIO_sUpAddr_Team_Yes))->GetCheck();
	


	CString strIp;
	m_ip_sUpIp.GetWindowText(strIp);
	sData.sUpIp.ip[0] = cfg.GetIpNum(strIp, 0);
	sData.sUpIp.ip[1] = cfg.GetIpNum(strIp, 1);
	sData.sUpIp.ip[2] = cfg.GetIpNum(strIp, 2);
	sData.sUpIp.ip[3] = cfg.GetIpNum(strIp, 3);
	
	m_ip_sUpMask.GetWindowText(strIp);
	sData.sUpMask.ip[0] = cfg.GetIpNum(strIp, 0);
	sData.sUpMask.ip[1] = cfg.GetIpNum(strIp, 1);
	sData.sUpMask.ip[2] = cfg.GetIpNum(strIp, 2);
	sData.sUpMask.ip[3] = cfg.GetIpNum(strIp, 3);

	
	m_ip_sGateIp.GetWindowText(strIp);
	sData.sGateIp.ip[0] = cfg.GetIpNum(strIp, 0);
	sData.sGateIp.ip[1] = cfg.GetIpNum(strIp, 1);
	sData.sGateIp.ip[2] = cfg.GetIpNum(strIp, 2);
	sData.sGateIp.ip[3] = cfg.GetIpNum(strIp, 3);

	m_ip_sDelgIp.GetWindowText(strIp);
	sData.sDelgIp.ip[0] = cfg.GetIpNum(strIp, 0);
	sData.sDelgIp.ip[1] = cfg.GetIpNum(strIp, 1);
	sData.sDelgIp.ip[2] = cfg.GetIpNum(strIp, 2);
	sData.sDelgIp.ip[3] = cfg.GetIpNum(strIp, 3);
	
	//m_edit_ucDlegPwd
	
	
	eMcUpPara_index index_UpPara = 	(eMcUpPara_index)m_cmb_eUpPara.GetCurSel();;
	
	switch (index_UpPara)
	{
	case TUPP_DEL:
		sData.eUpPara = MC_TUPP_DEL;
		break;
		
	case TUPP_SER:
		sData.eUpPara = MC_TUPP_SER;
		break;
		
	case TUPP_ETH:
		sData.eUpPara = MC_TUPP_ETH;
		break;
		
	default:
		sData.eUpPara = MC_TUPP_DEL;
		break;
	}

	index_eDelegate eDelegate = (index_eDelegate)m_cmb_eDelegate.GetCurSel();;
	switch (eDelegate)
	{
	case INDEX_DELG_NULL:
		sData.eDelegate = MC_DELG_NULL;
		break;
		
	case INDEX_DELG_HTTP:
		sData.eDelegate = MC_DELG_HTTP;
		break;
		
	case INDEX_DELG_SOCK4:
		sData.eDelegate = MC_DELG_SOCK4;
		break;
		
	case INDEX_DELG_SOCK5:
		sData.eDelegate = MC_DELG_SOCK5;
		break;
		
	default:
		sData.eDelegate = MC_DELG_HTTP;
		break;		
	}
	
	

	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_eDelgLink_yes))->GetCheck();
	if (bCheck == TRUE)
	{
		sData.eDelgLink = MC_DELK_USRPWD;
	}
	else
	{
		sData.eDelgLink = MC_DELK_ANYONE;
	}
	

	sData.usDelgPort     = m_edit_usDelgPort;
	sData.ucHeartBeat    = m_edit_heart_beat;
	sData.ucReSendTimes  =m_edit_resent_times;
	sData.usWaitTimeoutS =m_edit_wait_timeout;
	sData.ucPermitDelayM =m_edit_ucPermitDelayM;

	sData.bPermitRt = ((CButton*)GetDlgItem(IDC_RADIO_ASK1_PERMIT))->GetCheck();
	sData.bPermitTk = ((CButton*)GetDlgItem(IDC_RADIO_ASK2_PERMIT))->GetCheck();
	sData.bPermitEv = ((CButton*)GetDlgItem(IDC_RADIO_ASK3_PERMIT))->GetCheck();
	
	cfg.SetPreAfn04F17(&sData, TRUE, TRUE);
}
