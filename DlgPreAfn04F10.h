#if !defined(AFX_DLGPREAFN04F10_H__3268420E_13B8_4F50_A05D_C80603752798__INCLUDED_)
#define AFX_DLGPREAFN04F10_H__3268420E_13B8_4F50_A05D_C80603752798__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F10.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F10 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn04F10 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F10(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	CButton *m_pCheckIn[8];
	CButton *m_pCheckOn[8];
	void GetCurValues();
	void SetNewValues();

// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F10)
	enum { IDD = IDD_DLG_PRE_AFN04_F10 };
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F10)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F10)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F10_H__3268420E_13B8_4F50_A05D_C80603752798__INCLUDED_)
