// NxRuler.h: interface for the CNxRuler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NXRULER_H__410AFF02_F248_4933_924F_A13E450903C9__INCLUDED_)
#define AFX_NXRULER_H__410AFF02_F248_4933_924F_A13E450903C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if 0
/******************************************************************************

              版权所有 (C), 2001-2015, 国网电科院通信与用电技术分公司

 ******************************************************************************
  文 件 名   : NxRuler.h
  版 本 号   : 初稿
  作    者   : liming
  生成日期   : 2013年2月21日
  最近修改   :
  功能描述   : Q/GDW376.1 协议api实现头文件
  简语说明   : (1)master -> mst 主站   (2)concentrator -> con  集中器   (3)terminal -> tml 终端
               (4)mt 主站到集中器或终端
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月13日
    作    者   : liming
    修改内容   : 创建文件

******************************************************************************/
//#include "NxRulerTypes.h"
#include <vector>
#include <afxtempl.h>
using namespace std;

typedef eMtErr (*pNxTransFunc)(eMtTransDir eDir, void* pUser, void* pFrame, UINT16 *pusfLen);  // pusFLen为该数据在帧侧的长度

typedef struct
{
	eMtCmd         eCmd;
	eMtDir         eDir;      // 该种报文能发的方向
	eMtPn 		   ePn;
	pNxTransFunc   pFunc;
	CString        strName;
}sMtCmdInfors;     // 与单一命令字相关的信息



typedef CMap<eMtCmd,eMtCmd,sMtCmdInfors,sMtCmdInfors> mapCmdInfor;






typedef struct
{
    /* 必选域 */
    sMtuAddress  sAddress;               // 地址信息
    eMtAFN       eMainCmd;               // 主命令字
    BOOL         bActive;                // 是主动发的，即是启动站， 如主站的命令，从站的心跳，自动上报是为true
    UINT8        ucPFC;                  // 帧计数器

    // 附加域
    sMtEC  sEC;                         // 事件计数器
    sMtuTp sTP;                         // tp字段
    UINT8  aucPW[16];                   // pw字段
	
    /* 变长域 */
    UINT8    ucSubNum;                  // 该帧中包含子命令字的个数最大值(255)
	smtSub   sSub[1];                   // 子命令类型及应用层数据 变长
	
}smtPackLite;       // 用户侧封装解和封装数据结构 精简，会自动算相关量



typedef struct  
{
	eMtRole      eRole;                    // 身份   
	//sMtuAddress  sAdress; 
	UINT8        ucPermitDelayMinutes;     // 允许时延
}sMtInit;






class CNxRuler  
{
public:
	eMtErr emt_init(sMtInit *psInit);
	eMtErr emtPack(smtPack *psPack, UINT16 *pusLen, UINT8  *pOutBuf);
	eMtErr emtUnPack(smtPack *psUnpack, UINT8* pInBuf, UINT16 usLen);

public:
	void setEC(sMtEC sEC);
	void setPw(CString strPw);
	eMtPRM getPrm(eMtDir eDir, eMtAFN eAfn, BOOL bAuto = FALSE);
	char * getErrMessage(eMtErr err);

	eMtErr emtPackLite(smtPackLite *psPackLite, UINT16 *pusLen, UINT8  *pOutBuf);


	BOOL bmt_need_con(eMtAFN eAFN, eMtDir eDir);
	BOOL bmt_have_tp(eMtAFN eAFN, eMtDir eDir);
	BOOL bmt_have_pw(eMtAFN eAFN, eMtDir eDir);
	BOOL bmt_have_ec(eMtAFN eAFN, eMtDir eDir);
	eMtErr eMtIsValidPack(UINT8  *pOutBuf, UINT16 usLen);
	eMtErr emt_find_frist_valid_pack(UINT8  *pinBuf, UINT16 usLen, UINT16 *pusFirstOff, UINT16 *pusFirstLen);
	eMtErr eMtPackCommon(eMtAFN     eAFN,    sMtPackCommon *psCommon,UINT16 *pusLen, UINT8  *pOutBuf);


