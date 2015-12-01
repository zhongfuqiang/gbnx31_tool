// TabDlgUnpack.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "TabDlgUnpack.h"
#include "NxMasterDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDlgUnpack dialog


CTabDlgUnpack::CTabDlgUnpack(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlgUnpack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabDlgUnpack)
	//}}AFX_DATA_INIT
}


void CTabDlgUnpack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDlgUnpack)
	DDX_Control(pDX, IDC_BTN_UNPACK, m_btn_unpack);
	DDX_Control(pDX, IDC_BTN_CLR_INPUT, m_btn_clr);
	DDX_Control(pDX, IDC_CHECK_TEXT, m_check_show_text);
	DDX_Control(pDX, IDC_CHECK_TREE, m_check_show_tree);
	DDX_Control(pDX, IDC_EDIT_UNPACK_CMD, m_edit_unpack);
	DDX_Control(pDX, IDC_TREE_UNPACK, m_tree_unpack);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabDlgUnpack, CDialog)
	//{{AFX_MSG_MAP(CTabDlgUnpack)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_UNPACK, OnBtnUnpack)
	ON_BN_CLICKED(IDC_BTN_CLR_INPUT, OnBtnClrInput)
	ON_EN_CHANGE(IDC_EDIT_UNPACK_CMD, OnChangeEditUnpackCmd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDlgUnpack message handlers

void CTabDlgUnpack::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

BOOL CTabDlgUnpack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_check_show_text.SetCheck(TRUE);
	setCtrlPos();
	GetDlgItem(IDC_BTN_CLR_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UNPACK)->EnableWindow(FALSE);

	m_btn_clr.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_clr.SetIcon(IDI_ICON_E);
	m_btn_clr.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_clr.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	
	m_btn_unpack.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_unpack.SetIcon(IDI_ICON_RIGHT);
	m_btn_unpack.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_unpack.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabDlgUnpack::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	setCtrlPos();
	//Invalidate(TRUE);
	// TODO: Add your message handler code here
	
}

void CTabDlgUnpack::setCtrlPos()
{
	RECT rect_client,rect_ctrl;
	GetClientRect(&rect_client);
	
	const int border = 4;
	rect_ctrl.top = 200;
	rect_ctrl.left = rect_client.left + border;
	rect_ctrl.right = rect_client.right - border;
	rect_ctrl.bottom = rect_client.bottom - border;
	if(m_tree_unpack.m_hWnd)
	{
		m_tree_unpack.MoveWindow(&rect_ctrl);

	}

}


void CTabDlgUnpack::OnBtnUnpack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_edit_unpack.GetWindowText(m_strUnpack);
	char buffer[1024] = {0};
	UINT16 usLen = 0;


    //CQgdw3761api ruler;
	CGbnx_31     ruler;
	sMcInit      sInit;
	sInit.eRole = MC_ROLE_MASTER;
	sInit.ucPermitDelayMinutes = 255;

	eMcInit(&sInit);

	CString strBuf, strLen;
	strBuf = m_strUnpack;
	strBuf.Replace(" ", "");
	strBuf.Replace("\n", "");
	strBuf.Replace("\r", "");
	strBuf.Replace("\t", "");
	strLen.Format("%d\n", strBuf.GetLength()/2);
	//strBuf += "\n";

	BOOL bOk = ruler.CStringToHexBuffer(m_strUnpack, buffer, &usLen);
	
	if(usLen == 0)
	{
		MessageBox("请输入要解析的报文", "提示", MB_OK|MB_ICONQUESTION);
		return;
	}

	m_pNxMstDlg->m_rich_edit.AppendColor("\n解析报文:", RGB(0,0,0));
	m_pNxMstDlg->m_rich_edit.AppendColor(m_strUnpack, RGB(255,0,255));

	m_pNxMstDlg->m_rich_edit.AppendColor("\n报文长度:", RGB(0,0,0));
	m_pNxMstDlg->m_rich_edit.AppendColor(strLen, RGB(0,0,255));

	// 调用解析函数，并显示


    eMcErr eRet = unpackgb31buffer(buffer, usLen);
	
	if(eRet != MC_OK)
	{
		m_pNxMstDlg->m_rich_edit.AppendColor("解析结果:", RGB(0,0,0));
		CString str = "解析失败 ";
		str+= ruler.getErrMessage(eRet);
		m_pNxMstDlg->m_rich_edit.AppendColor(str, RGB(255,0,0));
		//AfxMessageBox(str);
		m_tree_unpack.DeleteAllItems();
		Invalidate(TRUE);
		return;
	}
	
	m_pNxMstDlg->insetLineStype();
}

