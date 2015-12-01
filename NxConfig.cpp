// NxConfig.cpp: implementation of the CNxConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NxMaster.h"
#include "NxConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define  STR_TRUE  "true"
#define  STR_FALSE "false"

CNxConfig::CNxConfig()
{

	m_hRootKey = HKEY_LOCAL_MACHINE;
	m_mstPreName = "master_pre";
	m_tmlPreName = "terminal_pre";
	m_configMst  = "master_config";
	m_configTml  = "terminal_config";
	m_rootName   = "NxMaster";
}

CNxConfig::~CNxConfig()
{
	
}



void CNxConfig::initConfig()
{
	UINT16 ausPn[255] = {0};
#define  BUF_LEN 512
	UINT8  buf[BUF_LEN] = {0};   // 为变长的数据结构申请空间
	int i = 0;
	

	CString      strSubRootKey = "software";
	
	CRegistry  reg_mst, reg_mst_pre, reg_tml_pre,reg_tml_cfg, reg_mst_cfg;
	reg_mst.SetRootKey(m_hRootKey);
	BOOL bOk;
	bOk = reg_mst.Open(strSubRootKey);
	if(reg_mst.bKeyExists(m_rootName, NULL) == FALSE)
	{
		bOk = reg_mst.CreateKey(m_rootName);
	}
	

	//insert master_pre
	reg_mst_pre.SetRootKey(m_hRootKey);
	reg_mst_pre.Open(strSubRootKey);
	reg_mst_pre.Open(m_rootName);
	reg_mst_pre.CreateKey(m_mstPreName);


	// insert reg_tml_pre
	reg_tml_pre.SetRootKey(m_hRootKey);
	reg_tml_pre.Open(strSubRootKey);
	reg_tml_pre.Open(m_rootName);
	reg_tml_pre.CreateKey(m_tmlPreName);
	
	// insert m_configMst
	reg_mst_cfg.SetRootKey(m_hRootKey);
	reg_mst_cfg.Open(strSubRootKey);
	reg_mst_cfg.Open(m_rootName);
	reg_mst_cfg.CreateKey(m_configMst);

	// insert m_configTml
	reg_tml_cfg.SetRootKey(m_hRootKey);
	reg_tml_cfg.Open(strSubRootKey);
	reg_tml_cfg.Open(m_rootName);
	reg_tml_cfg.CreateKey(m_configTml);


	// set afn00f1
	sMcAfn00F1 eResCode = MC_RES_OK;
	SetPreAfn00F1(&eResCode, TRUE,  FALSE);
	SetPreAfn00F1(&eResCode, FALSE, FALSE);
	
	// set afn04f1
	sMcAfn04f1 sAfn04f01;
	sAfn04f01.ucPermitDelayM = 255;
	sAfn04f01.ucHeartBeat = 1;
	sAfn04f01.usWaitTimeoutS = 4095;
	sAfn04f01.ucReSendTimes = 3;
	sAfn04f01.bPermitRt = TRUE;
	sAfn04f01.bPermitTk = TRUE;
	sAfn04f01.bPermitEv = TRUE;
	SetPreAfn04F1(&sAfn04f01, TRUE, FALSE);
	SetPreAfn04F1(&sAfn04f01, FALSE, FALSE);



	// set afn04F2
	sMcAfn04f2 *pData;
	pData = (sMcAfn04f2 *)buf;
	pData->ucN = 1;
	pData->sOne[0].bValid = TRUE;
	pData->sOne[0].ucID = 1;
	pData->sOne[0].ucNoNum = 0;
	pData->sOne[0].sBackIP.ip[0] = 192;
	pData->sOne[0].sBackIP.ip[1] = 168;
	pData->sOne[0].sBackIP.ip[2] = 1;
	pData->sOne[0].sBackIP.ip[3] = 2;

	pData->sOne[0].sMainIP.ip[0] = 192;
	pData->sOne[0].sMainIP.ip[1] = 168;
	pData->sOne[0].sMainIP.ip[2] = 1;
	pData->sOne[0].sMainIP.ip[3] = 1;
	
	pData->sOne[0].usMainPort = 6666;
	pData->sOne[0].usBackPort = 7777;
	
	memcpy(pData->sOne[0].ucascAPN, "apn", 3);
	memcpy(pData->sOne[0].usr, "username", 8);
	memcpy(pData->sOne[0].pwd, "password", 8);

	SetPreAfn04F2(pData, TRUE, FALSE);
	SetPreAfn04F2(pData, FALSE, FALSE);

	// set Afn 04 F3
	sMcAfn04f3 sAfn04f3;
	sAfn04f3.ucTypeID = 255;
	sAfn04f3.usAuthPara = 0;
	SetPreAfn04F3(&sAfn04f3, TRUE, FALSE);
	SetPreAfn04F3(&sAfn04f3, FALSE, FALSE);

	// set afn04 f4
	sMcAfn04f4 sAfn04f4;
	for (i = 0; i < 8; i++)
	{
		sAfn04f4.ulAddr[i] = 0;
	}

	SetPreAfn04F4(&sAfn04f4, TRUE, FALSE);
	SetPreAfn04F4(&sAfn04f4, FALSE, FALSE);

	// set AFN04 F5
	sMcAfn04f5 sAfn04f5;
	sAfn04f5.usPort = 1;
	sAfn04f5.sConIp.eVersion = MC_IP_V4;
	sAfn04f5.sConIp.ip[0] = 192;
	sAfn04f5.sConIp.ip[1] = 168;
	sAfn04f5.sConIp.ip[2] = 0;
	sAfn04f5.sConIp.ip[3] = 1;

	sAfn04f5.sMask.eVersion = MC_IP_V4;
	sAfn04f5.sMask.ip[0] = 255;
	sAfn04f5.sMask.ip[1] = 255;
	sAfn04f5.sMask.ip[2] = 255;
	sAfn04f5.sMask.ip[3] = 0;


	sAfn04f5.sGateIp.eVersion = MC_IP_V4;
	sAfn04f5.sGateIp.ip[0] = 192;
	sAfn04f5.sGateIp.ip[1] = 168;
	sAfn04f5.sGateIp.ip[2] = 0;
	sAfn04f5.sGateIp.ip[3] = 1;
	
	sAfn04f5.sDelgIp.eVersion = MC_IP_V4;
	sAfn04f5.sDelgIp.ip[0] = 192;
	sAfn04f5.sDelgIp.ip[1] = 168;
	sAfn04f5.sDelgIp.ip[2] = 0;
	sAfn04f5.sDelgIp.ip[3] = 1;

	sAfn04f5.eDelegate = MC_DELG_HTTP;
	sAfn04f5.usDelgPort = 1234;
	sAfn04f5.eDelgLink = MC_DELK_USRPWD;
	sAfn04f5.bDlegUsr = TRUE;
	sAfn04f5.bDlegPwd = TRUE;
	sAfn04f5.ucDlegUsrLen = 5;
	sAfn04f5.ucDlegPwdLen = 5;

	memcpy(sAfn04f5.ucDlegPwd, "admin", 5);
	memcpy(sAfn04f5.ucDlegUsr, "admin", 5);

	SetPreAfn04F5(&sAfn04f5, TRUE, FALSE);
	
	// setAfn 0a F2
	sMcAfn11f2q *sAfn11f2q;
	memset(buf, 0, BUF_LEN);
	sAfn11f2q = (sMcAfn11f2q*)buf;
	sAfn11f2q->ucN = 2;
	sAfn11f2q->ucID[0] = 1;
	sAfn11f2q->ucID[1] = 2;
	SetPreAfn0aF2q(sAfn11f2q, TRUE, FALSE);

	// set Afn 0a F7
	sMcAfn10f7q *sAfn10f7q;
	memset(buf, 0, BUF_LEN);
	sAfn10f7q = (sMcAfn10f7q*)buf;
	sAfn10f7q->usN = 2;
	sAfn10f7q->usPort[0] = 1;
	sAfn10f7q->usPort[1] = 2;
	SetPreAfn0aF7q(sAfn10f7q, TRUE, FALSE);

	// set afn 04 f6
	sMcAfn04f6 *psAfn04f6;
	memset(buf, 0, BUF_LEN);
	psAfn04f6 = (sMcAfn04f6*)buf;
	psAfn04f6->eType       = MC_CASC_RS485;
    psAfn04f6->sSer.eBaud  = MC_BAUD_1200;
    psAfn04f6->sSer.bStop1 = TRUE;
    psAfn04f6->sSer.bCheck = TRUE;
    psAfn04f6->sSer.bOdd   = TRUE;
    psAfn04f6->sSer.eBit   = MC_SBIT_5;
    psAfn04f6->ucWaitP     = 123;
    psAfn04f6->ucWaitC     = 123;
    psAfn04f6->ucReTry     = 123;
    psAfn04f6->ucPeriod    = 123;
    psAfn04f6->ucN         = 3;
	psAfn04f6->bCasc = TRUE;
    
    memcpy(psAfn04f6->sOne[0].acRegionCode, "110000", MC_REGN_LEN);
    psAfn04f6->sOne[0].ulConAddr   = 12345678;
    psAfn04f6->sOne[0].sIp.eVersion = MC_IP_V4;
    psAfn04f6->sOne[0].sIp.ip[0]  = 192;
    psAfn04f6->sOne[0].sIp.ip[1]  = 168;
    psAfn04f6->sOne[0].sIp.ip[2]  = 1;
    psAfn04f6->sOne[0].sIp.ip[3]  = 1;
	
    psAfn04f6->sOne[0].usPort   = 1; 

	memcpy(psAfn04f6->sOne[1].acRegionCode, "112233", MC_REGN_LEN);
    psAfn04f6->sOne[1].ulConAddr   = 8765321;
    psAfn04f6->sOne[1].sIp.eVersion = MC_IP_V4;
    psAfn04f6->sOne[1].sIp.ip[0]  = 192;
    psAfn04f6->sOne[1].sIp.ip[1]  = 168;
    psAfn04f6->sOne[1].sIp.ip[2]  = 1;
    psAfn04f6->sOne[1].sIp.ip[3]  = 2;
	
    psAfn04f6->sOne[1].usPort   = 2; 

	memcpy(psAfn04f6->sOne[2].acRegionCode, "223344", MC_REGN_LEN);
    psAfn04f6->sOne[2].ulConAddr   = 121;
    psAfn04f6->sOne[2].sIp.eVersion = MC_IP_V4;
    psAfn04f6->sOne[2].sIp.ip[0]  = 192;
    psAfn04f6->sOne[2].sIp.ip[1]  = 168;
    psAfn04f6->sOne[2].sIp.ip[2]  = 1;
    psAfn04f6->sOne[2].sIp.ip[3]  = 4;
	
    psAfn04f6->sOne[2].usPort   = 4; 
	SetPreAfn04F6(psAfn04f6, TRUE, FALSE);


	// set afn 04 F7
	sMcAfn04f7 sAfn04F7;
	sAfn04F7.ucPort = 1;
	sAfn04F7.sMainIp.eVersion = MC_IP_V4;
	sAfn04F7.sMainIp.ip[0] = 192;
	sAfn04F7.sMainIp.ip[1] = 168;
	sAfn04F7.sMainIp.ip[2] = 0;
	sAfn04F7.sMainIp.ip[3] = 1;

	sAfn04F7.sBackIp.eVersion = MC_IP_V4;
	sAfn04F7.sBackIp.ip[0] = 192;
	sAfn04F7.sBackIp.ip[1] = 168;
	sAfn04F7.sBackIp.ip[2] = 0;
	sAfn04F7.sBackIp.ip[3] = 2;
	
	sAfn04F7.usBackPort = 6666;
	sAfn04F7.usMainPort = 7777;
	
	memset(sAfn04F7.ucAPN, 0, 16);
	memcpy(sAfn04F7.ucAPN, "apn", 3);

	memset(sAfn04F7.ucUsr, 0, 32);
	memcpy(sAfn04F7.ucUsr, "admin", 5);

	memset(sAfn04F7.ucPwd, 0, 32);
	memcpy(sAfn04F7.ucPwd, "admin", 5);
	
	SetPreAfn04F7(&sAfn04F7, TRUE, FALSE);
	

	// set afn 04 f9
	sMcAfn04f9 sAfn04F9;
	sAfn04F9.ucNeed = 3;
	sAfn04F9.ucImpt = 1;
	sAfn04F9.usImpRecNum = 255;
	sAfn04F9.usNmlRecNum = 255;
	sAfn04F9.aImpt[0] = MC_ERC_1_RESET;
	sAfn04F9.aNeed[0] = MC_ERC_1_RESET;
	sAfn04F9.aNeed[1] = MC_ERC_2_DATA_CLEAR;
	sAfn04F9.aNeed[2] = MC_ERC_3_SOFT_CHANGE;
	SetPreAfn04F9(&sAfn04F9, TRUE, FALSE);
	
	// set afn 04 f10
	sMcAfn04f10 sAfn04f10;
	for(i = 0; i < 8; i++)
	{
		sAfn04f10.bIn[i] = TRUE;
		sAfn04f10.bOn[i] = TRUE;
	}
	
	SetPreAfn04F10(&sAfn04f10, TRUE, FALSE);


	// set afn04 F17
	sMcAfn04f17 sAfn04F17;
	sAfn04F17.ucDownPort   = 1;
	sAfn04F17.usListenPort = 1;
	sAfn04F17.eUpPara      = MC_TUPP_SER;
	
	// sUpAddr
	sAfn04F17.sUpAddr.ucMstAddress = 1;
	sAfn04F17.sUpAddr.bTeam = FALSE;
	sAfn04F17.sUpAddr.ulConAddress = 2;
	memcpy(sAfn04F17.sUpAddr.acRegionCode, "110000", MC_REGN_LEN);
	
	// ucUpProto
	sAfn04F17.ucUpProto = MC_TML_UP_PROTO;
	
	// sUpIp
	sAfn04F17.sUpIp.eVersion = MC_IP_V4;
	sAfn04F17.sUpIp.ip[0]  = 192;
	sAfn04F17.sUpIp.ip[1]  = 168;
	sAfn04F17.sUpIp.ip[2]  = 1;
	sAfn04F17.sUpIp.ip[3]  = 2;
	
	// sUpMask
	sAfn04F17.sUpMask.eVersion = MC_IP_V4;
	sAfn04F17.sUpMask.ip[0]  = 255;
	sAfn04F17.sUpMask.ip[1]  = 255;
	sAfn04F17.sUpMask.ip[2]  = 255;
	sAfn04F17.sUpMask.ip[3]  = 0;
	
	// sGateIp
	sAfn04F17.sGateIp.eVersion = MC_IP_V4;
	sAfn04F17.sGateIp.ip[0]  = 192;
	sAfn04F17.sGateIp.ip[1]  = 168;
	sAfn04F17.sGateIp.ip[2]  = 1;
	sAfn04F17.sGateIp.ip[3]  = 1;
	
	// eDelegate
	sAfn04F17.eDelegate  = MC_DELG_HTTP;
	
	// sDelgIp
	sAfn04F17.sDelgIp.eVersion = MC_IP_V4;
	sAfn04F17.sDelgIp.ip[0]  = 192;
	sAfn04F17.sDelgIp.ip[1]  = 168;
	sAfn04F17.sDelgIp.ip[2]  = 1;
	sAfn04F17.sDelgIp.ip[3]  = 2;
	
	// usDelgPort
	sAfn04F17.usDelgPort  = 123;
	sAfn04F17.eDelgLink   = MC_DELK_USRPWD;
	
	sAfn04F17.bDlegUsr  = TRUE;
	sAfn04F17.ucDlegUsrLen  = 16;
	memcpy(sAfn04F17.ucDlegUsr, "1234567890abcdef", 16);
	
	
	sAfn04F17.bDlegPwd  = TRUE;
	sAfn04F17.ucDlegPwdLen  = 16;
	memcpy(sAfn04F17.ucDlegPwd, "1234567890abcdef", 16);
	
	sAfn04F17.ucPermitDelayM  = 123;
	sAfn04F17.ucReSendTimes   = 3;
	sAfn04F17.ucHeartBeat     = 1;
	sAfn04F17.usWaitTimeoutS  = 1234;
	sAfn04F17.bPermitRt       = TRUE;
	sAfn04F17.bPermitEv       = TRUE;
	sAfn04F17.bPermitTk       = TRUE;
	
	
	
	
	SetPreAfn04F17(&sAfn04F17, TRUE, FALSE);




	// set Afn04 F25 F33
	sMcAfn04f25 sAfn04f25;
	sAfn04f25.usID = 0;
	sAfn04f25.ucPort = 1;
	memset(sAfn04f25.ucAddr,0, 16);
	memcpy(sAfn04f25.ucAddr, "1", 1);
	 
	sAfn04f25.eAcsProto = MC_ACS_PROT_GBNX_32;
	memcpy(sAfn04f25.ucPwd, "123456", 6);

	sAfn04f25.eAcsPort = MC_ACS_PORT_SER;
	sAfn04f25.uPortPara.sSer.eBaud  = MC_BAUD_9600;
	sAfn04f25.uPortPara.sSer.bStop1  = TRUE;
	sAfn04f25.uPortPara.sSer.bCheck  = TRUE;
	sAfn04f25.uPortPara.sSer.bOdd  = TRUE;
	sAfn04f25.uPortPara.sSer.eBit  = MC_SBIT_6;

	sAfn04f25.usAcsPort = 1;
	sAfn04f25.sAccess.eVersion = MC_IP_V4;
	sAfn04f25.sAccess.ip[0] = 192;
	sAfn04f25.sAccess.ip[1] = 168;
	sAfn04f25.sAccess.ip[2] = 1;
	sAfn04f25.sAccess.ip[3] = 1;
	SetPreAfn04F25(&sAfn04f25, TRUE, FALSE);
	SetPreAfn04F25(&sAfn04f25, FALSE, FALSE);
	SetPreAfn04F33(&sAfn04f25, TRUE, FALSE);
	SetPreAfn04F33(&sAfn04f25, FALSE, FALSE);

	// set afn04 f26
	sMcAfn04f26 sAfn04f26;
	sAfn04f26.sDigit.ucDecimal = 1;
	sAfn04f26.sDigit.ucInteger = 4;
	sAfn04f26.fI = 123.456f;
	sAfn04f26.fU = 123.4f;
	sAfn04f26.usTimesU = 1;
	sAfn04f26.usTimesI = 1;
	sAfn04f26.sLinkWay.eLink = MC_LINK_P3_L3;
	sAfn04f26.sLinkWay.ePhase = MC_PHASE_A;
	SetPreAfn04F26(&sAfn04f26, TRUE, FALSE);

	// set afn04 f27
	sMcAfn04f27 sAfn04f27;
	sAfn04f27.ucTimeLossV = 1;
	sAfn04f27.fDropV = 123.4f;
	sAfn04f27.sOverV.fFactor = 12.34f;
	sAfn04f27.sOverV.fUpUp   = 999.9f;
	sAfn04f27.sOverV.ucTime = 1;

	sAfn04f27.sLossV.fDownDown = 123.4f;
	sAfn04f27.sLossV.fFactor = 12.34f;
	sAfn04f27.sLossV.ucTime = 2;

	sAfn04f27.sOverI.fUpUp = 123.456f;
	sAfn04f27.sOverI.fFactor = 45.67f;
	sAfn04f27.sOverI.ucTime = 3;

	sAfn04f27.sSuperI.fUp = 456.123f;
	sAfn04f27.sSuperI.fFactor = 77.88f;
	sAfn04f27.sSuperI.ucTime = 4;

	sAfn04f27.sZeroI.fUp = 123.456f;
	sAfn04f27.sZeroI.fFactor = 78.91f;
	sAfn04f27.sZeroI.ucTime = 6;

	sAfn04f27.sUblV.fLimit = 12.3456f;
	sAfn04f27.sUblV.fFactor = 11.22f;
	sAfn04f27.sUblV.ucTime = 7;

	sAfn04f27.sUblI.fFactor = 22.33f;
	sAfn04f27.sUblI.fLimit = 34.5678f;
	sAfn04f27.sUblI.ucTime = 8;
	
	SetPreAfn04F27(&sAfn04f27, TRUE, FALSE);
	
	// set afn 04 f28
	sMcAfn04F28 sAfn04F28;
	sAfn04F28.fPara1 = 12.34f;
	sAfn04F28.fPara2 = 12.34f;
	sAfn04F28.fWarning = 99.99f;
	SetPreAfn04F28(&sAfn04F28, TRUE, FALSE);
	
	
	// set afn04 f29
	sMcAfn04F29 sAfn04F29;
	sAfn04F29.sVa.fTotal = 12.34f;
	sAfn04F29.sVa.fOdd   = 12.34f;
	sAfn04F29.sVa.fEven  = 12.34f;

	sAfn04F29.sVb.fTotal = 12.34f;
	sAfn04F29.sVb.fOdd   = 12.34f;
	sAfn04F29.sVb.fEven  = 12.34f;


	sAfn04F29.sVc.fTotal = 12.34f;
	sAfn04F29.sVc.fOdd   = 12.34f;
	sAfn04F29.sVc.fEven  = 12.34f;

	sAfn04F29.sIa.fTotal = 12.34f;
	sAfn04F29.sIa.fOdd   = 12.34f;
	sAfn04F29.sIa.fEven  = 12.34f;
	
	sAfn04F29.sIb.fTotal = 12.34f;
	sAfn04F29.sIb.fOdd   = 12.34f;
	sAfn04F29.sIb.fEven  = 12.34f;
	
	
	sAfn04F29.sIc.fTotal = 12.34f;
	sAfn04F29.sIc.fOdd   = 12.34f;
	sAfn04F29.sIc.fEven  = 12.34f;
	SetPreAfn04F29(&sAfn04F29, TRUE, FALSE);

	// set afn 04 f 30
	sMcAfn04f30 sAfn04F30;
	sAfn04F30.fLong  = 12.34f;
	sAfn04F30.fShort = 12.34f;
	SetPreAfn04F30(&sAfn04F30, TRUE, FALSE);

	

	// set AFN04 F34
	sMcAfn04f34 sAfn04f34;
	sAfn04f34.eType = MC_NELC_TEMP;
	sAfn04f34.sUp.ePrec = MC_PREC_P0;
	sAfn04f34.sUp.dValue = -100;
	
	sAfn04f34.sDown.ePrec = MC_PREC_P0;
	sAfn04f34.sDown.dValue = 100;
	
	SetPreAfn04F34(&sAfn04f34, TRUE, FALSE);
	SetPreAfn04F34(&sAfn04f34, FALSE, FALSE);

	// set AFN04 F34
	sMcAfn04f35 sAfn04f35;
	sAfn04f35.eType = MC_NELC_TEMP;
	sAfn04f35.sUp.ePrec = MC_PREC_P0;
	sAfn04f35.sUp.dValue = -100;
	
	sAfn04f35.sDown.ePrec = MC_PREC_P0;
	sAfn04f35.sDown.dValue = 100;
	
	SetPreAfn04F35(&sAfn04f35, TRUE, FALSE);
	SetPreAfn04F35(&sAfn04f35, FALSE, FALSE);


	// set afn04 f49
	
	memset(buf, 0, BUF_LEN);
	sMcAfn04f49 *psAfn04f49;
	psAfn04f49 = (sMcAfn04f49*)buf;
	psAfn04f49->sTimeFrez.ucYY = 14;
	psAfn04f49->sTimeFrez.ucMM = 1;
	psAfn04f49->sTimeFrez.ucDD = 1;
	psAfn04f49->sTimeFrez.ucWW = 3;
	psAfn04f49->sTimeFrez.ucHH = 11;
	psAfn04f49->sTimeFrez.ucmm = 11;
	psAfn04f49->sTimeFrez.ucss = 11;

	psAfn04f49->sTimeRprt.ucYY = 14;
	psAfn04f49->sTimeRprt.ucMM = 1;
	psAfn04f49->sTimeRprt.ucDD = 1;
	psAfn04f49->sTimeRprt.ucWW = 3;
	psAfn04f49->sTimeRprt.ucHH = 11;
	psAfn04f49->sTimeRprt.ucmm = 11;
	psAfn04f49->sTimeRprt.ucss = 11;
	
	psAfn04f49->sFreez.usPeriod = 5;
	psAfn04f49->sFreez.eUnit = MC_PUNT_MIN;
	psAfn04f49->sFreez.ucTimes = 0;
	
	psAfn04f49->ucPeriodRpt = 5;
	psAfn04f49->eUnitRpt = MC_PUNT_MIN;
	
	psAfn04f49->uCmdPnNum = 2;
	psAfn04f49->sCmdPn[0].eCmd = MCMD_AFN_D_F57_VOLT_A;
	psAfn04f49->sCmdPn[0].usPn  = 1;
	
	psAfn04f49->sCmdPn[1].eCmd = MCMD_AFN_D_F65_ELEC_A;
	psAfn04f49->sCmdPn[1].usPn  = 1;


	SetPreAfn04F49(psAfn04f49, TRUE, FALSE);



	// 设置地址消息
	sMcAddress sAddr;
	
	memcpy(	sAddr.acRegionCode, "110000", 6);
	sAddr.bTeam = FALSE;
	sAddr.ulConAddress = 1;
	sAddr.ucMstAddress  = 1;
	SetPreAddress(&sAddr, FALSE, FALSE);
	SetPreAddress(&sAddr, TRUE, FALSE);


	// pw
	SetPrePw("0123456789ABCDEF", TRUE);
	SetPrePw("0123456789ABCDEF", FALSE);
	
	// pn
	// master
	ausPn[0] = 1;
	ausPn[1] = 2;
	SetPrePn(CMD_AFN_4_F25_MP_BASE_CFG, MT_ROLE_MASTER, ausPn, 2, FALSE);

	UINT8 ucNum = 0;
	GetPrePn(CMD_AFN_4_F25_MP_BASE_CFG, MT_ROLE_MASTER, ausPn, &ucNum);



}

