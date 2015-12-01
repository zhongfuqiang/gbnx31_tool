// DlgPreAfn04F49.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F49.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F49 dialog


CDlgPreAfn04F49::CDlgPreAfn04F49(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F49::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F49)
	m_edit_pn = 0;
	m_edit_frez_ucTimes = 0;
	m_edit_Frez_usPeriod = 0;
	m_edit_rept_ucPeriod = 0;
	//}}AFX_DATA_INIT


	m_strFrezUint[FREZ_MONTH] = "月";
	m_strFrezUint[FREZ_DAY] = "日";
	m_strFrezUint[FREZ_HOUR] = "时";
	m_strFrezUint[FREZ_MIN] = "分";
	m_strFrezUint[FREZ_SEC] = "秒";
	m_strFrezUint[FREZ_MS] = "毫秒";


	m_strReptUint[REPT_MONTH] = "月";
	m_strReptUint[REPT_DAY] = "日";
	m_strReptUint[REPT_HOUR] = "时";
	m_strReptUint[REPT_MIN] = "分";



	sMcmdInfor infor;
	eMcErr eRet = MC_OK; 
	eMcmd  eCmd ;

	int i = 0;
	int j = 0;
	int nFn = 0;
	int nStart, nEnd;
	nStart = (int)MCMD_AFN_D_F1_CLOCK;
	nEnd   = (int)MCMD_AFN_D_F233_NELC_VALUE;

	for (i = nStart; i <= nEnd; i++)
	{
		eCmd = (eMcmd)i;
		eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &infor);
		if (MC_OK == eRet)
		{
			m_cmdName[j].eCmd = eCmd;
			nFn = i & 0xFF;
			m_cmdName[j].sName.Format("F%d %s", nFn, infor.pName);
			j++;
		}
	}

}


void CDlgPreAfn04F49::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F49)
	DDX_Control(pDX, IDC_DATETIMEPICKER_sTimeRprt_Time, m_time_rept);
	DDX_Control(pDX, IDC_DATETIMEPICKER_sTimeRprt_Date, m_date_rept);
	DDX_Control(pDX, IDC_CMB_REPT_UNIT, m_cmb_rept_unit);
	DDX_Control(pDX, IDC_CMB_FREZ_UNIT, m_cmb_frez_uint);
	DDX_Control(pDX, IDC_DATETIMEPICKER_sTimeFrez_Time, m_time_frez);
	DDX_Control(pDX, IDC_DATETIMEPICKER_sTimeFrez_Date, m_date_frez);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_CMB_FN_ADD, m_cmb_fn_add);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_EDIT_PN, m_edit_pn);
	DDV_MinMaxUInt(pDX, m_edit_pn, 0, 2040);
	DDX_Text(pDX, IDC_EDIT_Frez_ucTimes, m_edit_frez_ucTimes);
	DDX_Text(pDX, IDC_EDIT_Frez_usPeriod, m_edit_Frez_usPeriod);
	DDX_Text(pDX, IDC_EDIT_Rept_ucPeriod, m_edit_rept_ucPeriod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F49, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F49)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_CBN_EDITCHANGE(IDC_CMB_FN_ADD, OnEditchangeCmbFnAdd)
	ON_CBN_SELENDOK(IDC_CMB_FN_ADD, OnSelendokCmbFnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F49 message handlers

BOOL CDlgPreAfn04F49::OnInitDialog() 
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



	int i = 0;
	for (i = 0; i < INDEX_MCMD_MAX; i++)
	{
		m_cmb_fn_add.InsertString(i, m_cmdName[i].sName);
	}
	
	m_cmb_fn_add.SetCurSel(0);
	
	m_list.SetHeadings(_T("数据标识,300;测量点号,80"));
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	
	
	for (i = 0; i < FREZ_MAX; i++)
	{
		m_cmb_frez_uint.InsertString(i, m_strFrezUint[i]);
	}

	for (i = 0; i < REPT_MAX; i++)
	{
		m_cmb_rept_unit.InsertString(i, m_strReptUint[i]);
	}


	GetCurValues();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F49::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

void CDlgPreAfn04F49::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int iSel;
	sMcmdPn cmdPn;
	iSel = m_cmb_fn_add.GetCurSel();
	cmdPn.eCmd = m_cmdName[iSel].eCmd;
	cmdPn.usPn = m_edit_pn;

	
	BOOL bAddOk;
	bAddOk = AddCmdPnList(cmdPn);
	
	if (bAddOk == TRUE)
	{
		CString strPn;
		int item = 0;
		UINT8 ucR,ucG,ucB;
	
		ucR = cmdPn.eCmd & 0xFF;
		//ucG = ucR;
		//ucB = ucR;
		
		ucG = rand()%50;
		ucB = rand()%50;

		strPn.Format("%d", m_edit_pn);
		item = m_list.AddItem(m_cmdName[iSel].sName, strPn);

		m_list.SetItemColor(item,0,RGB(ucR,ucG,ucB),RGB(255,255,255));
		m_list.SetItemColor(item,1,RGB(ucR,ucG,ucB),RGB(255,255,255));
	}
}


