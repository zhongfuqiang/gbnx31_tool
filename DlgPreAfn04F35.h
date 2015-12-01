#if !defined(AFX_DLGPREAFN04F35_H__C42C558B_AED6_4B7C_920A_F8C59F638229__INCLUDED_)
#define AFX_DLGPREAFN04F35_H__C42C558B_AED6_4B7C_920A_F8C59F638229__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F35.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F35 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn04F35 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F35(CWnd* pParent = NULL);   // standard constructor
	CString  m_strPrecise[MC_PREC_N3];
	BOOL     m_bMaster;
	eMcNElcType m_eNelctype;
	void     SetNelcType(eMcNElcType eNelctype);
	void     GetNelcType(eMcNElcType &eNelctype);
	void     GetCurValues();
	void     SetNewValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F35)
	enum { IDD = IDD_DLG_PRE_AFN04_F35 };
	CStatic	m_static_info2;
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	CStatic	m_static_info;
	CEdit	m_edit_up;
	CEdit	m_edit_dn;
	CComboBox	m_comb_prec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F35)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F35)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokCmboPrec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F35_H__C42C558B_AED6_4B7C_920A_F8C59F638229__INCLUDED_)