	eMtAFN  GetResponeAfn( eMtRole eRole, eMtCmd eCmd);// 获得对某cmd的答复类型
	eMtAFN  GetCmdAfn(eMtCmd eCmd);        // 获得某个cmd的所属的afn
	eMtErr  eMtGetCmdInfor(eMtCmd eCmd, eMtDir eDir, sMtCmdInfors *psInfors);
	eMtRole eMtWhoAmI();
	BOOL bMtIsBigEndian();
	CString BufferToHex(char* pBuf, UINT16 usLen);
	BOOL    CStringToHexBuffer(CString strText, char *pOutBuf, UINT16 *pLen);
	CString GetAfnName(eMtAFN eAfn);
	void add(UINT8 ucFn);


	CNxRuler();
	CNxRuler(eMtRole eRole);
	virtual ~CNxRuler();



private:
	void initMapCmdInfor();
	void SetAtMap(eMtCmd eCmd, eMtDir eDir, eMtPn ePn, pNxTransFunc pFunc, CString strName);
	void AddInforVector(eMtCmd eCmd, eMtDir eDir, eMtPn ePn, pNxTransFunc pFunc, CString strName);

	UINT32 ulmt_read_uint32_small_endian(UINT8 *pRead);
	UINT16 usmt_read_uint16_small_endian(UINT8 *pRead);	
	eMtErr emt_write_uint32_small_endian(UINT32 ulData,   UINT8* pWrite);
	eMtErr emt_write_uint16_small_endian(UINT16 usData, UINT8* pWrite);
	UINT16 usmt_get_ec_pw_tp_len(eMtAFN eAFN, eMtDir eDir);
	UINT8 ucmt_get_bcd(UINT32 ulData, UINT8 ucPos);
	eMtErr eMtGetCtrl(eMtAFN eAFN, eMtDir eDir, eMtPRM ePRM, sMtuCtrl *psuCtrl);

	eMtErr emt_bcd_to_str(const char* pbcd, char *pstr, int len);
	eMtErr eMtTransDaDt_to_PnFn(sMtDaDt *psDaDt, sMtPnFn *psPnFn);
	eMtErr emt_str_to_bcd(const char *pstr, char *pbcd, int len);
	UINT8 ucmt_get_check_sum(UINT8 *pStartPos, UINT16 usLen);
	eMtErr emt_trans_SEQ(eMtTransDir eDir, sMtuSEQ *puSEQ, sMtfSEQ *pfSEQ);
	eMtErr emt_trans_addr(eMtTransDir eDir, sMtuAddress *puAddr, sMtfAddress *pfAddr);
	eMtErr emt_trans_ctrl(eMtTransDir eDir, sMtuCtrl *puCtrl, UINT8* pfCtrl);
	eMtErr emt_get_mtutp(UINT8 ucPFC, sMtuTp *psuTp);
	eMtErr emt_trans_tp(eMtTransDir eDir, sMtuTp* puTp, sMtfTp* pfTp);
	eMtErr eMtTransPnFn_to_DaDt(sMtPnFn *psPnFn, sMtDaDt *psDaDt);
	void vMtfree(UINT8 *pBuf);
	
	eMtRole      m_role;                    // 身份   
	sMtuAddress  m_address; 
	mapCmdInfor  m_mapCmdInfor;             // cmd与相当信息对应map
	BOOL         m_bInit;                   // 是否已经初始化
	UINT8        m_ucPermitDelayMinutes;    // 允许时延
	UINT8        m_ucPFC;                   // 帧序列
	sMtEC        m_EC;                      // 事件计数器
	UINT8        m_aucPw[MT_PW_LEN];        // 密码

	vector<UINT8>  m_fnList;
	eMtAFN       m_eAfn;
	
	vector<sMtCmdInfors> m_vCmdInfor;

};

#endif
#endif // !defined(AFX_NXRULER_H__410AFF02_F248_4933_924F_A13E450903C9__INCLUDED_)
