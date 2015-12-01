#if !defined(AFX_DLGPREAFN04F7_H__34035F00_F706_41CB_B476_3DEBFE78ACFE__INCLUDED_)
#define AFX_DLGPREAFN04F7_H__34035F00_F706_41CB_B476_3DEBFE78ACFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F7.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F7 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn04F7 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F7(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	void GetCurValues();
	void SetNewValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F7)
	enum { IDD = IDD_DLG_PRE_AFN04_F7 };
	CIPAddressCtrl	m_ip_main;
	CIPAddressCtrl	m_ip_back;
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	UINT	m_edit_usMainPort;
	UINT	m_edit_usBackPort;
	CString	m_edit_ucUsr;
	CString	m_edit_ucPwd;
	UINT	m_edit_ucPort;
	CString	m_edit_ucApn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F7)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F7)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F7_H__34035F00_F706_41CB_B476_3DEBFE78ACFE__INCLUDED_)
