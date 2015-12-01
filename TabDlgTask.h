#if !defined(AFX_TABDLGTASK_H__4266EAF1_6485_49DB_B844_9D465BD98F96__INCLUDED_)
#define AFX_TABDLGTASK_H__4266EAF1_6485_49DB_B844_9D465BD98F96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlgTask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabDlgTask dialog

#include "BtnST.h"
#include "ShadeButtonST.h"

class CTabDlgTask : public CDialog
{
// Construction
public:
	void initListCtrl();
	void setCtrlPos();
	void SendOneTimer();  // 单条发送任务的定时器响应函数
	void SendListTimer(); // 逐条发送任务的定时器响应函数
	void setMainDlg(CNxMasterDlg *pNxMstDlg);
	void setOneText(CString str);
	CTabDlgTask(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bOneRun;
	BOOL m_bListRun;
	int  m_nOneZq;         //单条发送的周期
	int  m_nOneMaxTime;    //单条发送的最大次数
	int  m_nOneLeftTime;   // 单条发送的剩余次数

	int  m_nListZq;        //逐条发送的周期
	int  m_nListMaxTime;   //逐条发送的最大次数
	int  m_nListLeftTime;  // 逐条发送的剩余次数

private:
	CNxMasterDlg *m_pNxMstDlg;
 
// Dialog Data
	//{{AFX_DATA(CTabDlgTask)
	enum { IDD = IDD_DLG_TASK };
	CShadeButtonST	m_btn_clr;
	CShadeButtonST	m_btn_go_stop_list;
	CShadeButtonST  m_btn_go_stop;
	CEdit	m_edit_one;
	CListCtrl	m_list_task;
	CButton	m_static_one;
	CButton	m_static_list;
	int		m_zqOne;
	int		m_timesOne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlgTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDlgTask)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnGoStop();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnListGoStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnClr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLGTASK_H__4266EAF1_6485_49DB_B844_9D465BD98F96__INCLUDED_)
