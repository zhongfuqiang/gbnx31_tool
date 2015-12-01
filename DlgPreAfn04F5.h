#if !defined(AFX_DLGPREAFN04F5_H__7BD93C8C_7448_4D30_AE3D_B6586E794E17__INCLUDED_)
#define AFX_DLGPREAFN04F5_H__7BD93C8C_7448_4D30_AE3D_B6586E794E17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F5 dialog
#include "NxConfig.h"
#include "BtnST.h"
#include "ShadeButtonST.h"


typedef enum
{
	DELG_NULL,    // 不使用代理
		DELG_HTTP,    // 
		DELG_SOCK4,   //
		DELG_SOCK5,   // 
		DELG_MAX,
		
}eDelegate_index;

typedef enum
{
	DELK_ANYONE, // 无需要验证
    DELK_USRPWD, // 需要用户名和密码
	MC_DELK_MAX, // 

}eDelgLink_index;


class CDlgPreAfn04F5 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F5(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	CString m_strDelegate[DELG_MAX];
	CString m_strDelgLink[MC_DELK_MAX];
	void SetNewValues();
	void GetCurValues();

// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F5)
	enum { IDD = IDD_DLG_PRE_AFN04_F5 };
	CIPAddressCtrl	m_ip_sMask;
	CIPAddressCtrl	m_ip_sGateIp;
	CIPAddressCtrl	m_ip_sDelgIp;
	CIPAddressCtrl	m_ip_sConIP;
	CComboBox	m_comb_eDelegate;
	CEdit	m_edit_pwd;
	CEdit	m_edit_usr;
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	UINT	m_edit_usPort;
	UINT	m_edit_usDelgPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F5)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnSelendokCOMBOeDelegate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F5_H__7BD93C8C_7448_4D30_AE3D_B6586E794E17__INCLUDED_)
