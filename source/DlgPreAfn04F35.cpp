// DlgPreAfn04F35.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F35.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F35 dialog


CDlgPreAfn04F35::CDlgPreAfn04F35(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F35::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F35)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strPrecise[MC_PREC_P4-1] = "0, (+/-)10000～99999990000";
	m_strPrecise[MC_PREC_P3-1] = "0, (+/-)1000～9999999000";
	m_strPrecise[MC_PREC_P2-1] = "0, (+/-)100～999999900";
	m_strPrecise[MC_PREC_P1-1] = "0, (+/-)10～99999990";
	m_strPrecise[MC_PREC_P0-1] = "0, (+/-)1～9999999";
	m_strPrecise[MC_PREC_N1-1] = "0, (+/-)0.1～999999.9";
	m_strPrecise[MC_PREC_N2-1] = "0, (+/-)0.01～99999.99";
	m_strPrecise[MC_PREC_N3-1] = "0, (+/-)0.001～9999.999";
}


void CDlgPreAfn04F35::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F35)
	DDX_Control(pDX, IDC_STATIC_INFO2, m_static_info2);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDC_STATIC_INFO, m_static_info);
	DDX_Control(pDX, IDC_EDIT_UP, m_edit_up);
	DDX_Control(pDX, IDC_EDIT_DN, m_edit_dn);
	DDX_Control(pDX, IDC_CMBO_PREC, m_comb_prec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F35, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F35)
	ON_CBN_SELENDOK(IDC_CMBO_PREC, OnSelendokCmboPrec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F35 message handlers

void CDlgPreAfn04F35::OnOK() 
{
	// TODO: Add extra validation here
	eMcPrecise  ePrec;
	ePrec = (eMcPrecise)(m_comb_prec.GetCurSel() + 1);
	
	// sUp
	switch (ePrec)
	{
	case MC_PREC_P4:
	case MC_PREC_P3:
	case MC_PREC_P2:
	case MC_PREC_P0:
		break;
	default:
		break;
	}
	
	// sDown
	
	
	
	
	SetNewValues();
	GetCurValues();
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F35::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// 初始化精度名称
	int i = 0;
	for (i = 0; i < MC_PREC_N3; i++)
	{
		m_comb_prec.InsertString(i, m_strPrecise[i]);
	}
	
	
	m_static_info2.SetWindowText("");
	m_static_info.SetWindowText("");
	
	
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



// 
void CDlgPreAfn04F35::SetNelcType(eMcNElcType eNelctype)
{

	// 显示数据到界面上
	switch (eNelctype)
	{
	case MC_NELC_TEMP:
		((CButton*)GetDlgItem(IDC_RADIO_TEMP))->SetCheck(TRUE);
		break;

	case MC_NELC_FLOW:
		((CButton*)GetDlgItem(IDC_RADIO_FLOW))->SetCheck(TRUE);
		break;

	case MC_NELC_FV:
		((CButton*)GetDlgItem(IDC_RADIO_FV))->SetCheck(TRUE);
		break;
		
	case MC_NELC_PRESS:
		((CButton*)GetDlgItem(IDC_RADIO_PRESS))->SetCheck(TRUE);
		break;

	case MC_NELC_HUMI:
		((CButton*)GetDlgItem(IDC_RADIO_HUMI))->SetCheck(TRUE);
		break;
		
	case MC_NELC_LIGHT:
		((CButton*)GetDlgItem(IDC_RADIO_LIGHT))->SetCheck(TRUE);
		break;

	case MC_NELC_RV:
		((CButton*)GetDlgItem(IDC_RADIO_RV))->SetCheck(TRUE);
		break;
		
	case MC_NELC_420MA:
		((CButton*)GetDlgItem(IDC_RADIO_420MA))->SetCheck(TRUE);
		break;
		
	default:
		break;
		
	}
}

void CDlgPreAfn04F35::GetNelcType( eMcNElcType &eNelctype )
{
	BOOL  bCheck = FALSE;
	
	// IDC_RADIO_TEMP
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_TEMP))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_TEMP;
		return;
	}
	
	// IDC_RADIO_FLOW
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_FLOW))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_FLOW;
		return;
	}
	
	// IDC_RADIO_FV
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_FV))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_FV;
		return;
	}
	
	// IDC_RADIO_PRESS
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_PRESS))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_PRESS;
		return;
	}
	
	// IDC_RADIO_HUMI
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_HUMI))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_HUMI;
		return;
	}
	
	// IDC_RADIO_LIGHT
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_LIGHT))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_LIGHT;
		return;
	}
	
	// IDC_RADIO_RV
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_RV))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_RV;
		return;
	}
	
	// IDC_RADIO_420MA
	bCheck = ((CButton*)GetDlgItem(IDC_RADIO_420MA))->GetCheck();
	if(bCheck == TRUE)
	{
		eNelctype = MC_NELC_420MA;
		return;
	}

}

