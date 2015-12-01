// TabDlgPack.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "TabDlgPack.h"
#include "NxMasterDlg.h"
#include "DlgPreAfn04F1.h"
#include "DlgPreAfn04F33.h"
#include "DlgPreA00F1.h"
#include "DlgPreAfn04F2.h"
#include "DlgPreAfn04F3.h"
#include "DlgPreAfn04F4.h"
#include "DlgPreAfn04F5.h"
#include "DlgPreAfn04F6.h"
#include "DlgPreAfn04F7.h"
#include "DlgPreAfn04F9.h"
#include "DlgPreAfn04F10.h"
#include "DlgPreAfn04F17.h"
#include "DlgPreAfn04F25_33.h"
#include "DlgPreAfn04F26.h"
#include "DlgPreAfn04F27.h"
#include "DlgPreAfn04F28.h"
#include "DlgPreAfn04F29.h"
#include "DlgPreAfn04F30.h"
#include "DlgPreAfn04F34.h"
#include "DlgPreAfn04F35.h"
#include "DlgPreAfn04F49.h"
#include "DlgPreAfn0aF2.h"
#include "DlgPrePn.h"
#include "DlgPreAfn0AF7Q.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPack dialog

#define AUTO_TIME_ID 100  // 自动对时定时器

CTabDlgPack::CTabDlgPack(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlgPack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabDlgPack)
	m_edit_ec2 = 0;
	m_edit_ec1 = 0;
	m_edit_mst_addr = 0;
	m_edit_tml_addr = 0;
	m_edit_zone_code = 0;
	m_edit_pw = _T("");
	m_edit_tp_day = _T("");
	m_edit_tp_hour = _T("");
	m_edit_tp_minute = _T("");
	m_edit_tp_second = _T("");
	m_edit_pfc = 0;
	m_ucPermitDelayMinutes = 255;
	m_edit_auto_response_delay = 0;
	m_edit_pseq = 0;
	m_pNxMstDlg = NULL;
	m_edit_rseq = 0;
	//}}AFX_DATA_INIT


}


void CTabDlgPack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDlgPack)
	DDX_Control(pDX, IDC_CHECK_AUTO, m_check_auto);
	DDX_Control(pDX, IDC_CHECK_TEXT, m_check_text);
	DDX_Control(pDX, IDC_CHECK_SEND_INSTANT, m_check_send_instant);
	DDX_Control(pDX, IDC_CHECK_INTO_SEND, m_check_into_send);
	DDX_Control(pDX, IDC_CHECK_INTO_TASK, m_check_into_task);
	DDX_Control(pDX, IDC_CHECK_TP_AUTO, m_check_auto_tp);
	DDX_Control(pDX, IDC_CHECK_TEAM, m_check_team);
	DDX_Control(pDX, IDC_STATIC_DIR_S2M, m_static_s2m);
	DDX_Control(pDX, IDC_STATIC_DIR_RES, m_static_res);
	DDX_Control(pDX, IDC_STATIC_DIR_M2S, m_static_m2s);
	DDX_Control(pDX, ID_BTN_GET_CMD, m_btn_get_cmd);
	DDX_Control(pDX, IDC_EDIT_CMD_RESULT, m_edit_cmd_result);
	DDX_Control(pDX, IDC_LIST_FN, m_fnList);
	DDX_Control(pDX, IDC_TREE_FN, m_fnTree);
	DDX_Control(pDX, IDC_COMBO_AFN, m_combo_afn);
	DDX_Text(pDX, IDC_EDIT_EC2, m_edit_ec2);
	DDV_MinMaxInt(pDX, m_edit_ec2, 0, 255);
	DDX_Text(pDX, IDC_EDIT_EC1, m_edit_ec1);
	DDV_MinMaxInt(pDX, m_edit_ec1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_MST_ADDR, m_edit_mst_addr);
	DDX_Text(pDX, IDC_EDIT_TML_ADDR, m_edit_tml_addr);
	DDX_Text(pDX, IDC_EDIT_ZONE_CODE, m_edit_zone_code);
	DDX_Text(pDX, IDC_EDIT_PW, m_edit_pw);
	DDX_Text(pDX, IDC_EDITTP_DAY, m_edit_tp_day);
	DDX_Text(pDX, IDC_EDIT_TP_HOUR, m_edit_tp_hour);
	DDX_Text(pDX, IDC_EDIT_TP_MINUTE, m_edit_tp_minute);
	DDX_Text(pDX, IDC_EDIT_TP_SECOND, m_edit_tp_second);
	DDX_Text(pDX, IDC_EDIT_PFC, m_edit_pfc);
	DDX_Text(pDX, IDC_EDIT_PermitDelayMinutes, m_ucPermitDelayMinutes);
	DDV_MinMaxInt(pDX, m_ucPermitDelayMinutes, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RES_DELAY, m_edit_auto_response_delay);
	DDX_Text(pDX, IDC_EDIT_PSEQ, m_edit_pseq);
	DDV_MinMaxInt(pDX, m_edit_pseq, 0, 31);
	DDX_Text(pDX, IDC_EDIT_RSEQ, m_edit_rseq);
	DDV_MinMaxInt(pDX, m_edit_rseq, 0, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabDlgPack, CDialog)
	//{{AFX_MSG_MAP(CTabDlgPack)
	ON_CBN_SELCHANGE(IDC_COMBO_AFN, OnSelchangeComboAfn)
	ON_NOTIFY(NM_RDBLCLK, IDC_TREE_FN, OnRdblclkTreeFn)
	ON_NOTIFY(NM_CLICK, IDC_TREE_FN, OnClickTreeFn)
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_BTN_GET_CMD, OnBtnGetCmd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_INTO_SEND, OnCheckIntoSend)
	ON_BN_CLICKED(IDC_CHECK_TP_AUTO, OnCheckTpAuto)
	ON_EN_CHANGE(IDC_EDIT_TML_ADDR, OnChangeEditTmlAddr)
	ON_EN_CHANGE(IDC_EDIT_ZONE_CODE, OnChangeEditZoneCode)
	ON_EN_CHANGE(IDC_EDIT_MST_ADDR, OnChangeEditMstAddr)
	ON_BN_CLICKED(IDC_CHECK_TEAM, OnCheckTeam)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_FN, OnRclickTreeFn)
	ON_COMMAND(IDM_ITEM_CHECK, OnItemCheck)
	ON_COMMAND(IDM_ITEM_UNCHECK, OnItemUncheck)
	ON_COMMAND(IDM_SET_PRE, OnSetPre)
	ON_COMMAND(IDM_SET_PN, OnSetPrePn)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPack message handlers



BOOL CTabDlgPack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int index = 0;
	m_strName[INDEX_AFN_00_CONF] = STR_AFN_00_CONF;
	m_strName[INDEX_AFN_01_RSET] = STR_AFN_01_RSET;
	m_strName[INDEX_AFN_02_LINK] = STR_AFN_02_LINK;
	//m_strName[INDEX_AFN_03_RELY] = STR_AFN_03_RELY;
	m_strName[INDEX_AFN_04_SETP] = STR_AFN_04_SETP;
	m_strName[INDEX_AFN_05_CTRL] = STR_AFN_05_CTRL;
	m_strName[INDEX_AFN_06_AUTH] = STR_AFN_06_AUTH;
	m_strName[INDEX_AFN_08_CASC] = STR_AFN_08_CASC;
	//m_strName[INDEX_AFN_09_CFIG] = STR_AFN_09_CFIG;
	m_strName[INDEX_AFN_0A_GETP] = STR_AFN_0A_GETP;
	//m_strName[INDEX_AFN_0B_ASKT] = STR_AFN_0B_ASKT;
	m_strName[INDEX_AFN_0C_ASKT] = STR_AFN_0C_ASKT;
	m_strName[INDEX_AFN_0D_ASKR] = STR_AFN_0D_ASKR;
	m_strName[INDEX_AFN_0E_ASKE] = STR_AFN_0E_ASKE;
	m_strName[INDEX_AFN_0F_FILE] = STR_AFN_0F_FILE;
	m_strName[INDEX_AFN_10_DATA] = STR_AFN_10_DATA;

	// TODO: Add extra initialization here
	int i = 0;
	int j = 0;
	for (i = 0; i < AFN_11_MAX; i++)
	{
		if(m_strName[i] != "")
		{
			m_combo_afn.InsertString(j++, m_strName[i]);
		}
	}
	
	
	m_combo_afn.SetCurSel(0);
	BuildFnTree(INDEX_AFN_00_CONF);
	setPosCtrls();
	ShowPreInfor(TRUE);
	m_check_text.SetCheck(TRUE);
	SetTimer(AUTO_TIME_ID,100, NULL);
	m_check_auto_tp.SetCheck(TRUE);
	m_check_send_instant.SetCheck(TRUE);
	m_check_into_send.SetCheck(TRUE);
	m_check_auto.EnableWindow(FALSE);
	m_edit_auto_response_delay = 0;
	showEcPwTp(TRUE);
	m_fnTree.SetCheck(m_fnTree.GetFirstVisibleItem(), TRUE);
	

	// 设置生成命令按钮样式

	m_btn_get_cmd.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
//	m_btn_get_cmd.SetIcon(IDI_ICON20, IDI_ICON6);
	m_btn_get_cmd.SetIcon(IDI_ICON20);
	m_btn_get_cmd.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_get_cmd.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));







	


	return TRUE;  // return TRUE u;nless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabDlgPack::OnSelchangeComboAfn() 
{
	// TODO: Add your control notification handler code here
	m_cur_index = m_combo_afn.GetCurSel();

	m_fnTree.DeleteAllItems();
	BuildFnTree(m_cur_index);
	eMtDir	eDir = (m_pNxMstDlg->m_bMaster == TRUE) ? MT_DIR_M2S : MT_DIR_S2M;
	showEcPwTp(m_pNxMstDlg->m_bMaster);
	showCmdTypes(m_cur_index);
}

void CTabDlgPack::showCmdTypes(int index)
{
	CString strM2S,strS2M,strRes;
//	CNxRuler ruler;
	eMtAFN eAfn;
	switch(index)
	{
	case INDEX_AFN_00_CONF:
		strM2S = "有";
		strS2M = "有";
		strRes = "无答复";
		break;
	case INDEX_AFN_01_RSET:
		strM2S = "有";
		strS2M = "无";
		strRes = "AFN 00";
		break;
	case INDEX_AFN_02_LINK:
		strM2S = "有";
		strS2M = "有";
		strRes = "AFN 00";
		break;
/*
	case INDEX_AFN_03_RELY:
		strM2S =  "有";
		strS2M = "无";
		strRes = "无答复";
		break;
*/
	case INDEX_AFN_04_SETP:
		strM2S = "有";
		strS2M = "无";
		strRes = "AFN 00";
		break;
	case INDEX_AFN_05_CTRL:
		strM2S =  "有";
		strS2M = "无";
		strRes = "AFN 00";
		break;
	case INDEX_AFN_06_AUTH:
		strM2S = "有";
		strS2M = "有";
		strRes = "AFN 06";
		break;
		/*
	case INDEX_AFN_09_CFIG:
		strM2S =  "有";
		strS2M = "有";
		strRes = "AFN 09";
		break;
		*/

	case INDEX_AFN_0A_GETP:
		strM2S =  "有";
		strS2M = "有";
		strRes = "AFN 0A";
		break;
		/*
	case INDEX_AFN_0B_ASKT:
		strM2S =  "有";
		strS2M = "有";
		strRes = "AFN 0C 0D";
		break;
		*/
	case INDEX_AFN_0C_ASKT:
		strM2S =  "有";
		strS2M =  "有";
		strRes = "AFN 0C";
		break;
	case INDEX_AFN_0D_ASKR:
		strM2S =  "有";
		strS2M =  "有";
		strRes = "AFN 0D";
		break;
	case INDEX_AFN_0E_ASKE:
		strM2S =  "有";
		strS2M = "有";
		strRes = "AFN 0E";
		break;
	case INDEX_AFN_0F_FILE:
		strM2S =  "有";
		strS2M =  "有";
		strRes = "无答复";
		break;
		
	case INDEX_AFN_10_DATA:
		strM2S =  "有";
		strS2M =  "有";
		strRes = "AFN 10";
		break;
		
	default:
		eAfn = AFN_NULL;
		break;
		
	}
	
	m_static_m2s.SetWindowText(strM2S);
	m_static_s2m.SetWindowText(strS2M);
	m_static_res.SetWindowText(strRes);

	// 禁用树控件
	if (m_pNxMstDlg->m_bMaster == TRUE && strM2S == "无")
	{
		m_fnTree.DeleteAllItems();
		//GetDlgItem(IDC_TREE_FN)->EnableWindow(FALSE);
	}
	if (m_pNxMstDlg->m_bMaster == FALSE && strS2M == "无")
	{
		m_fnTree.DeleteAllItems();
	}

}


