// DlgPreAfn04F27.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F27.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F27 dialog


CDlgPreAfn04F27::CDlgPreAfn04F27(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F27::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F27)
	m_edit_fDropV = 0.0f;
	m_edit_ucTimeLossV = 0;
	m_edit_sMcOverV_fUpUp = 0.0f;
	m_edit_sMcLossV_fDownFDown = 0.0f;
	m_edit_sMcLossV_fFactor = 0.0f;
	m_edit_sMcLossV_ucTime = 0;
	m_edit_sMcOverI_fFactor = 0.0f;
	m_edit_sMcOverI_fUpUp = 0.0f;
	m_edit_sMcOverI_ucTime = 0;
	m_edit_sMcOverV_fFactor = 0.0f;
	m_edit_sMcOverV_ucTime = 0;
	m_edit_sMcZeroI_ucTime = 0;
	m_edit_sMcZeroI_fUp = 0.0f;
	m_edit_sMcZeroI_fFactor = 0.0f;
	m_edit_sMcUnblnV_fFactor = 0.0f;
	m_edit_sMcUnblnV_fLimit = 0.0f;
	m_edit_sMcUnblnV_ucTime = 0;
	m_edit_sMcSuperI_fFactor = 0.0f;
	m_edit_sMcSuperI_fUp = 0.0f;
	m_edit_sMcSuperI_ucTime = 0;
	m_edit_sMcUnblnI_fFactor = 0.0f;
	m_edit_sMcUnblnI_fLimit = 0.0f;
	m_edit_sMcUnblnI_ucTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F27::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F27)
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_fDropV, m_edit_fDropV);
	DDX_Text(pDX, IDC_EDIT_ucTimeLossV, m_edit_ucTimeLossV);
	DDV_MinMaxUInt(pDX, m_edit_ucTimeLossV, 0, 255);
	DDX_Text(pDX, IDC_EDIT_sMcOverV_fUpUp, m_edit_sMcOverV_fUpUp);
	DDX_Text(pDX, IDC_EDIT_sMcLossV_fDownDown, m_edit_sMcLossV_fDownFDown);
	DDX_Text(pDX, IDC_EDIT_sMcLossV_fFactor, m_edit_sMcLossV_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcLossV_ucTime, m_edit_sMcLossV_ucTime);
	DDX_Text(pDX, IDC_EDIT_sMcOverI_fFactor, m_edit_sMcOverI_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcOverI_fUpUp, m_edit_sMcOverI_fUpUp);
	DDX_Text(pDX, IDC_EDIT_sMcOverI_ucTime, m_edit_sMcOverI_ucTime);
	DDX_Text(pDX, IDC_EDIT_sMcOverV_fFactor, m_edit_sMcOverV_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcOverV_ucTime, m_edit_sMcOverV_ucTime);
	DDX_Text(pDX, IDC_EDIT_sMcZeroI_ucTime, m_edit_sMcZeroI_ucTime);
	DDX_Text(pDX, IDC_EDIT_sMcZeroI_fUp, m_edit_sMcZeroI_fUp);
	DDX_Text(pDX, IDC_EDIT_sMcZeroI_fFactor, m_edit_sMcZeroI_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcUnblnV_fFactor, m_edit_sMcUnblnV_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcUnblnV_fLimit, m_edit_sMcUnblnV_fLimit);
	DDX_Text(pDX, IDC_EDIT_sMcUnblnV_ucTime, m_edit_sMcUnblnV_ucTime);
	DDX_Text(pDX, IDC_EDIT_sMcSuperI_fFactor, m_edit_sMcSuperI_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcSuperI_fUp, m_edit_sMcSuperI_fUp);
	DDX_Text(pDX, IDC_EDIT_sMcSuperI_ucTime, m_edit_sMcSuperI_ucTime);
	DDX_Text(pDX, IDC_EDIT_sMcUnblnI_fFactor, m_edit_sMcUnblnI_fFactor);
	DDX_Text(pDX, IDC_EDIT_sMcUnblnI_fLimit, m_edit_sMcUnblnI_fLimit);
	DDX_Text(pDX, IDC_EDIT_sMcUnblnI_ucTime, m_edit_sMcUnblnI_ucTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F27, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F27)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F27 message handlers

void CDlgPreAfn04F27::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F27::OnInitDialog() 
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

