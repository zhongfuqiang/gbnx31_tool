#if !defined(AFX_TABDLGPRETML_H__39B0E034_DBE1_4744_B2D8_41A847A8C7FE__INCLUDED_)
#define AFX_TABDLGPRETML_H__39B0E034_DBE1_4744_B2D8_41A847A8C7FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlgPreTml.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPreTml dialog
//#include "NxRuler.h"
#include "Qgdw3761api.h"
#include "Gbnx_31.h"
#include "NxConfig.h"
#include "ColorListCtrl.h"
#include "FontColorTree.h"
#include "BtnST.h"
#include "ShadeButtonST.h"

class CTabDlgPreTml : public CDialog
{
private:
	void ShowTmlPreAfn04F1();
	void showMstPreAfn0cF90_NotElec();
	void showNullData();
	void showAfn0dFS(eMcmd eCmd);
	void showPreAfn00F1();
	void ShowPreAfn04F1();
// Construction
private:
	CImageList* m_imagelist;                   /*图标列表*/
	CNxConfig   m_nxCfg;
	eMtCmd m_eCmd; // 当前查看或修改的命令
	eMcmd m_mcmd; // 当前查看或修改的命令
public:
	void setTreePos();
	void setListPos();
	void initProtoTree();  // 初始化协议选择树
	
	void initList();
	void setItemColors();

	CTabDlgPreTml(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabDlgPreTml)
	enum { IDD = IDD_DLG_PRE_TML };
	//CButton	m_btn_modify;
	CShadeButtonST m_btn_modify;
	CEdit	m_edit_pn;
	CFontColorTree	m_tree;
	CColorListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlgPreTml)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDlgPreTml)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedTreePreTml(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnModify();
	afx_msg void OnBtnModify();
	afx_msg void OnChangeEditPn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLGPRETML_H__39B0E034_DBE1_4744_B2D8_41A847A8C7FE__INCLUDED_)
