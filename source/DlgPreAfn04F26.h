#if !defined(AFX_DLGPREAFN04F26_H__38AFC1BF_860C_44E9_BF21_2F25924CAAF7__INCLUDED_)
#define AFX_DLGPREAFN04F26_H__38AFC1BF_860C_44E9_BF21_2F25924CAAF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F26.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F26 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"
typedef enum
{
	INTGR_4,
	INTGR_5,
	INTGR_6,
	INTGR_7,
	INTGR_MAX,

}INTGR_INDEX;

typedef enum
{
	DECIM_1,
	DECIM_2,
	DECIM_3,
	DECIM_4,
	DECIM_MAX,
}DECIM_INDEX;

typedef enum
{
    LINK_P3_L3,  // 三相三线
	LINK_P3_L4,  // 三相四线
    LINK_P1,     // 单相表
	LINK_MAX

}LINK_INDEX;

typedef enum
{
   PHASE_UNKOWN, // 未知
   PHASE_A,      // A 相
   PHASE_B,      // B 相
   PHASE_C,      // C 相
   PHASE_MAX

}PHASE_INDEX;

class CDlgPreAfn04F26 : public CDialog
{
// Construction
public:
	CDlgPreAfn04F26(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bMaster;
	void GetCurValues();
	void SetNewValues();
	CButton *m_pRadioIntgr[INTGR_MAX];
	CButton *m_pRadioDecim[DECIM_MAX];
	CButton *m_pRadioLink[LINK_MAX];
	CButton *m_pRadioPhase[PHASE_MAX];

// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F26)
	enum { IDD = IDD_DLG_PRE_AFN04_F26 };
	CShadeButtonST	m_btn_no;
	CShadeButtonST	m_btn_ok;
	UINT	m_edit_usTimesI;
	float	m_edit_fI;
	float	m_edit_fU;
	UINT	m_edit_usTimesU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F26)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F26)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F26_H__38AFC1BF_860C_44E9_BF21_2F25924CAAF7__INCLUDED_)