void CDlgPreAfn04F27::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f27 sAfn04F27;
	
	cfg.GetPreAfn04F27(&sAfn04F27, TRUE);
	
	m_edit_fDropV              = sAfn04F27.fDropV;
	m_edit_ucTimeLossV         = sAfn04F27.ucTimeLossV;
	m_edit_sMcOverV_fUpUp      = sAfn04F27.sOverV.fUpUp;

	m_edit_sMcLossV_fDownFDown = sAfn04F27.sLossV.fDownDown;
	m_edit_sMcLossV_fFactor    = sAfn04F27.sLossV.fFactor;
	m_edit_sMcLossV_ucTime     = sAfn04F27.sLossV.ucTime;

	m_edit_sMcOverI_fFactor    = sAfn04F27.sOverI.fFactor;
	m_edit_sMcOverI_fUpUp      = sAfn04F27.sOverI.fUpUp;
	m_edit_sMcOverI_ucTime     = sAfn04F27.sOverI.ucTime;
	m_edit_sMcOverV_fFactor    = sAfn04F27.sOverV.fFactor;
	m_edit_sMcOverV_ucTime     = sAfn04F27.sOverV.ucTime;
	m_edit_sMcZeroI_ucTime     = sAfn04F27.sZeroI.ucTime;
	m_edit_sMcZeroI_fUp        = sAfn04F27.sZeroI.fUp;
	m_edit_sMcZeroI_fFactor    = sAfn04F27.sZeroI.fFactor;
	m_edit_sMcUnblnV_fFactor   = sAfn04F27.sUblV.fFactor;
	m_edit_sMcUnblnV_fLimit    = sAfn04F27.sUblV.fLimit;
	m_edit_sMcUnblnV_ucTime    = sAfn04F27.sUblV.ucTime;
	m_edit_sMcSuperI_fFactor   = sAfn04F27.sSuperI.fFactor;
	m_edit_sMcSuperI_fUp       = sAfn04F27.sSuperI.fFactor;
	m_edit_sMcSuperI_ucTime    = sAfn04F27.sSuperI.ucTime;
	m_edit_sMcUnblnI_fFactor   = sAfn04F27.sUblI.fFactor;
	m_edit_sMcUnblnI_fLimit    = sAfn04F27.sUblI.fLimit;
	m_edit_sMcUnblnI_ucTime    = sAfn04F27.sUblI.ucTime;

	UpdateData(FALSE);
}

void CDlgPreAfn04F27::SetNewValues()
{
	UpdateData();
	CNxConfig cfg;
	sMcAfn04f27 sAfn04F27;


	sAfn04F27.fDropV = m_edit_fDropV;
	sAfn04F27.ucTimeLossV = m_edit_ucTimeLossV;
	sAfn04F27.sOverV.fUpUp = m_edit_sMcOverV_fUpUp;
	sAfn04F27.sLossV.fDownDown = m_edit_sMcLossV_fDownFDown;
	sAfn04F27.sLossV.fFactor = m_edit_sMcLossV_fFactor;
	sAfn04F27.sLossV.ucTime = m_edit_sMcLossV_ucTime;
	sAfn04F27.sOverI.fFactor = m_edit_sMcOverI_fFactor;
	sAfn04F27.sOverI.fUpUp = m_edit_sMcOverI_fUpUp;
	sAfn04F27.sOverI.ucTime = m_edit_sMcOverI_ucTime;
	
	sAfn04F27.sOverV.fFactor = m_edit_sMcOverV_fFactor;
	sAfn04F27.sOverV.ucTime = m_edit_sMcOverV_ucTime;
	sAfn04F27.sZeroI.ucTime = m_edit_sMcZeroI_ucTime;
	sAfn04F27.sZeroI.fUp = m_edit_sMcZeroI_fUp;
	sAfn04F27.sZeroI.fFactor = m_edit_sMcZeroI_fFactor;
	
	sAfn04F27.sUblV.fFactor = m_edit_sMcUnblnV_fFactor;
	sAfn04F27.sUblV.fLimit = m_edit_sMcUnblnV_fLimit;
	sAfn04F27.sUblV.ucTime = m_edit_sMcUnblnV_ucTime;
	sAfn04F27.sSuperI.fFactor = m_edit_sMcSuperI_fFactor;
	sAfn04F27.sSuperI.fUp      = m_edit_sMcSuperI_fUp;
	sAfn04F27.sSuperI.ucTime = m_edit_sMcSuperI_ucTime;
	sAfn04F27.sUblI.fFactor = m_edit_sMcUnblnI_fFactor;
	sAfn04F27.sUblI.fLimit = m_edit_sMcUnblnI_fLimit;
	sAfn04F27.sUblI.ucTime = m_edit_sMcUnblnI_ucTime;

	
	cfg.SetPreAfn04F27(&sAfn04F27, TRUE, TRUE);
}
