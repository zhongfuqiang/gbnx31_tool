// FontColorTree.cpp : implementation file
//

#include "stdafx.h"
#include "FontColorTree.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontColorTree





CFontColorTree::CFontColorTree()
{

}

CFontColorTree::~CFontColorTree()
{
	if (!m_map_colorfont.IsEmpty())
	{
		m_map_colorfont.RemoveAll();
	}
	if (m_memDC.m_hDC)
	{
		m_memDC.DeleteDC();
	}
    if (m_memBitmap.m_hObject)
    {
		m_memBitmap.DeleteObject();
    }
	if (m_Rgn.m_hObject)
	{
		m_Rgn.DeleteObject();
	}
}


BEGIN_MESSAGE_MAP(CFontColorTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CFontColorTree)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontColorTree message handlers

//获得节点文本Bold
BOOL CFontColorTree::GetItemBold(HTREEITEM hItem)
{
	return GetItemState(hItem,TVIS_BOLD)&TVIS_BOLD;
}

//设置节点BOLD
void CFontColorTree::SetItemBold(HTREEITEM hItem, BOOL bBold)
{
	SetItemState(hItem,bBold?TVIS_BOLD:0,TVIS_BOLD);
}

//设置节点文本颜色
void CFontColorTree::SetItemColor(HTREEITEM hItem, COLORREF color)
{

	color_font cf;
	if (m_map_colorfont.Lookup(hItem,cf))
	{
		cf.logfont.lfFaceName[0]='\0';
	}
	cf.color=color;
	m_map_colorfont[hItem]=cf;
}

//获得文本颜色
COLORREF CFontColorTree::GetItemColor(HTREEITEM hItem)
{
	color_font cf;
	if (m_map_colorfont.Lookup(hItem,cf))
	{
		return (COLORREF)-1;
	}
	return cf.color;

}

//设置条目字体
void CFontColorTree::SetItemFont(HTREEITEM hItem, LOGFONT logfont)
{

	color_font cf;
	if (!m_map_colorfont.Lookup(hItem,cf))
	{
		cf.color=(COLORREF)-1;
	}
	cf.logfont=logfont;
	m_map_colorfont[hItem]=cf;
}


//获得节点字体
BOOL CFontColorTree::GetItemFont(HTREEITEM hItem, LOGFONT *plogfont)
{
	color_font cf;
	if (m_map_colorfont.Lookup(hItem,cf))
	{
		return FALSE;
	}
	if (cf.logfont.lfFaceName[0]=='\0')
	{
		return FALSE;
	}
	*plogfont=cf.logfont;
	return true;
}

//设置自定义样式
void CFontColorTree::SetItemLabel(HTREEITEM hItem, int nlabel)
{
	color_font cf;
	if (m_map_colorfont.Lookup(hItem,cf))
	{
		cf.logfont.lfFaceName[0]='\0';
	}
	cf.label=nlabel;
	
	m_map_colorfont[hItem]=cf;
	
	Invalidate(TRUE); 
	
}

//获得节点自定义样式类型
int CFontColorTree::GetItemLabel(HTREEITEM hItem)
{
	color_font cf;

	if (m_map_colorfont.Lookup(hItem,cf))
	{
		cf.logfont.lfFaceName[0]='\0';
	}
	return cf.label;
}

//设置节点有无下划线
void CFontColorTree::SetItemUnderline(HTREEITEM hItem, BOOL bUnderline)
{
	
	color_font cf;
	if (m_map_colorfont.Lookup(hItem,cf))
	{
		cf.logfont.lfFaceName[0]='\0';
		
		if (bUnderline)
		{ 
			cf.logfont.lfUnderline=TRUE;
		}
		else
		{
			cf.logfont.lfUnderline=FALSE;
		}
		
	}
	m_map_colorfont[hItem]=cf;

	//Invalidate(TRUE); 
}

//获得节点有无下划线
BOOL CFontColorTree::GetItemUnderline(HTREEITEM hItem)
{
	color_font cf;
	if (m_map_colorfont.Lookup(hItem,cf))
	{
		cf.logfont.lfFaceName[0]='\0';
	}
	
	if (cf.logfont.lfUnderline==TRUE)
	{ 
		return TRUE;
		
	}
	else
	{
		return FALSE;
	}
	
}

//设置节点加减文字
void CFontColorTree::SetItemTextAdd(HTREEITEM hitem, CString strAdd, BOOL bAdd)
{
	
	CString stritem;
	if (bAdd)
	{
		stritem=GetItemText(hitem);
		stritem=stritem+strAdd;
		
	}
	else
	{
		CString str;
		int m_nadd,m_nold,m_nnew;
		m_nadd=strAdd.GetLength();
		stritem=GetItemText(hitem);
		str=stritem.Right(m_nadd);
		if (str!=strAdd)
			return;
		m_nnew=stritem.GetLength();
		m_nold=m_nnew-m_nadd;
		stritem=stritem.Left(m_nold);
	}
	SetItemText(hitem,stritem);
	//Invalidate(TRUE); 
}

