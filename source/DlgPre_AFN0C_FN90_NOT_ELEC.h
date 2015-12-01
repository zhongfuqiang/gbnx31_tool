#if !defined(AFX_DLGPRE_AFN0C_FN90_NOT_ELEC_H__3292C75F_910A_497B_AD0E_93D64C8BABD0__INCLUDED_)
#define AFX_DLGPRE_AFN0C_FN90_NOT_ELEC_H__3292C75F_910A_497B_AD0E_93D64C8BABD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPre_AFN0C_FN90_NOT_ELEC.h : header file
//
//#include "NxRuler.h"
#include "Qgdw3761api.h"
#include "NxConfig.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPre_AFN0C_FN90_NOT_ELEC dialog

class CDlgPreAfn0cF90_NotElec : public CDialog
{
private:
	CString m_type_name[7];
	BOOL  m_bMaster;
// Construction
public:
	CDlgPreAfn0cF90_NotElec(CWnd* pParent = NULL);   // standard constructor
    CString m_strTile;
	void setTitle(CString strTitle);
	void GetPreData();
	void SetPreData();
	void InitCombType();
	void setRole(BOOL bMaster = TRUE);
// Dialog Data
	//{{AFX_DATA(CDlgPre_AFN0C_FN90_NOT_ELEC)
	enum { IDD = IDD_DLG_PRE_AFN0C_F90_NOT_ELEC };
	CEdit	m_edit_value;
	CComboBox	m_comb_type;
	CEdit	m_edit_pn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPre_AFN0C_FN90_NOT_ELEC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CDlgPre_AFN0C_FN90_NOT_ELEC)
	afx_msg void OnButtonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRE_AFN0C_FN90_NOT_ELEC_H__3292C75F_910A_497B_AD0E_93D64C8BABD0__INCLUDED_)
