#if !defined(AFX_DLGPREAFN04F9_H__54BAE3C0_B8F6_44ED_9C28_EBD1378292D1__INCLUDED_)
#define AFX_DLGPREAFN04F9_H__54BAE3C0_B8F6_44ED_9C28_EBD1378292D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F9.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F9 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn04F9 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F9(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	CButton *m_pStatic[20];
	CButton *m_pCheck[20];
	CButton *m_pRadioN[20];   // 一般
	CButton *m_pRadioI[20]; // 重要的
	CString m_strRec[20];


	void EnableRadio(int i, BOOL bEnable);
	void GetCurValues();
	void SetNewValues();

// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F9)
	enum { IDD = IDD_DLG_PRE_AFN04_F9 };
	CButton	m_check_all_valid;
	CButton	m_check_all_nml;
	CButton	m_check_all_imp;
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	UINT	m_edit_usImpRecNum;
	UINT	m_edit_usNmlRecNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F9)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F9)
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnCheck20();
	afx_msg void OnCheckAllValid();
	afx_msg void OnCheckAllNomarl();
	afx_msg void OnCheckAllImp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F9_H__54BAE3C0_B8F6_44ED_9C28_EBD1378292D1__INCLUDED_)
