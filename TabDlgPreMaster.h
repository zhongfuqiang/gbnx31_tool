#if !defined(AFX_TABDLGPREMASTER_H__1535B977_0332_406E_98EC_5A371E468C67__INCLUDED_)
#define AFX_TABDLGPREMASTER_H__1535B977_0332_406E_98EC_5A371E468C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlgPreMaster.h : header file
//

//#include "NxRuler.h"
#include "Qgdw3761api.h"
#include "NxConfig.h"
#include "ColorListCtrl.h"
#include "FontColorTree.h"
#include "BtnST.h"
#include "ShadeButtonST.h"

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPreMaster dialog

class CTabDlgPreMaster : public CDialog
{
// Construction
private:
	CImageList* m_imagelist;                   /*图标列表*/
	CNxConfig   m_nxCfg;
private:
	void showMstNullData();  // 在列表中显示，没有数据不需要配置
	void showMstPreAfn00F1();
	void ShowMstPreAfn04F1();
	void ShowMstPreAfn04F3();
	void ShowMstPreAfn04F4();
	void ShowMstPreAfn04F7();
	void ShowMstPreAfn04F33();
	void ShowMstPreAfn04F34();
	void ShowMstPreAfn04F35();
	void showMstPreAfn0cF90_NotElec();
public:
	void setTreePos();
	void setListPos();
	CTabDlgPreMaster(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTabDlgPreMaster();
	void initProtoTree();  // 初始化协议选择树
	void initList();
	void setItemColors();
	eMtCmd m_eCmd; // 当前查看或修改的命令
	eMcmd  m_mcmd;
// Dialog Data
	//{{AFX_DATA(CTabDlgPreMaster)
	enum { IDD = IDD_DLG_PRE_MST };
	//CButton	m_btn_modify;
	CShadeButtonST m_btn_modify;
	CEdit	m_edit_pn;
	CFontColorTree	m_tree;
	CColorListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlgPreMaster)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDlgPreMaster)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnItemexpandedTreePreMst(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreePreMst(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnModify();
	afx_msg void OnChangeEditPn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLGPREMASTER_H__1535B977_0332_406E_98EC_5A371E468C67__INCLUDED_)