/*
国标能效协议(3-1)解析与结果显示

*/
eMcErr CTabDlgUnpack::unpackgb31buffer( char *pBuf, UINT16 usLen )
{
	#define USER_LEN (1024*50)
	CString strValue;
	if (!pBuf)
	{
		AfxMessageBox("unpackgb31buffer() 参数错误");
		return MC_ERR_NULL; 
	}
	
	char *pUnpackBuf = (char*)malloc(USER_LEN);
	if(!pUnpackBuf)
	{
		AfxMessageBox("unpackgb31buffer 内存申请失败");
		return MC_ERR_IO;
	}
	else
	{
// 		m_pNxMstDlg->m_rich_edit.AppendColor("\n申请成功:",RGB(0,255,0));
// 		strValue.Format("0x%X\n", pUnpackBuf);
// 		m_pNxMstDlg->m_rich_edit.AppendColor(strValue,RGB(255,0,0));

	}
	
	memset(pUnpackBuf, 0,USER_LEN);

	//CNxRuler ruler;
	sMtInit sinit;
	sinit.eRole = MT_ROLE_MASTER;
	eMtInit(&sinit);
	
	smcPack *psmcPack = (smcPack *)pUnpackBuf;
	eMcErr  eRet;

	eRet = emcUnPack(psmcPack, (UINT8*)pBuf, usLen);
	
	if(eRet == MT_OK)
	{
		// 文本显示
		if(m_check_show_text.GetCheck() == TRUE)
		{
			m_pNxMstDlg->showUnpackText31(psmcPack);
		}
		
		// 树形显示
		if(m_check_show_tree.GetCheck() == TRUE)
		{
			showUnpackTree31(psmcPack);
		}
	}
	
	if(pUnpackBuf != NULL)
	{
		free(pUnpackBuf);
// 		m_pNxMstDlg->m_rich_edit.AppendColor("\n释放成功:",RGB(0,255,0));
// 		strValue.Format("0x%X\n", pUnpackBuf);
// 		m_pNxMstDlg->m_rich_edit.AppendColor(strValue,RGB(255,0,0));
	}
	
	return eRet;

}


eMtErr CTabDlgUnpack::unpack3761buffer( char *pBuf, UINT16 usLen )
{
	if (!pBuf)
	{
		AfxMessageBox("unpack3761buffer() 参数错误");
		return MT_ERR_NULL; 
	}

	char *pUnpackBuf = (char*)malloc(MT_USER_MAX);
	if(!pUnpackBuf)
	{
		AfxMessageBox("unpack3761buffer 内存申请失败");
		return MT_ERR_IO;
	}

	memset(pUnpackBuf, 0,MT_USER_MAX);
	
	//CNxRuler ruler;
	sMtInit sinit;
	sinit.eRole = MT_ROLE_MASTER;
	eMtInit(&sinit);
	
	smtPack *psmtPack = (smtPack *)pUnpackBuf;
	eMtErr  eRet;
	
	eRet = emtUnPack(psmtPack, (UINT8*)pBuf, usLen);
	
	if(eRet == MT_OK)
	{
		// 文本显示
		if(m_check_show_text.GetCheck() == TRUE)
		{
			m_pNxMstDlg->showUnpackText(psmtPack);
		}
		
		// 树形显示
		if(m_check_show_tree.GetCheck() == TRUE)
		{
			showUnpackTree(psmtPack);
		}
	}

	vFree(pUnpackBuf);

	return eRet;
}

void CTabDlgUnpack::vFree( char *pBuf )
{
	if(!pBuf)
	{
		free(pBuf);
		pBuf = NULL;
	}
}


void CTabDlgUnpack::setMainDlg( CNxMasterDlg *pNxMstDlg )
{
	m_pNxMstDlg = pNxMstDlg;	
}




