// DlgPreAfn04F10.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F10.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F10 dialog


CDlgPreAfn04F10::CDlgPreAfn04F10(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F10::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F10)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F10)
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F10, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F10 message handlers

void CDlgPreAfn04F10::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F10::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btn_ok.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_ok.SetIcon(IDI_ICON_RIGHT);
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	m_btn_no.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_no.SetIcon(IDI_ICON_X);
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));

	int i = 0;
	for (i = 0; i < 8; i++)
	{
		m_pCheckIn[i] = (CButton*)GetDlgItem(IDC_CHECK_IN_1 + i);
		m_pCheckOn[i] = (CButton*)GetDlgItem(IDC_CHECK_ON_1 + i);
	}
	
	// TODO: Add extra initialization here

	GetCurValues();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F10::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f10 sAfn04f10;
	cfg.GetPreAfn04F10(&sAfn04f10, TRUE);
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (sAfn04f10.bIn[i] == TRUE)
		{
			m_pCheckIn[i]->SetCheck(TRUE);	
		}


		if (sAfn04f10.bOn[i] == TRUE)
		{
			m_pCheckOn[i]->SetCheck(TRUE);
		}
	}
		
}


void CDlgPreAfn04F10::SetNewValues()
{
	CNxConfig cfg;
	sMcAfn04f10 sAfn04f10;
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (m_pCheckIn[i]->GetCheck() == TRUE)
		{
			sAfn04f10.bIn[i] = TRUE;
		}
		else
		{
			sAfn04f10.bIn[i] = FALSE;
		}

		if(m_pCheckOn[i]->GetCheck() == TRUE)
		{
			sAfn04f10.bOn[i] = TRUE;
		}
		else
		{
			sAfn04f10.bOn[i] = FALSE;
		}
	}

	cfg.SetPreAfn04F10(&sAfn04f10, TRUE, TRUE);
}
