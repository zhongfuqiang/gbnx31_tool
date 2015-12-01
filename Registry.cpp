// Registry.cpp : implementation file
//

#include "stdafx.h"
#include "Registry.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistry

CRegistry::CRegistry(HKEY hKey)
{
	m_hKey=hKey;
}

CRegistry::~CRegistry()
{
	Close();
}

/////////////////////////////////////////////////////////////////////////////
// CRegistry Functions

BOOL CRegistry::CreateKey(LPCTSTR lpSubKey)
{
	ASSERT(m_hKey);
	ASSERT(lpSubKey);

	HKEY hKey;
	DWORD dw;
	long lReturn=RegCreateKeyEx(m_hKey,lpSubKey,0L,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
    
	if(lReturn==ERROR_SUCCESS)
	{
		m_hKey=hKey;
		return TRUE;
	}
	
	return FALSE;
	
}

BOOL CRegistry::Open(LPCTSTR lpSubKey)
{
	ASSERT(m_hKey);
	ASSERT(lpSubKey);
    
	HKEY hKey;
	long lReturn=RegOpenKeyEx(m_hKey,lpSubKey,0L,KEY_ALL_ACCESS,&hKey);
    
	if(lReturn==ERROR_SUCCESS)
	{
        m_hKey=hKey;
		return TRUE;
	}
	return FALSE;
	
}

void CRegistry::Close()
{
	if(m_hKey)
	{
		RegCloseKey(m_hKey);
		m_hKey=NULL;
	}
	
}

BOOL CRegistry::DeleteValue(LPCTSTR lpValueName)
{
	ASSERT(m_hKey);
	ASSERT(lpValueName);
	
	long lReturn=RegDeleteValue(m_hKey,lpValueName);
	
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	return FALSE;
	
}

BOOL CRegistry::DeleteKey(HKEY hKey, LPCTSTR lpSubKey)
{
	ASSERT(hKey);
	ASSERT(lpSubKey);
	
	long lReturn=RegDeleteValue(hKey,lpSubKey);
	
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	return FALSE;
	
}

BOOL CRegistry::Write(LPCTSTR lpSubKey, int nVal)
{
	ASSERT(m_hKey);
	ASSERT(lpSubKey);
	
	DWORD dwValue;
	dwValue=(DWORD)nVal;
	
	long lReturn=RegSetValueEx(m_hKey,lpSubKey,0L,REG_DWORD,(const BYTE *) &dwValue,sizeof(DWORD));
	
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
	
}

BOOL CRegistry::Write(LPCTSTR lpSubKey, DWORD dwVal)
{
	ASSERT(m_hKey);
	ASSERT(lpSubKey);
	
	long lReturn=RegSetValueEx(m_hKey,lpSubKey,0L,REG_DWORD,(const BYTE *) &dwVal,sizeof(DWORD));
	
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
	
}

BOOL CRegistry::Write(LPCTSTR lpValueName, LPCTSTR lpValue)
{
	ASSERT(m_hKey);
	ASSERT(lpValueName);
	ASSERT(lpValue);	

	long lReturn=RegSetValueEx(m_hKey,lpValueName,0L,REG_SZ,(const BYTE *) lpValue,strlen(lpValue)+1);
	
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
	
}


BOOL CRegistry::Read(LPCTSTR lpValueName, int* pnVal)
{
	ASSERT(m_hKey);
	ASSERT(lpValueName);
	ASSERT(pnVal);
	
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwDest;
	long lReturn=RegQueryValueEx(m_hKey,lpValueName,NULL,&dwType,(BYTE *)&dwDest,&dwSize);
	
	if(lReturn==ERROR_SUCCESS)
	{
		*pnVal=(int)dwDest;
		return TRUE;
	}
	return FALSE;
	
}

BOOL CRegistry::Read(LPCTSTR lpValueName, DWORD* pdwVal)
{
	ASSERT(m_hKey);
	ASSERT(lpValueName);
	ASSERT(pdwVal);
	
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwDest;
	long lReturn=RegQueryValueEx(m_hKey,lpValueName,NULL,&dwType,(BYTE *)&dwDest,&dwSize);
	
	if(lReturn==ERROR_SUCCESS)
	{
		*pdwVal=dwDest;
		return TRUE;
	}
	return FALSE;
	
}




BOOL CRegistry::RestoreKey(LPCTSTR lpFileName)
{
	ASSERT(m_hKey);
	ASSERT(lpFileName);
	
	long lReturn=RegRestoreKey(m_hKey,lpFileName,REG_WHOLE_HIVE_VOLATILE);
	
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}

BOOL CRegistry::SaveKey(LPCTSTR lpFileName)
{
	ASSERT(m_hKey);
	ASSERT(lpFileName);
	
	long lReturn=RegSaveKey(m_hKey,lpFileName,NULL);
	
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}


BOOL CRegistry::Read(LPCTSTR lpValueName, CString* lpVal)
{
	ASSERT(m_hKey);
	ASSERT(lpValueName);
	ASSERT(lpVal);
	
	DWORD dwType;
	DWORD dwSize=200;
	char szString[2550];
	
	long lReturn=RegQueryValueEx(m_hKey,lpValueName,NULL,&dwType,(BYTE *)szString,&dwSize);
	
	if(lReturn==ERROR_SUCCESS)
	{
		*lpVal=szString;
		return TRUE;
	}
	return FALSE;
	
}


BOOL CRegistry::SetRootKey(HKEY hRootKey)
{
	// sets the root key
	// make sure to set it to a valid key
	if (hRootKey != HKEY_CLASSES_ROOT &&
		hRootKey != HKEY_CURRENT_USER &&
		hRootKey != HKEY_LOCAL_MACHINE &&
		hRootKey != HKEY_USERS) return FALSE;
	
	m_hKey = hRootKey;
	return TRUE;
}





BOOL CRegistry::bKeyExists(CString strKey, HKEY hRootKey = NULL)
{
	/* Call KeyExists to determine if a key of a specified name exists.
		 Key is the name of the key for which to search. */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;

	if (hRootKey == NULL) hRootKey = m_hKey;
	
	LONG lResult = ::RegOpenKeyEx(hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	::RegCloseKey(hKey);
	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}

BOOL CRegistry::DeleteSubKey( LPCTSTR lpSubKey )
{
	ASSERT(lpSubKey);
	
	long lReturn=RegDeleteValue(m_hKey,lpSubKey);
	
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	return FALSE;
}

