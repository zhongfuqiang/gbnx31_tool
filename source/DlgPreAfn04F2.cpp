// DlgPreAfn04F2.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F2 dialog


CDlgPreAfn04F2::CDlgPreAfn04F2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F2)
	m_edit_total = 0;
	m_edit_index = 0;
	m_edit_apn = _T("");
	m_edit_port_back = 0;
	m_edit_port_main = 0;
	m_edit_pwd = _T("");
	m_edit_usr = _T("");
	m_edit_id = 0;
	m_edit_usPn = 0;
	m_static_pn = _T("");
	//}}AFX_DATA_INIT
	m_index = 0;
	m_totalNum = 0;
	memset(m_sMcMstParaOne, 0, sizeof(m_sMcMstParaOne));


	int i = 0;
	int s, e;
	s = MCMD_AFN_4_F1_CON_UP_CFG;
	e = MCMD_AFN_4_F49_FREZ_TASK_PARA;
	eMcmd eCmd;
	sMcmdInfor cmdinfor;
	eMcErr eRet;
	int j = 0;
	for (i = s; i <= e; i++)
	{
		eCmd = (eMcmd)i;
		eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &cmdinfor);
		if (MC_OK == eRet)
		{
			m_set[j].eCmd = eCmd;
			m_set[j].name.Format("F%-2d %s", eCmd &0xFF, cmdinfor.pName);
			j++;
		}

	}
}


