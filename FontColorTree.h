#if !defined(AFX_FONTCOLORTREE_H__92833ABD_55B0_4D78_8934_B1698CEF92C1__INCLUDED_)
#define AFX_FONTCOLORTREE_H__92833ABD_55B0_4D78_8934_B1698CEF92C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontColorTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFontColorTree window
//实现任意结点样式可设置的树型控件
//   类名:CFontColorTree
//　 功能：可以设置节点文本字体、加粗、下划线、颜色
//         李明
//　  鼎普科技股份有限公司
class CFontColorTree : public CTreeCtrl
{
	// Construction
public:
	CFontColorTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontColorTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetItemAllCheck(HTREEITEM hitemstart,BOOL bCheck);
	HTREEITEM GetHitemByText(HTREEITEM hitemstart,CString strtext);
	void RedrawTree();
	void SetItemTextAdd(HTREEITEM hitem, CString strAdd,BOOL bAdd);
	BOOL GetItemUnderline(HTREEITEM hItem);
	void SetItemUnderline(HTREEITEM hItem, BOOL bUnderline);
	int GetItemLabel(HTREEITEM hItem);
	void SetItemLabel(HTREEITEM hItem, int nlabel);
	BOOL GetItemFont(HTREEITEM hItem, LOGFONT *plogfont);
	void SetItemFont(HTREEITEM hItem, LOGFONT logfont);
	COLORREF GetItemColor(HTREEITEM hItem);
	void SetItemColor(HTREEITEM hItem, COLORREF color);
	void SetItemBold(HTREEITEM hItem, BOOL bBold);
	BOOL GetItemBold(HTREEITEM hItem);
	virtual ~CFontColorTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFontColorTree)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	struct color_font
	{
		COLORREF color;//节点颜色
		LOGFONT logfont;//字体
		int label;//用于自定义样式----完成、正在检测
		
	};
    CMap<void*,void*,color_font,color_font&>m_map_colorfont;
	DECLARE_MESSAGE_MAP()
	public:
		CBitmap m_memBitmap;    /*之前放在OnPaint中的*/ 
		CRgn m_Rgn;             /*之前放在OnPaint中的*/
	private:
		CDC m_memDC;            /*之前放在OnPaint中的*/
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTCOLORTREE_H__92833ABD_55B0_4D78_8934_B1698CEF92C1__INCLUDED_)
