// DlgPreAfn04F33.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F33.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F33 dialog


CDlgPreAfn04F33::CDlgPreAfn04F33(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F33::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F33)
	m_edit_pn = 0;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F33::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F33)
	DDX_Control(pDX, IDC_EDIT_MIN, m_edit_min);
	DDX_Control(pDX, IDC_EDIT_MAX, m_edit_max);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comb_type);
	DDX_Text(pDX, IDC_EDIT_PN, m_edit_pn);
	DDV_MinMaxInt(pDX, m_edit_pn, 0, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F33, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F33)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F33 message handlers

BOOL CDlgPreAfn04F33::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitCombType();
	GetOldValue();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F33::GetOldValue()
{
	CNxConfig cfg;
	
	UINT16 usPn = 0;
//	sMtCfgNotElec sCfgNotElec;
	CString strValue;

	//cfg.GetPreAfn04F33(&usPn,&sCfgNotElec, MT_ROLE_MASTER);
	
	m_edit_pn = usPn;
	
//	strValue.Format("%0.3lf",sCfgNotElec.dMax);
//	m_edit_max.SetWindowText(strValue);

//	strValue.Format("%0.3lf",sCfgNotElec.dMin);
//	m_edit_min.SetWindowText(strValue);


//	int type = sCfgNotElec.eType;
	//m_comb_type.SetCurSel(type -1);

	UpdateData(FALSE);
	
}

void CDlgPreAfn04F33::SetNewValue()
{

	CNxConfig cfg;
	UINT16 usPn = 0;
//	sMtCfgNotElec sCfgNotElec;
	CString strValue;
	
//	sCfgNotElec.eType = eMtNotElec(m_comb_type.GetCurSel() + 1);
	
	m_edit_max.GetWindowText(strValue);
//	sCfgNotElec.dMax  = atof(strValue);
	
	m_edit_min.GetWindowText(strValue);
//	sCfgNotElec.dMin = atof(strValue);

	UpdateData(TRUE);
	usPn = m_edit_pn;

//	cfg.SetPreAfn04F33(usPn,&sCfgNotElec, MT_ROLE_MASTER);

}

void CDlgPreAfn04F33::InitCombType()
{

		m_type_name[0] = "温度";
		m_type_name[1] = "流量";
		m_type_name[2] = "流速";
		m_type_name[3] = "压力";
		m_type_name[4] = "湿度";
		m_type_name[5] = "照度";
		m_type_name[6] = "转速";

		int i;
		for (i = 0; i < 7 ;i ++)
		{
			m_comb_type.InsertString(i, m_type_name[i]);
		}
		
		m_comb_type.SetCurSel(0);
	
}

void CDlgPreAfn04F33::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValue();
	CDialog::OnOK();
}