void CDlgPreAfn04F35::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f35 sAfn04f35;		
	cfg.GetPreAfn04F35(&sAfn04f35, TRUE);
	SetNelcType(sAfn04f35.eType);
	
	
	// 精度
	m_comb_prec.SetCurSel(sAfn04f35.sUp.ePrec-1);
	
	CString strUp, strDn;
	
	// sUp
	switch (sAfn04f35.sUp.ePrec)
	{
	case  MC_PREC_P4:
	case MC_PREC_P3:
	case MC_PREC_P2:
	case MC_PREC_P1:
	case MC_PREC_P0:
		strUp.Format("%0.0f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.0f", sAfn04f35.sDown.dValue);
		
		break;
		
	case MC_PREC_N1:
		strUp.Format("%0.1f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.1f", sAfn04f35.sDown.dValue);
		break;
		
		
	case MC_PREC_N2:
		strUp.Format("%0.2f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.2f", sAfn04f35.sDown.dValue);
		break;
		
		
	case MC_PREC_N3:
		strUp.Format("%0.3f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.3f", sAfn04f35.sDown.dValue);
		break;
		
	default:
		break;
	}
	
	m_edit_up.SetWindowText(strUp);
	m_edit_dn.SetWindowText(strDn);
}

void CDlgPreAfn04F35::SetNewValues()
{
	CNxConfig cfg;
	sMcAfn04f35 sAfn04f35;	
	eMcNElcType eType;
	GetNelcType(eType);
	sAfn04f35.eType = eType;
	sAfn04f35.sUp.ePrec = (eMcPrecise)(m_comb_prec.GetCurSel() + 1);
	sAfn04f35.sDown.ePrec = sAfn04f35.sUp.ePrec;
	
	CString strUp,strDn;
	m_edit_up.GetWindowText(strUp);
	m_edit_dn.GetWindowText(strDn);
	
	sAfn04f35.sUp.dValue = atof(strUp.GetBuffer(strUp.GetLength()));
	strUp.ReleaseBuffer();
	
	sAfn04f35.sDown.dValue = atof(strDn.GetBuffer(strDn.GetLength()));
	strDn.ReleaseBuffer();
	
	cfg.SetPreAfn04F35(&sAfn04f35, TRUE, TRUE);
}

void CDlgPreAfn04F35::OnSelendokCmboPrec() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	i = m_comb_prec.GetCurSel();
	i+= 1;
	CString strInfo = "";
	switch (i)
	{
	case MC_PREC_P4:
		strInfo += "(+/-)1～9999非法";
		break;
		
	case MC_PREC_P3:
		strInfo += "(+/-)1～999非法";
		break;
		
	case MC_PREC_P2:
		strInfo += "(+/-)1～999非法";
		break;
		
	case MC_PREC_P1:
		strInfo += "(+/-)1～9非法";
		break;
		
	case MC_PREC_P0:
		strInfo += "-9999999～9999999";
		break;
		
	case MC_PREC_N1:
		strInfo += "(+/-)0.01～0.09非法";
		break;
		
	case MC_PREC_N2:
		strInfo += "(+/-)0.001～0.009非法";
		break;
		
	case MC_PREC_N3:
		strInfo += "(+/-)0.0001～0.0009非法";
		break;
		
	default:
		break;
	}
	
	m_static_info2.SetWindowText(strInfo);
	m_static_info.SetWindowText(strInfo);
}
