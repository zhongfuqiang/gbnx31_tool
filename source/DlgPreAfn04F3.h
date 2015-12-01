#if !defined(AFX_DLGPREAFN04F3_H__865FA985_6EAE_4DAA_BF1C_F9520D4EF79A__INCLUDED_)
#define AFX_DLGPREAFN04F3_H__865FA985_6EAE_4DAA_BF1C_F9520D4EF79A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F3 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn04F3 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F3(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	void SetNewValues();
	void GetCurValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F3)
	enum { IDD = IDD_DLG_PRE_AFN04_F3 };
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	UINT	m_edit_para;
	UINT	m_edit_type_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F3)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTypeId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F3_H__865FA985_6EAE_4DAA_BF1C_F9520D4EF79A__INCLUDED_)
