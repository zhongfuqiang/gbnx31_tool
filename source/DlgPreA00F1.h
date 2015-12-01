#if !defined(AFX_DLGPREA00F1_H__90918B86_2D68_4728_B919_96A66B7C814C__INCLUDED_)
#define AFX_DLGPREA00F1_H__90918B86_2D68_4728_B919_96A66B7C814C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreA00F1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreA00F1 dialog

/*
设置 MCMD_AFN_0_F1_ALL_OK_DENY 参数

*/
#include "Gbnx_31.h"
#include "NxConfig.h"
#include "BtnST.h"
#include "ShadeButtonST.h"

class CDlgPreA00F1 : public CDialog
{
// Construction
public:
	CDlgPreA00F1(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;  // 是否为主站
	eMcResCode eGetResCode();
	void GetPre();
	void SetNew();
// Dialog Data
	//{{AFX_DATA(CDlgPreA00F1)
	enum { IDD = IDD_DIALOG_AFN00_F1 };
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreA00F1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	eMcResCode eResCode;
	// Generated message map functions
	//{{AFX_MSG(CDlgPreA00F1)
	afx_msg void OnRadio0();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio255();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREA00F1_H__90918B86_2D68_4728_B919_96A66B7C814C__INCLUDED_)
