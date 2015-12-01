// NxMaster.h : main header file for the NXMASTER application
//

#if !defined(AFX_NXMASTER_H__42819343_7236_4769_905A_017FA7360A62__INCLUDED_)
#define AFX_NXMASTER_H__42819343_7236_4769_905A_017FA7360A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNxMasterApp:
// See NxMaster.cpp for the implementation of this class
//

class CNxMasterApp : public CWinApp
{
public:
	CNxMasterApp();
	BOOL IsAdministrator();
	void SetRegAdmin();
	CString ReturnPath();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNxMasterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNxMasterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NXMASTER_H__42819343_7236_4769_905A_017FA7360A62__INCLUDED_)
