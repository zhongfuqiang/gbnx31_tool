// TabDlgTask.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "NxMasterDlg.h"
#include "TabDlgTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDlgTask dialog
#define TIMER_ID_ONE  102 // 单条发送的定时器ID
#define TIMER_ID_LIST 103 // 逐条发送的定时器ID 


CTabDlgTask::CTabDlgTask(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlgTask::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabDlgTask)
	m_zqOne = 0;
	m_timesOne = 0;
	//}}AFX_DATA_INIT
	m_bOneRun  = FALSE;
	m_bListRun = FALSE;
	m_nOneZq = 1;
	m_nOneMaxTime = 100;
	m_nOneLeftTime = m_nOneMaxTime;
	m_zqOne = 1000;
	m_timesOne = 10;
}


void CTabDlgTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDlgTask)
	DDX_Control(pDX, IDC_BTN_CLR, m_btn_clr);
	DDX_Control(pDX, IDC_BTN_LIST_GO_STOP, m_btn_go_stop_list);
	DDX_Control(pDX, IDC_BTN_GO_STOP, m_btn_go_stop);
	DDX_Control(pDX, IDC_EDIT_SEND_TEXT, m_edit_one);
	DDX_Control(pDX, IDC_LIST_TASK, m_list_task);
	DDX_Control(pDX, IDC_STATIC_ONE, m_static_one);
	DDX_Control(pDX, IDC_STATIC_LIST, m_static_list);
	DDX_Text(pDX, IDC_EDIT_ONE_ZQ, m_zqOne);
	DDV_MinMaxInt(pDX, m_zqOne, 1, 10240);
	DDX_Text(pDX, IDC_EDIT_ONE_TIMES, m_timesOne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabDlgTask, CDialog)
	//{{AFX_MSG_MAP(CTabDlgTask)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_GO_STOP, OnBtnGoStop)
	ON_BN_CLICKED(IDC_BTN_LIST_GO_STOP, OnBtnListGoStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CLR, OnBtnClr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDlgTask message handlers

void CTabDlgTask::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	setCtrlPos();
	// TODO: Add your message handler code here
	
}


// 调整对话框上控件的位置及大小
void CTabDlgTask::setCtrlPos()
{
	RECT rect_client,rect_ctrl, rect_static_one, rect_edit_one, rect_list;
	GetClientRect(&rect_client);
	
	const int border = 4;


	// static one
	rect_static_one.top = border;
	rect_static_one.left = rect_client.left + border;
	rect_static_one.right = rect_client.right - border;
	rect_static_one.bottom = rect_static_one.top + 190;

	if(m_static_one.m_hWnd)
	{
		m_static_one.MoveWindow(&rect_static_one);	
	}

	// static list
	rect_ctrl.top = rect_static_one.bottom + border;
	rect_ctrl.left = rect_client.left + border;
	rect_ctrl.right = rect_client.right - border;
	rect_ctrl.bottom = rect_client.bottom - border;
	if(m_static_list.m_hWnd)
	{
		m_static_list.MoveWindow(&rect_ctrl);	
	}


	//rect_edit_one
	const int border_ctrl = 8;
	rect_edit_one.top  = rect_static_one.top  + 82;
	rect_edit_one.left = rect_static_one.left + border_ctrl;
	rect_edit_one.right = rect_static_one.right - border_ctrl;
	rect_edit_one.bottom = rect_edit_one.top  +  100;
	if(m_edit_one.m_hWnd)
	{
		m_edit_one.MoveWindow(&rect_edit_one);
	}
	
	//rect_list
	rect_list.top   = rect_ctrl.top + 100;
	rect_list.left  = rect_ctrl.left + border_ctrl;
	rect_list.right = rect_ctrl.right - border_ctrl;
	rect_list.bottom = rect_client.bottom - border_ctrl;
	if(m_list_task.m_hWnd)
	{
		m_list_task.MoveWindow(&rect_list);
	}

}

