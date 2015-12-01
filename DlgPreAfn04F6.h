#if !defined(AFX_DLGPREAFN04F6_H__F554748C_25F9_49CE_AA94_877C9141533C__INCLUDED_)
#define AFX_DLGPREAFN04F6_H__F554748C_25F9_49CE_AA94_877C9141533C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreAfn04F6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F6 dialog
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "NxConfig.h"

class CDlgPreAfn04F6 : public CDialog
{
	typedef enum eBaud_e
	{
		INDEX_BAUD_1200,            
			INDEX_BAUD_2400,
			INDEX_BAUD_4800,
			INDEX_BAUD_9600,
			INDEX_BAUD_19200,
			INDEX_BAUD_38400,         
			INDEX_BAUD_76800,   
			BAUD_NUM_MAX,
	}eBaud;
	
	
	typedef enum
	{
		CHECK_NONE,
			CHECK_ODD,
			CHECK_EVEN,
			CHECK_NUM_MAX,
			
	}eCheck;
	
	typedef enum
	{
		STOP_1,
			STOP_2,
			STOP_NUM_MAX,
	}eStopBit;
	
	typedef enum
	{
		DBIT_5,
			DBIT_6,
			DBIT_7,
			DBIT_8,
			DBIT_NUM_MAX,
	}eDataBit;
	
	
	typedef enum
	{
		CASC_NULL,     // 不启用级联功能
			CASC_RS485,    // RS485级联
			CASC_ETH,       // 以太网级联
			CASC_MAX
			
	}eCascType;
// Construction
public:
	CDlgPreAfn04F6(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bPreMaster;
	void GetCurValues();
	void SetNewValues();
	sMcascAddr m_sMcascAddr[3];


	CString m_NameCasc[CASC_MAX];
	CString m_BaudName[BAUD_NUM_MAX];
	CString m_checkName[CHECK_NUM_MAX];
	CString m_stopName[STOP_NUM_MAX];
	CString m_DBitName[DBIT_NUM_MAX];
	
// Dialog Data
	//{{AFX_DATA(CDlgPreAfn04F6)
	enum { IDD = IDD_DLG_PRE_AFN04_F6 };
	CTabCtrl	m_tab;
	CIPAddressCtrl	m_ip_sIp;
	CComboBox	m_cmb_stop;
	CComboBox	m_cmb_databit;
	CComboBox	m_cmb_check;
	CComboBox	m_cmb_baud;
	CButton	m_static_index;
	CComboBox	m_cmb_eType;
	CShadeButtonST	m_btn_ok;
	CShadeButtonST	m_btn_no;
	UINT	m_edit_ucN;
	UINT	m_edit_index;
	CString	m_edit_RegionCode;
	UINT	m_edit_ucPeriod;
	UINT	m_edit_ucRetry;
	UINT	m_edit_ucWaitC;
	UINT	m_edit_ucWaitP;
	UINT	m_edit_ulConAddr;
	UINT	m_edit_usPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreAfn04F6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CDlgPreAfn04F6)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEDITucN();
	afx_msg void OnChangeEditIndex();
	afx_msg void OnRADIObCascyes();
	afx_msg void OnRADIObCasced();
	afx_msg void OnSelchangeTabIndex(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEDITacRegionCode();
	afx_msg void OnChangeEDITulConAddr();
	afx_msg void OnFieldchangedIPsIp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEDITusPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREAFN04F6_H__F554748C_25F9_49CE_AA94_877C9141533C__INCLUDED_)
