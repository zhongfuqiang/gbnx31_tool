// MyRichEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "MyRichEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRichEdit

CMyRichEdit::CMyRichEdit()
{
	initCf();
	
}

CMyRichEdit::~CMyRichEdit()
{
}


BEGIN_MESSAGE_MAP(CMyRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CMyRichEdit)
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRichEdit message handlers

void CMyRichEdit::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	CMenu menu,*pPopup;
// 	menu.LoadMenu(IDR_MENU_RICHEDIT);
// 	pPopup=menu.GetSubMenu(0);
// 	ClientToScreen(&point);
// 	pPopup->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
// 	
	CRichEditCtrl::OnRButtonUp(nFlags, point);
}

void CMyRichEdit::PrintLine(CString str)
{
	//setMasterCf(m_cfMasterMsg);
	SetSel(-1,-1);
	ReplaceSel((LPCTSTR)str);

}

void CMyRichEdit::SetCharColor(COLORREF cr)
{


}

void CMyRichEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("11");
	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CMyRichEdit::setMasterCf(CHARFORMAT cfMasterMsg)
{
	m_cf[CF_MSATER] = cfMasterMsg;
	
}

void CMyRichEdit::setTerminalCf(CHARFORMAT cfTerminMsg)
{
	m_cf[CF_TERMINAL] = cfTerminMsg;
}

void CMyRichEdit::cfprint(CString str, eTextCf txtCf = CF_DEFAULT)
{
	long nStartChar,  nEndChar;
	GetSel(nStartChar,nEndChar);

 	SetSel(-1,-1); 
	ReplaceSel(str);
	SetSel(nStartChar,str.GetLength());
	SetSelectionCharFormat(m_cf[txtCf]);
}

void CMyRichEdit::initCf()
{
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
//	this->GetDefaultCharFormat(cf);
   
   // default
   m_cf[CF_DEFAULT] = cf;

	
   // master
   cf.crTextColor = RGB(0,0,255);
   m_cf[CF_MSATER] = cf;
	
   // terminal
   cf.crTextColor = RGB(0,255,0);
   m_cf[CF_TERMINAL] = cf;

   //info



}

int CMyRichEdit::AppendColor(CString str, COLORREF color)
{
	int nOldLines = 0, nNewLines = 0, nScroll = 0;
	long nInsertionPoint = 0;
	//CHARRANGE cr;
	CHARFORMAT cf;

	// Save number of lines before insertion of new text
	nOldLines		= GetLineCount();

	// Initialize character format structure
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR;
	cf.dwEffects	= 0;	// To disable CFE_AUTOCOLOR
	cf.crTextColor	= color;

	// Set insertion point to end of text
	nInsertionPoint = GetWindowTextLength();
	/*if (nInsertionPoint > 800)
	{
		// Delete first half of text to avoid running into the 64k limit
		m_ctrlLog.SetSel(0, nInsertionPoint / 2);
		m_ctrlLog.ReplaceSel("");
		UpdateData(FALSE);
	}*/
	nInsertionPoint = -1;
	SetSel(nInsertionPoint, -1);

    //  Set the character format
    SetSelectionCharFormat(cf);

	// Replace selection. Because we have nothing selected, this will simply insert
	// the string at the current caret position.
	ReplaceSel(str);

	// Get new line count
	nNewLines		= GetLineCount();

	// Scroll by the number of lines just inserted
	nScroll			= nNewLines - nOldLines;
	LineScroll(nScroll);

	return 0;

}

int CMyRichEdit::cfAppend(CString str, eTextCf cftype)
{

	return cfAppend(str, m_cf[cftype]);
}
int CMyRichEdit::cfAppend(CString str, CHARFORMAT cf)
{
	int nOldLines = 0, nNewLines = 0, nScroll = 0;
	long nInsertionPoint = 0;
	//CHARRANGE cr;
	/*CHARFORMAT cf;*/

	// Save number of lines before insertion of new text
	nOldLines		= GetLineCount();

	// Initialize character format structure
// 	cf.cbSize		= sizeof(CHARFORMAT);
// 	cf.dwMask		= CFM_COLOR;
// 	cf.dwEffects	= 0;	// To disable CFE_AUTOCOLOR
// 	cf.crTextColor	= color;

	// Set insertion point to end of text
	nInsertionPoint = GetWindowTextLength();
	/*if (nInsertionPoint > 800)
	{
		// Delete first half of text to avoid running into the 64k limit
		m_ctrlLog.SetSel(0, nInsertionPoint / 2);
		m_ctrlLog.ReplaceSel("");
		UpdateData(FALSE);
	}*/
	nInsertionPoint = -1;
	SetSel(nInsertionPoint, -1);

    //  Set the character format
    SetSelectionCharFormat(cf);

	// Replace selection. Because we have nothing selected, this will simply insert
	// the string at the current caret position.
	ReplaceSel(str);

	// Get new line count
	nNewLines		= GetLineCount();

	// Scroll by the number of lines just inserted
	nScroll			= nNewLines - nOldLines;
	LineScroll(nScroll);
	long lLimitText = GetLimitText();
	long lTextCont  = GetTextLength();
	if (lTextCont > (lLimitText -10) )
	{
	//	AfxMessageBox("Clear()");
		Clear();
	}
	return 0;
}

void CMyRichEdit::setCfColor(eTextCf type, COLORREF cr)
{
	m_cf[type].dwMask = CFM_COLOR;
	m_cf[type].dwEffects = NULL;
	m_cf[type].crTextColor = cr;
	
}
