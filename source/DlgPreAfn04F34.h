#if !defined(AFX_DLGPREAFN04F34_H__F5510BE1_5EE3_4CAD_9847_8090B37042F5__INCLUDED_)
#define AFX_DLGPREAFN04F34_H__F5510BE1_5EE3_4CAD_9847_8090B37042F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F34.h : header file
//

#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F34 dialog

class CDlgPreAfn04F34 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F34(CWnd* pParent = NULL);   // standard constructor

	CString  m_strPrecise[MC_PREC_N3];
	BOOL     m_bMaster;
	eMcNElcType m_eNelctype;
	void     SetNelcType(eMcNElcType eNelctype);
	void     GetNelcType(eMcNElcType &eNelctype);
	void     GetCurValues();
	void     SetNewValues();

		
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F34)
	enum { IDD = IDD_DLG_PRE_AFN04_F34 };
	CEdit	m_edit_up;
	CEdit	m_edit_dn;
	CStatic	m_static_info2;
	CStatic	m_static_info;
	CComboBox	m_comb_prec;
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F34)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F34)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeCmboPrec();
	afx_msg void OnSelendokCmboPrec();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F34_H__F5510BE1_5EE3_4CAD_9847_8090B37042F5__INCLUDED_)