void CFontColorTree::OnPaint() 
{
	//Invalidate(FALSE); 
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	if (NULL == m_memDC.m_hDC)
	{
		m_memDC.CreateCompatibleDC(&dc);
	}
	//从当前DC创建内存对象
	CRect rcClip,rcClient;
	//定义CRect对象，用来确定区域
	dc.GetClipBox(&rcClip);
	GetClientRect(&rcClient);
	
	if (NULL == m_memBitmap.m_hObject)
	{
		m_memBitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	}	
   
	m_memDC.SelectObject(&m_memBitmap);
	
	if (NULL == m_Rgn.m_hObject)
	{
		m_Rgn.CreateRectRgnIndirect( &rcClip );
	}	
	m_memDC.SelectClipRgn(&m_Rgn);
	m_Rgn.DeleteObject();
 	
// 	
 	CWnd::DefWindowProc( WM_PAINT, (WPARAM)m_memDC.m_hDC, 0 );
	
	HTREEITEM hItem = GetFirstVisibleItem();
	int n = GetVisibleCount()+1;
	while( (hItem!=NULL) && n--)
	{
		
		CRect rect;
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		//定义字体、颜色
		color_font cf;
		//设置字体
		if ( !(GetItemState( hItem, selflag ) & selflag )
			&& m_map_colorfont.Lookup( hItem, cf ))
		{
			CFont *pFontDC;
			CFont fontDC;
			LOGFONT logfont;
			int m_nlabel;
			
			if( cf.logfont.lfFaceName[0] != '\0' )
			{
				//用户定义了字体
				logfont = cf.logfont;
			}
			else
			{
				// 用户没有定义，使用系统字体
				CFont *pFont = GetFont();
				pFont->GetLogFont( &logfont );
				
			}
			
			
			//用户是否设定节点为加粗
			if( GetItemBold( hItem ) )
				logfont.lfWeight = 700;
			
			if (GetItemUnderline(hItem))
			{				
				logfont.lfUnderline=TRUE;
			}
			
			//创建字体
			fontDC.CreateFontIndirect( &logfont );
			pFontDC = m_memDC.SelectObject( &fontDC );
			
			//设置字体颜色
			if( cf.color != (COLORREF)-1 )
				m_memDC.SetTextColor( cf.color );
			
			//获取节点文字
			CString sItem = GetItemText( hItem );
			
			//获取节点区域
			GetItemRect( hItem, &rect, TRUE );
			//设置背景色为系统色
			m_memDC.SetBkColor( GetSysColor( COLOR_WINDOW ) );
			//向内存中的图片写入内容,为该节点的内容
			m_nlabel=cf.label;
			m_memDC.TextOut( rect.left+2, rect.top+1, sItem );
			if (m_nlabel==1)
			{
				
				m_memDC.SetTextColor(RGB(255,0,0));
				m_memDC.TextOut(rect.right+2,rect.top+1,"(正在检测……)");
			}
            else if (m_nlabel==2)
			{
				m_memDC.SetTextColor(RGB(107,142,35));
				m_memDC.TextOut(rect.right+2,rect.top+1,"(检测完成)");
			}
			
			m_memDC.SelectObject( pFontDC );
			fontDC.DeleteObject();
			
			
		}
		hItem = GetNextVisibleItem( hItem );
	}
	
	
	
	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &m_memDC,
		rcClip.left, rcClip.top, SRCCOPY );
	
	//m_memBitmap.DeleteObject();

	//////////////////////////////////////////////////////////////////////////
	//2009-11-9-修改的错误，memdc申请没有delet造成内存不足-修改人：范波　
// 	if (memDC.m_hDC)
// 	{
// 		memDC.DeleteDC();
// 	}
}

//刷新树控件
void CFontColorTree::RedrawTree()
{
	Invalidate(FALSE); 	
}



//获得指定文本的条目句枘
HTREEITEM CFontColorTree::GetHitemByText(HTREEITEM hitemstart,CString strtext)
{
	HTREEITEM hchild,hnext;
	hchild=GetChildItem(hitemstart);
	
	while(hchild)
	{
		if (GetItemText(hchild)==strtext)
		{
			return hchild;
		}
		hnext=hchild;
		GetHitemByText(hnext,strtext);
		hchild=GetNextSiblingItem(hchild);
	}	
	return hchild;
}


//设置所有节点都选中
void CFontColorTree::SetItemAllCheck(HTREEITEM hitemstart,BOOL bCheck)
{
	
	HTREEITEM hchild,hnext;
	hchild=GetChildItem(hitemstart);
	
	while(hchild)
	{
		if (bCheck)
		{
			SetCheck(hchild,TRUE);
		}
		else
		{
			SetCheck(hchild,FALSE);
		}
		hnext=hchild;
		SetItemAllCheck(hnext,bCheck);
		hchild=GetNextSiblingItem(hchild);
	}
	
}

void CFontColorTree::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("dfdf");
	//此消息可以取消
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CFontColorTree::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	

	CRect rc;
    TVHITTESTINFO tvInfo;
    tvInfo.pt=point;
	HTREEITEM hitem=HitTest(&tvInfo);
	//GetItemRect(hitem,rc,TRUE);
	GetItemRect(hitem,rc,TRUE);



	CTreeCtrl::OnMouseMove(nFlags, point);
}