// 生成命令
void CTabDlgPack::OnOK() 
{
	// TODO: Add extra validation here
	
	m_pNxMstDlg->m_rich_edit.Clear();
	HTREEITEM hitem;
	CString str;
	hitem = m_fnTree.GetFirstVisibleItem();
	while (hitem != NULL)
	{
		if(m_fnTree.GetCheck(hitem) == TRUE)
		{
			str = m_fnTree.GetItemText(hitem);
			str+= "\r\n";
	   	m_pNxMstDlg->m_rich_edit.AppendColor(str,RGB(255,0,0));
		}
		
		hitem = m_fnTree.GetNextVisibleItem(hitem);
	}


	//CDialog::OnOK();
}

void CTabDlgPack::showEcPwTp(BOOL bMaster)
{
	eMtDir	eDir = (bMaster == TRUE) ? MT_DIR_M2S : MT_DIR_S2M;
	int index = m_combo_afn.GetCurSel();
	showEcPwTp(index, eDir);

	if(bMaster == FALSE)
	{
		GetDlgItem(IDC_CHECK_AUTO)->EnableWindow(TRUE);
		if (index == INDEX_AFN_0C_ASKT || index == INDEX_AFN_0D_ASKR)
		{
			m_check_auto.ShowWindow(SW_SHOW);
		}
		else
		{
			m_check_auto.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		
		m_check_auto.ShowWindow(SW_HIDE);
	}

}
void CTabDlgPack::showEcPwTp(int index, eMtDir eDir)
{
	eMtAFN eAfn;
//	CNxRuler ruler;
	switch(index)
	{
	case INDEX_AFN_00_CONF:
		eAfn = AFN_00_CONF;
		break;
	case INDEX_AFN_01_RSET:
		eAfn = AFN_01_RSET;
		break;
	case INDEX_AFN_02_LINK:
		eAfn = AFN_02_LINK;
		break;
		/*
	case INDEX_AFN_03_RELY:
		eAfn = AFN_03_RELY;
		break;
		*/
	case INDEX_AFN_04_SETP:
		eAfn = AFN_04_SETP;
		break;
	case INDEX_AFN_05_CTRL:
		eAfn = AFN_05_CTRL;
		break;
	case INDEX_AFN_06_AUTH:
		eAfn = AFN_06_AUTH;
		break;
		/*
	case INDEX_AFN_09_CFIG:
		eAfn = AFN_09_CFIG;
		break;
		*/
	case INDEX_AFN_0A_GETP:
		eAfn = AFN_0A_GETP;
		break;
		/*
	case INDEX_AFN_0B_ASKT:
		eAfn = AFN_0B_ASKT;
		break;*/
	case INDEX_AFN_0C_ASKT:
		eAfn = AFN_0C_ASK1;
		break;
	case INDEX_AFN_0D_ASKR:
		eAfn = AFN_0D_ASK2;
		break;
	case INDEX_AFN_0E_ASKE:
		eAfn = AFN_0E_ASK3;
		break;
	case INDEX_AFN_0F_FILE:
		eAfn = AFN_0F_FILE;
		break;

	case INDEX_AFN_10_DATA:
		eAfn = AFN_10_DATA;
		break;

	default:
		eAfn = AFN_NULL;
		break;

	}


	// ec
	m_bEC = bmt_have_ec(eAfn, eDir);
	EnableEditBoxEc(m_bEC);

	// tp 
	m_bTP = bmt_have_tp(eAfn, eDir);
	EnableEditBoxTp(m_bTP);

	// pw
	m_bPW = bmt_have_pw(eAfn, eDir);
	EnableEditBoxPw(m_bPW);
	

}

void CTabDlgPack::setMainDlg(CNxMasterDlg *pNxMstDlg)
{
	m_pNxMstDlg= pNxMstDlg;
}


void CTabDlgPack::BuildFnTree(int index)
{
	BOOL bMaster = FALSE;
	if(m_pNxMstDlg != NULL)
	{
		bMaster = m_pNxMstDlg->m_bMaster;
	}

	m_fnTree.DeleteAllItems();
	HTREEITEM hitem;
	switch (index)
	{
	case INDEX_AFN_00_CONF:
		hitem = m_fnTree.InsertItem(STR_AFN_00_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_00_F2,TVI_ROOT);		
		break;

	case INDEX_AFN_01_RSET:
		hitem = m_fnTree.InsertItem(STR_AFN_01_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_01_F2,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_01_F3,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_01_F4,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_01_F5,TVI_ROOT);
		break;

	case INDEX_AFN_02_LINK:
		if (bMaster == TRUE)
		{
		
			hitem = m_fnTree.InsertItem(STR_AFN_02_F4,TVI_ROOT);
		}
		else
		{
			hitem = m_fnTree.InsertItem(STR_AFN_02_F1,TVI_ROOT);
			m_fnTree.InsertItem(STR_AFN_02_F2,TVI_ROOT);
		    m_fnTree.InsertItem(STR_AFN_02_F3,TVI_ROOT);
		}
	
		break;

		/*
	case	INDEX_AFN_03_RELY:
		hitem = m_fnTree.InsertItem(STR_AFN_03_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_03_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_03_F2,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_03_F3,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_03_F4,TVI_ROOT);
		break;
*/
	 case INDEX_AFN_04_SETP:

		 hitem = m_fnTree.InsertItem(STR_AFN_04_F1,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F2,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F3,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F4,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F5,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F6,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F7,TVI_ROOT);
	    //  m_fnTree.InsertItem(STR_AFN_04_F8,TVI_ROOT);

		 m_fnTree.InsertItem(STR_AFN_04_F9,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F10,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F11,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F12,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F13,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F14,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F15,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F16,TVI_ROOT);
		 
		 m_fnTree.InsertItem(STR_AFN_04_F17,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F18,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F19,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F20,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F21,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F22,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F23,TVI_ROOT);

		 m_fnTree.InsertItem(STR_AFN_04_F25,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F26,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F27,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F28,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F29,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F30,TVI_ROOT);
		 
		//  m_fnTree.InsertItem(STR_AFN_04_F31,TVI_ROOT);
		 
		 m_fnTree.InsertItem(STR_AFN_04_F33,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F34,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F35,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_04_F49,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F37,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F38,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F39,TVI_ROOT);
// 
// 		 m_fnTree.InsertItem(STR_AFN_04_F41,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F42,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F43,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F44,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F45,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F46,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F47,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F48,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F57,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F58,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F59,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F60,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F61,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F65,TVI_ROOT);
// 		 
// 		 m_fnTree.InsertItem(STR_AFN_04_F66,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F67,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F68,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F73,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F74,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F75,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F76,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F81,TVI_ROOT);
// 		 m_fnTree.InsertItem(STR_AFN_04_F82,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_04_F83,TVI_ROOT);

		 break;

	 case  INDEX_AFN_05_CTRL:
		 hitem = m_fnTree.InsertItem(STR_AFN_05_F1,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_05_F2,TVI_ROOT);	
		 m_fnTree.InsertItem(STR_AFN_05_F3,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_05_F4,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_05_F5,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_05_F6,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_05_F9,TVI_ROOT);
		 m_fnTree.InsertItem(STR_AFN_05_F10,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F11,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F12,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F15,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F16,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F17,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F18,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F19,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F20,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F23,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F24,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F25,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F26,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F27,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_05_F28,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F29,TVI_ROOT);		
// 		m_fnTree.InsertItem(STR_AFN_05_F31,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F32,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F33,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F34,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F35,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F36,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F37,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F38,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F39,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F41,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F42,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F49,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F50,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F51,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F52,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_05_F53,TVI_ROOT);

		break;
		
	case INDEX_AFN_06_AUTH:
		hitem = m_fnTree.InsertItem(STR_AFN_06_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_06_F2,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_06_F3,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_06_F4,TVI_ROOT);
		break;
		/*
	case INDEX_AFN_09_CFIG:
		
		hitem = m_fnTree.InsertItem(STR_AFN_09_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F2,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F3,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F4,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F5,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F6,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F7,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_09_F8,TVI_ROOT);

		break;
*/
	case INDEX_AFN_0A_GETP:
		hitem = m_fnTree.InsertItem(STR_AFN_0A_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F2,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F3,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F4,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F5,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F6,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F7,TVI_ROOT);
		//m_fnTree.InsertItem(STR_AFN_0A_F8,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F9,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F10,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F11,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F12,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F13,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F14,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F15,TVI_ROOT);
	//	m_fnTree.InsertItem(STR_AFN_0A_F16,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F17,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F18,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F19,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F20,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F21,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F22,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F23,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F25,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F26,TVI_ROOT);
	    m_fnTree.InsertItem(STR_AFN_0A_F27,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F28,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F29,TVI_ROOT);
    	m_fnTree.InsertItem(STR_AFN_0A_F30,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F31,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F33,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F34,TVI_ROOT);
     	m_fnTree.InsertItem(STR_AFN_0A_F35,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F36,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F36,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F37,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F38,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F39,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F41,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F42,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F43,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F44,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F45,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F46,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F47,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F48,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F49,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0A_F57,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F58,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F59,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F60,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F61,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F65,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F66,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F67,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F68,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F73,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F74,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F75,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F76,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F81,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F82,TVI_ROOT);
// 		m_fnTree.InsertItem(STR_AFN_0A_F83,TVI_ROOT);

		break;
		/*
		case INDEX_AFN_0B_ASKT:
		
		  hitem = m_fnTree.InsertItem(STR_AFN_0B_F1,TVI_ROOT);
		  m_fnTree.InsertItem(STR_AFN_0B_F2,TVI_ROOT);
		  
			break;
			
		*/
		case INDEX_AFN_0C_ASKT:
		hitem = m_fnTree.InsertItem(STR_AFN_0C_F1 ,TVI_ROOT);
		m_fnTree.InsertItem( STR_AFN_0C_F9,TVI_ROOT);//"F3终端参数状态"
// 		m_fnTree.InsertItem( STR_AFN_0C_F4 ,TVI_ROOT);//"F4终端上行通信状态"
// 		m_fnTree.InsertItem( STR_AFN_0C_F5 ,TVI_ROOT);//"F5终端控制设置状态"
// 		m_fnTree.InsertItem( STR_AFN_0C_F6 ,TVI_ROOT);//"F6终端当前控制状态"
// 		m_fnTree.InsertItem( STR_AFN_0C_F7 ,TVI_ROOT);//"F7终端事件计数器当前值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F8 ,TVI_ROOT);//"F8终端事件标志状态"
// 		
// 		//2
// 		m_fnTree.InsertItem( STR_AFN_0C_F9 ,TVI_ROOT);//"F9终端状态量及变位标志"
// 		m_fnTree.InsertItem( STR_AFN_0C_F10   ,TVI_ROOT);//"F10  终端与主站当日、月通信流量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F11   ,TVI_ROOT);//"F10  终端集中抄表状态信息"
// 		
// 		//3
// 		m_fnTree.InsertItem( STR_AFN_0C_F17   ,TVI_ROOT);//"F17  当前总加有功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F18   ,TVI_ROOT);//"F18  当前总加无功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F19   ,TVI_ROOT);//"F19  当日总加有功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F20   ,TVI_ROOT);//"F20  当日总加无功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F21   ,TVI_ROOT);//"F21  当月总加有功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F22   ,TVI_ROOT);//"F22  当月总加无功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F23   ,TVI_ROOT);//"F23  终端当前剩余电量(费)"
// 		m_fnTree.InsertItem( STR_AFN_0C_F24   ,TVI_ROOT);//"F24  当前功率下浮控控后总加有功功率冻结值"
// 		
// 		//4
// 		m_fnTree.InsertItem( STR_AFN_0C_F25   ,TVI_ROOT);//"F25  当前三相及总有/无功功率、功率因数 , 三相电压、电流、零序电流、视在功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F26   ,TVI_ROOT);//"F26  A、B、C三相断相统计数据及最近一次断相记录"
// 		m_fnTree.InsertItem( STR_AFN_0C_F27   ,TVI_ROOT);//"F27  电能表日历时钟、编程次数及其最近一次操作时间"
// 		m_fnTree.InsertItem( STR_AFN_0C_F28   ,TVI_ROOT);//"F28  电表运行状态字及其变位标志"
// 		m_fnTree.InsertItem( STR_AFN_0C_F29   ,TVI_ROOT);//"F29  当前铜损、铁损有功总电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F30   ,TVI_ROOT);//"F30  上一结算日当前铜损、铁损有功总电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F31   ,TVI_ROOT);//"F31  当前A、B、C三相正/反向有功电能示值、组合无功1/2电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F32   ,TVI_ROOT);//"F32  上一结算日A、B、C三相正/反向有功电能示值、组合无功1/2电能示值"
// 		
// 		//5
// 		m_fnTree.InsertItem( STR_AFN_0C_F33   ,TVI_ROOT);//"F33  当前正向有/无功(组合无功1)电能示值、一/四象限无功电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F34   ,TVI_ROOT);//"F34  当前反向有/无功(组合无功2)电能示值、二/三象限无功电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F35   ,TVI_ROOT);//"F35  当月正向有/无功最大需量及发生时间"
// 		m_fnTree.InsertItem( STR_AFN_0C_F36   ,TVI_ROOT);//"F36  当月反向有/无功最大需量及发生时间"
// 		m_fnTree.InsertItem( STR_AFN_0C_F37   ,TVI_ROOT);//"F37  上月(上一结算日)正向有/无功(组合无功1)电能示值、一/四象限无功电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F38   ,TVI_ROOT);//"F38  上月(上一结算日)反向有/无功(组合无功2)电能示值、二/三象限无功电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F39   ,TVI_ROOT);//"F39  上月（上一结算日）正向有/无功最大需量及发生时间"
// 		m_fnTree.InsertItem( STR_AFN_0C_F40   ,TVI_ROOT);//"F40  上月（上一结算日）反向有/无功最大需量及发生时间"
// 		
// 		//6
// 		m_fnTree.InsertItem( STR_AFN_0C_F41   ,TVI_ROOT);//"F41  当日正向有功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F42   ,TVI_ROOT);//"F42  当日正向无功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F43   ,TVI_ROOT);//"F43  当日反向有功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F44   ,TVI_ROOT);//"F44  当日反向无功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F45   ,TVI_ROOT);//"F45  当月正向有功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F46   ,TVI_ROOT);//"F46  当月正向无功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F47   ,TVI_ROOT);//"F47  当月反向有功电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F48   ,TVI_ROOT);//"F48  当月反向无功电能量"
// 		
// 		//7
// 		m_fnTree.InsertItem( STR_AFN_0C_F49   ,TVI_ROOT);//"F49  当前电压、电流相位角"
// 		
// 		//8
// 		
// 		m_fnTree.InsertItem( STR_AFN_0C_F57   ,TVI_ROOT);//"F57  当前A、B、C三相电压、电流2～N次谐波有效值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F58   ,TVI_ROOT);//"F58  当前A、B、C三相电压、电流2～N次谐波含有率"
// 		
// 		//9
// 		m_fnTree.InsertItem( STR_AFN_0C_F65   ,TVI_ROOT);//"F65  当前电容器投切状态"
// 		m_fnTree.InsertItem( STR_AFN_0C_F66   ,TVI_ROOT);//"F66  当前电容器累计补偿投入时间和次数"
// 		m_fnTree.InsertItem( STR_AFN_0C_F67   ,TVI_ROOT);//"F67  当日、当月电容器累计补偿的无功电能量"
// 		
// 		//10
// 		
// 		m_fnTree.InsertItem( STR_AFN_0C_F73   ,TVI_ROOT);//"F73  直流模拟量实时数据"
// 		//11
// 		m_fnTree.InsertItem( STR_AFN_0C_F81   ,TVI_ROOT);//"F81  小时冻结总加有功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F82   ,TVI_ROOT);//"F82  小时冻结总加无功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F83   ,TVI_ROOT);//"F83  小时冻结总加有功总电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F84   ,TVI_ROOT);//"F84  小时冻结总加无功总电能量"
// 		
// 		//12
// 		m_fnTree.InsertItem( STR_AFN_0C_F89   ,TVI_ROOT);//"F89  小时冻结有功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F90   ,TVI_ROOT);//"F90  小时冻结A相有功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F91   ,TVI_ROOT);//"F91  小时冻结B相有功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F92   ,TVI_ROOT);//"F92  小时冻结C相有功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F93   ,TVI_ROOT);//"F93  小时冻结无功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F94   ,TVI_ROOT);//"F94  小时冻结A相无功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F95   ,TVI_ROOT);//"F95  小时冻结B相无功功率"
// 		m_fnTree.InsertItem( STR_AFN_0C_F96   ,TVI_ROOT);//"F96  小时冻结C相无功功率"
// 		//13
// 		m_fnTree.InsertItem( STR_AFN_0C_F97   ,TVI_ROOT);//"F97  小时冻结A相电压"
// 		m_fnTree.InsertItem( STR_AFN_0C_F98   ,TVI_ROOT);//"F98  小时冻结B相电压"
// 		m_fnTree.InsertItem( STR_AFN_0C_F99   ,TVI_ROOT);//"F99  小时冻结C相电压"
// 		m_fnTree.InsertItem( STR_AFN_0C_F100   ,TVI_ROOT);//"F100  小时冻结A相电流"
// 		m_fnTree.InsertItem( STR_AFN_0C_F101   ,TVI_ROOT);//"F101  小时冻结B相电流"
// 		m_fnTree.InsertItem( STR_AFN_0C_F102   ,TVI_ROOT);//"F102  小时冻结C相电流"
// 		m_fnTree.InsertItem( STR_AFN_0C_F103   ,TVI_ROOT);//"F103  小时冻结零序电流"
// 		
// 		//14
// 		m_fnTree.InsertItem( STR_AFN_0C_F105   ,TVI_ROOT);//"F105  小时冻结正向有功总电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F106   ,TVI_ROOT);//"F106  小时冻结正向无功总电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F107   ,TVI_ROOT);//"F107  小时冻结反向有功总电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F108   ,TVI_ROOT);//"F108  小时冻结反向无功总电能量"
// 		m_fnTree.InsertItem( STR_AFN_0C_F109   ,TVI_ROOT);//"F109  小时冻结正向有功总电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F110   ,TVI_ROOT);//"F110  小时冻结正向无功总电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F111   ,TVI_ROOT);//"F111  小时冻结反向有功总电能示值"
// 		m_fnTree.InsertItem( STR_AFN_0C_F112   ,TVI_ROOT);//"F112  小时冻结反向无功总电能示值"
// 		
// 		//15
// 		m_fnTree.InsertItem( STR_AFN_0C_F113   ,TVI_ROOT);//"F113  小时冻结总功率因数"
// 		m_fnTree.InsertItem( STR_AFN_0C_F114   ,TVI_ROOT);//"F114  小时冻结A相功率因数"
// 		m_fnTree.InsertItem( STR_AFN_0C_F115   ,TVI_ROOT);//"F115  小时冻结B相功率因数"
// 		m_fnTree.InsertItem( STR_AFN_0C_F116   ,TVI_ROOT);//"F116  小时冻结C相功率因数"
// 		
// 		// 16
// 		m_fnTree.InsertItem( STR_AFN_0C_F121   ,TVI_ROOT);//"F121  小时冻结直流模拟量"
// 		
// 		//17
// 		m_fnTree.InsertItem( STR_AFN_0C_F129   ,TVI_ROOT);//"F129  当前正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F130   ,TVI_ROOT);//"F130  当前正向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F131   ,TVI_ROOT);//"F131  当前反向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F132   ,TVI_ROOT);//"F132  当前反向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F133   ,TVI_ROOT);//"F133  当前一象限无功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F134   ,TVI_ROOT);//"F134  当前二象限无功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F135   ,TVI_ROOT);//"F135  当前三象限无功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F136   ,TVI_ROOT);//"F136  当前四象限无功电能示值（总、费率1～M）"
// 		//18
// 		m_fnTree.InsertItem( STR_AFN_0C_F137   ,TVI_ROOT);//"F137  上月（上一结算日）正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F138   ,TVI_ROOT);//"F138  上月（上一结算日）正向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F139   ,TVI_ROOT);//"F139  上月（上一结算日）反向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F140   ,TVI_ROOT);//"F140  上月（上一结算日）反向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F141   ,TVI_ROOT);//"F141  上月（上一结算日）一象限无功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F142   ,TVI_ROOT);//"F142  上月（上一结算日）二象限无功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F143   ,TVI_ROOT);//"F143  上月（上一结算日）三象限无功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F144   ,TVI_ROOT);//"F144  上月（上一结算日）四象限无功电能示值（总、费率1～M）"
// 		
// 		//19
// 		m_fnTree.InsertItem( STR_AFN_0C_F145   ,TVI_ROOT);//"F145  当月正向有功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F146   ,TVI_ROOT);//"F146  当月正向无功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F147   ,TVI_ROOT);//"F147  当月反向有功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F148   ,TVI_ROOT);//"F148  当月反向无功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F149   ,TVI_ROOT);//"F149  上月（上一结算日）正向有功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F150   ,TVI_ROOT);//"F150  上月（上一结算日）正向无功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F151   ,TVI_ROOT);//"F151  上月（上一结算日）反向有功最大需量及发生时间（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F152   ,TVI_ROOT);//"F152  上月（上一结算日）反向无功最大需量及发生时间（总、费率1～M）"
// 		//20
// 		m_fnTree.InsertItem( STR_AFN_0C_F153   ,TVI_ROOT);//"F153  第一时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F154   ,TVI_ROOT);//"F154  第二时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F155   ,TVI_ROOT);//"F155  第三时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F156   ,TVI_ROOT);//"F156  第四时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F157   ,TVI_ROOT);//"F157  第五时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F158   ,TVI_ROOT);//"F158  第六时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F159   ,TVI_ROOT);//"F159  第七时区冻结正向有功电能示值（总、费率1～M）"
// 		m_fnTree.InsertItem( STR_AFN_0C_F160   ,TVI_ROOT);//"F160  第八时区冻结正向有功电能示值（总、费率1～M）"
// 		//21
// 		m_fnTree.InsertItem( STR_AFN_0C_F161   ,TVI_ROOT);//"F161  电能表远程控制通断电状态及记录"
// 		m_fnTree.InsertItem( STR_AFN_0C_F165   ,TVI_ROOT);//"F165  电能表开关操作次数及时间"
// 		m_fnTree.InsertItem( STR_AFN_0C_F166   ,TVI_ROOT);//"F166  电能表参数修改次数及时间"
// 		m_fnTree.InsertItem( STR_AFN_0C_F167   ,TVI_ROOT);//"F167  电能表购、用电信息"
// 		m_fnTree.InsertItem( STR_AFN_0C_F168   ,TVI_ROOT);//"F168  电能表结算信息"
// 		
// 		//22
// 		m_fnTree.InsertItem( STR_AFN_0C_F169   ,TVI_ROOT);//"F169  集中抄表中继路由信息"
// 		m_fnTree.InsertItem( STR_AFN_0C_F170   ,TVI_ROOT);//"F170  集中抄表电表抄读信息"

		break;

	case INDEX_AFN_0D_ASKR:
		hitem = m_fnTree.InsertItem(STR_CMD_AFN_D_F1_CLOCK,TVI_ROOT);//F1   正向有/无功电能示值、一/四象限无功电能示值"
		//组1 pn: p0/监测终端号
		//m_fnTree.InsertItem(STR_CMD_AFN_D_F1_CLOCK, TVI_ROOT);, TVI_ROOT);//日历时钟
		m_fnTree.InsertItem(STR_CMD_AFN_D_F2_PARA_STATE, TVI_ROOT);//参数状态标志
		m_fnTree.InsertItem(STR_CMD_AFN_D_F3_EVENT_1, TVI_ROOT);//重要事件计数器当前值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F4_EVENT_2, TVI_ROOT);//一般事件计数器当前值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F5_EVENT_STATE, TVI_ROOT);//事件状态标志
		m_fnTree.InsertItem(STR_CMD_AFN_D_F6_POWR_TIMES, TVI_ROOT);//上电次数 
		//组2 pn:p0/监测终端号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F9_STATE, TVI_ROOT);//状态量及变位标志
		m_fnTree.InsertItem(STR_CMD_AFN_D_F10_SWITCH, TVI_ROOT);//控制输出回路开关接入状态量及变位标志 
		//组4 pn:p0/电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F25_POWR_HAVE_T, TVI_ROOT);//总有功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F26_POWR_NONE_T, TVI_ROOT);//总无功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F27_FACTR_T, TVI_ROOT);//总功率因数
		m_fnTree.InsertItem(STR_CMD_AFN_D_F28_FACTR_A, TVI_ROOT);//A相功率因素
		m_fnTree.InsertItem(STR_CMD_AFN_D_F29_FACTR_B, TVI_ROOT);//B相功率因数
		m_fnTree.InsertItem(STR_CMD_AFN_D_F30_FACTR_C, TVI_ROOT);//C相功率因数
		//组5 pn:p0/电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F33_DEMAND, TVI_ROOT);//需量
		m_fnTree.InsertItem(STR_CMD_AFN_D_F34_DEMAND_MAX, TVI_ROOT);//日最大需量
		m_fnTree.InsertItem(STR_CMD_AFN_D_F35_DEMAND_TIME, TVI_ROOT);//日最大需量发生时间 
		//组6 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F41_POWR_HAVE_A, TVI_ROOT);//A相有功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F42_POWR_HAVE_B, TVI_ROOT);//B相有功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F43_POWR_HAVE_C, TVI_ROOT);//C相有功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F44_POWR_NONE_A, TVI_ROOT);//A相无功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F45_POWR_NONE_B, TVI_ROOT);//B相无功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F46_POWR_NONE_C, TVI_ROOT);//C相无功功率 
		//组7 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F49_POWR_HAVE_FRTH, TVI_ROOT);//（正向）有功总电能示数
		m_fnTree.InsertItem(STR_CMD_AFN_D_F50_POWR_HAVE_BACK, TVI_ROOT);//（反向）有功总电能示数
		m_fnTree.InsertItem(STR_CMD_AFN_D_F51_POWR_NONE_FRTH, TVI_ROOT);//（正向）无功总电能示数
		m_fnTree.InsertItem(STR_CMD_AFN_D_F52_POWR_NONE_BACK, TVI_ROOT);//（反向）无功总电能示数 
		//组8 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F57_VOLT_A, TVI_ROOT);//A相电压
		m_fnTree.InsertItem(STR_CMD_AFN_D_F58_VOLT_B, TVI_ROOT);//B相电压
		m_fnTree.InsertItem(STR_CMD_AFN_D_F59_VOLT_C, TVI_ROOT);//C相电压
		m_fnTree.InsertItem(STR_CMD_AFN_D_F60_VANGL_A, TVI_ROOT);//A相电压相位角
		m_fnTree.InsertItem(STR_CMD_AFN_D_F61_VANGL_B, TVI_ROOT);//B相电压相位角
		m_fnTree.InsertItem(STR_CMD_AFN_D_F62_VANGL_C, TVI_ROOT);//C相电压相位角
		m_fnTree.InsertItem(STR_CMD_AFN_D_F63_VOLT_UBL, TVI_ROOT);//电压不平衡度
		m_fnTree.InsertItem(STR_CMD_AFN_D_F64_CIRCLE_V, TVI_ROOT);//周波
		//组9 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F65_ELEC_A, TVI_ROOT);//A相电流
		m_fnTree.InsertItem(STR_CMD_AFN_D_F66_ELEC_B, TVI_ROOT);//B相电流
		m_fnTree.InsertItem(STR_CMD_AFN_D_F67_ELEC_C, TVI_ROOT);//C相电流
		m_fnTree.InsertItem(STR_CMD_AFN_D_F68_ELEC_M, TVI_ROOT);//中性线电流
		m_fnTree.InsertItem(STR_CMD_AFN_D_F69_EANGL_A, TVI_ROOT);//A相电流相位角
		m_fnTree.InsertItem(STR_CMD_AFN_D_F70_EANGL_B, TVI_ROOT);//B相电流相位角
		m_fnTree.InsertItem(STR_CMD_AFN_D_F71_EANGL_C, TVI_ROOT);//C相电流相位角
		m_fnTree.InsertItem(STR_CMD_AFN_D_F72_ELEC_UBL, TVI_ROOT);//电流不平衡度 
		//组10 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F73_VDMAX_A, TVI_ROOT);//日A相电压极大值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F74_VDMAX_A_TIME, TVI_ROOT);//日A相电压极大值发生时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F75_VDMAX_B, TVI_ROOT);//日A相电压极大值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F76_VDMAX_B_TIME, TVI_ROOT);//日A相电压极大值发生时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F77_VDMAX_C, TVI_ROOT);//日A相电压极大值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F78_VDMAX_C_TIME, TVI_ROOT);//日A相电压极大值发生时间 
		//组11 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F81_IDMAX_A, TVI_ROOT);//日A相电流极大值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F82_IDMAX_A_TIME, TVI_ROOT);//日A相电流极大值发生时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F83_IDMAX_B, TVI_ROOT);//日B相电流极大值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F84_IDMAX_B_TIME, TVI_ROOT);//日B相电流极大值发生时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F85_IDMAX_C, TVI_ROOT);//日C相电流极大值
		m_fnTree.InsertItem(STR_CMD_AFN_D_F86_IDMAX_C_TIME, TVI_ROOT);//日C相电流极大值发生时间 
		//组12 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F89_TFW_HAVE, TVI_ROOT);//总基波有功功率(Total Fundamental Wave)
		m_fnTree.InsertItem(STR_CMD_AFN_D_F90_TFW_NONE, TVI_ROOT);//总基波无功功率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F91_THW_HAVE, TVI_ROOT);//总谐波有功功率(Total Harmonic Wave)
		m_fnTree.InsertItem(STR_CMD_AFN_D_F92_THW_NONE, TVI_ROOT);//总基波无功功率 
		//组13 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F97_VDPP_TIME_A, TVI_ROOT);//A相电压越上上限日累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F98_VDPP_TIME_B, TVI_ROOT);//B相电压越上上限日累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F99_VDPP_TIME_C, TVI_ROOT);//C相电压越上上限日累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F100_VDNN_TIME_A, TVI_ROOT);//A相电压越下下限日累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F101_VDNN_TIME_B, TVI_ROOT);//B相电压越下下限日累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F102_VDNN_TIME_C, TVI_ROOT);//C相电压越下下限日累计时间
		//组14 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F105_VMPP_TIME_A, TVI_ROOT);//A相电压越上上限月累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F106_VMPP_TIME_B, TVI_ROOT);//B相电压越上上限月累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F107_VMPP_TIME_C, TVI_ROOT);//C相电压越上上限月累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F108_VMNN_TIME_A, TVI_ROOT);//A相电压越下下限月累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F109_VMNN_TIME_B, TVI_ROOT);//B相电压越下下限月累计时间
		m_fnTree.InsertItem(STR_CMD_AFN_D_F110_VMNN_TIME_C, TVI_ROOT);//C相电压越下下限月累计时间 
		//组15 pn:电气测量点号 (aberrance)
		m_fnTree.InsertItem(STR_CMD_AFN_D_F113_VABR_TOTL_A, TVI_ROOT);//A相电压总畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F114_VABR_TOTL_B, TVI_ROOT);//B相电压总畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F115_VABR_TOTL_C, TVI_ROOT);//C相电压总畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F116_EABR_TOTL_A, TVI_ROOT);//A相电流总畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F117_EABR_TOTL_B, TVI_ROOT);//B相电流总畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F118_EABR_TOTL_C, TVI_ROOT);//C相电流总畸变率 
		//组16 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F121_VABR_ODD_A, TVI_ROOT);//A相电压奇次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F122_VABR_EVN_A, TVI_ROOT);//A相电压偶次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F123_VABR_ODD_B, TVI_ROOT);//B相电压奇次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F124_VABR_EVN_B, TVI_ROOT);//B相电压偶次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F125_VABR_ODD_C, TVI_ROOT);//C相电压奇次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F126_VABR_EVN_C, TVI_ROOT);//C相电压偶次畸变率 
		//组17 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F128_EABR_OOD_A, TVI_ROOT);//A相电流奇次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F129_EABR_EVN_A, TVI_ROOT);//A相电流偶次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F130_EABR_OOD_B, TVI_ROOT);//B相电流奇次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F131_EABR_EVN_B, TVI_ROOT);//B相电流偶次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F132_EABR_OOD_C, TVI_ROOT);//C相电流奇次畸变率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F133_EABR_EVN_C, TVI_ROOT);//C相电流偶次畸变率
		//组18 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F137_FLS_SHRT_A, TVI_ROOT);//A相短时闪变
		m_fnTree.InsertItem(STR_CMD_AFN_D_F138_FLS_SHRT_B, TVI_ROOT);//B相短时闪变
		m_fnTree.InsertItem(STR_CMD_AFN_D_F139_FLS_SHRT_C, TVI_ROOT);//C相短时闪变
		m_fnTree.InsertItem(STR_CMD_AFN_D_F140_FLS_LONG_A, TVI_ROOT);//A相长时闪变
		m_fnTree.InsertItem(STR_CMD_AFN_D_F141_FLS_LONG_B, TVI_ROOT);//B相长时闪变
		m_fnTree.InsertItem(STR_CMD_AFN_D_F142_FLS_LONG_C, TVI_ROOT);//C相长时闪变 
		//组19 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F145_HARM_VOLT_A, TVI_ROOT);//A相N次谐波电压
		m_fnTree.InsertItem(STR_CMD_AFN_D_F146_HARM_VOLT_B, TVI_ROOT);//B相N次谐波电压
		m_fnTree.InsertItem(STR_CMD_AFN_D_F147_HARM_VOLT_C, TVI_ROOT);//C相N次谐波电压
		m_fnTree.InsertItem(STR_CMD_AFN_D_F148_HARM_ELEC_A, TVI_ROOT);//A相N次谐波电流
		m_fnTree.InsertItem(STR_CMD_AFN_D_F149_HARM_ELEC_B, TVI_ROOT);//B相N次谐波电流
		m_fnTree.InsertItem(STR_CMD_AFN_D_F150_HARM_ELEC_C, TVI_ROOT);//C相N次谐波电流 
		//组20 pn:电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F153_HARM_VINC_A, TVI_ROOT);//A相N次谐波电压含有率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F154_HARM_VINC_B, TVI_ROOT);//B相N次谐波电压含有率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F155_HARM_VINC_C, TVI_ROOT);//C相N次谐波电压含有率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F156_HARM_EINC_A, TVI_ROOT);//A相N次谐波电流含有率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F157_HARM_EINC_B, TVI_ROOT);//B相N次谐波电流含有率
		m_fnTree.InsertItem(STR_CMD_AFN_D_F158_HARM_EINC_C, TVI_ROOT);//C相N次谐波电流含有率 
		//组30 pn:非电气测量点号
		m_fnTree.InsertItem(STR_CMD_AFN_D_F233_NELC_VALUE, TVI_ROOT);//非电气量
		break;
		
	case INDEX_AFN_0E_ASKE:
		hitem =	m_fnTree.InsertItem(STR_AFN_0E_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_0E_F2,TVI_ROOT); 
		m_fnTree.InsertItem(STR_AFN_0E_F3,TVI_ROOT); 
		break;
	case INDEX_AFN_0F_FILE:
		hitem = m_fnTree.InsertItem(STR_AFN_0F_F1,TVI_ROOT);
		break;
	case INDEX_AFN_10_DATA:
		hitem = m_fnTree.InsertItem(STR_AFN_10_F1,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_10_F9,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_10_F10,TVI_ROOT);
		m_fnTree.InsertItem(STR_AFN_10_F11,TVI_ROOT);
		break;
	default:
		 break;
	 }

	 // 刷新控件
	 //hitem = m_fnTree.GetFirstVisibleItem();
     //m_fnTree.SetCheck(hitem, TRUE);
	 Invalidate(TRUE);
}



void CTabDlgPack::BuildFnTree()
{
	m_cur_index = m_combo_afn.GetCurSel();
	
	m_fnTree.DeleteAllItems();
	BuildFnTree(m_cur_index);
	
}

void CTabDlgPack::OnRdblclkTreeFn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	CPoint pt;
	GetCursorPos(&pt);
	m_fnTree.ScreenToClient(&pt);
	UINT nFlag = 0;
	HTREEITEM hItem = m_fnTree.HitTest(pt, &nFlag);
	if(hItem != NULL)
	{
		if (m_fnTree.GetCheck(hItem) == TRUE)
		{
			m_fnTree.SetCheck(hItem, FALSE);
			//AfxMessageBox("false");
		}
		else
		{
			m_fnTree.SetCheck(hItem, TRUE);
			//AfxMessageBox("true");
	}
	}




	*pResult = 0;
}

