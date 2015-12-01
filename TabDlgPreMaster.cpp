// TabDlgPreMaster.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "TabDlgPreMaster.h"


#include "DlgPreAfn04F1.h"
#include "DlgPreAfn04F33.h"
#include "DlgPreA00F1.h"
#include "DlgPreAfn04F2.h"
#include "DlgPreAfn04F3.h"
#include "DlgPreAfn04F4.h"
#include "DlgPreAfn04F5.h"
#include "DlgPreAfn04F6.h"
#include "DlgPreAfn04F7.h"
#include "DlgPreAfn04F9.h"
#include "DlgPreAfn04F10.h"
#include "DlgPreAfn04F17.h"
#include "DlgPreAfn04F25_33.h"
#include "DlgPreAfn04F26.h"
#include "DlgPreAfn04F27.h"
#include "DlgPreAfn04F28.h"
#include "DlgPreAfn04F29.h"
#include "DlgPreAfn04F30.h"
#include "DlgPreAfn04F34.h"
#include "DlgPreAfn04F35.h"
#include "DlgPreAfn04F49.h"
#include "DlgPreAfn0aF2.h"
#include "DlgPreAfn0AF7Q.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPreMaster dialog


CTabDlgPreMaster::CTabDlgPreMaster(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlgPreMaster::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabDlgPreMaster)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT



}

CTabDlgPreMaster::~CTabDlgPreMaster()
{

}

void CTabDlgPreMaster::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDlgPreMaster)
	DDX_Control(pDX, IDC_BTN_MODIFY, m_btn_modify);
	DDX_Control(pDX, IDC_EDIT_PN, m_edit_pn);
	DDX_Control(pDX, IDC_TREE_PRE_MST, m_tree);
	DDX_Control(pDX, IDC_LIST_PRE_MST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabDlgPreMaster, CDialog)
	//{{AFX_MSG_MAP(CTabDlgPreMaster)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE_PRE_MST, OnItemexpandedTreePreMst)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PRE_MST, OnSelchangedTreePreMst)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_EN_CHANGE(IDC_EDIT_PN, OnChangeEditPn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDlgPreMaster message handlers

void CTabDlgPreMaster::initList()
{
	m_list.SetHeadings(_T("数据名称,150;数据内容,100;单位格式,80;范围说明,100"));
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}



