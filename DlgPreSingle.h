#if !defined(AFX_DLGPRESINGLE_H__1DF6C4E3_5166_48F3_97B9_71DFF13D1ADD__INCLUDED_)
#define AFX_DLGPRESINGLE_H__1DF6C4E3_5166_48F3_97B9_71DFF13D1ADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreSingle.h : header file
//

#include "Gbnx_31.h"
#include "NxConfig.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPreSingle dialog

class CDlgPreSingle : public CDialog
{
// Construction
public:
	CDlgPreSingle(CWnd* pParent = NULL);   // standard constructor
	CString m_strTitle;  // 
	BOOL    m_bMaster;
	eMcmd   m_eCmd;
	
// Dialog Data
	//{{AFX_DATA(CDlgPreSingle)
	enum { IDD = IDD_DLG_SINGLE };
	double	m_edit_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreSingle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreSingle)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRESINGLE_H__1DF6C4E3_5166_48F3_97B9_71DFF13D1ADD__INCLUDED_)