void CTabDlgPack::OnClickTreeFn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	ClickFnTreeSelect();
	*pResult = 0;
}

void CTabDlgPack::EnableEditBoxEc(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_EC1)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_EC2)->EnableWindow(bEnable);

}


void CTabDlgPack::EnableEditBoxPw(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_PW)->EnableWindow(bEnable);
}


void CTabDlgPack::EnableEditBoxTp(BOOL bEnable)
{
	GetDlgItem(IDC_EDITTP_DAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_TP_HOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_TP_MINUTE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_TP_SECOND)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PFC)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PermitDelayMinutes)->EnableWindow(bEnable);
	
}

/************************************************************************/
/* 鼠标单击条目
 * 如果是多选的，单击勾选，再次单元取消勾选
 * 如果是单选的，单击勾选，取消其他选择                                                                   
 */
/************************************************************************/
void CTabDlgPack::ClickFnTreeSelect()
{
	BOOL bMult = FALSE; // 允许多选 ?
	
	int m_cur_index = m_combo_afn.GetCurSel();
	
	switch(m_cur_index)
	{
	case INDEX_AFN_04_SETP:
	case INDEX_AFN_05_CTRL:
	//case INDEX_AFN_09_CFIG:
	case INDEX_AFN_0A_GETP:
	//case INDEX_AFN_0B_ASKT:
	case INDEX_AFN_0C_ASKT:
	case INDEX_AFN_0D_ASKR:
	case INDEX_AFN_0E_ASKE:
		bMult = TRUE;
		break;

	default:
		break;
	}

	CPoint pt;
	GetCursorPos(&pt);
	m_fnTree.ScreenToClient(&pt);
	//m_fnTree.ClientToScreen(&pt);
	UINT nFlag = 0;
	HTREEITEM hItem,hItemTmp;
		
    hItem = m_fnTree.HitTest(pt, &nFlag);

	if(hItem != NULL)
	{
		m_fnTree.SelectItem(hItem);

		if(bMult == TRUE)
		{
			// 可以多选
			
			if (m_fnTree.GetCheck(hItem) == TRUE)
			{
				m_fnTree.SetCheck(hItem, FALSE);
		
			}
			else
			{
				m_fnTree.SetCheck(hItem, TRUE);
			}
		}
		else
		{
			m_fnTree.SetCheck(hItem, TRUE);
		   // 只能单选
		   hItemTmp = m_fnTree.GetFirstVisibleItem();
		   while (hItemTmp != NULL)
		   {
			   if(hItemTmp != hItem)
			   {
				   m_fnTree.SetCheck(hItemTmp, FALSE);
			   }
			   
			   hItemTmp = m_fnTree.GetNextVisibleItem(hItemTmp);
		   }

		}

	}
}



