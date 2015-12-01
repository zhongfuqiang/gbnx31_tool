#if !defined(AFX_TABDLGUNPACK_H__56BB4658_9EC7_48AC_ABB9_39BB1737DDAE__INCLUDED_)
#define AFX_TABDLGUNPACK_H__56BB4658_9EC7_48AC_ABB9_39BB1737DDAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlgUnpack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabDlgUnpack dialog

//#include "NxRuler.h"
#include "Qgdw3761api.h"
#include "Gbnx_31.h"
#include "FontColorTree.h"
#include "BtnST.h"
#include "ShadeButtonST.h"

class CNxMasterDlg;

class CTabDlgUnpack : public CDialog
{
// Construction
public:
	CTabDlgUnpack(CWnd* pParent = NULL);   // standard constructor
	void setCtrlPos();
    eMtErr unpack3761buffer(char *pBuf, UINT16 usLen); 
	eMcErr unpackgb31buffer(char *pBuf, UINT16 usLen);
	void   showUnpackTree(smtPack *psmtPack);
	void   showUnpackTree31(smcPack *psmtPack);
	HTREEITEM AddTreeItem(CString strText, HTREEITEM hitem, BOOL bBold, COLORREF color = RGB(0,0,0));
	HTREEITEM AddSubCmdData(sMtData *psMtData,eMtDir eDir, HTREEITEM hitem, BOOL bBold, COLORREF color = RGB(0,0,0));
	HTREEITEM AddSubCmdData31(sMcData *psMtData,eMcDir eDir, HTREEITEM hitem, BOOL bBold, COLORREF color = RGB(0,0,0));

	void setMainDlg(CNxMasterDlg *pNxMstDlg);

	void    vFree(char *pBuf);
	void    unpack(CString strPack);
	CString m_strUnpack;  // 准备解析的报文
private:
	CNxMasterDlg *m_pNxMstDlg;
 
// Dialog Data
	//{{AFX_DATA(CTabDlgUnpack)
	enum { IDD = IDD_DLG_UNPACK };

	//CButton	m_btn_unpack;
	//CButton	m_btn_clr;
	CShadeButtonST m_btn_unpack;
	CShadeButtonST m_btn_clr;

	CButton	m_check_show_text;
	CButton	m_check_show_tree;
	CEdit	m_edit_unpack;
	CFontColorTree	m_tree_unpack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlgUnpack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDlgUnpack)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnUnpack();
	afx_msg void OnBtnClrInput();
	afx_msg void OnChangeEditUnpackCmd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLGUNPACK_H__56BB4658_9EC7_48AC_ABB9_39BB1737DDAE__INCLUDED_)