// 以树型方式显示gb31报文
void CTabDlgUnpack::showUnpackTree31( smcPack *psmtPack )
{
	if(!psmtPack)
	{
		return;
	}
	
	CString strValue;
	LOGFONT logfont;
	HTREEITEM hItem;
	char *pstr = NULL;
	eMcDir eDir;
	// 用户没有定义，使用系统字体
	CFont *pFont = GetFont();
	pFont->GetLogFont( &logfont );

	// 清空解析树
	m_tree_unpack.DeleteAllItems();
	m_tree_unpack.SetTextColor(RGB(0,0,0));

	HTREEITEM hmainroot = AddTreeItem("报文解析结果",TVI_ROOT, FALSE, RGB(139,139,0));

	// 地址域
	HTREEITEM haddress = AddTreeItem("地址域",hmainroot, FALSE, RGB(0,0,255));
	
	// 主站地址
	strValue.Format("主站地址:%d\n", psmtPack->sAddress.ucMstAddress);
	AddTreeItem(strValue,haddress, FALSE);

	// 行政区码
	strValue.Format("行政区码:%c%c%c%c%c%c\n", 
					psmtPack->sAddress.acRegionCode[0],
					psmtPack->sAddress.acRegionCode[1],
					psmtPack->sAddress.acRegionCode[2],
					psmtPack->sAddress.acRegionCode[3],
					psmtPack->sAddress.acRegionCode[4],
					psmtPack->sAddress.acRegionCode[5]);
	AddTreeItem(strValue,haddress, FALSE);
	
	// 终端地址
	strValue.Format("集中器地址:%d\n", psmtPack->sAddress.ulConAddress);
	AddTreeItem(strValue,haddress, FALSE,RGB(255,0,255));
	
	// 是组地址
	strValue.Format("是组地址:%s\n", psmtPack->sAddress.bTeam == TRUE ? "是": "否");
	AddTreeItem(strValue,haddress, FALSE);
	m_tree_unpack.Expand(haddress,TVE_EXPAND);

	/************************************************************************/
	/*     控制域                                                           */
	/************************************************************************/
	HTREEITEM hctrl =AddTreeItem("控制域",hmainroot, FALSE,RGB(255,104,32));

	// 报文方向
	eDir = psmtPack->sCtrl.eDir;
	strValue.Format("报文方向:%s\n", eDir == MT_DIR_S2M ? "上行" :  "下行");
	hItem = AddTreeItem(strValue,hctrl,FALSE, RGB(255,0,255));

    // 方向解释
	strValue.Format("%s\n", eDir == MC_DIR_S2M ? "从站到主站" :  "主站到从站");
	AddTreeItem(strValue,hItem,FALSE);


	// 启动标志
	strValue.Format("启动从动:%s\n", psmtPack->sCtrl.ePRM == MC_PRM_A2P ? "来自主动站": "来自从动站");
	AddTreeItem(strValue,hctrl,FALSE);



	// 固定帧
	if (psmtPack->bFixed == TRUE)
	{
		switch(psmtPack->sCtrl.eFcode)
        {
		case MC_FCD_LINK_OK:
            pstr = "链路确认";
            break;
			
		case MC_FCD_LOG_IN:
            pstr = "建立链路、登录系统";
            break;
			
		case MC_FCD_LOG_OUT:
            pstr = "拆除链路、退出系统";
            break;
			
		case MC_FCD_HEART_BEAT:
            pstr = "保持链路、在线心跳";
            break;
			
		default:
            pstr = "错误的功能码";
            break;			
        }
	}
	else
	{
		switch(psmtPack->sCtrl.eFcode)
        {
		case MC_FCD_OK:  
            //case MC_FCD_NOTI:
			if(psmtPack->sCtrl.ePRM == MC_PRM_A2P)
			{
				pstr = "发送/无回答";
			}
			else
			{
				pstr = "链路用户确认";
			}
			
            break;
			
		case MC_FCD_ANSWER:
            //case MC_FCD_CONF:
			if(psmtPack->sCtrl.ePRM == MC_PRM_A2P)
			{
				pstr = "以用户数据响应请求";
			}
			else
			{
				pstr = "发送/确认";
			}
			
            break;
            
		case MC_FCD_ASK:
            pstr = "请求/响应";
            break;
			
		default:
            pstr = "错误的功能码";
            break;
        }
	}

	strValue.Format("功能码值:%d %s", psmtPack->sCtrl.eFcode, pstr);
	hItem = AddTreeItem(strValue,hctrl,FALSE);



	// 地址域
	HTREEITEM hFrameType = AddTreeItem("帧类型",hmainroot, FALSE, RGB(111,0,222));
	// 是否为固定帧
	strValue.Format("封帧类型:%s\n", psmtPack->bFixed == TRUE ? "固定帧": "可变帧");
	AddTreeItem(strValue,hFrameType,FALSE);


	if (psmtPack->bFixed == TRUE )
	{
		// 数据域
		HTREEITEM hUserData = AddTreeItem("数据域", hmainroot, FALSE, RGB(60,179,67));
		

		strValue.Format("%s", pstr);
		AddTreeItem(strValue,hUserData,FALSE, RGB(255,0,255));
		m_tree_unpack.Expand(hUserData,TVE_EXPAND);
		m_tree_unpack.Expand(hmainroot,TVE_EXPAND);	
	}
	else
	{
		//多帧类型
		//psmtPack->bEC
		
		/************************************************************************/
		/*   附加域                                                            */
		/************************************************************************/
		HTREEITEM hAppend = AddTreeItem("附加域", hmainroot, FALSE, RGB(128,128,255));
		HTREEITEM hEC = AddTreeItem("事件计数",hAppend, FALSE);
		if(psmtPack->sAc.bEc == TRUE)
		{
			strValue.Format("重要事件: EC1 = %d", psmtPack->sEc.usEC1);
			AddTreeItem(strValue,hEC, FALSE);
			strValue.Format("一般事件: EC2 = %d", psmtPack->sEc.usEC2);	
			AddTreeItem(strValue,hEC, FALSE);
			
		}
		else
		{
			AddTreeItem("无",hEC, FALSE);
		}
		
		m_tree_unpack.Expand(hEC,TVE_EXPAND);
		
		HTREEITEM hTP = AddTreeItem("时间标签",hAppend, FALSE);
		if (psmtPack->sAc.bTp == TRUE)
		{
			strValue.Format("封帧时间: %02d日 %02d:%02d:%02d",
				psmtPack->sTp.sTime.ucDD,
				psmtPack->sTp.sTime.ucHH,
				psmtPack->sTp.sTime.ucmm,
				psmtPack->sTp.sTime.ucss);
			AddTreeItem(strValue,hTP,FALSE);
			
			strValue.Format("允许时延: %d分钟", psmtPack->sTp.ucPermitDelayMinutes);
			AddTreeItem(strValue,hTP,FALSE);
			m_tree_unpack.Expand(hAppend,TVE_EXPAND);
			
		}
		else
		{
			AddTreeItem("无",hTP, FALSE);
		}
		
		m_tree_unpack.Expand(hTP,TVE_EXPAND);
		
		HTREEITEM hPW = AddTreeItem("登录密码",hAppend, FALSE);
		if (psmtPack->bPw == TRUE)
		{
			char password[17] = {0};
			memcpy(password, psmtPack->aPw, 16);
			
			strValue.Format("密钥代码: %s",password);
			AddTreeItem(strValue,hPW,FALSE);
			
			m_tree_unpack.Expand(hPW,TVE_EXPAND);
		}
		else
		{
			AddTreeItem("无",hPW, FALSE);
		}
		
		// 数据域
		HTREEITEM hUserData = AddTreeItem("数据域", hmainroot, FALSE, RGB(60,179,67));
		// main cmd
		
		CGbnx_31 ruler;
		CString  strMainCmd;
		strMainCmd = ruler.GetAfnName(psmtPack->sAc.eAfn);
		strValue = "主功能码: ";
		strValue += strMainCmd;
		AddTreeItem(strValue,hUserData,FALSE, RGB(255,0,255));
		
		// sub cmd num
		if(psmtPack->usNum > 1)
		{
			int i = 0;
			int Num = psmtPack->usNum;
			strValue.Format("数据个数: %d", Num);
			AddTreeItem(strValue,hUserData,FALSE);
			UINT8 ucR, ucG, ucB;
			for (i = 0; i < Num; i++)
			{	
				ucR = rand()%255;
				ucG = rand()%255;
				ucB = rand()%255;
				
				strValue.Format("子命令: %d", i+1);
				hItem = AddTreeItem(strValue, hUserData, FALSE, RGB(ucR, ucG, ucB));
				
				AddSubCmdData31(psmtPack->sData + i, eDir,hItem, FALSE);
			}
			
			
			
		}
		else
		{
			AddSubCmdData31(psmtPack->sData,eDir,hUserData, FALSE);
		}
		m_tree_unpack.Expand(hUserData,TVE_EXPAND);
		m_tree_unpack.Expand(hmainroot,TVE_EXPAND);	
	}





	Invalidate(TRUE);

}


