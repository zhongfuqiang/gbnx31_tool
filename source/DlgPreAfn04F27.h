#if !defined(AFX_DLGPREAFN04F27_H__92124B9F_53EC_4F5C_A40B_585AE063C7CE__INCLUDED_)
#define AFX_DLGPREAFN04F27_H__92124B9F_53EC_4F5C_A40B_585AE063C7CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F27.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F27 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
class CDlgPreAfn04F27 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F27(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;
	void GetCurValues();
	void SetNewValues();
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F27)
	enum { IDD = IDD_DLG_PRE_AFN04_F27 };
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	float	m_edit_fDropV;
	UINT	m_edit_ucTimeLossV;
	float	m_edit_sMcOverV_fUpUp;
	float	m_edit_sMcLossV_fDownFDown;
	float	m_edit_sMcLossV_fFactor;
	UINT	m_edit_sMcLossV_ucTime;
	float	m_edit_sMcOverI_fFactor;
	float	m_edit_sMcOverI_fUpUp;
	UINT	m_edit_sMcOverI_ucTime;
	float	m_edit_sMcOverV_fFactor;
	UINT	m_edit_sMcOverV_ucTime;
	UINT	m_edit_sMcZeroI_ucTime;
	float	m_edit_sMcZeroI_fUp;
	float	m_edit_sMcZeroI_fFactor;
	float	m_edit_sMcUnblnV_fFactor;
	float	m_edit_sMcUnblnV_fLimit;
	UINT	m_edit_sMcUnblnV_ucTime;
	float	m_edit_sMcSuperI_fFactor;
	float	m_edit_sMcSuperI_fUp;
	UINT	m_edit_sMcSuperI_ucTime;
	float	m_edit_sMcUnblnI_fFactor;
	float	m_edit_sMcUnblnI_fLimit;
	UINT	m_edit_sMcUnblnI_ucTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F27)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F27)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F27_H__92124B9F_53EC_4F5C_A40B_585AE063C7CE__INCLUDED_)
