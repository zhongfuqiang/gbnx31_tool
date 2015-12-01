// NxMaster.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NxMaster.h"
#include "NxMasterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNxMasterApp

BEGIN_MESSAGE_MAP(CNxMasterApp, CWinApp)
	//{{AFX_MSG_MAP(CNxMasterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNxMasterApp construction

CNxMasterApp::CNxMasterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNxMasterApp object

CNxMasterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNxMasterApp initialization

BOOL CNxMasterApp::InitInstance()
{


	BOOL bAdmin = IsAdministrator();
	if (bAdmin == FALSE)
	{
		AfxMessageBox("需要以管理员身份运行该程序", MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	else
	{
		SetRegAdmin();
		CNxConfig cfg;
		cfg.initConfig();
	}

	// socket初始化一定要加上
    if (!AfxSocketInit())
	{
		AfxMessageBox("初始化失败");
		return FALSE;
	}
	:: AfxInitRichEdit();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CNxMasterDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CNxMasterApp::IsAdministrator()
{
	BOOL bIsElevated = FALSE;
	HANDLE hToken = NULL;
	UINT16 uWinVer = LOWORD(GetVersion());
	uWinVer = MAKEWORD(HIBYTE(uWinVer),LOBYTE(uWinVer));
	
	if (uWinVer < 0x0600)//不是VISTA、Windows7
		return(TRUE);
	
	if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {
		
		struct {
			DWORD TokenIsElevated;
		} /*TOKEN_ELEVATION*/te;
		DWORD dwReturnLength = 0;
		
		if (GetTokenInformation(hToken,/*TokenElevation*/(_TOKEN_INFORMATION_CLASS)20,&te,sizeof(te),&dwReturnLength)) {
			if (dwReturnLength == sizeof(te))
				bIsElevated = te.TokenIsElevated;
		}
		CloseHandle( hToken );
	}
	return bIsElevated;

}

void CNxMasterApp::SetRegAdmin()
{
	CString strPath = ReturnPath();
	/*
	HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers]
		"C:\\Program Files\\win7test2.exe"="RUNASADMIN"
		*/

	CRegistry reg;
	CString strSubKey = "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
	reg.SetRootKey(HKEY_CURRENT_USER);
	
	if(reg.bKeyExists(strSubKey, NULL) == FALSE)
	{
		reg.CreateKey(strSubKey);
	}
	else
	{
		
		reg.Open(strSubKey);
	}
	reg.Write(strPath, "RUNASADMIN");
}

CString CNxMasterApp::ReturnPath()
{
	
	CString    sPath;   
	// 	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	// 	sPath.ReleaseBuffer    ();   
	// 	int    nPos;   
	// 	nPos=sPath.ReverseFind('\\');   
	// 	sPath=sPath.Left(nPos);   
	// 	return    sPath;   
	
	   char pBuf[MAX_PATH];                                               //存放路径的变量
	   GetCurrentDirectory(MAX_PATH,pBuf);                   //获取程序的当前目录
	   strcat(pBuf,"\\");
	   strcat(pBuf,AfxGetApp()->m_pszExeName);   
	   strcat(pBuf,".exe"); 
	   sPath.Format("%s", pBuf);
	   
	   return    sPath;   
}