void CDlgPreAfn04F2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F2)
	DDX_Control(pDX, IDC_COMB_CMD, m_cmb_cmd);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_IP_MAIN, m_ip_main);
	DDX_Control(pDX, IDC_IP_BACK, m_ip_back);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_NUM_TOTAL, m_edit_total);
	DDV_MinMaxInt(pDX, m_edit_total, 0, 255);
	DDX_Text(pDX, IDC_EDIT_NUM_TH, m_edit_index);
	DDX_Text(pDX, IDC_EDIT_APN, m_edit_apn);
	DDX_Text(pDX, IDC_EDIT_PORT_BACK, m_edit_port_back);
	DDX_Text(pDX, IDC_EDIT_PORT_MAIN, m_edit_port_main);
	DDX_Text(pDX, IDC_EDIT_PWD, m_edit_pwd);
	DDX_Text(pDX, IDC_EDIT_USR, m_edit_usr);
	DDX_Text(pDX, IDC_EDIT_ID, m_edit_id);
	DDV_MinMaxUInt(pDX, m_edit_id, 0, 255);
	DDX_Text(pDX, IDC_EDIT_PN, m_edit_usPn);
	DDX_Text(pDX, IDC_STATIC_PN, m_static_pn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F2, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F2)
	ON_EN_CHANGE(IDC_EDIT_NUM_TOTAL, OnChangeEditNumTotal)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_EN_CHANGE(IDC_EDIT_ID, OnChangeEditId)
	ON_BN_CLICKED(IDC_RADIO_VALID, OnRadioValid)
	ON_BN_CLICKED(IDC_RADIO_INVALID, OnRadioInvalid)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_MAIN, OnFieldchangedIpMain)
	ON_EN_CHANGE(IDC_EDIT_PORT_MAIN, OnChangeEditPortMain)
	ON_EN_CHANGE(IDC_EDIT_PORT_BACK, OnChangeEditPortBack)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_BACK, OnFieldchangedIpBack)
	ON_EN_CHANGE(IDC_EDIT_APN, OnChangeEditApn)
	ON_EN_CHANGE(IDC_EDIT_USR, OnChangeEditUsr)
	ON_EN_CHANGE(IDC_EDIT_PWD, OnChangeEditPwd)
	ON_CBN_EDITCHANGE(IDC_COMB_CMD, OnEditchangeCombCmd)
	ON_CBN_SELENDOK(IDC_COMB_CMD, OnSelendokCombCmd)
	ON_EN_CHANGE(IDC_EDIT_PN, OnChangeEditPn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
	// TODO: Add extra validation here
	

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F2 message handlers
void CDlgPreAfn04F2::OnOK() 
{
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F2::OnInitDialog() 
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


// 	m_btn_next.SetShade(CShadeButtonST::SHS_METAL,8,50,5,RGB(255,255,55));
// 	m_btn_next.SetIcon(IDI_ICON_R);
// 	m_btn_next.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
// 	m_btn_next.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
// 	
// 	m_btn_pre.SetShade(CShadeButtonST::SHS_METAL,8,50,5,RGB(255,255,55));
// 	m_btn_pre.SetIcon(IDI_ICON_L);
// 	m_btn_pre.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
// 	m_btn_pre.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));


	int i = 0;
	for (i = 0; i < INDEX_AFN_4_MAX; i++)
	{
		m_cmb_cmd.InsertString(i, m_set[i].name);
	}



	GetCurValues();
	((CButton*)GetDlgItem(IDC_RADIO_PAITU))->SetCheck(TRUE);
	GetDlgItem(IDC_RADIO_PAITU)->EnableWindow(FALSE);

	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



// 从注册表中获取已经存在的数据，并将其显示在界面上
void CDlgPreAfn04F2::GetCurValues()
{
	CNxConfig cfg;
	char buf[10240];
	CString strIP;
	CString strTmp;
	


	sMcAfn04f2 *pData;
	pData = (sMcAfn04f2*)buf;
	cfg.GetPreAfn04F2(pData, TRUE);
	
	m_totalNum = pData->ucN;
	int i = 0;
	
	if (m_totalNum == 0)
	{
		EnableCtrls(FALSE);
	}
	else
	{
		EnableCtrls(TRUE);
		
		m_index = 1;

		m_edit_id = pData->sOne[0].ucID;
		m_edit_total = m_totalNum;

		m_edit_index = 1;

		if (pData->sOne[0].bValid == TRUE)
		{
			((CButton*)GetDlgItem(IDC_RADIO_VALID))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_INVALID))->SetCheck(FALSE);

		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_VALID))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_INVALID))->SetCheck(TRUE);
		}

		//main ip
		strIP.Format("%d.%d.%d.%d", pData->sOne[0].sMainIP.ip[0], 
			pData->sOne[0].sMainIP.ip[1], 
			pData->sOne[0].sMainIP.ip[2],
			pData->sOne[0].sMainIP.ip[3]);

		m_ip_main.SetWindowText(strIP);
		//back ip
	
		strIP.Format("%d.%d.%d.%d", pData->sOne[0].sBackIP.ip[0], 
			pData->sOne[0].sBackIP.ip[1], 
			pData->sOne[0].sBackIP.ip[2],
			pData->sOne[0].sBackIP.ip[3]);
		
		m_ip_back.SetWindowText(strIP);

		
		m_edit_port_back = pData->sOne[0].usBackPort;
		m_edit_port_main = pData->sOne[0].usMainPort;

		char buf_apn[18] = {0};
		memcpy(buf_apn, pData->sOne[0].ucascAPN, 16);
		strTmp.Format("%s", buf_apn);
		m_edit_apn = strTmp;

		char buf_usr[36] = {0};
		memcpy(buf_usr, pData->sOne[0].usr, 32);
		strTmp.Format("%s", buf_usr);
		m_edit_usr = strTmp;

		char buf_pwd[36] = {0};
		memcpy(buf_pwd, pData->sOne[0].pwd, 32);
		m_edit_pwd.Format("%s", buf_pwd);
		



			int i = 0;
		
		if(pData->sOne[0].ucNoNum == 1)
		{
			for (i = 0; i < INDEX_AFN_4_MAX; i++)
			{
				if (pData->sOne[0].sCmdPn[0].eCmd == m_set[i].eCmd)
				{
					m_cmb_cmd.SetCurSel(i);
					m_edit_usPn = pData->sOne[0].sCmdPn[0].usPn;
					if (m_edit_usPn == 0)
					{
						m_static_pn = "仅0 集中器";
						((CButton*)GetDlgItem(IDC_EDIT_PN))->EnableWindow(FALSE);
					}
					else
					{
						((CButton*)GetDlgItem(IDC_EDIT_PN))->EnableWindow(TRUE);
						m_static_pn = "1~2040";
					}
				}
			}
		
		}
		




	
		for (i = 0; i < pData->ucN; i++)
		{
			m_sMcMstParaOne[i] = pData->sOne[i];
			strTmp.Format("第%d个", i+1);
			m_tab.InsertItem(i, strTmp);
		}
		



		UpdateData(FALSE);
		


	}
	
}

void CDlgPreAfn04F2::OnChangeEditNumTotal() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	m_totalNum = m_edit_total;

	if (m_edit_total == 0)
	{
		EnableCtrls(FALSE);
	}
	else
	{
		EnableCtrls(TRUE);
	}

	int i = 0;
	CString strValue;
	m_tab.DeleteAllItems();
	for (i = 0; i < m_totalNum; i++)
	{
		strValue.Format("第%d个", i+1);
		m_tab.InsertItem(i, strValue);
	}

}

void CDlgPreAfn04F2::EnableCtrls( BOOL bEnable )
{
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NUM_TH)->EnableWindow(bEnable);
	GetDlgItem(IDC_IP_BACK)->EnableWindow(bEnable);
	GetDlgItem(IDC_IP_MAIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PORT_MAIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PORT_BACK)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_APN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_USR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PWD)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_BTN_NEXT)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_BTN_PRE)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_VALID)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_INVALID)->EnableWindow(bEnable);