// 以树型方式显示3761报文
void CTabDlgUnpack::showUnpackTree( smtPack *psmtPack )
{
	if(!psmtPack)
	{
		return;
	}
	
	CString strValue;
	LOGFONT logfont;
	HTREEITEM hItem;
	eMtDir eDir;
	// 用户没有定义，使用系统字体
	CFont *pFont = GetFont();
	pFont->GetLogFont( &logfont );

	// 清空解析树
	m_tree_unpack.DeleteAllItems();
	m_tree_unpack.SetTextColor(RGB(0,0,0));

	HTREEITEM hmainroot = AddTreeItem("报文解析结果",TVI_ROOT, FALSE, RGB(139,139,0));

	// 地址域
	HTREEITEM haddress = AddTreeItem("地址域",hmainroot, FALSE, RGB(0,0,255));
	
	// 主站地址
	strValue.Format("主站地址:%d\n", psmtPack->sAddress.ucMAddress);
	AddTreeItem(strValue,haddress, FALSE);

	// 行政区码
	strValue.Format("行政区码:%c%c%c%c\n", 
					psmtPack->sAddress.acRegionCode[0],
					psmtPack->sAddress.acRegionCode[1],
					psmtPack->sAddress.acRegionCode[2],
					psmtPack->sAddress.acRegionCode[3]);
	AddTreeItem(strValue,haddress, FALSE);
	
	// 终端地址
	strValue.Format("终端地址:%d\n", psmtPack->sAddress.usTAddress);
	AddTreeItem(strValue,haddress, FALSE,RGB(255,0,255));
	
	// 是组地址
	strValue.Format("是组地址:%s\n", psmtPack->sAddress.bTeamAddr == TRUE ? "是": "否");
	AddTreeItem(strValue,haddress, FALSE);
	m_tree_unpack.Expand(haddress,TVE_EXPAND);

	/************************************************************************/
	/*     控制域                                                           */
	/************************************************************************/
	HTREEITEM hctrl =AddTreeItem("控制域",hmainroot, FALSE,RGB(255,104,32));

	// 报文方向
	eDir = psmtPack->eDir;
	strValue.Format("报文方向:%s\n", eDir == MT_DIR_S2M ? "上行" :  "下行");
	hItem = AddTreeItem(strValue,hctrl,FALSE, RGB(255,0,255));

    // 方向解释
	strValue.Format("%s\n", eDir == MT_DIR_S2M ? "从站到主站" :  "主站到从站");
	AddTreeItem(strValue,hItem,FALSE);


	// 启动标志
	strValue.Format("启动从动:%s\n", psmtPack->ePRM == MT_PRM_ACTIVE ? "来自主动站": "来自从动站");
	AddTreeItem(strValue,hctrl,FALSE);

	strValue.Format("功能码值:%d ", psmtPack->ePRM);
	hItem = AddTreeItem(strValue,hctrl,FALSE);

/*
	if(psmtPack->ePRM == MT_PRM_ACTIVE)
	{
		switch(psmtPack->sCtrl.uFCode.eFcdPrm1)
		{
		case MT_FCD_RPM1_RESET:
			strValue = "FCD_PRM_1_RESET 复位命令";		
			break;
		case MT_FCD_RPM1_USER:
			strValue = "FCD_PRM_1_USER 用户数据";		
			break;
		case MT_FCD_RPM1_LINK:
			strValue = "MT_FCD_RPM1_LINK 链路测试";		
			break;
		case MT_FCD_RPM1_ASK_1:
			strValue = "MT_FCD_RPM1_ASK_1 请求1级数据";		
			break;
		case MT_FCD_RPM1_ASK_2:
			strValue = "MT_FCD_RPM1_ASK_2 请求2级数据";		
			break;
		default:
			strValue = "FCD_PRM_1_UNKOWN";		
			break;
		}
	}
	else if(psmtPack->sCtrl.ePRM == MT_PRM_PASIVE)
	{
		switch(psmtPack->sCtrl.uFCode.eFcdPrm0)
		{
		case MT_FCD_RPM0_OK:
			strValue = "MT_FCD_RPM0_OK 认可";		
			break;
		case MT_FCD_RPM0_USER:
			strValue = "MT_FCD_RPM0_USER 用户数据";		
			break;
		case MT_FCD_RPM0_NONE:
			strValue = "MT_FCD_RPM0_NONE 否认:无所召唤的数据";		
			break;
		case MT_FCD_RPM0_LINK:
			strValue = "MT_FCD_RPM0_LINK 链路状态";		
			break;
		default:
			strValue = "FCD_PRM_1_UNKOWN 未知功能码";		
			break;
		}
		
	}
	// 功能码 详细
	hItem = AddTreeItem(strValue,hItem,FALSE);
	m_tree_unpack.Expand(hctrl,TVE_EXPAND);
	*/

	// 帧计数
	//strValue.Format("发帧计数:%d", psmtPack->ucPFC);
//	AddTreeItem(strValue,hctrl,FALSE);
	
	// 是否需要确认
	//strValue.Format("需要确认:%s", psmtPack->sSEQ.bCon == TRUE ? "是": "否");
	AddTreeItem(strValue,hctrl,FALSE);

	//多帧类型
	//psmtPack->bEC

	/************************************************************************/
	/*   附加域                                                            */
	/************************************************************************/
	HTREEITEM hAppend = AddTreeItem("附加域", hmainroot, FALSE, RGB(128,128,255));
	HTREEITEM hEC = AddTreeItem("事件计数",hAppend, FALSE);
	if(psmtPack->bEC == TRUE)
	{
		strValue.Format("重要事件: EC1 = %d", psmtPack->sEC.ucEC1);
		AddTreeItem(strValue,hEC, FALSE);
		strValue.Format("一般事件: EC2 = %d", psmtPack->sEC.ucEC2);	
		AddTreeItem(strValue,hEC, FALSE);
	
	}
	else
	{
		AddTreeItem("无",hEC, FALSE);
	}

	m_tree_unpack.Expand(hEC,TVE_EXPAND);

	HTREEITEM hTP = AddTreeItem("时间标签",hAppend, FALSE);
	if (psmtPack->bTP == TRUE)
	{
		strValue.Format("封帧时间: %02d日 %02d:%02d:%02d",
			psmtPack->sTP.sDDHHmmss.ucDD,
			psmtPack->sTP.sDDHHmmss.ucHH,
			psmtPack->sTP.sDDHHmmss.ucmm,
			psmtPack->sTP.sDDHHmmss.ucss);
		AddTreeItem(strValue,hTP,FALSE);

		strValue.Format("允许时延: %d分钟", psmtPack->sTP.ucPermitDelayMinutes);
		AddTreeItem(strValue,hTP,FALSE);
		m_tree_unpack.Expand(hAppend,TVE_EXPAND);

	}
	else
	{
		AddTreeItem("无",hTP, FALSE);
	}

	m_tree_unpack.Expand(hTP,TVE_EXPAND);

	HTREEITEM hPW = AddTreeItem("登录密码",hAppend, FALSE);
	if (psmtPack->bPW == TRUE)
	{
		char password[17] = {0};
		memcpy(password, psmtPack->acPW, 16);

		strValue.Format("密钥代码: %s",password);
		AddTreeItem(strValue,hPW,FALSE);
		
		m_tree_unpack.Expand(hPW,TVE_EXPAND);
	}
	else
	{
		AddTreeItem("无",hPW, FALSE);
	}

	// 数据域
	HTREEITEM hUserData = AddTreeItem("数据域", hmainroot, FALSE, RGB(60,179,67));
	// main cmd
	
	CQgdw3761api ruler;
	CString  strMainCmd;
	strMainCmd = ruler.GetAfnName(psmtPack->eAFN);
	strValue = "主功能码: ";
	strValue += strMainCmd;
	AddTreeItem(strValue,hUserData,FALSE, RGB(255,0,255));
	
	// sub cmd num
	if(psmtPack->usDataNum > 1)
	{
		int i = 0;
		int Num = psmtPack->usDataNum;
		strValue.Format("数据个数: %d", Num);
		AddTreeItem(strValue,hUserData,FALSE);
		UINT8 ucR, ucG, ucB;
		for (i = 0; i < Num; i++)
		{	
			ucR = rand()%255;
			ucG = rand()%255;
			ucB = rand()%255;
			
			strValue.Format("子命令: %d", i+1);
			hItem = AddTreeItem(strValue, hUserData, FALSE, RGB(ucR, ucG, ucB));

			AddSubCmdData(psmtPack->sData + i, eDir,hItem, FALSE);
		}



	}
	else
	{
		AddSubCmdData(psmtPack->sData,eDir,hUserData, FALSE);
	}


	m_tree_unpack.Expand(hUserData,TVE_EXPAND);
	m_tree_unpack.Expand(hmainroot,TVE_EXPAND);
	Invalidate(TRUE);
}



