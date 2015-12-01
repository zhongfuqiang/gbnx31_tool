// ServerSock.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "ServerSock.h"

#include "NxMasterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSock

CServerSock::CServerSock()
{
}

CServerSock::~CServerSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSock, CSocket)
	//{{AFX_MSG_MAP(CServerSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSock member functions

void CServerSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pNxDlg->SevAcceptConnect();
	CSocket::OnAccept(nErrorCode);
}

void CServerSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnConnect(nErrorCode);
}

void CServerSock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pNxDlg->SocketStop(this);
	CSocket::OnClose(nErrorCode);
}

void CServerSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pNxDlg->sevReceveMsg(this);

	CSocket::OnReceive(nErrorCode);
}

void CServerSock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnSend(nErrorCode);
}

void CServerSock::setNxDlg(CNxMasterDlg *pDlg)
{
	m_pNxDlg = pDlg;
}
