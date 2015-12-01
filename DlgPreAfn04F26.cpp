// DlgPreAfn04F26.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F26.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F26 dialog


CDlgPreAfn04F26::CDlgPreAfn04F26(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F26::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F26)
	m_edit_usTimesI = 0;
	m_edit_fI = 0.0f;
	m_edit_fU = 0.0f;
	m_edit_usTimesU = 0;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F26::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F26)
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_usTimesI, m_edit_usTimesI);
	DDX_Text(pDX, IDC_EDIT_fI, m_edit_fI);
	DDX_Text(pDX, IDC_EDIT_fU, m_edit_fU);
	DDX_Text(pDX, IDC_EDIT_usTimesU, m_edit_usTimesU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F26, CDialog)


	//{{AFX_MSG_MAP(CDlgPreAfn04F26)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F26 message handlers

BOOL CDlgPreAfn04F26::OnInitDialog() 
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


	m_pRadioIntgr[INTGR_4] = (CButton *)GetDlgItem(IDC_RADIO1);
	m_pRadioIntgr[INTGR_5] = (CButton *)GetDlgItem(IDC_RADIO2);
	m_pRadioIntgr[INTGR_6] = (CButton *)GetDlgItem(IDC_RADIO3);
	m_pRadioIntgr[INTGR_7] = (CButton *)GetDlgItem(IDC_RADIO4);


	m_pRadioDecim[DECIM_1] = (CButton *)GetDlgItem(IDC_RADIO5);
	m_pRadioDecim[DECIM_2] = (CButton *)GetDlgItem(IDC_RADIO6);
	m_pRadioDecim[DECIM_3] = (CButton *)GetDlgItem(IDC_RADIO7);
	m_pRadioDecim[DECIM_4] = (CButton *)GetDlgItem(IDC_RADIO8);

	
	m_pRadioLink[LINK_P3_L3] = (CButton *)GetDlgItem(IDC_RADIO9);
	m_pRadioLink[LINK_P3_L4] = (CButton *)GetDlgItem(IDC_RADIO10);
	m_pRadioLink[LINK_P1] = (CButton *)GetDlgItem(IDC_RADIO11);
	
	
	m_pRadioPhase[PHASE_UNKOWN] = (CButton *)GetDlgItem(IDC_RADIO16);
	m_pRadioPhase[PHASE_A] = (CButton *)GetDlgItem(IDC_RADIO13);
	m_pRadioPhase[PHASE_B] = (CButton *)GetDlgItem(IDC_RADIO14);
	m_pRadioPhase[PHASE_C] = (CButton *)GetDlgItem(IDC_RADIO15);
	
	
	GetCurValues();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F26::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

void CDlgPreAfn04F26::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f26 sAfn04f26;
	cfg.GetPreAfn04F26(&sAfn04f26, TRUE);
	
	INTGR_INDEX intgr_index;
	switch (sAfn04f26.sDigit.ucInteger)
	{
	case 4:
		intgr_index = INTGR_4;
		break;
	case 5:
		intgr_index = INTGR_5;
		break;

	case 6:
		intgr_index = INTGR_6;
		break;
	case 7:
		intgr_index = INTGR_7;
		break;
	default:
		break;
	}

	m_pRadioIntgr[intgr_index]->SetCheck(TRUE);

	DECIM_INDEX decim_index;
	switch (sAfn04f26.sDigit.ucDecimal)
	{
	case 1:
		decim_index = DECIM_1;
		break;
	case 2:
		decim_index = DECIM_2;
		break;
		
	case 3:
		decim_index = DECIM_3;
		break;
	case 4:
		decim_index = DECIM_4;
		break;
	default:
		break;
		
	}

	m_pRadioDecim[decim_index]->SetCheck(TRUE);




	
	LINK_INDEX link;
	switch (sAfn04f26.sLinkWay.eLink)
	{
	case MC_LINK_P3_L3:
		link = LINK_P3_L3;
		break;

	case MC_LINK_P3_L4:
		link = LINK_P3_L4;
		break;

	case MC_LINK_P1:
		link = LINK_P1;
		break;

	default:
		break;

	}
	m_pRadioLink[link]->SetCheck(TRUE);

	PHASE_INDEX phase;
	switch (sAfn04f26.sLinkWay.ePhase)
	{
	case MC_PHASE_UNKOWN:
		phase = PHASE_UNKOWN;
		break;
		
	case MC_PHASE_A:
		phase = PHASE_A;
		break;

	case MC_PHASE_B:
		phase = PHASE_B;
		break;
		
	case MC_PHASE_C:
		phase = PHASE_C;
		break;
		
	default:
		break;
		
	}

	m_pRadioPhase[phase]->SetCheck(TRUE);


	m_edit_fU = sAfn04f26.fU;
	m_edit_fI = sAfn04f26.fI;
	m_edit_usTimesU = sAfn04f26.usTimesU;
	m_edit_usTimesI = sAfn04f26.usTimesI;
	UpdateData(FALSE);

}

void CDlgPreAfn04F26::SetNewValues()
{
	UpdateData();
	CNxConfig cfg;
	sMcAfn04f26 sAfn04f26;
	cfg.GetPreAfn04F26(&sAfn04f26, TRUE);
	
	int i = 0;
	for (i = 0; i < INTGR_MAX; i++)
	{
		if (m_pRadioIntgr[i]->GetCheck() == TRUE)
		{
			sAfn04f26.sDigit.ucInteger = i+4;
		}
	}

	for (i = 0; i < DECIM_MAX; i++)
	{
		if (TRUE == m_pRadioDecim[i]->GetCheck())
		{
			sAfn04f26.sDigit.ucDecimal = i + 1;
		}
	}

	for (i = 0; i < LINK_MAX; i++)
	{
		if (TRUE == m_pRadioLink[i]->GetCheck())
		{
			sAfn04f26.sLinkWay.eLink = (eMcLink)(i+1);
		}
	}
		
	for (i = 0;i < PHASE_MAX; i++)
	{
		if (m_pRadioPhase[i]->GetCheck() == TRUE)
		{
			sAfn04f26.sLinkWay.ePhase = (eMcPhase)i;

		}
	}
	
	sAfn04f26.fU = m_edit_fU;
	sAfn04f26.fI  = m_edit_fI;
	sAfn04f26.usTimesU = m_edit_usTimesU;
	sAfn04f26.usTimesI = m_edit_usTimesI;

	cfg.SetPreAfn04F26(&sAfn04f26, TRUE, TRUE);
}