/************************************************************************/
/* 向树控件插入一条信息                                                 */
/************************************************************************/
HTREEITEM CTabDlgUnpack::AddTreeItem( CString strText, HTREEITEM hitem, BOOL bBold, COLORREF color /*= RGB(0,0,0)*/ )
{
	HTREEITEM hItemInsert;
	LOGFONT logfont;
	CFont *pFont = GetFont();
	pFont->GetLogFont( &logfont );

	hItemInsert = m_tree_unpack.InsertItem(strText,hitem);
	m_tree_unpack.SetItemFont(hItemInsert,logfont);
	m_tree_unpack.SetItemBold(hItemInsert,bBold);
	m_tree_unpack.SetItemColor(hItemInsert,color);

	return hItemInsert;	
}



/************************************************************************/
/* 插入子命令应用层数据到树型控件                                       */
/************************************************************************/
HTREEITEM CTabDlgUnpack::AddSubCmdData( sMtData *psMtData,eMtDir eDir,HTREEITEM hitem, BOOL bBold, COLORREF color /*= RGB(0,0,0)*/ )
{
	if(!psMtData)
	{
		return NULL;
	}

	HTREEITEM hItemInsert;
	CString strCmdName;
	//CNxRuler ruler;
	sMtCmdInfor cmdInfor;
	CString strValue;
	eMtErr eRet = eMtGetCmdInfor(psMtData->eCmd, eDir, &cmdInfor);
	if(eRet == MT_OK)
	{
		strCmdName = cmdInfor.pName;
	}
	else
	{
		strCmdName = "不识别的命令类型";
	}


	// 子命令ID
	strValue.Format("子功能码: %04X ", (UINT16)psMtData->eCmd);
	hItemInsert = AddTreeItem(strValue,hitem,FALSE);
	AddTreeItem(strCmdName, hItemInsert, FALSE);


	strValue.Format("测量点号: %d", (UINT16)psMtData->usPN);
	AddTreeItem(strValue,hitem,FALSE);

	strValue.Format("有无数据: %s", psMtData->bApp == TRUE ? "true" : "false");
	AddTreeItem(strValue,hitem,FALSE);
	
	
	
	switch(psMtData->eCmd)
	{
	case CMD_AFN_0_F1_ALL_OK:
	case CMD_AFN_0_F2_ALL_DENY:
		hItemInsert = AddTreeItem("数据内容: 无",hitem,FALSE);

		break;
		
		
		
	default:
		hItemInsert = AddTreeItem("数据内容: 暂不支持的命令",hitem,FALSE);
		break;
	}
	


	return  hItemInsert;
}

