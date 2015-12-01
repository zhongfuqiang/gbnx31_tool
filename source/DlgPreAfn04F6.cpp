// DlgPreAfn04F6.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F6 dialog


CDlgPreAfn04F6::CDlgPreAfn04F6(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F6)
	m_edit_ucN = 0;
	m_edit_index = 0;
	m_edit_RegionCode = _T("");
	m_edit_ucPeriod = 0;
	m_edit_ucRetry = 0;
	m_edit_ucWaitC = 0;
	m_edit_ucWaitP = 0;
	m_edit_ulConAddr = 0;
	m_edit_usPort = 0;
	//}}AFX_DATA_INIT


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
	
	// casc name
	m_NameCasc[CASC_NULL] = "不启用";
	m_NameCasc[CASC_RS485] = "串口";
	m_NameCasc[CASC_ETH] = "以太网";


	memset(m_sMcascAddr, 0, sizeof(sMcascAddr)*3);
	

}


void CDlgPreAfn04F6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F6)
	DDX_Control(pDX, IDC_TAB_INDEX, m_tab);
	DDX_Control(pDX, IDC_IP_sIp, m_ip_sIp);
	DDX_Control(pDX, IDC_COMB_STOP, m_cmb_stop);
	DDX_Control(pDX, IDC_COMB_DATABIT, m_cmb_databit);
	DDX_Control(pDX, IDC_COMB_CHECK, m_cmb_check);
	DDX_Control(pDX, IDC_COMB_BAUD, m_cmb_baud);
	DDX_Control(pDX, IDC_STATIC_INDEX, m_static_index);
	DDX_Control(pDX, IDC_CMB_eType, m_cmb_eType);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_ucN, m_edit_ucN);
	DDX_Text(pDX, IDC_EDIT_acRegionCode, m_edit_RegionCode);
	DDX_Text(pDX, IDC_EDIT_ucPeriod, m_edit_ucPeriod);
	DDX_Text(pDX, IDC_EDIT_ucReTry, m_edit_ucRetry);
	DDX_Text(pDX, IDC_EDIT_ucWaitC, m_edit_ucWaitC);
	DDX_Text(pDX, IDC_EDIT_ucWaitP, m_edit_ucWaitP);
	DDX_Text(pDX, IDC_EDIT_ulConAddr, m_edit_ulConAddr);
	DDX_Text(pDX, IDC_EDIT_usPort, m_edit_usPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F6, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F6)
	ON_EN_CHANGE(IDC_EDIT_ucN, OnChangeEDITucN)
	ON_BN_CLICKED(IDC_RADIO_bCasc_yes, OnRADIObCascyes)
	ON_BN_CLICKED(IDC_RADIO_bCasc_ed, OnRADIObCasced)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_INDEX, OnSelchangeTabIndex)
	ON_EN_CHANGE(IDC_EDIT_acRegionCode, OnChangeEDITacRegionCode)
	ON_EN_CHANGE(IDC_EDIT_ulConAddr, OnChangeEDITulConAddr)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_sIp, OnFieldchangedIPsIp)
	ON_EN_CHANGE(IDC_EDIT_usPort, OnChangeEDITusPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F6 message handlers

void CDlgPreAfn04F6::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F6::OnInitDialog() 
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
	// baud 
	for (i = 0; i < BAUD_NUM_MAX; i++)
	{
		m_cmb_baud.InsertString(i, m_BaudName[i]);
	}
	
	m_cmb_baud.SetCurSel(INDEX_BAUD_9600);
	
	// check
	for (i = 0; i < CHECK_NUM_MAX; i++)
	{
		m_cmb_check.InsertString(i, m_checkName[i]);
	}
	
	m_cmb_check.SetCurSel(CHECK_NONE);
	
	// stop
	for (i = 0; i < STOP_NUM_MAX; i++)
	{
		m_cmb_stop.InsertString(i, m_stopName[i]);
	}
	
	m_cmb_stop.SetCurSel(0);
	
	// data bit
	for (i = 0; i < DBIT_NUM_MAX; i++)
	{
		m_cmb_databit.InsertString(i, m_DBitName[i]);
	}
	
	m_cmb_databit.SetCurSel(DBIT_5);

	for (i = 0; i < CASC_MAX; i++)
	{
		m_cmb_eType.InsertString(i, m_NameCasc[i]);
	}

	GetCurValues();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F6::OnChangeEDITucN() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int nMax = 0;
	int n = m_edit_ucN;
	BOOL bCasc = FALSE;  // 是级联方吗

	bCasc = ((CButton*)GetDlgItem(IDC_RADIO_bCasc_yes))->GetCheck();

	if (bCasc == TRUE)
	{
		nMax = 3;
		((CButton*)GetDlgItem(IDC_EDIT_ucN))->EnableWindow(TRUE); 
	}
	else
	{
    	nMax = 1;
		//((CButton*)GetDlgItem(IDC_EDIT_ucN))->EnableWindow(FALSE);
	}



	
	//int i ;
	CString strIndex;
	
	if (n == 0)
	{
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(FALSE);
	}
	else if (n == 1)
	{
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(TRUE);
	}
	else if(n == 2)
	{
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(TRUE);

	}
	else if(n == 3)
	{
		
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(TRUE);

	}
	else
	{
		
			MessageBox("参数越界", "提示", MB_OK|MB_ICONERROR);
			m_edit_ucN = 3;
			UpdateData(FALSE);
			return;
	}
	

	int i = 0;
	CString strText;
	m_tab.DeleteAllItems();
	for (i = 0; i < n; i++)
	{
		strText.Format("第%d个参数", i+1);
		m_tab.InsertItem(i, strText);
	}

	if (n == 0)
	{
		m_tab.ShowWindow(SW_HIDE);
	}
	else
	{
		m_tab.ShowWindow(SW_SHOW);
	}



	//m_slider_con.SetRange(0, m_edit_ucN, TRUE);

	
}