//	GetDlgItem(IDC_RADIO_PAITU)->EnableWindow(bEnable);
}

void CDlgPreAfn04F2::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_tab.GetCurSel();
	CString strIP;
	CString strTmp;
	strTmp.Format("%d", i+1);
	((CButton*)GetDlgItem(IDC_EDIT_NUM_TH))->SetWindowText(strTmp);


	m_edit_id = m_sMcMstParaOne[i].ucID;
	m_edit_total = m_totalNum;
	
	m_edit_index = i+1;
	
	if (m_sMcMstParaOne[i].bValid == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO_VALID))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_INVALID))->SetCheck(FALSE);
		
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_VALID))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_INVALID))->SetCheck(TRUE);
	}
	
	//main ip
	strIP.Format("%d.%d.%d.%d", m_sMcMstParaOne[i].sMainIP.ip[0], 
		m_sMcMstParaOne[i].sMainIP.ip[1], 
		m_sMcMstParaOne[i].sMainIP.ip[2],
		m_sMcMstParaOne[i].sMainIP.ip[3]);
	
	m_ip_main.SetWindowText(strIP);
	//back ip
	
	strIP.Format("%d.%d.%d.%d", m_sMcMstParaOne[i].sBackIP.ip[0], 
		m_sMcMstParaOne[i].sBackIP.ip[1], 
		m_sMcMstParaOne[i].sBackIP.ip[2],
		m_sMcMstParaOne[i].sBackIP.ip[3]);
	
	m_ip_back.SetWindowText(strIP);
	
	
	m_edit_port_back = m_sMcMstParaOne[i].usBackPort;
	m_edit_port_main = m_sMcMstParaOne[i].usMainPort;
	
	char buf_apn[18] = {0}; 
	memcpy(buf_apn, m_sMcMstParaOne[i].ucascAPN, 16);
	
	strTmp.Format("%s", buf_apn);
	m_edit_apn = strTmp;
	
	char buf_usr[36] = {0};
	memcpy(buf_usr, m_sMcMstParaOne[i].usr, 32);
	strTmp.Format("%s", buf_usr);
	m_edit_usr = strTmp;
	
	char buf_pwd[36] = {0};
	memcpy(buf_pwd, m_sMcMstParaOne[i].pwd, 32);
	m_edit_pwd.Format("%s", buf_pwd);
	
	int j;
	for (j = 0; j < INDEX_AFN_4_MAX; j++)
	{
		if (m_sMcMstParaOne[i].sCmdPn[0].eCmd == m_set[j].eCmd)
		{
			m_cmb_cmd.SetCurSel(j);
			m_edit_usPn = m_sMcMstParaOne[i].sCmdPn[0].usPn;
			if (m_edit_usPn == 0)
			{
				m_static_pn = "仅0 集中器";
				((CButton*)GetDlgItem(IDC_EDIT_PN))->EnableWindow(FALSE);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_EDIT_PN))->EnableWindow(TRUE);
				m_static_pn = "1~2040";
			}
		}
	}
	
	
	
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgPreAfn04F2::SetNewValues()
{
	UpdateData();

	char buf[10240];

	int i  = 0;
	
	
	sMcAfn04f2 *pData;
	pData = (sMcAfn04f2*)buf;



	pData->ucN = m_edit_total;

	for (i = 0; i < pData->ucN; i++)
	{
		pData->sOne[i] = m_sMcMstParaOne[i];
	}

	
	CNxConfig cfg;
	cfg.SetPreAfn04F2(pData, TRUE, TRUE);
	
	

}

void CDlgPreAfn04F2::OnChangeEditId() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();

	m_sMcMstParaOne[i].ucID = m_edit_id; 
}

void CDlgPreAfn04F2::OnRadioValid() 
{
	// TODO: Add your control notification handler code here
	int i = m_tab.GetCurSel();
	m_sMcMstParaOne[i].bValid = ((CButton*)GetDlgItem(IDC_RADIO_VALID))->GetCheck(); 
}

void CDlgPreAfn04F2::OnRadioInvalid() 
{
	// TODO: Add your control notification handler code here
	int i = m_tab.GetCurSel();
	m_sMcMstParaOne[i].bValid = ((CButton*)GetDlgItem(IDC_RADIO_VALID))->GetCheck(); 
}

