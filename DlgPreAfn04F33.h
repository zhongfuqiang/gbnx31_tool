#if !defined(AFX_DLGPREAFN04F33_H__BF26BB5C_F170_4445_AF9B_2CC39995B0C2__INCLUDED_)
#define AFX_DLGPREAFN04F33_H__BF26BB5C_F170_4445_AF9B_2CC39995B0C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F33.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F33 dialog

//#include "NxRuler.h"
#include "Qgdw3761api.h"
#include "NxConfig.h"

class CDlgPreAfn04F33 : public CDialog
{
// Construction
private:
	CString m_type_name[7];
public:
	void SetNewValue();
	void GetOldValue();
	void InitCombType(); // 初始化类型comb
	CDlgPreAfn04F33(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F33)
	enum { IDD = IDD_DLG_PRE_AFN04_F33 };
	CEdit	m_edit_min;
	CEdit	m_edit_max;
	CComboBox	m_comb_type;
	int		m_edit_pn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F33)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F33)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F33_H__BF26BB5C_F170_4445_AF9B_2CC39995B0C2__INCLUDED_)
