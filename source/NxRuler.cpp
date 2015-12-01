// NxRuler.cpp: implementation of the CNxRuler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NxMaster.h"
#include "NxRuler.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#if 0
#define  MT_DBG_ON // 调试开关
//#undef   MT_DBG_ON


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNxRuler::CNxRuler()
{
	m_role = MT_ROLE_MASTER;
	initMapCmdInfor();
	m_bInit = FALSE;
}

CNxRuler::CNxRuler( eMtRole eRole )
{

	m_bInit = FALSE;
	m_role = eRole;
	initMapCmdInfor();
}

CNxRuler::~CNxRuler()
{

}


/*****************************************************************************
 函 数 名  : eMtGetCmdInfor
 功能描述  : 获得该命令字对应的信息
 输入参数  : eMtCmd eCmd           
             eMtDir eDir           
             sMtCmdInfor *psInfor  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月21日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::eMtGetCmdInfor(eMtCmd eCmd, eMtDir eDir, sMtCmdInfors *psInfors)
{
	if(psInfors == NULL)
	{
		return MT_NULL;
	}

	sMtCmdInfors sCmdInfors;


/*  map 方式
	BOOL bHave = m_mapCmdInfor.Lookup(eCmd, sCmdInfors);
	if(bHave == TRUE)
	{
		if(sCmdInfors.eDir == eDir || sCmdInfors.eDir == MT_DIR_ALL)
		{
			*psInfors = sCmdInfors;
			return MT_OK;
		}
	}

*/



	/* vector 方式	*/

    int nCount = 0;
	int i = 0;

	nCount = m_vCmdInfor.size();
	for (i = 0; i < nCount; i++)
	{
		sCmdInfors = m_vCmdInfor.at(i);
		if((sCmdInfors.eCmd == eCmd) && (sCmdInfors.eDir == eDir || sCmdInfors.eDir ==  MT_DIR_ALL))
		{
			*psInfors = sCmdInfors;
			return MT_OK;
		}
	}
	
	

	return MT_NONE;
}

eMtRole CNxRuler::eMtWhoAmI()
{
	return m_role;
}





eMtAFN CNxRuler::GetCmdAfn(eMtCmd eCmd)
{	
	UINT16 usCmd = (UINT16)eCmd;
	UINT8  ucAfn = (usCmd & 0xFF00) >> 8;
	eMtAFN eAfn  = (eMtAFN)ucAfn;   
	
	
	switch(eAfn)
	{
		
	case AFN_00_CONF:
	case AFN_01_RSET:
	case AFN_02_LINK:
	case AFN_03_RELY:
	case AFN_04_SETP:
	case AFN_05_CTRL:
	case AFN_06_AUTH:
	case AFN_08_CASC:
	case AFN_09_CFIG:
	case AFN_0A_GETP:
	case AFN_0B_ASKT:
	case AFN_0C_ASK1:
	case AFN_0D_ASK2:
	case AFN_0E_ASK3:
	case AFN_0F_FILE:
	case AFN_10_DATA:
	break;
					
					// 没有对应的afn
	default:
		eAfn = AFN_NULL;
		break;
	}

    return eAfn;
}

