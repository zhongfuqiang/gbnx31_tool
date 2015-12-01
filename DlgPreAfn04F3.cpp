// DlgPreAfn04F3.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F3 dialog


CDlgPreAfn04F3::CDlgPreAfn04F3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F3)
	m_edit_para = 0;
	m_edit_type_id = 0;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F3)
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_PARA, m_edit_para);
	DDV_MinMaxUInt(pDX, m_edit_para, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_TYPE_ID, m_edit_type_id);
	DDV_MinMaxUInt(pDX, m_edit_type_id, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F3, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F3)
	ON_EN_CHANGE(IDC_EDIT_TYPE_ID, OnChangeEditTypeId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F3 message handlers

void CDlgPreAfn04F3::OnOK() 
{
	// TODO: Add extra validation here


	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	

	GetCurValues();


	// TODO: Add extra initialization here
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

void CDlgPreAfn04F3::SetNewValues()
{
	UpdateData(TRUE);
	CNxConfig cfg;
	sMcAfn04f3 sAfn04f3;
	sAfn04f3.ucTypeID = m_edit_type_id;
	sAfn04f3.usAuthPara = m_edit_para;
	
	cfg.SetPreAfn04F3(&sAfn04f3, TRUE, TRUE);
}

void CDlgPreAfn04F3::GetCurValues()
{
	CNxConfig cfg;
	sMcAfn04f3 sAfn04f3;
	cfg.GetPreAfn04F3(&sAfn04f3, TRUE);
	
	m_edit_type_id = sAfn04f3.ucTypeID ;
	m_edit_para = sAfn04f3.usAuthPara;

	if (m_edit_type_id == 0)
	{
		((CButton*)GetDlgItem(IDC_EDIT_PARA))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_EDIT_PARA))->EnableWindow(TRUE);
	}


	UpdateData(FALSE);
}

void CDlgPreAfn04F3::OnChangeEditTypeId() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_edit_type_id == 0)
	{
		m_edit_para = 0;
		((CButton*)GetDlgItem(IDC_EDIT_PARA))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_EDIT_PARA))->EnableWindow(TRUE);
	}
		
	UpdateData(FALSE);
}
