// TerminalSock.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "TerminalSock.h"

#include "NxMasterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTerminalSock

CTerminalSock::CTerminalSock()
{
}

CTerminalSock::~CTerminalSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CTerminalSock, CSocket)
	//{{AFX_MSG_MAP(CTerminalSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CTerminalSock member functions

void CTerminalSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnAccept(nErrorCode);
}

void CTerminalSock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_pNxDlg->TmlOnClose(this);
	this->Close();

	CSocket::OnClose(nErrorCode);
}

void CTerminalSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnConnect(nErrorCode);
}

void CTerminalSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pNxDlg->tmlReceveMsg(this);
	CSocket::OnReceive(nErrorCode);
}

void CTerminalSock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnSend(nErrorCode);
}

void CTerminalSock::setNxDlg(CNxMasterDlg *pDlg)
{
	m_pNxDlg = pDlg;
}