/*****************************************************************************
 函 数 名  : GetResponeAfn
 功能描述  : 通过收到命令的标识 及 收到方身份获得应该回复的afn类型，不回复或是没有找到对应的类型
		     return AFN_NULL
 输入参数  : eMtCmd eCmd
			 eMtRole eRole
			                    
 输出参数  :  
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月13日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtAFN CNxRuler::GetResponeAfn(eMtRole eRole, eMtCmd eCmd)
{
	eMtAFN eAfn,eResAfn;
	eAfn = GetCmdAfn(eCmd);

	if(eAfn == AFN_NULL)
	{
		return AFN_NULL;
	}


	if (MT_ROLE_MASTER == eRole)
	{
		switch(eAfn)
		{
		case AFN_00_CONF:
			eResAfn = AFN_NULL;
			break;


		default:
			break;

		}
	}
	else if(MT_ROLE_CONTOR == eRole)
	{
		switch(eAfn)
		{
		case AFN_00_CONF:
			eResAfn = AFN_NULL;
			break;
	//	case :

			//break;
			
			
		default:
			break;
			
		}

	}
	else
	{
		eResAfn = AFN_NULL;
	}

	return eResAfn;
}

void CNxRuler::SetAtMap(eMtCmd eCmd, eMtDir eDir, eMtPn ePn, pNxTransFunc pFunc, CString strName)
{
	sMtCmdInfors sCmdInfor;
	sCmdInfor.eCmd   = eCmd;
	sCmdInfor.eDir    = eDir;
	sCmdInfor.ePn     = ePn;
	sCmdInfor.pFunc   = pFunc;
	sCmdInfor.strName = strName;	
    //m_mapCmdInfor.SetAt(eCmd, sCmdInfor);
	m_vCmdInfor.push_back(sCmdInfor);
}

/*****************************************************************************
 函 数 名  : initMapCmdInfor
 功能描述  : 初始化m_mapCmdInfor 成员，该函数应在应用协议模块前调用
		     重要函数
 输入参数  : 			 		                    
 输出参数  :  
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月13日
    作    者   : liming
    修改内容   : 新生成函数
	
*****************************************************************************/
void CNxRuler::initMapCmdInfor()
{

    /* (0)确认∕否认（AFN=00H） */
    // 双向
    SetAtMap(CMD_AFN_0_FN_1_ALL_OK,     MT_DIR_ALL, MT_PN_0,  NULL,     "全部确认：对收到报文中的全部数据单元标识进行确认");
    SetAtMap(CMD_AFN_0_FN_2_ALL_DENY,   MT_DIR_ALL, MT_PN_0,  NULL,     "全部否认：对收到报文中的全部数据单元标识进行否认");
    SetAtMap(CMD_AFN_0_FN_3_ONE_BY_ONE, MT_DIR_ALL, MT_PN_0,  emtTrans_OneByOne,     "按数据单元标识确认和否认：对收到报文中的全部数据单元标识进行逐个确认/否认");

    /* (1)复位命令（AFN=01H） */
    // 下行
    SetAtMap(CMD_AFN_1_FN_1_HARD_INIT,  MT_DIR_M2S, MT_PN_0,  NULL,     "硬件初始化");
    SetAtMap(CMD_AFN_1_FN_2_DATA_INIT,  MT_DIR_M2S, MT_PN_0,  NULL,     "数据区初始化");
    SetAtMap(CMD_AFN_1_FN_3_FACTORY_RESET, MT_DIR_M2S, MT_PN_0,  NULL,  "参数及全体数据区初始化（即恢复至出厂配置）");
    SetAtMap(CMD_AFN_1_FN_4_PARA_INIT,  MT_DIR_M2S, MT_PN_0,  NULL,     "参数（除与系统主站通信有关的）及全体数据区初始化");

    // 上行
    // 确认∕否认（AFN=00H)

    /* (2) 链路接口检测（AFN=02H） */
    // 下行
    // 确认∕否认（AFN=00H)
     
    // 上行
    SetAtMap(CMD_AFN_2_FN_1_LOG_IN,     MT_DIR_S2M, MT_PN_0,  NULL,     "登录");
    SetAtMap(CMD_AFN_2_FN_2_LOG_OUT,    MT_DIR_S2M, MT_PN_0,  NULL,     "退出登录");
    SetAtMap(CMD_AFN_2_FN_3_HEART_BEAT, MT_DIR_S2M, MT_PN_0,  NULL,     "心跳");

    /* (4) 设置参数（AFN == 04H） */
    // 下行
	SetAtMap(CMD_AFN_4_FN_1_CON_UP_CFG,    MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F1_ConUpPortPara, "集中器上行通信口通信参数设置");
	//SetAtMap(CMD_AFN_4_FN_2_CON_UP_WAY_ETH,MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F2_ConUpPortParaWireless, "集中器上行通信工作方式（以太专网或虚拟专网）");
	SetAtMap(CMD_AFN_4_FN_2_CON_UP_REWORD,MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F2_ConUpPortParaWireless, "集中器上行通信工作方式（以太专网或虚拟专网）");

	SetAtMap(CMD_AFN_4_FN_3_MST_IP_PORT,   MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F3_MasterIpPort,   "主站IP地址和端口"); 
	SetAtMap(CMD_AFN_4_FN_4_PHONE_MST_SMS, MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F4_MstSmsPhone, "主站电话号码和短信中心号码");  
	SetAtMap(CMD_AFN_4_FN_5_CON_UP_PARA,   MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F5_UpMsgAuth,     "集中器上行通信消息认证参数设置");
	SetAtMap(CMD_AFN_4_FN_6_TEAM_ADDR,     MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04f6_ConGroupAddr,   "集中器组地址设置");
	SetAtMap(CMD_AFN_4_FN_7_CON_IP_PORT,   MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F7_ConIpPort,      "集中器IP地址和端口"); 
	SetAtMap(CMD_AFN_4_FN_8_CON_UP_WAY,    MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F8_ConUpComWay,   "集中器上行通信工作方式（以太专网或虚拟专网）"); 
	SetAtMap(CMD_AFN_4_FN_9_CFG_TML_MNT,   MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F9_Con2TmlComPara,"集中器与终端通信读取数据运行参数设置");
	SetAtMap(CMD_AFN_4_FN_10_CON_DOWN_CFG, MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F10_ConDownPara, "集中器下行通信模块的参数设置");
	SetAtMap(CMD_AFN_4_FN_11_VPN_PWD,      MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F11_VpnPwd,      "虚拟专网用户名、密码"); 
	SetAtMap(CMD_AFN_4_FN_12_CON_UP_LIMIT, MT_DIR_M2S, MT_PN_0,   emt_trans_Afn04F12_ConUpLimit,  "集中器上行通信流量门限设置"); 
	SetAtMap(CMD_AFN_4_FN_13_CON_CASC_CFG, MT_DIR_M2S, MT_PN_0,    NULL, "集中器级联通信参数数据单元格式"); 
    SetAtMap(CMD_AFN_4_FN_17_CFG_EVENT,    MT_DIR_M2S, MT_PN_0,    NULL, "集中器事件记录配置设置"); 
    SetAtMap(CMD_AFN_4_FN_18_CFG_TM_STATE, MT_DIR_M2S, MT_PN_0,    NULL, "集中器状态量输入参数"); 
    SetAtMap(CMD_AFN_4_FN_19_CFG_METERING, MT_DIR_M2S, MT_PN_0,    NULL, "计量表基本配置基本参数"); 
    SetAtMap(CMD_AFN_4_FN_25_POWER_LIMIT,  MT_DIR_M2S, MT_PN_0,    NULL, "电能量限值参数"); 
    SetAtMap(CMD_AFN_4_FN_26_FACTOR_LIMIT, MT_DIR_M2S, MT_PN_0,    NULL, "测量点功率因数分段限值"); 
    SetAtMap(CMD_AFN_4_FN_28_CFG_POWER,    MT_DIR_M2S, MT_PN_0,    NULL, "电能类数据配置参数"); 
    SetAtMap(CMD_AFN_4_FN_29_CFG_UN_POWER, MT_DIR_M2S, MT_PN_0,    NULL, "非电量数据配置参数"); 
    //SetAtMap(CMD_AFN_4_FN_33_TIMING_REPORT_1, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报1类数据任务设置"); 
    SetAtMap(CMD_AFN_4_FN_33_CFG_NOT_ELEC, MT_DIR_M2S, MT_PN_TP,    emtTrans_CfgNotElecValue, "非电气测量点数据参数配置"); 
    SetAtMap(CMD_AFN_4_FN_34_TIMING_REPORT_2, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报2类数据任务设置"); 
    SetAtMap(CMD_AFN_4_FN_35_STOP_TIMING_REPORT_1, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报1类数据任务启动/停止设置"); 
    SetAtMap(CMD_AFN_4_FN_36_STOP_TIMING_REPORT_2, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报2类数据任务启动/停止设置"); 
    SetAtMap(CMD_AFN_4_FN_41_CFG_TML_MNT,   MT_DIR_M2S, MT_PN_0,    NULL, "终端配置基本参数设置"); 
    SetAtMap(CMD_AFN_4_FN_42_CFG_TML_STATE, MT_DIR_M2S, MT_PN_0,    NULL, "终端状态量输入参数"); 
    SetAtMap(CMD_AFN_4_FN_43_CFG_TML_TRANS, MT_DIR_M2S, MT_PN_0,    NULL, "终端透传设备配置"); 
    // 上行
    // 确认∕否认（AFN=00H)
  
    /* (5) 控制命令（AFN=05H） */
    // 下行
    SetAtMap(CMD_AFN_5_FN_1_REMOTE_SWITCH_OFF, MT_DIR_M2S, MT_PN_TM, emt_trans_Afn05F1_RemoteCtrlTrip, "遥控跳闸"); 
    SetAtMap(CMD_AFN_5_FN_2_PERMIT_SWITCH_ON,  MT_DIR_M2S, MT_PN_TM, NULL, "允许合闸"); 
    SetAtMap(CMD_AFN_5_FN_29_STRT_AUTO_REPORT, MT_DIR_M2S, MT_PN_0,  NULL, "允许集中器主动上报"); 
    SetAtMap(CMD_AFN_5_FN_31_TIME_TICK,        MT_DIR_M2S, MT_PN_0,  emt_trans_Afn05F31_TimeTick, "对时命令"); 
    SetAtMap(CMD_AFN_5_FN_37_STOP_AUTO_REPORT, MT_DIR_M2S, MT_PN_0,  NULL, "禁止集中器主动上报"); 
    SetAtMap(CMD_AFN_5_FN_38_LINK_MST_TML,     MT_DIR_M2S, MT_PN_0,  NULL, "激活集中器连接主站"); 
    SetAtMap(CMD_AFN_5_FN_39_UNLINK_MST_TML,   MT_DIR_M2S, MT_PN_0,  NULL, "命令集中器断开连接"); 
    SetAtMap(CMD_AFN_5_FN_49_PORT_TML_SUSPEND, MT_DIR_M2S, MT_PN_0,  emt_trans_Afn05F49_PortSuspend, "命令指定通信端口暂停与终端通信读取数据"); 
    SetAtMap(CMD_AFN_5_FN_50_PORT_TML_RESUME,  MT_DIR_M2S, MT_PN_0,  emt_trans_Afn05F50_PortResume, "命令指定通信端口恢复与终端通信读取数据"); 
    SetAtMap(CMD_AFN_5_FN_51_PORT_TML_AGAIN,   MT_DIR_M2S, MT_PN_0,  emt_trans_Afn05F51_PortAgain, "命令指定通信端口重新与终端通信读取数据"); 
    SetAtMap(CMD_AFN_5_FN_52_INIT_ROUT_INFO,   MT_DIR_M2S, MT_PN_0,  NULL, "初始化指定通信端口下的全部中继路由信息"); 
    SetAtMap(CMD_AFN_5_FN_53_DEL_ALL_TML,      MT_DIR_M2S, MT_PN_0,  NULL, "删除指定通信端口下的全部终端"); 

    // 上行
    // 确认∕否认（AFN=00H)
  
    /* (6) 身份认证及密钥协商（AFN=06H） */
    // 下行
    SetAtMap(CMD_AFN_6_FN_1_ID_AUTH_Q,   MT_DIR_ALL, MT_PN_0,  emt_trans_Afn06F1_IdAuthQ, "身份认证请求");
    SetAtMap(CMD_AFN_6_FN_2_ID_AUTH_A,   MT_DIR_ALL, MT_PN_0,  emt_trans_Afn06F2_IdAuthA, "身份认证响应"); 
    SetAtMap(CMD_AFN_6_FN_3_RAND_Q,      MT_DIR_ALL, MT_PN_0,  emt_trans_Afn06F3_RandQ,   "取随机数请求"); 
    SetAtMap(CMD_AFN_6_FN_4_RAND_A,      MT_DIR_ALL, MT_PN_0,  emt_trans_Afn06F4_RandA,   "取随机数响应"); 


    /* (9) 请求集中器配置及信息（AFN=09H） */
    // 下行
//     SetAtMap(CMD_AFN_9_FN_1_CON_VERSION,       MT_DIR_M2S, MT_PN_0,  NULL,   "集中器版本信息"); 
//     SetAtMap(CMD_AFN_9_FN_4_SUPPORT_PARA_CFG,  MT_DIR_M2S, MT_PN_0,  NULL,   "集中器支持的参数配置"); 
//     SetAtMap(CMD_AFN_9_FN_5_SUPPORT_CTRL_CFG,  MT_DIR_M2S, MT_PN_0,  NULL,   "集中器支持的控制配置"); 
//     SetAtMap(CMD_AFN_9_FN_6_SUPPORT_ASK1_CFG,  MT_DIR_M2S, MT_PN_0,  NULL,   "集中器支持的1类数据配置"); 
//     SetAtMap(CMD_AFN_9_FN_7_SUPPORT_ASK2_CFG,  MT_DIR_M2S, MT_PN_0,  NULL,   "集中器支持的2类数据配置"); 
// 	SetAtMap(CMD_AFN_9_FN_8_SUPPORT_EVNT_CFG,  MT_DIR_M2S, MT_PN_0,  NULL,   "集中器支持的事件记录配置"); 

    // 上行 
    SetAtMap(CMD_AFN_9_FN_1_CON_VERSION,       MT_DIR_ALL, MT_PN_0,  emt_trans_Afn09F1_ConVersion,   "集中器版本信息"); 
    SetAtMap(CMD_AFN_9_FN_4_SUPPORT_PARA_CFG,  MT_DIR_ALL, MT_PN_0,  emt_trans_Afn09F4_ConParaCfg,   "集中器支持的参数配置"); 
    SetAtMap(CMD_AFN_9_FN_5_SUPPORT_CTRL_CFG,  MT_DIR_ALL, MT_PN_0,  emt_trans_Afn09F5_ConCtrlCfg,   "集中器支持的控制配置"); 
    SetAtMap(CMD_AFN_9_FN_6_SUPPORT_ASK1_CFG,  MT_DIR_ALL, MT_PN_0,  emt_trans_Afn09F6_ConAsk1Cfg,   "集中器支持的1类数据配置"); 
    SetAtMap(CMD_AFN_9_FN_7_SUPPORT_ASK2_CFG,  MT_DIR_ALL, MT_PN_0,  emt_trans_Afn09F7_ConAsk2Cfg,   "集中器支持的2类数据配置"); 
	SetAtMap(CMD_AFN_9_FN_8_SUPPORT_EVNT_CFG,  MT_DIR_ALL, MT_PN_0,  emt_trans_Afn09F8_ConEvntCfg,   "集中器支持的事件记录配置"); 



    /* (10)  查询参数（AFN=0AH） */
    // 下行
//     SetAtMap(CMD_AFN_A_FN_1_CON_UP_CFG,       MT_DIR_M2S, MT_PN_0,   NULL, "集中器上行通信口通信参数设置");
// 	SetAtMap(CMD_AFN_A_FN_2_CON_UP_WAY_ETH,   MT_DIR_M2S, MT_PN_0,   NULL, "集中器上行通信工作方式（以太专网或虚拟专网）");
// 	SetAtMap(CMD_AFN_A_FN_3_MST_IP_PORT,      MT_DIR_M2S, MT_PN_0,   NULL,   "主站IP地址和端口"); 
// 	SetAtMap(CMD_AFN_A_FN_4_PHONE_MST_SMS,    MT_DIR_M2S, MT_PN_0,   NULL, "主站电话号码和短信中心号码");  
// 	SetAtMap(CMD_AFN_A_FN_5_CON_UP_PARA,      MT_DIR_M2S, MT_PN_0,   NULL,     "集中器上行通信消息认证参数设置");
// 	SetAtMap(CMD_AFN_A_FN_6_TEAM_ADDR,        MT_DIR_M2S, MT_PN_0,   NULL,   "集中器组地址设置");
// 	SetAtMap(CMD_AFN_A_FN_7_CON_IP_PORT,      MT_DIR_M2S, MT_PN_0,   NULL,      "集中器IP地址和端口"); 
// 	SetAtMap(CMD_AFN_A_FN_8_CON_UP_WAY,       MT_DIR_M2S, MT_PN_0,   NULL,   "集中器上行通信工作方式（以太专网或虚拟专网）"); 
// 	SetAtMap(CMD_AFN_A_FN_9_CFG_TML_MNT,      MT_DIR_M2S, MT_PN_0,   NULL,"集中器与终端通信读取数据运行参数设置");
// 	SetAtMap(CMD_AFN_A_FN_10_CON_DOWN_CFG,    MT_DIR_M2S, MT_PN_0,   NULL, "集中器下行通信模块的参数设置");
// 	SetAtMap(CMD_AFN_A_FN_11_VPN_PWD,         MT_DIR_M2S, MT_PN_0,   NULL,      "虚拟专网用户名、密码"); 
// 	SetAtMap(CMD_AFN_A_FN_12_CON_UP_LIMIT,    MT_DIR_M2S, MT_PN_0,   NULL,  "集中器上行通信流量门限设置"); 
// 	SetAtMap(CMD_AFN_A_FN_13_CON_CASC_CFG,    MT_DIR_M2S, MT_PN_0,    NULL, "集中器级联通信参数数据单元格式"); 
//     SetAtMap(CMD_AFN_A_FN_17_CFG_EVENT,       MT_DIR_M2S, MT_PN_0,    NULL,    "集中器事件记录配置设置"); 
//     SetAtMap(CMD_AFN_A_FN_18_CFG_TM_STATE,    MT_DIR_M2S, MT_PN_0,    NULL, "集中器状态量输入参数"); 
//     SetAtMap(CMD_AFN_A_FN_19_CFG_METERING,    MT_DIR_M2S, MT_PN_0,    NULL, "计量表基本配置基本参数"); 
//     SetAtMap(CMD_AFN_A_FN_25_POWER_LIMIT,     MT_DIR_M2S, MT_PN_0,    NULL, "电能量限值参数"); 
//     SetAtMap(CMD_AFN_A_FN_26_FACTOR_LIMIT,    MT_DIR_M2S, MT_PN_0,    NULL, "测量点功率因数分段限值"); 
//     SetAtMap(CMD_AFN_A_FN_28_CFG_POWER,       MT_DIR_M2S, MT_PN_0,    NULL, "电能类数据配置参数"); 
//     SetAtMap(CMD_AFN_A_FN_29_CFG_UN_POWER,    MT_DIR_M2S, MT_PN_0,    NULL, "非电量数据配置参数"); 
//     SetAtMap(CMD_AFN_A_FN_33_TIMING_REPORT_1, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报1类数据任务设置"); 
//     SetAtMap(CMD_AFN_A_FN_34_TIMING_REPORT_2, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报2类数据任务设置"); 
//     SetAtMap(CMD_AFN_A_FN_35_STOP_TIMING_REPORT_1, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报1类数据任务启动/停止设置"); 
//     SetAtMap(CMD_AFN_A_FN_36_STOP_TIMING_REPORT_2, MT_DIR_M2S, MT_PN_0,    NULL, "定时上报2类数据任务启动/停止设置"); 
//     SetAtMap(CMD_AFN_A_FN_41_CFG_TML_MNT,   MT_DIR_M2S, MT_PN_0,    NULL, "终端配置基本参数设置"); 
//     SetAtMap(CMD_AFN_A_FN_42_CFG_TML_STATE, MT_DIR_M2S, MT_PN_0,    NULL, "终端状态量输入参数"); 
//     SetAtMap(CMD_AFN_A_FN_43_CFG_TML_TRANS, MT_DIR_M2S, MT_PN_0,    NULL, "终端透传设备配置"); 

    // 上行 
    SetAtMap(CMD_AFN_A_FN_1_CON_UP_CFG,       MT_DIR_S2M, MT_PN_0,   NULL, "集中器上行通信口通信参数设置");
	SetAtMap(CMD_AFN_A_FN_2_CON_UP_WAY_ETH,   MT_DIR_S2M, MT_PN_0,   NULL, "集中器上行通信工作方式（以太专网或虚拟专网）");
	SetAtMap(CMD_AFN_A_FN_3_MST_IP_PORT,      MT_DIR_S2M, MT_PN_0,   NULL,   "主站IP地址和端口"); 
	SetAtMap(CMD_AFN_A_FN_4_PHONE_MST_SMS,    MT_DIR_S2M, MT_PN_0,   NULL, "主站电话号码和短信中心号码");  
	SetAtMap(CMD_AFN_A_FN_5_CON_UP_PARA,      MT_DIR_S2M, MT_PN_0,   NULL,     "集中器上行通信消息认证参数设置");
	SetAtMap(CMD_AFN_A_FN_6_TEAM_ADDR,        MT_DIR_S2M, MT_PN_0,   NULL,   "集中器组地址设置");
	SetAtMap(CMD_AFN_A_FN_7_CON_IP_PORT,      MT_DIR_S2M, MT_PN_0,   NULL,      "集中器IP地址和端口"); 
	SetAtMap(CMD_AFN_A_FN_8_CON_UP_WAY,       MT_DIR_S2M, MT_PN_0,   NULL,   "集中器上行通信工作方式（以太专网或虚拟专网）"); 
	SetAtMap(CMD_AFN_A_FN_9_CFG_TML_MNT,      MT_DIR_S2M, MT_PN_0,   NULL,"集中器与终端通信读取数据运行参数设置");
	SetAtMap(CMD_AFN_A_FN_10_CON_DOWN_CFG,    MT_DIR_S2M, MT_PN_0,   NULL, "集中器下行通信模块的参数设置");
	SetAtMap(CMD_AFN_A_FN_11_VPN_PWD,         MT_DIR_S2M, MT_PN_0,   NULL,      "虚拟专网用户名、密码"); 
	SetAtMap(CMD_AFN_A_FN_12_CON_UP_LIMIT,    MT_DIR_S2M, MT_PN_0,   NULL,  "集中器上行通信流量门限设置"); 
	SetAtMap(CMD_AFN_A_FN_13_CON_CASC_CFG,    MT_DIR_S2M, MT_PN_0,    NULL, "集中器级联通信参数数据单元格式"); 
    SetAtMap(CMD_AFN_A_FN_17_CFG_EVENT,       MT_DIR_S2M, MT_PN_0,    NULL,    "集中器事件记录配置设置"); 
    SetAtMap(CMD_AFN_A_FN_18_CFG_TM_STATE,    MT_DIR_S2M, MT_PN_0,    NULL, "集中器状态量输入参数"); 
    SetAtMap(CMD_AFN_A_FN_19_CFG_METERING,    MT_DIR_S2M, MT_PN_0,    NULL, "计量表基本配置基本参数"); 
    SetAtMap(CMD_AFN_A_FN_25_POWER_LIMIT,     MT_DIR_S2M, MT_PN_0,    NULL, "电能量限值参数"); 
    SetAtMap(CMD_AFN_A_FN_26_FACTOR_LIMIT,    MT_DIR_S2M, MT_PN_0,    NULL, "测量点功率因数分段限值"); 
    SetAtMap(CMD_AFN_A_FN_28_CFG_POWER,       MT_DIR_S2M, MT_PN_0,    NULL, "电能类数据配置参数"); 
    SetAtMap(CMD_AFN_A_FN_29_CFG_UN_POWER,    MT_DIR_S2M, MT_PN_0,    NULL, "非电量数据配置参数"); 
    SetAtMap(CMD_AFN_A_FN_33_TIMING_REPORT_1, MT_DIR_S2M, MT_PN_0,    NULL, "定时上报1类数据任务设置"); 
    SetAtMap(CMD_AFN_A_FN_34_TIMING_REPORT_2, MT_DIR_S2M, MT_PN_0,    NULL, "定时上报2类数据任务设置"); 
    SetAtMap(CMD_AFN_A_FN_35_STOP_TIMING_REPORT_1, MT_DIR_S2M, MT_PN_0,    NULL, "定时上报1类数据任务启动/停止设置"); 
    SetAtMap(CMD_AFN_A_FN_36_STOP_TIMING_REPORT_2, MT_DIR_S2M, MT_PN_0,    NULL, "定时上报2类数据任务启动/停止设置"); 
    SetAtMap(CMD_AFN_A_FN_41_CFG_TML_MNT,   MT_DIR_S2M, MT_PN_0,    NULL, "终端配置基本参数设置"); 
    SetAtMap(CMD_AFN_A_FN_42_CFG_TML_STATE, MT_DIR_S2M, MT_PN_0,    NULL, "终端状态量输入参数"); 
    SetAtMap(CMD_AFN_A_FN_43_CFG_TML_TRANS, MT_DIR_S2M, MT_PN_0,    NULL, "终端透传设备配置"); 
  
    /* (11) 请求任务数据（AFN=0BH） */
    // 下行
    SetAtMap(CMD_AFN_B_FN_1_TIMING_REPORT_1, MT_DIR_M2S, MT_PN_0,    NULL, "终端状态量输入参数"); 
    SetAtMap(CMD_AFN_B_FN_2_TIMING_REPORT_2, MT_DIR_M2S, MT_PN_0,    NULL, "终端透传设备配置"); 

    // 上行 
    // CMD_AFN_B_FN_1_TIMING_REPORT_1 请求1类数据（AFN=0CH）的上行报文应答
    // CMD_AFN_B_FN_1_TIMING_REPORT_2 请求2类数据（AFN=0DH）的上行报文应答
  
    /* (12) 请求1类数据（AFN=0CH） */


	// 下行
	SetAtMap(CMD_AFN_C_FN_90_NOT_ELEC, MT_DIR_M2S, MT_PN_TP,    emtTrans_NotElecValue, "非电气量");
	
	
	// 上行 
	SetAtMap(CMD_AFN_C_FN_90_NOT_ELEC, MT_DIR_S2M, MT_PN_TP,    emtTrans_NotElecValue, "非电气量");

   
    
		


  
    /* (13) 请求2类数据（AFN=0DH） */
    // 下行
    

    // 上行 

  
    /* (14) 请求3类数据（AFN=0EH） */
    // 下行
    

    // 上行 

    /* (15) 文件传输（AFN=0FH） */
  
    /* (16) 数据转发（AFN=10H） */
    // 下行
    

    // 上行 

    SetAtMap(CMD_AFN_FN_MAX, MT_DIR_UNKOWN, MT_PN_0,  NULL,     "最大命令码, 没有实际意义");

}





// 全局函数



/*****************************************************************************
 函 数 名  : eMtTransDaDt_to_PnFn_g
 功能描述  : 将数据信息单元标识从DaDt结构转换为PnFn结构
 输入参数  : sMtDaDt *psDaDt  
             sMtPnFn *psPnFn  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr eMtTransDaDt_to_PnFn_g(sMtDaDt *psDaDt, sMtPnFn *psPnFn)
{
	if(!psPnFn || !psDaDt)
	{
		return MT_NULL;
	}

	if(psDaDt->ucDT2 > 30)
	{
		return MT_OUT_RNG;
	}

    UINT8 ucShift = 0;

    if(psDaDt->ucDA1 == 0 && psDaDt->ucDA2 == 0)
    {
        psPnFn->usPn = 0;
    }
    else
    {
        switch(psDaDt->ucDA1)
        {
            case 0x01:
                ucShift = 1;
                break;
                
            case 0x02:
                ucShift = 2; 
                break;
                
            case 0x04:
                ucShift = 3;
                break;
                
            case 0x08:
                ucShift = 4; 
                break;

            case 0x10:
                ucShift = 5;
                break;
                
            case 0x20:
                ucShift = 6; 
                break;
                
            case 0x40:
                ucShift = 7;
                break;
                
            case 0x80:
                ucShift = 8; 
                break;

            default:
                  return MT_ERR_PARA;
                  //break;

        }
        
       psPnFn->usPn = ((psDaDt->ucDA2 - 1) * 8 + ucShift);
    }


    if(psDaDt->ucDT1 == 0 && psDaDt->ucDT2 == 0)
    {
        psPnFn->usFn = 0;
    }
    else
    {
         switch(psDaDt->ucDT1)
        {
            case 0x01:
                ucShift = 1;
                break;
                
            case 0x02:
                ucShift = 2; 
                break;
                
            case 0x04:
                ucShift = 3;
                break;
                
            case 0x08:
                ucShift = 4; 
                break;

            case 0x10:
                ucShift = 5;
                break;
                
            case 0x20:
                ucShift = 6; 
                break;
                
            case 0x40:
                ucShift = 7;
                break;
                
            case 0x80:
                ucShift = 8; 
                break;

            default:
                  return MT_ERR_PARA;
                  //break;

        }

        psPnFn->usFn = (psDaDt->ucDT2 * 8 + ucShift);

    }
    
    #ifdef MT_DBG_ON
    printf("eMtTransDaDt_to_PnFn() in sPnFn.usfn = %d sPnFn.usPn = %d\n", psPnFn->usFn, psPnFn->usPn);
    printf("eMtTransDaDt_to_PnFn() out Da1 = %d Da2 = %d Dt1 = %d Dt2 = %d\n", 
            psDaDt->ucDA1,
            psDaDt->ucDA2,
            psDaDt->ucDT1,
            psDaDt->ucDT2);
    #endif 
	return MT_OK;
}
/*****************************************************************************
 函 数 名  : eMtTransPnFn_to_DaDt_g
 功能描述  : 将数据信息标识从PnFn结构转换为Data结构
 输入参数  : sMtPnFn *psPnFn  
             sMtDaDt *psDaDt  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr eMtTransPnFn_to_DaDt_g(sMtPnFn *psPnFn, sMtDaDt *psDaDt)
{
	if(!psPnFn || !psDaDt)
	{
		return MT_NULL;
	}
	
	if(psPnFn->usPn > MT_DA_PN_MAX || psPnFn->usFn > MT_DT_FN_MAX)
	{
		return MT_OUT_RNG;
	}
	
    UINT8 ucShift = 0; 
    UINT8 ucMask  = 0x01;
    
    if(psPnFn->usPn == 0)
    {
        psDaDt->ucDA1 = 0;
        psDaDt->ucDA2 = 0;
    }
    else
    {
        ucShift = psPnFn->usPn % 8;
        ucShift = ucShift == 0 ? 7 : (ucShift -1);
        psDaDt->ucDA1 = (UINT8)(ucMask << ucShift);
		psDaDt->ucDA2 = (UINT8)((psPnFn->usPn - 1) / 8 + 1);
    }
	
	if(psPnFn->usFn == 0)
	{
        psDaDt->ucDT1 = 0;
        psDaDt->ucDT2 = 0;
    }
    else
    {
        ucShift = psPnFn->usFn % 8;
        ucShift = ucShift == 0 ? 7 : (ucShift -1);
        
        psDaDt->ucDT1 = (UINT8)(ucMask << ucShift);
		psDaDt->ucDT2 = (UINT8)((psPnFn->usFn -1) / 8);
		
    }
	
	return MT_OK;
}

/*****************************************************************************
 函 数 名  : emt_trans_Afn04F1_ConUpPortPara
 功能描述  : 数据结构转换函数
 输入参数  : eMtTransDir eDir                      
             sMtAfn04F1  *psUser    
             sMtAfn04F1_f  *psFrame  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月8日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emt_trans_Afn04F1_ConUpPortPara(eMtTransDir eDir, 
								       void *pUser, 
									   void *pFrame, 
									   UINT16 *pusfLen)
{

	if(!pUser || !pUser || !pusfLen)
    {
        return MT_NULL;
    }

	sMtAfn04F1 *psUser  = (sMtAfn04F1 *)pUser;
	sMtAfn04F1_f *psFrame = (sMtAfn04F1_f *)pFrame;
    
    UINT8 bs8Con = 0;
    
    if(MT_TRANS_U2F == eDir)
    {
		
        psFrame->ucRTS       = psUser->ucRTS;
        psFrame->ucRTM       = psUser->ucRTM;
        psFrame->ucHeartBeat = psUser->ucHeartBeat;
        psFrame->ucSWTS1     = (psUser->usTmWaitTimeoutS & 0xFF);
        psFrame->ucSWTS2     = ((psUser->usTmWaitTimeoutS & 0x0F00) >> 8);
        psFrame->ucSWTS2    |= ((psUser->ucReSendTimes & 0x03) << 4);
        
        if(psUser->bAutoReportAsk_1 == TRUE)
        {
            bs8Con |= 0x01;
        }
		
        if(psUser->bAutoReportAsk_2 == TRUE)
        {
            bs8Con |= 0x02;
        }
		
        if(psUser->bAutoReportAsk_3 == TRUE)
        {
            bs8Con |= 0x04;
        }
		
        psFrame->bs8Con   = bs8Con;
		
    }
    else if(MT_TRANS_F2U == eDir)
    {
        psUser->ucRTS            = psFrame->ucRTS;
        psUser->ucRTM            = psFrame->ucRTM;
        psUser->ucHeartBeat      = psFrame->ucHeartBeat;
        psUser->usTmWaitTimeoutS = (((psFrame->ucSWTS2 & 0x0F) << 8)  |  psFrame->ucSWTS1);
        psUser->ucReSendTimes    = (psFrame->ucSWTS2 >> 4) & 0x03;
        psUser->bAutoReportAsk_1 = ((psFrame->bs8Con & 0x01) ? TRUE : FALSE);
        psUser->bAutoReportAsk_2 = ((psFrame->bs8Con & 0x02) ? TRUE : FALSE);
        psUser->bAutoReportAsk_3 = ((psFrame->bs8Con & 0x04) ? TRUE : FALSE);
		
    }
    else
    {
        return MT_ERR_PARA;
    }
    
    *pusfLen = sizeof(sMtAfn04F1_f);
    return MT_OK;
}
/*****************************************************************************
 函 数 名  : emt_trans_Afn04F2_ConUpPortParaWireless
 功能描述  : 数据转换函数
 输入参数  : eMtTransDir eDir                             
             sMtAfn04F2_ConUpPortParaWireless_u  *psUser   
             sMtAfn04F2_ConUpPortParaWireless_f  *psFrame  
             UINT16 *pusfLen                              
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月13日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emt_trans_Afn04F2_ConUpPortParaWireless(eMtTransDir eDir,
                                               void  *pUser,
                                               void  *pFrame,
                                               UINT16 *pusfLen)
{
   	if(!pUser || !pUser || !pusfLen)
    {
        return MT_NULL;
    }

	sMtAfn04F2_ConUpPortParaWireless_u  *psUser  = (sMtAfn04F2_ConUpPortParaWireless_u *)pUser;
	sMtAfn04F2_ConUpPortParaWireless_f  *psFrame = (sMtAfn04F2_ConUpPortParaWireless_f *)pFrame;



    UINT16 usfLen = 0;
    int i = 0;
    int nAddrCount = 0;
    
    if(MT_TRANS_U2F == eDir)
    {
        if(psUser->bPermit == TRUE)
        {
            psFrame->ucPermit = 1;
        }
        else
        {
            psFrame->ucPermit = 0;
        }

        nAddrCount = (int)(psUser->ucAddrCount);
       
        if(nAddrCount > 16)
        {
            return MT_ERR_PARA;    // 该值不可以超过16 
        }
        else
        {
            psFrame->ucAddrCount = psUser->ucAddrCount;
        }

        for(i = 0; i < nAddrCount; i++)
        {
            psFrame->usAddress[i] = psUser->usAddress[i];
        }

        usfLen = 1 + nAddrCount*sizeof(UINT16);

        #ifdef MT_DBG_ON
        printf("emt_trans_Afn04F2_ConUpPortParaWireless() user to frame\n");
        printf("ucPermit\t= %d\n",    psFrame->ucPermit);
        printf("ucAddrCount\t= %d\n", psFrame->ucAddrCount);
        for(i = 0; i < nAddrCount; i++)
        {
            printf("usAddress[%d]\t= %d\n", i+1, psFrame->usAddress[i]);
        }     
        #endif
        
    }
    else if(MT_TRANS_F2U == eDir)
    {
        psUser->bPermit     = (psFrame->ucPermit == 1) ? TRUE:FALSE;
        psUser->ucAddrCount = psFrame->ucAddrCount;
        nAddrCount          = (int)(psFrame->ucAddrCount);
        
        for(i = 0; i < nAddrCount; i++)
        {
          psUser->usAddress[i] = psFrame->usAddress[i];
        }

        usfLen = 1 + nAddrCount*sizeof(UINT16);

#ifdef MT_DBG_ON
        printf("emt_trans_Afn04F2_ConUpPortParaWireless() frame to user\n");
        printf("ucPermit\t= %s\n", psUser->bPermit == TRUE ? "true" : "false");
        printf("ucAddrCount\t= %d\n", psUser->ucAddrCount);
        for(i = 0; i < nAddrCount; i++)
        {
            printf("usAddress[%d]\t= %d\n", i+1, psUser->usAddress[i]);
        }
#endif
    }
    else
    {
        return MT_ERR_PARA;
    }

    *pusfLen = usfLen;
    
    return MT_OK;
}





eMtErr emt_trans_Afn04F3_MasterIpPort(eMtTransDir eDir,
                                      void  *pUser,
                                      void  *pFrame,
                                      UINT16 *pusfLen)
{
	
    if(!pUser || !pFrame || !pusfLen)
    {
        return MT_NULL;
    }

	sMtAfn04F3_MasterIpPort_u  *psUser = (sMtAfn04F3_MasterIpPort_u  *)pUser;
	sMtAfn04F3_MasterIpPort_f  *psFrame = (sMtAfn04F3_MasterIpPort_f  *)pFrame;

    
    if(MT_TRANS_U2F == eDir)
    {
        psFrame->ucMainIP[0] =  psUser->ulMainIP & 0xFF;
        psFrame->ucMainIP[1] = (psUser->ulMainIP & 0xFF00)     >> 8;
        psFrame->ucMainIP[2] = (psUser->ulMainIP & 0xFF0000)   >> 16;
        psFrame->ucMainIP[3] = (psUser->ulMainIP & 0xFF000000) >> 24;
		
        psFrame->ucBackIP[0] = psUser->ulBackIP  & 0xFF;
        psFrame->ucBackIP[1] = (psUser->ulBackIP & 0xFF00)     >> 8;
        psFrame->ucBackIP[2] = (psUser->ulBackIP & 0xFF0000)   >> 16;
        psFrame->ucBackIP[3] = (psUser->ulBackIP & 0xFF000000) >> 24;
		
        psFrame->usMainPort  = psUser->usMainPort;
        psFrame->usBackPort  = psUser->usBackPort;
        memcpy(psFrame->ucascAPN, psUser->ucascAPN, 16);
		
    }
    else if(MT_TRANS_F2U == eDir)
    {
        psUser->ulMainIP =    psFrame->ucMainIP[0] 
			| psFrame->ucMainIP[1] << 8
			| psFrame->ucMainIP[2] << 16
			| psFrame->ucMainIP[3] << 24;
		
        psUser->ulBackIP =    psFrame->ucBackIP[0] 
			| psFrame->ucBackIP[1] << 8
			| psFrame->ucBackIP[2] << 16
			| psFrame->ucBackIP[3] << 24;
		
        psUser->usMainPort = psFrame->usMainPort;
        psUser->usBackPort = psFrame->usBackPort;
        memcpy(psUser->ucascAPN, psFrame->ucascAPN, 16);
    }
    else
    {
        return MT_ERR_PARA;
    }
    
    *pusfLen = sizeof(sMtAfn04F3_MasterIpPort_f);
    return MT_OK;
}




eMtErr emt_trans_Afn04F4_MstSmsPhone(eMtTransDir eDir,
                                     void  *psUser,
                                     void  *psFrame,
                                     UINT16 *pusfLen)
{

// 	sMtAfn04F4_MstSmsPhone_u  *psUser,
// 		sMtAfn04F4_MstSmsPhone_f  *psFrame,

    
    return MT_OK;
}


eMtErr emt_trans_Afn04F5_UpMsgAuth(eMtTransDir eDir,
                                   void  *psUser,
                                   void  *psFrame,
                                   UINT16 *pusfLen)
{

// 	sMtAfn04F5_UpMsgAuth_u  *psUser,
//                                    sMtAfn04F5_UpMsgAuth_f  *psFrame,
    
    return MT_OK;
}


eMtErr emt_trans_Afn04f6_ConGroupAddr(eMtTransDir eDir,
									  void  *psUser,
                                      void  *psFrame,
                                    //sMtAfn04F6_ConGroupAddr_u  *psUser,
                                    //sMtAfn04F6_ConGroupAddr_f  *psFrame,
                                    UINT16 *pusfLen)
{


     return MT_OK;

}


eMtErr emt_trans_Afn04F7_ConIpPort(eMtTransDir eDir,
								   void  *psUser,
                                   void  *psFrame,
//                                   sMtAfn04F7_ConIpPort_u  *psUser,
//                                   sMtAfn04F7_ConIpPort_f  *psFrame,
                                  UINT16 *pusfLen)                             
{


     return MT_OK;

}

eMtErr emt_trans_Afn04F8_ConUpComWay(eMtTransDir eDir,
									 void  *psUser,
                                   void  *psFrame,
//                                      sMtAfn04F8_ConUpComWay_u  *psUser,
//                                      sMtAfn04F8_ConUpComWay_f  *psFrame,
                                     UINT16 *pusfLen)
{


    return MT_OK;
}


eMtErr emt_trans_Afn04F9_Con2TmlComPara(eMtTransDir eDir,
										void  *psUser,
                                   void  *psFrame,
//                                         sMtAfn04F9_Con2TmlComPara_u  *psUser,
//                                         sMtAfn04F9_Con2TmlComPara_f  *psFrame,
                                        UINT16 *pusfLen)
{


    return MT_OK;
}

eMtErr emt_trans_Afn04F10_ConDownPara(eMtTransDir eDir,
									  void  *psUser,
                                   void  *psFrame,
//                                       sMtAfn04F10_ConDownPara_u  *psUser,
//                                       sMtAfn04F10_ConDownPara_f  *psFrame,
                                       UINT16 *pusfLen)
{return MT_OK;}

eMtErr emt_trans_Afn04F11_VpnPwd(eMtTransDir eDir,
								 void  *psUser,
                                   void  *psFrame,
//                                  sMtAfn04F11_VpnPwd_u  *psUser,
//                                  sMtAfn04F11_VpnPwd_f  *psFrame,
                                 UINT16 *pusfLen)
{return MT_OK;}        


eMtErr emt_trans_Afn04F12_ConUpLimit(eMtTransDir eDir,
									 void  *psUser,
                                   void  *psFrame,
//                                      sMtAfn04F12_ConUpLimit_u  *psUser,
//                                      sMtAfn04F12_ConUpLimit_f  *psFrame,
                                     UINT16 *pusfLen)
{return MT_OK;}   



/*****************************************************************************
 函 数 名  : emt_trans_Afn05F1_RemoteCtrlTrip
 功能描述  : 远程摇控跳闸 数据结构转换函数 最后输出该数据在帧侧的字长度
 输入参数  : eMtTransDir eDir                       
             sMtAfn05F1_RemoteCtrlTrip_u  *psUser   
             sMtAfn05F1_RemoteCtrlTrip_f  *psFrame  
             UINT16 *pusfLen                        
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emt_trans_Afn05F1_RemoteCtrlTrip(eMtTransDir eDir,
										void  *pUser,
                                        void  *pFrame,                                  
                                        UINT16 *pusfLen)
{


    if(!pUser || !pFrame || !pusfLen)
    {
        return MT_NULL;
    }

// 	sMtAfn05F1_RemoteCtrlTrip_u  *psUser  = (sMtAfn05F1_RemoteCtrlTrip_u  *)pUser,
//     sMtAfn05F1_RemoteCtrlTrip_f  *psFrame = (sMtAfn05F1_RemoteCtrlTrip_f  *)pFrame;
// 
//     if(MT_TRANS_U2F == eDir)
//     {
//         if(psUser->ucLimitPowerTime > 15 || psUser->ucHoldAlarmTime > 15)
//         {
//             return MT_ERR_PARA;
//         }
//         
//         psFrame->ucLimitPowerTime = psUser->ucLimitPowerTime;
//         psFrame->ucHoldAlarmTime  = psUser->ucHoldAlarmTime;
//     }
//     else if(MT_TRANS_F2U == eDir)
//     {
//        psUser->ucLimitPowerTime   =  psFrame->ucLimitPowerTime;
//        psUser->ucHoldAlarmTime    =  psFrame->ucHoldAlarmTime;
//     }
//     else
//     {
//         return MT_ERR_PARA;
//     }
//     
//     *pusfLen = sizeof(sMtAfn05F1_RemoteCtrlTrip_f);
    return MT_OK;
}       




/*****************************************************************************
 函 数 名  : emt_trans_Afn05F31_TimeTick
 功能描述  : 对时数据结构转换函数
 输入参数  : eMtTransDir eDir                  
             sMtAfn05F31_TimeTick_u  *psUser   
             sMtAfn05F31_TimeTick_f  *psFrame  
             UINT16 *pusfLen                   
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emt_trans_Afn05F31_TimeTick(eMtTransDir eDir,
								   void  *psUser,
                                   void  *psFrame,
//                                    sMtAfn05F31_TimeTick_u  *psUser,
//                                    sMtAfn05F31_TimeTick_f  *psFrame,
                                   UINT16 *pusfLen)
{


    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}       


eMtErr emt_trans_Afn05F49_PortSuspend(eMtTransDir eDir,
									  void  *psUser,
                                   void  *psFrame,
//                                       sMtAfn05F49_PortSuspend_u  *psUser,
//                                       sMtAfn05F49_PortSuspend_f  *psFrame,
                                      UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}


eMtErr emt_trans_Afn05F50_PortResume(eMtTransDir eDir,
									 void  *psUser,
                                   void  *psFrame,
//                                      sMtAfn05F50_PortResume_u  *psUser,
//                                      sMtAfn05F50_PortResume_f  *psFrame,
                                     UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}

eMtErr emt_trans_Afn05F51_PortAgain(eMtTransDir eDir,
									void  *psUser,
                                   void  *psFrame,
//                                     sMtAfn05F51_PortAgain_u  *psUser,
//                                     sMtAfn05F51_PortAgain_f  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}


eMtErr emt_trans_Afn06F1_IdAuthQ(eMtTransDir eDir,
								 void  *psUser,
                                   void  *psFrame,
//                                  sMtAfn06F1_IdAuthQ_u  *psUser,
//                                  sMtAfn06F1_IdAuthQ_f  *psFrame,
                                 UINT16 *pusfLen)
{

//     if(!psUser || !psFrame || !pusfLen)
//     {
//         return MT_NULL;
//     }
// 
//     if(MT_TRANS_U2F == eDir)
//     {
//         memcpy(psFrame->aCiphertext, psUser->aCiphertext, 16);
//     }
//     else if(MT_TRANS_F2U == eDir)
//     {
//         memcpy(psUser->aCiphertext, psFrame->aCiphertext, 16);
//     }
//     else
//     {
//         return MT_ERR_PARA;
//     }
//     
//     *pusfLen = sizeof(sMtAfn06F1_IdAuthQ_f);
    return MT_OK;
}


eMtErr emt_trans_Afn06F2_IdAuthA(eMtTransDir eDir,
								 void  *psUser,
                                   void  *psFrame,
//                                  sMtAfn06F2_IdAuthA_u  *psUser,
//                                  sMtAfn06F2_IdAuthA_f  *psFrame,
                                 UINT16 *pusfLen)
{

	/*
    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }


    if(MT_TRANS_U2F == eDir)
    {
        memcpy(psFrame->aCiphertext, psUser->aCiphertext, 16);
    }
    else if(MT_TRANS_F2U == eDir)
    {
        memcpy(psUser->aCiphertext, psFrame->aCiphertext, 16);
    }
    else
    {
        return MT_ERR_PARA;
    }
    
    *pusfLen = sizeof(sMtAfn06F2_IdAuthA_f);
*/
    return MT_OK;
}

eMtErr emt_trans_Afn06F3_RandQ(eMtTransDir eDir,
							   void  *psUser,
                                   void  *psFrame,
//                                sMtAfn06F3_RandQ_u  *psUser,
//                                sMtAfn06F3_RandQ_f  *psFrame,
                               UINT16 *pusfLen)
{

     if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }
/*

    if(MT_TRANS_U2F == eDir)
    {
        memcpy(psFrame->aCiphertext, psUser->aCiphertext, 16);
    }
    else if(MT_TRANS_F2U == eDir)
    {
        memcpy(psUser->aCiphertext, psFrame->aCiphertext, 16);
    }
    else
    {
        return MT_ERR_PARA;
    }
    
    *pusfLen = sizeof(sMtAfn06F3_RandQ_f);
*/
    return MT_OK;
}

eMtErr emt_trans_Afn06F4_RandA(eMtTransDir eDir,
							   void  *psUser,
                                   void  *psFrame,
//                                sMtAfn06F4_RandA_u  *psUser,
//                                sMtAfn06F4_RandA_f  *psFrame,
                               UINT16 *pusfLen)
{

     if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }
/*

    if(MT_TRANS_U2F == eDir)
    {
        memcpy(psFrame->aCiphertext, psUser->aCiphertext, 16);
    }
    else if(MT_TRANS_F2U == eDir)
    {
        memcpy(psUser->aCiphertext, psFrame->aCiphertext, 16);
    }
    else
    {
        return MT_ERR_PARA;
    }
    
    *pusfLen = sizeof(sMtAfn06F4_RandA_f);
*/


    return MT_OK;
}

