#if !defined(AFX_TABDLGPACK_H__C3A4D187_2937_467B_A586_E02A5B1FE52B__INCLUDED_)
#define AFX_TABDLGPACK_H__C3A4D187_2937_467B_A586_E02A5B1FE52B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlgPack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPack dialog
#include "NxConfig.h"
#include "FontColorTree.h"
//#include "NxRuler.h"
#include "Qgdw3761api.h"
#include "Gbnx_31.h"

#include "BtnST.h"
#include "ShadeButtonST.h"

class CNxMasterDlg;
class CTabDlgPack : public CDialog
{
// Construction
public:
	CTabDlgPack(CWnd* pParent = NULL);   // standard constructor
	void BuildFnTree(int index);
	void BuildFnTree();
	void BuildFnList(eMtAFN  eAFN);
	void setMainDlg(CNxMasterDlg *pNxMstDlg);
	void showEcPwTp(int index, eMtDir eDir);
	void showEcPwTp(BOOL bMaster);
	void showCmdTypes(int index); // 显示该命令的信息及从站应回复的规约类型
	void showCmdType();
	void showCurTime();
	void GetCtrlTp(sMtTP *psTP); // 获得控件上的TP
	void GetCtrlTp31(sMcTp *psTP); // 获得控件上的TP
	void GetCtrlEc();
	void GetCtrlPw(char *pw);
	int  GetAutoResponseDelaySecond();
	HTREEITEM m_hItemSel; // 当前树型控制右键菜单选择的节点
public :
	BOOL m_bTP;
	BOOL m_bEC;
	BOOL m_bPW;

private:
	void ShowPreInfor(BOOL bMaster = TRUE);  // 将预配的地址消息显示在控件上
	int m_cur_index;
	CString m_strName[AFN_11_MAX];
	CNxMasterDlg *m_pNxMstDlg;
	void ClickFnTreeSelect();  //鼠标点击条目勾选 
	void EnableEditBoxTp(BOOL bEnable);
	void EnableEditBoxPw(BOOL bEnable);
	void EnableEditBoxEc(BOOL bEnable);
	void setPosCtrls(); // 动态调整控件位置
	void GetCtrlsPack(); /// 获取控件上的信息然后打包
	eMcAFN GetAfnSelect(); // 获取当前选择的Afn
	BOOL   bGetActive(eMtAFN eAfn, eMtDir eDir); // 获得当前报文是主动站还是从站
	BOOL   GetfnSelectAndPreApp(sMtData *psMtData, UINT16 *pucNum, eMtDir eDir);  // 获取combo fn 及注册表中预配的数据封装命令 
	BOOL   GetfnSelectAndPreApp31(sMcData *psData, UINT16 *pucNum, eMcDir eDir, eMcPRM ePrm, eMcFcode *peFcode, BOOL *bFixed);  // 获取combo fn 及注册表中预配的数据封装命令 
	UINT8  getStrItemFn(CString str);

	eMtCmd GetCmdAfnFn(eMtAFN eAfn, UINT8 ucFn);
	eMcmd GetCmdAfnFn31(eMcAFN eAfn, UINT8 ucFn);

	BOOL   bFillCmdApp(sMtData *psMtData, UINT16 usPn, eMtCmd eCmd, eMtDir eDir); // 3761
	BOOL   bFillCmdApp31(sMcData *psData, UINT16 usPn, eMcmd eCmd, eMcDir eDir);
	void   vFree(char *pMem);
	void ChangAddr();

	CMenu m_PopMenu;


// Dialog Data
	//{{AFX_DATA(CTabDlgPack)
	enum { IDD = IDD_DLG_PACK };
	CButton	m_check_auto;
	CButton	m_check_text;
	CButton	m_check_send_instant;
	CButton	m_check_into_send;
	CButton	m_check_into_task;
	CButton	m_check_auto_tp;
	CButton	m_check_team;
	CStatic	m_static_s2m;
	CStatic	m_static_res;
	CStatic	m_static_m2s;
	//CButton	m_btn_get_cmd;
	CShadeButtonST m_btn_get_cmd;
	CEdit	m_edit_cmd_result;
	CListBox	m_fnList;
	CTreeCtrl	m_fnTree;
	CComboBox	m_combo_afn;
	int		m_edit_ec2;
	int		m_edit_ec1;
	int		m_edit_mst_addr;
	int		m_edit_tml_addr;
	int		m_edit_zone_code;
	CString	m_edit_pw;
	CString	m_edit_tp_day;
	CString	m_edit_tp_hour;
	CString	m_edit_tp_minute;
	CString	m_edit_tp_second;
	int		m_edit_pfc;
	int		m_ucPermitDelayMinutes;
	int		m_edit_auto_response_delay;
	int		m_edit_pseq;
	int		m_edit_rseq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlgPack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	// 要修改数据的节点的数据信息
	eMcPn   m_pnType_modify;
	eMcDir  m_eDir_Modify;
	eMcmd   m_eCmd_Modify;
	BOOL    m_bMaster_modify;
	sMcmdInfor m_cmdInfor;
	CString m_strName_modify;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDlgPack)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboAfn();
	virtual void OnOK();
	afx_msg void OnRdblclkTreeFn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeFn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnGetCmd();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckIntoSend();
	afx_msg void OnCheckTpAuto();
	afx_msg void OnChangeEditTmlAddr();
	afx_msg void OnChangeEditZoneCode();
	afx_msg void OnChangeEditMstAddr();
	afx_msg void OnCheckTeam();
	afx_msg void OnRclickTreeFn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemCheck();
	afx_msg void OnItemUncheck();
	afx_msg void OnSetPre();
	afx_msg void OnSetPrePn();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLGPACK_H__C3A4D187_2937_467B_A586_E02A5B1FE52B__INCLUDED_)
