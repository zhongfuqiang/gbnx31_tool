#if !defined(AFX_DLGPREAFN0AF2_H__8FB80E83_F3B3_4031_88C2_5A31FF430A75__INCLUDED_)
#define AFX_DLGPREAFN0AF2_H__8FB80E83_F3B3_4031_88C2_5A31FF430A75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn0aF2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn0aF2 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn0aF2 : public CDialog
{
// Construction
public:
	CDlgPreAfn0aF2(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;
	void SetNew();
	void GetCur();
	UINT8  m_ucId[256];
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn0aF2)
	enum { IDD = IDD_DLG_PRE_AFN0A_F2 };
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	CTabCtrl	m_tab;
	UINT	m_edit_total;
	UINT	m_edit_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn0aF2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn0aF2)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditNumTotal();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN0AF2_H__8FB80E83_F3B3_4031_88C2_5A31FF430A75__INCLUDED_)