void CDlgPreAfn04F6::OnChangeEditIndex() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgPreAfn04F6::GetCurValues()
{
	CNxConfig cfg;
	
	UINT8 buf[512] = {0};
	sMcAfn04f6 * pData = (sMcAfn04f6*)buf;
	
	cfg.GetPreAfn04F6(pData, TRUE);
	
	if (pData->bCasc == TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO_bCasc_yes))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_bCasc_ed))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_STATIC_CON_PARA))->SetWindowText("0~3");
		((CButton*)GetDlgItem(IDC_EDIT_ucN))->EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_bCasc_yes))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_bCasc_ed))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_STATIC_CON_PARA))->SetWindowText("仅1");
		m_edit_ucN = 1;
		m_tab.DeleteAllItems();
		m_tab.InsertItem(0, "第1个参数");
		((CButton*)GetDlgItem(IDC_EDIT_ucN))->EnableWindow(FALSE);
	}
	
	eCascType eCase;
	switch (pData->eType)
	{
	case MC_CASC_NULL:
		eCase = CASC_NULL;
		break;

	case MC_CASC_RS485:
		eCase = CASC_RS485;
		break;

	case MC_CASC_ETH:
		eCase = CASC_ETH;
		break;
	default:
		break;
	}

	m_cmb_eType.SetCurSel(eCase);


	// eBaud
	eBaud ebaud;
	
	switch (pData->sSer.eBaud)
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
	
	m_cmb_baud.SetCurSel(ebaud);
	
	// check
	eCheck check_index;
	
	if (pData->sSer.bCheck == TRUE)
	{
		check_index = pData->sSer.bOdd ? CHECK_ODD : CHECK_EVEN;
	}
	else
	{
		check_index = CHECK_NONE;
	}
	
	m_cmb_check.SetCurSel(check_index);
	
	
	// databit
	eDataBit eDatabit;
	eDatabit = (eDataBit)pData->sSer.eBit;
	m_cmb_databit.SetCurSel(eDatabit);
	
	// stop
	eStopBit eStop;
	eStop = pData->sSer.bStop1 == TRUE ? STOP_1:STOP_2;
	m_cmb_stop.SetCurSel(eStop);

	m_edit_ucN = pData->ucN;
	m_edit_ucPeriod = pData->ucPeriod;

	m_edit_ucRetry = pData->ucReTry;
	m_edit_ucWaitC = pData->ucWaitC;
	m_edit_ucWaitP = pData->ucWaitP;


	if (pData->ucN == 0)
	{
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(FALSE);
	}
	else if (pData->ucN == 1)
	{
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(TRUE);
	}
	else if(pData->ucN == 2)
	{
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(TRUE);
		
	}
	else if(pData->ucN == 3)
	{
		
		(CButton*)GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
		
		(CButton*)GetDlgItem(IDC_EDIT_acRegionCode)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_ulConAddr)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_IP_sIp)->EnableWindow(TRUE);
		(CButton*)GetDlgItem(IDC_EDIT_usPort)->EnableWindow(TRUE);
		
	}

	if (pData->ucN != 0)
	{
		
		char buf[8] = {0};
		memcpy(buf, pData->sOne[0].acRegionCode, 6);
		CString strValue;
		m_edit_RegionCode.Format("%s", buf);

		m_edit_usPort = pData->sOne[0].usPort;
		m_edit_ulConAddr = pData->sOne[0].ulConAddr;
	
		strValue.Format("%d.%d.%d.%d", pData->sOne[0].sIp.ip[0], 
			pData->sOne[0].sIp.ip[1],
			pData->sOne[0].sIp.ip[2],
			pData->sOne[0].sIp.ip[3]);
		m_ip_sIp.SetWindowText(strValue);
		
	}
	
	int i ;
	for (i = 0; i < pData->ucN; i++)
	{
		m_sMcascAddr[i] = pData->sOne[i];
	}

	CString strText;
	m_tab.DeleteAllItems();
	for (i = 0; i < pData->ucN; i++)
	{
		strText.Format("第%d个参数", i+1);
		m_tab.InsertItem(i, strText);
	}
	
	if (pData->ucN == 0)
	{
		m_tab.ShowWindow(SW_HIDE);
	}
	else
	{
		m_tab.ShowWindow(SW_SHOW);
	}

	UpdateData(FALSE);

}

