#if !defined(AFX_DLGPREAFN04F49_H__1D368CBD_0A8E_429D_9A63_06DDC8888F46__INCLUDED_)
#define AFX_DLGPREAFN04F49_H__1D368CBD_0A8E_429D_9A63_06DDC8888F46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F49.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F49 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
#include "ColorListCtrl.h"

typedef enum
{

	INDEX_AFN_D_F1_CLOCK,//日历时钟
	INDEX_AFN_D_F2_PARA_STATE,//参数状态标志
	INDEX_AFN_D_F3_EVENT_1,//重要事件计数器当前值
	INDEX_AFN_D_F4_EVENT_2,//一般事件计数器当前值
	INDEX_AFN_D_F5_EVENT_STATE,//事件状态标志
	INDEX_AFN_D_F6_POWR_TIMES,//上电次数

	//组2pn:p0/监测终端号
	INDEX_AFN_D_F9_STATE,//状态量及变位标志
	INDEX_AFN_D_F10_SWITCH,//控制输出回路开关接入状态量及变位标志

	//组4pn:p0/电气测量点号
	INDEX_AFN_D_F25_POWR_HAVE_T,//总有功功率
	INDEX_AFN_D_F26_POWR_NONE_T,//总无功功率
	INDEX_AFN_D_F27_FACTR_T,//总功率因数
	INDEX_AFN_D_F28_FACTR_A,//A相功率因素
	INDEX_AFN_D_F29_FACTR_B,//B相功率因数
	INDEX_AFN_D_F30_FACTR_C,//C相功率因数

	//组5pn:p0/电气测量点号
	INDEX_AFN_D_F33_DEMAND,//需量
	INDEX_AFN_D_F34_DEMAND_MAX,//日最大需量
	INDEX_AFN_D_F35_DEMAND_TIME,//日最大需量发生时间

	//组6pn:电气测量点号
	INDEX_AFN_D_F41_POWR_HAVE_A,//A相有功功率
	INDEX_AFN_D_F42_POWR_HAVE_B,//B相有功功率
	INDEX_AFN_D_F43_POWR_HAVE_C,//C相有功功率
	INDEX_AFN_D_F44_POWR_NONE_A,//A相无功功率
	INDEX_AFN_D_F45_POWR_NONE_B,//B相无功功率
	INDEX_AFN_D_F46_POWR_NONE_C,//C相无功功率

	//组7pn:电气测量点号
	INDEX_AFN_D_F49_POWR_HAVE_FRTH,//（正向）有功总电能示数
	INDEX_AFN_D_F50_POWR_HAVE_BACK,//（反向）有功总电能示数
	INDEX_AFN_D_F51_POWR_NONE_FRTH,//（正向）无功总电能示数
	INDEX_AFN_D_F52_POWR_NONE_BACK,//（反向）无功总电能示数

	//组8pn:电气测量点号
	INDEX_AFN_D_F57_VOLT_A,//A相电压
	INDEX_AFN_D_F58_VOLT_B,//B相电压
	INDEX_AFN_D_F59_VOLT_C,//C相电压
	INDEX_AFN_D_F60_VANGL_A,//A相电压相位角
	INDEX_AFN_D_F61_VANGL_B,//B相电压相位角
	INDEX_AFN_D_F62_VANGL_C,//C相电压相位角
	INDEX_AFN_D_F63_VOLT_UBL,//电压不平衡度
	INDEX_AFN_D_F64_CIRCLE_V0,//周波

	//组9pn:电气测量点号
	INDEX_AFN_D_F65_ELEC_A,//A相电流
	INDEX_AFN_D_F66_ELEC_B,//B相电流
	INDEX_AFN_D_F67_ELEC_C,//C相电流
	INDEX_AFN_D_F68_ELEC_M,//中性线电流
	INDEX_AFN_D_F69_EANGL_A,//A相电流相位角
	INDEX_AFN_D_F70_EANGL_B,//B相电流相位角
	INDEX_AFN_D_F71_EANGL_C,//C相电流相位角
	INDEX_AFN_D_F72_ELEC_UBL,//电流不平衡度

	//组10pn:电气测量点号
	INDEX_AFN_D_F73_VDMAX_A,//日A相电压极大值
	INDEX_AFN_D_F74_VDMAX_A_TIME,//日A相电压极大值发生时间
	INDEX_AFN_D_F75_VDMAX_B,//日A相电压极大值
	INDEX_AFN_D_F76_VDMAX_B_TIME,//日A相电压极大值发生时间
	INDEX_AFN_D_F77_VDMAX_C,//日A相电压极大值
	INDEX_AFN_D_F78_VDMAX_C_TIME,//日A相电压极大值发生时间

	//组11pn:电气测量点号
	INDEX_AFN_D_F81_IDMAX_A,//日A相电流极大值
	INDEX_AFN_D_F82_IDMAX_A_TIME,//日A相电流极大值发生时间
	INDEX_AFN_D_F83_IDMAX_B,//日B相电流极大值
	INDEX_AFN_D_F84_IDMAX_B_TIME,//日B相电流极大值发生时间
	INDEX_AFN_D_F85_IDMAX_C,//日C相电流极大值
	INDEX_AFN_D_F86_IDMAX_C_TIME,//日C相电流极大值发生时间

	//组12pn:电气测量点号
	INDEX_AFN_D_F89_TFW_HAVE,//总基波有功功率(TotalFundamentalWave)
	INDEX_AFN_D_F90_TFW_NONE,//总基波无功功率
	INDEX_AFN_D_F91_THW_HAVE,//总谐波有功功率(TotalHarmonicWave)
	INDEX_AFN_D_F92_THW_NONE,//总基波无功功率

	//组13pn:电气测量点号
	INDEX_AFN_D_F97_VDPP_TIME_A,//A相电压越上上限日累计时间
	INDEX_AFN_D_F98_VDPP_TIME_B,//B相电压越上上限日累计时间
	INDEX_AFN_D_F99_VDPP_TIME_C,//C相电压越上上限日累计时间
	INDEX_AFN_D_F100_VDNN_TIME_A,//A相电压越下下限日累计时间
	INDEX_AFN_D_F101_VDNN_TIME_B,//B相电压越下下限日累计时间
	INDEX_AFN_D_F102_VDNN_TIME_C,//C相电压越下下限日累计时间

	//组14pn:电气测量点号
	INDEX_AFN_D_F105_VMPP_TIME_A,//A相电压越上上限月累计时间
	INDEX_AFN_D_F106_VMPP_TIME_B,//B相电压越上上限月累计时间
	INDEX_AFN_D_F107_VMPP_TIME_C,//C相电压越上上限月累计时间
	INDEX_AFN_D_F108_VMNN_TIME_A,//A相电压越下下限月累计时间
	INDEX_AFN_D_F109_VMNN_TIME_B,//B相电压越下下限月累计时间
	INDEX_AFN_D_F110_VMNN_TIME_C,//C相电压越下下限月累计时间

	//组15pn:电气测量点号(aberrance)
	INDEX_AFN_D_F113_VABR_TOTL_A,//A相电压总畸变率
	INDEX_AFN_D_F114_VABR_TOTL_B,//B相电压总畸变率
	INDEX_AFN_D_F115_VABR_TOTL_C,//C相电压总畸变率
	INDEX_AFN_D_F116_EABR_TOTL_A,//A相电流总畸变率
	INDEX_AFN_D_F117_EABR_TOTL_B,//B相电流总畸变率
	INDEX_AFN_D_F118_EABR_TOTL_C,//C相电流总畸变率

	//组16pn:电气测量点号
	INDEX_AFN_D_F121_VABR_ODD_A,//A相电压奇次畸变率
	INDEX_AFN_D_F122_VABR_EVN_A,//A相电压偶次畸变率
	INDEX_AFN_D_F123_VABR_ODD_B,//B相电压奇次畸变率
	INDEX_AFN_D_F124_VABR_EVN_B,//B相电压偶次畸变率
	INDEX_AFN_D_F125_VABR_ODD_C,//C相电压奇次畸变率
	INDEX_AFN_D_F126_VABR_EVN_C,//C相电压偶次畸变率

	//组17pn:电气测量点号
	INDEX_AFN_D_F128_EABR_OOD_A0,//A相电流奇次畸变率
	INDEX_AFN_D_F129_EABR_EVN_A,//A相电流偶次畸变率
	INDEX_AFN_D_F130_EABR_OOD_B,//B相电流奇次畸变率
	INDEX_AFN_D_F131_EABR_EVN_B,//B相电流偶次畸变率
	INDEX_AFN_D_F132_EABR_OOD_C,//C相电流奇次畸变率
	INDEX_AFN_D_F133_EABR_EVN_C,//C相电流偶次畸变率

	//组18pn:电气测量点号
	INDEX_AFN_D_F137_FLS_SHRT_A,//A相短时闪变
	INDEX_AFN_D_F138_FLS_SHRT_B,//B相短时闪变
	INDEX_AFN_D_F139_FLS_SHRT_C,//C相短时闪变
	INDEX_AFN_D_F140_FLS_LONG_A,//A相长时闪变
	INDEX_AFN_D_F141_FLS_LONG_B,//B相长时闪变
	INDEX_AFN_D_F142_FLS_LONG_C,//C相长时闪变

	//组19pn:电气测量点号
	INDEX_AFN_D_F145_HARM_VOLT_A,//A相N次谐波电压
	INDEX_AFN_D_F146_HARM_VOLT_B,//B相N次谐波电压
	INDEX_AFN_D_F147_HARM_VOLT_C,//C相N次谐波电压
	INDEX_AFN_D_F148_HARM_ELEC_A,//A相N次谐波电流
	INDEX_AFN_D_F149_HARM_ELEC_B,//B相N次谐波电流
	INDEX_AFN_D_F150_HARM_ELEC_C,//C相N次谐波电流

	//组20pn:电气测量点号
	INDEX_AFN_D_F153_HARM_VINC_A,//A相N次谐波电压含有率
	INDEX_AFN_D_F154_HARM_VINC_B,//B相N次谐波电压含有率
	INDEX_AFN_D_F155_HARM_VINC_C,//C相N次谐波电压含有率
	INDEX_AFN_D_F156_HARM_EINC_A,//A相N次谐波电流含有率
	INDEX_AFN_D_F157_HARM_EINC_B,//B相N次谐波电流含有率
	INDEX_AFN_D_F158_HARM_EINC_C,//C相N次谐波电流含有率

	//组30pn:非电气测量点号
	INDEX_AFN_D_F233_NELC_VALUE,//非电气量
	
	INDEX_MCMD_MAX,

}eRealFnIndex; // 数据索引

