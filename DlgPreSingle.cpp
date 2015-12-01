// DlgPreSingle.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreSingle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreSingle dialog


CDlgPreSingle::CDlgPreSingle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreSingle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreSingle)
	m_edit_value = 0.0;
	//}}AFX_DATA_INIT
	m_strTitle = "未设置窗口名称";
	m_bMaster = FALSE;
}


void CDlgPreSingle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreSingle)
	DDX_Text(pDX, IDC_EDIT_VALUE, m_edit_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreSingle, CDialog)
	//{{AFX_MSG_MAP(CDlgPreSingle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreSingle message handlers

BOOL CDlgPreSingle::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// 
	eMcDir eDir;
	eMcErr eRet;

	sMcmdInfor cmdinfor;
	eDir = (m_bMaster == TRUE) ? MC_DIR_M2S : MC_DIR_S2M;

	eRet = eMcGetCmdInfor(m_eCmd, eDir, &cmdinfor);
	
	m_strTitle.Format("%s预配 F%d %s", (m_bMaster == TRUE) ? "主站":"集中器", m_eCmd& 0xFF, cmdinfor.pName);

	SetWindowText(m_strTitle);
	
	// 获得预配值
	CNxConfig cfg;
	CString strValue;
	cfg.GetPreAfn0DFS(&strValue, m_eCmd, m_bMaster);

	if(strValue == "")
	{
		strValue = "0.0";
	}

	GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(strValue);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreSingle::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CNxConfig cfg;
	CString strValue;
	strValue.Format("%f", m_edit_value);
	cfg.SetPreAfn0DFS(&strValue, m_eCmd, m_bMaster, TRUE);
	CDialog::OnOK();
}