void CDlgPreAfn04F6::OnRADIObCascyes() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_STATIC_CON_PARA))->SetWindowText("0~3");
	((CButton*)GetDlgItem(IDC_EDIT_ucN))->EnableWindow(TRUE);
}

void CDlgPreAfn04F6::OnRADIObCasced() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_STATIC_CON_PARA))->SetWindowText("仅1");
	m_edit_ucN = 1;
	m_tab.DeleteAllItems();
	m_tab.InsertItem(0, "第1个参数");
	((CButton*)GetDlgItem(IDC_EDIT_ucN))->EnableWindow(FALSE);



	char buf[8] = {0};
	memcpy(buf, m_sMcascAddr[0].acRegionCode, 6);
	CString strValue;
	m_edit_RegionCode.Format("%s", buf);
	
	m_edit_usPort = m_sMcascAddr[0].usPort;
	m_edit_ulConAddr = m_sMcascAddr[0].ulConAddr;
	
	strValue.Format("%d.%d.%d.%d", m_sMcascAddr[0].sIp.ip[0], 
		m_sMcascAddr[0].sIp.ip[1],
		m_sMcascAddr[0].sIp.ip[2],
		m_sMcascAddr[0].sIp.ip[3]);
	m_ip_sIp.SetWindowText(strValue);

	UpdateData(FALSE);

}

void CDlgPreAfn04F6::OnSelchangeTabIndex(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	i = m_tab.GetCurSel();
	
	
	char buf[8] = {0};
	memcpy(buf, m_sMcascAddr[i].acRegionCode, 6);
	CString strValue;
	m_edit_RegionCode.Format("%s", buf);
	
	m_edit_usPort = m_sMcascAddr[i].usPort;
	m_edit_ulConAddr = m_sMcascAddr[i].ulConAddr;
	
	strValue.Format("%d.%d.%d.%d", m_sMcascAddr[i].sIp.ip[0], 
		m_sMcascAddr[i].sIp.ip[1],
		m_sMcascAddr[i].sIp.ip[2],
		m_sMcascAddr[i].sIp.ip[3]);
	m_ip_sIp.SetWindowText(strValue);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgPreAfn04F6::OnChangeEDITacRegionCode() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	
	memcpy(m_sMcascAddr[i].acRegionCode, m_edit_RegionCode.GetBuffer(6), 6);
	m_edit_RegionCode.ReleaseBuffer();
	
}

