#if !defined(AFX_LISTCTRLSOCK_H__D7B2ECF4_E756_44A5_8C81_07AF98714D9B__INCLUDED_)
#define AFX_LISTCTRLSOCK_H__D7B2ECF4_E756_44A5_8C81_07AF98714D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlSock.h : header file
//

#include "Terminal.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlSock window

class CListCtrlSock : public CListCtrl
{
// Construction
public:
	CListCtrlSock();
	
// Attributes
public:
	CPtrList      *m_pListTml; // 与主站建立连接的终端链表
	int            m_maxItem;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlSock)
	//}}AFX_VIRTUAL

// Implementation
public:
	void addItemTerminal(CTerminal *pTml);
	void delItemTerminal(CTerminal *pTml);
	void setItemLogIn(CTerminal *pTml, UINT32 ulAddress);// 设置地址
	void setItemLogOut(CTerminal *pTml);
	void setItemHeartBeat(CTerminal *pTml);
	void initListCtrl();
	virtual ~CListCtrlSock();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLSOCK_H__D7B2ECF4_E756_44A5_8C81_07AF98714D9B__INCLUDED_)
