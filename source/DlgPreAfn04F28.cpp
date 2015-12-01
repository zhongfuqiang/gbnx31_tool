// DlgPreAfn04F28.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F28.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F28 dialog


CDlgPreAfn04F28::CDlgPreAfn04F28(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F28::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F28)
	m_edit_para2 = 0.0f;
	m_edit_para1 = 0.0f;
	m_edit_limit = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F28::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F28)
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_PARA_2, m_edit_para2);
	DDX_Text(pDX, IDC_EDIT_PARA_1, m_edit_para1);
	DDX_Text(pDX, IDC_EDIT_LIMIT_3, m_edit_limit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F28, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F28)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F28 message handlers

void CDlgPreAfn04F28::OnOK() 
{
	// TODO: Add extra validation here
SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F28::OnInitDialog() 
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

void CDlgPreAfn04F28::SetNewValues()
{
	UpdateData();

	CNxConfig cfg;
	sMcAfn04F28 sData;
	sData.fPara1 = m_edit_para1;
	sData.fWarning = m_edit_limit;
	sData.fPara2 = m_edit_para2;

	cfg.SetPreAfn04F28(&sData, TRUE,TRUE);
}

void CDlgPreAfn04F28::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04F28 sData;
	cfg.GetPreAfn04F28(&sData, TRUE);

	m_edit_limit = sData.fWarning;
	m_edit_para1 = sData.fPara1;
	m_edit_para2 = sData.fPara2;


	UpdateData(FALSE);
}