/*****************************************************************************
 函 数 名  : emt_trans_Afn09F1_ConVersion
 功能描述  : 集中器版本信息数据结构转换函数
 输入参数  : eMtTransDir eDir                   
             sMtAfn09F1_ConVersion_u  *psUser   
             sMtAfn09F1_ConVersion_f  *psFrame  
             UINT16 *pusfLen                    
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emt_trans_Afn09F1_ConVersion(eMtTransDir eDir,
									void  *psUser,
                                   void  *psFrame,
//                                     sMtAfn09F1_ConVersion_u  *psUser,
//                                     sMtAfn09F1_ConVersion_f  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}

eMtErr emt_trans_Afn09F4_ConParaCfg(eMtTransDir eDir,
									void  *psUser,
                                   void  *psFrame,
//                                     sMtAfn09F4_ConParaCfg_u *psUser,
//                                     sMtAfn09F4_ConParaCfg_f  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}

eMtErr emt_trans_Afn09F5_ConCtrlCfg(eMtTransDir eDir,
									void  *psUser,
                                   void  *psFrame,
//                                     sMtAfn09F5_ConCtrlCfg_u *psUser,
//                                     sMtAfn09F5_ConCtrlCfg_f  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }



    
    return MT_OK;
}


eMtErr emt_trans_Afn09F6_ConAsk1Cfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }

// 	sMtAfn09F6_ConAsk1Cfg_u *psUser,
//                                     sMtAfn09F6_ConAsk1Cfg_f  *psFrame,

    
    return MT_OK;
}


eMtErr emt_trans_Afn09F7_ConAsk2Cfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }
// 
// 	sMtAfn09F7_ConAsk2Cfg_u *psUser,
//                                     sMtAfn09F7_ConAsk2Cfg_f  *psFrame,

    
    return MT_OK;
}       



eMtErr emt_trans_Afn09F8_ConEvntCfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen)
{

    if(!psUser || !psFrame || !pusfLen)
    {
        return MT_NULL;
    }

// 	sMtAfn09F8_ConEvntCfg_u *psUser,
//   sMtAfn09F8_ConEvntCfg_f  *psFrame,


    
    return MT_OK;
}       


/*****************************************************************************
 函 数 名  : eMtPackCommon
 功能描述  : 报文封装函数
 输入参数  : eMtAFN         eAFN      
             sMtPackCommon *psCommon  
             UINT16 *pusLen           
             UINT8  *pOutBuf          
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月22日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::eMtPackCommon(eMtAFN eAFN, sMtPackCommon *psCommon, UINT16 *pusLen, UINT8 *pOutBuf)
{
	eMtErr eErr     = MT_OK;
    UINT16 usBufLen = 0;
    UINT8  ucCtrl   = 0;
    UINT16 usUserDataLen = 0; // 用户数据区字长 用于CS 和 长度域 
    
    UINT8 *pucSeq  = NULL;
    UINT8 *pucCtrl = NULL;   // 用于计算CS
    UINT8 *pucCS   = NULL;
    sMtfComHead *psHead = NULL;
   
    if(!psCommon || !pusLen || !pOutBuf)
    {
        return MT_NULL;
    }


    if(m_bInit != TRUE)
    {
        return MT_ERR_INIT;
    }

    // 帧长是否超限
    if(psCommon->usSeq2CsLen > MT_SEQ2CS_BYTES_MAX)
    {
        return MT_OUT_RNG;
    }

    if(!(psCommon->pSeq2Cs))
    {
        return MT_ERR_SEQ2CS;
    }
       
    psHead = (sMtfComHead *)pOutBuf;

    // 0x68
    psHead->f68 = 0x68;
    psHead->s68 = 0x68;

    // AFN 
    psHead->AFN  = eAFN;
    
    // 计算应用层数据的长度
    usUserDataLen  = psCommon->usSeq2CsLen + MT_CANS_LEN;  
    psHead->L1 = (usUserDataLen & 0x003F);
    psHead->L2 = (usUserDataLen & 0x3FC0) >> 6;

    psHead->p10 = 3;
    
    // 计算控制域
    eErr = emt_trans_ctrl(MT_TRANS_U2F, &(psCommon->suCtrl), &ucCtrl);
    if(eErr != MT_OK)
    {
        #ifdef MT_DBG_ON
        printf("emt_trans_ctrl failed: %d\n", eErr);
        #endif 
        return MT_ERR_CTRL;
    }


   
    psHead->C = ucCtrl;

    // 地址域
    eErr = emt_trans_addr(MT_TRANS_U2F, &(psCommon->suAddr), &(psHead->A));
    if(eErr != MT_OK)
    {
        return MT_ERR_ADDR;
    }
        
    // 构造SEQ
    eErr = emt_trans_SEQ(MT_TRANS_U2F, &(psCommon->suSEQ), (sMtfSEQ*)&(psHead->SEQ));

    if(eErr != MT_OK)
    {
        #ifdef MT_DBG_ON
        printf("emt_trans_SEQ failed: %d\n", eErr);
        #endif 
        return MT_ERR_SEQ;
    }

    // 复制SEQ 到 CS 之间的数据
    pucSeq = (UINT8*)&(psHead->SEQ);
    pucSeq++;  // 取得应用层数据首地址
      
    memcpy((void*)pucSeq, (void*)(psCommon->pSeq2Cs), psCommon->usSeq2CsLen);

    // 计算CS
    pucCtrl = (UINT8*)&(psHead->C);   // 计算起始位置
    pucCS   = (UINT8*)(pucCtrl + usUserDataLen);
    
    *pucCS = ucmt_get_check_sum(pucCtrl, usUserDataLen);

    // 0x16H
    pucCS++;
    *pucCS = 0x16;    

    // 计算总长
    usBufLen = usUserDataLen + MT_UN_USER_LEN;

    // 将封装后的报文 传入回调
    

    // 根据返回值不同的处理
  




    // 输出长度
    *pusLen = usBufLen;

    #ifdef MT_DBG_ON
    printf("\\------eMtPackCommon()-----------------/\n");
    #endif
    // 输出报文数据
    return MT_OK;

}

/*****************************************************************************
 函 数 名  : emt_trans_ctrl
 功能描述  : 控制域用户侧和帧侧数据转换函数
 输入参数  : eMtTransDir eDir  
             sMtuCtrl *puCtrl  
             UINT8* pfCtrl     
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月17日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_trans_ctrl(eMtTransDir eDir, sMtuCtrl *puCtrl, UINT8 *pfCtrl)
{
	
   UINT8 ucfCtrl = 0;

    if(!puCtrl || !pfCtrl)
    {
        return MT_NULL;
    }
    
    if(MT_TRANS_U2F == eDir)       // 用户侧转换为帧侧
    {

        (puCtrl->eDir == MT_DIR_M2S)  ? (ucfCtrl &= 0x7F) : (ucfCtrl |= 0x80);
        (puCtrl->ePRM == MT_PRM_ACTIVE) ? (ucfCtrl |= 0x40) : (ucfCtrl &= 0xBF);

        if(puCtrl->eDir == MT_DIR_M2S)
        { 
            //下行报文 
            (puCtrl->uDir.sDown.bFcv == TRUE) ? (ucfCtrl |= 0x10) : (ucfCtrl &= 0xEF);
            (puCtrl->uDir.sDown.btFCB == 1)   ? (ucfCtrl |= 0x10) : (ucfCtrl &= 0xEF);
           
        }
        else
        {
            // 上行报文
            (puCtrl->uDir.sUp.bAcd == TRUE) ? (ucfCtrl |= 0x20) : (ucfCtrl &= 0xDF);
        }

        // 功能码
        if(puCtrl->ePRM == MT_PRM_ACTIVE)
        {
            ucfCtrl |= (puCtrl->uFCode.eFcdPrm0 & 0x0F);
        }
        else
        {
            ucfCtrl |= (puCtrl->uFCode.eFcdPrm1 & 0x0F);
        } 

        *pfCtrl = ucfCtrl;

    }
    else if (MT_TRANS_F2U == eDir)
    { 

       ucfCtrl = * pfCtrl;
       if(ucfCtrl & 0x80)
       {
            puCtrl->eDir = MT_DIR_S2M;  // 上行
            (ucfCtrl & 0x20) ?  (puCtrl->uDir.sUp.bAcd =  TRUE)  : (puCtrl->uDir.sUp.bAcd = FALSE);
       }
       else
       {
            puCtrl->eDir = MT_DIR_M2S;  // 下行
            (ucfCtrl & 0x20) ?  (puCtrl->uDir.sDown.bFcv =  TRUE)  : (puCtrl->uDir.sDown.bFcv  = FALSE);
            (ucfCtrl & 0x10) ?  (puCtrl->uDir.sDown.btFCB = 1)     :  (puCtrl->uDir.sDown.btFCB = 0);
       }

       (ucfCtrl & 0x40) ?  (puCtrl->ePRM = MT_PRM_ACTIVE)     : (puCtrl->ePRM = MT_PRM_PASIVE);
  
        puCtrl->uFCode.eFcdPrm0 = (eFcodePrm0)(ucfCtrl & 0x0F);


        
        
    }
    else
    {   
        return MT_ERR_PARA;
    }




    return MT_OK;

}

/*****************************************************************************
 函 数 名  : emt_trans_addr
 功能描述  : 地址信息 用户侧与帧侧数据结构转换函数
 输入参数  : eMtTransDir eDir     
             sMtAddress *puAddr  
             sMtfAddress *pfAddr  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_trans_addr(eMtTransDir eDir, sMtuAddress *puAddr, sMtfAddress *pfAddr)
{
#ifdef MT_DBG_ON_emt_trans_addr
	printf("------emt_trans_addr() \n");
#endif 
    
	if(!puAddr || !pfAddr)
	{
		return MT_NULL;
	}
	
	if(eDir != MT_TRANS_U2F && eDir != MT_TRANS_F2U)
	{
		
		return MT_ERR_PARA;
	}
	
	if(eDir == MT_TRANS_U2F)  // user interface to frame  
	{
        if(puAddr->usTAddress == 0)
		{
			
			return MT_ERR_ADDR;  // 0x0000为无效地址
		}
		
        if(puAddr->ucMAddress > MT_MST_ADDR_MAX)
        {
            return MT_ERR_ADDR; // 错误的主站的地址
        }
        
		
		(void)emt_str_to_bcd((char*)puAddr->acRegionCode, (char*)pfAddr->ucRegionCode , 4);
	

		(void)emt_write_uint16_small_endian(puAddr->usTAddress, (UINT8*)&(pfAddr->usTAddress));
		
#ifdef MT_DBG_ON_emt_trans_addr
        printf("emt_trans_addr() frame terminal address = %x\n", *(UINT32*)&(pfAddr->usTAddress));
        printf("emt_trans_addr() user  terminal address = %x\n", puAddr->ulTAddress);
#endif 
        
        pfAddr->ucMAddress = (puAddr->ucMAddress << 1);
		if(puAddr->bTeamAddr == TRUE)
		{
			
			pfAddr->ucMAddress |= 0x01;
		}
		else
		{
			
			pfAddr->ucMAddress &= 0xFE;
		}
		
		
	}
	else // frame to user interface
	{
		
		(void)emt_bcd_to_str((char*)(pfAddr->ucRegionCode), (char*)(puAddr->acRegionCode), 2);
		puAddr->usTAddress = usmt_read_uint16_small_endian((UINT8*)&(pfAddr->usTAddress));
		puAddr->bTeamAddr  = (pfAddr->ucMAddress & 0x01) ? TRUE : FALSE;
		puAddr->ucMAddress = (pfAddr->ucMAddress >> 1) & 0x7F;
 
	}
    
	return MT_OK;

}

/*****************************************************************************
 函 数 名  : emt_trans_SEQ
 功能描述  : 将SEQ字段从用户侧到帧侧转换函数
 输入参数  : eMtTransDir eDir  
             sMtuSEQ *puSEQ    
             sMtfSEQ *pfSEQ    
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_trans_SEQ(eMtTransDir eDir, sMtuSEQ *puSEQ, sMtfSEQ *pfSEQ)
{
	if(!puSEQ || !pfSEQ)
	{
		
		return MT_NULL;
	}
	
	if(MT_TRANS_F2U == eDir)
	{
		       
		puSEQ->bTpv  = (pfSEQ->TpV == 1) ? TRUE :FALSE;
		puSEQ->bCon  = (pfSEQ->CON == 1) ? TRUE :FALSE;
		puSEQ->ucSEQ = pfSEQ->SEQ;
		
		if(pfSEQ->FIR == 1)
		{
			
			if(pfSEQ->FIN == 1)
			{
				
				puSEQ->ePos = MT_POS_SIGLE;
			}
			else
			{
				
				puSEQ->ePos = MT_POS_MUL_S;
			}
		}
		else
		{
			
			if(pfSEQ->FIN == 1)
			{
				
				puSEQ->ePos = MT_POS_MUL_E;
			}
			else
			{
				
				puSEQ->ePos = MT_POS_MUL_M;
			}
		}
		
        
	}
	else if(MT_TRANS_U2F == eDir)
	{
		
		pfSEQ->TpV = (puSEQ->bTpv == TRUE) ? 1 : 0;
		pfSEQ->CON = (puSEQ->bCon == TRUE) ? 1 : 0;
		pfSEQ->SEQ =  puSEQ->ucSEQ & 0x0F;
		
		switch(puSEQ->ePos)
		{
			
		case MT_POS_SIGLE:
			pfSEQ->FIR = 1;
			pfSEQ->FIN = 1;
			break;
			
		case MT_POS_MUL_S:
			pfSEQ->FIR = 1;
			pfSEQ->FIN = 0;
			break;
			
		case MT_POS_MUL_M:
			pfSEQ->FIR = 0;
			pfSEQ->FIN = 0;
			break;
			
		case MT_POS_MUL_E:
			pfSEQ->FIR = 0;
			pfSEQ->FIN = 1;
			break;
			
		default:
			return MT_ERR_PARA;
			//break;
		}
		
	}
	else
	{
		
		return MT_ERR_PARA;
	}
	
	return MT_OK;

}

/*****************************************************************************
 函 数 名  : ucmt_get_check_sum
 功能描述  : 计算校验和函数
 输入参数  : UINT8 *pStartPos  
             UINT16 usLen      
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月16日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
UINT8 CNxRuler::ucmt_get_check_sum(UINT8 *pStartPos, UINT16 usLen)
{
	UINT8 ucCheckSum = 0;
    int i = 0;
	
    for(i = 0; i < usLen; i++)
    {
        ucCheckSum += pStartPos[i];
    }
	
    return ucCheckSum;
}

/*****************************************************************************
 函 数 名  : emt_str_to_bcd
 功能描述  : 将长度为len的字符串转化为BCD 长度为 len/2
 输入参数  : const char *pstr  
             UINT8 *pbcd       
             int len           
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_str_to_bcd(const char *pstr, char *pbcd, int len)
{
	if(!pstr || !pbcd)
	{
		
		return MT_NULL;
	}
	
	if(len < 0)
	{
		
		return MT_ERR_PARA;
	}
	
	UINT8 tmpValue;
	int i;
	int j;
	int m;
	int sLen;
	
	sLen = strlen(pstr);
	for(i = 0; i < sLen; i++)
	{
		if((pstr[i] < '0')
			||((pstr[i] > '9') && (pstr[i] < 'A')) 
			||((pstr[i] > 'F') && (pstr[i] < 'a')) 
			||(pstr[i] > 'f'))
		{
			sLen=i;
			break;
		}
	}
	
	sLen = (sLen <= (len * 2) ) ?  sLen : sLen * 2;
	memset((void *)pbcd, 0x00, len);
	
	for(i = sLen-1, j = 0, m = 0; (i>=0) && (m<len); i--, j++)
	{
		if((pstr[i] >= '0') && (pstr[i] <= '9'))
		{
			tmpValue=pstr[i] - '0';
		}
		else if((pstr[i] >= 'A') && (pstr[i] <= 'F'))
		{
			tmpValue=pstr[i] - 'A' + 0x0A;
		}
		else if((pstr[i] >= 'a') && (pstr[i] <= 'f'))
		{
			tmpValue=pstr[i] - 'a' + 0x0A;
		}
		else
		{
			tmpValue=0;
		}
		
		if((j%2) == 0)
		{
			pbcd[m] = tmpValue;		
		}
		else
		{
			pbcd[m++] |= (tmpValue << 4);
		}
		
		if((tmpValue==0) && (pstr[i] != '0'))
		{
			break;
		}
	}
	
	return MT_OK;

}

/*****************************************************************************
 函 数 名  : emt_write_uint32_small_endian
 功能描述  : 将一个ulong数以小字节序的方式写入指定内存
 输入参数  : UINT32 ulData  
             UINT8* pWrite  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月16日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_write_uint32_small_endian(UINT32 ulData, UINT8 *pWrite)
{
	UINT8 *pucData;
    BOOL  bBigEndian = FALSE;
    
    if(!pWrite)
	{

		return MT_NULL;
	}
    
	bBigEndian = bMtIsBigEndian();

	if(bBigEndian == TRUE)
	{

		pucData = (UINT8 *)pWrite;
        *pucData++ = (UINT8)(ulData & 0xFF);
        *pucData++ = (UINT8)((ulData & 0xFF00)     >> 8);
		*pucData++ = (UINT8)((ulData & 0xFF0000)   >> 16);
        *pucData++ = (UINT8)((ulData & 0xFF000000) >> 24);
	}
	else
	{

		//*(UINT32*)pWrite = ulData;
        memcpy((void*)pWrite, (void*)&ulData, sizeof(UINT32));

	}
		
	return MT_OK;
}

/*****************************************************************************
 函 数 名  : emt_bcd_to_str
 功能描述  : 将长度为len的BCD码转为2*len长的字符串
 输入参数  : const char* pbcd  
             char *pstr        
             int len           
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_bcd_to_str(const char *pbcd, char *pstr, int len)
{
	if(!pstr || !pbcd)
	{
		
		return MT_NULL;
	}
	
	if(len < 0)
	{
		
		return MT_ERR_PARA;
	}
	
	int i = 0,j= 0;
	char c1 = 0,c0 = 0;
	
	for(i = len - 1,j = 0; i >= 0; i--)
	{
		c0 = pbcd[i] & 0xF;
		c1 = (pbcd[i] >> 4) & 0xF;
		if(c1 >= 0 && c1 <= 9)
		{
			pstr[j++] = c1 + '0';	
		}
		else
		{
			pstr[j++] = c1 + 'A';
		}
		
		if(c0 >= 0 && c0 <= 9)
		{
			pstr[j++] = c0 + '0';			
		}
		else
		{
			pstr[j++] = c0 + 'A';
		}	
	}
	
	return MT_OK;

}

/*****************************************************************************
 函 数 名  : ulmt_read_uint32_small_endian
 功能描述  : 以小字节序的方式读入一个长整型数
 输入参数  : UINT8 *pRead  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月16日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 CNxRuler::ulmt_read_uint32_small_endian(UINT8 *pRead)
{
	UINT8 ucData[4];
	UINT32 ulRet = 0;
    BOOL bBigEndian = FALSE;
    
    if(!pRead)
	{
		
		return 0xFFFFFFFF;
	}
	
	bBigEndian = bMtIsBigEndian();
	
	if(bBigEndian == TRUE)
	{
		
		ucData[3] = *(pRead + 0);
		ucData[2] = *(pRead + 1);
        ucData[1] = *(pRead + 2);
		ucData[0] = *(pRead + 3);
		ulRet = *(UINT32*)ucData;		
	}
	else
	{
		
		//ulRet = *(UINT32*)pRead;
        memcpy((void*)&ulRet, (void*)pRead, sizeof(UINT32));
	}
	
	return ulRet;

}
/*****************************************************************************
 函 数 名  : bMtIsBigEndian
 功能描述  : 判断主机序是否为大字节序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
BOOL CNxRuler::bMtIsBigEndian()
{
	UINT16 usData = 0x1234;
	
	if(*(UINT8*)&usData == 0x12)
	{
		
		return TRUE;
	}
	else
	{
		
		return FALSE;
	}

}


/*****************************************************************************
 函 数 名  : emt_find_frist_valid_pack
 功能描述  : 找到第一个有效帧的位置及长度
 输入参数  : UINT8  *pinBuf     
             UINT16 usLen       
             UINT16 *pusFirstOff 第一个有效帧的偏移  
             UINT16 *pusFirstLen   第一个有效帧的长度
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月26日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_find_frist_valid_pack(UINT8 *pinBuf, UINT16 usLen, UINT16 *pusFirstOff, UINT16 *pusFirstLen)
{
	if(!pinBuf || !pusFirstOff || !pusFirstLen)
    {
        return MT_NULL;
    }
    
    eMtErr eRet = MT_OK;
    int i = 0, j = 0, k = 0;
    UINT16 usValidLen = 0;
    
	
    for(i = 0; i < usLen; i++)
    {
        if(pinBuf[i] == 0x68)
        {
#ifdef MT_DBG_ON
            //printf("eMtIsValidPack() first 0x68 i = %d\n", i);
#endif
            // 判断下两个字节位置是不是0x68
            if(pinBuf[i+3] == 0x68)
            {
#ifdef MT_DBG_ON
                //printf("eMtIsValidPack() second 0x68 i = %d\n", i+2);
#endif
				
                for(j = i+4; j < usLen; j++)
                {
                    if(pinBuf[j] == 0x16)
                    {                        
                        usValidLen = j + 1;
                        eRet = eMtIsValidPack((UINT8*)(pinBuf + i), usValidLen);
                        if(eRet == MT_OK)
                        {
                            *pusFirstOff = i;
                            *pusFirstLen = usValidLen;
#ifdef MT_DBG_ON
                            //printf("emt_find_frist_valid_pack() pusFirstOff = %d pusFirstLen = %d\n", *pusFirstOff, usValidLen);
#endif
                            return MT_OK;
                        }
                        
                    }
                }
				
                continue;
            }
        }
    }
    
    return MT_NONE;

}

/*****************************************************************************
 函 数 名  : eMtIsValidPack
 功能描述  : 判断一个以0x68开头以0x16结尾的buffer是否为一个有效的367.1报文
 输入参数  : UINT8  *pOutBuf  
             UINT16 usLen     
 输出参数  : 无
 返 回 值  : 如果是一个有效的正常的报文，返回MT_OK， 否则返回错误类型
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月26日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::eMtIsValidPack(UINT8 *pOutBuf, UINT16 usLen)
{
	if(!pOutBuf)
    {
        return MT_NULL;
    }
	
    UINT16 usUserLen   = 0;     
    UINT8  ucCheckSumP = 0;    
    UINT8  ucCheckSumC = 0;   
    UINT8  uc0x16      = 0;
    UINT16 usProtoLen  = 0; //实际应该的协议数据长度
    
    sMtfComHead *pfComHead = NULL;
    pfComHead = (sMtfComHead *)pOutBuf;
	
    if(pfComHead->f68 != 0x68 || pfComHead->s68 != 0x68)
    {
        return MT_ERR_0x68;
    }
	
    if(pfComHead->p10 != 3)
    {
        return MT_ERR_PROTO;
    }
	
    usUserLen =  ((pfComHead->L2 << 6) & 0x3FC0 )| (pfComHead->L1 & 0x003F) ; 
	
	
    ucCheckSumP =  *(UINT8*)((UINT8*)&(pfComHead->C) + usUserLen);
#ifdef MT_DBG_ON
    printf("ucCheckSumP = %d\n", ucCheckSumP);

#endif 
	
    ucCheckSumC = ucmt_get_check_sum((UINT8*)&(pfComHead->C), usUserLen);
    
#ifdef MT_DBG_ON
	printf("ucCheckSumC = %d\n", ucCheckSumC);
#endif 
	
    if(ucCheckSumC != ucCheckSumP)
    {
        return MT_ERR_CS;
    }
	
    // 协议应该的数据长度
    usProtoLen = usUserLen + MT_UN_USER_LEN;
    if(usLen < usProtoLen)
    {   
        return MT_ERR_UNCOMP;
    }
	
    uc0x16 = *(UINT8*)((UINT8*)&(pfComHead->C) + usUserLen + 1);
#ifdef MT_DBG_ON
    //printf("uc0x16 = %d\n", uc0x16);
#endif 
	
    if(uc0x16 != 0x16)
    {
        return MT_ERR_0x16;
    }
	
    
	
    return MT_OK;

}

/*****************************************************************************
 函 数 名  : emt_write_uint16_small_endian
 功能描述  : 将一个UINT16以小字节序的方式写到指定地址
 输入参数  : UINT16 usData  
             UINT8* pWrite  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_write_uint16_small_endian(UINT16 usData, UINT8 *pWrite)
{
	if(!pWrite)
	{
		
		return MT_NULL;
	}
	
	UINT8 ucByteHi = 0, ucByteLo = 0;
	BOOL bBigEndian = bMtIsBigEndian();
	
	if(bBigEndian == TRUE)
	{
		
		ucByteHi    = *(UINT8*)&usData;
		ucByteLo    = *((UINT8*)&usData + 1);
		*pWrite     = ucByteLo;
		*(pWrite+1) = ucByteHi;
		
	}
	else
	{
		
		*(UINT16*)pWrite = usData;
	}
	
	return MT_OK;	

}

/*****************************************************************************
 函 数 名  : usmt_read_uint16_small_endian
 功能描述  : 以小字节方式读取一个short
 输入参数  : UINT8 *pRead  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月16日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
UINT16 CNxRuler::usmt_read_uint16_small_endian(UINT8 *pRead)
{
	if(!pRead)
	{
		
		return 0xFFFF;
	}
	
	BOOL bBigEndian = bMtIsBigEndian();
	UINT8 ucData[2];
	UINT16 usRet = 0;
	
	if(bBigEndian == TRUE)
	{
		
		ucData[1] = *pRead;
		ucData[0] = *(pRead+1);
		usRet = *(UINT16*)ucData;		
	}
	else
	{
		
		usRet = *(UINT16*)pRead;
	}
	
	return usRet;

}

/*****************************************************************************
 函 数 名  : emtPack
 功能描述  : 封装命令帧函数
 输入参数  : smtPack *sPack   
             UINT16 *pusLen   
             UINT8  *pOutBuf  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 函数说明  : 可以封装多子命令数据帧, 
 
 修改历史      :
  1.日    期   : 2013年4月17日 星期三
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emtPack(smtPack *psPack, UINT16 *pusLen, UINT8 *pOutBuf)
{
    // 进入函数
   
    if(!psPack || !pusLen || !pOutBuf)
    {
        return MT_NULL;
    }

    if(m_bInit != TRUE)
    {
        return MT_ERR_INIT; 
    }

    eMtErr         eRet        = MT_OK;
    eMtCmd         eCmd        = CMD_AFN_0_FN_0_UNKOWN;
    eMtDir         eDir        = MT_DIR_UNKOWN;
    eMtAFN         eAFN        = AFN_NULL;
    INT32          i           = 0;
    UINT16         usPn        = 0;
    UINT16         usSeq2CsLen = 0;
    UINT16         usSeq2CsPos = 0; 
    UINT16         usfDataLen  = 0;      // 帧侧数据单元字长
    UINT8          *pSeq2Cs    = NULL;
    UINT8          *puData     = NULL;   // 数据单元用户侧数据
    sMtDaDt        *pDaDt      = NULL;   // 数据单元标识
    UINT8          *pData      = NULL;   // 数据单元
    sMtEC          *psEC       = NULL;
    sMtfTp         *psfTp      = NULL;   // 帧侧Tp字段
    
    pMtTransFunc   pFunc       = NULL;
    sMtuCtrl       suCtrl;
    sMtCmdInfors   sCmdInfor;
    sMtPackCommon  sPackCommon;
    sMtPnFn        sPnFn;
    //sMtuTp         suTp;    // 用户侧Tp字段信息

    if(m_role == MT_ROLE_MASTER)
    {
        eDir = MT_DIR_M2S;
    }
    else
    {
        eDir = MT_DIR_S2M;
    }


    /* 封装packCommon 入参 */

    // 构建通用封包参数
    pSeq2Cs = (UINT8*)malloc(MT_SEQ2CS_BYTES_MAX);

    if(pSeq2Cs == NULL)
    {
        return MT_ERR_IO;
    }

    // 封装变长的数据单元标识与数据单元组
    if(psPack->ucSubNum == 0)
    {
        return MT_ERR_PROTO;
    }
	
	
    // 封装至少一个数据标识与数据单元组合
    for(i = 0; i < (INT32)psPack->ucSubNum; i++)
    {    
        eCmd  = (eMtCmd)((psPack->sSub[i].eSubCmd) & 0xFFFF); //去掉主动上报命令标识
        usPn  = psPack->sSub[i].usPN;
        pDaDt = (sMtDaDt*)(pSeq2Cs + usSeq2CsPos);
        
        // 获取该命令字对应的信息
        eRet = eMtGetCmdInfor(eCmd, eDir, &sCmdInfor);
        if(eRet != MT_OK)
        {          
            vMtfree(pSeq2Cs);
            return eRet;
        }
		
        /* 数据单元标识 */
        // 如果该命令对应的pn类型为 P0 忽略用户传入的Pn值
        if(sCmdInfor.ePn == MT_PN_0) 
        {
            usPn = 0;
        }

        usSeq2CsPos += sizeof(sMtDaDt);
        sPnFn.usFn  = eCmd & 0xFF;
        sPnFn.usPn  = usPn;
        eRet = eMtTransPnFn_to_DaDt(&sPnFn, pDaDt);
        if(eRet != MT_OK)
        {
            vMtfree(pSeq2Cs);
            return eRet;
        }

        // 数据单元
        pData = (UINT8*)(pSeq2Cs + usSeq2CsPos);
        pFunc = sCmdInfor.pFunc;

        if(pFunc != NULL)
        {
            puData = (UINT8*)&(psPack->sSub[i].uAppData);
            eRet = pFunc(MT_TRANS_U2F, puData, pData, &usfDataLen);
            if(eRet != MT_OK)
            {
                vMtfree(pSeq2Cs);
                return eRet;
            }

            usSeq2CsPos += usfDataLen;
			CString str;
			str.Format("data %d",usSeq2CsPos);
	     	//AfxMessageBox(str);
        }
		
    }
    
	
	/* 附加信息域AUX */
    eAFN = psPack->eMainCmd;
	
    // 计算控制域
    eRet = eMtGetCtrl(eAFN, eDir, psPack->sCtrl.ePRM, &suCtrl);
    if(eRet != MT_OK)
    {
        vMtfree(pSeq2Cs);
        return eRet;
    }

    // 如果有 EC
    if(bmt_have_ec(eAFN, eDir) == TRUE)
     {       
        pData = (UINT8*)(pSeq2Cs + usSeq2CsPos);
        psEC  = (sMtEC*)pData;
        psEC->ucEC1 = m_EC.ucEC1;
        psEC->ucEC2 = m_EC.ucEC2;
        usSeq2CsPos += sizeof(sMtEC);
     }
    
    // 如果有 pw  pw用于重要的下行报文中,由主站产生,收端验证，通过后执行(16字节)
    if(bmt_have_pw(eAFN, eDir) == TRUE)    
    {
        pData = (UINT8*)(pSeq2Cs + usSeq2CsPos);
        // 消息认证算法, 格式化为这16个字节, 默认为0
        memcpy((void*)pData, (void*)m_aucPw, MT_PW_LEN); 
        usSeq2CsPos += MT_PW_LEN;

		CString str;
		str.Format("pw %d",usSeq2CsPos);
		//AfxMessageBox(str);
        
    }

    // 如果有 TP
    if(bmt_have_tp(eAFN, eDir) == TRUE)  // 除了这种情况的所有报文中
    {
		CString str;
		str.Format("tp %d",usSeq2CsPos);
	     //	AfxMessageBox(str);

        //pData = (UINT8*)(pSeq2Cs + usSeq2CsPos);
        psfTp = (sMtfTp *)(pSeq2Cs + usSeq2CsPos);;
        //(void)emt_get_mtutp(m_ucPFC, &suTp);
        (void)emt_trans_tp(MT_TRANS_U2F, &psPack->sTP, psfTp);
        usSeq2CsPos += sizeof(sMtfTp);
        sPackCommon.suSEQ.bTpv = TRUE;
    }
	else
	{
		sPackCommon.suSEQ.bTpv = FALSE;
	}

    // 该报文是否需要从动站确认
	sPackCommon.suSEQ.bCon = bmt_need_con(eAFN, eDir);
  

    // 总结数据
    usSeq2CsLen             = usSeq2CsPos;
    sPackCommon.suSEQ.ePos  = MT_POS_SIGLE;    // 目前都是单帧的
    sPackCommon.suSEQ.ucSEQ = psPack->sTP.ucPFC & 0x0F;
    sPackCommon.suAddr      = psPack->sAddress;
    sPackCommon.pSeq2Cs     = pSeq2Cs;
    sPackCommon.usSeq2CsLen = usSeq2CsLen;
    sPackCommon.suCtrl      = suCtrl;
    
    // 通过通用封包函数pack
    eRet = eMtPackCommon(eAFN,  &sPackCommon, pusLen, pOutBuf);   
    if(eRet != MT_OK)
    {
        #ifdef MT_DBG_ON
		CString strdbg;
		strdbg.Format("eMtPackCommon failed: %d\n", eRet);
		OutputDebugString(strdbg);
        #endif 

        vMtfree(pSeq2Cs);
        return eRet;
    }
	else
	{
		OutputDebugString("eMtPackCommon()成功");
	}

  
    #ifdef MT_DBG_ON
    printf("\\----------------------------eMtPack()----------------------------/\n");
    #endif 
    vMtfree(pSeq2Cs);
    return MT_OK;
}