void CTabDlgPack::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	setPosCtrls();
	// TODO: Add your message handler code here
	
}


//动态调整控件
void CTabDlgPack::setPosCtrls()
{
	const int pos_left    = 460;
	const int pos_top     = 235;
	const int pos_bottom  = 80;
	const int border   = 4;
	const int height   = 63; // 高度

    RECT rect_client,rect_ctrl;
	GetClientRect(&rect_client);

	// 发送消息窗口调整
	RECT rect_send;
	const int pos_send_bottom = 10;
	const int pos_sned_top = 10;
	const int size_btn_send = 150;
	rect_send.left   = rect_client.left + border;
	rect_send.right = rect_client.right-120;
	rect_send.bottom  = rect_client.bottom -border;
	rect_send.top  = rect_client.bottom - height;
	if(m_edit_cmd_result.m_hWnd)
     m_edit_cmd_result.MoveWindow(&rect_send);

	// send btn

	RECT rect_btn_send;
	const int pos_btn_left = 25;
	const int height_btn = rect_send.bottom - rect_send.top;
	const int weight = height_btn + 45;
	const int btn_border = 5;
	rect_btn_send.top    = rect_client.bottom - height + btn_border;
	rect_btn_send.left   = rect_send.right + border+btn_border;
	rect_btn_send.right  = rect_btn_send.left + weight;
	rect_btn_send.bottom = rect_client.bottom -border - btn_border;
	if(m_btn_get_cmd.m_hWnd)
     m_btn_get_cmd.MoveWindow(&rect_btn_send);


	rect_ctrl.left = rect_client.left + border;;
	rect_ctrl.top=pos_top;	
	rect_ctrl.bottom=rect_send.top-border;
    rect_ctrl.right=rect_client.right -border;
	if(m_fnTree.m_hWnd)
		m_fnTree.MoveWindow(&rect_ctrl);


}