void CTabDlgTask::OnBtnGoStop() 
{
	// TODO: Add your control notification handler code here
	if (m_bOneRun == FALSE)
	{
			
		if(m_pNxMstDlg->m_bMaster == true)
		{
			int i;
			int nItemCount;
			BOOL bCheck = FALSE;//是否至少有一项被勾选  
			if (m_pNxMstDlg->m_bServerRun == false)
			{
					//AfxMessageBox("服务器没有启动");
					MessageBox("服务器没有启动", "错误", MB_OK|MB_ICONWARNING);
					return;
			}
			
			nItemCount = m_pNxMstDlg->m_list_tml.GetItemCount();
			if (nItemCount == 0)
			{
				//AfxMessageBox("没有终端上线");
		    	MessageBox("没有终端上线", "错误", MB_OK|MB_ICONWARNING);
				return;
			}
			else
			{
				for(i = 0; i < nItemCount; i++)
				{
					if (m_pNxMstDlg->m_list_tml.GetCheck(i) == TRUE)
					{
						bCheck = TRUE;
						break;
					}
				}

				if (bCheck == FALSE)
				{
					AfxMessageBox("请勾选通信集中器!");
					return;
				}
			}

		
		}
		else
		{
			if (m_pNxMstDlg->m_bClientLink == false)
			{
				AfxMessageBox("未与服务器建立连接!");
				return;
			}

		}

		CString strSend;
		m_edit_one.GetWindowText(strSend);
		if (strSend.GetLength() == 0)
		{
			AfxMessageBox("请输入正确的发送报文!");
			return;
		}

		GetDlgItem(IDC_BTN_GO_STOP)->SetWindowText("停止");
		m_btn_go_stop.SetIcon(IDI_ICON_STOP);
		GetDlgItem(IDC_EDIT_ONE_ZQ)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_ONE_TIMES)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_SEND_TEXT)->EnableWindow(false);

		UpdateData(true);
	
		// 启动定时器
		m_nOneZq = m_zqOne;
		m_nOneMaxTime = m_timesOne;
		m_nOneLeftTime = m_timesOne;
		m_bOneRun = TRUE;
		SetTimer(TIMER_ID_ONE, m_zqOne,NULL);
	}
	else
	{
		GetDlgItem(IDC_BTN_GO_STOP)->SetWindowText("开始");
		m_btn_go_stop.SetIcon(IDI_ICON_RUN);
		GetDlgItem(IDC_EDIT_ONE_ZQ)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_ONE_TIMES)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SEND_TEXT)->EnableWindow(true);
		KillTimer(TIMER_ID_ONE);
		m_bOneRun = FALSE;
	}
}

void CTabDlgTask::initListCtrl()
{
	m_list_task.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int i = 0;
	m_list_task.InsertColumn(i++,"序号",LVCFMT_LEFT,50);
	m_list_task.InsertColumn(i++,"摘要",LVCFMT_LEFT,100);
	m_list_task.InsertColumn(i++,"地址",LVCFMT_LEFT,50);
	m_list_task.InsertColumn(i++,"长度",LVCFMT_LEFT,50);
	m_list_task.InsertColumn(i++,"报文",LVCFMT_LEFT,150);
}

BOOL CTabDlgTask::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	initListCtrl();
	
	m_btn_go_stop.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	//m_btn_go_stop.SetIcon(IDI_ICON_FEET);
	m_btn_go_stop.SetIcon(IDI_ICON_RUN);
	m_btn_go_stop.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_go_stop.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	
	m_btn_go_stop_list.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	//m_btn_go_stop_list.SetIcon(IDI_ICON_FEET);
	m_btn_go_stop_list.SetIcon(IDI_ICON_RUN);
	m_btn_go_stop_list.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_go_stop_list.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));

	m_btn_clr.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	//m_btn_go_stop_list.SetIcon(IDI_ICON_FEET);
	m_btn_clr.SetIcon(IDI_ICON_E);
	m_btn_clr.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_clr.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabDlgTask::OnBtnListGoStop() 
{
	// TODO: Add your control notification handler code here
	if (m_bListRun == FALSE)
	{
		GetDlgItem(IDC_BTN_LIST_GO_STOP)->SetWindowText("停止");
		m_btn_go_stop_list.SetIcon(IDI_ICON_STOP);
		m_bListRun = TRUE;
	}
	else
	{
		GetDlgItem(IDC_BTN_LIST_GO_STOP)->SetWindowText("开始");
		m_btn_go_stop_list.SetIcon(IDI_ICON_RUN);
		m_bListRun = FALSE;
	}
}

