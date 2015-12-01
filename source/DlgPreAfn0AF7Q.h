#if !defined(AFX_DLGPREAFN0AF7Q_H__502A21B2_5FFA_422F_9570_6E5D5D7F1CAA__INCLUDED_)
#define AFX_DLGPREAFN0AF7Q_H__502A21B2_5FFA_422F_9570_6E5D5D7F1CAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn0AF7Q.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn0AF7Q dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
class CDlgPreAfn0AF7Q : public CDialog
{
// Construction
public:
	CDlgPreAfn0AF7Q(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;
	void SetNew();
	void GetCur();
	UINT16  m_usPort[256];
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn0AF7Q)
	enum { IDD = IDD_DLG_PRE_AFN0A_F7 };
	CTabCtrl	m_tab;
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	UINT	m_edit_total;
	UINT	m_edit_usport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn0AF7Q)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn0AF7Q)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditNumTotal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN0AF7Q_H__502A21B2_5FFA_422F_9570_6E5D5D7F1CAA__INCLUDED_)
