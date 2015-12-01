#if !defined(AFX_DLGPREAFN04F1_H__6010BF53_4247_4840_8A69_C9A29232552A__INCLUDED_)
#define AFX_DLGPREAFN04F1_H__6010BF53_4247_4840_8A69_C9A29232552A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F1 dialog
//#include "NxRuler.h"
#include "NxConfig.h"
#include "Qgdw3761api.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
class CDlgPreAfn04F1 : public CDialog
{
public:
	BOOL  m_bPreMaster;
	CString m_strWindowText;
// Construction
public:
	CDlgPreAfn04F1(CWnd* pParent = NULL);   // standard constructor
	void setTitle(CString strTitle);
	void GetCurValues(); 
	void SetNewValues();
// Dialog Data

	//{{AFX_DATA(CDlgPreAfn04F1)
	enum { IDD = IDD_DLG_PRE_AFN04_F1 };
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	int		m_ucRts;
	int		m_ucRtm;
	int		m_usTmWaitTimeoutS;
	int		m_ucReSendTimes;
	int		m_ucHearBeat;
	int		m_bAsk1;
	int		m_bAsk2;
	int		m_bAsk3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F1)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F1_H__6010BF53_4247_4840_8A69_C9A29232552A__INCLUDED_)
