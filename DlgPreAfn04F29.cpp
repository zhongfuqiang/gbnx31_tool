// DlgPreAfn04F29.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F29.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F29 dialog


CDlgPreAfn04F29::CDlgPreAfn04F29(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F29::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F29)
	m_sIa_fEven = 0.0f;
	m_sIa_fOdd = 0.0f;
	m_sIa_fTotal = 0.0f;
	m_sIb_fEven = 0.0f;
	m_sIb_fOdd = 0.0f;
	m_sIb_fTotal = 0.0f;
	m_sIc_fEven = 0.0f;
	m_sIc_fOdd = 0.0f;
	m_sIc_fTotal = 0.0f;
	m_sVa_fEven = 0.0f;
	m_sVa_fOdd = 0.0f;
	m_sVa_fTotal = 0.0f;
	m_sVb_fEven = 0.0f;
	m_sVb_fOdd = 0.0f;
	m_sVb_fTotal = 0.0f;
	m_sVc_fEven = 0.0f;
	m_sVc_fOdd = 0.0f;
	m_sVc_fTotal = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F29::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F29)
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_sIa_fEven, m_sIa_fEven);
	DDV_MinMaxFloat(pDX, m_sIa_fEven, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIa_fOdd, m_sIa_fOdd);
	DDV_MinMaxFloat(pDX, m_sIa_fOdd, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIa_fTotal, m_sIa_fTotal);
	DDV_MinMaxFloat(pDX, m_sIa_fTotal, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIb_fEven, m_sIb_fEven);
	DDV_MinMaxFloat(pDX, m_sIb_fEven, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIb_fOdd, m_sIb_fOdd);
	DDV_MinMaxFloat(pDX, m_sIb_fOdd, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIb_fTotal, m_sIb_fTotal);
	DDV_MinMaxFloat(pDX, m_sIb_fTotal, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIc_fEven, m_sIc_fEven);
	DDV_MinMaxFloat(pDX, m_sIc_fEven, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIc_fOdd, m_sIc_fOdd);
	DDV_MinMaxFloat(pDX, m_sIc_fOdd, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sIc_fTotal, m_sIc_fTotal);
	DDV_MinMaxFloat(pDX, m_sIc_fTotal, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVa_fEven, m_sVa_fEven);
	DDV_MinMaxFloat(pDX, m_sVa_fEven, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVa_fOdd, m_sVa_fOdd);
	DDV_MinMaxFloat(pDX, m_sVa_fOdd, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVa_fTotal, m_sVa_fTotal);
	DDV_MinMaxFloat(pDX, m_sVa_fTotal, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVb_fEven, m_sVb_fEven);
	DDV_MinMaxFloat(pDX, m_sVb_fEven, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVb_fOdd, m_sVb_fOdd);
	DDV_MinMaxFloat(pDX, m_sVb_fOdd, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVb_fTotal, m_sVb_fTotal);
	DDV_MinMaxFloat(pDX, m_sVb_fTotal, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVc_fEven, m_sVc_fEven);
	DDV_MinMaxFloat(pDX, m_sVc_fEven, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVc_fOdd, m_sVc_fOdd);
	DDV_MinMaxFloat(pDX, m_sVc_fOdd, 0.f, 99.99f);
	DDX_Text(pDX, IDC_EDIT_sVc_fTotal, m_sVc_fTotal);
	DDV_MinMaxFloat(pDX, m_sVc_fTotal, 0.f, 99.99f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F29, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F29)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F29 message handlers

void CDlgPreAfn04F29::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F29::OnInitDialog() 
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

void CDlgPreAfn04F29::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04F29 sData;
	cfg.GetPreAfn04F29(&sData, TRUE);

	m_sVa_fTotal = sData.sVa.fTotal;
	m_sVa_fOdd   = sData.sVa.fOdd;
	m_sVa_fEven  = sData.sVa.fEven;
	
	
	m_sVb_fTotal = sData.sVb.fTotal;
	m_sVb_fOdd   = sData.sVb.fOdd;
	m_sVb_fEven  = sData.sVb.fEven;
	
	
	m_sVc_fTotal = sData.sVc.fTotal;
	m_sVc_fOdd   = sData.sVc.fOdd;
	m_sVc_fEven  = sData.sVc.fEven;

	m_sIa_fTotal = sData.sIa.fTotal;
	m_sIa_fOdd   = sData.sIa.fOdd;
	m_sIa_fEven  = sData.sIa.fEven;
	
	
	m_sIb_fTotal = sData.sIb.fTotal;
	m_sIb_fOdd   = sData.sIb.fOdd;
	m_sIb_fEven  = sData.sIb.fEven;
	
	
	m_sIc_fTotal = sData.sIc.fTotal;
	m_sIc_fOdd   = sData.sIc.fOdd;
	m_sIc_fEven  = sData.sIc.fEven;

	UpdateData(FALSE);
}	

void CDlgPreAfn04F29::SetNewValues()
{
	UpdateData();

	CNxConfig cfg;
	sMcAfn04F29 sData;


	sData.sVa.fTotal = m_sVa_fTotal;
	sData.sVa.fOdd = m_sVa_fOdd;
	sData.sVa.fEven = m_sVa_fEven;

	sData.sVb.fTotal = m_sVb_fTotal;
	sData.sVb.fOdd = m_sVb_fOdd;
	sData.sVb.fEven = m_sVb_fEven;

	sData.sVc.fTotal = m_sVc_fTotal;
	sData.sVc.fOdd = m_sVc_fOdd;
	sData.sVc.fEven = m_sVc_fEven;

	sData.sIa.fTotal = m_sIa_fTotal;
	sData.sIa.fOdd = m_sIa_fOdd;
	sData.sIa.fEven = m_sIa_fEven;

	sData.sIb.fTotal = m_sIb_fTotal;
	sData.sIb.fOdd = m_sIb_fOdd;
	sData.sIb.fEven = m_sIb_fEven;

	sData.sIc.fTotal = m_sIc_fTotal;
	sData.sIc.fOdd = m_sIc_fOdd;
	sData.sIc.fEven = m_sIc_fEven;
	
	cfg.SetPreAfn04F29(&sData, TRUE, TRUE);
}