typedef struct  
{
	eMcmd eCmd;
	CString sName;

}sRealCmdName;
 
typedef enum
{
	FREZ_MONTH,   // 月
	FREZ_DAY,     // 日
	FREZ_HOUR,    // 时
	FREZ_MIN,     // 分钟
	FREZ_SEC,     // 秒
	FREZ_MS,      // 毫秒
	FREZ_MAX	
}eUnitFrez_index;

typedef enum
{
	REPT_MONTH,   // 月
	REPT_DAY,     // 日
	REPT_HOUR,    // 时
	REPT_MIN,     // 分钟
	REPT_MAX

}eUnitRpt_index;



class CDlgPreAfn04F49 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F49(CWnd* pParent = NULL);   // standard constructor
	sRealCmdName m_cmdName[INDEX_MCMD_MAX];

	BOOL AddCmdPnList(sMcmdPn cmdPn);
	CString m_strFrezUint[FREZ_MAX];
	CString m_strReptUint[REPT_MAX];

	void GetCurValues();
	void SetNewValues();
	
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F49)
	enum { IDD = IDD_DLG_PRE_AFN04_F49 };
	CDateTimeCtrl	m_time_rept;
	CDateTimeCtrl	m_date_rept;
	CComboBox	m_cmb_rept_unit;
	CComboBox	m_cmb_frez_uint;
	CDateTimeCtrl	m_time_frez;
	CDateTimeCtrl	m_date_frez;
	CColorListCtrl	m_list;
	CComboBox	m_cmb_fn_add;
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	UINT	m_edit_pn;
	UINT	m_edit_frez_ucTimes;
	UINT	m_edit_Frez_usPeriod;
	UINT	m_edit_rept_ucPeriod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F49)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F49)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnEditchangeCmbFnAdd();
	afx_msg void OnSelendokCmbFnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F49_H__1D368CBD_0A8E_429D_9A63_06DDC8888F46__INCLUDED_)
