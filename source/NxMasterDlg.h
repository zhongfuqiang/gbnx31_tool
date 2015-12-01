// NxMasterDlg.h : header file
//

#if !defined(AFX_NXMASTERDLG_H__17C20C4A_A48A_44E0_AB02_8A8D36A840C0__INCLUDED_)
#define AFX_NXMASTERDLG_H__17C20C4A_A48A_44E0_AB02_8A8D36A840C0__INCLUDED_

#include "ServerSock.h"
#include "TerminalSock.h"
#include "Terminal.h"
#include "ColorListCtrl.h"
#include "ListCtrlSock.h"
#include "MyRichEdit.h"
#include "TabDlgPack.h"
#include "TabDlgUnpack.h"
#include "TabDlgPreMaster.h"
#include "TabDlgPreTml.h"
#include "TabDlgTask.h"

#include "CJColorPicker.h"
#include "CJFlatComboBox.h"
#include "XPTabCtrl.h"
//#include "NxRuler.h"
#include "NxConfig.h"
#include "Qgdw3761api.h"


#include "BtnST.h"
#include "ShadeButtonST.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNxMasterDlg dialog
#define NX_MASTER_DBG   // debug switch
//#undef  NX_MASTER_DBG

// 主界面tab控件各
typedef enum
{
	TAB_INDEX_PACK,
	TAB_INDEX_PRE_MASTER,
	TAB_INDEX_PRE_TERMINAL,

	TAB_INDEX_UNPACK,
	TAB_INDEX_TASK,
	TAB_INDEX_MAX
		
}TAB_INDEX;


#define TAB_NAME_PRE_MASTER     "主站预配"
#define TAB_NAME_PRE_TERMINAL   "终端预配"
#define TAB_NAME_PACK           "规约封装"
#define TAB_NAME_UNPACK         "规约解析" 
#define TAB_NAME_TASK           "计划任务"



class CNxMasterDlg : public CDialog
{
// Construction
public:
	CNxMasterDlg(CWnd* pParent = NULL);	// standard constructor
	void ClickSendBtn();
	BOOL SendToList( CString strSend); // 将报文发送给列表中勾选的每一个集中器
	CImageList* m_imagelist;                   /*图标列表*/
// Dialog Data
	//{{AFX_DATA(CNxMasterDlg)
	enum { IDD = IDD_NXMASTER_DIALOG };
// 	CButton	m_btn_stop_link;
// 	CButton	m_btn_start_link;

	CShadeButtonST	m_btn_stop_link;
	CShadeButtonST	m_btn_start_link;


