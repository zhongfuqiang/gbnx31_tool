// DlgPreAfn04F7.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F7 dialog


CDlgPreAfn04F7::CDlgPreAfn04F7(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F7::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F7)
	m_edit_usMainPort = 0;
	m_edit_usBackPort = 0;
	m_edit_ucUsr = _T("");
	m_edit_ucPwd = _T("");
	m_edit_ucPort = 0;
	m_edit_ucApn = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F7)
	DDX_Control(pDX, IDC_IP_sMainIp, m_ip_main);
	DDX_Control(pDX, IDC_IP_sBackIp, m_ip_back);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_usMainPort, m_edit_usMainPort);
	DDX_Text(pDX, IDC_EDIT_usBackPort, m_edit_usBackPort);
	DDX_Text(pDX, IDC_EDIT_ucUsr, m_edit_ucUsr);
	DDX_Text(pDX, IDC_EDIT_ucPwd, m_edit_ucPwd);
	DDX_Text(pDX, IDC_EDIT_ucPort, m_edit_ucPort);
	DDX_Text(pDX, IDC_EDIT_ucAPN, m_edit_ucApn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F7, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F7 message handlers

void CDlgPreAfn04F7::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F7::OnInitDialog() 
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

void CDlgPreAfn04F7::GetCurValues()
{
	

	CNxConfig cfg;
	sMcAfn04f7 sData;
	CString strIp;
	CString strValue;


	cfg.GetPreAfn04F7(&sData, TRUE);
	

	m_edit_ucPort = sData.ucPort;
	m_edit_usBackPort = sData.usBackPort;
	m_edit_usMainPort = sData.usMainPort;

	strIp.Format("%d.%d.%d.%d", 
		sData.sMainIp.ip[0],
		sData.sMainIp.ip[1],
		sData.sMainIp.ip[2],
		sData.sMainIp.ip[3]);
	m_ip_main.SetWindowText(strIp);

	strIp.Format("%d.%d.%d.%d", 
		sData.sBackIp.ip[0],
		sData.sBackIp.ip[1],
		sData.sBackIp.ip[2],
		sData.sBackIp.ip[3]);
	m_ip_back.SetWindowText(strIp);

	#define  LEN_BUF 34
	char pStr[LEN_BUF];

	// apn
	memset(pStr, 0, LEN_BUF);
	memcpy(pStr, sData.ucAPN, 16);
	strValue.Format("%s", pStr);
	m_edit_ucApn = strValue;
	
	// usr
	memset(pStr, 0, LEN_BUF);
	memcpy(pStr, sData.ucUsr, 32);
	strValue.Format("%s", pStr);
	m_edit_ucUsr = strValue;
	
	// pwd
	memset(pStr, 0, LEN_BUF);
	memcpy(pStr, sData.ucPwd, 32);
	strValue.Format("%s", pStr);
	m_edit_ucPwd = strValue;	


	UpdateData(FALSE);

}

void CDlgPreAfn04F7::SetNewValues()
{
	UpdateData();

	CNxConfig cfg;
	CString strIp;
	sMcAfn04f7 sData;


	sData.ucPort     = m_edit_ucPort;
	sData.usMainPort = m_edit_usMainPort;
	sData.usBackPort = m_edit_usBackPort;
	// main ip
	m_ip_main.GetWindowText(strIp);
	sData.sMainIp.eVersion = MC_IP_V4;
	sData.sMainIp.ip[0] = cfg.GetIpNum(strIp, 0);
	sData.sMainIp.ip[1] = cfg.GetIpNum(strIp, 1);
	sData.sMainIp.ip[2] = cfg.GetIpNum(strIp, 2);
	sData.sMainIp.ip[3] = cfg.GetIpNum(strIp, 3);

	// back ip
	m_ip_back.GetWindowText(strIp);
	sData.sBackIp.eVersion = MC_IP_V4;
	sData.sBackIp.ip[0] = cfg.GetIpNum(strIp, 0);
	sData.sBackIp.ip[1] = cfg.GetIpNum(strIp, 1);
	sData.sBackIp.ip[2] = cfg.GetIpNum(strIp, 2);
	sData.sBackIp.ip[3] = cfg.GetIpNum(strIp, 3);

	// apn
	int len = 0;
	len = m_edit_ucApn.GetLength();
	len = len > 16 ? 16: len;
	memset(sData.ucAPN, 0, 16);
	memcpy(sData.ucAPN, m_edit_ucApn.GetBuffer(len), len);
	m_edit_ucApn.ReleaseBuffer();

	// usr
	len = m_edit_ucUsr.GetLength();
	len = len ? 32 : len;
	memset(sData.ucUsr, 0, 32);
	memcpy(sData.ucUsr, m_edit_ucUsr.GetBuffer(len), len);
	m_edit_ucUsr.ReleaseBuffer();

	// pwd
	len = m_edit_ucPwd.GetLength();
	len = len ? 32 : len;
	memset(sData.ucPwd, 0, 32);
	memcpy(sData.ucPwd, m_edit_ucPwd.GetBuffer(len), len);
	m_edit_ucPwd.ReleaseBuffer();


	cfg.SetPreAfn04F7(&sData, TRUE, TRUE);
}
