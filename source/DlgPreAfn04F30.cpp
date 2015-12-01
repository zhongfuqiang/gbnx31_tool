// DlgPreAfn04F30.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F30.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F30 dialog


CDlgPreAfn04F30::CDlgPreAfn04F30(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F30::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F30)
	m_edit_fShort = 0.0f;
	m_edit_fLong = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F30::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F30)
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_SHORT, m_edit_fShort);
	DDV_MinMaxFloat(pDX, m_edit_fShort, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_LONG, m_edit_fLong);
	DDV_MinMaxFloat(pDX, m_edit_fLong, 0.f, 99.99f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F30, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F30)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F30 message handlers

void CDlgPreAfn04F30::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F30::OnInitDialog() 
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

void CDlgPreAfn04F30::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f30 sData;
	cfg.GetPreAfn04F30(&sData, TRUE);


	m_edit_fLong = sData.fLong;
	m_edit_fShort = sData.fShort;

	UpdateData(FALSE);
}
void CDlgPreAfn04F30::SetNewValues()
{
	UpdateData();
	CNxConfig cfg;
	sMcAfn04f30 sData;

	sData.fShort = m_edit_fShort;
	sData.fLong = m_edit_fLong;
	cfg.SetPreAfn04F30(&sData, TRUE, TRUE);
	
}