HTREEITEM CTabDlgUnpack::AddSubCmdData31( sMcData *psMtData,eMcDir eDir, HTREEITEM hitem, BOOL bBold, COLORREF color /*= RGB(0,0,0)*/ )
{
	if(!psMtData)
	{
		return NULL;
	}
	
	HTREEITEM hItemInsert;
	CString strCmdName;
	//CNxRuler ruler;
	sMcmdInfor cmdInfor;
	CString strValue;
	eMcErr eRet = eMcGetCmdInfor(psMtData->eCmd, eDir, &cmdInfor);
	if(eRet == MT_OK)
	{
		strCmdName = cmdInfor.pName;
	}
	else
	{
		strCmdName = "不识别的命令类型";
	}
	
	
	// 子命令ID
	strValue.Format("子功能码: %04X ", (UINT16)psMtData->eCmd);
	hItemInsert = AddTreeItem(strValue,hitem,FALSE);
	AddTreeItem(strCmdName, hItemInsert, FALSE);
	
	
	strValue.Format("测量点号: %d", (UINT16)psMtData->usPN);
	AddTreeItem(strValue,hitem,FALSE);
	
	strValue.Format("有无数据: %s", psMtData->bApp == TRUE ? "true" : "false");
	AddTreeItem(strValue,hitem,FALSE);
	
	
	
	switch(psMtData->eCmd)
	{
	case CMD_AFN_0_F1_ALL_OK:
	case CMD_AFN_0_F2_ALL_DENY:
		hItemInsert = AddTreeItem("数据内容: 无",hitem,FALSE);
		
		break;
		
		
		
	default:
		hItemInsert = AddTreeItem("数据内容: 暂不支持的命令",hitem,FALSE);
		break;
	}
	
	
	
	return  hItemInsert;
}


