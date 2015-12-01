// DlgPreAfn04F4.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F4 dialog


CDlgPreAfn04F4::CDlgPreAfn04F4(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F4)
	m_edit_team_1 = 0;
	m_edit_team_2 = 0;
	m_edit_team_3 = 0;
	m_edit_team_4 = 0;
	m_edit_team_5 = 0;
	m_edit_team_6 = 0;
	m_edit_team_7 = 0;
	m_edit_team_8 = 0;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F4)
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_TEAM_1, m_edit_team_1);
	DDX_Text(pDX, IDC_EDIT_TEAM_2, m_edit_team_2);
	DDX_Text(pDX, IDC_EDIT_TEAM_3, m_edit_team_3);
	DDX_Text(pDX, IDC_EDIT_TEAM_4, m_edit_team_4);
	DDX_Text(pDX, IDC_EDIT_TEAM_5, m_edit_team_5);
	DDX_Text(pDX, IDC_EDIT_TEAM_6, m_edit_team_6);
	DDX_Text(pDX, IDC_EDIT_TEAM_7, m_edit_team_7);
	DDX_Text(pDX, IDC_EDIT_TEAM_8, m_edit_team_8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F4, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F4 message handlers

void CDlgPreAfn04F4::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F4::OnInitDialog() 
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


	GetCurValues();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F4::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f4 sAfn04f4;
	cfg.GetPreAfn04F4(&sAfn04f4, TRUE);
	
	m_edit_team_1 = sAfn04f4.ulAddr[0];
	m_edit_team_2 = sAfn04f4.ulAddr[1];
	m_edit_team_3 = sAfn04f4.ulAddr[2];
	m_edit_team_4 = sAfn04f4.ulAddr[3];
	m_edit_team_5 = sAfn04f4.ulAddr[4];
	m_edit_team_6 = sAfn04f4.ulAddr[5];
	m_edit_team_7 = sAfn04f4.ulAddr[6];
	m_edit_team_8 = sAfn04f4.ulAddr[7];

	UpdateData(FALSE);
				
}

void CDlgPreAfn04F4::SetNewValues()
{
	UpdateData(TRUE);
	CNxConfig cfg;
	sMcAfn04f4 sAfn04f4;
	
	
	sAfn04f4.ulAddr[0] = m_edit_team_1;
	sAfn04f4.ulAddr[1] = m_edit_team_2;
	sAfn04f4.ulAddr[2] = m_edit_team_3;
	sAfn04f4.ulAddr[3] = m_edit_team_4;
	sAfn04f4.ulAddr[4] = m_edit_team_5 ;
	sAfn04f4.ulAddr[5] = m_edit_team_6;
	sAfn04f4.ulAddr[6] = m_edit_team_7;
	sAfn04f4.ulAddr[7] = m_edit_team_8;
	
	cfg.SetPreAfn04F4(&sAfn04f4, TRUE, TRUE);
	
}
