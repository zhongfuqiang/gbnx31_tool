// DlgPrePn.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPrePn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrePn dialog


CDlgPrePn::CDlgPrePn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrePn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPrePn)
	m_static_type = _T("");
	m_edit_pn = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPrePn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrePn)
	DDX_Control(pDX, IDC_LIST_PN, m_list_pn);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Text(pDX, IDC_STATIC_TYPE, m_static_type);
	DDX_Text(pDX, IDC_EDIT_PN, m_edit_pn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrePn, CDialog)
	//{{AFX_MSG_MAP(CDlgPrePn)
	ON_EN_CHANGE(IDC_EDIT_PN, OnChangeEditPn)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PN, OnRclickListPn)
	ON_COMMAND(AFX_ID_PN_DEL, OnIdPnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrePn message handlers

void CDlgPrePn::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDlgPrePn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btn_ok.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_ok.SetIcon(IDI_ICON_RIGHT);
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	m_btn_no.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_no.SetIcon(IDI_ICON_X);
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	SetWindowText(m_strTitle);
	
	//m_list_pn.SetHeadings(_T("序号,100;测量点号,150"));
	m_list_pn.SetHeadings(_T("测量点号,250"));
	m_list_pn.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	GetCur();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrePn::SetTitle( CString strT )
{
	m_strTitle = strT;
}

void CDlgPrePn::GetCur()
{
	
	switch (m_cmdInfor.ePn)
	{
	case MC_PN_MP:
		m_static_type = "测量点号";
		break;
	case MC_PN_TK:
			m_static_type = "任务号";
		break;
	case MC_PN_TM:
			m_static_type = "终端号";
			break;
	}
	
	CNxConfig cfg;
	eMcRole eRole;
	eRole = m_cmdInfor.eDir == MC_DIR_M2S ? MC_ROLE_MASTER:MC_ROLE_CONTOR;
	
	cfg.GetPrePnStr31(m_cmdInfor.eCmd, eRole, &m_edit_pn);
	
	initList();

	UpdateData(FALSE);

}

void CDlgPrePn::OnChangeEditPn() 
{
	
	UpdateData();
	CNxConfig cfg;
	eMcRole eRole;
	eRole = m_cmdInfor.eDir == MC_DIR_M2S ? MC_ROLE_MASTER:MC_ROLE_CONTOR;
    cfg.SetPrePnStr31(m_cmdInfor.eCmd, eRole, m_edit_pn, TRUE);
	initList();	
}

void CDlgPrePn::initList()
{
	UINT16 usPn[256] = {0};
	CNxConfig cfg;
	UINT8  ucNum;
	eMcRole eRole;
	eRole = m_cmdInfor.eDir == MC_DIR_M2S ? MC_ROLE_MASTER:MC_ROLE_CONTOR;
	cfg.GetPrePn31(m_cmdInfor.eCmd, eRole,usPn, &ucNum);	
	
	CString strPn;
	//	CString strIndex;
	
	int i = 0;
	m_list_pn.DeleteAllItems();
	for (i = 0; i < ucNum; i++)
	{
		//strIndex.Format("%d", i+1);
		strPn.Format("%d", usPn[i]);
		if (usPn[i] > 2040)
		{
			usPn[i] = 0;
			MessageBox("请输入0~2040整数", "提示", MB_OK|MB_ICONWARNING);
			return;

		}
		m_list_pn.AddItem(strPn);
	}

	cfg.SetPrePn31(m_cmdInfor.eCmd, eRole,usPn, ucNum);
}

void CDlgPrePn::OnRclickListPn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu popMenu;
	
	popMenu.LoadMenu(IDR_MENU_PN_DEL);
	CMenu *pMu = popMenu.GetSubMenu(0); 
	POINT pt; 
	::GetCursorPos(&pt); 
	
	
	
	
	
	
	pMu->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_LEFTALIGN, pt.x, pt.y, this);
	*pResult = 0;
}

void CDlgPrePn::OnIdPnDel() 
{
	// TODO: Add your command handler code here
	UINT16 usPn[256] = {0};
	int i = 0;
	CList<int, int> list_del;
	POSITION pos;
	int index;
	pos = m_list_pn.GetFirstSelectedItemPosition();
	int nSel = 0;
	CString strText;
	while(nSel!= -1)
	{
		nSel = m_list_pn.GetNextSelectedItem(pos);


		list_del.AddHead(nSel);
	}
	
	POSITION posList;
	posList = list_del.GetHeadPosition();
	int x;
	while (posList)
	{
		x = list_del.GetAt(posList);
		index = list_del.GetNext(posList);
		
		if (x!= -1)
		{
			m_list_pn.DeleteItem(x);
		}
	}
	
	
	// 将删除之后的数据写入
	int j = 0;
	for (j = 0; j < m_list_pn.GetItemCount(); j++)
	{
		strText = m_list_pn.GetItemText(j, 0);
		usPn[i++] = atoi(strText.GetBuffer(strText.GetLength()));
		strText.ReleaseBuffer();
	}

	CNxConfig cfg;
	
	eMcRole eRole;
	eRole = m_cmdInfor.eDir == MC_DIR_M2S ? MC_ROLE_MASTER:MC_ROLE_CONTOR;
	cfg.SetPrePn31(m_cmdInfor.eCmd, eRole,usPn, i);
	

	cfg.GetPrePnStr31(m_cmdInfor.eCmd, eRole, &m_edit_pn);
	UpdateData(FALSE);

}