void CTabDlgPack::OnBtnGetCmd() 
{
	// TODO: Add your control notification handler code here
	m_pNxMstDlg->m_rich_edit.Clear();

	GetCtrlsPack();

}


// 将预配的地址消息显示在控件上
void CTabDlgPack::ShowPreInfor( BOOL bMaster /*= TRUE*/ )
{
	CNxConfig cfg;
	char buf[7] = {0};

	// 地址信息
	sMcAddress sAddr;
	cfg.GetPreAddress(&sAddr, bMaster);
	CString strCode;
	memcpy(buf, sAddr.acRegionCode, 6);
	strCode.Format("%s", buf);
	
	m_edit_tml_addr = sAddr.ulConAddress;
	m_edit_mst_addr = sAddr.ucMstAddress;
	m_edit_zone_code = _ttoi(strCode);
	
	UpdateData(FALSE);
	m_check_team.SetCheck(sAddr.bTeam);

 // PW
	CNxConfig cfgPw;
	CString strPw;
	cfgPw.GetPrePw(&strPw);
	m_edit_pw = strPw;


	// times
	showCurTime();

	UpdateData(FALSE);

}

void CTabDlgPack::showCmdType()
{
	int index = m_combo_afn.GetCurSel();	

	showCmdTypes(index);

}



void CTabDlgPack::showCurTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	m_edit_tp_day.Format("%02d", st.wDay);
	m_edit_tp_hour.Format("%02d", st.wHour);
	m_edit_tp_minute.Format("%02d", st.wMinute);
	m_edit_tp_second.Format("%02d", st.wSecond);
	GetDlgItem(IDC_EDITTP_DAY)->SetWindowText(m_edit_tp_day);
	GetDlgItem(IDC_EDIT_TP_HOUR)->SetWindowText(m_edit_tp_hour);
	GetDlgItem(IDC_EDIT_TP_MINUTE)->SetWindowText(m_edit_tp_minute);
	GetDlgItem(IDC_EDIT_TP_SECOND)->SetWindowText(m_edit_tp_second);
}

void CTabDlgPack::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case AUTO_TIME_ID:
			showCurTime();

		break;
	}


	CDialog::OnTimer(nIDEvent);
}

void CTabDlgPack::OnCheckIntoSend() 
{
	// TODO: Add your control notification handler code here
	
}

void CTabDlgPack::OnCheckTpAuto() 
{
	// TODO: Add your control notification handler code here
	BOOL bCheck;
	bCheck = m_check_auto_tp.GetCheck();
	if(bCheck == TRUE)
	{
		SetTimer(AUTO_TIME_ID,100, NULL);
	}
	else
	{
		KillTimer(AUTO_TIME_ID);
	}
}



