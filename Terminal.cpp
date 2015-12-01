// Terminal.cpp: implementation of the CTerminal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NxMaster.h"
#include "Terminal.h"
#include "ServerSock.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTerminal::CTerminal()
{
  m_heartbeat = 0;
}

CTerminal::~CTerminal()
{

}

void CTerminal::setSocket(CServerSock *pSevSocket)
{
	m_pSevSocket = pSevSocket;
}