void CTabDlgUnpack::OnBtnClrInput() 
{
	// TODO: Add your control notification handler code here
	m_edit_unpack.SetWindowText("");
	GetDlgItem(IDC_BTN_CLR_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UNPACK)->EnableWindow(FALSE);
}

void CTabDlgUnpack::OnChangeEditUnpackCmd() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_edit_unpack.GetWindowText(m_strUnpack);
	if (m_strUnpack != "")
	{
		GetDlgItem(IDC_BTN_CLR_INPUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UNPACK)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_UNPACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CLR_INPUT)->EnableWindow(FALSE);
	}
}

void CTabDlgUnpack::unpack( CString strPack )
{
	if(strPack != "")
	{
		strPack.Replace("\n", "");
		strPack.Replace("\t", "");
		strPack.Replace("\r", "");
		//strPack.Replace(" ", "");
		char buffer[1024] = {0};
		UINT16 usLen = 0;
		
		
		//CQgdw3761api ruler;
		CGbnx_31     ruler;
		sMcInit      sInit;
		sInit.eRole = MC_ROLE_MASTER;
		sInit.ucPermitDelayMinutes = 255;
		
		eMcInit(&sInit);
		
		CString strLen;
		CString strLenTmp =strPack;
		strLenTmp.Replace(" ", "");
		
		strLen.Format("%d\n", strLenTmp.GetLength()/2);
		//strBuf += "\n";
		
		BOOL bOk = ruler.CStringToHexBuffer(strPack, buffer, &usLen);
		
		if(usLen == 0)
		{
			MessageBox("请输入要解析的报文", "提示", MB_OK|MB_ICONQUESTION);
			return;
		}
		
		m_pNxMstDlg->m_rich_edit.AppendColor("\n解析报文:", RGB(0,0,0));
		m_pNxMstDlg->m_rich_edit.AppendColor(strPack, RGB(255,0,255));
		
		m_pNxMstDlg->m_rich_edit.AppendColor("\n报文长度:", RGB(0,0,0));
		m_pNxMstDlg->m_rich_edit.AppendColor(strLen, RGB(0,0,255));
		
		// 调用解析函数，并显示
		
		
		eMcErr eRet = unpackgb31buffer(buffer, usLen);
		
		if(eRet != MC_OK)
		{
			m_pNxMstDlg->m_rich_edit.AppendColor("解析结果:", RGB(0,0,0));
			CString str = "解析失败 ";
			str+= ruler.getErrMessage(eRet);
			m_pNxMstDlg->m_rich_edit.AppendColor(str, RGB(255,0,0));
			//AfxMessageBox(str);
			m_tree_unpack.DeleteAllItems();
			Invalidate(TRUE);
			return;
		}
		
		m_pNxMstDlg->insetLineStype();
	}
	




}