// 写预配置 主站 AFN04 F1   bReWrite 覆盖原有值
void CNxConfig::SetMstPreAfn04F1(sMtAfn04F1 *psCfg, BOOL bReWrite)
{
	if(psCfg == NULL)
	{
		return;
	}

	CRegistry reg;
	CString   strAfn04F1 = "afn04f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	reg.Open(m_mstPreName);
	if(reg.bKeyExists(strAfn04F1, NULL) == FALSE)
	{
		reg.CreateKey(strAfn04F1);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}

		reg.Open(strAfn04F1);
	}
	
	CString   ucRTS            = "ucRTS";             // 终端数传机延时时间RTS
	CString   ucRTM            = "ucRTM";             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   ucReSendTimes    = "ucReSendTimes";     // 重发次数 (0~3)   0 表示不允许重发
	CString   ucHeartBeat      = "ucHeartBeat";       // 心跳周期
    CString   usTmWaitTimeoutS = "usTmWaitTimeoutS";  // 集中器等待从动站响应的超时时间 秒数 0~4095
    CString   bAutoReportAsk_1 = "bAutoReportAsk_1";  // 允许自动上报1类数据，同时需要主站确认
    CString   bAutoReportAsk_2 = "bAutoReportAsk_2";  // 允许自动上报2类数据，同时需要主站确认
    CString   bAutoReportAsk_3 = "bAutoReportAsk_3";  // 允许自动上报3类数据，同时需要主站确认


	reg.Write(ucRTS,psCfg->ucRTS);
	reg.Write(ucRTM,psCfg->ucRTM);
	reg.Write(ucReSendTimes,psCfg->ucReSendTimes);
	reg.Write(ucHeartBeat,psCfg->ucHeartBeat);
	reg.Write(usTmWaitTimeoutS,psCfg->usTmWaitTimeoutS);
	reg.Write(bAutoReportAsk_1,(psCfg->bAutoReportAsk_1 == TRUE) ? STR_TRUE:STR_FALSE);
	reg.Write(bAutoReportAsk_2,(psCfg->bAutoReportAsk_2 == TRUE) ? STR_TRUE:STR_FALSE);
	reg.Write(bAutoReportAsk_3,(psCfg->bAutoReportAsk_3 == TRUE) ? STR_TRUE:STR_FALSE);

}

// 读预配置 主站 AFN04 F1
void CNxConfig::GetMstPreAfn04F1(sMtAfn04F1 *psCfg)
{
	if(psCfg == NULL)
	{
		return;
	}
	

	CString   ucRTS            = "ucRTS";             // 终端数传机延时时间RTS
	CString   ucRTM            = "ucRTM";             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   ucReSendTimes    = "ucReSendTimes";     // 重发次数 (0~3)   0 表示不允许重发
	CString   ucHeartBeat      = "ucHeartBeat";       // 心跳周期
    CString   usTmWaitTimeoutS = "usTmWaitTimeoutS";  // 集中器等待从动站响应的超时时间 秒数 0~4095
    CString   bAutoReportAsk_1 = "bAutoReportAsk_1";  // 允许自动上报1类数据，同时需要主站确认
    CString   bAutoReportAsk_2 = "bAutoReportAsk_2";  // 允许自动上报2类数据，同时需要主站确认
    CString   bAutoReportAsk_3 = "bAutoReportAsk_3";  // 允许自动上报3类数据，同时需要主站确认

	
	CRegistry reg;
	CString   strAfn04F1 = "afn04f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	reg.Open(m_mstPreName);
	reg.Open(strAfn04F1);

	// 读取数据
    int       v_ucRTS;             // 终端数传机延时时间RTS
	int       v_ucRTM;             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	int       v_ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
	int       v_ucHeartBeat;       // 心跳周期
    int       v_usTmWaitTimeoutS;  // 集中器等待从动站响应的超时时间 秒数 0~4095
    CString   v_bAutoReportAsk_1;  // 允许自动上报1类数据，同时需要主站确认
    CString   v_bAutoReportAsk_2;  // 允许自动上报2类数据，同时需要主站确认
    CString   v_bAutoReportAsk_3;  // 允许自动上报3类数据，同时需要主站确认
	
	reg.Read(ucRTS, &v_ucRTS);
	reg.Read(ucRTM, &v_ucRTM);
	reg.Read(ucReSendTimes, &v_ucReSendTimes);
	reg.Read(ucHeartBeat, &v_ucHeartBeat);
	reg.Read(usTmWaitTimeoutS, &v_usTmWaitTimeoutS);
	reg.Read(bAutoReportAsk_1, &v_bAutoReportAsk_1);
	reg.Read(bAutoReportAsk_2, &v_bAutoReportAsk_2);
	reg.Read(bAutoReportAsk_3, &v_bAutoReportAsk_3);
	
	psCfg->ucRTS = v_ucRTS;
	psCfg->ucRTM = v_ucRTM;
	psCfg->ucReSendTimes = v_ucReSendTimes;
	psCfg->ucHeartBeat   = v_ucHeartBeat;
	psCfg->usTmWaitTimeoutS = v_usTmWaitTimeoutS;
	psCfg->bAutoReportAsk_1 = v_bAutoReportAsk_1 == STR_TRUE ? TRUE : FALSE;
	psCfg->bAutoReportAsk_2 = v_bAutoReportAsk_2 == STR_TRUE ? TRUE : FALSE;
	psCfg->bAutoReportAsk_3 = v_bAutoReportAsk_3 == STR_TRUE ? TRUE : FALSE;
	
}

// 写预配置 主站 AFN04 F1   bReWrite 覆盖原有值
void CNxConfig::SetTmlPreAfn04F1(sMtAfn04F1 *psCfg, BOOL bReWrite)
{
	if(psCfg == NULL)
	{
		return;
	}

	CRegistry reg;
	CString   strAfn04F1 = "afn04f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	reg.Open(m_tmlPreName);
	if(reg.bKeyExists(strAfn04F1, NULL) == FALSE)
	{
		reg.CreateKey(strAfn04F1);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}

		reg.Open(strAfn04F1);
	}
	
	CString   ucRTS            = "ucRTS";             // 终端数传机延时时间RTS
	CString   ucRTM            = "ucRTM";             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   ucReSendTimes    = "ucReSendTimes";     // 重发次数 (0~3)   0 表示不允许重发
	CString   ucHeartBeat      = "ucHeartBeat";       // 心跳周期
    CString   usTmWaitTimeoutS = "usTmWaitTimeoutS";  // 集中器等待从动站响应的超时时间 秒数 0~4095
    CString   bAutoReportAsk_1 = "bAutoReportAsk_1";  // 允许自动上报1类数据，同时需要主站确认
    CString   bAutoReportAsk_2 = "bAutoReportAsk_2";  // 允许自动上报2类数据，同时需要主站确认
    CString   bAutoReportAsk_3 = "bAutoReportAsk_3";  // 允许自动上报3类数据，同时需要主站确认


	reg.Write(ucRTS,psCfg->ucRTS);
	reg.Write(ucRTM,psCfg->ucRTM);
	reg.Write(ucReSendTimes,psCfg->ucReSendTimes);
	reg.Write(ucHeartBeat,psCfg->ucHeartBeat);
	reg.Write(usTmWaitTimeoutS,psCfg->usTmWaitTimeoutS);
	reg.Write(bAutoReportAsk_1,(psCfg->bAutoReportAsk_1 == TRUE) ? STR_TRUE:STR_FALSE);
	reg.Write(bAutoReportAsk_2,(psCfg->bAutoReportAsk_2 == TRUE) ? STR_TRUE:STR_FALSE);
	reg.Write(bAutoReportAsk_3,(psCfg->bAutoReportAsk_3 == TRUE) ? STR_TRUE:STR_FALSE);

}