// 初始化 主站命令预配 界面上的协议选择树
void CTabDlgPreMaster::initProtoTree()
{
	m_imagelist = new CImageList();
	m_tree.SetItemHeight(m_tree.GetItemHeight()+2);
    //m_imagelist->Create(16,16,ILC_COLOR32,0,0);
	m_imagelist->Create(16,16,ILC_COLOR32,0,0);
	m_imagelist->SetBkColor(RGB(255,255,255));

	
	#define ICON_MAX 3
	int i = 0;
	HICON hicon[ICON_MAX];
	int ico_afn;
	int ico_fn;
	int ico_sel;

	hicon[ico_afn = 0] = AfxGetApp()->LoadIcon(IDI_ICON9);
	hicon[ico_sel = 1] = AfxGetApp()->LoadIcon(IDI_ICON_CHECK);
	hicon[ico_fn  = 2] = AfxGetApp()->LoadIcon(IDI_ICON_CHECK_NO);


	for (i = 0; i < ICON_MAX; i++)
	{
		m_imagelist->Add(hicon[i]);
	}
	
	m_tree.SetImageList(m_imagelist,TVSIL_NORMAL);


	HTREEITEM hitem;
	//afn 00
	hitem = m_tree.InsertItem(STR_AFN_00_CONF,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_00_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	//m_tree.InsertItem(STR_AFN_00_F2,ico_fn,ico_sel,hitem,TVI_LAST);

	// afn 01
	hitem = m_tree.InsertItem(STR_AFN_01_RSET,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_01_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_01_F2,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_01_F3,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_01_F4,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_01_F5,ico_fn,ico_sel,hitem,TVI_LAST);

	// afn 02
	hitem = m_tree.InsertItem(STR_AFN_02_LINK,ico_afn,ico_afn,TVI_ROOT);
	//m_tree.InsertItem(STR_AFN_02_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	//m_tree.InsertItem(STR_AFN_02_F2,ico_fn,ico_sel,hitem,TVI_LAST);
	//m_tree.InsertItem(STR_AFN_02_F3,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_02_F4,ico_fn,ico_sel,hitem,TVI_LAST);

	// afn 04
	hitem = m_tree.InsertItem(STR_AFN_04_SETP,ico_afn,ico_afn,TVI_ROOT);
	
	m_tree.InsertItem(STR_AFN_04_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F2,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F3,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F4,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F5,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F6,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F7,ico_fn,ico_sel,hitem,TVI_LAST);
	// m_tree.InsertItem(STR_AFN_04_F8,ico_fn,ico_sel,hitem,TVI_LAST);
	
	m_tree.InsertItem(STR_AFN_04_F9,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F10,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F11,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F12,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F13,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F14,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F15,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F16,ico_fn,ico_sel,hitem,TVI_LAST);
	
	m_tree.InsertItem(STR_AFN_04_F17,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F18,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F19,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F20,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F21,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F22,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F23,ico_fn,ico_sel,hitem,TVI_LAST);
	
	m_tree.InsertItem(STR_AFN_04_F25,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F26,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F27,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F28,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F29,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F30,ico_fn,ico_sel,hitem,TVI_LAST);
	
	// m_tree.InsertItem(STR_AFN_04_F31,ico_fn,ico_sel,hitem,TVI_LAST);
	
	m_tree.InsertItem(STR_AFN_04_F33,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F34,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F35,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_04_F49,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F36,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F37,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F38,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F39,ico_fn,ico_sel,hitem,TVI_LAST);
// 	
// 	m_tree.InsertItem(STR_AFN_04_F41,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F42,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F43,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F44,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F45,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F46,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F47,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F48,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F57,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F58,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F59,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F60,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F61,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F65,ico_fn,ico_sel,hitem,TVI_LAST);
// 	
// 	m_tree.InsertItem(STR_AFN_04_F66,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F67,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F68,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F73,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F74,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F75,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F76,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F81,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_04_F82,ico_fn,ico_sel,hitem,TVI_LAST);
	// 	m_tree.InsertItem(STR_AFN_04_F83,ico_fn,ico_sel,hitem,TVI_LAST);

	// afn 05
	hitem = m_tree.InsertItem(STR_AFN_05_CTRL,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_05_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F2,ico_fn,ico_sel,hitem,TVI_LAST);	
	m_tree.InsertItem(STR_AFN_05_F3,ico_fn,ico_sel,hitem,TVI_LAST);	
	m_tree.InsertItem(STR_AFN_05_F4,ico_fn,ico_sel,hitem,TVI_LAST);	
	m_tree.InsertItem(STR_AFN_05_F5,ico_fn,ico_sel,hitem,TVI_LAST);	
	m_tree.InsertItem(STR_AFN_05_F6,ico_fn,ico_sel,hitem,TVI_LAST);	
    m_tree.InsertItem(STR_AFN_05_F9,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F10,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F11,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F12,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F15,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F16,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F17,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F18,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F19,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F20,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F23,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F24,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F25,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F26,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F27,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_05_F28,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F29,ico_fn,ico_sel,hitem,TVI_LAST);		
// 	m_tree.InsertItem(STR_AFN_05_F31,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F32,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F33,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F34,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F35,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F36,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F37,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F38,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F39,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F41,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F42,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F49,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F50,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F51,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_05_F52,ico_fn,ico_sel,hitem,TVI_LAST);
//     m_tree.InsertItem(STR_AFN_05_F53,ico_fn,ico_sel,hitem,TVI_LAST);

	
	// afn06
	hitem = m_tree.InsertItem(STR_AFN_06_AUTH,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_06_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_06_F2,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_06_F3,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_06_F4,ico_fn,ico_sel,hitem,TVI_LAST);

	// afn 09
// 	hitem = m_tree.InsertItem(STR_AFN_09_CFIG,ico_afn,ico_afn,TVI_ROOT);
// 	m_tree.InsertItem(STR_AFN_09_F1,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_09_F4,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_09_F5,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_09_F6,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_09_F7,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_09_F8,ico_fn,ico_sel,hitem,TVI_LAST);

	// AFN 0A
	hitem = m_tree.InsertItem(STR_AFN_0A_GETP,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_0A_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F2,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F3,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F4,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F5,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F6,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F7,ico_fn,ico_sel,hitem,TVI_LAST);
	// m_tree.InsertItem(STR_AFN_0A_F8,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F9,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F10,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F11,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F12,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F13,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F14,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F15,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F16,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F17,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F18,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F19,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F20,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F21,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F22,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F23,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F25,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F26,ico_fn,ico_sel,hitem,TVI_LAST);

	 m_tree.InsertItem(STR_AFN_0A_F27,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F28,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F29,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F30,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F31,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F33,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F34,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F35,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F36,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F36,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F37,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F38,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F39,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F41,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F42,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F43,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F44,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F45,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F46,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F47,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F48,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F49,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0A_F57,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F58,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F59,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F60,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F61,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F65,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F66,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F67,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F68,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F73,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F74,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F75,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F76,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F81,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0A_F82,ico_fn,ico_sel,hitem,TVI_LAST);
// 		m_tree.InsertItem(STR_AFN_0A_F83,ico_fn,ico_sel,hitem,TVI_LAST);

	
	// AFN 0B
// 	hitem = m_tree.InsertItem(STR_AFN_0B_ASKT,ico_afn,ico_afn,TVI_ROOT);
// 	m_tree.InsertItem(STR_AFN_0B_F1,ico_fn,ico_sel,hitem,TVI_LAST);
// 	m_tree.InsertItem(STR_AFN_0B_F2,ico_fn,ico_sel,hitem,TVI_LAST);

	// 	AFN 0C
	hitem = m_tree.InsertItem(STR_AFN_0C_ASKT,ico_afn,ico_afn,TVI_ROOT);
	
		m_tree.InsertItem( STR_AFN_0C_F1 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F3终端参数状态"
		m_tree.InsertItem( STR_AFN_0C_F9 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F3终端参数状态"
// 		m_tree.InsertItem( STR_AFN_0C_F4 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F4终端上行通信状态"
// 		m_tree.InsertItem( STR_AFN_0C_F5 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F5终端控制设置状态"
// 		m_tree.InsertItem( STR_AFN_0C_F6 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F6终端当前控制状态"
// 		m_tree.InsertItem( STR_AFN_0C_F7 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F7终端事件计数器当前值"
// 		m_tree.InsertItem( STR_AFN_0C_F8 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F8终端事件标志状态"
// 		
// 		//2
// 		m_tree.InsertItem( STR_AFN_0C_F9 ,ico_fn,ico_sel,hitem,TVI_LAST);//"F9终端状态量及变位标志"
// 		m_tree.InsertItem( STR_AFN_0C_F10   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F10  终端与主站当日、月通信流量"
// 		m_tree.InsertItem( STR_AFN_0C_F11   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F10  终端集中抄表状态信息"
// 		
// 		//3
// 		m_tree.InsertItem( STR_AFN_0C_F17   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F17  当前总加有功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F18   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F18  当前总加无功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F19   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F19  当日总加有功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F20   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F20  当日总加无功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F21   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F21  当月总加有功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F22   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F22  当月总加无功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F23   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F23  终端当前剩余电量(费)"
// 		m_tree.InsertItem( STR_AFN_0C_F24   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F24  当前功率下浮控控后总加有功功率冻结值"
// 		
// 		//4
// 		m_tree.InsertItem( STR_AFN_0C_F25   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F25  当前三相及总有/无功功率、功率因数 , 三相电压、电流、零序电流、视在功率"
// 		m_tree.InsertItem( STR_AFN_0C_F26   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F26  A、B、C三相断相统计数据及最近一次断相记录"
// 		m_tree.InsertItem( STR_AFN_0C_F27   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F27  电能表日历时钟、编程次数及其最近一次操作时间"
// 		m_tree.InsertItem( STR_AFN_0C_F28   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F28  电表运行状态字及其变位标志"
// 		m_tree.InsertItem( STR_AFN_0C_F29   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F29  当前铜损、铁损有功总电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F30   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F30  上一结算日当前铜损、铁损有功总电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F31   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F31  当前A、B、C三相正/反向有功电能示值、组合无功1/2电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F32   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F32  上一结算日A、B、C三相正/反向有功电能示值、组合无功1/2电能示值"
// 		
// 		//5
// 		m_tree.InsertItem( STR_AFN_0C_F33   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F33  当前正向有/无功(组合无功1)电能示值、一/四象限无功电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F34   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F34  当前反向有/无功(组合无功2)电能示值、二/三象限无功电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F35   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F35  当月正向有/无功最大需量及发生时间"
// 		m_tree.InsertItem( STR_AFN_0C_F36   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F36  当月反向有/无功最大需量及发生时间"
// 		m_tree.InsertItem( STR_AFN_0C_F37   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F37  上月(上一结算日)正向有/无功(组合无功1)电能示值、一/四象限无功电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F38   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F38  上月(上一结算日)反向有/无功(组合无功2)电能示值、二/三象限无功电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F39   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F39  上月（上一结算日）正向有/无功最大需量及发生时间"
// 		m_tree.InsertItem( STR_AFN_0C_F40   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F40  上月（上一结算日）反向有/无功最大需量及发生时间"
// 		
// 		//6
// 		m_tree.InsertItem( STR_AFN_0C_F41   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F41  当日正向有功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F42   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F42  当日正向无功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F43   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F43  当日反向有功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F44   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F44  当日反向无功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F45   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F45  当月正向有功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F46   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F46  当月正向无功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F47   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F47  当月反向有功电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F48   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F48  当月反向无功电能量"
// 		
// 		//7
// 		m_tree.InsertItem( STR_AFN_0C_F49   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F49  当前电压、电流相位角"
// 		
// 		//8
// 		
// 		m_tree.InsertItem( STR_AFN_0C_F57   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F57  当前A、B、C三相电压、电流2～N次谐波有效值"
// 		m_tree.InsertItem( STR_AFN_0C_F58   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F58  当前A、B、C三相电压、电流2～N次谐波含有率"
// 		
// 		//9
// 		m_tree.InsertItem( STR_AFN_0C_F65   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F65  当前电容器投切状态"
// 		m_tree.InsertItem( STR_AFN_0C_F66   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F66  当前电容器累计补偿投入时间和次数"
// 		m_tree.InsertItem( STR_AFN_0C_F67   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F67  当日、当月电容器累计补偿的无功电能量"
// 		
// 		//10
// 		
// 		m_tree.InsertItem( STR_AFN_0C_F73   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F73  直流模拟量实时数据"
// 		//11
// 		m_tree.InsertItem( STR_AFN_0C_F81   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F81  小时冻结总加有功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F82   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F82  小时冻结总加无功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F83   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F83  小时冻结总加有功总电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F84   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F84  小时冻结总加无功总电能量"
// 		
// 		//12
// 		m_tree.InsertItem( STR_AFN_0C_F89   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F89  小时冻结有功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F90   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F90  小时冻结A相有功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F91   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F91  小时冻结B相有功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F92   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F92  小时冻结C相有功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F93   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F93  小时冻结无功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F94   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F94  小时冻结A相无功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F95   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F95  小时冻结B相无功功率"
// 		m_tree.InsertItem( STR_AFN_0C_F96   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F96  小时冻结C相无功功率"
// 		//13
// 		m_tree.InsertItem( STR_AFN_0C_F97   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F97  小时冻结A相电压"
// 		m_tree.InsertItem( STR_AFN_0C_F98   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F98  小时冻结B相电压"
// 		m_tree.InsertItem( STR_AFN_0C_F99   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F99  小时冻结C相电压"
// 		m_tree.InsertItem( STR_AFN_0C_F100   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F100  小时冻结A相电流"
// 		m_tree.InsertItem( STR_AFN_0C_F101   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F101  小时冻结B相电流"
// 		m_tree.InsertItem( STR_AFN_0C_F102   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F102  小时冻结C相电流"
// 		m_tree.InsertItem( STR_AFN_0C_F103   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F103  小时冻结零序电流"
// 		
// 		//14
// 		m_tree.InsertItem( STR_AFN_0C_F105   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F105  小时冻结正向有功总电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F106   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F106  小时冻结正向无功总电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F107   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F107  小时冻结反向有功总电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F108   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F108  小时冻结反向无功总电能量"
// 		m_tree.InsertItem( STR_AFN_0C_F109   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F109  小时冻结正向有功总电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F110   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F110  小时冻结正向无功总电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F111   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F111  小时冻结反向有功总电能示值"
// 		m_tree.InsertItem( STR_AFN_0C_F112   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F112  小时冻结反向无功总电能示值"
// 		
// 		//15
// 		m_tree.InsertItem( STR_AFN_0C_F113   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F113  小时冻结总功率因数"
// 		m_tree.InsertItem( STR_AFN_0C_F114   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F114  小时冻结A相功率因数"
// 		m_tree.InsertItem( STR_AFN_0C_F115   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F115  小时冻结B相功率因数"
// 		m_tree.InsertItem( STR_AFN_0C_F116   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F116  小时冻结C相功率因数"
// 		
// 		// 16
// 		m_tree.InsertItem( STR_AFN_0C_F121   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F121  小时冻结直流模拟量"
// 		
// 		//17
// 		m_tree.InsertItem( STR_AFN_0C_F129   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F129  当前正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F130   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F130  当前正向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F131   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F131  当前反向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F132   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F132  当前反向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F133   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F133  当前一象限无功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F134   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F134  当前二象限无功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F135   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F135  当前三象限无功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F136   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F136  当前四象限无功电能示值（总、费率1～M）"
// 		//18
// 		m_tree.InsertItem( STR_AFN_0C_F137   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F137  上月（上一结算日）正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F138   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F138  上月（上一结算日）正向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F139   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F139  上月（上一结算日）反向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F140   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F140  上月（上一结算日）反向无功（组合无功1）电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F141   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F141  上月（上一结算日）一象限无功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F142   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F142  上月（上一结算日）二象限无功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F143   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F143  上月（上一结算日）三象限无功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F144   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F144  上月（上一结算日）四象限无功电能示值（总、费率1～M）"
// 		
// 		//19
// 		m_tree.InsertItem( STR_AFN_0C_F145   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F145  当月正向有功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F146   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F146  当月正向无功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F147   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F147  当月反向有功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F148   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F148  当月反向无功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F149   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F149  上月（上一结算日）正向有功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F150   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F150  上月（上一结算日）正向无功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F151   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F151  上月（上一结算日）反向有功最大需量及发生时间（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F152   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F152  上月（上一结算日）反向无功最大需量及发生时间（总、费率1～M）"
// 		//20
// 		m_tree.InsertItem( STR_AFN_0C_F153   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F153  第一时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F154   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F154  第二时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F155   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F155  第三时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F156   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F156  第四时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F157   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F157  第五时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F158   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F158  第六时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F159   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F159  第七时区冻结正向有功电能示值（总、费率1～M）"
// 		m_tree.InsertItem( STR_AFN_0C_F160   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F160  第八时区冻结正向有功电能示值（总、费率1～M）"
// 		//21
// 		m_tree.InsertItem( STR_AFN_0C_F161   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F161  电能表远程控制通断电状态及记录"
// 		m_tree.InsertItem( STR_AFN_0C_F165   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F165  电能表开关操作次数及时间"
// 		m_tree.InsertItem( STR_AFN_0C_F166   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F166  电能表参数修改次数及时间"
// 		m_tree.InsertItem( STR_AFN_0C_F167   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F167  电能表购、用电信息"
// 		m_tree.InsertItem( STR_AFN_0C_F168   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F168  电能表结算信息"
// 		
// 		//22
// 		m_tree.InsertItem( STR_AFN_0C_F169   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F169  集中抄表中继路由信息"
// 		m_tree.InsertItem( STR_AFN_0C_F170   ,ico_fn,ico_sel,hitem,TVI_LAST);//"F170  集中抄表电表抄读信息"

		
	// AFN 0D
	hitem = m_tree.InsertItem(STR_AFN_0D_ASKR,ico_afn,ico_afn,TVI_ROOT);
	//组1 pn: p0/监测终端号
	m_tree.InsertItem(STR_CMD_AFN_D_F1_CLOCK, ico_fn,ico_sel,hitem,TVI_LAST);//日历时钟
	m_tree.InsertItem(STR_CMD_AFN_D_F2_PARA_STATE, ico_fn,ico_sel,hitem,TVI_LAST);//参数状态标志
	m_tree.InsertItem(STR_CMD_AFN_D_F3_EVENT_1, ico_fn,ico_sel,hitem,TVI_LAST);//重要事件计数器当前值
	m_tree.InsertItem(STR_CMD_AFN_D_F4_EVENT_2, ico_fn,ico_sel,hitem,TVI_LAST);//一般事件计数器当前值
	m_tree.InsertItem(STR_CMD_AFN_D_F5_EVENT_STATE, ico_fn,ico_sel,hitem,TVI_LAST);//事件状态标志
	m_tree.InsertItem(STR_CMD_AFN_D_F6_POWR_TIMES, ico_fn,ico_sel,hitem,TVI_LAST);//上电次数 
	//组2 pn:p0/监测终端号
	m_tree.InsertItem(STR_CMD_AFN_D_F9_STATE, ico_fn,ico_sel,hitem,TVI_LAST);//状态量及变位标志
	m_tree.InsertItem(STR_CMD_AFN_D_F10_SWITCH, ico_fn,ico_sel,hitem,TVI_LAST);//控制输出回路开关接入状态量及变位标志 
	//组4 pn:p0/电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F25_POWR_HAVE_T, ico_fn,ico_sel,hitem,TVI_LAST);//总有功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F26_POWR_NONE_T, ico_fn,ico_sel,hitem,TVI_LAST);//总无功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F27_FACTR_T, ico_fn,ico_sel,hitem,TVI_LAST);//总功率因数
	m_tree.InsertItem(STR_CMD_AFN_D_F28_FACTR_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相功率因素
	m_tree.InsertItem(STR_CMD_AFN_D_F29_FACTR_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相功率因数
	m_tree.InsertItem(STR_CMD_AFN_D_F30_FACTR_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相功率因数
	//组5 pn:p0/电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F33_DEMAND, ico_fn,ico_sel,hitem,TVI_LAST);//需量
	m_tree.InsertItem(STR_CMD_AFN_D_F34_DEMAND_MAX, ico_fn,ico_sel,hitem,TVI_LAST);//日最大需量
	m_tree.InsertItem(STR_CMD_AFN_D_F35_DEMAND_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日最大需量发生时间 
	//组6 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F41_POWR_HAVE_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相有功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F42_POWR_HAVE_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相有功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F43_POWR_HAVE_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相有功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F44_POWR_NONE_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相无功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F45_POWR_NONE_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相无功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F46_POWR_NONE_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相无功功率 
	//组7 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F49_POWR_HAVE_FRTH, ico_fn,ico_sel,hitem,TVI_LAST);//（正向）有功总电能示数
	m_tree.InsertItem(STR_CMD_AFN_D_F50_POWR_HAVE_BACK, ico_fn,ico_sel,hitem,TVI_LAST);//（反向）有功总电能示数
	m_tree.InsertItem(STR_CMD_AFN_D_F51_POWR_NONE_FRTH, ico_fn,ico_sel,hitem,TVI_LAST);//（正向）无功总电能示数
	m_tree.InsertItem(STR_CMD_AFN_D_F52_POWR_NONE_BACK, ico_fn,ico_sel,hitem,TVI_LAST);//（反向）无功总电能示数 
	//组8 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F57_VOLT_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压
	m_tree.InsertItem(STR_CMD_AFN_D_F58_VOLT_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压
	m_tree.InsertItem(STR_CMD_AFN_D_F59_VOLT_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压
	m_tree.InsertItem(STR_CMD_AFN_D_F60_VANGL_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压相位角
	m_tree.InsertItem(STR_CMD_AFN_D_F61_VANGL_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压相位角
	m_tree.InsertItem(STR_CMD_AFN_D_F62_VANGL_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压相位角
	m_tree.InsertItem(STR_CMD_AFN_D_F63_VOLT_UBL, ico_fn,ico_sel,hitem,TVI_LAST);//电压不平衡度
	m_tree.InsertItem(STR_CMD_AFN_D_F64_CIRCLE_V, ico_fn,ico_sel,hitem,TVI_LAST);//周波
	//组9 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F65_ELEC_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电流
	m_tree.InsertItem(STR_CMD_AFN_D_F66_ELEC_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电流
	m_tree.InsertItem(STR_CMD_AFN_D_F67_ELEC_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电流
	m_tree.InsertItem(STR_CMD_AFN_D_F68_ELEC_M, ico_fn,ico_sel,hitem,TVI_LAST);//中性线电流
	m_tree.InsertItem(STR_CMD_AFN_D_F69_EANGL_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电流相位角
	m_tree.InsertItem(STR_CMD_AFN_D_F70_EANGL_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电流相位角
	m_tree.InsertItem(STR_CMD_AFN_D_F71_EANGL_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电流相位角
	m_tree.InsertItem(STR_CMD_AFN_D_F72_ELEC_UBL, ico_fn,ico_sel,hitem,TVI_LAST);//电流不平衡度 
	//组10 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F73_VDMAX_A, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电压极大值
	m_tree.InsertItem(STR_CMD_AFN_D_F74_VDMAX_A_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电压极大值发生时间
	m_tree.InsertItem(STR_CMD_AFN_D_F75_VDMAX_B, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电压极大值
	m_tree.InsertItem(STR_CMD_AFN_D_F76_VDMAX_B_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电压极大值发生时间
	m_tree.InsertItem(STR_CMD_AFN_D_F77_VDMAX_C, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电压极大值
	m_tree.InsertItem(STR_CMD_AFN_D_F78_VDMAX_C_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电压极大值发生时间 
	//组11 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F81_IDMAX_A, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电流极大值
	m_tree.InsertItem(STR_CMD_AFN_D_F82_IDMAX_A_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日A相电流极大值发生时间
	m_tree.InsertItem(STR_CMD_AFN_D_F83_IDMAX_B, ico_fn,ico_sel,hitem,TVI_LAST);//日B相电流极大值
	m_tree.InsertItem(STR_CMD_AFN_D_F84_IDMAX_B_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日B相电流极大值发生时间
	m_tree.InsertItem(STR_CMD_AFN_D_F85_IDMAX_C, ico_fn,ico_sel,hitem,TVI_LAST);//日C相电流极大值
	m_tree.InsertItem(STR_CMD_AFN_D_F86_IDMAX_C_TIME, ico_fn,ico_sel,hitem,TVI_LAST);//日C相电流极大值发生时间 
	//组12 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F89_TFW_HAVE, ico_fn,ico_sel,hitem,TVI_LAST);//总基波有功功率(Total Fundamental Wave)
	m_tree.InsertItem(STR_CMD_AFN_D_F90_TFW_NONE, ico_fn,ico_sel,hitem,TVI_LAST);//总基波无功功率
	m_tree.InsertItem(STR_CMD_AFN_D_F91_THW_HAVE, ico_fn,ico_sel,hitem,TVI_LAST);//总谐波有功功率(Total Harmonic Wave)
	m_tree.InsertItem(STR_CMD_AFN_D_F92_THW_NONE, ico_fn,ico_sel,hitem,TVI_LAST);//总基波无功功率 
	//组13 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F97_VDPP_TIME_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压越上上限日累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F98_VDPP_TIME_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压越上上限日累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F99_VDPP_TIME_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压越上上限日累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F100_VDNN_TIME_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压越下下限日累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F101_VDNN_TIME_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压越下下限日累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F102_VDNN_TIME_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压越下下限日累计时间
	//组14 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F105_VMPP_TIME_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压越上上限月累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F106_VMPP_TIME_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压越上上限月累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F107_VMPP_TIME_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压越上上限月累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F108_VMNN_TIME_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压越下下限月累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F109_VMNN_TIME_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压越下下限月累计时间
	m_tree.InsertItem(STR_CMD_AFN_D_F110_VMNN_TIME_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压越下下限月累计时间 
	//组15 pn:电气测量点号 (aberrance)
	m_tree.InsertItem(STR_CMD_AFN_D_F113_VABR_TOTL_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压总畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F114_VABR_TOTL_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压总畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F115_VABR_TOTL_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压总畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F116_EABR_TOTL_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电流总畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F117_EABR_TOTL_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电流总畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F118_EABR_TOTL_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电流总畸变率 
	//组16 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F121_VABR_ODD_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压奇次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F122_VABR_EVN_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电压偶次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F123_VABR_ODD_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压奇次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F124_VABR_EVN_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电压偶次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F125_VABR_ODD_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压奇次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F126_VABR_EVN_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电压偶次畸变率 
	//组17 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F128_EABR_OOD_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电流奇次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F129_EABR_EVN_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相电流偶次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F130_EABR_OOD_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电流奇次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F131_EABR_EVN_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相电流偶次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F132_EABR_OOD_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电流奇次畸变率
	m_tree.InsertItem(STR_CMD_AFN_D_F133_EABR_EVN_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相电流偶次畸变率
	//组18 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F137_FLS_SHRT_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相短时闪变
	m_tree.InsertItem(STR_CMD_AFN_D_F138_FLS_SHRT_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相短时闪变
	m_tree.InsertItem(STR_CMD_AFN_D_F139_FLS_SHRT_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相短时闪变
	m_tree.InsertItem(STR_CMD_AFN_D_F140_FLS_LONG_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相长时闪变
	m_tree.InsertItem(STR_CMD_AFN_D_F141_FLS_LONG_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相长时闪变
	m_tree.InsertItem(STR_CMD_AFN_D_F142_FLS_LONG_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相长时闪变 
	//组19 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F145_HARM_VOLT_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相N次谐波电压
	m_tree.InsertItem(STR_CMD_AFN_D_F146_HARM_VOLT_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相N次谐波电压
	m_tree.InsertItem(STR_CMD_AFN_D_F147_HARM_VOLT_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相N次谐波电压
	m_tree.InsertItem(STR_CMD_AFN_D_F148_HARM_ELEC_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相N次谐波电流
	m_tree.InsertItem(STR_CMD_AFN_D_F149_HARM_ELEC_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相N次谐波电流
	m_tree.InsertItem(STR_CMD_AFN_D_F150_HARM_ELEC_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相N次谐波电流 
	//组20 pn:电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F153_HARM_VINC_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相N次谐波电压含有率
	m_tree.InsertItem(STR_CMD_AFN_D_F154_HARM_VINC_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相N次谐波电压含有率
	m_tree.InsertItem(STR_CMD_AFN_D_F155_HARM_VINC_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相N次谐波电压含有率
	m_tree.InsertItem(STR_CMD_AFN_D_F156_HARM_EINC_A, ico_fn,ico_sel,hitem,TVI_LAST);//A相N次谐波电流含有率
	m_tree.InsertItem(STR_CMD_AFN_D_F157_HARM_EINC_B, ico_fn,ico_sel,hitem,TVI_LAST);//B相N次谐波电流含有率
	m_tree.InsertItem(STR_CMD_AFN_D_F158_HARM_EINC_C, ico_fn,ico_sel,hitem,TVI_LAST);//C相N次谐波电流含有率 
	//组30 pn:非电气测量点号
	m_tree.InsertItem(STR_CMD_AFN_D_F233_NELC_VALUE, ico_fn,ico_sel,hitem,TVI_LAST);//非电气量


	// 0E
	hitem = m_tree.InsertItem(STR_AFN_0E_ASKE,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_0E_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_0E_F2,ico_fn,ico_sel,hitem,TVI_LAST);
		m_tree.InsertItem(STR_AFN_0E_F3,ico_fn,ico_sel,hitem,TVI_LAST);
	
	// 0F
	hitem = m_tree.InsertItem(STR_AFN_0F_FILE,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_0F_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	
	// 10
	hitem = m_tree.InsertItem(STR_AFN_10_DATA,ico_afn,ico_afn,TVI_ROOT);
	m_tree.InsertItem(STR_AFN_10_F1,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_10_F9,ico_fn,ico_sel,hitem,TVI_LAST);
	m_tree.InsertItem(STR_AFN_10_F10,ico_fn,ico_sel,hitem,TVI_LAST);
    m_tree.InsertItem(STR_AFN_10_F11,ico_fn,ico_sel,hitem,TVI_LAST);
}

void CTabDlgPreMaster::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CTabDlgPreMaster::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	initProtoTree();
	initList();


		m_btn_modify.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_modify.SetIcon(IDI_ICON_NOTE);
	m_btn_modify.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_modify.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTabDlgPreMaster::setTreePos()
{
	
	RECT rect_tree, rect_list,rect_client;
	GetClientRect(&rect_client);

	// tree
	const int top    = 10;
	const int border = 3;
	const int weight = 270;
	const int height = 250;
	rect_tree.top    = rect_client.top  + top;
	rect_tree.left   = rect_client.left + border;
	rect_tree.right  = rect_client.right   - border;
	rect_tree.bottom = rect_tree.top    + height;

	if(m_tree.m_hWnd)
	{
		m_tree.MoveWindow(&rect_tree);
	}


	// list
	rect_list.top = rect_tree.bottom + top + 50;
	rect_list.left = rect_tree.left;
	rect_list.right = rect_client.right - border;
	rect_list.bottom = rect_client.bottom - border;
	if(m_list.m_hWnd)
	{
		m_list.MoveWindow(&rect_list);
	}


}


void CTabDlgPreMaster::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	setTreePos();
}

void CTabDlgPreMaster::OnItemexpandedTreePreMst(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}



void CTabDlgPreMaster::ShowMstPreAfn04F1()
{
	/*

	// 取出预配数据
	sMtAfn04F1 sCnf;
	m_nxCfg.GetMstPreAfn04F1(&sCnf);
	
	// 插入列表显示
	CString   name_ucRTS             = "终端数传机延时时间RTS";             // 终端数传机延时时间RTS
	CString   name_ucRTM             = "终端作为启动站允许发送传输延时时间";           
	CString   name_ucReSendTimes     = "重发次数";     // 重发次数 (0~3)   0 表示不允许重发
	CString   name_ucHeartBeat       = "心跳周期";       // 
	CString   name_usTmWaitTimeoutS  = "集中器等待从动站响应的超时时间";  //  秒数 0~4095
	CString   name_bAutoReportAsk_1  = "允许自动上报1类数据，同时需要主站确认";  // 
	CString   name_bAutoReportAsk_2  = "允许自动上报2类数据，同时需要主站确认";  // 
	CString   name_bAutoReportAsk_3  = "允许自动上报3类数据，同时需要主站确认";  // 
	
	CString   value_ucRTS;             // 终端数传机延时时间RTS
	CString   value_ucRTM;             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   value_ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
	CString   value_ucHeartBeat;       // 心跳周期
	CString   value_usTmWaitTimeoutS;  // 集中器等待从动站响应的超时时间 秒数 0~4095
	CString   value_bAutoReportAsk_1;  // 允许自动上报1类数据，同时需要主站确认
	CString   value_bAutoReportAsk_2;  // 允许自动上报2类数据，同时需要主站确认
    CString   value_bAutoReportAsk_3;  // 允许自动上报3类数据，同时需要主站确认
	
	value_ucRTS.Format("%d",sCnf.ucRTS);
	value_ucRTM.Format("%d",sCnf.ucRTM);
	value_ucReSendTimes.Format("%d",sCnf.ucReSendTimes);
	value_ucHeartBeat.Format("%d",  sCnf.ucHeartBeat);
	value_usTmWaitTimeoutS.Format("%d",sCnf.usTmWaitTimeoutS);
	value_bAutoReportAsk_1.Format("%s",sCnf.bAutoReportAsk_1 == TRUE ? "允许":"禁止");
	value_bAutoReportAsk_2.Format("%s",sCnf.bAutoReportAsk_2 == TRUE ? "允许":"禁止");
	value_bAutoReportAsk_3.Format("%s",sCnf.bAutoReportAsk_3 == TRUE ? "允许":"禁止");
		
	CString   format_ucRTS            = FMT_MS_20;             // 终端数传机延时时间RTS
	CString   format_ucRTM            = FMT_MINUTE;             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   format_ucReSendTimes    = FMT_TIMES;     // 重发次数 (0~3)   0 表示不允许重发
	CString   format_ucHeartBeat      = FMT_MINUTE;       // 心跳周期
	CString   format_usTmWaitTimeoutS = FMT_SECOND;  // 集中器等待从动站响应的超时时间 秒数 0~4095
	CString   format_bAutoReportAsk_1 = FMT_BOOL;  // 允许自动上报1类数据，同时需要主站确认
	CString   format_bAutoReportAsk_2 = FMT_BOOL;  // 允许自动上报2类数据，同时需要主站确认
    CString   format_bAutoReportAsk_3 = FMT_BOOL;  // 允许自动上报3类数据，同时需要主站确认
	
		
	CString   limit_ucRTS;             // 终端数传机延时时间RTS
	CString   limit_ucRTM;             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	CString   limit_ucReSendTimes = "0 ~ 3";     // 重发次数 (0~3)   0 表示不允许重发
	CString   limit_ucHeartBeat;       // 心跳周期
	CString   limit_usTmWaitTimeoutS = "0 ~ 4095";  // 集中器等待从动站响应的超时时间 秒数 0~4095
	CString   limit_bAutoReportAsk_1;  // 允许自动上报1类数据，同时需要主站确认
	CString   limit_bAutoReportAsk_2;  // 允许自动上报2类数据，同时需要主站确认
    CString   limit_bAutoReportAsk_3;  // 允许自动上报3类数据，同时需要主站确认
	
	
	m_list.DeleteAllItems();
	
	m_list.AddItem(name_ucRTS,value_ucRTS,format_ucRTS,limit_ucRTS);
	m_list.AddItem(name_ucRTM,value_ucRTM,format_ucRTM,limit_ucRTM);
	m_list.AddItem(name_ucReSendTimes,value_ucReSendTimes,format_ucReSendTimes,limit_ucReSendTimes);
	m_list.AddItem(name_ucHeartBeat,value_ucHeartBeat,format_ucHeartBeat,limit_ucHeartBeat);
	m_list.AddItem(name_usTmWaitTimeoutS,value_usTmWaitTimeoutS,format_usTmWaitTimeoutS,limit_usTmWaitTimeoutS);
	m_list.AddItem(name_bAutoReportAsk_1,value_bAutoReportAsk_1,format_bAutoReportAsk_1,limit_bAutoReportAsk_1);
	m_list.AddItem(name_bAutoReportAsk_2,value_bAutoReportAsk_2,format_bAutoReportAsk_2,limit_bAutoReportAsk_2);
	m_list.AddItem(name_bAutoReportAsk_3,value_bAutoReportAsk_3,format_bAutoReportAsk_3,limit_bAutoReportAsk_3);
*/

	/* 以上为原3761实现*/
	sMcAfn04f1 sData;
	m_nxCfg.GetPreAfn04F1(&sData,TRUE);
	
	// 插入列表显示
	CString   name_ucPermitDelayM             = "集中器作为启动站允许传输延时时间";           
	CString   name_ucReSendTimes             = "重发次数 (0~3)   0 表示不允许重发";           
	CString   name_ucHeartBeat       = "心跳周期";      
	CString   name_usWaitTimeoutS  = "中器为启动站等待应答的超时时间";  
	CString   name_bPermitRt  = "实时数据 允许确认";  
	CString   name_bPermitTk  = "任务数据 允许确认";  
	CString   name_bPermitEv  = "事件数据 允许确认"; 
	
    
	CString   value_ucRTM;           
	CString   value_ucReSendTimes;    
	CString   value_ucHeartBeat;     
	CString   value_usTmWaitTimeoutS; 
	CString   value_bPermitRt; 
	CString   value_bPermitTk;  
    CString   value_bPermitEv;  
	
	
	value_ucRTM.Format("%d",sData.ucPermitDelayM);
	value_ucReSendTimes.Format("%d",sData.ucReSendTimes);
	value_ucHeartBeat.Format("%d",  sData.ucHeartBeat);
	value_usTmWaitTimeoutS.Format("%d",sData.usWaitTimeoutS);
	value_bPermitRt.Format("%s",sData.bPermitRt == TRUE ? "允许":"禁止");
	value_bPermitTk.Format("%s",sData.bPermitTk == TRUE ? "允许":"禁止");
	value_bPermitEv.Format("%s",sData.bPermitEv == TRUE ? "允许":"禁止");
	
	
	CString   format_ucRTM            = FMT_MINUTE;         
	CString   format_ucReSendTimes    = FMT_TIMES;   
	CString   format_ucHeartBeat      = FMT_MINUTE;    
	CString   format_usTmWaitTimeoutS = FMT_SECOND;  
	CString   format_bPermitRt = FMT_BOOL; 
	CString   format_bPermitTk = FMT_BOOL; 
    CString   format_bPermitEv = FMT_BOOL; 
	
	
	
	CString   limit_ucRTM;           
	CString   limit_ucReSendTimes = "0 ~ 3";     
	CString   limit_ucHeartBeat;     
	CString   limit_usTmWaitTimeoutS = "0 ~ 4095";  
	CString   limit_bPermitRt; 
	CString   limit_bPermitTk; 
    CString   limit_bPermitEv;  
	
	
	m_list.DeleteAllItems();
	
	
	m_list.AddItem(name_ucPermitDelayM,value_ucRTM,format_ucRTM,limit_ucRTM);
	m_list.AddItem(name_ucReSendTimes,value_ucReSendTimes,format_ucReSendTimes,limit_ucReSendTimes);
	m_list.AddItem(name_ucHeartBeat,value_ucHeartBeat,format_ucHeartBeat,limit_ucHeartBeat);
	m_list.AddItem(name_usWaitTimeoutS,value_usTmWaitTimeoutS,format_usTmWaitTimeoutS,limit_usTmWaitTimeoutS);
	m_list.AddItem(name_bPermitRt,value_bPermitRt,format_bPermitRt,limit_bPermitRt);
	m_list.AddItem(name_bPermitTk,value_bPermitTk,format_bPermitTk,limit_bPermitTk);
	m_list.AddItem(name_bPermitEv,value_bPermitEv,format_bPermitEv,limit_bPermitEv);

}

void CTabDlgPreMaster::ShowMstPreAfn04F34()
{
	CNxConfig cfg;
	sMcAfn04f34 sAfn04f34;		
	cfg.GetPreAfn04F34(&sAfn04f34, TRUE);

	CString strUp, strDn;
	CString name_type = "非电气量";
	CString name_up   = "量程上限";
	CString name_dn   = "量程下限";
	
	CString val_type;
	CString formt_value;
	CString info_up,info_dn;

	
	switch (sAfn04f34.eType)
	{
	case MC_NELC_TEMP:
		val_type = "温度";
		break;
		
	case MC_NELC_FLOW:
		val_type = "流量";
		break;

	case MC_NELC_FV:
		val_type = "流速";
		break;
		
	case MC_NELC_PRESS:
		val_type = "压力";
		break;
		
	case MC_NELC_HUMI:
		val_type = "湿度";
		break;
		
	case MC_NELC_LIGHT:
		val_type = "照度";
		break;
		
	case MC_NELC_RV:
		val_type = "转速";
		break;
		
	case MC_NELC_420MA:
		val_type = "4~20MA";
		break;
		
	default:
		val_type = "未知类型";
		break;
	}

	
	switch(sAfn04f34.sUp.ePrec)
	{
	case MC_PREC_P4:
		info_up = "0, (+/-)10000~99999990000\n";
		break;
		
	case MC_PREC_P3:
		info_up = "0, (+/-)1000~9999999000\n";
		break;
		
	case MC_PREC_P2:
		info_up = "0, (+/-)100~999999900\n";
		break;
		
	case MC_PREC_P1:
		info_up = "0, (+/-)10~99999990\n";
		break;
		
	case MC_PREC_P0:
		info_up = "0, (+/-)1~9999999\n";
		break;
		
	case MC_PREC_N1:
		info_up = "0, (+/-)0.1~999999.9\n";
		
		break;				
		
	case MC_PREC_N2:
		info_up = "0, (+/-)0.01~99999.99\n";
		break;
		
	case MC_PREC_N3:
		info_up = "0, (+/-)0.001~9999.999\n";
		break;	
		
	default:
		info_up = "未知\n";
		break;
	}


	switch (sAfn04f34.sUp.ePrec)
	{
	case  MC_PREC_P4:
	case MC_PREC_P3:
	case MC_PREC_P2:
	case MC_PREC_P1:
	case MC_PREC_P0:
		strUp.Format("%0.0f", sAfn04f34.sUp.dValue);
		strDn.Format("%0.0f", sAfn04f34.sDown.dValue);
		formt_value = "整数";
		break;
		
	case MC_PREC_N1:
		strUp.Format("%0.1f", sAfn04f34.sUp.dValue);
		strDn.Format("%0.1f", sAfn04f34.sDown.dValue);
		formt_value = "浮点数";
		break;
		
		
	case MC_PREC_N2:
		strUp.Format("%0.2f", sAfn04f34.sUp.dValue);
		strDn.Format("%0.2f", sAfn04f34.sDown.dValue);
		formt_value = "浮点数";
		break;
		
		
	case MC_PREC_N3:
		strUp.Format("%0.3f", sAfn04f34.sUp.dValue);
		strDn.Format("%0.3f", sAfn04f34.sDown.dValue);
		formt_value = "浮点数";
		break;
		
	default:
		break;
	}

	
	m_list.DeleteAllItems();
	m_list.AddItem(name_type,val_type,"自定义","");
	m_list.AddItem(name_up,strUp,formt_value,info_up);
	m_list.AddItem(name_dn,strDn,formt_value,info_up);
	
}

// 显示 非电气量参数设置预配信息
void CTabDlgPreMaster::ShowMstPreAfn04F33()
{
#if 0
	CNxConfig cfg;
	
	UINT16 usPn = 0;
	sMtCfgNotElec sCfgNotElec;
	CString strPn, strMax, strMin, strType;
	
	cfg.GetPreAfn04F33(&usPn,&sCfgNotElec, MT_ROLE_MASTER);
	
	
	


	// 插入列表显示
	CString   name_pn      = "测量点号";            
	CString   name_type    = "非电气量类型";           
	CString   name_max     = "量程上限";     
	CString   name_min     = "量程下限";      

	
	strMax.Format("%0.3lf",sCfgNotElec.dMax);
	strMin.Format("%0.3lf",sCfgNotElec.dMin);
	switch (sCfgNotElec.eType)
	{
	case MT_NELEC_TEMP:
		strType = "温度";
		break;
	case MT_NELEC_FLOW:
		strType = "流量";
		break;
	case MT_NELEC_FLOW_V:
		strType = "流速";
		break;
	case MT_NELEC_PRESS:
		strType = "压力";
		break;
	case MT_NELEC_HUMID:
		strType = "湿度";
		break;
	case MT_NELEC_ILLUM:
		strType = "照度";
		break;
		
	case MT_NELEC_ROTATE:
		strType = "转速";
		break;
		
	default:
		strType = "未知非电气量";
		break;
	}
		
	strPn.Format("%d", usPn);

	
	CString   format_pn     = FMT_PN;            
	CString   format_type   = "";           
	CString   format_max    = "";    
	CString   format_min    = "";      
	
	CString   limit_pn     = "0 ~ 65535";             
	CString   limit_type   = "1 - 7";            
	CString   limit_max = "9999.999";    
	CString   limit_min = "-9999.999"; ;       
	
	m_edit_pn.SetWindowText(strPn);
	m_edit_pn.EnableWindow(TRUE);

	m_list.DeleteAllItems();
	m_list.AddItem(name_pn,strPn,format_pn,limit_pn);
	m_list.AddItem(name_type,strType,format_type,limit_type);
	m_list.AddItem(name_max,strMax,format_max,limit_max);
	m_list.AddItem(name_min,strMin,format_min,limit_min);

#endif
}


void CTabDlgPreMaster::setItemColors()
{
	int i, nItemCount = 0;
	nItemCount = m_list.GetItemCount();
	for (i = 0; i < nItemCount; i++)
	{
		m_list.SetItemColor(i,0,RGB(0,64,128),RGB(255,255,255));
		m_list.SetItemColor(i,1,RGB(255,0,255),RGB(255,255,255));
		m_list.SetItemColor(i,2,RGB(128,64,0),RGB(255,255,255));
		m_list.SetItemColor(i,3,RGB(255,0,0),RGB(255,255,255));
	}
}



void CTabDlgPreMaster::OnSelchangedTreePreMst(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	HTREEITEM hParent, hChild;
	CString strChildText, strParentText,str;
	eMcErr eRet = MC_OK;
	hChild = pNMTreeView->itemNew.hItem;
	strChildText = m_tree.GetItemText(hChild);
	hParent      = m_tree.GetParentItem(hChild);

	m_eCmd = CMD_AFN_F_UNKOWN;
	m_mcmd = MCMD_AFN_F_UNKOWN;
	// 清除显示列表
	m_list.DeleteAllItems();

    GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_PN)->EnableWindow(FALSE);

	if (hParent == NULL)
	{
			//AfxMessageBox("root");
			return;
	}

	strParentText = m_tree.GetItemText(hParent);

	UINT16 usCmd = 0;
	UINT8 ucAfn = 0;
	UINT8 ucFn  = 0;

	// 分命令设置数据参数
	if(strParentText == STR_AFN_00_CONF)
	{
		if(strChildText == STR_AFN_00_F1)
		{
			GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
			m_mcmd = MCMD_AFN_0_F1_ALL_OK_DENY;
			showMstPreAfn00F1();	
		}
	}

	if(strParentText == STR_AFN_01_RSET)
	{
		if(strChildText != STR_AFN_01_F5)
		{
			showMstNullData();	
		}
	}

	if(strParentText == STR_AFN_02_LINK)
	{
		showMstNullData();	
	}




	// 设置参数
	if(strParentText == STR_AFN_04_SETP)
	{
		if(strChildText == STR_AFN_04_F1)
		{
			GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
			m_mcmd = MCMD_AFN_4_F1_CON_UP_CFG;
			ShowMstPreAfn04F1();	
		}
		
#if 0
		if (strChildText == STR_AFN_04_F33)
		{
			GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
		//	m_eCmd = CMD_AFN_4_FN_33_CFG_NOT_ELEC;
			ShowMstPreAfn04F33();
		}

#endif
		if (strChildText == STR_AFN_04_F34)
		{
		
			ShowMstPreAfn04F34();
		}

		if (strChildText == STR_AFN_04_F35)
		{
			
			ShowMstPreAfn04F35();
		}

		if (strChildText == STR_AFN_04_F3)
		{
			ShowMstPreAfn04F3();
		}


		if (strChildText == STR_AFN_04_F4)
		{
			ShowMstPreAfn04F4();
		}

		
		if (strChildText == STR_AFN_04_F7)
		{
			ShowMstPreAfn04F7();
		}
	}
	
	// 请求一类数据
	if(strParentText == STR_AFN_0C_ASKT)
	{
// 		if(strChildText == STR_AFN_0C_F90)
// 		{
// 			GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
// 			//m_eCmd = CMD_AFN_C_FN_90_NOT_ELEC;
// 			//showMstPreAfn0cF90_NotElec();	
// 		}
	
	}


	// 合成命令
	if(strParentText == STR_AFN_00_CONF)
	{
		ucAfn = 0;
	}
	else if(strParentText == STR_AFN_01_RSET)
	{
		ucAfn = 1;
	}
	else if(strParentText == STR_AFN_02_LINK)
	{
		ucAfn = 2;
	}
// 	else if(strParentText == STR_AFN_03_RELY)
// 	{
// 		ucAfn = 3;
// 	}
	else if(strParentText == STR_AFN_04_SETP)
	{
		ucAfn = 4;
	}	
	else if(strParentText == STR_AFN_05_CTRL)
	{
		ucAfn = 5;
	}
	else if(strParentText == STR_AFN_06_AUTH)
	{
		ucAfn = 6;
	}
	else if(strParentText == STR_AFN_08_CASC)
	{
		ucAfn = 8;
	}
// 	else if(strParentText == STR_AFN_09_CFIG)
// 	{
// 		ucAfn = 9;
// 	}
	else if(strParentText == STR_AFN_0A_GETP)
	{
		ucAfn = 0x0A;
	}	
// 	else if(strParentText == STR_AFN_0B_ASKT)
// 	{
// 		ucAfn = 0x0B;
// 	}
	else if(strParentText == STR_AFN_0C_ASKT)
	{
		ucAfn = 0x0C;
	}
	else if(strParentText == STR_AFN_0D_ASKR)
	{
		ucAfn = 0x0D;
	}
	else if(strParentText == STR_AFN_0E_ASKE)
	{
		ucAfn = 0x0E;
	}	
	else if(strParentText == STR_AFN_0F_FILE)
	{
		ucAfn = 0xF;
	}
	else if(strParentText == STR_AFN_10_DATA)
	{
		ucAfn = 0x10;
	}


	CString strTmp;
	strTmp = strChildText.Left(strChildText.Find(" "));
	strTmp = strTmp.Right(strTmp.GetLength() - 1);
	ucFn = atoi(strTmp);
	
	usCmd = ucFn + (ucAfn << 8);
	//m_eCmd = (eMtCmd)usCmd;
	m_mcmd = (eMcmd)usCmd;
	// 显示Pn
	//获得该命令的类型
		
	//sMtCmdInfor sCmdInfor;
	//	eRet = eMtGetCmdInfor(m_eCmd, MT_DIR_M2S, &sCmdInfor);

	
	sMcmdInfor sCmdInfor;
	eRet = eMcGetCmdInfor(m_mcmd, MC_DIR_M2S, &sCmdInfor);
	if(MC_OK != eRet)
	{
		return;
	}
		
	if (sCmdInfor.pFunc == NULL)
	{
		m_btn_modify.EnableWindow(FALSE);
		showMstNullData();
	}
	else
	{
		m_btn_modify.EnableWindow(TRUE);
	}
		

	// pn = p0
	if(sCmdInfor.ePn == MC_PN_P0)
	{
		m_edit_pn.EnableWindow(FALSE);
		m_edit_pn.SetWindowText("0:集中器");
	}
	else
	{
		m_edit_pn.EnableWindow(TRUE);
		CString strPn;
		// 将注册表中该命令对应的预设置的pn值读出来
		m_nxCfg.GetPrePnStr31(m_mcmd, MC_ROLE_MASTER, &strPn);
		m_edit_pn.SetWindowText(strPn);
	}

	setItemColors();
	*pResult = 0;
}

void CTabDlgPreMaster::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	switch (m_mcmd)
	{


	case MCMD_AFN_0_F1_ALL_OK_DENY:
		{
			CDlgPreA00F1 dlg;
			if (dlg.DoModal() == IDOK)
			{
		    	showMstPreAfn00F1();
			}
		}
		break;

	case MCMD_AFN_4_F1_CON_UP_CFG:
		{
			CDlgPreAfn04F1 dlg;
			dlg.setTitle("AFN04_F1 信息集中与交互终端上行通信口通信参数");
			dlg.m_bPreMaster = TRUE;
			if(dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F1();
			}

		}
		break;
		
		
	case MCMD_AFN_4_F2_MST_PARA:
		{
			CDlgPreAfn04F2 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F2();
			}
		}
		break;


	case MCMD_AFN_4_F3_CON_AUTH_PARA:
		{
			CDlgPreAfn04F3 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F3();
			}
		}
		break;

	case MCMD_AFN_4_F4_TEAM_ADDR:
		{
			CDlgPreAfn04F4 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F4();
			}
		}
		break;


	case MCMD_AFN_4_F5_CON_IP_PORT:
		{
			CDlgPreAfn04F5 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F4();
			}
		}
		break;

	case MCMD_AFN_4_F6_CON_CASC:
		{
			CDlgPreAfn04F6 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F4();
			}
		}
		break;


	case MCMD_AFN_4_F7_CON_DOWN_CFG:
		{
			CDlgPreAfn04F7 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F7();
			}
		}
		break;

	case MCMD_AFN_4_F9_CON_EVENT_CFG:
		{
			CDlgPreAfn04F9 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;
	case MCMD_AFN_4_F17_TML_UP_CFG:
		{
			CDlgPreAfn04F17 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;
	case MCMD_AFN_4_F10_CON_STATE_INPUT:
		{
			CDlgPreAfn04F10 dlg;
			dlg.m_bPreMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F7();
			}
		}
		break;

	case MCMD_AFN_4_F25_ELEC_MP_CFG:
		{
			CDlgPreAfn04F25_33 dlg;
			dlg.m_bF25Elec = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}
		
		break;
		
	case MCMD_AFN_4_F26_ELEC_MP_BASE:
		{
			CDlgPreAfn04F26 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}
		break;
		
	case MCMD_AFN_4_F27_ELEC_LMIT_POWER:
		{
			CDlgPreAfn04F27 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F28_ELEC_LMIT_FACTR:
		{
			CDlgPreAfn04F28 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F30_ELEC_FLASH:
		{
			CDlgPreAfn04F30 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F29_ELEC_FIX_HARM:
		{
			CDlgPreAfn04F29 dlg;
			dlg.m_bMaster = TRUE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}	
		break;

	case MCMD_AFN_4_F33_NELC_MP_CFG:
		{
			CDlgPreAfn04F25_33 dlg;
			dlg.m_bF25Elec = FALSE;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F34();
			}
		}
		
		break;


	case MCMD_AFN_4_F34_NELC_MP_PARA:
		{
			CDlgPreAfn04F34 dlg;
			if (dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F34();
			}
		}

		break;
	
	case MCMD_AFN_4_F35_NELC_MP_LMIT:
		{
			CDlgPreAfn04F35 dlg;
			if (dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F35();
			}
		}

	break;

	case MCMD_AFN_4_F49_FREZ_TASK_PARA:
		{
			CDlgPreAfn04F49 dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}
		
	break;

	case MCMD_AFN_A_F2_MST_PARA:
		{
			CDlgPreAfn0aF2 dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}
		
	break;

	case MCMD_AFN_A_F7_CON_DOWN_CFG:
		{
			CDlgPreAfn0AF7Q dlg;
			if (dlg.DoModal() == IDOK)
			{
				//ShowMstPreAfn04F35();
			}
		}
		
	break;

/*
	case CMD_AFN_4_F1_TML_UP_CFG:
		{
			CDlgPreAfn04F1 dlg;
			dlg.setTitle("主站预设置 (AFN_04 F1) 集中器上行通信口通信参数设置");
			dlg.m_bPreMaster = TRUE;
			if(dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F1();
			}
		}
	  break;

	case CMD_AFN_4_FN_33_CFG_NOT_ELEC:
		{
			
			CDlgPreAfn04F33 dlg;
	
			if(dlg.DoModal() == IDOK)
			{
				ShowMstPreAfn04F33();
			}
		}
	  break;
		
	case CMD_AFN_C_FN_90_NOT_ELEC:
		{
			CDlgPreAfn0cF90_NotElec dlg;
			dlg.setRole(TRUE);
			if(dlg.DoModal() == IDOK)
			{
				showMstPreAfn0cF90_NotElec();
			}
		
		}
		break;

		*/
	default:
		break;
	}

	
	setItemColors();
}

void CTabDlgPreMaster::showMstPreAfn0cF90_NotElec()
{
	/*
	CNxConfig cfg;
	
	UINT16 usPn = 0;
	sMtNotElec sNotElec;
	CString strPn, strValue, strMin, strType;
	
	cfg.GetPreAfn0CF90_NotElec(&usPn,&sNotElec, MT_ROLE_MASTER);
	
	
	
	
	
	// 插入列表显示
	CString   name_pn      = "测量点号";            
	CString   name_type    = "非电气量类型";           
	CString   name_max     = "量程上限";     
	CString   name_min     = "量程下限";      
	
	
	strValue.Format("%0.3lf",sNotElec.dValue);
	switch (sNotElec.eType)
	{
	case MT_NELEC_TEMP:
		strType = "温度";
		break;
	case MT_NELEC_FLOW:
		strType = "流量";
		break;
	case MT_NELEC_FLOW_V:
		strType = "流速";
		break;
	case MT_NELEC_PRESS:
		strType = "压力";
		break;
	case MT_NELEC_HUMID:
		strType = "湿度";
		break;
	case MT_NELEC_ILLUM:
		strType = "照度";
		break;
		
	case MT_NELEC_ROTATE:
		strType = "转速";
		break;
		
	default:
		strType = "未知非电气量";
		break;
	}
	
	strPn.Format("%d", usPn);
	
	
	CString   format_pn     = FMT_PN;            
	CString   format_type   = "";           
	CString   format_max    = "";    
	CString   format_min    = "";      
	
	CString   limit_pn     = "0 ~ 65535";             
	CString   limit_type   = "1 - 7";            
	CString   limit_max = "9999.999";    
	CString   limit_min = "-9999.999"; ;       
	
	m_edit_pn.SetWindowText(strPn);
	m_edit_pn.EnableWindow(TRUE);
	
	m_list.DeleteAllItems();
	m_list.AddItem(name_pn,strPn,format_pn,limit_pn);
	m_list.AddItem(name_type,strType,format_type,limit_type);
//	m_list.AddItem(name_max,strValue,format_max,limit_max);
	//m_list.AddItem(name_min,strMin,format_min,limit_min);
	
	  */
}



void CTabDlgPreMaster::OnChangeEditPn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString strPn;
	m_edit_pn.GetWindowText(strPn);
    m_nxCfg.SetPrePnStr31(m_mcmd, MC_ROLE_MASTER, strPn, TRUE);
}

void CTabDlgPreMaster::showMstPreAfn00F1()
{
	
	// 取出预配数据
	eMcResCode eResCode;
	m_nxCfg.GetPreAfn00F1(&eResCode, TRUE);
	
	// 插入列表显示
	CString   name_rescode  = "确认否认信息码";          
	CString   value_rescode;             
	CString   format_rescode = FMT_UINT8;  
	CString   limit_rescode = "0-7,255"; 
	
	value_rescode.Format("%d ",eResCode);

	switch(eResCode)
	{
		
	case MC_RES_OK:
		value_rescode += "确认";
		break;
		
	case MC_RES_NONE:
		value_rescode += "无请求的数据、无设置的参数、无要执行的功能";
		break;
		
	case MC_RES_NOT_READY:
		value_rescode += "请求的数据未产生、功能执行未满足";
		break;
		
	case MC_RES_REMOVE:
		value_rescode += "请求的数据已经被移出保存窗口";
		break;
		
	case MC_RES_DATA_OTRNG:
		value_rescode += "请求的数据超出支持的信息点范围";
		break;
		
	case MC_RES_PARA_OTRNG:
		value_rescode += "设置的参数超出支持的信息点范围";
		break;
		
	case MC_RES_NOT_SAME:
		value_rescode += "设置的接入端口号及属性与实际不符";
		break;
		
	case MC_RES_NOT_SUPT:
		value_rescode += "指定接口不支持转发";
		break;
		
	case MC_RES_DENY:
		value_rescode += "否认";
		break;
		
	default:
		value_rescode += "未知确认";
		break;
		
	}
	
	m_list.DeleteAllItems();	
	m_list.AddItem(name_rescode,value_rescode,format_rescode,limit_rescode);
}

void CTabDlgPreMaster::showMstNullData()
{
	m_list.DeleteAllItems();

	CString   name    = "无";          
	CString   svalue  = "无";             
	CString   format  = "无";  
	CString   limit   = "无"; 
	m_list.AddItem(name,svalue,format,limit);
}

void CTabDlgPreMaster::ShowMstPreAfn04F35()
{
	CNxConfig cfg;
	sMcAfn04f35 sAfn04f35;		
	cfg.GetPreAfn04F35(&sAfn04f35, TRUE);

	CString strUp, strDn;
	CString name_type = "非电气量";
	CString name_up   = "量程上限";
	CString name_dn   = "量程下限";
	
	CString val_type;
	CString formt_value;
	CString info_up,info_dn;

	
	switch (sAfn04f35.eType)
	{
	case MC_NELC_TEMP:
		val_type = "温度";
		break;
		
	case MC_NELC_FLOW:
		val_type = "流量";
		break;

	case MC_NELC_FV:
		val_type = "流速";
		break;
		
	case MC_NELC_PRESS:
		val_type = "压力";
		break;
		
	case MC_NELC_HUMI:
		val_type = "湿度";
		break;
		
	case MC_NELC_LIGHT:
		val_type = "照度";
		break;
		
	case MC_NELC_RV:
		val_type = "转速";
		break;
		
	case MC_NELC_420MA:
		val_type = "4~20MA";
		break;
		
	default:
		val_type = "未知类型";
		break;
	}

	
	switch(sAfn04f35.sUp.ePrec)
	{
	case MC_PREC_P4:
		info_up = "0, (+/-)10000~99999990000\n";
		break;
		
	case MC_PREC_P3:
		info_up = "0, (+/-)1000~9999999000\n";
		break;
		
	case MC_PREC_P2:
		info_up = "0, (+/-)100~999999900\n";
		break;
		
	case MC_PREC_P1:
		info_up = "0, (+/-)10~99999990\n";
		break;
		
	case MC_PREC_P0:
		info_up = "0, (+/-)1~9999999\n";
		break;
		
	case MC_PREC_N1:
		info_up = "0, (+/-)0.1~999999.9\n";
		
		break;				
		
	case MC_PREC_N2:
		info_up = "0, (+/-)0.01~99999.99\n";
		break;
		
	case MC_PREC_N3:
		info_up = "0, (+/-)0.001~9999.999\n";
		break;	
		
	default:
		info_up = "未知\n";
		break;
	}


	switch (sAfn04f35.sUp.ePrec)
	{
	case  MC_PREC_P4:
	case MC_PREC_P3:
	case MC_PREC_P2:
	case MC_PREC_P1:
	case MC_PREC_P0:
		strUp.Format("%0.0f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.0f", sAfn04f35.sDown.dValue);
		formt_value = "整数";
		break;
		
	case MC_PREC_N1:
		strUp.Format("%0.1f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.1f", sAfn04f35.sDown.dValue);
		formt_value = "浮点数";
		break;
		
		
	case MC_PREC_N2:
		strUp.Format("%0.2f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.2f", sAfn04f35.sDown.dValue);
		formt_value = "浮点数";
		break;
		
		
	case MC_PREC_N3:
		strUp.Format("%0.3f", sAfn04f35.sUp.dValue);
		strDn.Format("%0.3f", sAfn04f35.sDown.dValue);
		formt_value = "浮点数";
		break;
		
	default:
		break;
	}

	
	m_list.DeleteAllItems();
	m_list.AddItem(name_type,val_type,"自定义","");
	m_list.AddItem(name_up,strUp,formt_value,info_up);
	m_list.AddItem(name_dn,strDn,formt_value,info_up);
}

void CTabDlgPreMaster::ShowMstPreAfn04F3()
{
	CNxConfig cfg;
	sMcAfn04f3 sAfn04f3;		
	cfg.GetPreAfn04F3(&sAfn04f3, TRUE);

	CString val_type;
	val_type.Format("%d", sAfn04f3.ucTypeID);
	m_list.DeleteAllItems();
	m_list.AddItem("消息认证方案号",val_type,"整数","0~255 0不认证，255硬件认证，其他软件认证");
	val_type.Format("%d", sAfn04f3.usAuthPara);
	m_list.AddItem("消息认证方案参数",val_type,"整数","0~65535");
}

void CTabDlgPreMaster::ShowMstPreAfn04F4()
{
	CNxConfig cfg;
	sMcAfn04f4 sAfn04f4;	
	int i = 0;
	cfg.GetPreAfn04F4(&sAfn04f4, TRUE);
	

	m_list.DeleteAllItems();

	CString str_name, str_val, str_format, str_info;
	
	str_format = "整数";
	for (i = 0; i < 8; i++)
	{
		str_name.Format("组地址 %d", i+1);
		str_val.Format("%u", sAfn04f4.ulAddr[i]);
		if (sAfn04f4.ulAddr[i] == 0)
		{
			str_info = "不设组地址";
		}
		else
		{
			str_info = "";
		}

	m_list.AddItem(str_name, str_val, str_format, str_info);
		
	}
}

void CTabDlgPreMaster::ShowMstPreAfn04F7()
{
	m_list.DeleteAllItems();

	CNxConfig cfg;
	sMcAfn04f7 sData;	
	int i = 0;
	cfg.GetPreAfn04F7(&sData, TRUE);
	


	CString strName, strVal, strFmt, strInfor;
	CString strIp;
	CString strValue;
	
	CString str_ucPort;
	
	cfg.GetPreAfn04F7(&sData, TRUE);
	

	// ucPort
	strName = "集中器下行端口号";
	strVal.Format("%d", sData.ucPort);
	strFmt = "";
	strIp = "0 ~ 255";
	m_list.AddItem(strName, strVal, strFmt, strInfor);
	
	// main ip
	strName = "主用IP地址";
	strFmt = "";
	strInfor = "";
	strVal.Format("%d.%d.%d.%d", 
		sData.sMainIp.ip[0],
		sData.sMainIp.ip[1],
		sData.sMainIp.ip[2],
		sData.sMainIp.ip[3]);
	m_list.AddItem(strName, strVal, strFmt, strInfor);

	// main port
	strName = "主用端口";
	strVal.Format("%d", sData.usMainPort);
	strFmt = "";
	strInfor = "0 ~ 65535";
	m_list.AddItem(strName, strVal, strFmt, strInfor);

	// main ip
	strName = "备用IP地址";
	strFmt = "";
	strInfor = "";
	strVal.Format("%d.%d.%d.%d", 
		sData.sBackIp.ip[0],
		sData.sBackIp.ip[1],
		sData.sBackIp.ip[2],
		sData.sBackIp.ip[3]);
	m_list.AddItem(strName, strVal, strFmt, strInfor);

	// main port
	strName = "备用端口";
	strVal.Format("%d", sData.usBackPort);
	strFmt = "";
	strInfor = "0 ~ 65535";
	m_list.AddItem(strName, strVal, strFmt, strInfor);


	
	#define  LEN_BUF 34
	char pStr[LEN_BUF];
	
	// apn
	memset(pStr, 0, LEN_BUF);
	memcpy(pStr, sData.ucAPN, 16);
	strVal.Format("%s", pStr);

	strName = "APN";
	strFmt = "";
	strInfor = "";
	m_list.AddItem(strName, strVal, strFmt, strInfor);

	
	// usr
	memset(pStr, 0, LEN_BUF);
	memcpy(pStr, sData.ucUsr, 32);
	strVal.Format("%s", pStr);
	strName = "用户名";
	strFmt = "";
	strInfor = "";
	m_list.AddItem(strName, strVal, strFmt, strInfor);
	
	// pwd
	memset(pStr, 0, LEN_BUF);
	memcpy(pStr, sData.ucPwd, 32);
	strVal.Format("%s", pStr);	
	strName = "密码";
	strFmt = "";
	strInfor = "";
	m_list.AddItem(strName, strVal, strFmt, strInfor);



}