void CDlgPreAfn04F2::OnFieldchangedIpMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	CString strIP;
	m_ip_main.GetWindowText(strIP);
	CNxConfig cfg;

	m_sMcMstParaOne[i].sMainIP.ip[0] = cfg.GetIpNum(strIP, 0); 
	m_sMcMstParaOne[i].sMainIP.ip[1] = cfg.GetIpNum(strIP, 1); 
	m_sMcMstParaOne[i].sMainIP.ip[2] = cfg.GetIpNum(strIP, 2); 
	m_sMcMstParaOne[i].sMainIP.ip[3] = cfg.GetIpNum(strIP, 3); 
	*pResult = 0;
}

void CDlgPreAfn04F2::OnChangeEditPortMain() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	m_sMcMstParaOne[i].usMainPort = m_edit_port_main;
	
}

void CDlgPreAfn04F2::OnChangeEditPortBack() 
{
	UpdateData();
	int i = m_tab.GetCurSel();
	m_sMcMstParaOne[i].usBackPort = m_edit_port_back;
	
}

void CDlgPreAfn04F2::OnFieldchangedIpBack(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	CString strIP;
	m_ip_back.GetWindowText(strIP);
	CNxConfig cfg;
	
	m_sMcMstParaOne[i].sBackIP.ip[0] = cfg.GetIpNum(strIP, 0); 
	m_sMcMstParaOne[i].sBackIP.ip[1] = cfg.GetIpNum(strIP, 1); 
	m_sMcMstParaOne[i].sBackIP.ip[2] = cfg.GetIpNum(strIP, 2); 
	m_sMcMstParaOne[i].sBackIP.ip[3] = cfg.GetIpNum(strIP, 3); 
	*pResult = 0;
}

void CDlgPreAfn04F2::OnChangeEditApn() 
{
	UpdateData();
	int i = m_tab.GetCurSel();
	memset(m_sMcMstParaOne[i].ucascAPN, 0, 16);
	memcpy(m_sMcMstParaOne[i].ucascAPN, m_edit_apn.GetBuffer(m_edit_apn.GetLength()), m_edit_apn.GetLength());
	m_edit_apn.ReleaseBuffer();

}

void CDlgPreAfn04F2::OnChangeEditUsr() 
{
	UpdateData();
	int i = m_tab.GetCurSel();
	memset(m_sMcMstParaOne[i].usr, 0, 32);
	memcpy(m_sMcMstParaOne[i].usr, m_edit_usr.GetBuffer(m_edit_usr.GetLength()), m_edit_usr.GetLength());
	m_edit_usr.ReleaseBuffer();
}

void CDlgPreAfn04F2::OnChangeEditPwd() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	memset(m_sMcMstParaOne[i].pwd, 0, 32);
	memcpy(m_sMcMstParaOne[i].pwd, m_edit_pwd.GetBuffer(m_edit_pwd.GetLength()), m_edit_pwd.GetLength());
	m_edit_pwd.ReleaseBuffer();
}

void CDlgPreAfn04F2::OnEditchangeCombCmd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgPreAfn04F2::OnSelendokCombCmd() 
{
	// TODO: Add your control notification handler code here
	int i = m_cmb_cmd.GetCurSel();
	
	eMcmd eCmd;
	eMcErr eRet;
	sMcmdInfor cmdinfor;
	eCmd = m_set[i].eCmd;
	eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &cmdinfor);
	if (eRet == MC_OK)
	{
		if(cmdinfor.ePn == MC_PN_P0)
		{
			m_edit_usPn = 0;
			m_static_pn = "仅0 集中器";
			UpdateData(FALSE);
			((CButton*)GetDlgItem(IDC_EDIT_PN))->EnableWindow(FALSE);
		}
		else
		{
			UpdateData();
			if (m_edit_usPn == 0)
			{
				m_edit_usPn = 1;
			}
			((CButton*)GetDlgItem(IDC_EDIT_PN))->EnableWindow(TRUE);
			m_static_pn = "1~2040";
			UpdateData(FALSE);
		}
	}



	UpdateData();
	i = m_tab.GetCurSel();
	m_sMcMstParaOne[i].ucNoNum = 1;
	m_sMcMstParaOne[i].sCmdPn[0].eCmd = eCmd;
	m_sMcMstParaOne[i].sCmdPn[0].usPn = m_edit_usPn;
}

void CDlgPreAfn04F2::OnChangeEditPn() 
{

	UpdateData();
	int i;
	int j;
	i = m_tab.GetCurSel();
	j = m_cmb_cmd.GetCurSel();

	m_sMcMstParaOne[i].ucNoNum = 1;
	m_sMcMstParaOne[i].sCmdPn[0].eCmd = m_set[j].eCmd;
	m_sMcMstParaOne[i].sCmdPn[0].usPn = m_edit_usPn;
}