// 读预配置 主站 AFN04 F1
void CNxConfig::GetTmlPreAfn04F1(sMtAfn04F1 *psCfg)
{
	if(psCfg == NULL)
	{
		return;
	}
	

	CString   ucRTS            = "ucRTS";             // 终端数传机延时时间RTS
	CString   ucRTM            = "ucRTM";             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   ucReSendTimes    = "ucReSendTimes";     // 重发次数 (0~3)   0 表示不允许重发
	CString   ucHeartBeat      = "ucHeartBeat";       // 心跳周期
    CString   usTmWaitTimeoutS = "usTmWaitTimeoutS";  // 集中器等待从动站响应的超时时间 秒数 0~4095
    CString   bAutoReportAsk_1 = "bAutoReportAsk_1";  // 允许自动上报1类数据，同时需要主站确认
    CString   bAutoReportAsk_2 = "bAutoReportAsk_2";  // 允许自动上报2类数据，同时需要主站确认
    CString   bAutoReportAsk_3 = "bAutoReportAsk_3";  // 允许自动上报3类数据，同时需要主站确认

	
	CRegistry reg;
	CString   strAfn04F1 = "afn04f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	reg.Open(m_tmlPreName);
	reg.Open(strAfn04F1);

	// 读取数据
    int       v_ucRTS;             // 终端数传机延时时间RTS
	int       v_ucRTM;             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	int       v_ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
	int       v_ucHeartBeat;       // 心跳周期
    int       v_usTmWaitTimeoutS;  // 集中器等待从动站响应的超时时间 秒数 0~4095
    CString   v_bAutoReportAsk_1;  // 允许自动上报1类数据，同时需要主站确认
    CString   v_bAutoReportAsk_2;  // 允许自动上报2类数据，同时需要主站确认
    CString   v_bAutoReportAsk_3;  // 允许自动上报3类数据，同时需要主站确认
	
	reg.Read(ucRTS, &v_ucRTS);
	reg.Read(ucRTM, &v_ucRTM);
	reg.Read(ucReSendTimes, &v_ucReSendTimes);
	reg.Read(ucHeartBeat, &v_ucHeartBeat);
	reg.Read(usTmWaitTimeoutS, &v_usTmWaitTimeoutS);
	reg.Read(bAutoReportAsk_1, &v_bAutoReportAsk_1);
	reg.Read(bAutoReportAsk_2, &v_bAutoReportAsk_2);
	reg.Read(bAutoReportAsk_3, &v_bAutoReportAsk_3);
	
	psCfg->ucRTS = v_ucRTS;
	psCfg->ucRTM = v_ucRTM;
	psCfg->ucReSendTimes = v_ucReSendTimes;
	psCfg->ucHeartBeat   = v_ucHeartBeat;
	psCfg->usTmWaitTimeoutS = v_usTmWaitTimeoutS;
	psCfg->bAutoReportAsk_1 = v_bAutoReportAsk_1 == STR_TRUE ? TRUE : FALSE;
	psCfg->bAutoReportAsk_2 = v_bAutoReportAsk_2 == STR_TRUE ? TRUE : FALSE;
	psCfg->bAutoReportAsk_3 = v_bAutoReportAsk_3 == STR_TRUE ? TRUE : FALSE;
	
}

// 将地址预配信息写入注册表 bMaster true 作为主站时
void CNxConfig::SetPreAddress( sMcAddress *psAddr, BOOL bMaster /*= TRUE*/,  BOOL bReWrite)
{
	if(!psAddr)
	{
		return;
	}

	char buf[7] = {0};

	CRegistry reg;
	CString   strItem = "address";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);

	if(bMaster == TRUE)
	{
     	reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}

	if(reg.bKeyExists(strItem, NULL) == FALSE)
	{
		reg.CreateKey(strItem);
	}
	else
	{	
		if(bReWrite == FALSE)
		{
			return;
		}
		reg.Open(strItem);
	}



	CString  n_acRegionCode = "acRegionCode";         // 行政区划码(BCD)  如北京 1100   
	CString  n_ulTAddress   = "usTAddress";           // 终端或集中器地址  (BIN) A2 范围(1 ~ 65535)
	CString  n_bTeamAddr    = "bTeamAddr";            // 为true表示 ulTAddress 为组地址， 为 false 表示ulTAddress单地址
	CString  n_ucMAddress   = "ucMAddress";           // 主站地址	范围(0~127)

	CString  v_acRegionCode;      // 行政区划码(BCD)  如北京 1100   
	int   v_ulTAddress;           // 终端或集中器地址  (BIN) A2 范围(1 ~ 4294967295)
	CString  v_bTeamAddr;            // 为true表示 ulTAddress 为组地址， 为 false 表示ulTAddress单地址
	UINT8  v_ucMAddress;           // 主站地址	范围(0~127)
	
	memcpy(buf, psAddr->acRegionCode, 6);
	v_acRegionCode.Format("%s", buf) ;
	v_ulTAddress = psAddr->ulConAddress;
	v_ucMAddress = psAddr->ucMstAddress;
	v_bTeamAddr  = (psAddr->bTeam == TRUE) ? STR_TRUE:STR_FALSE;

	reg.Write(n_acRegionCode,_T(v_acRegionCode));
	reg.Write(n_ulTAddress,v_ulTAddress);
	reg.Write(n_bTeamAddr,v_bTeamAddr);
	reg.Write(n_ucMAddress,v_ucMAddress);

}


// 获取地址预配信息 bMaster true 作为主站时
void CNxConfig::GetPreAddress( sMcAddress *psAddr, BOOL bMaster /*= TRUE*/ )
{
	if(!psAddr)
	{
		return;

	}
	CRegistry reg;
	CString   strItem = "address";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	
	if(bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strItem, NULL) == TRUE)
	{
		reg.Open(strItem);
	}
	else
	{	
		return;
	}
	
	
	
	CString  n_acRegionCode = "acRegionCode";         // 行政区划码(BCD)  如北京 1100   
	CString  n_usTAddress   = "usTAddress";           // 终端或集中器地址  (BIN) A2 范围(1 ~ 4294967295)
	CString  n_bTeamAddr    = "bTeamAddr";            // 为true表示 ulTAddress 为组地址， 为 false 表示ulTAddress单地址
	CString  n_ucMAddress   = "ucMAddress";           // 主站地址	范围(0~127)
	
	CString  v_usRegionCode;      // 行政区划码(BCD)  如北京 1100   
	int   v_ulTAddress;           // 终端或集中器地址  (BIN) A2 范围(1 ~ 4294967295)
	CString  v_bTeamAddr;            // 为true表示 ulTAddress 为组地址， 为 false 表示ulTAddress单地址
	int  v_ucMAddress;           // 主站地址	范围(0~127)
	
	
	reg.Read(n_acRegionCode,&v_usRegionCode);
	reg.Read(n_usTAddress,&v_ulTAddress);
	reg.Read(n_bTeamAddr,&v_bTeamAddr);
	reg.Read(n_ucMAddress,&v_ucMAddress);
	
    memcpy(psAddr->acRegionCode, (LPCTSTR)v_usRegionCode, 6);
	psAddr->ulConAddress = v_ulTAddress;
	psAddr->bTeam = (v_bTeamAddr == STR_TRUE) ? TRUE:FALSE;
	psAddr->ucMstAddress = v_ucMAddress;
}



void CNxConfig::SetPrePw( CString pw, BOOL bMaster /*= TRUE*/ )
{
	CRegistry reg;
	CString   strItem = "pw";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	
	if(bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strItem, NULL) == FALSE)
	{
		reg.CreateKey(strItem);
	}
	else
	{	
		reg.Open(strItem);
	}
	
	reg.Write("pw",_T(pw));

}

void CNxConfig::GetPrePw( CString *pw, BOOL bMaster /*= TRUE*/ )
{
	CRegistry reg;
	CString   strItem = "pw";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	
	if(bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strItem, NULL) == FALSE)
	{
		;
	}
	else
	{	
		reg.Open(strItem);
	}


		reg.Read("pw",pw);
	
}






// gb31
void CNxConfig::SetPrePnStr31( eMcmd eCmd, eMcRole eRole,CString strValue, BOOL bReWrite /*= TRUE*/ )
{
	CRegistry reg;
	CString   strPn = "pn";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MC_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	
	
	if(reg.bKeyExists(strPn, NULL) == FALSE)
	{
		reg.CreateKey(strPn);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}
		reg.Open(strPn);
	}
	
	// name
	CString strName;
	strName.Format("PN%04X", (UINT16)eCmd);
	reg.Write(strName,strValue);
}

// 3761
void CNxConfig::SetPrePnStr( eMtCmd eCmd, eMtRole eRole,CString strValue, BOOL bReWrite /*= TRUE*/ )
{
	CRegistry reg;
	CString   strPn = "pn";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MT_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	

	if(reg.bKeyExists(strPn, NULL) == FALSE)
	{
		reg.CreateKey(strPn);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}
		reg.Open(strPn);
	}
	
	// name
	CString strName;
	strName.Format("PN%04X", (UINT16)eCmd);
	reg.Write(strName,strValue);
}


// 预设置pn
void CNxConfig::SetPrePn( eMtCmd eCmd, eMtRole eRole,UINT16 *pusPN, UINT8 ucNum, BOOL bReWrite /*= TRUE*/ )
{
	if(!pusPN)
	{
		return;
	}

	CRegistry reg;
	CString   strPn = "pn";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MT_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	

	
	if(reg.bKeyExists(strPn, NULL) == FALSE)
	{
		reg.CreateKey(strPn);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}
		reg.Open(strPn);
	}

	// name
	CString strName;
	CString strValue, strValueTmp;
	strName.Format("PN%04X", (UINT16)eCmd);

	// value
	int i = 0;
	for(i = 0; i < ucNum; i++)
	{
		strValueTmp.Format("%d,", (UINT16)pusPN[i]);
		strValue += strValueTmp;
	}

	reg.Write(strName,strValue);

}

void CNxConfig::GetPrePn31(eMcmd eCmd,  eMcRole eRole,UINT16 *pusPN, UINT8 *pucNum)
{
	if(!pusPN || !pucNum)
	{
		return;
	}
	
	CRegistry reg;
	CString   strPn = "pn";
	eMcDir    eDir;
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MT_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
		eDir = MC_DIR_S2M;
	}
	else
	{
		reg.Open(m_mstPreName);
		eDir = MC_DIR_M2S;
	}
	
	if(reg.bKeyExists(strPn, NULL) == TRUE)
	{
		reg.Open(strPn);
	}
	else
	{
		
		return;
	}
	
	// name
	CString strName;
	CString strValue, strValueTmp;
	strName.Format("PN%04X", (UINT16)eCmd);
	
	
	sMcmdInfor sCmdInfor;
	eMcErr eRet = eMcGetCmdInfor(eCmd,eDir, &sCmdInfor);
	if (MT_OK != eRet)
	{
		return;
	}
	
	if (sCmdInfor.ePn == MT_PN_P0)
	{
		pusPN[0] = 0;
		*pucNum  = 1;
		return;
	}
	
	// value
	reg.Read(strName,&strValue);
	
	int flag  = 0;
	int i = 0;
	
	while(strValue.GetLength() != 0 && flag != -1)
	{
		flag = strValue.Find(",", 0);
		if(-1 == flag)
		{
			strValueTmp = strValue;
		}
		else
		{
			strValueTmp = strValue.Left(flag);
			strValue = strValue.Right(strValue.GetLength() - flag -1);
		}
		
		pusPN[i++] = atoi(strValueTmp);
		
	}
	
	*pucNum = i;
	
}

void CNxConfig::GetPrePn( eMtCmd eCmd, eMtRole eRole,UINT16 *pusPN, UINT8 *pucNum )
{
	if(!pusPN || !pucNum)
	{
		return;
	}
	
	CRegistry reg;
	CString   strPn = "pn";
	eMtDir    eDir;
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MT_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
		eDir = MT_DIR_S2M;
	}
	else
	{
		reg.Open(m_mstPreName);
		eDir = MT_DIR_M2S;
	}
	
	if(reg.bKeyExists(strPn, NULL) == TRUE)
	{
	    reg.Open(strPn);
	}
	else
	{

     	return;
	}
	
	// name
	CString strName;
	CString strValue, strValueTmp;
	strName.Format("PN%04X", (UINT16)eCmd);


	sMtCmdInfor sCmdInfor;
	eMtErr eRet = eMtGetCmdInfor(eCmd,eDir, &sCmdInfor);
	if (MT_OK != eRet)
	{
		return;
	}
	
	if (sCmdInfor.ePn == MT_PN_P0)
	{
		pusPN[0] = 0;
		*pucNum  = 1;
		return;
	}
	
	// value
	reg.Read(strName,&strValue);
	
	int flag  = 0;
	int i = 0;
	
	while(strValue.GetLength() != 0 && flag != -1)
	{
		flag = strValue.Find(",", 0);
		if(-1 == flag)
		{
			strValueTmp = strValue;
		}
		else
		{
			strValueTmp = strValue.Left(flag);
		    strValue = strValue.Right(strValue.GetLength() - flag -1);
		}
		
		pusPN[i++] = atoi(strValueTmp);
	
	}

	*pucNum = i;

}

// 获得pn的预设值3761
void CNxConfig::GetPrePnStr31( eMcmd eCmd, eMcRole eRole,CString *pStr )
{
	if(!pStr)
	{
		return;
	}
	
	CRegistry reg;
	CString   strPn = "pn";
	eMcDir    eDir;
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MC_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	
	if(reg.bKeyExists(strPn, NULL) == TRUE)
	{
		reg.Open(strPn);
	}
	else
	{
		return;
	}
	
	// name
	CString strName;
	CString strValue, strValueTmp;
	strName.Format("PN%04X", (UINT16)eCmd);
	
	eDir = (eRole == MC_ROLE_CONTOR) ? MC_DIR_S2M : MC_DIR_M2S;
	
	sMcmdInfor sCmdInfor;
	eMcErr eRet = eMcGetCmdInfor(eCmd,eDir, &sCmdInfor);
	if (MC_OK != eRet)
	{
		return;
	}
	
	if (sCmdInfor.ePn == MC_PN_P0)
	{
		*pStr = "0:集中器";
		return;
	}
	
	// value
	reg.Read(strName,&strValue);
	*pStr = strValue;
	if (strValue == "")
	{
    	SetPrePnStr31( eCmd, eRole, "1", TRUE);
		*pStr = "1";
	}
	
}



// 获得pn的预设值3761
void CNxConfig::GetPrePnStr( eMtCmd eCmd, eMtRole eRole,CString *pStr )
{
	if(!pStr)
	{
		return;
	}
	
	CRegistry reg;
	CString   strPn = "pn";
	eMtDir    eDir;
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MT_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	
	if(reg.bKeyExists(strPn, NULL) == TRUE)
	{
		reg.Open(strPn);
	}
	else
	{
		return;
	}
	
	// name
	CString strName;
	CString strValue, strValueTmp;
	strName.Format("PN%04X", (UINT16)eCmd);
	
	eDir = (eRole == MT_ROLE_CONTOR) ? MT_DIR_S2M : MT_DIR_M2S;

	sMtCmdInfor sCmdInfor;
	eMtErr eRet = eMtGetCmdInfor(eCmd,eDir, &sCmdInfor);
	if (MT_OK != eRet)
	{
		return;
	}
	
	if (sCmdInfor.ePn == MT_PN_P0)
	{
		*pStr = "0:集中器";
		return;
	}



	// value
	reg.Read(strName,&strValue);
	*pStr = strValue;

	

}

/* 设置 数据*/
void CNxConfig::SetPreAfn00F1( sMcAfn00F1 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(!pData)
	{
		return;
	}

	// 打开注册表中对应的键位置
	CRegistry reg;
	CString   strAfnFn = "afn00f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(bMaster == FALSE)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	
	
	if(reg.bKeyExists(strAfnFn, NULL) == FALSE)
	{
		reg.CreateKey(strAfnFn);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}
		reg.Open(strAfnFn);
	}



	// name
	//CString strValue;
	CString strName;
	
	strName.Format("%s", "eMcResCode");
	//strValue.Format("%d", *pData);

	reg.Write(strName, *pData);
}

void CNxConfig::GetPreAfn00F1( sMcAfn00F1 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(!pData)
	{
		return;
	}
	
	// 打开注册表中对应的键位置
	CRegistry reg;
	CString   strAfnFn = "afn00f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(bMaster == FALSE)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	
	if(reg.bKeyExists(strAfnFn, NULL) == TRUE)
	{
		reg.Open(strAfnFn);
		CString strName;	
		int nResCode = 0;
    	strName.Format("%s", "eMcResCode");
		reg.Read(strName, &nResCode);
		*pData = (eMcResCode)nResCode;
	}
}

