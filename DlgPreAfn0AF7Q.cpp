// DlgPreAfn0AF7Q.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn0AF7Q.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn0AF7Q dialog


CDlgPreAfn0AF7Q::CDlgPreAfn0AF7Q(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn0AF7Q::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn0AF7Q)
	m_edit_total = 0;
	m_edit_usport = 0;
	//}}AFX_DATA_INIT
	memset(m_usPort, 0 , sizeof(m_usPort));
}


void CDlgPreAfn0AF7Q::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn0AF7Q)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_NUM_TOTAL, m_edit_total);
	DDX_Text(pDX, IDC_EDIT_ID, m_edit_usport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn0AF7Q, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn0AF7Q)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_EN_CHANGE(IDC_EDIT_NUM_TOTAL, OnChangeEditNumTotal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn0AF7Q message handlers

void CDlgPreAfn0AF7Q::OnOK() 
{
	// TODO: Add extra validation here
	SetNew();
	CDialog::OnOK();
}

BOOL CDlgPreAfn0AF7Q::OnInitDialog() 
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

	GetCur();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn0AF7Q::SetNew()
{
	UpdateData();
	char buf[512] = {0};
	sMcAfn10f7q *pData = (sMcAfn10f7q*)buf;
	
	CNxConfig cfg;
	
	
	pData->usN = m_edit_total;
	int i = 0;
	for (i = 0; i < pData->usN; i++)
	{
		pData->usPort[i] = m_usPort[i];
	}
	
	cfg.SetPreAfn0aF7q(pData, TRUE, TRUE);

}

void CDlgPreAfn0AF7Q::GetCur()
{
	char buf[512] = {0};
	sMcAfn10f7q *pData = (sMcAfn10f7q*)buf;
	
	CNxConfig cfg;
	cfg.GetPreAfn0aF7q(pData, TRUE);
	
	m_edit_total = pData->usN;
	int i = 0;
	CString strValue;
	m_tab.DeleteAllItems();
	for (i = 0; i < pData->usN; i++)
	{
		strValue.Format("第%d个", i+1);
		m_tab.InsertItem(i, strValue);
		m_usPort[i] = pData->usPort[i];
	}
	
	m_edit_usport = m_usPort[0];
	
	UpdateData(FALSE);
	
}

void CDlgPreAfn0AF7Q::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_tab.GetCurSel();
	m_edit_usport = m_usPort[i];
	UpdateData(FALSE);
	*pResult = 0;

}

void CDlgPreAfn0AF7Q::OnChangeEditNumTotal() 
{
UpdateData(TRUE);


	if (m_edit_total == 0)
	{
		(CButton*)GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
	}
	else
	{
		(CButton*)GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
	}
	
	int i = 0;
	CString strValue;
	m_tab.DeleteAllItems();
	int nEnd = m_edit_total;
	for (i = 0; i < nEnd; i++)
	{
		strValue.Format("第%d个", i+1);
		m_tab.InsertItem(i, strValue);
	}
	
}