void CTabDlgTask::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER_ID_ONE:
		SendOneTimer();
		break;

	case TIMER_ID_LIST:
		SendListTimer();
		break;
	}

	CDialog::OnTimer(nIDEvent);
}


// 定时器响应函数 单条发送任务
void CTabDlgTask::SendOneTimer()
{

	// 发送报文到每个勾选的对象
	CString strSend;
	m_edit_one.GetWindowText(strSend);

	if (m_pNxMstDlg != NULL)
	{
		if (m_pNxMstDlg->m_bMaster == true)
		{
			//主站
			if(m_pNxMstDlg->m_bServerRun == false)
			{
				GetDlgItem(IDC_STATIC_SHOW_ONE)->SetWindowText("服务器已经停止!");
				KillTimer(TIMER_ID_ONE);
				GetDlgItem(IDC_BTN_GO_STOP)->SetWindowText("开始");
				GetDlgItem(IDC_EDIT_ONE_ZQ)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_ONE_TIMES)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_SEND_TEXT)->EnableWindow(true);
				KillTimer(TIMER_ID_ONE);
				m_bOneRun = FALSE;
				return;
			}
		}
		else
		{
			// 从站
			if(m_pNxMstDlg->m_bClientLink == false)
			{
				GetDlgItem(IDC_STATIC_SHOW_ONE)->SetWindowText("已经与服务器断开连接!");
				KillTimer(TIMER_ID_ONE);
				GetDlgItem(IDC_BTN_GO_STOP)->SetWindowText("开始");
				GetDlgItem(IDC_EDIT_ONE_ZQ)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_ONE_TIMES)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_SEND_TEXT)->EnableWindow(true);
				KillTimer(TIMER_ID_ONE);
				m_bOneRun = FALSE;
				return;
			}
		}
			
		BOOL bSendOk = m_pNxMstDlg->SendToList(strSend);
		if (bSendOk == FALSE)
		{
			GetDlgItem(IDC_STATIC_SHOW_ONE)->SetWindowText("没有通信对象!");
			KillTimer(TIMER_ID_ONE);
			GetDlgItem(IDC_BTN_GO_STOP)->SetWindowText("开始");
			GetDlgItem(IDC_EDIT_ONE_ZQ)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_ONE_TIMES)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SEND_TEXT)->EnableWindow(true);
			KillTimer(TIMER_ID_ONE);
			m_bOneRun = FALSE;
			return;
		}
	}



	// 显示执行状态结果
	CString strShow;
	strShow.Format("每 %d 毫秒发送一次，共发送 %d 次，剩余 %d 次", m_nOneZq, m_nOneMaxTime, --m_nOneLeftTime);
	GetDlgItem(IDC_STATIC_SHOW_ONE)->SetWindowText(strShow);
	if (m_nOneLeftTime == 0)
	{
		KillTimer(TIMER_ID_ONE);
		GetDlgItem(IDC_BTN_GO_STOP)->SetWindowText("开始");
		GetDlgItem(IDC_EDIT_ONE_ZQ)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_ONE_TIMES)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SEND_TEXT)->EnableWindow(true);
		KillTimer(TIMER_ID_ONE);
		m_bOneRun = FALSE;
	}
}

// 定时器响应函数 逐条发送任务
void CTabDlgTask::SendListTimer()
{
	
}


// 获得主对话框
void CTabDlgTask::setMainDlg( CNxMasterDlg *pNxMstDlg )
{
	m_pNxMstDlg = pNxMstDlg;
}

void CTabDlgTask::setOneText( CString str )
{
	m_edit_one.SetWindowText(str);
}

void CTabDlgTask::OnBtnClr() 
{
	// TODO: Add your control notification handler code here
	m_edit_one.SetWindowText("");
}
