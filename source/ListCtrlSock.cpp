// ListCtrlSock.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "ListCtrlSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlSock

CListCtrlSock::CListCtrlSock()
{
	m_maxItem = 0;
}

CListCtrlSock::~CListCtrlSock()
{
}


BEGIN_MESSAGE_MAP(CListCtrlSock, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlSock)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlSock message handlers

void CListCtrlSock::initListCtrl()
{
	SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int i = 0;
	InsertColumn(i++,"发送",LVCFMT_CENTER,40);
	InsertColumn(i++,"地址",LVCFMT_CENTER,50);
	InsertColumn(i++,"IP",LVCFMT_CENTER,110);
	InsertColumn(i++,"心跳计数",LVCFMT_CENTER,70);
	InsertColumn(i++,"终端状态",LVCFMT_CENTER,110);
	InsertColumn(i++,"逻辑编号",LVCFMT_CENTER,70);
}






void CListCtrlSock::addItemTerminal(CTerminal *pTml)
{
	CString strAddr;
	CString strIp;
	CString strCmdNum;
	CString strState;
	CString strObjID;
	int i = 1;
	
	strObjID.Format("%X",(unsigned long)pTml);
	strAddr = pTml->m_address;
	strIp   = pTml->m_strTerminalIp;
	InsertItem(m_maxItem," ");
	SetItemText(m_maxItem,i++,strAddr);
	SetItemText(m_maxItem,i++,strIp);
	SetItemText(m_maxItem,i++,strCmdNum);
	SetItemText(m_maxItem,i++,"上线-未登录");
	SetItemText(m_maxItem,i++,strObjID);
	m_maxItem++;
}

// 删除该终端实体对应的在列表中的条目
void CListCtrlSock::delItemTerminal( CTerminal *pTml )
{
	CString strObjID, strObjIDList;
	strObjID.Format("%X",(unsigned long)pTml);
	int nItem = 0;
	int i = 0;
	for(i = 0; i < GetItemCount(); i++)
	{
		strObjIDList = GetItemText(i, 5);
		if(strObjID.Compare(strObjIDList) == 0)
		{
			DeleteItem(i);
			m_maxItem--;
		}
	}
}

// 终端登录 将列表中的信息更新
void CListCtrlSock::setItemLogIn( CTerminal *pTml, UINT32 ulAddress )
{
	CString strObjID, strObjIDList;
	CString strAddress;
	strAddress.Format("%d",ulAddress );
	strObjID.Format("%X",(unsigned long)pTml);
	pTml->m_address = ulAddress;
	int nItem = 0;
	int i = 0;
	for(i = 0; i < GetItemCount(); i++)
	{
		strObjIDList = GetItemText(i, 5);
		if(strObjID.Compare(strObjIDList) == 0)
		{
			SetItemText(i, 1, strAddress);
			SetItemText(i, 4,"上线-已登录");
		}
	}
}

void CListCtrlSock::setItemLogOut( CTerminal *pTml )
{
	CString strObjID, strObjIDList;
	CString strAddress = "";

	pTml->m_heartbeat = 0;
	strObjID.Format("%X",(unsigned long)pTml);
	int nItem = 0;
	int i = 0;
	for(i = 0; i < GetItemCount(); i++)
	{
		strObjIDList = GetItemText(i, 5);
		if(strObjID.Compare(strObjIDList) == 0)
		{
			SetItemText(i, 1, strAddress);
			SetItemText(i, 3,"");
			SetItemText(i, 4,"退出登录");
		}
	}
	
}

void CListCtrlSock::setItemHeartBeat( CTerminal *pTml )
{
	CString strObjID, strObjIDList;
	CString strHeartbeat = "";
	pTml->m_heartbeat++;

	strHeartbeat.Format("%d", pTml->m_heartbeat);

	strObjID.Format("%X",(unsigned long)pTml);
	int nItem = 0;
	int i = 0;
	for(i = 0; i < GetItemCount(); i++)
	{
		strObjIDList = GetItemText(i, 5);
		if(strObjID.Compare(strObjIDList) == 0)
		{
			SetItemText(i, 3,strHeartbeat);
		}
	}
	
}