/*****************************************************************************
 函 数 名  : vMtfree
 功能描述  : 解放malloc 申请的内存内间
 输入参数  : UINT8 *pBuf  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月22日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
void CNxRuler::vMtfree(UINT8 *pBuf)
{
	if(pBuf != NULL)
    {
        free(pBuf);
        pBuf = NULL;
    }

}

/*****************************************************************************
 函 数 名  : eMtTransPnFn_to_DaDt
 功能描述  : 将数据信息标识从PnFn结构转换为Data结构
 输入参数  : sMtPnFn *psPnFn  
             sMtDaDt *psDaDt  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::eMtTransPnFn_to_DaDt(sMtPnFn *psPnFn, sMtDaDt *psDaDt)
{
	if(!psPnFn || !psDaDt)
	{
		return MT_NULL;
	}
	
	if(psPnFn->usPn > MT_DA_PN_MAX || psPnFn->usFn > MT_DT_FN_MAX)
	{
		return MT_OUT_RNG;
	}
	
    UINT8 ucShift = 0; 
    UINT8 ucMask  = 0x01;
    
    if(psPnFn->usPn == 0)
    {
        psDaDt->ucDA1 = 0;
        psDaDt->ucDA2 = 0;
    }
    else
    {
        ucShift = psPnFn->usPn % 8;
        ucShift = ucShift == 0 ? 7 : (ucShift -1);
        psDaDt->ucDA1 = (UINT8)(ucMask << ucShift);
		psDaDt->ucDA2 = (UINT8)((psPnFn->usPn - 1) / 8 + 1);
    }
	
	if(psPnFn->usFn == 0)
	{
        psDaDt->ucDT1 = 0;
        psDaDt->ucDT2 = 0;
    }
    else
    {
        ucShift = psPnFn->usFn % 8;
        ucShift = ucShift == 0 ? 7 : (ucShift -1);
        
        psDaDt->ucDT1 = (UINT8)(ucMask << ucShift);
		psDaDt->ucDT2 = (UINT8)((psPnFn->usFn -1) / 8);
		
    }
	
#ifdef MT_DBG_ON
    printf("eMtTransPnFn_to_DaDt() in sPnFn.usfn = %d sPnFn.usPn = %d\n", psPnFn->usFn, psPnFn->usPn);
    printf("eMtTransPnFn_to_DaDt() out Da1 = %d Da2 = %d Dt1 = %d Dt2 = %d\n", 
		psDaDt->ucDA1,
		psDaDt->ucDA2,
		psDaDt->ucDT1,
		psDaDt->ucDT2);
	
#endif 
	return MT_OK;
}

eMtErr CNxRuler::eMtGetCtrl(eMtAFN eAFN, eMtDir eDir, eMtPRM ePRM, sMtuCtrl *psuCtrl)
{
	
    if(!psuCtrl)
    {
        return MT_NULL;
    }
    
    // 方向错误
    if(eDir != MT_DIR_M2S && eDir != MT_DIR_S2M)
    {
       return  MT_ERR_PARA;
    }

    // 启动站从动站参数错误
    if(ePRM != MT_PRM_ACTIVE && ePRM != MT_PRM_PASIVE)
    {
        return MT_ERR_PARA;
    }


    psuCtrl->eDir = eDir;
    psuCtrl->ePRM = ePRM;


    switch(eAFN)
    {
        
        case AFN_00_CONF:

             if(ePRM == MT_PRM_PASIVE) //  确认否认报文只能从动站发出
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_OK; 
             }
             else
             {
                return MT_ERR_LOGIC;
             }
            
             if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
                
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = TRUE;
             }

            break; 
            
        case AFN_01_RSET:
            
             if(eDir == MT_DIR_M2S && ePRM == MT_PRM_ACTIVE)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
                
                psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_RESET; 
             }
             else                    // 上行
             {
                return MT_ERR_LOGIC;
             }


            break;
            
        case AFN_02_LINK:
            
             if(eDir == MT_DIR_S2M && ePRM == MT_PRM_ACTIVE)    // 该命令只有上行的主动
             {
                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_LINK; 
             }
             else                   
             {
                  return MT_ERR_LOGIC;
             }

            
        case AFN_03_RELY:

#if 0
            if(eDir == MT_DIR_M2S && ePRM == MT_PRM_ACTIVE)   // 只有下行主动  
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
                
                psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_USER; 
             }
             else                     // 上行
             {
                 return MT_ERR_LOGIC;
             }
#endif
            break;

            
        case AFN_04_SETP:
             if(eDir == MT_DIR_M2S && ePRM == MT_PRM_ACTIVE)   // 只有下行主动  
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
                
                psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_USER; 
             }
             else                     // 上行
             {
                 return MT_ERR_LOGIC;
             }

            break;

        case AFN_05_CTRL:
            if(eDir == MT_DIR_M2S && ePRM == MT_PRM_ACTIVE)   // 只有下行主动  
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
                
                psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_RESET; 
             }
             else                     // 上行
             {
                 return MT_ERR_LOGIC;
             }

            break;
            
        case AFN_06_AUTH:
             if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = FALSE;  //EC
             }


             if(ePRM == MT_PRM_ACTIVE) //主动站
             {

                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_RESET;    
             }
             else                                         //从动站
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_USER;   
             }
            break;
            
        case AFN_08_CASC:
             if(eDir == MT_DIR_M2S)   // 下行
             {
                
             }
             else                     // 上行
             {

             }

             if(ePRM == MT_PRM_ACTIVE) //主动站
             {


             }
             else                                         //从动站
             {

             }
            break;
            
        case AFN_09_CFIG:
             if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = TRUE;  //EC
             }

              if(ePRM == MT_PRM_ACTIVE) //主动站
             {

                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_RESET;    
             }
             else                                         //从动站
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_USER;   
             }
            break;
            
        case AFN_0A_GETP:
              if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = TRUE;  //EC
             }

              if(ePRM == MT_PRM_ACTIVE) //主动站
             {

                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_USER;    
             }
             else                                         //从动站
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_USER;   
             }
            break;
            

        case AFN_0B_ASKT:
           if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = TRUE;  //EC
             }

              if(ePRM == MT_PRM_ACTIVE) //主动站
             {

                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_USER;    
             }
             else                                         //从动站
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_USER;   
             }
            break;
        case AFN_0C_ASK1:
           if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = TRUE;  //EC
             }

             if(ePRM == MT_PRM_ACTIVE) //主动站
             {

                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_ASK_1;    
             }
             else                                         //从动站
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_USER;   
             }
            break;

            
        case AFN_0D_ASK2:
          if(eDir == MT_DIR_M2S)   // 下行
             {
                psuCtrl->uDir.sDown.bFcv = FALSE; 
                psuCtrl->uDir.sDown.btFCB = 1; 
                psuCtrl->uDir.sDown.btRcv = 0; 
             }
             else                     // 上行
             {
                psuCtrl->uDir.sUp.bAcd = TRUE;  //EC
             }

             if(ePRM == MT_PRM_ACTIVE) //主动站
             {

                 psuCtrl->uFCode.eFcdPrm1 = FCD_PRM_1_ASK_2;    
             }
             else                                         //从动站
             {
                  psuCtrl->uFCode.eFcdPrm0 = FCD_PRM_0_USER;   
             }
            break;

            
        case AFN_0E_ASK3:
           if(eDir == MT_DIR_M2S)   // 下行
             {
                
             }
             else                     // 上行
             {

             }

             if(ePRM == MT_PRM_ACTIVE) //主动站
             {


             }
             else                                         //从动站
             {

             }
            break;
        case AFN_0F_FILE:
           if(eDir == MT_DIR_M2S)   // 下行
             {
                
             }
             else                     // 上行
             {

             }

             if(ePRM == MT_PRM_ACTIVE) //主动站
             {


             }
             else                                         //从动站
             {

             }
            break;
        case AFN_10_DATA:
             if(eDir == MT_DIR_M2S)   // 下行
             {
                
             }
             else                     // 上行
             {

             }

             if(ePRM == MT_PRM_ACTIVE) //主动站
             {


             }
             else                                         //从动站
             {

             }
            break;

        default:
            return MT_ERR_PARA;
            //break;

    }

 
    return MT_OK;

}

/*****************************************************************************
 函 数 名  : bmt_have_ec
 功能描述  : 此类报文中是否应该含有ec字段
 输入参数  : eMtAFN eAFN 
             eMtDir eDir  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
BOOL CNxRuler::bmt_have_ec(eMtAFN eAFN, eMtDir eDir)
{
	if((eAFN == AFN_00_CONF) ||                              // 确认否认报文 上下行都有EC
		(eAFN != AFN_02_LINK && eAFN != AFN_06_AUTH && MT_DIR_S2M == eDir))     // 除了链路检测外的所有上行报文都有EC
    {
        return TRUE;
    }
	
	
    return FALSE;

}

/*****************************************************************************
 函 数 名  : bmt_have_pw
 功能描述  : 此报文中是否应该还有pw字段
 输入参数  : eMtAFN eAFN    
             eMtDir eDir 
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
BOOL CNxRuler::bmt_have_pw(eMtAFN eAFN, eMtDir eDir)
{
    if(((MT_DIR_M2S == eDir) &&
        (AFN_01_RSET == eAFN  ||
		AFN_04_SETP == eAFN  || 
		AFN_05_CTRL == eAFN  ||
		AFN_10_DATA == eAFN  ||
		AFN_0F_FILE == eAFN))        // PW字段只出现在下行报文中
		|| (AFN_06_AUTH == eAFN))    // 双向身份认证报文中都有PW
    {
        return TRUE;
    }
	
    return FALSE;
}




/*****************************************************************************
 函 数 名  : bmt_have_tp
 功能描述  : 此报文(从 eRole 发送的报文)中是否应该还有tp字段
 输入参数  : eMtAFN eAFN    
             eMtDir eDir 
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月27日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
BOOL CNxRuler::bmt_have_tp(eMtAFN eAFN, eMtDir eDir)
{
    if(eAFN == AFN_02_LINK &&  MT_DIR_S2M == eDir)  // 除了这种情况的所有报文中
    {
         return FALSE;
    }

   return TRUE;
}



/*****************************************************************************
 函 数 名  : bmt_need_con
 功能描述  : 此报文是否需要确认
 输入参数  : eMtAFN eAFN  
             eMtDir eDir  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月23日 星期二
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
BOOL CNxRuler::bmt_need_con(eMtAFN eAFN, eMtDir eDir)
{
  // 该报文是否需要从动站确认
    if((MT_DIR_M2S == eDir) &&
       (AFN_01_RSET == eAFN || 
        AFN_02_LINK == eAFN || 
        AFN_04_SETP == eAFN ||
        AFN_05_CTRL == eAFN))
    {
       return TRUE;
    }
    else
    {
        return FALSE;
    }

    
}
/*****************************************************************************
 函 数 名  : emt_trans_tp
 功能描述  : 时间标签TP转换函数
 输入参数  : eMtTransDir eDir  
             sMtuTp* puTp      
             sMtfTp* pfTp      
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月22日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_trans_tp(eMtTransDir eDir, sMtuTp *puTp, sMtfTp *pfTp)
{

    if(!puTp || !pfTp)
    {
        return MT_OK;
    }

    if(MT_TRANS_U2F == eDir)
    {
        pfTp->ucPFC = puTp->ucPFC;
        pfTp->ucPermitDelayMinutes = puTp->ucPermitDelayMinutes;

        // 日时分秒
        pfTp->sTime.ddBCD_0 = ucmt_get_bcd(puTp->ucDD, 0);
        pfTp->sTime.ddBCD_1 = ucmt_get_bcd(puTp->ucDD, 1);
        pfTp->sTime.hhBCD_0 = ucmt_get_bcd(puTp->ucHH, 0);
        pfTp->sTime.hhBCD_1 = ucmt_get_bcd(puTp->ucHH, 1);
        pfTp->sTime.mmBCD_0 = ucmt_get_bcd(puTp->ucmm, 0);
        pfTp->sTime.mmBCD_1 = ucmt_get_bcd(puTp->ucmm, 1);
        pfTp->sTime.ssBCD_0 = ucmt_get_bcd(puTp->ucss, 0);
        pfTp->sTime.ssBCD_1 = ucmt_get_bcd(puTp->ucss, 1);
    }
    else if(MT_TRANS_F2U == eDir)
    {
        puTp->ucPFC = pfTp->ucPFC;
        puTp->ucPermitDelayMinutes = pfTp->ucPermitDelayMinutes;

        // 日时分秒
        puTp->ucDD =   (pfTp->sTime.ddBCD_1 * 10) + pfTp->sTime.ddBCD_0;
        puTp->ucHH =   (pfTp->sTime.hhBCD_1 * 10) + pfTp->sTime.hhBCD_0;
        puTp->ucmm =   (pfTp->sTime.mmBCD_1 * 10) + pfTp->sTime.mmBCD_0; 
        puTp->ucss =   (pfTp->sTime.ssBCD_1 * 10) + pfTp->sTime.ssBCD_0;
    }
    else
    {
        return MT_ERR_PARA;
    }
    

   return MT_OK;

}



/*****************************************************************************
 函 数 名  : emt_get_mtutp
 功能描述  : 获得当前用户侧Tp原始数据
 输入参数  : UINT8 ucPFC 启动帧计数器
 输出参数  : sMtuTp *psuTp 
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月22日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emt_get_mtutp(UINT8 ucPFC, sMtuTp *psuTp)
{
    time_t now;
    struct tm* timenow;
    
    if(!psuTp)
    {
        return MT_NULL;
    }

    // 获取系统当前时间
    time(&now);
    timenow = localtime(&now);
    
    psuTp->ucDD = timenow->tm_mday;
    psuTp->ucHH = timenow->tm_hour;
    psuTp->ucmm = timenow->tm_min;
    psuTp->ucss = timenow->tm_sec;

    psuTp->ucPermitDelayMinutes = m_ucPermitDelayMinutes;
    psuTp->ucPFC = ucPFC;

    #ifdef MT_DBG_ON
    printf("emt_get_mtutp() \n");
    printf("DD = %d HH = %d mm = %d ss =%d\n", psuTp->ucDD, psuTp->ucHH, psuTp->ucmm, psuTp->ucss);
    printf("PermitDelayMinutes = %d\n", psuTp->ucPermitDelayMinutes);
    printf("PFC = %d\n", psuTp->ucPFC);
    #endif
    
    return MT_OK;
}


/*****************************************************************************
 函 数 名  : ucmt_get_bcd
 功能描述  : 获得一个整数的某一位对应的BCD码
             ucPos = 
             0 个数
             1 十位
             2 百位
             3 千位
             4 万位
             5 
 输入参数  : UINT32 ulData  
             UINT8 ucPos    
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年1月22日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
UINT8 CNxRuler::ucmt_get_bcd(UINT32 ulData, UINT8 ucPos)
{
    //UINT8 ucBCD;
    UINT8 aucBCD[10];
    int i = 0;
    UINT32 ulTmp = 0;

    if(ucPos > 9)
    {
        return 0;
    }

    ulTmp = ulData;
    
    for(i = 0; i < 10; i++)
    {
        aucBCD[i] = ulTmp % 10;
        ulTmp = ulTmp / 10;
    }

    return aucBCD[ucPos];    

}


eMtErr CNxRuler::emtUnPack(smtPack *psUnpack, UINT8* pInBuf, UINT16 usLen)
{

#ifdef MT_DBG_ON
    printf("-----------------eMtUnpack()------------------\n");
#endif 

    if(!psUnpack || !pInBuf)
    {
        return MT_NULL;
    }

    eMtErr      eRet       = MT_OK;
    eMtDir      eDir       = MT_DIR_UNKOWN;
    eMtAFN      eAFN       = AFN_MAX;
    eMtCmd      eCmd       = CMD_AFN_0_FN_0_UNKOWN;
    sMtPnFn     sPnFn;
    sMtuSEQ     suSEQ;
    sMtCmdInfors sCmdInfor;
    sMtfComHead *psHead    = NULL;
    sMtDaDt     *pDaDt     = NULL;
    UINT8       *pucTemp   = NULL;
    sMtEC       *psEC      = NULL;
    sMtfTp      *psfTp     = NULL;     // 帧侧Tp字段
    pMtTransFunc pFunc     = NULL;
    UINT16      usUsrdLen  = 0;        //用户应用数据在帧侧的字长
    UINT16      usLenPack  = 0;
    UINT16      usLenEcPwTp    = 0;    // 该类型帧的EcPwTp帧侧的几个域的部字长
    UINT16      usLenUserField = 0;    // 用户数据区长度   
    
    INT32       nLenUserField  = 0;    // 每次解析一个子命令数据单元后的用户数据域字长 
    INT32       i          = 0;
    
    if(usLen < MT_PACK_LEN_MIN)
    {
        #ifdef MT_DBG_ON
        printf("eMtUnpack usLen = %d\n", usLen);
        #endif 
        return MT_ERR_UNCOMP;
    }

    // 检查报文的有效性
    eRet = eMtIsValidPack(pInBuf, usLen);
    if(eRet != MT_OK)
    {
        #ifdef MT_DBG_ON
        printf("eMtUnpack eMtIsValidPack() error = %d\n", eRet);
        #endif 
        return eRet;
    }

    // user date field
    psHead = (sMtfComHead *)pInBuf;
    //usLenUserField = (psHead->L2 & 0x3F) | ((psHead->L1 << 6) & 0x3FC0); 
    
    usLenUserField =  ((psHead->L2 << 6) & 0x3FC0 )| (psHead->L1 & 0x003F) ; 
    
    #ifdef MT_DBG_ON
    printf("eMtUnpack() usLenUserField = %d\n", usLenUserField);
    #endif

    // address
    eRet = emt_trans_addr(MT_TRANS_F2U, &(psUnpack->sAddress), &(psHead->A));
    if(eRet != MT_OK)
    {
        #ifdef MT_DBG_ON
        printf("eMtUnpack() emt_trans_addr() error = %d\n", eRet);
        #endif
        return eRet;
    }

    // ctrl field
    eRet = emt_trans_ctrl(MT_TRANS_F2U, &(psUnpack->sCtrl), &(psHead->C));
    if(eRet != MT_OK)
    {
        #ifdef MT_DBG_ON
        printf("eMtUnpack() emt_trans_ctrl() error = %d\n", eRet);
        #endif
        return eRet;
    }
    
    if(psUnpack->sCtrl.eDir == MT_DIR_S2M && psUnpack->sCtrl.uDir.sUp.bAcd == TRUE)
    {
        psUnpack->bEC = TRUE;
    }
    else
    {
        psUnpack->bEC = FALSE;
    }
    

    // SEQ
    eRet = emt_trans_SEQ(MT_TRANS_F2U, &suSEQ, (sMtfSEQ*)&(psHead->SEQ));
    if(eRet != MT_OK)
    {
        #ifdef MT_DBG_ON
        printf("eMtUnpack() emt_trans_SEQ() error = %d\n", eRet);
        #endif
        return eRet;
    }
    
    psUnpack->ucSEQ = suSEQ.ucSEQ;
    psUnpack->bTP   = suSEQ.bTpv;
    psUnpack->bCon  = suSEQ.bCon;



    // AFN
    psUnpack->eMainCmd = (eMtAFN)psHead->AFN;
    eAFN               = (eMtAFN)psHead->AFN;
    #ifdef MT_DBG_ON
    printf("eMtUnpack() afn = 0x%02X\n", psHead->AFN);
    #endif

    // 计算除了附加域的应用层数据字长
    eDir = psUnpack->sCtrl.eDir;
    usLenEcPwTp = usmt_get_ec_pw_tp_len(eAFN, eDir);
    nLenUserField = (INT32)(usLenUserField - usLenEcPwTp - MT_CANS_LEN);

	pucTemp = (UINT8*)((UINT8*)&(psHead->SEQ) + 1) ;

    while(nLenUserField > 0)
    {
        // 初始化
        usUsrdLen = 0;
        
        // cmd
        
        pDaDt = (sMtDaDt*)pucTemp;
        eMtTransDaDt_to_PnFn(pDaDt, &sPnFn);
        #ifdef MT_DBG_ON
        printf("eMtUnpack() fn = %d pn = %d\n", sPnFn.usFn, sPnFn.usPn);
        #endif
        
        eCmd =(eMtCmd)( (psHead->AFN << 8) | ( sPnFn.usFn & 0xFF));
        #ifdef MT_DBG_ON
        printf("eMtUnpack() eCmd = 0x%04X\n", eCmd);
        #endif   

       
        pucTemp += sizeof(sMtDaDt);
       
        // user data field
       
        eRet = eMtGetCmdInfor(eCmd, eDir, &sCmdInfor);
        if(eRet != MT_OK)
        {
            #ifdef MT_DBG_ON
            printf("eMtUnpack() eMtGetCmdInfor() error = %d\n", eRet);
            #endif
            return eRet;
        }
        
        pFunc = sCmdInfor.pFunc;
        if(pFunc != NULL)
        {
		    if(CMD_AFN_0_FN_3_ONE_BY_ONE == eCmd)
			{
                 usUsrdLen = nLenUserField - sizeof(sMtDaDt);;

			}
            eRet = pFunc(MT_TRANS_F2U, (void*)&(psUnpack->sSub[i].uAppData), (void*)pucTemp, &usUsrdLen);
            if(eRet != MT_OK)
            {
                #ifdef MT_DBG_ON
                printf("eMtUnpack() transfunc() error = %d\n", eRet);
                #endif
                return eRet;
            }

            pucTemp += usUsrdLen;
        }
		
        // 输出数据
        
        psUnpack->ucSubNum++;
        psUnpack->sSub[i].eSubCmd = eCmd;
        psUnpack->sSub[i].usPN = sPnFn.usPn;
        psUnpack->sSub[i].usLen = usUsrdLen;

        // 长度计算
        nLenUserField -= sizeof(sMtDaDt);
        nLenUserField -= usUsrdLen;

        i++;
       
        
    }
    
    // 如果有EC
    if(bmt_have_ec(eAFN, eDir) == TRUE)
    {
        printf("unpack ec()\n");
        psUnpack->bEC = TRUE;
        psEC = (sMtEC *)pucTemp;
        psUnpack->sEC.ucEC1 = psEC->ucEC1;
        psUnpack->sEC.ucEC2 = psEC->ucEC2;

        pucTemp += sizeof(sMtEC);
    }
    
    // 如果有pw
    if(TRUE == bmt_have_pw(eAFN, eDir))
    {
        psUnpack->bPW = TRUE;
        memcpy((void*)(psUnpack->aucPW), (void*)pucTemp, MT_PW_LEN);
        #ifdef MT_DBG_ON
        int i;
        printf("eMtUnpack pw:");
        for(i = 0; i < MT_PW_LEN; i++)
        {
            printf("%d", (UINT8)psUnpack->aucPW[i]);
        }
        printf("\n");
        #endif

        pucTemp += MT_PW_LEN;
    }


    // 如果有TP
    if(TRUE == psUnpack->bTP)
    {
        eRet = emt_trans_tp(MT_TRANS_F2U, (sMtuTp*)&(psUnpack->sTP), (sMtfTp*)pucTemp);
        if(eRet != MT_OK)
        {
            #ifdef MT_DBG_ON
            printf("eMtUnpack() emt_trans_tp() error = %d\n", eRet);
            #endif
            return eRet;
        }

        //pucTemp += sizeof(sMtfTp);
    }
#ifdef MT_DBG_ON
    else
    {
        printf("unpack have none tp\n");
    }
#endif
    
    
    


#ifdef MT_DBG_ON
    printf("-------eMtUnpack()------------------\n");
#endif 
    return MT_OK;
}

/*****************************************************************************
 函 数 名  : usmt_get_ec_pw_tp_len
 功能描述  : 根据一个主命令类型 和 报文的传送方向，计算三个域的总字长
 输入参数  : eMtAFN eAFN  
             eMtDir eDir  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月25日 星期四
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
UINT16 CNxRuler::usmt_get_ec_pw_tp_len(eMtAFN eAFN, eMtDir eDir)
{

    UINT16 usLenEcPwTp = 0;
    BOOL   bEc = FALSE;
    BOOL   bPw = FALSE;
    BOOL   bTp = FALSE;
	
    bEc = bmt_have_ec(eAFN, eDir);
    bPw = bmt_have_pw(eAFN, eDir);
    bTp = bmt_have_tp(eAFN, eDir);
	
    if(bEc == TRUE)
    {
        usLenEcPwTp += sizeof(sMtEC);
    }
	
    
    if(bPw == TRUE)
    {
        usLenEcPwTp += MT_PW_LEN;
    }
	
	
    if(bTp == TRUE)
    {
        usLenEcPwTp += sizeof(sMtfTp);
    }
	
    
    return usLenEcPwTp;
}


/*****************************************************************************
 函 数 名  : eMtTransDaDt_to_PnFn
 功能描述  : 将数据信息单元标识从DaDt结构转换为PnFn结构
 输入参数  : sMtDaDt *psDaDt  
             sMtPnFn *psPnFn  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::eMtTransDaDt_to_PnFn(sMtDaDt *psDaDt, sMtPnFn *psPnFn)
{
	if(!psPnFn || !psDaDt)
	{
		return MT_NULL;
	}

	if(psDaDt->ucDT2 > 30)
	{
		return MT_OUT_RNG;
	}

    UINT8 ucShift = 0;

    if(psDaDt->ucDA1 == 0 && psDaDt->ucDA2 == 0)
    {
        psPnFn->usPn = 0;
    }
    else
    {
        switch(psDaDt->ucDA1)
        {
            case 0x01:
                ucShift = 1;
                break;
                
            case 0x02:
                ucShift = 2; 
                break;
                
            case 0x04:
                ucShift = 3;
                break;
                
            case 0x08:
                ucShift = 4; 
                break;

            case 0x10:
                ucShift = 5;
                break;
                
            case 0x20:
                ucShift = 6; 
                break;
                
            case 0x40:
                ucShift = 7;
                break;
                
            case 0x80:
                ucShift = 8; 
                break;

            default:
                  return MT_ERR_PARA;
                  //break;

        }
        
       psPnFn->usPn = ((psDaDt->ucDA2 - 1) * 8 + ucShift);
    }


    if(psDaDt->ucDT1 == 0 && psDaDt->ucDT2 == 0)
    {
        psPnFn->usFn = 0;
    }
    else
    {
         switch(psDaDt->ucDT1)
        {
            case 0x01:
                ucShift = 1;
                break;
                
            case 0x02:
                ucShift = 2; 
                break;
                
            case 0x04:
                ucShift = 3;
                break;
                
            case 0x08:
                ucShift = 4; 
                break;

            case 0x10:
                ucShift = 5;
                break;
                
            case 0x20:
                ucShift = 6; 
                break;
                
            case 0x40:
                ucShift = 7;
                break;
                
            case 0x80:
                ucShift = 8; 
                break;

            default:
                  return MT_ERR_PARA;
                  //break;

        }

        psPnFn->usFn = (psDaDt->ucDT2 * 8 + ucShift);

    }
    
    #ifdef MT_DBG_ON
    printf("eMtTransDaDt_to_PnFn() in sPnFn.usfn = %d sPnFn.usPn = %d\n", psPnFn->usFn, psPnFn->usPn);
    printf("eMtTransDaDt_to_PnFn() out Da1 = %d Da2 = %d Dt1 = %d Dt2 = %d\n", 
            psDaDt->ucDA1,
            psDaDt->ucDA2,
            psDaDt->ucDT1,
            psDaDt->ucDT2);
    #endif 
	return MT_OK;
}


void CNxRuler::add( UINT8 ucFn )
{
	
}


// 协议初始化
eMtErr CNxRuler::emt_init( sMtInit *psInit )
{
	if(!psInit)
	{
		return MT_NULL;
	}
	
	m_role = psInit->eRole ;
	//m_address = psInit->sAdress;
	m_ucPermitDelayMinutes = psInit->ucPermitDelayMinutes;
	
	//initMapCmdInfor();
	m_bInit = TRUE;
	
	return MT_OK;
}

/*****************************************************************************
 函 数 名  : emtPackLite
 功能描述  : 打包函数，尽量屏蔽用户不关心的数据
 输入参数  : sMtDaDt *psDaDt  
             sMtPnFn *psPnFn  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr CNxRuler::emtPackLite( smtPackLite *psPackLite, UINT16 *pusLen, UINT8 *pOutBuf )
{
	if(!psPackLite || !pusLen || !pOutBuf)
	{
		return MT_NULL;
	}

	char *pPara = (char *)malloc (MT_PACK_LEN_MAX);
	if(!pPara)
	{
		return MT_ERR_IO;
	}

	if(m_bInit == FALSE)
	{
		return MT_ERR_INIT;
	}
	
	smtPack *psPack = (smtPack *)pPara;
	sMtuCtrl     sCtrl;
	eMtAFN eAfn;
	eMtDir eDir;
	eMtPRM ePRM;
	eMtErr eRet;
	sMtuSEQ suSEQ;
	UINT8 ucSEQ = 0;

	eDir = (m_role == MT_ROLE_MASTER) ? MT_DIR_M2S : MT_DIR_S2M;
	ePRM = (psPackLite->bActive == TRUE) ? MT_PRM_ACTIVE : MT_PRM_PASIVE;
	eAfn = psPackLite->eMainCmd;
	// 构造 emtPack()参数
	psPack->sAddress = psPackLite->sAddress;
	psPack->eMainCmd = eAfn;
	

	eRet = eMtGetCtrl(eAfn, eDir, ePRM, &sCtrl);
	if(eRet != MT_OK)
	{
		return MT_ERR_CTRL;
	}
	psPack->sCtrl = sCtrl;
	//psPack->ucPFC = psPackLite->ucPFC;


	suSEQ.bCon = bmt_need_con(eAfn,eDir);
	suSEQ.bTpv = bmt_have_tp(eAfn,eDir);
	suSEQ.ePos = MT_POS_SIGLE;
	suSEQ.ucSEQ = m_ucPFC & 0x0F;
	eRet = emt_trans_SEQ(MT_TRANS_U2F,&suSEQ,(sMtfSEQ*)&ucSEQ);
	if(eRet != MT_OK)
	{
		return MT_ERR_SEQ;
	}

	//psPack->ucSEQ = ucSEQ;
	
	psPack->bCon = suSEQ.bCon;
	psPack->bEC = bmt_have_ec(eAfn,eDir);
	psPack->bPW = bmt_have_pw(eAfn,eDir);
	psPack->bTP = suSEQ.bTpv;

	// 调用 emtPack()
	psPack->sEC = psPackLite->sEC;
	psPack->sTP = psPackLite->sTP;
	
	m_EC = psPackLite->sEC;
	


	for(int i = 0; i < 16; i++)
	{
		psPack->aucPW[i] = psPackLite->aucPW[i];
	}
	
	psPack->ucSubNum = psPackLite->ucSubNum;
	
	memcpy(psPack->sSub, psPackLite->sSub, psPack->ucSubNum * sizeof(smtSub));
	
	

	eRet = emtPack(psPack,pusLen,pOutBuf);
	if(eRet != MT_OK)
	{
		return eRet;
	}


	
	if(pPara != NULL)
	{
		free(pPara);
		pPara = NULL;
	}
	return MT_OK;
}

char * CNxRuler::getErrMessage( eMtErr err )
{
	char * pRet;
	switch(err)
	{
	case MT_OK:             // 无错误   
		pRet = "MT_OK";
		break;
	case MT_NULL:           // 指针为空    
        pRet = "MT_NULL";
		break;
	case MT_OUT_RNG:        // 参数越界  
		pRet = "MT_OUT_RNG";
		break;
	case MT_NONE:           // 不存在:没有找到  
		pRet = "MT_NONE";
		break;
	case MT_ERR_IO:         // IO错误    
		pRet = "MT_ERR_IO";
		break;
	case MT_ERR_RES:        // 资源不足
		pRet = "MT_ERR_RES";
		break;
	case MT_ERR_INIT:       // 没有初始化
		pRet = "MT_ERR_INIT";
		break;
	case MT_ERR_PARA:       // 参数错误
		pRet = "MT_ERR_PARA";
		break;
	case MT_ERR_FN:         // 指定Afn 中不支持的 Fn
		pRet = "MT_ERR_FN";
		break;
	case MT_ERR_PN:         // 指定Afn Fn 中不支持的 Pn
		pRet = "MT_ERR_PN";
		break;
	case MT_ERR_ADDR:       // 无效地址
		pRet = "MT_ERR_ADDR";
		break;
	case MT_ERR_CTRL:       // 控制域错误 
		pRet = "MT_ERR_CTRL";
		break;
	case MT_ERR_SEQ:        // SEQ域错误
		pRet = "MT_ERR_SEQ";
		break;
	case MT_ERR_SEQ2CS:     // 
		pRet = "MT_ERR_SEQ2CS";
		break;
	case MT_ERR_AFN:        // AFN 错误
		pRet = "MT_ERR_AFN";
		break;
	case MT_ERR_UNCOMP:     // 不完整的协议包
		pRet = "MT_ERR_UNCOMP";
		break;
	case MT_ERR_0x68:       // 错误的报文起始
		pRet = "MT_ERR_0x68";
		break;
	case MT_ERR_PROTO:      // 错误的协议标识
		pRet = "MT_ERR_PROTO";
		break;
	case MT_ERR_CS:         // 错误的检测和
		pRet = "MT_ERR_CS";
		break;
	case MT_ERR_0x16:       // 错误的结尾符
		pRet = "MT_ERR_0x16";
		break;
	case MT_ERR_LOGIC:      // 错误的处理逻辑
		pRet = "MT_ERR_LOGIC";
		break;
	case MT_ERR_PACK:       // 不是一个有效的包 
		pRet = "MT_ERR_PACK";
	break;
	default:
		pRet = "unkown";
		break;

	}

	return pRet;
}

CString CNxRuler::BufferToHex( char* pBuf, UINT16 usLen )
{
	CString strOut;
	CString strTmp;
	int len;
	len = (int)usLen;
	int i;
	for (i = 0; i < len; i++)
	{
		strTmp.Format("%02X ",(UINT8)pBuf[i]);
		strOut+= strTmp;
		
	}

	return strOut;
	
}



/************************************************************************
函数名称：CStringToHexBuffer
函数功能：将字符串 转换向16进制的char[],并输出其长度
输入参数：strText
输出参数：pOutBuf
		  pLen
返回值：  BOOL 转换成功 true 否则 false
函数说明：

************************************************************************/
BOOL CNxRuler::CStringToHexBuffer( CString strText, char *pOutBuf, UINT16 *pLen )
{
	if(!pOutBuf || !pLen)
	{
		return FALSE;
	}

	// 去掉空格
	strText.Replace(" ",NULL);
	int StrLen     = 0;
	int BufLen     = 0;
	int strLenLeft = 0;
	int i          = 0;
	char *pBuf     = NULL;
	CString strHex, strTmp;

	StrLen = strText.GetLength();

	if(StrLen%2 != 0)
	{
		return FALSE;
	}
	
	BufLen = StrLen/2;
	strLenLeft = StrLen;

	for (i = 0; i < BufLen; i++)
	{
		strHex = strText.Left(2);
		pOutBuf[i] = strtol(strHex, NULL, 16);
		strLenLeft -= 2;
		strText = strText.Right(strLenLeft);

	}

	*pLen = BufLen;


	return TRUE;	
}