// 报文封装
void CTabDlgPack::GetCtrlsPack()
{
	// 将当前控件上的值
	UpdateData(TRUE);
	CString strRegionCode,strPack;
	strRegionCode.Format("%d", m_edit_zone_code);

	int lenUser = MT_USER_MAX;
	// 构造参数
	char *pMem = (char*)malloc(MT_USER_MAX);
	if(pMem == NULL)
	{
		return;
	}

	memset(pMem, 0, MT_USER_MAX);
	//smtPackLite *psmtPackLite = NULL;
	//smtPack *psmtPack = NULL;	
	// 	eMtAFN eAfn;
	// 	CQgdw3761api ruler;
	// 	sMtInit sInit;

	smcPack *psmcPack = NULL;
	eMcAFN  eAfn;
	CGbnx_31 ruler;
	sMcInit sInit;
	sMcEc    sEc;

	sInit.eRole = m_pNxMstDlg->m_bMaster == TRUE ? MC_ROLE_MASTER : MC_ROLE_CONTOR;
	sInit.ucPermitDelayMinutes = m_ucPermitDelayMinutes;
	eMcInit(&sInit);
	psmcPack = (smcPack *)pMem;


	strncpy((char*)psmcPack->sAddress.acRegionCode,(LPCTSTR)strRegionCode, MC_REGN_LEN); 
	psmcPack->sAddress.ucMstAddress = m_edit_mst_addr;
	psmcPack->sAddress.ulConAddress = m_edit_tml_addr;
	psmcPack->sAddress.bTeam = m_check_team.GetCheck();
	

	eMcDir	eDir = (m_pNxMstDlg->m_bMaster == TRUE) ? MC_DIR_M2S : MC_DIR_S2M;
	eAfn = GetAfnSelect();
	psmcPack->sAc.eAfn = eAfn;
	psmcPack->sEc.usEC1 = m_edit_ec1;
	psmcPack->sEc.usEC2 = m_edit_ec2;
	
	sEc.usEC1 = psmcPack->sEc.usEC1;
	sEc.usEC2 = psmcPack->sEc.usEC2;
	
	psmcPack->sCtrl.ucPSEQ = m_edit_pseq;
	psmcPack->sCtrl.ucRSEQ = m_edit_rseq;

	vmc_set_ec(&sEc);
	
	strncpy((char*)psmcPack->aPw,(LPCTSTR)m_edit_pw, 16);

	psmcPack->sTp.sTime.ucDD = atoi(m_edit_tp_day);
	psmcPack->sTp.sTime.ucHH = atoi(m_edit_tp_hour);
	psmcPack->sTp.sTime.ucmm = atoi(m_edit_tp_minute);
	psmcPack->sTp.sTime.ucss = atoi(m_edit_tp_second);
	psmcPack->sTp.ucPermitDelayMinutes = m_ucPermitDelayMinutes;
	//psmcPack->sTp.ucPFC	= m_edit_pfc & 0xFF;

	psmcPack->usNum = 1;
	//psmtPack->ucSeq = m_edit_pfc & 0x0F;

	//pw
	//vmtSetPw(m_edit_pw.GetBuffer(16));


	// ctrl
	BOOL bAuto = m_check_auto.GetCheck();
	BOOL bFixed = FALSE;
	psmcPack->sCtrl.eDir = eDir;
	psmcPack->sCtrl.ePRM = emc_get_prm(eDir, eAfn, bAuto);
	
	// 获取控件上的所选
	BOOL bGet = GetfnSelectAndPreApp31(psmcPack->sData, &(psmcPack->usNum), eDir,psmcPack->sCtrl.ePRM,  &(psmcPack->sCtrl.eFcode), &bFixed);
	if(bGet != TRUE)
	{		
		//AfxMessageBox("获取参数失败");
		vFree(pMem);
		return;
	}
	
	
	// 调用封装函数
	UINT16 usLen = 0;
	UINT8 ucOutBuffer[10240] = {0};
	psmcPack->bFixed = bFixed;
	
	eMcErr eRet = emcPack(psmcPack, ucOutBuffer, &usLen);
	
	
	if(eRet != MT_OK)
	{
		vFree(pMem);
		if (eRet == MT_ERR_NONE)
		{
			MessageBox("该方向没有对应的命令", "提示", MB_OK|MB_ICONWARNING);
		}
		else
		{
			strPack.Format("错误码 %d %s", eRet , ruler.getErrMessage(eRet));
	    	MessageBox(strPack, "命令生成错误", MB_OK|MB_ICONERROR);
		}
	
		return;
	}
	else
	{
		strPack = ruler.BufferToHex((char*)ucOutBuffer, usLen);
		
		BOOL bIntoSend, bText, bSendInstant;



		m_edit_cmd_result.Clear();
		m_edit_cmd_result.SetWindowText(strPack);
		
		bIntoSend = m_check_into_send.GetCheck();
		bSendInstant = m_check_send_instant.GetCheck();
		if(bIntoSend == TRUE)
		{
			m_pNxMstDlg->m_edit_send.Clear();
			m_pNxMstDlg->m_edit_send.SetWindowText(strPack);
			if(bSendInstant)
			{
				m_pNxMstDlg->ClickSendBtn();
			}

		}		
		
		bText = m_check_text.GetCheck();
		if (bText == TRUE)
		{

			// 显示命令生成结果
			COLORREF crNormal, crValue;
			CString strValue;
			crNormal = RGB(128,128,128);
			crValue  = RGB(0,0,255);

			//m_pNxMstDlg->m_rich_edit.AppendColor("\n生成成功\n",RGB(255,0,0));
			// 方向
			m_pNxMstDlg->m_rich_edit.AppendColor("命令内容:",crNormal);
	    	m_pNxMstDlg->m_rich_edit.AppendColor(strPack,RGB(255,0,0));

			m_pNxMstDlg->m_rich_edit.AppendColor("\n命令长度:",crNormal);
			strValue.Format("%d", usLen);
			m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);	

			strValue.Format("%s\n", eDir == MT_DIR_S2M ? "从站到主站" :  "主站到从站");
			m_pNxMstDlg->m_rich_edit.AppendColor("\n报文方向:",crNormal);
			m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);

			// 地址信息
			
			//m_pNxMstDlg->m_rich_edit.AppendColor("地址信息:\n",crNormal);

		    m_pNxMstDlg->m_rich_edit.AppendColor("主站地址:",crNormal);
			strValue.Format("%d\n", m_edit_mst_addr);
			m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);

			m_pNxMstDlg->m_rich_edit.AppendColor("行政区码:",crNormal);
			strValue.Format("%d\n", m_edit_zone_code);
			m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);

			m_pNxMstDlg->m_rich_edit.AppendColor("终端地址:",crNormal);
			strValue.Format("%d\n", m_edit_tml_addr);
			m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);


			m_pNxMstDlg->m_rich_edit.AppendColor("为组地址:",crNormal);
			strValue.Format("%s\n", m_check_team.GetCheck() == TRUE ? "是": "否");
			m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);

		

			
			// ec
			if(bmc_have_ec(eAfn, eDir) == TRUE)
			{
				//m_pNxMstDlg->m_rich_edit.AppendColor("事件计数:\n",crNormal);
				m_pNxMstDlg->m_rich_edit.AppendColor("重要事件:",crNormal);
				strValue.Format("EC1 = %d\n", m_edit_ec1);
				m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);
				m_pNxMstDlg->m_rich_edit.AppendColor("一般事件:",crNormal);
				strValue.Format("EC2 = %d\n", m_edit_ec2);
				m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);
			}
		

			// tp
			if(bmc_have_tp(eAfn, eDir) == TRUE)
			{
				//m_pNxMstDlg->m_rich_edit.AppendColor("事件计数:\n",crNormal);
				m_pNxMstDlg->m_rich_edit.AppendColor("封装时间:",crNormal);
				strValue = m_edit_tp_day + "日" +m_edit_tp_hour + "时" + m_edit_tp_minute + "分" + m_edit_tp_second + "秒\n";
				m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);
				m_pNxMstDlg->m_rich_edit.AppendColor("启动序号:",crNormal);
				strValue.Format("PFC = %d\n", m_edit_pfc);
				m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);
			}	


			// pw



		
			// 
			m_combo_afn.GetWindowText(strValue);
			strValue += "\n";
			m_pNxMstDlg->m_rich_edit.AppendColor("主命令ID:",crNormal);
    		m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);	

			// 子命令
			
			HTREEITEM hitem = m_fnTree.GetRootItem();
			int  i = 0;
			while (hitem != NULL)
			{
				if(m_fnTree.GetCheck(hitem) == TRUE)
				{
					strValue.Format("子命令");
					m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crNormal);
					strValue.Format("%2d", ++i);
					m_pNxMstDlg->m_rich_edit.AppendColor(strValue,RGB(255,0,255));
					m_pNxMstDlg->m_rich_edit.AppendColor(":",crNormal);

					strValue = m_fnTree.GetItemText(hitem);	
					UINT8 ucFn = getStrItemFn(strValue);
				
				
					m_pNxMstDlg->m_rich_edit.AppendColor(strValue,crValue);	

					// pn
					CNxConfig cfg;
				
		         	eMcmd eCmd = GetCmdAfnFn31(eAfn, ucFn);
					cfg.GetPrePnStr31(eCmd, sInit.eRole, &strValue);
					strValue = "  测量点(" + strValue+")\n";
			    	m_pNxMstDlg->m_rich_edit.AppendColor(strValue,RGB(255,0,255));	
				}
				
				hitem = m_fnTree.GetNextVisibleItem(hitem);
			}




		

			m_pNxMstDlg->m_rich_edit.AppendColor("\n",RGB(255,0,0));
		}
		
		m_pNxMstDlg->insetLineStype();
		//m_pNxMstDlg->m_rich_edit.AppendColor("------------------------------------------------------------------\n\n",RGB(128,128,128));

	}
	


	vFree(pMem);
	
}

eMcAFN CTabDlgPack::GetAfnSelect()
{
	int index;
	eMcAFN eAfn;
	index = m_combo_afn.GetCurSel();
	switch(index)
	{

	case INDEX_AFN_00_CONF:
		eAfn = MC_AFN_00_CONF;
		break;

	case INDEX_AFN_01_RSET:
		eAfn = MC_AFN_01_RSET;
		break;

	case INDEX_AFN_02_LINK:
		eAfn = MC_AFN_02_LINK;
		break;
//	case INDEX_AFN_03_RELY:
//		eAfn = AFN_03_RELY;
//		break;

	case INDEX_AFN_04_SETP:
		eAfn = MC_AFN_04_SETP;
		break;

	case INDEX_AFN_05_CTRL:
		eAfn = MC_AFN_05_CTRL;
		break;
		
	case INDEX_AFN_06_AUTH:
		eAfn = MC_AFN_06_AUTH;
		break;
		
	case INDEX_AFN_08_CASC:
		eAfn = MC_AFN_08_CASC;
		break;

	case INDEX_AFN_0A_GETP:
		eAfn = MC_AFN_10_GETP;
		break;

// 	case INDEX_AFN_0B_ASKT:
// 		eAfn = AFN_0B_ASKT;
// 		break;

	case INDEX_AFN_0C_ASKT:
		eAfn = MC_AFN_12_ASKT;
		break;
	case INDEX_AFN_0D_ASKR:
		eAfn = MC_AFN_13_ASKR;
		break;
	case INDEX_AFN_0E_ASKE: 
		eAfn = MC_AFN_14_ASKE;
		break;

	case INDEX_AFN_0F_FILE:
		eAfn = MC_AFN_15_FILE;
		break;

	case INDEX_AFN_10_DATA:
		eAfn = MC_AFN_16_DATA;
		break;
	default:
		eAfn = MC_AFN_NULL;
		break;
	}

	return eAfn;
}



// 这个逻辑再想一想
BOOL CTabDlgPack::bGetActive( eMtAFN eAfn, eMtDir eDir )
{
	BOOL bActive = FALSE;

	if(eDir == MT_DIR_M2S)
	{
		
		bActive = TRUE;
	
	}
	else
	{
		bActive = FALSE;
	}
	
	return bActive;
}


/************************************************************************
函数名称: GetfnSelectAndPreApp
函数功能: 获取当前combo控件选择的fn 及AFN  (gb31)
		  从预配信息中获得信息，封装子命令参数及子命令个数输出

输入参数:
输出参数:sMcData *psMtData 多个
	     UINT8 *pucNum
返回类型: void
函数说明
************************************************************************/
BOOL CTabDlgPack::GetfnSelectAndPreApp31( sMcData *psData, UINT16 *pucNum, eMcDir eDir, eMcPRM ePrm, eMcFcode *peFcode, BOOL *bFixed)
{
	if(!psData || !pucNum)
	{
		return FALSE; 
	}
	
	eMcAFN eAfn;
	CString str;
	HTREEITEM hitem;
	UINT8   ucFn = 0;
	eMcmd   eSubCmd;     // 子命令字
	UINT16 usSubCmd = 0;
	int i = 0;
	int j = 0;
	eMcRole eRole = MC_ROLE_UNKOWN;
	eMcErr eRet;
	BOOL   bRet = FALSE;
	BOOL   bSelect = FALSE;
	
	eAfn = GetAfnSelect();	
	//hitem = m_fnTree.GetFirstVisibleItem();
    hitem = m_fnTree.GetRootItem();
	while (hitem != NULL)
	{
		if(m_fnTree.GetCheck(hitem) == TRUE)
		{
			bSelect = TRUE;
			str = m_fnTree.GetItemText(hitem);
			ucFn = getStrItemFn(str);
			eSubCmd = GetCmdAfnFn31(eAfn, ucFn);
			if (eAfn == MC_AFN_02_LINK)
			{
				*bFixed = TRUE;
			}
			else
			{
			    *bFixed = FALSE;
			}
			eRet = emc_get_fcode(eSubCmd, eDir, ePrm, peFcode);

			// 实现多pn组合
			if(eDir == MC_DIR_M2S)
			{
				eRole =  MC_ROLE_MASTER;
			}
			else
			{
				eRole = MC_ROLE_CONTOR;
			}
			
			UINT16 ausPn[255] = {0};
			UINT8  ucNum = 0;
			
			CNxConfig cfg;
			cfg.GetPrePn31(eSubCmd, eRole, ausPn, &ucNum);
			
			if (ucNum == 0)
			{
				ucNum = 1;
			}
			
			for (j = 0; j < ucNum; j++)
			{					
				bRet = bFillCmdApp31(psData+i,ausPn[j], eSubCmd, eDir);
				if(bRet == FALSE)
				{
					return FALSE;
				}
				i++;
			}  
			
		}
		
		//hitem = m_fnTree.GetNextVisibleItem(hitem);
		hitem = m_fnTree.GetNextVisibleItem(hitem);
	}
	
	if(bSelect == FALSE)
	{
		MessageBox("没有选择命令!", "错误", MB_OK|MB_ICONERROR);
		return FALSE;
	}

	*pucNum = (UINT16)i;
	
	return TRUE;
}

/************************************************************************
函数名称: GetfnSelectAndPreApp
函数功能: 获取当前combo控件选择的fn 及AFN (3761)
		  从预配信息中获得信息，封装子命令参数及子命令个数输出

输入参数:
输出参数:sMtData *psMtData 多个
	     UINT8 *pucNum
返回类型: void
函数说明
************************************************************************/
BOOL CTabDlgPack::GetfnSelectAndPreApp( sMtData *psMtData, UINT16 *pucNum ,eMtDir eDir)
{
	/*
	if(!psMtData || !pucNum)
	{
		return FALSE; 
	}
	
	eMtAFN eAfn;
	CString str;
	HTREEITEM hitem;
	UINT8   ucFn = 0;
	eMtCmd eSubCmd;     // 子命令字
	UINT16 usSubCmd = 0;
	int i = 0;
	int j = 0;
	eMtRole eRole = MT_ROLE_UNKOWN;
	
	eAfn = GetAfnSelect();	
	//hitem = m_fnTree.GetFirstVisibleItem();
    hitem = m_fnTree.GetRootItem();
	while (hitem != NULL)
	{
		if(m_fnTree.GetCheck(hitem) == TRUE)
		{
			str = m_fnTree.GetItemText(hitem);
			ucFn = getStrItemFn(str);
			eSubCmd = GetCmdAfnFn(eAfn, ucFn);

			// 实现多pn组合
			if(eDir == MT_DIR_M2S)
			{
				eRole =  MT_ROLE_MASTER;
			}
			else
			{
				eRole = MT_ROLE_CONTOR;
			}

			UINT16 ausPn[255] = {0};
			UINT8  ucNum = 0;
			
			CNxConfig cfg;
			cfg.GetPrePn(eSubCmd, eRole, ausPn, &ucNum);
		
			if (ucNum == 0)
			{
				ucNum = 1;
			}

			for (j = 0; j < ucNum; j++)
			{					
				bFillCmdApp(psMtData+i,ausPn[j], eSubCmd,eDir);
				i++;
			}  
			
		}
		
		//hitem = m_fnTree.GetNextVisibleItem(hitem);
		hitem = m_fnTree.GetNextVisibleItem(hitem);
	}

	*pucNum = (UINT16)i;
*/
	return TRUE;
}