BOOL CDlgPreAfn04F49::AddCmdPnList( sMcmdPn cmdPn )
{
	int i, count;
	CString str;
	int Pn = 0;
	int fn = 0;
	int nBlack;
	CString strFn;
	CString strPn;
	CString strFnNum;
	count = m_list.GetItemCount();
	for (i = 0; i < count; i++)
	{
		strFn = m_list.GetItemText(i, 0);
		strPn = m_list.GetItemText(i, 1);
		nBlack = strFn.Find(" ", 2);
		
		strFnNum = strFn.Left(nBlack);
		strFnNum.Replace(" ", "");
		strFnNum.Replace("F", "");
		strPn.Replace(" ", "");
		
		
		fn = atoi(strFnNum.GetBuffer(strFnNum.GetLength()));
		strFnNum.ReleaseBuffer();
		Pn = atoi(strPn.GetBuffer(strPn.GetLength()));
	    strPn.ReleaseBuffer();

		if((cmdPn.eCmd & 0xFF) == fn && Pn == cmdPn.usPn)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

void CDlgPreAfn04F49::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	CList<int, int> list_del;
	POSITION pos;
	int index;
	pos = m_list.GetFirstSelectedItemPosition();
	int nSel = 0;
	while(nSel!= -1)
	{
		nSel = m_list.GetNextSelectedItem(pos);
		list_del.AddHead(nSel);
	}

	POSITION posList;
	posList = list_del.GetHeadPosition();
	int x;
	while (posList)
	{
		x = list_del.GetAt(posList);
		index = list_del.GetNext(posList);

		if (x!= -1)
		{
			m_list.DeleteItem(x);
		}
	}
	
}

void CDlgPreAfn04F49::GetCurValues()
{
	CNxConfig cfg;
	#define  BUF_SIZE 512
	UINT8 buf[BUF_SIZE];

	memset(buf, 0, BUF_SIZE);

	sMcAfn04f49 *psAfn04f49;
	psAfn04f49 = (sMcAfn04f49*)buf;
	
	cfg.GetPreAfn04F49(psAfn04f49, TRUE);

		
	// 上报时间
	SYSTEMTIME sTimeFrez;

	sTimeFrez.wYear  = psAfn04f49->sTimeFrez.ucYY + 2000;
	sTimeFrez.wMonth = psAfn04f49->sTimeFrez.ucMM;
	sTimeFrez.wDay   = psAfn04f49->sTimeFrez.ucDD;
	sTimeFrez.wHour   =  psAfn04f49->sTimeFrez.ucHH;
	sTimeFrez.wMinute  = psAfn04f49->sTimeFrez.ucmm;
	sTimeFrez.wSecond   = psAfn04f49->sTimeFrez.ucss;
	sTimeFrez.wDayOfWeek  = psAfn04f49->sTimeFrez.ucWW;
	sTimeFrez.wMilliseconds = 0;

	m_date_frez.SetTime(&sTimeFrez);
	m_time_frez.SetTime(&sTimeFrez);



	// 冻结时间
	sTimeFrez.wYear  = psAfn04f49->sTimeRprt.ucYY + 2000;
	sTimeFrez.wMonth = psAfn04f49->sTimeRprt.ucMM;
	sTimeFrez.wDay   = psAfn04f49->sTimeRprt.ucDD;
	sTimeFrez.wHour   =  psAfn04f49->sTimeRprt.ucHH;
	sTimeFrez.wMinute  = psAfn04f49->sTimeRprt.ucmm;
	sTimeFrez.wSecond   = psAfn04f49->sTimeRprt.ucss;
	sTimeFrez.wDayOfWeek  = psAfn04f49->sTimeRprt.ucWW;
	sTimeFrez.wMilliseconds = 0;
	
	m_date_rept.SetTime(&sTimeFrez);
	m_time_rept.SetTime(&sTimeFrez);

	m_edit_frez_ucTimes = psAfn04f49->sFreez.ucTimes;
	m_edit_Frez_usPeriod = psAfn04f49->sFreez.usPeriod;
	m_edit_rept_ucPeriod = psAfn04f49->ucPeriodRpt;

	// 定时上报周期单位
	eUnitRpt_index eRept;
	switch (psAfn04f49->eUnitRpt)
	{
	case MC_PUNT_MONTH:
		eRept = REPT_MONTH;
		break;

	case MC_PUNT_DAY:
		eRept = REPT_DAY;
		break;

	case MC_PUNT_HOUR:
		eRept = REPT_HOUR;
		break;

	case MC_PUNT_MIN:
		eRept = REPT_MIN;
		break;

	default:
		break;
	}

	m_cmb_rept_unit.SetCurSel(eRept);
	
	// 定时冻结周期单位
	eUnitFrez_index eFrez;
	switch(psAfn04f49->sFreez.eUnit)
	{
	case MC_PUNT_MONTH:
		eFrez = FREZ_MONTH;
		break;

	case MC_PUNT_DAY:
		eFrez = FREZ_DAY;
		break;


	case MC_PUNT_HOUR:
		eFrez = FREZ_HOUR;
		break;
		
	case MC_PUNT_MIN:
		eFrez = FREZ_MIN;
		break;
		
		
	case MC_PUNT_SEC:
		eFrez = FREZ_SEC;
		break;
		
	case MC_PUNT_MS:
		eFrez = FREZ_MS;
		break;
	default:
		break;
	}


	m_cmb_frez_uint.SetCurSel(eFrez);
	
	
	
	
	// 数据单元标识
	int i = 0;
	eMcErr eRet;
	CString strFn, strPn;
	int nFn, item;
	eMcmd eCmd;
	sMcmdInfor infor;
	UINT8 ucR, ucG, ucB;
	for (i = 0; i < psAfn04f49->uCmdPnNum; i++)
	{
		eCmd = psAfn04f49->sCmdPn[i].eCmd;
		eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &infor);
		if (MC_OK == eRet)
		{
			nFn = eCmd & 0xFF;
			strFn.Format("F%d %s", nFn, infor.pName);
			strPn.Format("%d", psAfn04f49->sCmdPn[i].usPn);
			
			item = m_list.AddItem(strFn, strPn);
			
			ucR = eCmd & 0xFF;
			
			
			ucG = rand()%50;
			ucB = rand()%50;
			m_list.SetItemColor(item,0,RGB(ucR,ucG,ucB),RGB(255,255,255));
			m_list.SetItemColor(item,1,RGB(ucR,ucG,ucB),RGB(255,255,255));
		}
	}

	(CButton*)GetDlgItem(IDC_EDIT_PN)->EnableWindow(FALSE);

	UpdateData(FALSE);
}

