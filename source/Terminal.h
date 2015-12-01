// Terminal.h: interface for the CTerminal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERMINAL_H__FEE96ACE_62C5_4C07_BB63_CE2EF3C4A0E0__INCLUDED_)
#define AFX_TERMINAL_H__FEE96ACE_62C5_4C07_BB63_CE2EF3C4A0E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ServerSock.h"

class CTerminal  
{
public:
	int m_address; // 
	CString m_strTerminalIp;
	CServerSock *m_pSevSocket;
	int m_heartbeat; //ÐÄÌø¼ÆÊý

	void setSocket(CServerSock *pSevSocket);
	CTerminal();
	virtual ~CTerminal();

};

#endif // !defined(AFX_TERMINAL_H__FEE96ACE_62C5_4C07_BB63_CE2EF3C4A0E0__INCLUDED_)
