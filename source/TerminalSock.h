#if !defined(AFX_TERMINALSOCK_H__33A6ACC9_37AB_460C_8C9E_6D74076DCC8C__INCLUDED_)
#define AFX_TERMINALSOCK_H__33A6ACC9_37AB_460C_8C9E_6D74076DCC8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TerminalSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CTerminalSock command target
class CNxMasterDlg;
class CTerminalSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CTerminalSock();
	virtual ~CTerminalSock();
	void setNxDlg(CNxMasterDlg * pDlg);
	CNxMasterDlg *m_pNxDlg;

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerminalSock)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CTerminalSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TERMINALSOCK_H__33A6ACC9_37AB_460C_8C9E_6D74076DCC8C__INCLUDED_)