CString CNxRuler::GetAfnName( eMtAFN eAfn )
{
	CString strName;
	switch(eAfn)
	{
	case AFN_00_CONF:
		strName = "AFN_00_CONF 确认否认";
		break;
	case AFN_01_RSET:
		strName = "AFN_01_RSET 复位";
		break;
	case AFN_02_LINK:
		strName = "AFN_02_LINK 接口检测";
		break;
	case AFN_03_RELY:
		strName = "AFN_03_RELY 中继站命令";
		break;
	case AFN_04_SETP:
		strName = "AFN_04_SETP 设置参数";
		break;
	case AFN_05_CTRL:
		strName = "AFN_05_CTRL 控制命令";
		break;
	case AFN_06_AUTH:
		strName = "AFN_06_AUTH 身份认证";
		break;
	case AFN_08_CASC:
		strName = "AFN_08_CASC 请求被级联终端主动上报";
		break;
	case AFN_09_CFIG:
		strName = "AFN_09_CFIG 请求终端配置";
		break;
	case AFN_0A_GETP:
		strName = "AFN_0A_GETP 查询参数";
		break;
	case AFN_0B_ASKT:
		strName = "AFN_0B_ASKT 请求任务数据";
		break;
	case AFN_0C_ASK1:
		strName = "AFN_0C_ASK1 请求1类数据 实时数据";
		break;
	case AFN_0D_ASK2:
		strName = "AFN_0D_ASK2 请求2类数据 历史数据";
		break;
	case AFN_0E_ASK3:
		strName = "AFN_0E_ASK3 请求3类数据 事件数据";
		break;
	case AFN_0F_FILE:
		strName = "AFN_0F_FILE 文件传输";
		break;
	case AFN_10_DATA:
		strName = "AFN_10_DATA 数据转发";
		break;
	default:
		break;
	}

	return strName;
}


