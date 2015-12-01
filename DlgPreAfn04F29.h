#if !defined(AFX_DLGPREAFN04F29_H__67E3F081_FEC9_480D_B53C_2136775826D0__INCLUDED_)
#define AFX_DLGPREAFN04F29_H__67E3F081_FEC9_480D_B53C_2136775826D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F29.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F29 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
class CDlgPreAfn04F29 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F29(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;
	void SetNewValues();
	void GetCurValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F29)
	enum { IDD = IDD_DLG_PRE_AFN04_F29 };
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	float	m_sIa_fEven;
	float	m_sIa_fOdd;
	float	m_sIa_fTotal;
	float	m_sIb_fEven;
	float	m_sIb_fOdd;
	float	m_sIb_fTotal;
	float	m_sIc_fEven;
	float	m_sIc_fOdd;
	float	m_sIc_fTotal;
	float	m_sVa_fEven;
	float	m_sVa_fOdd;
	float	m_sVa_fTotal;
	float	m_sVb_fEven;
	float	m_sVb_fOdd;
	float	m_sVb_fTotal;
	float	m_sVc_fEven;
	float	m_sVc_fOdd;
	float	m_sVc_fTotal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F29)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F29)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F29_H__67E3F081_FEC9_480D_B53C_2136775826D0__INCLUDED_)
