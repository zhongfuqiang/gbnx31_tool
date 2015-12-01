#if !defined(AFX_DLGPREPN_H__632E20B2_C361_4BE1_93CC_F7DF80708B27__INCLUDED_)
#define AFX_DLGPREPN_H__632E20B2_C361_4BE1_93CC_F7DF80708B27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrePn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrePn dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
#include "ColorListCtrl.h"
class CDlgPrePn : public CDialog
{
// Construction
public:
	CDlgPrePn(CWnd* pParent = NULL);   // standard constructor
	CString m_strTitle;
	void SetNew();
	void GetCur();
	void SetTitle(CString strT);
	void initList();
	sMcmdInfor m_cmdInfor;
	// Dialog Data
	//{{AFX_DATA(CDlgPrePn)
	enum { IDD = IDD_DIALOG_PN };
	CColorListCtrl	m_list_pn;
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	CString	m_static_type;
	CString	m_edit_pn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrePn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPrePn)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditPn();
	afx_msg void OnRclickListPn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnIdPnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREPN_H__632E20B2_C361_4BE1_93CC_F7DF80708B27__INCLUDED_)