/************************************************************************
获得该命令的类型的PRM                                              
BOOL bAuto  是否主动上报
                                      
************************************************************************/
eMtPRM CNxRuler::getPrm( eMtDir eDir, eMtAFN eAfn, BOOL bAuto )
{
	
	eMtPRM ePrm;
	
	switch(eAfn)
	{
	case AFN_00_CONF:
		ePrm = MT_PRM_PASIVE;
		break;
	
	case AFN_01_RSET:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_UNKWON;
		}
		else
		{
		  ePrm = MT_PRM_ACTIVE;
		}
	
		break;
	case AFN_02_LINK:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_ACTIVE;
		}
		else
		{
			ePrm = MT_PRM_UNKWON;
		}
		
		break;
	case AFN_03_RELY:
		ePrm = MT_PRM_PASIVE;
		break;
	case AFN_04_SETP:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_UNKWON;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;
	case AFN_05_CTRL:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_UNKWON;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;
	case AFN_06_AUTH:  // 该命令可以双向，不同的子命令，类型不同，需要程序内部写死

		ePrm = MT_PRM_UNKWON;
		break;
	case AFN_09_CFIG:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_UNKWON;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;

	case AFN_0A_GETP:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_PASIVE;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;


	case AFN_0B_ASKT:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_PASIVE;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;


	case AFN_0C_ASK1:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_PASIVE;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;

	case AFN_0D_ASK2:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_PASIVE;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;

	case AFN_0E_ASK3:
		if (eDir == MT_DIR_S2M)
		{
			ePrm = MT_PRM_PASIVE;
		}
		else
		{
			ePrm = MT_PRM_ACTIVE;
		}
		break;


	default:
			ePrm = MT_PRM_UNKWON;
		break;
	}



	if (eDir == MT_DIR_S2M && bAuto)
	{
	}


	return ePrm;
		
}