void CDlgPreAfn04F49::SetNewValues()
{
	UpdateData();
	
	CNxConfig cfg;
	#define  BUF_SIZE 512
	UINT8 buf[BUF_SIZE];

	memset(buf, 0, BUF_SIZE);

	sMcAfn04f49 *psAfn04f49;
	psAfn04f49 = (sMcAfn04f49*)buf;
	

	
	// 上报时间
	SYSTEMTIME sTimeFrez;

	m_date_frez.GetTime(&sTimeFrez);


	psAfn04f49->sTimeFrez.ucYY = sTimeFrez.wYear % 100;
    psAfn04f49->sTimeFrez.ucMM = (UINT8)sTimeFrez.wMonth;
	psAfn04f49->sTimeFrez.ucDD = (UINT8)sTimeFrez.wDay;
		psAfn04f49->sTimeFrez.ucWW = (UINT8)sTimeFrez.wDayOfWeek;

	m_time_frez.GetTime(&sTimeFrez);

	psAfn04f49->sTimeFrez.ucHH = (UINT8)sTimeFrez.wHour;
	psAfn04f49->sTimeFrez.ucmm = (UINT8)sTimeFrez.wMinute;
    psAfn04f49->sTimeFrez.ucss = (UINT8)sTimeFrez.wSecond;



	// 冻结时间
	m_date_rept.GetTime(&sTimeFrez);


	psAfn04f49->sTimeRprt.ucYY = sTimeFrez.wYear % 100;
    psAfn04f49->sTimeRprt.ucMM = (UINT8)sTimeFrez.wMonth;
	psAfn04f49->sTimeRprt.ucDD = (UINT8)sTimeFrez.wDay;
	psAfn04f49->sTimeRprt.ucWW = (UINT8)sTimeFrez.wDayOfWeek;

	m_time_rept.GetTime(&sTimeFrez);
	psAfn04f49->sTimeRprt.ucHH = (UINT8)sTimeFrez.wHour;
	psAfn04f49->sTimeRprt.ucmm = (UINT8)sTimeFrez.wMinute;
    psAfn04f49->sTimeRprt.ucss = (UINT8)sTimeFrez.wSecond;



	psAfn04f49->sFreez.ucTimes  = m_edit_frez_ucTimes;
	psAfn04f49->sFreez.usPeriod = m_edit_Frez_usPeriod;
	psAfn04f49->ucPeriodRpt     = m_edit_rept_ucPeriod;

	// 定时上报周期单位
	
	
	eUnitRpt_index eRept;
	eRept = (eUnitRpt_index)m_cmb_rept_unit.GetCurSel();
	switch (eRept)
	{
	case REPT_MONTH:
		psAfn04f49->eUnitRpt = MC_PUNT_MONTH;
		break;
		
	case REPT_DAY:
		psAfn04f49->eUnitRpt = MC_PUNT_DAY;
		break;
		
	case REPT_HOUR:
		psAfn04f49->eUnitRpt = MC_PUNT_HOUR;
		break;
		
	case REPT_MIN:
		psAfn04f49->eUnitRpt = MC_PUNT_MIN;
		break;

	default:
		break;
	}

	
	// 定时冻结周期单位
	eUnitFrez_index eFrez;
	eFrez = (eUnitFrez_index)m_cmb_frez_uint.GetCurSel();
	switch(eFrez)
	{
	case FREZ_MONTH:
		psAfn04f49->sFreez.eUnit = MC_PUNT_MONTH;
		break;
		
	case FREZ_DAY:
		psAfn04f49->sFreez.eUnit = MC_PUNT_DAY;
		break;
		
		
	case FREZ_HOUR:
		psAfn04f49->sFreez.eUnit = MC_PUNT_HOUR;
		break;
		
	case FREZ_MIN:
		
		psAfn04f49->sFreez.eUnit = MC_PUNT_MIN;
		break;
		
		
	case FREZ_SEC:
		psAfn04f49->sFreez.eUnit = MC_PUNT_SEC;
		break;
		
	case FREZ_MS:
		psAfn04f49->sFreez.eUnit = MC_PUNT_MS;
		break;
	default:
		break;
	}

	// 数据单元标识
	int i = 0, nBlack, fn, Pn;
	int count;
	CString strFn, strPn, strFnNum;
		eMcmd eCmd;

	count = m_list.GetItemCount();
	for (i = 0; i < count; i++)
	{
		strFn = m_list.GetItemText(i, 0);
		strPn = m_list.GetItemText(i, 1);
		nBlack = strFn.Find(" ", 2);
		
		strFnNum = strFn.Left(nBlack);
		strFnNum.Replace(" ", "");
		strFnNum.Replace("F", "");
		strPn.Replace(" ", "");
		
		
		fn = atoi(strFnNum.GetBuffer(strFnNum.GetLength()));
		strFnNum.ReleaseBuffer();
		Pn = atoi(strPn.GetBuffer(strPn.GetLength()));
		strPn.ReleaseBuffer();
		
		
		eCmd = (eMcmd)(fn | (MC_AFN_13_ASKR << 8));
		
		
		psAfn04f49->sCmdPn[i].eCmd = eCmd;
		psAfn04f49->sCmdPn[i].usPn = Pn;
	}
	
	psAfn04f49->uCmdPnNum = i;
	
	
	cfg.SetPreAfn04F49(psAfn04f49, TRUE, TRUE);
	

}

void CDlgPreAfn04F49::OnEditchangeCmbFnAdd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgPreAfn04F49::OnSelendokCmbFnAdd() 
{
	UpdateData();
	int iSel;
	eMcmd eCmd;
	iSel = m_cmb_fn_add.GetCurSel();
	eCmd = m_cmdName[iSel].eCmd;
	
	eMcErr eRet;
	sMcmdInfor infor;
	eRet = eMcGetCmdInfor(eCmd, MC_DIR_M2S, &infor);
	if (MC_OK == eRet)
	{
		if (infor.ePn == MC_PN_P0)
		{
			m_edit_pn = 0;
			(CButton*)GetDlgItem(IDC_EDIT_PN)->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_STATIC_PN))->SetWindowText("0 集中器");
		}
		else
		{
			if (m_edit_pn == 0)
			{
				m_edit_pn = 1;
			}
			
			(CButton*)GetDlgItem(IDC_EDIT_PN)->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_STATIC_PN))->SetWindowText("1~2040");
		}

		UpdateData(FALSE);
	}
	
	
}