eMcmd CTabDlgPack::GetCmdAfnFn31( eMcAFN eAfn, UINT8 ucFn )
{
	UINT16 usCmd = 0;
	usCmd = (UINT8)eAfn << 8 | ucFn;
	return (eMcmd)usCmd;
}

// 合成命令
eMtCmd CTabDlgPack::GetCmdAfnFn( eMtAFN eAfn, UINT8 ucFn )
{
	UINT16 usCmd = 0;
	usCmd = (UINT8)eAfn << 8 | ucFn;
	return (eMtCmd)usCmd;
}


// 通过Fn的字符串推荐其对应的fn
UINT8 CTabDlgPack::getStrItemFn( CString str )
{
	UINT8 ucAfn;
	CString strSub;
	int nSpace = 0; // 第一个空格的位置
	nSpace = str.Find(" ");
	strSub = str.Left(nSpace);
	strSub = strSub.Right(strSub.GetLength() - 1);
	ucAfn = atoi(strSub);
	return ucAfn;
	
}

// 根据子命令类型将注册表中的数据封装应用层数据 gb31
BOOL CTabDlgPack::bFillCmdApp31(sMcData *psData, UINT16 usPn, eMcmd eCmd, eMcDir eDir)
{
	if(!psData)	
	{
		return FALSE;
	}

	CNxConfig cfg;

	psData->eCmd = eCmd;
	psData->usPN = usPn;
	psData->bApp = FALSE;
	
	if (eDir == MC_DIR_M2S)
	{
		switch(eCmd)
		{
		case MCMD_AFN_1_F1_HARD_INIT:
		case MCMD_AFN_1_F2_DATA_INIT:
		case MCMD_AFN_1_F3_FACTORY_RESET:
		case MCMD_AFN_1_F4_PARA_INIT:	
		case MCMD_AFN_2_F4_LINK_OK:	
			psData->bApp = FALSE;
				break;

		    case MCMD_AFN_0_F1_ALL_OK_DENY:
			{
				psData->bApp = TRUE;
				CDlgPreA00F1 dlg_afn00_f1;
				if (dlg_afn00_f1.DoModal() == IDOK)
				{					
					psData->uApp.eResCode = dlg_afn00_f1.eGetResCode();
				}	
				else
				{
					return FALSE;
				}
			}
			
			break;
			case MCMD_AFN_4_F1_CON_UP_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F1(&(psData->uApp.sConUpCfg), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F2_MST_PARA:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F2(&(psData->uApp.sMstPara), TRUE);

				}
				break;

			case MCMD_AFN_4_F3_CON_AUTH_PARA:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F3(&(psData->uApp.sAuthPara), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F4_TEAM_ADDR:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F4(&(psData->uApp.sTeamAddr), TRUE);
					
				}
				break;
				
			case MCMD_AFN_4_F5_CON_IP_PORT:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F5(&(psData->uApp.sIpPort), TRUE);
					
				}
				
				break;

			case MCMD_AFN_4_F6_CON_CASC:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F6(&(psData->uApp.sCasc), TRUE);
					
				}
				break;	
				
			case MCMD_AFN_4_F7_CON_DOWN_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F7(&(psData->uApp.sDownCfg), TRUE);
					
				}
				break;


			case MCMD_AFN_4_F9_CON_EVENT_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F9(&(psData->uApp.sEventCfg), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F10_CON_STATE_INPUT:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F10(&(psData->uApp.sStateInput), TRUE);
					
				}
				break;
				
			case MCMD_AFN_4_F17_TML_UP_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F17(&(psData->uApp.sTmlUpCfg), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F25_ELEC_MP_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F25(&(psData->uApp.sElecMpCfg), TRUE);
					
				}
				break;
				
			case MCMD_AFN_4_F26_ELEC_MP_BASE:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F26(&(psData->uApp.sElecMpBase), TRUE);
					
				}
				break;
				
			case MCMD_AFN_4_F27_ELEC_LMIT_POWER:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F27(&(psData->uApp.sElecLimitPower), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F28_ELEC_LMIT_FACTR:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F28(&(psData->uApp.sFactorLimit), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F29_ELEC_FIX_HARM:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F29(&(psData->uApp.sElecFixHarm), TRUE);
					
				}
				break;

			case MCMD_AFN_4_F30_ELEC_FLASH:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F30(&(psData->uApp.sElecFlash), TRUE);
					
				}
				break;
				
			case MCMD_AFN_4_F33_NELC_MP_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F33(&(psData->uApp.sNelecMpCfg), TRUE);
					
				}
				break;
				

			case MCMD_AFN_4_F34_NELC_MP_PARA:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F34(&(psData->uApp.sNelcMpPara), TRUE);
					
				}
				break;
		
			case MCMD_AFN_4_F35_NELC_MP_LMIT:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F35(&(psData->uApp.sNelcMpLimit), TRUE);
					
				}
				break;
			
			case MCMD_AFN_4_F49_FREZ_TASK_PARA:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn04F49(&(psData->uApp.sFrezTaskPara), TRUE);
					
				}
				break;
			case MCMD_AFN_A_F2_MST_PARA:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn0aF2q(&(psData->uApp.sMstParaQ), TRUE);
					
				}
				break;
				
			case MCMD_AFN_A_F7_CON_DOWN_CFG:
				{
					psData->bApp = TRUE;
					cfg.GetPreAfn0aF7q(&(psData->uApp.sDownCfgQ), TRUE);
					
				}
				break;


			case MCMD_AFN_5_F1_CHECK_TIME:
				{
					SYSTEMTIME st;
					GetLocalTime(&st);
					psData->bApp = TRUE;
					psData->uApp.sCheckClock.ucYY = (UINT8)(st.wYear%100);
					psData->uApp.sCheckClock.ucMM = (UINT8)st.wMonth;
					psData->uApp.sCheckClock.ucWW = (UINT8)st.wDayOfWeek;
					psData->uApp.sCheckClock.ucDD = (UINT8)st.wDay;
					
					psData->uApp.sCheckClock.ucHH = (UINT8)st.wHour;
					psData->uApp.sCheckClock.ucmm = (UINT8)st.wMinute;
					psData->uApp.sCheckClock.ucDD = (UINT8)st.wDay;
					psData->uApp.sCheckClock.ucss = (UINT8)st.wSecond;
				}
				break;

	


		default:

			break;
		}


	}
	else if(eDir = MC_DIR_S2M)
	{

		switch(eCmd)
		{
		case MCMD_AFN_0_F1_ALL_OK_DENY:
			{
				psData->bApp = TRUE;
				CDlgPreA00F1 dlg_afn00_f1;
				if (dlg_afn00_f1.DoModal() == IDOK)
				{					
					psData->uApp.eResCode = dlg_afn00_f1.eGetResCode();
				}				
			}
			
			break;
		
		case MCMD_AFN_0_F2_ONE_BY_ONE:
		break;



		default:
			break;
		}

		if(eCmd >= MCMD_AFN_D_F25_POWR_HAVE_T && eCmd <= MCMD_AFN_D_F158_HARM_EINC_C) 
		{
			CNxConfig cfg;
			CString strValue;
			cfg.GetPreAfn0DFS(&strValue, eCmd, FALSE);
			psData->uApp.sVoltA.fXXX_X = 123.1f;

		}

	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}


// 根据子命令类型将注册表中的数据封装应用层数据
BOOL CTabDlgPack::bFillCmdApp( sMtData *psMtData,  UINT16 usPn, eMtCmd eCmd, eMtDir eDir )
{
	if(!psMtData)	
	{
		return FALSE;
	}


	psMtData->eCmd = eCmd;
	psMtData->usPN = usPn;
	psMtData->bApp = FALSE;

	if (eDir == MT_DIR_M2S)
	{
		switch(eCmd)
		{
		case CMD_AFN_0_F1_ALL_OK:
		case CMD_AFN_0_F2_ALL_DENY:
		case CMD_AFN_1_F1_HARD_INIT:
		case CMD_AFN_1_F2_DATA_INIT:
		case CMD_AFN_1_F3_FACTORY_RESET:
		case CMD_AFN_1_F4_PARA_INIT:
			psMtData->bApp = FALSE;
	
			break;
			
			// 
		case CMD_AFN_4_F1_TML_UP_CFG:
			{
				CNxConfig config;
				sMtAfn04F1 sAfn04F1_ConUpPortPara_u;
				
				config.GetMstPreAfn04F1(&sAfn04F1_ConUpPortPara_u);
				psMtData->uApp.sTmlUpCfg.bAutoReportAsk_1 = sAfn04F1_ConUpPortPara_u.bAutoReportAsk_1;
				psMtData->uApp.sTmlUpCfg.bAutoReportAsk_2 = sAfn04F1_ConUpPortPara_u.bAutoReportAsk_2;
				psMtData->uApp.sTmlUpCfg.bAutoReportAsk_3 = sAfn04F1_ConUpPortPara_u.bAutoReportAsk_3;
				psMtData->uApp.sTmlUpCfg.ucRTS = sAfn04F1_ConUpPortPara_u.ucRTS;
				psMtData->uApp.sTmlUpCfg.ucRTM = sAfn04F1_ConUpPortPara_u.ucRTM;
				psMtData->uApp.sTmlUpCfg.ucReSendTimes = sAfn04F1_ConUpPortPara_u.ucReSendTimes;
				psMtData->uApp.sTmlUpCfg.ucHeartBeat = sAfn04F1_ConUpPortPara_u.ucHeartBeat;
				psMtData->uApp.sTmlUpCfg.usTmWaitTimeoutS = sAfn04F1_ConUpPortPara_u.usTmWaitTimeoutS;

			
			}
			
			break;
		
#if 0
		case CMD_AFN_4_FN_33_CFG_NOT_ELEC:
			{
				UINT16 usPn;
				sMtCfgNotElec sCfgNotElec;
				CNxConfig cfg;
				cfg.GetPreAfn04F33(&usPn,&sCfgNotElec,MT_ROLE_MASTER);
				
				psMtData->usPN = usPn;
				psMtData->uAppData.sCfgNotElec.eType = sCfgNotElec.eType;
				psMtData->uAppData.sCfgNotElec.dMin = sCfgNotElec.dMin;
				psMtData->uAppData.sCfgNotElec.dMax = sCfgNotElec.dMax;
			}
			break;

		case CMD_AFN_C_FN_90_NOT_ELEC:
			{
				UINT16 usPn;
				sMtNotElec sCfgElec;
				CNxConfig cfg;
				cfg.GetPreAfn0CF90_NotElec(&usPn,&sCfgElec,MT_ROLE_MASTER);
				
				psMtData->usPN = usPn;
				psMtData->uAppData.sNotElec.eType = sCfgElec.eType;
				psMtData->uAppData.sNotElec.dValue = 0.0f;


			}
			break;

#endif



		default:

			break;
		}


	}
	else if(eDir = MT_DIR_S2M)
	{

		switch(eCmd)
		{
		case CMD_AFN_0_F1_ALL_OK:
		case CMD_AFN_0_F2_ALL_DENY:
		case CMD_AFN_2_F1_LOG_IN:
		case CMD_AFN_2_F2_LOG_OUT:
		case CMD_AFN_2_F3_HEART_BEAT:
			psMtData->bApp = FALSE;
		
			break;
#if 0
		case CMD_AFN_C_FN_90_NOT_ELEC:
			{
				UINT16 usPn;
				sMtNotElec sCfgElec;
				CNxConfig cfg;
				cfg.GetPreAfn0CF90_NotElec(&usPn,&sCfgElec,MT_ROLE_CONTOR);
				
				psMtData->usPN = usPn;
				psMtData->uAppData.sNotElec.eType = sCfgElec.eType;
				psMtData->uAppData.sNotElec.dValue = sCfgElec.dValue;
				
				
			}
			break;

#endif
		default:
			break;
		}

	}
	else
	{
		return FALSE;
	}



	
	
	return TRUE;
}

void CTabDlgPack::vFree( char *pMem )
{
	if(pMem != NULL)
	{
		free(pMem);
		pMem = NULL;
	}
	
}


// 获得控件上的TP
void CTabDlgPack::GetCtrlTp31( sMcTp *psTP )
{
	UpdateData(TRUE);
	psTP->sTime.ucDD = atoi(m_edit_tp_day);
	psTP->sTime.ucHH = atoi(m_edit_tp_hour);
	psTP->sTime.ucmm = atoi(m_edit_tp_minute);
	psTP->sTime.ucss = atoi(m_edit_tp_second);
	psTP->ucPermitDelayMinutes = m_ucPermitDelayMinutes;

}

