#if !defined(AFX_SERVERSOCK_H__E390F75D_C566_4E8E_9A13_11253D9EC12D__INCLUDED_)
#define AFX_SERVERSOCK_H__E390F75D_C566_4E8E_9A13_11253D9EC12D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSock command target

class CNxMasterDlg;
class CServerSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CServerSock();
	virtual ~CServerSock();
	CNxMasterDlg *m_pNxDlg;

// Overrides
public:
	void setNxDlg(CNxMasterDlg * pDlg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSock)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCK_H__E390F75D_C566_4E8E_9A13_11253D9EC12D__INCLUDED_)