BOOL CNxConfig::SetPreAfn04F1( sMcAfn04f1 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strAfn04F1 = "afn04f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
    	reg.Open(m_mstPreName);
	}
	else
	{
	    reg.Open(m_tmlPreName);
	}

	if(reg.bKeyExists(strAfn04F1, NULL) == FALSE)
	{
		reg.CreateKey(strAfn04F1);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strAfn04F1);
	}
	

	reg.Write("ucPermitDelayM", pData->ucPermitDelayM);
	reg.Write("ucReSendTimes", pData->ucReSendTimes);
	reg.Write("ucHeartBeat",    pData->ucHeartBeat);
	reg.Write("usWaitTimeoutS",pData->usWaitTimeoutS);
	reg.Write("bPermitRt",pData->bPermitRt);
	reg.Write("bPermitTk",pData->bPermitTk);
	reg.Write("bPermitEv",pData->bPermitEv);

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F1( sMcAfn04f1 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strAfn04F1 = "afn04f1";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strAfn04F1, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strAfn04F1);
	}
	
	int nValue;
	reg.Read("ucPermitDelayM", &nValue);
	pData->ucPermitDelayM = nValue;

	reg.Read("ucReSendTimes", &nValue);
	pData->ucReSendTimes = nValue;

	reg.Read("ucHeartBeat",    &nValue);
	pData->ucHeartBeat = nValue;

	reg.Read("usWaitTimeoutS",&nValue);
	pData->usWaitTimeoutS = nValue;
	reg.Read("bPermitRt",&pData->bPermitRt);
	reg.Read("bPermitTk",&pData->bPermitTk);
	reg.Read("bPermitEv",&pData->bPermitEv);
	return TRUE;
}

// 只支持设置一个子项
BOOL CNxConfig::SetPreAfn04F2( sMcAfn04f2 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	int i = 0;
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f2";
	
	reg.SetRootKey(HKEY_LOCAL_MACHINE);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	

	CString str_ucN        = "ucN";
	CString str_ucID       = "ucID";
	CString str_bValid     = "bValid";
	CString str_ucNoNum    = "ucNoNum";
	CString str_sCmdPn_cmd   = "sCmdPn[0].eCmd";
	CString str_sCmdPn_usPn   = "sCmdPn[0].usPn";
	CString str_sMainIp    = "sMainIp";
	CString str_sBackIp    = "sBackIp";
	CString str_usMainPort = "usMainPort";
	CString str_usBackPort = "usBackPort";
	CString str_ucascAPN   = "ucascAPN";
	CString str_usr        = "usr";
	CString str_pwd        = "pwd";
	CString str_tmp;
	CString str_key;
	CString str_ip;
	CString str_chars;
	
    reg.Write("ucN", pData->ucN);
	
	for (i = 0; i < pData->ucN; i++)
	{
		str_tmp.Format("%d", i);
		
		// ucID
		str_key = str_ucID+str_tmp;
		reg.Write(str_key, pData->sOne[i].ucID);
		
		// bValid
		str_key = str_bValid + str_tmp;
		reg.Write(str_key, pData->sOne[i].bValid);
		
		// ucNoNum
		str_key = str_ucNoNum + str_tmp;
		reg.Write(str_key, pData->sOne[i].ucNoNum);
		
		// sCmdPn[0]
		str_key = str_sCmdPn_cmd + str_tmp;
		reg.Write(str_key, pData->sOne[i].sCmdPn[0].eCmd);

		str_key = str_sCmdPn_usPn + str_tmp;
		reg.Write(str_key, pData->sOne[i].sCmdPn[0].usPn);

		
		
		// mainIp
		str_key = str_sMainIp+str_tmp + "[0]";
		reg.Write(str_key, pData->sOne[i].sMainIP.ip[0]);
		
		str_key = str_sMainIp+str_tmp + "[1]";
		reg.Write(str_key, pData->sOne[i].sMainIP.ip[1]);
		
		str_key = str_sMainIp+str_tmp + "[2]";
		reg.Write(str_key, pData->sOne[i].sMainIP.ip[2]);
		
		str_key = str_sMainIp+str_tmp + "[3]";
		reg.Write(str_key, pData->sOne[i].sMainIP.ip[3]);
		
		// sBackIp
		str_key = str_sBackIp+str_tmp + "[0]";
		reg.Write(str_key, pData->sOne[i].sBackIP.ip[0]);
		
		str_key = str_sBackIp+str_tmp + "[1]";
		reg.Write(str_key, pData->sOne[i].sBackIP.ip[1]);
		
		str_key = str_sBackIp+str_tmp + "[2]";
		reg.Write(str_key, pData->sOne[i].sBackIP.ip[2]);
		
		str_key = str_sBackIp+str_tmp + "[3]";
		reg.Write(str_key, pData->sOne[i].sBackIP.ip[3]);
		
		
		// usMainPort
		str_key = str_usMainPort + str_tmp;
		reg.Write(str_key, pData->sOne[i].usMainPort);
		
		// usBackPort
		str_key = str_usBackPort + str_tmp;
		reg.Write(str_key, pData->sOne[i].usBackPort);
		
		// ucascAPN
		char buf_apn[17] = {0};
		memcpy(buf_apn, pData->sOne[i].ucascAPN, 16);
		str_chars.Format("%s", buf_apn);
		str_key = str_ucascAPN + str_tmp;
		reg.Write(str_key, str_chars);
		
		// ucUsr
		char buf_usr[33] = {0};
		memcpy(buf_usr, pData->sOne[i].usr, 32);
		str_chars.Format("%s", buf_usr);
		str_key = str_usr + str_tmp;
		reg.Write(str_key, str_chars);
		
		// pwd
		char buf_pwd[33] = {0};
		memcpy(buf_pwd, pData->sOne[i].pwd, 32);
		str_chars.Format("%s", buf_pwd);
		str_key = str_pwd + str_tmp;
		reg.Write(str_key, str_chars);
		
	}


	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F2( sMcAfn04f2 *pData, BOOL bMaster /*= TRUE*/ )
{

	int i = 0;
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strAfn04F2 = "afn04f2";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strAfn04F2, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strAfn04F2);
	}

	CString str_ucN        = "ucN";
	CString str_ucID       = "ucID";
	CString str_bValid     = "bValid";
	CString str_ucNoNum    = "ucNoNum";
	CString str_sCmdPn_cmd   = "sCmdPn[0].eCmd";
	CString str_sCmdPn_usPn   = "sCmdPn[0].usPn";
	CString str_sMainIp    = "sMainIp";
	CString str_sBackIp    = "sBackIp";
	CString str_usMainPort = "usMainPort";
	CString str_usBackPort = "usBackPort";
	CString str_ucascAPN   = "ucascAPN";
	CString str_usr        = "usr";
	CString str_pwd        = "pwd";
	CString str_tmp;
	CString str_key;
	CString str_ip;
	CString str_chars;
	int N = 0;
    reg.Read(str_ucN, &N);
	pData->ucN = N;


	for (i = 0; i < pData->ucN; i++)
	{
		str_tmp.Format("%d", i);
		
		// ucID
		str_key = str_ucID+str_tmp;
		reg.Read(str_key, &N);
		pData->sOne[i].ucID = N;

		// bValid
		str_key = str_bValid + str_tmp;
		reg.Read(str_key, &(pData->sOne[i].bValid));

		// ucNoNum
		str_key = str_ucNoNum + str_tmp;
		reg.Read(str_key, &N);
		pData->sOne[i].ucNoNum = N;


		// sCmdPn[0]
		str_key = str_sCmdPn_cmd + str_tmp;
		reg.Read(str_key, &N);
		pData->sOne[i].sCmdPn[0].eCmd = (eMcmd)N;
		
		str_key = str_sCmdPn_usPn + str_tmp;
		reg.Read(str_key, &N);
		pData->sOne[i].sCmdPn[0].usPn = (UINT16)N;

		
		// mainIp
		str_key = str_sMainIp+str_tmp + "[0]";
		reg.Read(str_key, &N);
		pData->sOne[i].sMainIP.ip[0] = N;
		
		str_key = str_sMainIp+str_tmp + "[1]";
		reg.Read(str_key, &N);
		pData->sOne[i].sMainIP.ip[1] = N;
		
		str_key = str_sMainIp+str_tmp + "[2]";
		reg.Read(str_key, &N);
		pData->sOne[i].sMainIP.ip[2] = N;

	    str_key = str_sMainIp+str_tmp + "[3]";
		reg.Read(str_key, &N);
		pData->sOne[i].sMainIP.ip[3] = N;

		pData->sOne[i].sMainIP.eVersion = MC_IP_V4;
		// sBackIp
		str_key = str_sBackIp+str_tmp + "[0]";
		reg.Read(str_key, &N);
		pData->sOne[i].sBackIP.ip[0] = N;
		
		str_key = str_sBackIp+str_tmp + "[1]";
		reg.Read(str_key, &N);
		pData->sOne[i].sBackIP.ip[1] = N;
		
		str_key = str_sBackIp+str_tmp + "[2]";
		reg.Read(str_key, &N);
		pData->sOne[i].sBackIP.ip[2] = N;
		
		str_key = str_sBackIp+str_tmp + "[3]";
		reg.Read(str_key, &N);
		pData->sOne[i].sBackIP.ip[3] = N;

		pData->sOne[i].sBackIP.eVersion = MC_IP_V4; 

		// usMainPort
		str_key = str_usMainPort + str_tmp;
		reg.Read(str_key, &N);
		pData->sOne[i].usMainPort = N;

		// usBackPort
		str_key = str_usBackPort + str_tmp;
		reg.Read(str_key, &N);
		pData->sOne[i].usBackPort = N;
		
		// ucascAPN
		str_key = str_ucascAPN + str_tmp;
		reg.Read(str_key, &str_chars);
		memset(pData->sOne[i].ucascAPN, 0, 16);
		memcpy(pData->sOne[i].ucascAPN, str_chars.GetBuffer(str_chars.GetLength()), str_chars.GetLength());
		str_chars.ReleaseBuffer();
		// usr
		str_key = str_usr + str_tmp;
		reg.Read(str_key, &str_chars);
		memset(pData->sOne[i].usr, 0, 32);
		memcpy(pData->sOne[i].usr, str_chars.GetBuffer(str_chars.GetLength()), str_chars.GetLength());
		str_chars.ReleaseBuffer();
		
		// pwd
		str_key = str_pwd + str_tmp;
		reg.Read(str_key, &str_chars);
		memset(pData->sOne[i].pwd, 0, 32);
		memcpy(pData->sOne[i].pwd, str_chars.GetBuffer(str_chars.GetLength()), str_chars.GetLength());
		str_chars.ReleaseBuffer();
		
	}

	




	return TRUE;
}



// 统一设置一个浮点数的情况数据
BOOL CNxConfig::SetPreAfn0DFS( CString *pData, eMcmd eCmd, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey;

	strKey.Format("afn0df%d", eCmd&0xFF);
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
    reg.Write("fvalue", *pData);



	return TRUE;
}

