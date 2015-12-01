#if !defined(AFX_DLGPREAFN04F4_H__4BFEE2C7_E52E_4FDA_A074_ECF609F277C4__INCLUDED_)
#define AFX_DLGPREAFN04F4_H__4BFEE2C7_E52E_4FDA_A074_ECF609F277C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F4 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
class CDlgPreAfn04F4 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F4(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	void GetCurValues();
	void SetNewValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F4)
	enum { IDD = IDD_DLG_PRE_AFN04_F4 };
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	UINT	m_edit_team_1;
	UINT	m_edit_team_2;
	UINT	m_edit_team_3;
	UINT	m_edit_team_4;
	UINT	m_edit_team_5;
	UINT	m_edit_team_6;
	UINT	m_edit_team_7;
	UINT	m_edit_team_8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F4)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F4_H__4BFEE2C7_E52E_4FDA_A074_ECF609F277C4__INCLUDED_)