// 获得控件上的TP
void CTabDlgPack::GetCtrlTp( sMtTP *psTP )
{
	UpdateData(TRUE);
	psTP->sDDHHmmss.ucDD = atoi(m_edit_tp_day);
	psTP->sDDHHmmss.ucHH = atoi(m_edit_tp_hour);
	psTP->sDDHHmmss.ucmm = atoi(m_edit_tp_minute);
	psTP->sDDHHmmss.ucss = atoi(m_edit_tp_second);
	psTP->ucPermitDelayMinutes = m_ucPermitDelayMinutes;
	psTP->ucPFC	= m_edit_pfc & 0xFF;
}

// 获得控件上的PW
void CTabDlgPack::GetCtrlPw( char *pw )
{
	UpdateData(TRUE);
	strncpy(pw,(LPCTSTR)m_edit_pw,16);
}

int CTabDlgPack::GetAutoResponseDelaySecond()
{
	UpdateData(TRUE);
	return m_edit_auto_response_delay;
	
}




void CTabDlgPack::OnChangeEditTmlAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here



	
	ChangAddr();
}

void CTabDlgPack::OnChangeEditZoneCode() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	ChangAddr();
}

void CTabDlgPack::OnChangeEditMstAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	ChangAddr();
}

void CTabDlgPack::ChangAddr()
{
	
	UpdateData(TRUE);
	
	sMcAddress sAddr;
	CNxConfig cfg;
	char buf[7] = {0};	
	sprintf(buf, "%d", m_edit_zone_code);
	memcpy(	sAddr.acRegionCode, buf, 6);
	sAddr.bTeam = m_check_team.GetCheck();
	sAddr.ulConAddress = m_edit_tml_addr;
	sAddr.ucMstAddress = m_edit_mst_addr;
	cfg.SetPreAddress(&sAddr, FALSE, TRUE);
	cfg.SetPreAddress(&sAddr, TRUE, TRUE);
}

void CTabDlgPack::OnCheckTeam() 
{
	// TODO: Add your control notification handler code here
	ChangAddr();
}




void CTabDlgPack::OnRclickTreeFn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POINT pos;
	if (!GetCursorPos(&pos))
	{
		return;
	}
	
	m_fnTree.ScreenToClient(&pos);
	
	
	UINT uFlags;
	HTREEITEM hitemRightHit;//右键单击的树控件条目
	hitemRightHit=m_fnTree.HitTest(pos,&uFlags);
	
	if(hitemRightHit == NULL)
	{

		return;
	}
	if ((hitemRightHit!=NULL)&&(TVHT_ONITEM&uFlags))
	{
		m_fnTree.Select(hitemRightHit,TVGN_CARET);
	}
	//确定位置选定节点
	//////////////////////////////////////////////////////////////////////////
	

	
	//////////////////////////////////////////////////////////////////////////
	//加载menu
	CRect rect;
	this->GetClientRect(&rect);
	ClientToScreen(&rect);
	m_fnTree.ClientToScreen(&pos);
	int iCode=rect.PtInRect(pos);
	CString strText;
	

	if (iCode)
	{
	
		// 获得该项的FN 及方向
		CString strItemText;
		eMcmd eCmd;

		eMcDir	eDir = (m_pNxMstDlg->m_bMaster == TRUE) ? MC_DIR_M2S : MC_DIR_S2M;
		m_bMaster_modify = m_pNxMstDlg->m_bMaster;
		eMcAFN eAfn = GetAfnSelect();
		
		strItemText = m_fnTree.GetItemText(hitemRightHit);		
		strText = "配置(&S) " + strItemText;
		

		m_PopMenu.ModifyMenu(IDM_SET_PRE, MF_STRING, IDM_SET_PRE, strText);
		
		if (m_fnTree.GetCheck(hitemRightHit) == TRUE)
		{
			m_PopMenu.EnableMenuItem(IDM_ITEM_CHECK, MF_DISABLED|MF_GRAYED);
			m_PopMenu.EnableMenuItem(IDM_ITEM_UNCHECK, MF_ENABLED);
		}
		else
		{
			m_PopMenu.EnableMenuItem(IDM_ITEM_UNCHECK, MF_DISABLED|MF_GRAYED);
			m_PopMenu.EnableMenuItem(IDM_ITEM_CHECK, MF_ENABLED);
			
		}


		CString strFn;
		strFn = strItemText.Left(strItemText.Find(" ", 2));
		strFn.Replace(" ", "");
		strFn.Replace("F", "");
		
		int fn;
		fn = atoi(strFn.GetBuffer(strFn.GetLength()));
		
		eCmd = (eMcmd)((eAfn << 8) | fn);
		m_eCmd_Modify = eCmd;
		m_eDir_Modify = eDir;
		






		sMcmdInfor sCmdInfor;
		eMcErr eRet = eMcGetCmdInfor(eCmd,eDir, &sCmdInfor);
		if (MC_OK != eRet)
		{
			m_PopMenu.EnableMenuItem(IDM_SET_PRE, MF_DISABLED|MF_GRAYED);
			m_PopMenu.EnableMenuItem(IDM_SET_PN, MF_DISABLED|MF_GRAYED);
		}
		else
		{
			m_strName_modify.Format("F%-2d %s",eCmd&0xFF, sCmdInfor.pName);
			m_pnType_modify	 = sCmdInfor.ePn;
			m_cmdInfor = sCmdInfor;
			if (sCmdInfor.pFunc == NULL)
			{
				m_PopMenu.EnableMenuItem(IDM_SET_PRE, MF_DISABLED|MF_GRAYED);
			}
			else
			{
				m_PopMenu.EnableMenuItem(IDM_SET_PRE, MF_ENABLED);
			}
			
			if (sCmdInfor.ePn == MC_PN_P0)
			{
				m_PopMenu.EnableMenuItem(IDM_SET_PN, MF_DISABLED|MF_GRAYED);
			}
			else
			{
				m_PopMenu.EnableMenuItem(IDM_SET_PN, MF_ENABLED);
			}
		}
		
		
		
		
	
		
		
		m_hItemSel = hitemRightHit;
		m_PopMenu.TrackPopupMenu(TPM_RIGHTBUTTON|TPM_LEFTALIGN,pos.x,pos.y,this);
	}
	
	
	
	
	*pResult = 0;
}

void CTabDlgPack::OnItemCheck() 
{
	// TODO: Add your command handler code here
	m_fnTree.SetCheck(m_hItemSel, TRUE);

	BOOL bMult = FALSE; // 允许多选 ?
	
	int m_cur_index = m_combo_afn.GetCurSel();
	
	switch(m_cur_index)
	{
	case INDEX_AFN_04_SETP:
	case INDEX_AFN_05_CTRL:
		//case INDEX_AFN_09_CFIG:
	case INDEX_AFN_0A_GETP:
		//case INDEX_AFN_0B_ASKT:
	case INDEX_AFN_0C_ASKT:
	case INDEX_AFN_0D_ASKR:
	case INDEX_AFN_0E_ASKE:
		bMult = TRUE;
		break;
		
	default:
		break;
	}
	
	HTREEITEM hItemTmp;
	if(m_hItemSel != NULL)
	{
		m_fnTree.SelectItem(m_hItemSel);
		
		if(bMult == TRUE)
		{
			// 可以多选
			
			m_fnTree.SetCheck(m_hItemSel, TRUE);
			
		}
		else
		{
			m_fnTree.SetCheck(m_hItemSel, TRUE);
			// 只能单选
			hItemTmp = m_fnTree.GetFirstVisibleItem();
			while (hItemTmp != NULL)
			{
				if(hItemTmp != m_hItemSel)
				{
					m_fnTree.SetCheck(hItemTmp, FALSE);
				}
				
				hItemTmp = m_fnTree.GetNextVisibleItem(hItemTmp);
			}
		}
	}

}

void CTabDlgPack::OnItemUncheck() 
{
	// TODO: Add your command handler code here
		m_fnTree.SetCheck(m_hItemSel, FALSE);
	
}

int CTabDlgPack::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_PopMenu.CreatePopupMenu();
	m_PopMenu.AppendMenu(MF_STRING, IDM_ITEM_CHECK, "选择(&C)");
	m_PopMenu.AppendMenu(MF_STRING, IDM_ITEM_UNCHECK, "不选(&U)");
	m_PopMenu.AppendMenu(MF_STRING, IDM_SET_PN,  "测量点(&P)");
	m_PopMenu.AppendMenu(MF_STRING, IDM_SET_PRE, "配置(&S)");
	
	return 0;
}

void CTabDlgPack::OnSetPrePn()
{
	CDlgPrePn dlg;
	

	
	
	m_strName_modify+= " 测量点";
	
	dlg.m_cmdInfor = m_cmdInfor;
	dlg.SetTitle(m_strName_modify);
	dlg.DoModal();
}

void CTabDlgPack::OnSetPre() 
{
	// TODO: Add your command handler code here
	
	switch (m_eCmd_Modify)
	{

	case MCMD_AFN_0_F1_ALL_OK_DENY:
		{
			CDlgPreA00F1 dlg;
			dlg.m_bMaster = m_bMaster_modify;
			if (dlg.DoModal() == IDOK)
			{
		    	//showMstPreAfn00F1();
			}
		}
		break;

	case MCMD_AFN_4_F1_CON_UP_CFG:
		{
			CDlgPreAfn04F1 dlg;
			dlg.setTitle("AFN04_F1 信息集中与交互终端上行通信口通信参数");
			dlg.m_bPreMaster = TRUE;
			if(dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F1();
			}

		}
		break;
		
		
	case MCMD_AFN_4_F2_MST_PARA:
		{
			CDlgPreAfn04F2 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F2();
			}
		}
		break;


	case MCMD_AFN_4_F3_CON_AUTH_PARA:
		{
			CDlgPreAfn04F3 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F3();
			}
		}
		break;

	case MCMD_AFN_4_F4_TEAM_ADDR:
		{
			CDlgPreAfn04F4 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F4();
			}
		}
		break;


	case MCMD_AFN_4_F5_CON_IP_PORT:
		{
			CDlgPreAfn04F5 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F4();
			}
		}
		break;

		
	case MCMD_AFN_4_F6_CON_CASC:
		{
			CDlgPreAfn04F6 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F4();
			}
		}
		break;

	case MCMD_AFN_4_F7_CON_DOWN_CFG:
		{
			CDlgPreAfn04F7 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;

	case MCMD_AFN_4_F9_CON_EVENT_CFG:
		{
			CDlgPreAfn04F9 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;
	case MCMD_AFN_4_F17_TML_UP_CFG:
		{
			CDlgPreAfn04F17 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;
	case MCMD_AFN_4_F10_CON_STATE_INPUT:
		{
			CDlgPreAfn04F10 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;

	case MCMD_AFN_4_F25_ELEC_MP_CFG:
		{
			CDlgPreAfn04F25_33 dlg;
			dlg.m_bF25Elec = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}
		
		break;
		
	case MCMD_AFN_4_F26_ELEC_MP_BASE:
		{
			CDlgPreAfn04F26 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}
		break;
		
	case MCMD_AFN_4_F27_ELEC_LMIT_POWER:
		{
			CDlgPreAfn04F27 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F28_ELEC_LMIT_FACTR:
		{
			CDlgPreAfn04F28 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F30_ELEC_FLASH:
		{
			CDlgPreAfn04F30 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F29_ELEC_FIX_HARM:
		{
			CDlgPreAfn04F29 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F33_NELC_MP_CFG:
		{
			CDlgPreAfn04F25_33 dlg;
			dlg.m_bF25Elec = FALSE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}
		
		break;


	case MCMD_AFN_4_F34_NELC_MP_PARA:
		{
			CDlgPreAfn04F34 dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}

		break;
	
	case MCMD_AFN_4_F35_NELC_MP_LMIT:
		{
			CDlgPreAfn04F35 dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}

	break;

	case MCMD_AFN_4_F49_FREZ_TASK_PARA:
		{
			CDlgPreAfn04F49 dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}
		
	break;

	case MCMD_AFN_A_F2_MST_PARA:
		{
			CDlgPreAfn0aF2 dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}
		
	break;

	case MCMD_AFN_A_F7_CON_DOWN_CFG:
		{
			CDlgPreAfn0AF7Q dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}
		



	}



}

