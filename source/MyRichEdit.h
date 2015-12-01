#if !defined(AFX_MYRICHEDIT_H__60C549AA_49EE_41ED_BB4E_E473DFFDBB4A__INCLUDED_)
#define AFX_MYRICHEDIT_H__60C549AA_49EE_41ED_BB4E_E473DFFDBB4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRichEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyRichEdit window

typedef enum
{
	CF_DEFAULT, // 默认的样式
	CF_MSATER, // 主站的消息
    CF_TERMINAL, // 从站的消息
	CF_UNPACK,  // 解析消息
	CF_INFO,
	//在这上面添加新的类型
	CF_MAX_NUM,
}eTextCf;



class CMyRichEdit : public CRichEditCtrl
{
// Construction
public:
	CMyRichEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRichEdit)
	//}}AFX_VIRTUAL

// Implementation
	CHARFORMAT m_cf[CF_MAX_NUM];
public:
	void setCfColor(eTextCf cftype, COLORREF cr);
	int cfAppend(CString str, CHARFORMAT cf);
	int cfAppend(CString str, eTextCf cftype);
	int AppendColor(CString str, COLORREF color);
	void cfprint(CString str, eTextCf txtCf);
	void SetCharColor(COLORREF cr);
	void PrintLine(CString str);
	void setMasterCf(CHARFORMAT cfMasterMsg);
	void setTerminalCf(CHARFORMAT cfTerminMsg);
	void initCf();
	CHARFORMAT m_cfMaster;
    CHARFORMAT m_cfTerminal;

	virtual ~CMyRichEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyRichEdit)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYRICHEDIT_H__60C549AA_49EE_41ED_BB4E_E473DFFDBB4A__INCLUDED_)
