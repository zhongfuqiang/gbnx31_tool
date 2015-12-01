// DlgPreA00F1.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreA00F1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreA00F1 dialog


CDlgPreA00F1::CDlgPreA00F1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreA00F1::IDD, pParent)
{
	eResCode = MC_RES_OK;
	m_bMaster= TRUE;
	//{{AFX_DATA_INIT(CDlgPreA00F1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPreA00F1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreA00F1)
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreA00F1, CDialog)
	//{{AFX_MSG_MAP(CDlgPreA00F1)
	ON_BN_CLICKED(IDC_RADIO_0, OnRadio0)
	ON_BN_CLICKED(IDC_RADIO_1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO_2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO_3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO_4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO_5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO_6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO_7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO_255, OnRadio255)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

eMcResCode CDlgPreA00F1::eGetResCode()
{
	return eResCode;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPreA00F1 message handlers

void CDlgPreA00F1::OnRadio0() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_OK;
}

void CDlgPreA00F1::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_NONE;
}

void CDlgPreA00F1::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_NOT_READY;
}

void CDlgPreA00F1::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_NOT_READY;
}

void CDlgPreA00F1::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_DATA_OTRNG;
}

void CDlgPreA00F1::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_PARA_OTRNG;
}

void CDlgPreA00F1::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_NOT_SAME;
}

void CDlgPreA00F1::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_NOT_SUPT;
}

void CDlgPreA00F1::OnRadio255() 
{
	// TODO: Add your control notification handler code here
	eResCode = MC_RES_DENY;
}

BOOL CDlgPreA00F1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	GetPre();
	
	m_btn_ok.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_ok.SetIcon(IDI_ICON_RIGHT);
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	m_btn_no.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_no.SetIcon(IDI_ICON_X);
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPreA00F1::GetPre()
{
	CNxConfig cfg;
	cfg.GetPreAfn00F1(&eResCode, m_bMaster);
	switch (eResCode)
	{
		
	case MC_RES_OK:
		((CButton*)GetDlgItem(IDC_RADIO_0))->SetCheck(BST_CHECKED);
		break;

	case MC_RES_NONE:
		((CButton*)GetDlgItem(IDC_RADIO_1))->SetCheck(BST_CHECKED);
		break;

	case MC_RES_NOT_READY:
		((CButton*)GetDlgItem(IDC_RADIO_2))->SetCheck(BST_CHECKED);
		break;

	case MC_RES_REMOVE:
		((CButton*)GetDlgItem(IDC_RADIO_3))->SetCheck(BST_CHECKED);
		break;
	
	case MC_RES_DATA_OTRNG:
		((CButton*)GetDlgItem(IDC_RADIO_4))->SetCheck(BST_CHECKED);
		break;	
	
	case MC_RES_PARA_OTRNG:
		((CButton*)GetDlgItem(IDC_RADIO_5))->SetCheck(BST_CHECKED);
		break;
	
	case MC_RES_NOT_SAME:
		((CButton*)GetDlgItem(IDC_RADIO_6))->SetCheck(BST_CHECKED);
		break;	
		
	case MC_RES_NOT_SUPT:
		((CButton*)GetDlgItem(IDC_RADIO_7))->SetCheck(BST_CHECKED);
		break;

	case MC_RES_DENY:
		((CButton*)GetDlgItem(IDC_RADIO_255))->SetCheck(BST_CHECKED);
		break;	

		default:
		((CButton*)GetDlgItem(IDC_RADIO_255))->SetCheck(BST_CHECKED);
		break;	
	}

}

void CDlgPreA00F1::OnOK() 
{
	// TODO: Add extra validation here
	SetNew();
		UpdateData(TRUE);
	CDialog::OnOK();
}

void CDlgPreA00F1::SetNew()
{
	CNxConfig cfg;
	cfg.SetPreAfn00F1(&eResCode, m_bMaster, TRUE);
}
