#if !defined(AFX_COLORLISTCTRL_H__CA10128C_0C98_4988_B2A6_0E3842F1D2A7__INCLUDED_)
#define AFX_COLORLISTCTRL_H__CA10128C_0C98_4988_B2A6_0E3842F1D2A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl window
//待编写
//实现设置条目字体颜色、背景颜色
//实现对条目的排序
//
// tips liming 2009-09-27
//email:smallpotato@126.com
#ifndef SORTHEADERCTRL_H
#include "SortHeaderCtrl.h"
#endif	// SORTHEADERCTRL_H

#ifdef _DEBUG
#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG


class CColorListCtrl : public CListCtrl
{
	// Construction
public:
	CColorListCtrl();
	
	// Attributes
public:
	
	// Operations
public:
	BOOL SetHeadings( UINT uiStringID );
	BOOL SetHeadings( const CString& strHeadings );
	
	int AddItem( LPCTSTR pszText, ... );
	BOOL DeleteItem( int iItem );
	BOOL DeleteAllItems();
	void LoadColumnInfo();
	void SaveColumnInfo();
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	void Sort( int iColumn, BOOL bAscending );
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD GetItemData(int nItem) const;
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListCtrl)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	void SetItemColor(int nItem, int nSubItem, COLORREF clrText, COLORREF clrBkgnd);
	void DrawText(int nItem, int nSubItem, CDC *pDC, COLORREF crText, COLORREF crBkgnd, CRect &rect);
	BOOL GetSubItemRect(int nItem, int nSubItem, int nArea, CRect& rect);
	int GetColumns();
	int AddItemColor(LPCTSTR pszText,COLORREF crText,COLORREF crBak);
	virtual ~CColorListCtrl();
	
	// Generated message map functions
protected:
	void UpdateSubItem(int nItem, int nSubItem);
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	void FreeItemMemory( const int iItem );
	BOOL CColorListCtrl::SetArray( int iItem, LPTSTR* arrpsz ,COLORREF * clrText,COLORREF * clrBak);
	LPTSTR* CColorListCtrl::GetTextArray( int iItem ) const;
	
	
	CSortHeaderCtrl m_ctlHeader;
	
	int m_iNumColumns;
	int m_iSortColumn;
	BOOL m_bSortAscending;
	
	//{{AFX_MSG(CColorListCtrl)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
private:
	COLORREF crWindowText,crWindow,crHighLight,crHighLightText;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLISTCTRL_H__CA10128C_0C98_4988_B2A6_0E3842F1D2A7__INCLUDED_)
