#if !defined(AFX_DLGPREAFN04F17_H__3C4B0170_D184_4E39_929C_C8E2EA006241__INCLUDED_)
#define AFX_DLGPREAFN04F17_H__3C4B0170_D184_4E39_929C_C8E2EA006241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F17.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F17 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

typedef enum
{
	TUPP_DEL,                 // 删除该监测终端号的配置参数
	TUPP_SER,                 // 串口
	TUPP_ETH,                 // 以太网
	TUPP_MAX,
		
}eMcUpPara_index;                     // 监测终端上行通信端口属性

typedef enum
{
	INDEX_DELG_NULL,    // 不使用代理
		INDEX_DELG_HTTP,    // 
		INDEX_DELG_SOCK4,   //
		INDEX_DELG_SOCK5,   // 
		INDEX_DELG_MAX,
		
}index_eDelegate;

class CDlgPreAfn04F17 : public CDialog
{
	// Construction
public:
	CDlgPreAfn04F17(CWnd* pParent = NULL);   // standard constructor
	CString m_strUpPara[TUPP_MAX];
	CString m_strDelegate[INDEX_DELG_MAX];
	BOOL m_bPreMaster;
	void SetNewValues();
	void GetCurValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F17)
	enum { IDD = IDD_DLG_PRE_AFN04_F17 };
	CIPAddressCtrl	m_ip_sUpMask;
	CIPAddressCtrl	m_ip_sUpIp;
	CIPAddressCtrl	m_ip_sGateIp;
	CIPAddressCtrl	m_ip_sDelgIp;
	CComboBox	m_cmb_eUpPara;
	CComboBox	m_cmb_eDelegate;
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	UINT	m_edit_heart_beat;
	UINT	m_edit_resent_times;
	UINT	m_edit_sUpAddr_ConAddr;
	CString	m_edit_sUpAddr_RegCode;
	UINT	m_edit_sUpAddr_TerAddr;
	UINT	m_edit_wait_timeout;
	CString	m_edit_ucDlegPwd;
	CString	m_edit_ucDlegUsr;
	UINT	m_edit_usDelgPort;

	UINT	m_edit_ucDownPort;
	UINT	m_edit_ucPermitDelayM;
	UINT	m_edit_usListenPort;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F17)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F17)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEDITucDownPort();
	afx_msg void OnChangeEDITsUpAddrConAddr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F17_H__3C4B0170_D184_4E39_929C_C8E2EA006241__INCLUDED_)
