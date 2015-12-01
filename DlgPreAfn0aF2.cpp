// DlgPreAfn0aF2.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn0aF2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn0aF2 dialog


CDlgPreAfn0aF2::CDlgPreAfn0aF2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn0aF2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn0aF2)
	m_edit_total = 0;
	m_edit_id = 0;
	//}}AFX_DATA_INIT
	memset(m_ucId, 0, sizeof(m_ucId));
}


void CDlgPreAfn0aF2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn0aF2)
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Text(pDX, IDC_EDIT_NUM_TOTAL, m_edit_total);
	DDX_Text(pDX, IDC_EDIT_ID, m_edit_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn0aF2, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn0aF2)
	ON_EN_CHANGE(IDC_EDIT_NUM_TOTAL, OnChangeEditNumTotal)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_EN_CHANGE(IDC_EDIT_ID, OnChangeEditId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn0aF2 message handlers

void CDlgPreAfn0aF2::OnOK() 
{
	// TODO: Add extra validation here
	SetNew();
	CDialog::OnOK();
}

BOOL CDlgPreAfn0aF2::OnInitDialog() 
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

void CDlgPreAfn0aF2::OnChangeEditNumTotal() 
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

void CDlgPreAfn0aF2::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i = m_tab.GetCurSel();
	m_edit_id = m_ucId[i];
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgPreAfn0aF2::GetCur()
{
	char buf[128] = {0};
	sMcAfn11f2q *pData = (sMcAfn11f2q*)buf;

	CNxConfig cfg;
	cfg.GetPreAfn0aF2q(pData, TRUE);

	m_edit_total = pData->ucN;
	int i = 0;
	CString strValue;
	m_tab.DeleteAllItems();
	for (i = 0; i < pData->ucN; i++)
	{
		strValue.Format("第%d个", i+1);
		m_tab.InsertItem(i, strValue);
		m_ucId[i] = pData->ucID[i];
	}
	
	m_edit_id = m_ucId[0];
	
	UpdateData(FALSE);
}

void CDlgPreAfn0aF2::OnChangeEditId() 
{
	UpdateData();
	int i = m_tab.GetCurSel();
	m_ucId[i] = m_edit_id;
	
}

void CDlgPreAfn0aF2::SetNew()
{
	UpdateData();
	char buf[128] = {0};
	sMcAfn11f2q *pData = (sMcAfn11f2q*)buf;
	
	CNxConfig cfg;


	pData->ucN = m_edit_total;
	int i = 0;
	for (i = 0; i < pData->ucN; i++)
	{
		pData->ucID[i] = m_ucId[i];
	}

	cfg.SetPreAfn0aF2q(pData, TRUE, TRUE);

}