	CButton	m_check_auto_respone;
	CButton	m_check_omit_heart;
	CButton	m_check_auto_unpack;
	CCJColorPicker	m_btn_clr_info;
	CCJColorPicker	m_btn_clr_unpack;
	CCJColorPicker	m_btn_clr_terminal;
	CCJColorPicker	m_btn_clr_master;
	CButton	m_static_cmd_cach;
	CEdit	m_cmd_cach;
	CShadeButtonST m_btn_send_cmd;
	CEdit	m_edit_send;
	CMyRichEdit m_rich_edit;
	CListCtrlSock  m_list_tml;
	CXPTabCtrl	m_tab;
	CIPAddressCtrl	m_ctrl_ip;
	int		m_sev_port;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNxMasterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNxMasterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadioMaster();
	afx_msg void OnRadioTerminal();
	afx_msg void OnBtnStart();
	afx_msg void OnFieldchangedIpAddr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnStop();
	afx_msg void OnBtnSendCmd();
	afx_msg void OnItemchangedListTml(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetClrMasterMsg();  // 设置主站消息格式
	afx_msg void OnSetTmlCf();        // 设置终端显示
	afx_msg void OnSetUnpackCf();
	afx_msg void OnBtnAsClient();
	afx_msg void OnCheckAutoUnpack();
	afx_msg void OnAbout();
	afx_msg void OnSetInfoCf();
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClearRichEdit();
	afx_msg void OnChangeEditPort();
	afx_msg void OnCheckAutoRespone();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnDataPreSet();
	afx_msg void OnRclickRicheditMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickRicheditMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRichClr();
	afx_msg void OnRichTrans();
	afx_msg void OnRichCopy();
	afx_msg void OnRichAddt();
	afx_msg void OnIdTkSet();
	afx_msg void OnRichInsetLen();
	//}}AFX_MSG
	afx_msg void OnSelEndOK(UINT lParam, LONG wParam); // colorpicker
	DECLARE_MESSAGE_MAP()
public:
	void insetLineStype();
	void  showUnpackText(smtPack *psmtPack);// 文本方式显示解析结果
	void  showUnpackText31(smcPack *psmcPack); // 以文本方式显示gb3-1的报文解析结果
	void  showSubData(sMtData *psMtData, eMtDir eDir,COLORREF crText);     // 显示子命令信息 及应用层数据 3761
	void  showSubData31(sMcData *psMtData, eMcDir eDir,COLORREF crText);     // 显示子命令信息 及应用层数据 gb31
	void  insertLine();
	CString charToCString(char *pStr, int n);
	char *pStrGetErcName(UINT8 ucErc);
	void showTabDlg(int index);
	void InitTabCtrl();
	CTerminal* GetCTerminal(CServerSock *pSock);
	void InsertInfoMasterSend(CTerminal *pTml, int len); // 主站向某终端发送len命令的提示消息，将其插入richedit
	void InsertInfoMasterRecv(CTerminal *pTml, int len); // 主站收到某终端发来len的提示消息，将其插入richedit

	void insertInfoTmlSend(CTerminalSock *pSock, int len); // terminal向某主站发送len应答的提示消息，将其插入richedit
	void insertInfoTmlRecv(CTerminalSock *pSock, int len); // terminal收到主站发送len命令的提示消息，将其插入richedit

	CString GetCurTime();
	CString GetCurDate();
	void SetListTmlCtrlPos();
	int tmlSendMsg(CTerminalSock *pSock, CString strSend);
	int sevSendMsg(CServerSock   *pSock, CString strSend);
	void tmlReceveMsg(CTerminalSock *pSockTml);
	void sevReceveMsg(CServerSock   *pSockSev);
	void TmlOnClose(CTerminalSock *pSock);  // 服务器关闭后的响应
	void SocketStop(CServerSock *pSevSock); // 客户机退出后的响应
	void SevAcceptConnect();
	void    draw_main_tab();
	int     GetLocalHostName(CString &sHostName);
	int     GetIpAddress(const CString & sHostName,CString & sIpAddress);
	bool    bStartServer(int port,  CString strIp);     // 开启服务器
	bool    bConnectServer(int port,CString strIp);    // 连接服务器
	bool    m_bServerRun;                              // 服务器是否已经开启
	bool    m_bClientLink;                             // 从站是否连接到服务器
	void    AutoUnpack(char *buf, UINT16 usLen);       // 解析报文
	
    // 主站自动回复
	void    AutoResponseMaster(CTerminal *pTml, char *buf, UINT16 usLen);  
	void    AutoResponseMasterTimer();
	int     m_AutoResponseMasterSeconds;
	CTerminal *m_pTmlAutoResponseMaster;
	char    *m_sendBuferAutoResponseMaster;
    UINT16  m_usSendBufLenMaster;

	void    AutoResponseTerminal(char *buf, UINT16 usLen); // 从站自动回复
	void    MasterDealLink(CTerminal *pTml, char *pBuf, UINT16 usLen);   // //服务器处理登录命令
	CString m_strLocalIP;    // 本机IP地址
	CString m_strServerIP;   // 保存连接服务器的IP
	int     m_nSerPort;      // 服务器端口号
	bool    m_bMaster;       // 主站还是终端
	bool    m_bSevStop;      // 服务器是否停止
	CServerSock   m_sockSev;
	int     m_terminalId;    // 作为终端时的ID

	CTerminalSock m_sockTml;
	CPtrList      m_listTml; // 与主站建立连接的终端链表
//	CNxRuler      m_nxRuler;
	BOOL          m_bAutoUnpack;   // 是否选择自动解析
	BOOL          m_bAutoResponse; // 是否选择自动应答

private:
	CTabDlgTask      m_tabDlgTask;
	CTabDlgUnpack    m_tabDlgUnpack;
	CTabDlgPack      m_tabDlgPack;
	CTabDlgPreMaster m_tabDlgPreMst;
	CTabDlgPreTml    m_tabDlgPreTml;
	CNxConfig        m_preConfig;     // 预配置对象
	


public:
	BOOL IsAdministrator();
	void SetRegAdmin();
	CString ReturnPath();

	// 调用函数 正式版本将开关关闭
#ifdef NX_MASTER_DBG
	void test_GetMstPreAfn04F1();

#endif

private:
	void setMsgRichEditPos();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NXMASTERDLG_H__17C20C4A_A48A_44E0_AB02_8A8D36A840C0__INCLUDED_)