// 统一获得一个浮点数据情况的数据
BOOL CNxConfig::GetPreAfn0DFS( CString *pData, eMcmd eCmd, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey;	
	CString   strValue;
	strKey.Format("afn0df%d", eCmd&0xFF);
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		
		reg.Open(strKey);
	}
	
	reg.Read("fvalue", &strValue);
	*pData = strValue;
	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F34( sMcAfn04f34 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f34";

	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	CString str_eType          = "eType";
	CString str_sUp_ePrec      = "sUp_ePrec";
	CString str_sUp_dValue     = "sUp_dValue";
	CString str_sDown_ePrec    = "sDown_ePrec";
	CString str_sDown_dValue   = "sDown_dValue";
	CString str_double         = "";

	
    reg.Write(str_eType, pData->eType);
	reg.Write(str_sUp_ePrec, pData->sUp.ePrec);
	reg.Write(str_sDown_ePrec, pData->sDown.ePrec);

	str_double.Format("%f", pData->sUp.dValue);
	reg.Write(str_sUp_dValue, str_double);
	
	str_double.Format("%f", pData->sDown.dValue);
	reg.Write(str_sDown_dValue, str_double);

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F34( sMcAfn04f34 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f34";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	
	CString str_eType          = "eType";
	CString str_sUp_ePrec      = "sUp_ePrec";
	CString str_sUp_dValue     = "sUp_dValue";
	CString str_sDown_ePrec    = "sDown_ePrec";
	CString str_sDown_dValue   = "sDown_dValue";
	CString str_double         = "";
	int nValue = 0;

	reg.Read(str_eType, &nValue);
	pData->eType = (eMcNElcType)nValue;

	reg.Read(str_sUp_ePrec, &nValue);
	pData->sUp.ePrec = (eMcPrecise)nValue;

	reg.Read(str_sDown_ePrec, &nValue);
	pData->sDown.ePrec = (eMcPrecise)nValue;

	//str_double.Format("%f", pData->sUp.dValue);
	reg.Read(str_sUp_dValue, &str_double);
	
	pData->sUp.dValue = atof(str_double.GetBuffer(str_double.GetLength()));
	str_double.ReleaseBuffer();

	reg.Read(str_sDown_dValue, &str_double);
	pData->sDown.dValue = atof(str_double.GetBuffer(str_double.GetLength()));
	str_double.ReleaseBuffer();

	return TRUE;

}



BOOL CNxConfig::SetPreAfn04F35( sMcAfn04f35 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f35";

	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	CString str_eType          = "eType";
	CString str_sUp_ePrec      = "sUp_ePrec";
	CString str_sUp_dValue     = "sUp_dValue";
	CString str_sDown_ePrec    = "sDown_ePrec";
	CString str_sDown_dValue   = "sDown_dValue";
	CString str_double         = "";

	
    reg.Write(str_eType, pData->eType);
	reg.Write(str_sUp_ePrec, pData->sUp.ePrec);
	reg.Write(str_sDown_ePrec, pData->sDown.ePrec);

	str_double.Format("%f", pData->sUp.dValue);
	reg.Write(str_sUp_dValue, str_double);
	
	str_double.Format("%f", pData->sDown.dValue);
	reg.Write(str_sDown_dValue, str_double);

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F35( sMcAfn04f35 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f35";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	
	CString str_eType          = "eType";
	CString str_sUp_ePrec      = "sUp_ePrec";
	CString str_sUp_dValue     = "sUp_dValue";
	CString str_sDown_ePrec    = "sDown_ePrec";
	CString str_sDown_dValue   = "sDown_dValue";
	CString str_double         = "";
	int nValue = 0;

	reg.Read(str_eType, &nValue);
	pData->eType = (eMcNElcType)nValue;

	reg.Read(str_sUp_ePrec, &nValue);
	pData->sUp.ePrec = (eMcPrecise)nValue;

	reg.Read(str_sDown_ePrec, &nValue);
	pData->sDown.ePrec = (eMcPrecise)nValue;

	//str_double.Format("%f", pData->sUp.dValue);
	reg.Read(str_sUp_dValue, &str_double);
	
	pData->sUp.dValue = atof(str_double.GetBuffer(str_double.GetLength()));
	str_double.ReleaseBuffer();

	reg.Read(str_sDown_dValue, &str_double);
	pData->sDown.dValue = atof(str_double.GetBuffer(str_double.GetLength()));
	str_double.ReleaseBuffer();

	return TRUE;

}

BOOL CNxConfig::SetPreAfn04F25( sMcAfn04f25 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	return SetPreAfn04F25_f33("afn04f25", pData, bMaster, bReWrite);
}

BOOL CNxConfig::GetPreAfn04F25( sMcAfn04f25 *pData, BOOL bMaster /*= TRUE*/ )
{
	return GetPreAfn04F25_f33("afn04f25",pData, bMaster);
}

BOOL CNxConfig::SetPreAfn04F33( sMcAfn04f33 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	return SetPreAfn04F25_f33("afn04f33", pData, bMaster, bReWrite);
}
BOOL CNxConfig::GetPreAfn04F33( sMcAfn04f33 *pData,  BOOL bMaster /*= TRUE*/ )
{
	return GetPreAfn04F25_f33("afn04f33",pData, bMaster);
}


BOOL CNxConfig::SetPreAfn04F25_f33(CString strKeyName,  sMcAfn04f25 *pData,BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = strKeyName;
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	// key_name
	CString key_usID       = "usID";
	CString key_ucPort     = "ucPort";
	CString key_ucAddr     = "ucAddr";
	CString key_eAcsProto  = "eAcsProto";
	CString key_ucPwd      = "ucPwd";
	CString key_eAcsPort   = "eAcsPort";
	
	// ser
	CString key_eBaud      = "eBaud";
	CString key_bStop1     = "bStop1";
	CString key_bCheck     = "bCheck";
	CString key_bOdd       = "bOdd";
	CString key_eBit       = "eBit";

	// zigbee
	CString key_ulAddrZigb = "ulAddrZigb";

	// eth
	CString key_eth_usPort  = "usEthPort";
	CString key_sAcsIp0     = "sAcsIp0";
	CString key_sAcsIp1     = "sAcsIp1";
	CString key_sAcsIp2     = "sAcsIp2";
	CString key_sAcsIp3     = "sAcsIp3";

	// usAcsPort
	CString key_usAcsPort = "usAcsPort";
	CString key_sAccessIP0 = "sAccess0";
	CString key_sAccessIP1 = "sAccess1";
	CString key_sAccessIP2 = "sAccess2";
	CString key_sAccessIP3 = "sAccess3";


	// 值
	CString strValue;
	char buf[17] = {0};

	// 将值写入注册表
	// usID;
	reg.Write(key_usID, pData->usID);
	reg.Write(key_ucPort, pData->ucPort);
	
	// ucAddr
	memcpy(buf, pData->ucAddr, 16);
	strValue.Format("%s", buf);
	reg.Write(key_ucAddr, strValue);

	//eAcsProto
	reg.Write(key_eAcsProto, pData->eAcsProto);

	// key_ucPwd
	memset(buf, 0, 17);
	memcpy(buf, pData->ucPwd, 6);
	strValue.Format("%s", buf);
	reg.Write(key_ucPwd, strValue);
	
	// eAcsPort
	reg.Write(key_eAcsPort, pData->eAcsPort);

	switch (pData->eAcsPort)
	{
	case MC_ACS_PORT_SER:

		reg.Write(key_eBaud, pData->uPortPara.sSer.eBaud);
		reg.Write(key_bStop1, pData->uPortPara.sSer.bStop1);
		reg.Write(key_bCheck, pData->uPortPara.sSer.bCheck);
		reg.Write(key_bOdd, pData->uPortPara.sSer.bOdd == TRUE ? TRUE: FALSE);
		reg.Write(key_eBit, pData->uPortPara.sSer.eBit);
		break;

	case MC_ACS_PORT_ETH:
		reg.Write(key_eth_usPort, pData->uPortPara.sEth.usPort);
		reg.Write(key_sAcsIp0, pData->uPortPara.sEth.sAccess.ip[0]);
		reg.Write(key_sAcsIp1, pData->uPortPara.sEth.sAccess.ip[1]);
		reg.Write(key_sAcsIp2, pData->uPortPara.sEth.sAccess.ip[2]);
		reg.Write(key_sAcsIp3, pData->uPortPara.sEth.sAccess.ip[3]);
		break;

	case MC_ACS_PORT_ZIGB:

		trans_zigbee(false, strValue, (char*)&pData->uPortPara.mac[0]);
		reg.Write(key_ulAddrZigb, strValue);

		break;

	default:
		break;

	}


	reg.Write(key_usAcsPort, pData->usAcsPort);
	reg.Write(key_sAccessIP0, pData->sAccess.ip[0]);
	reg.Write(key_sAccessIP1, pData->sAccess.ip[1]);
	reg.Write(key_sAccessIP2, pData->sAccess.ip[2]);
	reg.Write(key_sAccessIP3, pData->sAccess.ip[3]);

	
	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F25_f33( CString strKeyName, sMcAfn04f25 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	//CString   strKeyName = strKeyName;
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	
	// key_name
	CString key_usID       = "usID";
	CString key_ucPort     = "ucPort";
	CString key_ucAddr     = "ucAddr";
	CString key_eAcsProto  = "eAcsProto";
	CString key_ucPwd      = "ucPwd";
	CString key_eAcsPort   = "eAcsPort";
	
	// ser
	CString key_eBaud      = "eBaud";
	CString key_bStop1     = "bStop1";
	CString key_bCheck     = "bCheck";
	CString key_bOdd       = "bOdd";
	CString key_eBit       = "eBit";
	
	// zigbee
	CString key_ulAddrZigb = "ulAddrZigb";
	
	// eth
	CString key_eth_usPort  = "usEthPort";
	CString key_sAcsIp0     = "sAcsIp0";
	CString key_sAcsIp1     = "sAcsIp1";
	CString key_sAcsIp2     = "sAcsIp2";
	CString key_sAcsIp3     = "sAcsIp3";

	// usAcsPort
	CString key_usAcsPort = "usAcsPort";
	CString key_sAccessIP0 = "sAccess0";
	CString key_sAccessIP1 = "sAccess1";
	CString key_sAccessIP2 = "sAccess2";
	CString key_sAccessIP3 = "sAccess3";

	// 值
	CString strValue;
	//char buf[17] = {0};
	DWORD dwValue = 0;

	// 将值写入注册表
	// usID;
	reg.Read(key_usID, &dwValue);
	pData->usID = (UINT16)dwValue;
	
	// ucPort
	reg.Read(key_ucPort, &dwValue);
	pData->ucPort = (UINT8)dwValue;
	
	// ucAddr
	reg.Read(key_ucAddr, &strValue);
	memset(pData->ucAddr, 0, 16);
	memcpy(pData->ucAddr, strValue.GetBuffer(strValue.GetLength()), strValue.GetLength());
	strValue.ReleaseBuffer();

	//eAcsProto
	reg.Read(key_eAcsProto, &dwValue);
	pData->eAcsProto = (eMcAcsProto)dwValue;
	
	// key_ucPwd
	memset(pData->ucPwd, 0, 6);
	reg.Read(key_ucPwd, &strValue);
	memcpy(pData->ucPwd, strValue.GetBuffer(strValue.GetLength()), strValue.GetLength());
	strValue.ReleaseBuffer();

	// eAcsPort
	reg.Read(key_eAcsPort, &dwValue);
	pData->eAcsPort = (eMcAcsPort)dwValue;
	
	switch (pData->eAcsPort)
	{
	case MC_ACS_PORT_SER:
		
		reg.Read(key_eBaud, &dwValue);
		pData->uPortPara.sSer.eBaud = (eMcSerBaud)dwValue;
		reg.Read(key_bStop1, &(pData->uPortPara.sSer.bStop1));
		reg.Read(key_bCheck, &pData->uPortPara.sSer.bCheck);
		reg.Read(key_bOdd, &pData->uPortPara.sSer.bOdd);
		reg.Read(key_eBit, &dwValue);
		pData->uPortPara.sSer.eBit = (eMcSerBit)dwValue;
		break;
		
	case MC_ACS_PORT_ETH:
		reg.Read(key_eth_usPort, &dwValue);
		pData->uPortPara.sEth.usPort = (UINT16)dwValue;
		reg.Read(key_sAcsIp0, &dwValue);
		pData->uPortPara.sEth.sAccess.ip[0] = (UINT8)dwValue;

		reg.Read(key_sAcsIp1, &dwValue);
		pData->uPortPara.sEth.sAccess.ip[1] = (UINT8)dwValue;

		reg.Read(key_sAcsIp2, &dwValue);
		pData->uPortPara.sEth.sAccess.ip[2] = (UINT8)dwValue;

		reg.Read(key_sAcsIp3, &dwValue);
		pData->uPortPara.sEth.sAccess.ip[3] = (UINT8)dwValue;
		pData->uPortPara.sEth.sAccess.eVersion = MC_IP_V4;
		break;
		
	case MC_ACS_PORT_ZIGB:
		memset(pData->uPortPara.mac, 0, 8);
		reg.Read(key_ulAddrZigb, &strValue);
		//memcpy(pData->uPortPara.mac, strValue.GetBuffer(strValue.GetLength()), strValue.GetLength());
		//strValue.ReleaseBuffer();
	    trans_zigbee(true, strValue, (char*)&pData->uPortPara.mac[0]);
			
		break;
		
	default:
		break;
		
	}

	reg.Read(key_usAcsPort, &dwValue);
	pData->usAcsPort = (UINT16)dwValue;

	reg.Read(key_sAccessIP0, &dwValue);
	pData->sAccess.ip[0] = (UINT8)dwValue;

	reg.Read(key_sAccessIP1, &dwValue);
	pData->sAccess.ip[1] = (UINT8)dwValue;

	reg.Read(key_sAccessIP2, &dwValue);
	pData->sAccess.ip[2] = (UINT8)dwValue;

	reg.Read(key_sAccessIP3, &dwValue);
	pData->sAccess.ip[3] = (UINT8)dwValue;

	pData->sAccess.eVersion = MC_IP_V4;
	
	return TRUE;
}


// 获得一个ip字符串中第(0-3)个地址
UINT8 CNxConfig::GetIpNum( CString strIp, int index )
{
	
	UINT8 ucRet = 0;
	int len;
	CString strTmp;
	CString strRet0,strRet1,strRet2,strRet3;

	
	strTmp = strIp;
	len = strTmp.Find(".", 0);
    strRet0 = strTmp.Left(len);

	// 1
	strTmp = strTmp.Right(strTmp.GetLength() - len - 1);
	len = strTmp.Find(".", 0);
    strRet1 = strTmp.Left(len);

	// 2
	strTmp = strTmp.Right(strTmp.GetLength() - len - 1);
	len = strTmp.Find(".", 0);
    strRet2 = strTmp.Left(len);

	// 3
	strRet3 = strTmp.Right(strTmp.GetLength() - len - 1);

	switch (index)
	{
	case 0:
		ucRet = atoi(strRet0.GetBuffer(strRet0.GetLength()));
		strRet0.ReleaseBuffer();
		break;
		
	case 1:
		ucRet = atoi(strRet1.GetBuffer(strRet1.GetLength()));
		strRet1.ReleaseBuffer();
		break;
		
	case 2:
		ucRet = atoi(strRet2.GetBuffer(strRet2.GetLength()));
		strRet2.ReleaseBuffer();
		break;
		
	case 3:
		ucRet = atoi(strRet3.GetBuffer(strRet3.GetLength()));
		strRet3.ReleaseBuffer();
		break;
			
	default:
		break;
	}
	
	return ucRet;
	
}

BOOL CNxConfig::SetPreAfn04F3( sMcAfn04f3 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f3";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	CString str_ucType  = "ucTypeID";
	CString str_usPara  = "usAuthPara";

	
    reg.Write(str_ucType, pData->ucTypeID);
	reg.Write(str_usPara, pData->usAuthPara);


	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F3( sMcAfn04f3 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f3";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}


	CString str_ucType  = "ucTypeID";
	CString str_usPara  = "usAuthPara";
	
	int nVal = 0;
    reg.Read(str_ucType, &nVal);
	pData->ucTypeID = nVal;

	reg.Read(str_usPara, &nVal);
	pData->usAuthPara = nVal;

	return TRUE;	
}

BOOL CNxConfig::SetPreAfn04F4( sMcAfn04f4 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f4";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	
	CString str_key = "";
	int i = 0;
	DWORD dwValue = 0;

	for (i = 0; i < 8; i++)
	{	
		str_key.Format("ulAddr%d", i);
		dwValue = pData->ulAddr[i];
		reg.Write(str_key, dwValue);
	}

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F4( sMcAfn04f4 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f4";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	


	CString str_key = "";
	int i = 0;
	DWORD dwValue = 0;
	for (i = 0; i < 8; i++)
	{	
		str_key.Format("ulAddr%d", i);
		reg.Read(str_key, &dwValue);
		pData->ulAddr[i] = (UINT32)dwValue;
	}
	
	
	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F5( sMcAfn04f5 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f5";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	
	int i = 0;
	// key
	CString key_usPort = "usPort";
	CString key_sConIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sConIp[i].Format("sConIp[%d]", i);
	}
	
	CString key_sMask[4];
	for (i = 0; i < 4; i++)
	{
		key_sMask[i].Format("sMask[%d]", i);
	}

	
	CString key_sGateIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sGateIp[i].Format("sGateIp[%d]", i);
	}


	CString key_eDelegate = "eDelegate";

	CString key_sDelgIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sDelgIp[i].Format("sDelgIp[%d]", i);
	}

	CString key_usDelgPort = "usDelgPort";
	CString key_eDelgLink  = "eDelgLink";
	CString key_bDlegUsr = "bDlegUsr";
	CString key_ucDlegUsrLen = "ucDlegUsrLen";
	CString key_ucDlegUsr = "ucDlegUsr";
	CString key_bDlegPwd = "bDlegPwd";
	CString key_ucDlegPwdLen = "ucDlegPwdLen";
	CString key_ucDlegPwd = "ucDlegPwd";

	// value
	reg.Write(key_usPort, pData->usPort);
	// sConIp
	for (i = 0; i < 4; i++)
	{
		reg.Write(key_sConIp[i], pData->sConIp.ip[i]);
		reg.Write(key_sGateIp[i], pData->sGateIp.ip[i]);
		reg.Write(key_sDelgIp[i], pData->sDelgIp.ip[i]);
		reg.Write(key_sMask[i], pData->sMask.ip[i]);
	}

	// 
	reg.Write(key_usDelgPort, pData->usDelgPort);
	reg.Write(key_eDelgLink, pData->eDelgLink);
	reg.Write(key_eDelegate, pData->eDelegate);

	// usr
	reg.Write(key_bDlegUsr, pData->bDlegUsr);
	reg.Write(key_ucDlegUsrLen, pData->ucDlegUsrLen);

	char buf[21] = {0};
	CString strValue;
	int len = 0;
	len	= pData->ucDlegUsrLen;
	len = len > 20 ? 20 : len;
	if (len > 0)
	{
	    memcpy(buf, pData->ucDlegUsr, len);
	}
	
	strValue.Format("%s", buf);
	reg.Write(key_ucDlegUsr, strValue);


	// pwd
	reg.Write(key_bDlegPwd, pData->bDlegUsr);
	reg.Write(key_ucDlegUsrLen, pData->ucDlegPwdLen);

	memset(buf, 0, 21);
	len	= pData->ucDlegPwdLen;
	len = len > 20 ? 20 : len;
	if (len > 0)
	{
		memcpy(buf, pData->ucDlegPwd, len);
	}

	strValue.Format("%s", buf);
	reg.Write(key_ucDlegPwd, strValue);


	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F5( sMcAfn04f5 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f5";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	
	int i = 0;
	DWORD dwValue = 0;

	// key
	CString key_usPort = "usPort";
	CString key_sConIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sConIp[i].Format("sConIp[%d]", i);
	}

	CString key_sMask[4];
	for (i = 0; i < 4; i++)
	{
		key_sMask[i].Format("sMask[%d]", i);
	}

	CString key_sGateIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sGateIp[i].Format("sGateIp[%d]", i);
	}
	
	
	CString key_eDelegate = "eDelegate";
	
	CString key_sDelgIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sDelgIp[i].Format("sDelgIp[%d]", i);
	}
	
	CString key_usDelgPort = "usDelgPort";
	CString key_eDelgLink  = "eDelgLink";
	CString key_bDlegUsr = "bDlegUsr";
	CString key_ucDlegUsrLen = "ucDlegUsrLen";
	CString key_ucDlegUsr = "ucDlegUsr";
	CString key_bDlegPwd = "bDlegPwd";
	CString key_ucDlegPwdLen = "ucDlegPwdLen";
	CString key_ucDlegPwd = "ucDlegPwd";
	



	// value
	reg.Read(key_usPort, &dwValue);
	pData->usPort = (UINT16)dwValue;

	// sConIp
	for (i = 0; i < 4; i++)
	{
		reg.Read(key_sConIp[i], &dwValue);
		pData->sConIp.ip[i] = (UINT8)dwValue;

		reg.Read(key_sMask[i], &dwValue);
		pData->sMask.ip[i] = (UINT8)dwValue;

		reg.Read(key_sGateIp[i], &dwValue);
		pData->sGateIp.ip[i] = (UINT8)dwValue;

		reg.Read(key_sDelgIp[i], &dwValue);
		pData->sDelgIp.ip[i] = (UINT8)dwValue;
	}
	
	pData->sConIp.eVersion = MC_IP_V4;
	pData->sMask.eVersion = MC_IP_V4;
	pData->sGateIp.eVersion = MC_IP_V4;
	pData->sDelgIp.eVersion = MC_IP_V4;

	// 
	reg.Read(key_usDelgPort, &dwValue);
	pData->usDelgPort = (UINT16)dwValue;

	reg.Read(key_eDelegate, &dwValue);
	pData->eDelegate = (eMcDelegate)dwValue;


	reg.Read(key_eDelgLink, &dwValue);
	pData->eDelgLink = (eMcDelgLink)dwValue;

	// usr
	reg.Read(key_bDlegUsr, &dwValue);
	pData->bDlegUsr = (BOOL)dwValue;
	reg.Read(key_ucDlegUsrLen, &dwValue);
	pData->ucDlegUsrLen = (UINT8)dwValue;
	
	CString strValue;
	reg.Read(key_ucDlegUsr, &strValue);
	memcpy(pData->ucDlegUsr, strValue.GetBuffer(strValue.GetLength()), pData->ucDlegUsrLen);
	strValue.ReleaseBuffer();


	// pwd
	reg.Read(key_bDlegPwd, &dwValue);
	pData->bDlegPwd = (BOOL)dwValue;
	reg.Read(key_ucDlegUsrLen, &dwValue);
	pData->ucDlegPwdLen = (UINT8)dwValue;
	
	reg.Read(key_ucDlegPwd, &strValue);
	memcpy(pData->ucDlegPwd, strValue.GetBuffer(strValue.GetLength()), pData->ucDlegPwdLen);
	strValue.ReleaseBuffer();

	

	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F7( sMcAfn04f7 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f7";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	
	int i = 0;
	// key
	CString key_usPort = "usPort";
	CString key_sMainIp[4];
	CString key_sBackIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sMainIp[i].Format("sMainIp[%d]", i);
		key_sBackIp[i].Format("sBackIp[%d]", i);
	}
	
	CString key_usMainPort = "usMainPort";
	CString key_usBackPort  = "usBackPort";
	CString key_ucAPN = "ucAPN";
	CString key_ucUsr = "ucUsr";
	CString key_ucPwd = "ucPwd";


	// value
	reg.Write(key_usPort, pData->ucPort);

	// main back ip
	for (i = 0; i < 4; i++)
	{
		reg.Write(key_sMainIp[i], pData->sMainIp.ip[i]);
		reg.Write(key_sBackIp[i], pData->sBackIp.ip[i]);

	}

	// port
	reg.Write(key_usMainPort, pData->usMainPort);
	reg.Write(key_usBackPort, pData->usBackPort);

	#define  LEN_BFU  34
	char pStr[LEN_BFU] = {0};
	CString strValue;
	
	// usr
	memcpy(pStr, pData->ucAPN, 16);
	strValue.Format("%s", pStr);
	reg.Write(key_ucAPN, strValue);
	
	// usr
	memset(pStr, 0, LEN_BFU);
	memcpy(pStr, pData->ucUsr, 32);
	strValue.Format("%s", pStr);
	reg.Write(key_ucUsr, strValue);

	// pwd
	memset(pStr, 0, LEN_BFU);
	memcpy(pStr, pData->ucPwd, 32);
	strValue.Format("%s", pStr);
	reg.Write(key_ucPwd, strValue);

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F7( sMcAfn04f7 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f7";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}


	int i = 0;
	DWORD dwValue = 0;

	// key
	CString key_usPort = "usPort";
	CString key_sMainIp[4];
	CString key_sBackIp[4];
	for (i = 0; i < 4; i++)
	{
		key_sMainIp[i].Format("sMainIp[%d]", i);
		key_sBackIp[i].Format("sBackIp[%d]", i);
	}
	
	CString key_usMainPort = "usMainPort";
	CString key_usBackPort  = "usBackPort";
	CString key_ucAPN = "ucAPN";
	CString key_ucUsr = "ucUsr";
	CString key_ucPwd = "ucPwd";
	
	
	// value
	reg.Read(key_usPort, &dwValue);
	pData->ucPort = (UINT8)dwValue;
	
	// main back ip
	pData->sMainIp.eVersion = MC_IP_V4;
	pData->sBackIp.eVersion = MC_IP_V4;
	for (i = 0; i < 4; i++)
	{
		reg.Read(key_sMainIp[i], &dwValue);
		pData->sMainIp.ip[i] = (UINT8)dwValue;
	
		reg.Read(key_sBackIp[i], &dwValue);
		pData->sBackIp.ip[i] = (UINT8)dwValue;
		
	}
	
	// port
	reg.Read(key_usMainPort, &dwValue);
	pData->usMainPort = (UINT16)dwValue;

	reg.Read(key_usBackPort, &dwValue);
	pData->usBackPort = (UINT16)dwValue;
	

	CString strValue;
	int len = 0;
	
	// usr
	memset(pData->ucAPN, 0, 16);
	reg.Read(key_ucAPN, &strValue);
	len = strValue.GetLength();
	len = len > 16 ? 16 : len;
	memcpy(pData->ucAPN, strValue.GetBuffer(strValue.GetLength()), len);
	strValue.ReleaseBuffer();

	// usr
	memset(pData->ucUsr, 0, 32);
	reg.Read(key_ucUsr, &strValue);
	len = strValue.GetLength();
	len = len > 32 ? 32 : len;
	memcpy(pData->ucUsr, strValue.GetBuffer(strValue.GetLength()), len);
	strValue.ReleaseBuffer();
	
	// pwd
	memset(pData->ucPwd, 0, 32);
	reg.Read(key_ucPwd, &strValue);
	len = strValue.GetLength();
	len = len > 32 ? 32 : len;
	memcpy(pData->ucPwd, strValue.GetBuffer(strValue.GetLength()), len);
	strValue.ReleaseBuffer();
	

	return TRUE;
}


// 
BOOL CNxConfig::SetPreAfn04F9( sMcAfn04f9 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f9";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}



	int i = 0;
	CString key_ucNeed = "ucNeed";
	CString key_aNeed;
	CString key_ucImpt = "ucImpt";
	CString key_aImpt;
	CString key_usImpRecNum = "usImpRecNum";
	CString key_usNmlRecNum = "usNmlRecNum";

	// ucNeed
	reg.Write(key_ucNeed, pData->ucNeed);
	reg.Write(key_ucImpt, pData->ucImpt);
	reg.Write(key_usImpRecNum, pData->usImpRecNum);
	reg.Write(key_usNmlRecNum, pData->usNmlRecNum);

	for(i = 0; i < pData->ucNeed; i++)
	{
		key_aNeed.Format("aNeed_%d", i);
		reg.Write(key_aNeed, pData->aNeed[i]);
	
	}

	for(i = 0; i < pData->ucImpt; i++)
	{
		key_aImpt.Format("aImpt_%d", i);
		reg.Write(key_aImpt, pData->aImpt[i]);
	}
	
	if (pData->ucNeed == 0)
	{
		for(i = 0; i < 64; i++)
		{
			key_aNeed.Format("aNeed_%d", i);
			reg.DeleteSubKey(key_aNeed);

			key_aImpt.Format("aImpt_%d", i);
			reg.DeleteSubKey(key_aImpt);
		}
	}

	if (pData->ucImpt == 0)
	{
		for(i = 0; i < 64; i++)
		{		
			key_aImpt.Format("aImpt_%d", i);
			reg.DeleteSubKey(key_aImpt);
		}
	}




	return TRUE;
	
}

BOOL CNxConfig::GetPreAfn04F9( sMcAfn04f9 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f9";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}



	int i = 0;
	DWORD dwValue = 0;
	CString key_ucNeed = "ucNeed";
	CString key_aNeed;
	CString key_ucImpt = "ucImpt";
	CString key_aImpt;
	CString key_usImpRecNum = "usImpRecNum";
	CString key_usNmlRecNum = "usNmlRecNum";
	
	// ucNeed
	reg.Read(key_ucNeed, &dwValue);
	pData->ucNeed = (UINT8)dwValue;

	reg.Read(key_ucImpt, &dwValue);
	pData->ucImpt = (UINT8)dwValue;
		

	reg.Read(key_usImpRecNum, &dwValue);
	pData->usImpRecNum = (UINT16)dwValue;
	
	reg.Read(key_usNmlRecNum, &dwValue);
	pData->usNmlRecNum = (UINT16)dwValue;
	
	for(i = 0; i < pData->ucNeed; i++)
	{
		key_aNeed.Format("aNeed_%d", i);
		reg.Read(key_aNeed, &dwValue);
		pData->aNeed[i]  = (eMcErc)dwValue;
		
	}
	
	for(i = 0; i < pData->ucImpt; i++)
	{
		key_aImpt.Format("aImpt_%d", i);
		reg.Read(key_aImpt, &dwValue);
		pData->aImpt[i] = (eMcErc)dwValue;
	}

	return TRUE;
	


}

BOOL CNxConfig::SetPreAfn04F10( sMcAfn04f10 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f10";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}


	int i = 0;
	CString str_in;
	CString str_on;
	for (i = 0; i < 8; i++)
	{
		str_in.Format("in_%d", i);
		str_on.Format("on_%d", i);

		reg.Write(str_in, pData->bIn[i]);
		reg.Write(str_on, pData->bOn[i]);
	}

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F10( sMcAfn04f10 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f10";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	
	int i = 0;
	CString str_in;
	CString str_on;
	for (i = 0; i < 8; i++)
	{
		str_in.Format("in_%d", i);
		str_on.Format("on_%d", i);
		
		reg.Read(str_in, &pData->bIn[i]);
		reg.Read(str_on, &pData->bOn[i]);
	}

	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F26( sMcAfn04f26 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f26";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}

	CString key_ucInteger = "ucInteger";
	CString key_ucDecimal = "ucDecimal";
	CString key_usTimesU  = "usTimesU";
	CString key_usTimesI  = "usTimesI";
	CString key_fU        = "fU";
	CString key_fI        = "fI";
	CString key_eLink     = "eLink";
	CString key_ePhase    = "ePhase";
	
	CString str_value;

	reg.Write(key_ucInteger, pData->sDigit.ucInteger);
	reg.Write(key_ucDecimal, pData->sDigit.ucDecimal);
	reg.Write(key_usTimesU, pData->usTimesU);
	reg.Write(key_usTimesI, pData->usTimesI);

	reg.Write(key_eLink, pData->sLinkWay.eLink);
	reg.Write(key_ePhase, pData->sLinkWay.ePhase);

	str_value.Format("%4.1f", pData->fU);
	reg.Write(key_fU, str_value);

	str_value.Format("%6.3f", pData->fI);
	reg.Write(key_fI, str_value);


	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F26( sMcAfn04f26 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f26";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	CString key_ucInteger = "ucInteger";
	CString key_ucDecimal = "ucDecimal";
	CString key_usTimesU  = "usTimesU";
	CString key_usTimesI  = "usTimesI";
	CString key_fU        = "fU";
	CString key_fI        = "fI";
	CString key_eLink     = "eLink";
	CString key_ePhase    = "ePhase";
	
	CString str_value;
	DWORD dwValue = 0;
	
	reg.Read(key_ucInteger, &dwValue);
	pData->sDigit.ucInteger = (UINT8)dwValue;

	reg.Read(key_ucDecimal, &dwValue);
	pData->sDigit.ucDecimal = (UINT8)dwValue;

	reg.Read(key_usTimesU, &dwValue);
	pData->usTimesU = (UINT16)dwValue;

	reg.Read(key_usTimesI, &dwValue);
	pData->usTimesI = (UINT16)dwValue;
	
	reg.Read(key_eLink, &dwValue);
	pData->sLinkWay.eLink = (eMcLink)dwValue;
	reg.Read(key_ePhase, &dwValue);
	pData->sLinkWay.ePhase = (eMcPhase)dwValue;
	
	
	reg.Read(key_fU, &str_value);
	pData->fU = (float)atof(str_value.GetBuffer(str_value.GetLength()));
	str_value.ReleaseBuffer();
	

	reg.Read(key_fI, &str_value);
	 pData->fI = (float)atof(str_value.GetBuffer(str_value.GetLength()));
	 str_value.ReleaseBuffer();

	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F27( sMcAfn04f27 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f27";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}


	// key name
	CString key_fDropV      = "fDropV";
	CString key_ucTimeLossV = "ucTimeLossV";

	CString key_sOverV_fUpUp = "sOverV_fUpUp";
	CString key_sOverV_ucTime = "sOverV_ucTime";
	CString key_sOverV_fFactor= "sOverV_fFactor";
	
	CString key_sLossV_fDownDown = "sLossV_fDownDown";
	CString key_sLossV_ucTime    = "sLossV_ucTime";
	CString key_sLossV_fFactor = "sLossV_fFactor";

	CString key_sOverI_fUpUp = "sOverI_fUpUp";
	CString key_sOverI_ucTime = "sOverI_ucTime";
	CString key_sOverI_fFactor= "sOverI_fFactor";
	
	CString key_sSuperI_fUp = "sSuperI_fUp";
	CString key_sSuperI_ucTime    = "sSuperI_ucTime";
	CString key_sSuperI_fFactor = "sSuperI_fFactor";

	CString key_sZeroI_fUp = "sZeroI_fUp";
	CString key_sZeroI_ucTime    = "sZeroI_ucTime";
	CString key_sZeroI_fFactor = "sZeroI_fFactor";

	CString key_sUblV_fLimit = "sUblV_fLimit";
	CString key_sUblV_ucTime    = "sUblV_ucTime";
	CString key_sUblV_fFactor = "sUblV_fFactor";

	CString key_sUblI_fLimit = "sUblI_fLimit";
	CString key_sUblI_ucTime    = "sUblI_ucTime";
	CString key_sUblI_fFactor = "sUblI_fFactor";

	
	CString strValue;

	strValue.Format("%4.1f", pData->fDropV);
	reg.Write(key_fDropV, strValue);
	
	reg.Write(key_ucTimeLossV, pData->ucTimeLossV);
	
	// sOverV
	strValue.Format("%4.1f", pData->sOverV.fUpUp);
	reg.Write(key_sOverV_fUpUp, strValue);
	
	strValue.Format("%4.2f", pData->sOverV.fFactor);
	reg.Write(key_sOverV_fFactor, strValue);
	
	reg.Write(key_sOverV_ucTime, pData->sOverV.ucTime);
	
	// sLossV
	strValue.Format("%4.1f", pData->sLossV.fDownDown);
	reg.Write(key_sLossV_fDownDown, strValue);

	strValue.Format("%4.2f", pData->sLossV.fFactor);
	reg.Write(key_sLossV_fFactor, strValue);
	
	reg.Write(key_sLossV_ucTime, pData->sLossV.ucTime);

	// sOverI
	strValue.Format("%6.3f", pData->sOverI.fUpUp);
	reg.Write(key_sOverI_fUpUp, strValue);
	
	strValue.Format("%4.2f", pData->sOverI.fFactor);
	reg.Write(key_sOverI_fFactor, strValue);
	
	reg.Write(key_sOverI_ucTime, pData->sOverI.ucTime);

	// sSuperI
	strValue.Format("%6.3f", pData->sSuperI.fUp);
	reg.Write(key_sSuperI_fUp, strValue);
	
	strValue.Format("%4.2f", pData->sSuperI.fFactor);
	reg.Write(key_sSuperI_fFactor, strValue);
	
	reg.Write(key_sSuperI_ucTime, pData->sSuperI.ucTime);

	// sLossV
	strValue.Format("%6.3f", pData->sZeroI.fUp);
	reg.Write(key_sZeroI_fUp, strValue);
	
	strValue.Format("%4.2f", pData->sZeroI.fFactor);
	reg.Write(key_sZeroI_fFactor, strValue);
	
	reg.Write(key_sZeroI_ucTime, pData->sZeroI.ucTime);

	// sUblV
	strValue.Format("%6.4f", pData->sUblV.fLimit);
	reg.Write(key_sUblV_fLimit, strValue);
	
	strValue.Format("%4.2f", pData->sUblV.fFactor);
	reg.Write(key_sUblV_fFactor, strValue);
	
	reg.Write(key_sUblV_ucTime, pData->sUblV.ucTime);
	
	// sUblI
	strValue.Format("%6.4f", pData->sUblI.fLimit);
	reg.Write(key_sUblI_fLimit, strValue);
	
	strValue.Format("%4.2f", pData->sUblI.fFactor);
	reg.Write(key_sUblI_fFactor, strValue);
	
	reg.Write(key_sUblI_ucTime, pData->sUblI.ucTime);
	
	
	
	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F27( sMcAfn04f27 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f27";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}


	// key name
	CString key_fDropV      = "fDropV";
	CString key_ucTimeLossV = "ucTimeLossV";

	CString key_sOverV_fUpUp = "sOverV_fUpUp";
	CString key_sOverV_ucTime = "sOverV_ucTime";
	CString key_sOverV_fFactor= "sOverV_fFactor";
	
	CString key_sLossV_fDownDown = "sLossV_fDownDown";
	CString key_sLossV_ucTime    = "sLossV_ucTime";
	CString key_sLossV_fFactor = "sLossV_fFactor";

	CString key_sOverI_fUpUp = "sOverI_fUpUp";
	CString key_sOverI_ucTime = "sOverI_ucTime";
	CString key_sOverI_fFactor= "sOverI_fFactor";
	
	CString key_sSuperI_fUp = "sSuperI_fUp";
	CString key_sSuperI_ucTime    = "sSuperI_ucTime";
	CString key_sSuperI_fFactor = "sSuperI_fFactor";

	CString key_sZeroI_fUp = "sZeroI_fUp";
	CString key_sZeroI_ucTime    = "sZeroI_ucTime";
	CString key_sZeroI_fFactor = "sZeroI_fFactor";

	CString key_sUblV_fLimit = "sUblV_fLimit";
	CString key_sUblV_ucTime    = "sUblV_ucTime";
	CString key_sUblV_fFactor = "sUblV_fFactor";

	CString key_sUblI_fLimit = "sUblI_fLimit";
	CString key_sUblI_ucTime    = "sUblI_ucTime";
	CString key_sUblI_fFactor = "sUblI_fFactor";

	
	CString strValue;
	DWORD dwValue = 0;

	reg.Read(key_fDropV, &strValue);
	pData->fDropV = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_ucTimeLossV, &dwValue);
	pData->ucTimeLossV = (UINT8)dwValue;
	
	// sOverV
	reg.Read(key_sOverV_fUpUp, &strValue);
	pData->sOverV.fUpUp = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	

	reg.Read(key_sOverV_fFactor, &strValue);
	pData->sOverV.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_sOverV_ucTime, &dwValue);
	pData->sOverV.ucTime = (UINT8)dwValue;
	
	// sLossV
	reg.Read(key_sLossV_fDownDown, &strValue);
	pData->sLossV.fDownDown = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_sLossV_fFactor, &strValue);
	pData->sLossV.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_sLossV_ucTime, &dwValue);
	pData->sLossV.ucTime = (UINT8)dwValue;
	
	// sOverI
	reg.Read(key_sOverI_fUpUp, &strValue);
	pData->sOverI.fUpUp = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_sOverI_fFactor, &strValue);
	pData->sOverI.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_sOverI_ucTime, &dwValue);
	pData->sOverI.ucTime = (UINT8)dwValue;

	
	// sSuperI
	reg.Read(key_sSuperI_fUp, &strValue);
	pData->sSuperI.fUp = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sSuperI_fFactor, &strValue);
	pData->sSuperI.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sSuperI_ucTime, &dwValue);
	pData->sSuperI.ucTime = (UINT8)dwValue;
	


	// sLossV
	reg.Read(key_sZeroI_fUp, &strValue);
	pData->sZeroI.fUp = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sZeroI_fFactor, &strValue);
	pData->sZeroI.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sZeroI_ucTime, &dwValue);
	pData->sZeroI.ucTime = (UINT8)dwValue;

	// sUblV
	reg.Read(key_sUblV_fLimit, &strValue);
	pData->sUblV.fLimit = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sUblV_fFactor, &strValue);
	pData->sUblV.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sUblV_ucTime, &dwValue);
	pData->sUblV.ucTime = (UINT8)dwValue;


	// sUblI
	reg.Read(key_sUblI_fLimit, &strValue);
	pData->sUblI.fLimit = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sUblI_fFactor, &strValue);
	pData->sUblI.fFactor = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();
	
	reg.Read(key_sUblI_ucTime, &dwValue);
	pData->sUblI.ucTime = (UINT8)dwValue;

	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F28( sMcAfn04F28 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f28";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	
	// key name
	CString key_fPara1    = "fPara1";
	CString key_fPara2    = "fPara2";
	CString key_fWarning  = "fWarning";

	CString strValue;
	
	strValue.Format("%4.2f", pData->fPara1);
	reg.Write(key_fPara1, strValue);
	
	strValue.Format("%4.2f", pData->fPara2);
	reg.Write(key_fPara2, strValue);
	
	strValue.Format("%4.2f", pData->fWarning);
	reg.Write(key_fWarning, strValue);
	

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F28( sMcAfn04F28 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f28";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	// key name
	CString key_fPara1    = "fPara1";
	CString key_fPara2    = "fPara2";
	CString key_fWarning  = "fWarning";
	
	CString strValue;

	reg.Read(key_fPara1, &strValue);
	pData->fPara1 = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_fPara2, &strValue);
	pData->fPara2 = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	reg.Read(key_fWarning, &strValue);
	pData->fWarning = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();

	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F29( sMcAfn04F29 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f29";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	

	CString strValue;
	strValue.Format("%4.2f", pData->sVa.fTotal);
	reg.Write("sVa.fTotal", strValue);

	strValue.Format("%4.2f", pData->sVa.fOdd);
	reg.Write("sVa.fOdd", strValue);

	strValue.Format("%4.2f", pData->sVa.fEven);
	reg.Write("sVa.fEven", strValue);

	// sVb
	strValue.Format("%4.2f", pData->sVb.fTotal);
	reg.Write("sVb.fTotal", strValue);
	
	strValue.Format("%4.2f", pData->sVb.fOdd);
	reg.Write("sVb.fOdd", strValue);
	
	strValue.Format("%4.2f", pData->sVb.fEven);
	reg.Write("sVb.fEven", strValue);
	
	// sVc
	strValue.Format("%4.2f", pData->sVc.fTotal);
	reg.Write("sVc.fTotal", strValue);
	
	strValue.Format("%4.2f", pData->sVc.fOdd);
	reg.Write("sVc.fOdd", strValue);
	
	strValue.Format("%4.2f", pData->sVc.fEven);
	reg.Write("sVc.fEven", strValue);
	
	// sIa
	strValue.Format("%4.2f", pData->sIa.fTotal);
	reg.Write("sIa.fTotal", strValue);
	
	strValue.Format("%4.2f", pData->sIa.fOdd);
	reg.Write("sIa.fOdd", strValue);
	
	strValue.Format("%4.2f", pData->sIa.fEven);
	reg.Write("sIasVa.fEven", strValue);
	
	// sIb
	strValue.Format("%4.2f", pData->sIb.fTotal);
	reg.Write("sIb.fTotal", strValue);
	
	strValue.Format("%4.2f", pData->sIb.fOdd);
	reg.Write("sIb.fOdd", strValue);
	
	strValue.Format("%4.2f", pData->sIb.fEven);
	reg.Write("sIb.fEven", strValue);
	
	// sIc
	strValue.Format("%4.2f", pData->sIc.fTotal);
	reg.Write("sIc.fTotal", strValue);
	
	strValue.Format("%4.2f", pData->sIc.fOdd);
	reg.Write("sIc.fOdd", strValue);
	
	strValue.Format("%4.2f", pData->sIc.fEven);
	reg.Write("sIc.fEven", strValue);

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F29( sMcAfn04F29 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f29";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	CString strValue;

	// sVa
	reg.Read("sVa.fTotal", &strValue);
	pData->sVa.fTotal = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	

	reg.Read("sVa.fOdd", &strValue);
	pData->sVa.fOdd = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	

	reg.Read("sVa.fEven", &strValue);
	pData->sVa.fEven = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	// sVb
	reg.Read("sVb.fTotal", &strValue);
	pData->sVb.fTotal = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sVb.fOdd", &strValue);
	pData->sVb.fOdd = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sVb.fEven", &strValue);
	pData->sVb.fEven = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	

	// sVc
	reg.Read("sVc.fTotal", &strValue);
	pData->sVc.fTotal = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sVc.fOdd", &strValue);
	pData->sVc.fOdd = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sVc.fEven", &strValue);
	pData->sVc.fEven = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	

	// sIa
	reg.Read("sIa.fTotal", &strValue);
	pData->sIa.fTotal = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sIa.fOdd", &strValue);
	pData->sIa.fOdd = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sIa.fEven", &strValue);
	pData->sIa.fEven = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	// sIb
	reg.Read("sIb.fTotal", &strValue);
	pData->sIb.fTotal = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sIb.fOdd", &strValue);
	pData->sIb.fOdd = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sIb.fEven", &strValue);
	pData->sIb.fEven = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	// sIc
	reg.Read("sIc.fTotal", &strValue);
	pData->sIc.fTotal = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sIc.fOdd", &strValue);
	pData->sIc.fOdd = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("sIc.fEven", &strValue);
	pData->sIc.fEven = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	

	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F30( sMcAfn04f30 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f30";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	

	CString strValue;
	strValue.Format("%4.2f", pData->fLong);
	reg.Write("fLong", strValue);
	
	strValue.Format("%4.2f", pData->fShort);
	reg.Write("fShort", strValue);

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F30( sMcAfn04f30 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f30";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	
	CString strValue;
	
	// sVa
	reg.Read("fShort", &strValue);
	pData->fShort = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	reg.Read("fLong", &strValue);
	pData->fLong = (float)atof(strValue.GetBuffer(strValue.GetLength()));
	strValue.ReleaseBuffer();	
	
	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F49( sMcAfn04f49 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f49";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	int i = 0;

	reg.Write("sTimeFrez.ucYY",  pData->sTimeFrez.ucYY);
	reg.Write("sTimeFrez.ucMonth",  pData->sTimeFrez.ucMM);
	reg.Write("sTimeFrez.ucDD",  pData->sTimeFrez.ucDD);
	reg.Write("sTimeFrez.ucWW",  pData->sTimeFrez.ucWW);
	reg.Write("sTimeFrez.ucHH",  pData->sTimeFrez.ucHH);
	reg.Write("sTimeFrez.ucmm",  pData->sTimeFrez.ucmm);
	reg.Write("sTimeFrez.ucss",  pData->sTimeFrez.ucss);

	reg.Write("sTimeRprt.ucYY",  pData->sTimeRprt.ucYY);
	reg.Write("sTimeRprt.ucMonth",  pData->sTimeRprt.ucMM);
	reg.Write("sTimeRprt.ucDD",  pData->sTimeRprt.ucDD);
	reg.Write("sTimeRprt.ucWW",  pData->sTimeRprt.ucWW);
	reg.Write("sTimeRprt.ucHH",  pData->sTimeRprt.ucHH);
	reg.Write("sTimeRprt.ucmm",  pData->sTimeRprt.ucmm);
	reg.Write("sTimeRprt.ucss",  pData->sTimeRprt.ucss);

	reg.Write("sFreez.ucTimes",  pData->sFreez.ucTimes);
	reg.Write("sFreez.eUnit",  pData->sFreez.eUnit);
	reg.Write("sFreez.usPeriod",  pData->sFreez.usPeriod);

	reg.Write("eUnitRpt",  pData->eUnitRpt);
	reg.Write("uCmdPnNum",  pData->uCmdPnNum);
	reg.Write("ucPeriodRpt",  pData->ucPeriodRpt);


	CString strKeyfn, strKeyPn;
	// 先删除已经存在的节点
	
	for (i = 0; i < 244; i++)
	{
		strKeyfn.Format("sCmdPn[%d].eCmd", i);
		strKeyPn.Format("sCmdPn[%d].usPn", i);
		reg.DeleteSubKey(strKeyfn);
		reg.DeleteSubKey(strKeyPn);
		
	}

	for (i = 0; i < pData->uCmdPnNum; i++)
	{
		strKeyfn.Format("sCmdPn[%d].eCmd", i);
		strKeyPn.Format("sCmdPn[%d].usPn", i);
		
		reg.Write(strKeyfn,  pData->sCmdPn[i].eCmd);
		reg.Write(strKeyPn,  pData->sCmdPn[i].usPn);
	}

	return TRUE;
}

BOOL CNxConfig::GetPreAfn04F49( sMcAfn04f49 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f49";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	int i = 0;
	DWORD dwValue = 0;
	
	reg.Read("sTimeFrez.ucYY",  &dwValue);
	pData->sTimeFrez.ucYY = (UINT8)dwValue;
	
	reg.Read("sTimeFrez.ucMonth",  &dwValue);
	pData->sTimeFrez.ucMM = (UINT8)dwValue;

	reg.Read("sTimeFrez.ucDD",  &dwValue);
	pData->sTimeFrez.ucDD= (UINT8)dwValue;

	reg.Read("sTimeFrez.ucWW",  &dwValue);
	pData->sTimeFrez.ucWW= (UINT8)dwValue;

	reg.Read("sTimeFrez.ucHH",  &dwValue);
	pData->sTimeFrez.ucHH= (UINT8)dwValue;

	reg.Read("sTimeFrez.ucmm",  &dwValue);
	pData->sTimeFrez.ucmm= (UINT8)dwValue;

	reg.Read("sTimeFrez.ucss",  &dwValue);
	pData->sTimeFrez.ucss= (UINT8)dwValue;
	
	reg.Read("sTimeRprt.ucYY",  &dwValue);
	pData->sTimeRprt.ucYY= (UINT8)dwValue;

	reg.Read("sTimeRprt.ucMonth",  &dwValue);
	pData->sTimeRprt.ucMM= (UINT8)dwValue;

	reg.Read("sTimeRprt.ucDD",  &dwValue);
	pData->sTimeRprt.ucDD= (UINT8)dwValue;

	reg.Read("sTimeRprt.ucWW",  &dwValue);
	pData->sTimeRprt.ucWW= (UINT8)dwValue;

	reg.Read("sTimeRprt.ucHH",  &dwValue);
	pData->sTimeRprt.ucHH = (UINT8)dwValue;

	reg.Read("sTimeRprt.ucmm",  &dwValue);
	pData->sTimeRprt.ucmm = (UINT8)dwValue;

	reg.Read("sTimeRprt.ucss",  &dwValue);
	pData->sTimeRprt.ucss = (UINT8)dwValue;
	
	reg.Read("sFreez.ucTimes",  &dwValue);
	pData->sFreez.ucTimes= (UINT8)dwValue;

	reg.Read("sFreez.eUnit",  &dwValue);
	pData->sFreez.eUnit= (eMcPeriodUnit)dwValue;
	reg.Read("sFreez.usPeriod", &dwValue );
	pData->sFreez.usPeriod= (UINT16)dwValue;
	
	reg.Read("eUnitRpt",  &dwValue);
	pData->eUnitRpt = (eMcPeriodUnit)dwValue;

	reg.Read("uCmdPnNum", &dwValue );
	pData->uCmdPnNum = (UINT8)dwValue;

	reg.Read("ucPeriodRpt", &dwValue );
	pData->ucPeriodRpt = (UINT8)dwValue;


	
	CString strKeyfn, strKeyPn;
	for (i = 0; i < pData->uCmdPnNum; i++)
	{
		strKeyfn.Format("sCmdPn[%d].eCmd", i);
		strKeyPn.Format("sCmdPn[%d].usPn", i);
		
		reg.Read(strKeyfn,  &dwValue);
		pData->sCmdPn[i].eCmd = (eMcmd)dwValue;
		reg.Read(strKeyPn,  &dwValue);
		pData->sCmdPn[i].usPn = (UINT16)dwValue;
	}
	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F17( sMcAfn04f17 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f17";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	int i = 0;
	UINT8 regcode[7] = {0};
	CString strValue;
	DWORD dwValue;
	reg.Write("ucDownPort",  pData->ucDownPort);
	reg.Write("usListenPort",  pData->usListenPort);
	reg.Write("eUpPara",  pData->eUpPara);
	
	// regcode
	memcpy(regcode, pData->sUpAddr.acRegionCode, 6);
	strValue.Format("%s", regcode);
	reg.Write("sUpAddr.acRegionCode",  strValue);
	
	dwValue = pData->sUpAddr.ulConAddress;
	reg.Write("sUpAddr.ulConAddress",  dwValue);
	reg.Write("sUpAddr.bTeam",  pData->sUpAddr.bTeam);
	reg.Write("sUpAddr.ucMstAddress",  pData->sUpAddr.ucMstAddress);
	
	pData->ucUpProto = 1;
	reg.Write("ucUpProto",  pData->ucUpProto);
	
	reg.Write("sUpIp.ip[0]",  pData->sUpIp.ip[0]);
	reg.Write("sUpIp.ip[1]",  pData->sUpIp.ip[1]);
	reg.Write("sUpIp.ip[2]",  pData->sUpIp.ip[2]);
	reg.Write("sUpIp.ip[3]",  pData->sUpIp.ip[3]);
					
	reg.Write("sUpMask.ip[0]",  pData->sUpMask.ip[0]);
	reg.Write("sUpMask.ip[1]",  pData->sUpMask.ip[1]);
	reg.Write("sUpMask.ip[2]",  pData->sUpMask.ip[2]);
	reg.Write("sUpMask.ip[3]",  pData->sUpMask.ip[3]);


	reg.Write("sGateIp.ip[0]",  pData->sGateIp.ip[0]);
	reg.Write("sGateIp.ip[1]",  pData->sGateIp.ip[1]);
	reg.Write("sGateIp.ip[2]",  pData->sGateIp.ip[2]);
	reg.Write("sGateIp.ip[3]",  pData->sGateIp.ip[3]);

	reg.Write("sDelgIp.ip[0]",  pData->sDelgIp.ip[0]);
	reg.Write("sDelgIp.ip[1]",  pData->sDelgIp.ip[1]);
	reg.Write("sDelgIp.ip[2]",  pData->sDelgIp.ip[2]);
	reg.Write("sDelgIp.ip[3]",  pData->sDelgIp.ip[3]);

	reg.Write("eDelegate",  pData->eDelegate);
	reg.Write("eDelgLink",  pData->eDelgLink);
	reg.Write("bDlegUsr",  pData->bDlegUsr);
	reg.Write("ucDlegUsrLen",  pData->ucDlegUsrLen);
	
	reg.Write("usDelgPort",  pData->usDelgPort);
	
	UINT8    ucDlegUsr[22] = {0};
	memcpy(ucDlegUsr, pData->ucDlegUsr, pData->ucDlegUsrLen);
	strValue.Format("%s", ucDlegUsr);
	reg.Write("ucDlegUsr",  strValue);
	reg.Write("bDlegPwd",  pData->bDlegPwd);
	reg.Write("ucDlegPwdLen",  pData->ucDlegPwdLen);
	
	UINT8    ucDlegPwd[22] = {0};
	memcpy(ucDlegPwd, pData->ucDlegPwd, pData->ucDlegPwdLen);
	strValue.Format("%s", ucDlegPwd);
	reg.Write("ucDlegPwd",  strValue);
	reg.Write("ucPermitDelayM",  pData->ucPermitDelayM);
	reg.Write("ucReSendTimes",  pData->ucReSendTimes);
	reg.Write("ucHeartBeat",  pData->ucHeartBeat);

	reg.Write("usWaitTimeoutS",  pData->usWaitTimeoutS);
	reg.Write("bPermitTk",  pData->bPermitTk);
	reg.Write("bPermitRt",  pData->bPermitRt);

	reg.Write("bPermitEv",  pData->bPermitEv);
		
    return TRUE;
}

BOOL CNxConfig::GetPreAfn04F17( sMcAfn04f17 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f17";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	
	int i = 0;
	CString strValue;
	DWORD dwValue;
	reg.Read("usDelgPort",  &dwValue);
	pData->usDelgPort = (UINT16)dwValue;

	reg.Read("ucDownPort",  &dwValue);
	pData->ucDownPort = (UINT8)dwValue;

	reg.Read("usListenPort",  &dwValue);
	pData->usListenPort = (UINT8)dwValue;

	reg.Read("eUpPara",  &dwValue);
	pData->eUpPara = (eMcUpPara)dwValue;
	
	// regcode
	
	reg.Read("sUpAddr.acRegionCode",  &strValue);
	memcpy(pData->sUpAddr.acRegionCode, strValue.GetBuffer(strValue.GetLength()), strValue.GetLength());
	strValue.ReleaseBuffer();

	reg.Read("sUpAddr.ulConAddress",  &dwValue);
	pData->sUpAddr.ulConAddress = dwValue;

	reg.Read("sUpAddr.bTeam",  &pData->sUpAddr.bTeam);
	reg.Read("sUpAddr.ucMstAddress",  &dwValue);
	pData->sUpAddr.ucMstAddress = (UINT8)dwValue;
	
	pData->ucUpProto = 1;
	//reg.Read("ucUpProto",  pData->ucUpProto);
	
	reg.Read("sUpIp.ip[0]",  &dwValue);
	pData->sUpIp.ip[0] = (UINT8)dwValue;
	
	reg.Read("sUpIp.ip[1]",  &dwValue);
	pData->sUpIp.ip[1] = (UINT8)dwValue;
	
	reg.Read("sUpIp.ip[2]",  &dwValue);
	pData->sUpIp.ip[2] = (UINT8)dwValue;
	
	reg.Read("sUpIp.ip[3]",  &dwValue);
	pData->sUpIp.ip[3] = (UINT8)dwValue;
	
	pData->sUpIp.eVersion = MC_IP_V4;
	
	reg.Read("sUpMask.ip[0]",  &dwValue);
	pData->sUpMask.ip[0] = (UINT8)dwValue;
	
	reg.Read("sUpMask.ip[1]",  &dwValue);
	pData->sUpMask.ip[1] = (UINT8)dwValue;
	
	reg.Read("sUpMask.ip[2]",  &dwValue);
	pData->sUpMask.ip[2] = (UINT8)dwValue;
	
	reg.Read("sUpMask.ip[3]",  &dwValue);
	pData->sUpMask.ip[3] = (UINT8)dwValue;
	pData->sUpMask.eVersion = MC_IP_V4;
	
	
	reg.Read("sGateIp.ip[0]",  &dwValue);
	pData->sGateIp.ip[0] = (UINT8)dwValue;
	
	reg.Read("sGateIp.ip[1]",  &dwValue);
	pData->sGateIp.ip[1] = (UINT8)dwValue;
	
	reg.Read("sGateIp.ip[2]",  &dwValue);
	pData->sGateIp.ip[2] = (UINT8)dwValue;
	
	reg.Read("sGateIp.ip[3]",  &dwValue);
	pData->sGateIp.ip[3] = (UINT8)dwValue;
	pData->sGateIp.eVersion = MC_IP_V4;
	
	reg.Read("sDelgIp.ip[0]",  &dwValue);
	pData->sDelgIp.ip[0] = (UINT8)dwValue;
	
	reg.Read("sDelgIp.ip[1]",  &dwValue);
	pData->sDelgIp.ip[1] = (UINT8)dwValue;
	
	reg.Read("sDelgIp.ip[2]",  &dwValue);
	pData->sDelgIp.ip[2] = (UINT8)dwValue;
	
	reg.Read("sDelgIp.ip[3]",  &dwValue);
	pData->sDelgIp.ip[3] = (UINT8)dwValue;
	pData->sDelgIp.eVersion = MC_IP_V4;
	


	reg.Read("eDelegate",  &dwValue);
	pData->eDelegate = (eMcDelegate)dwValue;

	reg.Read("eDelgLink",  &dwValue);
	pData->eDelgLink = (eMcDelgLink)dwValue;

	reg.Read("bDlegUsr",  &pData->bDlegUsr);
	reg.Read("ucDlegUsrLen",  &dwValue);
	pData->ucDlegUsrLen = (UINT8)dwValue;
	
	
	
	reg.Read("ucDlegUsr",  &strValue);
	memset(pData->ucDlegUsr, 0, 20);
	memcpy(pData->ucDlegUsr, strValue.GetBuffer(strValue.GetLength()), strValue.GetLength());
	strValue.ReleaseBuffer();

	reg.Read("bDlegPwd",  &pData->bDlegPwd);
	reg.Read("ucDlegPwdLen",  &dwValue);
	pData->ucDlegPwdLen = (UINT8)dwValue;
	
	
	reg.Read("ucDlegPwd",  &strValue);
	memset(pData->ucDlegPwd, 0, 20);
	memcpy(pData->ucDlegPwd, strValue.GetBuffer(strValue.GetLength()), strValue.GetLength());
	strValue.ReleaseBuffer();
	
	reg.Read("ucPermitDelayM",  &dwValue);
	pData->ucPermitDelayM = (UINT8)dwValue;

	reg.Read("ucReSendTimes",  &dwValue);
	pData->ucReSendTimes = (UINT8)dwValue;

	reg.Read("ucHeartBeat",  &dwValue );
	pData->ucHeartBeat = (UINT8)dwValue;
	
	reg.Read("usWaitTimeoutS",  &dwValue);
	pData->usWaitTimeoutS = (UINT8)dwValue;

	reg.Read("bPermitTk",  &pData->bPermitTk);
	reg.Read("bPermitRt", &pData->bPermitRt );
	reg.Read("bPermitEv",  &pData->bPermitEv);
	return TRUE;
}

BOOL CNxConfig::SetPreAfn04F6( sMcAfn04f6 *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn04f6";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	int i = 0;
	CString str_key;
	CString strValue;
	DWORD dwValue = 0;
	char buf[8] = {0};


	reg.Write("eType", pData->eType);
	reg.Write("sSer.eBaud", pData->sSer.eBaud);
	reg.Write("sSer.bStop1", pData->sSer.bStop1);
	reg.Write("sSer.bCheck", pData->sSer.bCheck);
	reg.Write("sSer.bOdd", pData->sSer.bOdd);
	reg.Write("sSer.eBit", pData->sSer.eBit);
	reg.Write("ucWaitP", pData->ucWaitP);
	reg.Write("ucWaitC", pData->ucWaitC);
	reg.Write("ucReTry", pData->ucReTry);
	reg.Write("ucPeriod", pData->ucPeriod);
	reg.Write("bCasc", pData->bCasc);
	reg.Write("ucN", pData->ucN);
	for (i = 0; i < pData->ucN; i++)
	{
		// regionCode
		memset(buf, 0, 8);
		memcpy(buf, pData->sOne[i].acRegionCode, 6);
		strValue.Format("%s", buf);

		str_key.Format("sOne[%d].acRegionCode", i);
		reg.Write(str_key, strValue);

		// ulConAddr
		dwValue = pData->sOne[i].ulConAddr;
		str_key.Format("sOne[%d].ulConAddr", i);
		reg.Write(str_key, dwValue);

		// ulConAddr
		str_key.Format("sOne[%d].usPort", i);
		reg.Write(str_key, pData->sOne[i].usPort);

		// ip
		/*
		str_key.Format("sOne[%d].sIp.ip[0]", i);
		reg.Write(str_key, pData->sOne[i].sIp.ip[0]);

		str_key.Format("sOne[%d].sIp.ip[1]", i);
		reg.Write(str_key, pData->sOne[i].sIp.ip[1]);

		str_key.Format("sOne[%d].sIp.ip[2]", i);
		reg.Write(str_key, pData->sOne[i].sIp.ip[2]);

		str_key.Format("sOne[%d].sIp.ip[3]", i);
		reg.Write(str_key, pData->sOne[i].sIp.ip[3]);
		*/


		str_key.Format("sOne[%d].sIp.ip", i);
		strValue.Format("%d.%d.%d.%d", 
			pData->sOne[i].sIp.ip[0],
			pData->sOne[i].sIp.ip[1],
			pData->sOne[i].sIp.ip[2],
			pData->sOne[i].sIp.ip[3]);

		reg.Write(str_key, strValue);
	}


	return TRUE;
	
}

BOOL CNxConfig::GetPreAfn04F6( sMcAfn04f6 *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn04f6";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}

	int i = 0;
	CString str_key;
	CString strValue;
	DWORD dwValue = 0;
	char buf[8] = {0};


	reg.Read("eType", &dwValue);
	pData->eType = (eMcTypeCasc)dwValue;

	reg.Read("sSer.eBaud", &dwValue);
	pData->sSer.eBaud = (eMcSerBaud)dwValue;

	reg.Read("sSer.bStop1", &pData->sSer.bStop1);
	reg.Read("sSer.bCheck", &pData->sSer.bCheck);
	reg.Read("sSer.bOdd", &pData->sSer.bOdd);
	reg.Read("sSer.eBit", &dwValue);
	pData->sSer.eBit = (eMcSerBit)dwValue;

	reg.Read("ucWaitP", &dwValue);
	pData->ucWaitP = (UINT8)dwValue;
		
	reg.Read("ucWaitC", &dwValue);
	pData->ucWaitC = (UINT8)dwValue;


	reg.Read("ucReTry", &dwValue);
	pData->ucReTry = (UINT8)dwValue;

	reg.Read("ucPeriod", &dwValue);
	pData->ucPeriod = (UINT8)dwValue;
	
	
	reg.Read("bCasc", &pData->bCasc);
	reg.Read("ucN", &dwValue);
	pData->ucN = (UINT8)dwValue;
	for (i = 0; i < pData->ucN; i++)
	{
		// regionCode
		str_key.Format("sOne[%d].acRegionCode", i);
		reg.Read(str_key, &strValue);
		memcpy(pData->sOne[i].acRegionCode, strValue.GetBuffer(6), 6);
		strValue.ReleaseBuffer();

		// ulConAddr
		str_key.Format("sOne[%d].ulConAddr", i);
		reg.Read(str_key, &dwValue);
		pData->sOne[i].ulConAddr = dwValue;

		// ulConAddr
		str_key.Format("sOne[%d].usPort", i);
		reg.Read(str_key, &dwValue);
		pData->sOne[i].usPort = (UINT16)dwValue;

		// ip
		/*
		str_key.Format("sOne[%d].sIp.ip[0]", i);
		reg.Read(str_key, pData->sOne[i].sIp.ip[0]);

		str_key.Format("sOne[%d].sIp.ip[1]", i);
		reg.Read(str_key, pData->sOne[i].sIp.ip[1]);

		str_key.Format("sOne[%d].sIp.ip[2]", i);
		reg.Read(str_key, pData->sOne[i].sIp.ip[2]);

		str_key.Format("sOne[%d].sIp.ip[3]", i);
		reg.Read(str_key, pData->sOne[i].sIp.ip[3]);
		*/

		str_key.Format("sOne[%d].sIp.ip", i);
		reg.Read(str_key, &strValue);
		pData->sOne[i].sIp.ip[0] = GetIpNum(strValue, 0);
		pData->sOne[i].sIp.ip[1] = GetIpNum(strValue, 1);
		pData->sOne[i].sIp.ip[2] = GetIpNum(strValue, 2);
		pData->sOne[i].sIp.ip[3] = GetIpNum(strValue, 3);
		pData->sOne[i].sIp.eVersion = MC_IP_V4;

	}

	return TRUE;
		
}

void CNxConfig::SetPrePn31( eMcmd eCmd, eMcRole eRole,UINT16 *pusPN, UINT8 ucNum, BOOL bReWrite /*= TRUE*/ )
{
	if(!pusPN)
	{
		return;
	}
	
	CRegistry reg;
	CString   strPn = "pn";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if(eRole == MT_ROLE_CONTOR)
	{
		reg.Open(m_tmlPreName);
	}
	else
	{
		reg.Open(m_mstPreName);
	}
	
	
	
	if(reg.bKeyExists(strPn, NULL) == FALSE)
	{
		reg.CreateKey(strPn);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return;
		}
		reg.Open(strPn);
	}
	
	// name
	CString strName;
	CString strValue, strValueTmp;
	strName.Format("PN%04X", (UINT16)eCmd);
	
	// value
	int i = 0;
	for(i = 0; i < ucNum; i++)
	{
		strValueTmp.Format("%d,", (UINT16)pusPN[i]);
		strValue += strValueTmp;
	}
	
	reg.Write(strName,strValue);
}

BOOL CNxConfig::SetPreAfn0aF2q( sMcAfn11f2q *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn0af2q";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	

	int i =0;
	CString str_key;

	reg.Write("ucN", pData->ucN);

	for (i = 0; i < pData->ucN; i++)
	{
		str_key.Format("ucID[%d]", i);
		reg.Write(str_key, pData->ucID[i]);
	}


	return TRUE;
}

BOOL CNxConfig::SetPreAfn0aF7q( sMcAfn10f7q *pData, BOOL bMaster, BOOL bReWrite /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKey = "afn0af7q";
	
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKey, NULL) == FALSE)
	{
		reg.CreateKey(strKey);
	}
	else
	{
		if(bReWrite == FALSE)
		{
			return FALSE;
		}
		
		reg.Open(strKey);
	}
	
	
	int i =0;
	CString str_key;
	
	reg.Write("usN", pData->usN);
	
	for (i = 0; i < pData->usN; i++)
	{
		str_key.Format("usPort[%d]", i);
		reg.Write(str_key, pData->usPort[i]);
	}
	
	
	return TRUE;
}
BOOL CNxConfig::GetPreAfn0aF2q( sMcAfn11f2q *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn0af2q";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	

	int i =0;
	CString str_key;
	DWORD dwValue = 0;
	reg.Read("ucN", &dwValue);
	pData->ucN = (UINT8)dwValue;
	
	for (i = 0; i < pData->ucN; i++)
	{
		str_key.Format("ucID[%d]", i);
		reg.Read(str_key, &dwValue);
		 pData->ucID[i] = (UINT8)dwValue;
	}
	

	return TRUE;
}

BOOL CNxConfig::GetPreAfn0aF7q( sMcAfn10f7q *pData, BOOL bMaster /*= TRUE*/ )
{
	if(pData == NULL)
	{
		return FALSE;
	}
	
	CRegistry reg;
	CString   strKeyName = "afn0af7q";
	reg.SetRootKey(m_hRootKey);
	reg.Open("software");
	reg.Open(m_rootName);
	if (bMaster == TRUE)
	{
		reg.Open(m_mstPreName);
	}
	else
	{
		reg.Open(m_tmlPreName);
	}
	
	if(reg.bKeyExists(strKeyName, NULL) == FALSE)
	{
		return FALSE;
	}
	else
	{
		reg.Open(strKeyName);
	}
	
	
	int i =0;
	CString str_key;
	DWORD dwValue = 0;
	reg.Read("usN", &dwValue);
	pData->usN = (UINT16)dwValue;
	
	for (i = 0; i < pData->usN; i++)
	{
		str_key.Format("usPort[%d]", i);
		reg.Read(str_key, &dwValue);
		pData->usPort[i] = (UINT16)dwValue;
	}
	
	
	return TRUE;
}

void CNxConfig::trans_zigbee( bool strtobuf, CString &strZigbee, char*bufZigbee )
{
	
	int i =0;
	int j = 0;
	char hi = 0;
	char lw = 0;
	char num = 0;
	int len ;
		char zigbee_hex[17] = {0};
	
	if(strtobuf == true)
	{
		memset(bufZigbee, 0, 8);
		len = strZigbee.GetLength();
	
		memcpy(zigbee_hex, strZigbee.GetBuffer(len), len > 16 ? 16 : len);
		
		
		len = HexStringToString((unsigned char*)bufZigbee, 8, zigbee_hex);
		if(len)
		{

		}
	}
	else
	{
		
		ConverToHexString(zigbee_hex, bufZigbee, 8);
		
		strZigbee.Format("%s", zigbee_hex);

	}
	
}

unsigned char CNxConfig::GetCharValue( char cAscii )
{
	unsigned char cRt = 0;
	for (int i = 0 ; i < 22; i++)
	{
		if (c2a[i].c == cAscii)
			return c2a[i].bValue;
	}
	return cRt;
}

void CNxConfig::ConverToHexString( char *strHexData, const char* pszSrc, int nLen )
{
	int j = 0;
	for (int i = 0; i < nLen; i++)
	{
		j = 2 * i;
		char szBuf[3] = {0};
        sprintf(szBuf, "%02X", (unsigned char)pszSrc[i]);
        strHexData[j]   = szBuf[0];
		strHexData[j+1] = szBuf[1];
 }
}

int CNxConfig::HexStringToString( unsigned char* strDest, int nDestLen, const char* pszHexSrc )
{
	int nRt = 0;
	
	if (NULL == pszHexSrc)
	{
		return 0;
	}
	
	int nLen = strlen(pszHexSrc);
	if (nLen == 0 || nLen % 2 != 0)
	{
		return 0;
	}
    for (int i = 0; i < nLen; i++)
	{  
		if (nRt > nDestLen)
		{
			return 0;
		}
        strDest[nRt] = GetCharValue(pszHexSrc[i]) * 16;
		strDest[nRt] += GetCharValue(pszHexSrc[++i]);
		nRt++;  
	}
	return nRt;
}
