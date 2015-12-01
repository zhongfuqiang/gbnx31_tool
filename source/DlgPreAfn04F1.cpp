// DlgPreAfn04F1.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F1 dialog


CDlgPreAfn04F1::CDlgPreAfn04F1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F1)
	m_ucRts = 0;
	m_ucRtm = 0;
	m_usTmWaitTimeoutS = 0;
	m_ucReSendTimes = 0;
	m_ucHearBeat = 0;
	m_bAsk1 = -1;
	m_bAsk2 = -1;
	m_bAsk3 = -1;
	//}}AFX_DATA_INIT
}


void CDlgPreAfn04F1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F1)
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_RTS, m_ucRts);
	DDV_MinMaxInt(pDX, m_ucRts, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RTM, m_ucRtm);
	DDV_MinMaxInt(pDX, m_ucRtm, 0, 255);
	DDX_Text(pDX, IDC_EDIT_TM_WAIT_TIMEOUT, m_usTmWaitTimeoutS);
	DDV_MinMaxInt(pDX, m_usTmWaitTimeoutS, 0, 4095);
	DDX_Text(pDX, IDC_EDIT_RESENDTIMES, m_ucReSendTimes);
	DDV_MinMaxInt(pDX, m_ucReSendTimes, 0, 3);
	DDX_Text(pDX, IDC_EDIT_HEART_BEAT, m_ucHearBeat);
	DDV_MinMaxInt(pDX, m_ucHearBeat, 0, 255);
	DDX_Radio(pDX, IDC_RADIO_ASK1_PERMIT, m_bAsk1);
	DDX_Radio(pDX, IDC_RADIO_ASK2_PERMIT, m_bAsk2);
	DDX_Radio(pDX, IDC_RADIO_ASK3_PERMIT, m_bAsk3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F1, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F1 message handlers

void CDlgPreAfn04F1::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}


BOOL CDlgPreAfn04F1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetCurValues();
	SetWindowText(m_strWindowText);
	
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


void CDlgPreAfn04F1::setTitle(CString strTitle)
{
	m_strWindowText = strTitle;
}

// 读取注册表中当前值，并显示到控件
void CDlgPreAfn04F1::GetCurValues()
{
	/* 原3761
	CNxConfig cfg;
	sMtAfn04F1 sValues;
	if (m_bPreMaster == TRUE)
	{
		cfg.GetMstPreAfn04F1(&sValues);
	}
	else
	{
		cfg.GetTmlPreAfn04F1(&sValues);
	}
	

	m_ucRts = sValues.ucRTS;
	m_ucRtm = sValues.ucRTM;
	m_ucReSendTimes = sValues.ucReSendTimes;
	m_ucHearBeat    = sValues.ucHeartBeat;
	m_usTmWaitTimeoutS = sValues.usTmWaitTimeoutS;

	m_bAsk1 = sValues.bAutoReportAsk_1 ==TRUE ? 0:1;
	m_bAsk2 = sValues.bAutoReportAsk_2 ==TRUE ? 0:1;
	m_bAsk3 = sValues.bAutoReportAsk_3 ==TRUE ? 0:1;

	UpdateData(FALSE);
	*/

	CNxConfig cfg;
	sMcAfn04f1 sValues;
	cfg.GetPreAfn04F1(&sValues, TRUE);
	
	
	//m_ucRts = sValues.bPermitEv;
	m_ucRtm = sValues.ucPermitDelayM;
	m_ucReSendTimes = sValues.ucReSendTimes;
	m_ucHearBeat    = sValues.ucHeartBeat;
	m_usTmWaitTimeoutS = sValues.usWaitTimeoutS;
	
	m_bAsk1 = sValues.bPermitRt ==TRUE ? 0:1;
	m_bAsk2 = sValues.bPermitTk ==TRUE ? 0:1;
	m_bAsk3 = sValues.bPermitEv ==TRUE ? 0:1;
	
	UpdateData(FALSE);
}

void CDlgPreAfn04F1::SetNewValues()
{
    CNxConfig cfg;
	sMcAfn04f1 sValues;
	UpdateData(TRUE);

	//sValues.ucRTM = m_ucRtm;
	sValues.ucPermitDelayM = m_ucRtm;
	sValues.ucReSendTimes = m_ucReSendTimes;
	sValues.ucHeartBeat = m_ucHearBeat;
	sValues.usWaitTimeoutS = m_usTmWaitTimeoutS;
	sValues.bPermitRt = (m_bAsk1 == 0) ? TRUE: FALSE;
	sValues.bPermitTk = (m_bAsk2 == 0) ? TRUE: FALSE;
	sValues.bPermitEv = (m_bAsk3 == 0) ? TRUE: FALSE;
	
	cfg.SetPreAfn04F1(&sValues, TRUE, TRUE);
	
}