void CDlgPreAfn04F6::OnChangeEDITulConAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	
	m_sMcascAddr[i].ulConAddr = m_edit_ulConAddr;
	
}

void CDlgPreAfn04F6::OnFieldchangedIPsIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_tab.GetCurSel();
	CString strIp;
	m_ip_sIp.GetWindowText(strIp);
	CNxConfig cfg;
	m_sMcascAddr[i].sIp.ip[0] = cfg.GetIpNum(strIp, 0);
	m_sMcascAddr[i].sIp.ip[1] = cfg.GetIpNum(strIp, 1);
	m_sMcascAddr[i].sIp.ip[2] = cfg.GetIpNum(strIp, 2);
	m_sMcascAddr[i].sIp.ip[3] = cfg.GetIpNum(strIp, 3);


	*pResult = 0;
}

void CDlgPreAfn04F6::OnChangeEDITusPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int i = m_tab.GetCurSel();
	m_sMcascAddr[i].usPort = m_edit_usPort;
	
	
}

void CDlgPreAfn04F6::SetNewValues()
{
	UpdateData();
	char buf[512] = {0};
	sMcAfn04f6 *pData = (sMcAfn04f6*)buf;
	
	
	pData->bCasc = ((CButton*)GetDlgItem(IDC_RADIO_bCasc_yes))->GetCheck();



	eCascType eCase = (eCascType)m_cmb_eType.GetCurSel();
	switch (eCase)
	{
	case CASC_NULL:
		pData->eType = MC_CASC_NULL;
		break;

	case CASC_RS485:
		pData->eType = MC_CASC_RS485;
		break;

	case CASC_ETH:
		pData->eType = MC_CASC_ETH;
		break;
	default:
		pData->eType = MC_CASC_NULL;
		break;
	}

	// eBaud
	eBaud ebaud = 	(eBaud)m_cmb_baud.GetCurSel();
	
	switch (ebaud)
	{
	case INDEX_BAUD_1200:   
		pData->sSer.eBaud = MC_BAUD_1200;
		break;
	case	INDEX_BAUD_2400:

		pData->sSer.eBaud = MC_BAUD_2400;
		break;
	case	INDEX_BAUD_4800:
		pData->sSer.eBaud = MC_BAUD_4800;
		break;

	case	INDEX_BAUD_9600:
		pData->sSer.eBaud = MC_BAUD_9600;
		break;
	case	INDEX_BAUD_19200:

		pData->sSer.eBaud = MC_BAUD_19200;
		break;
	case	INDEX_BAUD_38400:  

		pData->sSer.eBaud = MC_BAUD_38400;
		break;
	case INDEX_BAUD_76800:
		pData->sSer.eBaud = MC_BAUD_76800;
		break;
		
	default:
		pData->sSer.eBaud = MC_BAUD_9600;
		break;
	}
	

	// check
	eCheck check_index;
	check_index = (eCheck)m_cmb_check.GetCurSel();
	if ( check_index == CHECK_NONE)
	{
		pData->sSer.bCheck = FALSE;

	}
	else
	{
		pData->sSer.bCheck = TRUE;
		if (check_index == CHECK_ODD)
		{
			pData->sSer.bOdd = TRUE;
		}
		else
		{
			pData->sSer.bOdd = FALSE;
		}
	}
	
	// databit
	pData->sSer.eBit = (eMcSerBit)m_cmb_databit.GetCurSel();
	
	// stop
	eStopBit eStop;
	eStop = (eStopBit)m_cmb_stop.GetCurSel();
	pData->sSer.bStop1 = ((eStop == STOP_1 ) ? TRUE : FALSE) ;
	
	pData->ucN = m_edit_ucN;
	pData->ucPeriod = m_edit_ucPeriod;
	pData->ucReTry = m_edit_ucRetry ;
	pData->ucWaitC = m_edit_ucWaitC;
	pData->ucWaitP = m_edit_ucWaitP;
	
	
	int i ;
	for (i = 0; i < pData->ucN; i++)
	{
		pData->sOne[i] = m_sMcascAddr[i];
	}
	
	
	CNxConfig cfg;
	cfg.SetPreAfn04F6(pData, TRUE, TRUE);
	
	
}