void CNxRuler::setEC( sMtEC sEC )
{
	m_EC = sEC;
}


void CNxRuler::setPw( CString strPw )
{
	CString str = "0000000000000000";
	CString strPwLast;
	int lenInput = 0;
	lenInput = strPw.GetLength();
	if (lenInput > 16)
	{
		lenInput = 16;
		strPwLast = strPw.Left(16);
	}
	else
	{
		strPwLast = str.Left(16 - lenInput) + strPw;
	}
	
	char *pw = strPwLast.GetBuffer(16);
	memcpy(m_aucPw, pw, 16);
	strPwLast.ReleaseBuffer();
}




/*
用向量来管理命令信息，第二种方式，原来的map有局限
*/
void CNxRuler::AddInforVector( eMtCmd eCmd, eMtDir eDir, eMtPn ePn, pNxTransFunc pFunc, CString strName )
{


	sMtCmdInfors sCmdInfor;
	sCmdInfor.eCmd    = eCmd;
	sCmdInfor.eDir    = eDir;
	sCmdInfor.ePn     = ePn;
	sCmdInfor.pFunc   = pFunc;
	sCmdInfor.strName = strName;	

	m_vCmdInfor.push_back(sCmdInfor);
	
}


/*****************************************************************************
 函 数 名  : bMtGetDoubleSign
 功能描述  : 获得一个double 的符号位
 输入参数  : double dVal  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月30日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
#if 0
int bMtGetDoubleSign( double dVal )
{
	uMtDoubleFmt  doubleFmt;
	doubleFmt.v = dVal;
	
	return doubleFmt.s.sign;
}

/*****************************************************************************
 函 数 名  : vMtSetDoubleSign
 功能描述  : 设置浮点数的符号位
 输入参数  : int sign   >= 0 时，设置为正数， < 0时设置为负数    
 输出参数  : double *pdVal  
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月30日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
void vMtSetDoubleSign( double *pdVal, int sign )
{
	uMtDoubleFmt  *pdoubleFmt;
	pdoubleFmt = (uMtDoubleFmt*)pdVal;
	
	if(sign > 0)
	{
		pdoubleFmt->s.sign = 0;
	}
	else
	{
		pdoubleFmt->s.sign = 1;
	}
}
#endif
/*****************************************************************************
 函 数 名  : bMtTrans_fmtsMillion_to_double
 功能描述  : 将 sMtFmtsMillion 转换为double
 输入参数  : sMtFmtsMillion *psMtFmtsMillion                           
 输出参数  : double *pdValue    
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 函数说明  : double  : 1bit（符号位） 11bits（指数位） 52bits（尾数位） 
 			 2^52 = 4503599627370496
 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
BOOL bMtTrans_fmtsMillion_to_double( sMtFmtsMillion *psMtFmtsMillion, double *pdValue )
{
	int  valid   = 0;      // 有效位
	double  exp  = 0.0;    // 指数位
	int  sign    = 0;      // 符号位
	int  i       = 0;
	double  dRet = 0.0;
	UINT8 bcd[7] = {0};
	
	bcd[0] = (UINT8) psMtFmtsMillion->BCD_0;
	bcd[1] = (UINT8) psMtFmtsMillion->BCD_1;
	bcd[2] = (UINT8) psMtFmtsMillion->BCD_2;
	bcd[3] = (UINT8) psMtFmtsMillion->BCD_3;
	bcd[4] = (UINT8) psMtFmtsMillion->BCD_4;
	bcd[5] = (UINT8) psMtFmtsMillion->BCD_5;
	bcd[6] = (UINT8) psMtFmtsMillion->BCD_6;
	
	for(i = 0; i < 7; i++)
	{
		if(bcd[i] > 9)
		{
			return FALSE;
		}
	}
	
	for(i = 0; i < 7; i++)
	{
		valid += bcd[i]*nMtPow(i);
	}
	
	
	sign = psMtFmtsMillion->S == 0 ? 1 : -1;
	
	if(psMtFmtsMillion->G3 == 0)
	{
		if(psMtFmtsMillion->G2 == 0 && psMtFmtsMillion->G1 == 0)
		{
			exp = 4.0;
		}
		
		if(psMtFmtsMillion->G2 == 0 && psMtFmtsMillion->G1 == 1)
		{
			exp = 3.0;
		}
		
		if(psMtFmtsMillion->G2 == 1 && psMtFmtsMillion->G1 == 0)
		{
			exp = 2.0;
		}
		
		if(psMtFmtsMillion->G2 == 1 && psMtFmtsMillion->G1 == 1)
		{
			exp = 1.0;
		}
		
	}
	else
	{
		if(psMtFmtsMillion->G2 == 0 && psMtFmtsMillion->G1 == 0)
		{
			exp = 0.0;
		}
		
		if(psMtFmtsMillion->G2 == 0 && psMtFmtsMillion->G1 == 1)
		{
			exp = -1.0;
		}
		
		if(psMtFmtsMillion->G2 == 1 && psMtFmtsMillion->G1 == 0)
		{
			exp = -2.0;
		}
		
		if(psMtFmtsMillion->G2 == 1 && psMtFmtsMillion->G1 == 1)
		{
			exp = -3.0;
		}
		
	}
	
	
	dRet = sign * valid * pow(10.0,exp);
	
	*pdValue = dRet;
	
	return TRUE;
	
}


/*****************************************************************************
 函 数 名  : eMtTrans_double_to_fmtsMillion
 功能描述  : 将double转换为sMillon结构
 输入参数  : double dValue                    
             int exp  4 3 2 1 0 -1 -2 -3                         
             
 输出参数  : sMtFmtsMillion *psMtFmtsMillion  
 返 回 值  : eMtErr
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月30日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr eMtTrans_double_to_fmtsMillion( double dValue, int nExp, sMtFmtsMillion *psMtFmtsMillion )
{
	if(!psMtFmtsMillion)
	{
		return MT_NULL;
	}

	double zhengshu = 0.0;
	int    sign     = 0;   // 符号位
	const  int index = 6;
	
	switch(nExp)
	{

		case 4:
			{
				if(dValue > 99999990000.0 || dValue < -99999990000.0)
				{
					return MT_OUT_RNG;
				}

				modf(dValue/10000, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);

				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 1;
				psMtFmtsMillion->G2 = 0;
				psMtFmtsMillion->G3 = 0;	
			}
			break;

		case 3:// 只关心到千位。百位, 十位 个位及小数将忽略
			{
				
				if(dValue > 9999999000.0 || dValue < -9999999000.0)
				{
					return MT_OUT_RNG;
				}
				
				modf(dValue/1000, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);
				
				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 1;
				psMtFmtsMillion->G2 = 0;
				psMtFmtsMillion->G3 = 0;	
			}
			break;
		case 2:// // 只关心到百位, 十位 个位及小数将忽略
			{
				if(dValue > 999999900.0 || dValue < -999999900.0)
				{
					return MT_OUT_RNG;
				}

				modf(dValue/100, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);

				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);
				
				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 0;
				psMtFmtsMillion->G2 = 1;
				psMtFmtsMillion->G3 = 0;	
			}
			break;
		case 1: // 只关心到十位 个位及小数将忽略
			{
				if(dValue > 99999990.0 || dValue < -99999990.0)
				{
					return MT_OUT_RNG;
				}

				modf(dValue/10, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);

				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 1;
				psMtFmtsMillion->G2 = 1;
				psMtFmtsMillion->G3 = 0;	
			}
			break;
		case 0:	  //只关心到个位	
			{
				if(dValue > 9999999.0 || dValue < -9999999.0)
				{
					return MT_OUT_RNG;
				}
				
				modf(dValue, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);

				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 0;
				psMtFmtsMillion->G2 = 0;
				psMtFmtsMillion->G3 = 1;	
			}
			break;
			
		case -1: // 只关心到小数点后一位, 后边的数据将忽略
			   {
				if(dValue > 999999.9 || dValue < -999999.9)
				{
					return MT_OUT_RNG;
				}

				modf(dValue*10, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);

				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 1;
				psMtFmtsMillion->G2 = 0;
				psMtFmtsMillion->G3 = 1;	
			}
			break;
		case -2: // 只关心到小数点后2位, 后边的数据将忽略
			{
				if(dValue > 99999.99 || dValue < -99999.99)
				{
					return MT_OUT_RNG;
				}

				modf(dValue*100, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);

				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 0;
				psMtFmtsMillion->G2 = 1;
				psMtFmtsMillion->G3 = 1;	
			}
			break;
		case -3:// 只关心到小数点后3位, 后边的数据将忽略
			{
				if(dValue > 9999.999 || dValue < -9999.999)
				{
					return MT_OUT_RNG;
				}

				modf(dValue*1000, &zhengshu);
				sign = bMtGetDoubleSign(zhengshu);
				vMtSetDoubleSign(&zhengshu, 1);
				
				char buf[8] = {0};
				sprintf(buf, "%07.0lf\n", zhengshu, 7);

				//输出结构
				psMtFmtsMillion->BCD_0 = buf[index - 0] - '0';
				psMtFmtsMillion->BCD_1 = buf[index - 1] - '0';
				psMtFmtsMillion->BCD_2 = buf[index - 2] - '0';
				psMtFmtsMillion->BCD_3 = buf[index - 3] - '0';		
				psMtFmtsMillion->BCD_4 = buf[index - 4] - '0';
				psMtFmtsMillion->BCD_5 = buf[index - 5] - '0';
				psMtFmtsMillion->BCD_6 = buf[index - 6] - '0';

				psMtFmtsMillion->S  = sign;
				psMtFmtsMillion->G1 = 1;
				psMtFmtsMillion->G2 = 1;
				psMtFmtsMillion->G3 = 1;	
			}
			break;
		default:
			break;


	}



	return MT_OK;
}

#if 0
/*****************************************************************************
 函 数 名  : nMtPow
 功能描述  : 求10的N次方
 输入参数  : UINT8 exp  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
int nMtPow( UINT8 exp )
{
	if(exp > 10)
	{
		return -1;
	}
	
	if(exp == 0)
	{
		return 1;
	}
	
	return 10 * nMtPow(exp -1);
	
}

#endif


/*****************************************************************************
 函 数 名  : emtTrans_CfgNotElecValue
 功能描述  : 非电气量配置数据结构转换函数  (AFN04 F33)
 输入参数  : eMtTransDir eDir  
             void *psUser      
             void *psFrame     
             UINT16 *pusfLen   
 输出参数  : 无
 返 回 值  : eMtErr
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emtTrans_CfgNotElecValue(eMtTransDir eDir,void *psUser, void *psFrame, UINT16 *pusfLen)
{

	if(!psUser || !psFrame || !pusfLen)
	{
		return MT_NULL;
	}

	sMtCfgNotElec    *psMtCfgNotElec_u;
	sMtCfgNotElec_f  *psMtCfgNotElec_f;
	
	psMtCfgNotElec_u = (sMtCfgNotElec  *)psUser;
	psMtCfgNotElec_f = (sMtCfgNotElec_f*)psFrame;
	eMtErr eRet      = MT_OK;
	int    nExp      = 0;   // 精度   4 3 2 1 0 -1 -2 -3
	BOOL   bTrans    = FALSE;

	if(MT_TRANS_U2F == eDir)
	{

		switch(psMtCfgNotElec_u->eType)
		{
			case MT_NELEC_TEMP:
			case MT_NELEC_FLOW:
			case MT_NELEC_FLOW_V:
			case MT_NELEC_PRESS:
			case MT_NELEC_HUMID:
			case MT_NELEC_ILLUM:
			case MT_NELEC_ROTATE:
				nExp = -2;      // 这个量根据实际情况再详细调整
				break;

			default:
				return MT_NONE;
				//break;

		}

		// type
		psMtCfgNotElec_f->ucType = (UINT8)psMtCfgNotElec_u->eType;
		eRet = eMtTrans_double_to_fmtsMillion(psMtCfgNotElec_u->dMin, nExp, &(psMtCfgNotElec_f->sMin));
		if(eRet != MT_OK)
		{
			return eRet;
		}
		eRet = eMtTrans_double_to_fmtsMillion(psMtCfgNotElec_u->dMax, nExp, &(psMtCfgNotElec_f->sMax));
		if(eRet != MT_OK)
		{
			return eRet;
		}
		

	}
	else if(MT_TRANS_F2U == eDir)
	{
		psMtCfgNotElec_u->eType = (eMtNotElec)(psMtCfgNotElec_f->ucType);
		
		bTrans = bMtTrans_fmtsMillion_to_double(&(psMtCfgNotElec_f->sMin), &(psMtCfgNotElec_u->dMin));
		if(bTrans != TRUE)
		{
			return MT_ERR_PARA;
		}
		bTrans = bMtTrans_fmtsMillion_to_double(&(psMtCfgNotElec_f->sMax), &(psMtCfgNotElec_u->dMax));
		if(bTrans != TRUE)
		{
			return MT_ERR_PARA;
		}

	}
	
	*pusfLen = sizeof(sMtCfgNotElec_f);
	return MT_OK;
}




/*****************************************************************************
 函 数 名  : emtTrans_NotElecValue
 功能描述  : 非电气量数据结构转换函数  (AFN05 F90)
 输入参数  : eMtTransDir eDir  
             void *psUser      
             void *psFrame     
             UINT16 *pusfLen   
 输出参数  : 无
 返 回 值  : eMtErr
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emtTrans_NotElecValue(eMtTransDir eDir,void *psUser, void *psFrame, UINT16 *pusfLen)
{
	if(!psUser || !psFrame || !pusfLen)
	{
		//DEBUG("MT_NULL");
		return MT_NULL;
	}

	sMtNotElec    *psMtNotElec_u;
	sMtNotElec_f  *psMtNotElec_f;
	
	psMtNotElec_u = (sMtNotElec  *)psUser;
	psMtNotElec_f = (sMtNotElec_f*)psFrame;
	eMtErr eRet      = MT_OK;
	int    nExp      = 0;   // 精度   4 3 2 1 0 -1 -2 -3
	BOOL   bTrans    = FALSE;

	if(MT_TRANS_U2F == eDir)
	{

		switch(psMtNotElec_u->eType)
		{
			case MT_NELEC_TEMP:
			case MT_NELEC_FLOW:
			case MT_NELEC_FLOW_V:
			case MT_NELEC_PRESS:
			case MT_NELEC_HUMID:
			case MT_NELEC_ILLUM:
			case MT_NELEC_ROTATE:
				nExp = -2;      // 这个量根据实际情况再详细调整
				break;

			default:
				//DEBUG("MT_NELEC_UNKOWN");
				return MT_NONE;
				//break;

		}

		// type
		psMtNotElec_f->ucType = (UINT8)psMtNotElec_u->eType;
		eRet = eMtTrans_double_to_fmtsMillion(psMtNotElec_u->dValue, nExp, &(psMtNotElec_f->sValue));
		if(eRet != MT_OK)
		{
			//DEBUG("eMtTrans_double_to_fmtsMillion() error = %d", eRet );
			return eRet;
		}

	}
	else if(MT_TRANS_F2U == eDir)
	{
		psMtNotElec_u->eType = (eMtNotElec)(psMtNotElec_f->ucType);
		
		bTrans = bMtTrans_fmtsMillion_to_double(&(psMtNotElec_f->sValue), &(psMtNotElec_u->dValue));
		if(bTrans != TRUE)
		{
			//DEBUG("bMtTrans_fmtsMillion_to_double() error = %d", eRet );
			return MT_ERR_PARA;
		}
	}
	
	*pusfLen = sizeof(sMtNotElec_f);
	return MT_OK;
}






/*****************************************************************************
 函 数 名  : emtTrans_OneByOne
 功能描述  : 逐个确认否认转换函数
 输入参数  : eMtTransDir eDir  
             void *psUser      
             void *psFrame     
             UINT16 *pusfLen   
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年6月9日
    作    者   : 李明
    修改内容   : 新生成函数

*****************************************************************************/
eMtErr emtTrans_OneByOne(eMtTransDir eDir,void *psUser, void *psFrame, UINT16 *pusfLen)
{
	if(!psFrame || !psUser || !pusfLen)
	{
		return MT_NULL;
	}

	sMtOneByOne_f *psOneByOne_f = (sMtOneByOne_f *)psFrame;
	sMtOnebyOne   *psOneByOne_u = (sMtOnebyOne   *)psUser;
	int i = 0;
	sMtPnFn sPnFn = {0};
	eMtErr  eRet  = MT_OK;
	int     nNum  = 0;   // 侧
	
	if(MT_TRANS_F2U == eDir)
	// 帧侧转为用户侧
	{
		// 解析时将其应用层数据长度
		nNum = (int)*pusfLen;
		
		nNum -= sizeof(UINT8);
		nNum /= sizeof(sMtOne_f); // 计算含有确认否认个数

		if(nNum > MT_DT_FN_MAX)
		{
		
			return MT_OUT_RNG;
		}

		psOneByOne_u->eAFN = (eMtAFN)psOneByOne_f->ucAFN;
		psOneByOne_u->ucNum = nNum;
		for(i = 0; i < nNum; i++)
		{
			psOneByOne_u->sOne[i].bOk = psOneByOne_f->sOne[i].ucErr == 0 ? TRUE : FALSE;

			eRet = eMtTransDaDt_to_PnFn_g(&(psOneByOne_f->sOne[i].sDaDt), &sPnFn);
			if(eRet != MT_OK)
			{
			
				return eRet;
			}
			
			psOneByOne_u->sOne[i].eCmd = (eMtCmd) (psOneByOne_u->eAFN << 8 | sPnFn.usFn);
			psOneByOne_u->sOne[i].usPn = (UINT8)sPnFn.usPn;
		}

	}
	else 
	// 用户侧转为帧侧
	{
		psOneByOne_f->ucAFN  = (UINT8)psOneByOne_u->eAFN;
		for(i = 0; i < psOneByOne_u->ucNum; i++)
		{
			sPnFn.usFn = (UINT8)psOneByOne_u->sOne[i].eCmd;
			sPnFn.usPn = psOneByOne_u->sOne[i].usPn;
			eRet = eMtTransPnFn_to_DaDt_g(&sPnFn, &(psOneByOne_f->sOne[i].sDaDt));
			if(eRet != MT_OK)
			{
			
				return eRet;
			}

			// right or error
			psOneByOne_f->sOne[i].ucErr = psOneByOne_u->sOne[i].bOk == TRUE ? 0 : 1;
			
		}
	}

	// 计算在帧侧的字节长度
	*pusfLen = sizeof(UINT8) + sizeof(sMtOne_f) * psOneByOne_u->ucNum;
	
	return MT_OK;
}

#endif