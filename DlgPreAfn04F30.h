#if !defined(AFX_DLGPREAFN04F30_H__A7ABC16C_72FC_4924_BA8E_BD459A1AC4EF__INCLUDED_)
#define AFX_DLGPREAFN04F30_H__A7ABC16C_72FC_4924_BA8E_BD459A1AC4EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F30.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F30 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
class CDlgPreAfn04F30 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F30(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;
	void SetNewValues();
	void GetCurValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F30)
	enum { IDD = IDD_DLG_PRE_AFN04_F30 };
	CShadeButtonST m_btn_no;
	CShadeButtonST	m_btn_ok;
	float	m_edit_fShort;
	float	m_edit_fLong;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F30)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F30)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F30_H__A7ABC16C_72FC_4924_BA8E_BD459A1AC4EF__INCLUDED_)
