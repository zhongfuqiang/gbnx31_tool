// DlgPreAfn04F9.cpp : implementation file
//

#include "stdafx.h"
#include "NxMaster.h"
#include "DlgPreAfn04F9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F9 dialog


CDlgPreAfn04F9::CDlgPreAfn04F9(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreAfn04F9::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreAfn04F9)
	m_edit_usImpRecNum = 0;
	m_edit_usNmlRecNum = 0;
	//}}AFX_DATA_INIT
	m_strRec[0] = "ERC1: 复位事件";
	m_strRec[1] = "ERC2: 指定数据清零事件";
	m_strRec[2] = "ERC3: 软件版本变更事件";
	m_strRec[3] = "ERC4: 参数变更事件";
	m_strRec[4] = "ERC5: 校时事件";
	m_strRec[5] = "ERC6: 状态量变位事件";
	m_strRec[6] = "ERC7: 遥控跳闸事件";
	m_strRec[7] = "ERC8: 停/上电事件";
	m_strRec[8] = "ERC9: 总功率因素越限事件";
	m_strRec[9] = "ERC10: 电压偏差越限事件";
	m_strRec[10] = "ERC11: 电压回路异常事件";
	m_strRec[11] = "ERC12: 电流回路异常事件";
	m_strRec[12] = "ERC13: 电压越限事件";
	m_strRec[13] = "ERC14: 电流越限事件";
	m_strRec[14] = "ERC15: 电压不平衡度越限事件";
	m_strRec[15] = "ERC16: 电流不平衡度越限事件";
	m_strRec[16] = "ERC17: 谐波电压畸变率越限事件";
	m_strRec[17] = "ERC18: 谐波电流畸变率越限事件";
	m_strRec[18] = "ERC19: 闪变越限事件";
	m_strRec[19] = "ERC20: 非电气量越限事件";

}


void CDlgPreAfn04F9::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreAfn04F9)
	DDX_Control(pDX, IDC_CHECK_ALL_VALID, m_check_all_valid);
	DDX_Control(pDX, IDC_CHECK_ALL_NOMARL, m_check_all_nml);
	DDX_Control(pDX, IDC_CHECK_ALL_IMP, m_check_all_imp);
	DDX_Control(pDX, IDCANCEL, m_btn_no);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Text(pDX, IDC_EDIT_usImpRecNum, m_edit_usImpRecNum);
	DDX_Text(pDX, IDC_EDIT_usNmlRecNum, m_edit_usNmlRecNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreAfn04F9, CDialog)
	//{{AFX_MSG_MAP(CDlgPreAfn04F9)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK_ALL_VALID, OnCheckAllValid)
	ON_BN_CLICKED(IDC_CHECK_ALL_NOMARL, OnCheckAllNomarl)
	ON_BN_CLICKED(IDC_CHECK_ALL_IMP, OnCheckAllImp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreAfn04F9 message handlers

void CDlgPreAfn04F9::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CBrush BoardBrush;
	BoardBrush.CreateSolidBrush(RGB(128,128,128));
	
	CPen BoardPen;
	BoardPen.CreatePen(PS_SOLID,1,RGB(104,131,144));
	
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&BoardBrush);
	dc.SelectObject(&BoardPen);



	int nStartX = 43, nEndX = 400;
	int nStartY = 0, nEndY = 105;
	int i = 0;
	int nY = 18, y = 0;
	CRect crect;
	CRect pos_rect;
	for (i = 0; i < 20; i++)
	{
	

		y = nEndY + i*nY;
		dc.MoveTo(nStartX, y);
		dc.LineTo(nEndX, y);

		// 调整static 位置
		m_pStatic[i]->GetClientRect(&crect);
		pos_rect.top = y - 15;
		pos_rect.bottom = pos_rect.top + crect.bottom;
		pos_rect.left = nStartX + 10;
		pos_rect.right = pos_rect.left + crect.right;
		m_pStatic[i]->MoveWindow(&pos_rect);

		// 调整check位置
		m_pCheck[i]->GetClientRect(&crect);
		pos_rect.top = y - 15;
		pos_rect.bottom = pos_rect.top + crect.bottom;
		pos_rect.left = nStartX;
		pos_rect.right = pos_rect.left + 200;
		m_pCheck[i]->MoveWindow(&pos_rect);
		
		// radio nomal
		m_pRadioN[i]->GetClientRect(&crect);
		pos_rect.top = y - 15;
		pos_rect.bottom = pos_rect.top + crect.bottom;
		pos_rect.left = nStartX + 220;
		pos_rect.right = pos_rect.left + crect.right;
		m_pRadioN[i]->MoveWindow(&pos_rect);
		
		// radio import

		m_pRadioI[i]->GetClientRect(&crect);
		pos_rect.top = y - 15;
		pos_rect.bottom = pos_rect.top + crect.bottom;
		pos_rect.left = nStartX + 280;
		pos_rect.right = pos_rect.left + crect.right;
		m_pRadioI[i]->MoveWindow(&pos_rect);

	}



	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgPreAfn04F9::OnOK() 
{
	// TODO: Add extra validation here
	SetNewValues();
	CDialog::OnOK();
}

BOOL CDlgPreAfn04F9::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		m_pStatic[i] = (CButton*)GetDlgItem(IDC_STATIC1 + i);
		m_pCheck[i]  = (CButton*)GetDlgItem(IDC_CHECK1 + i);
		
		
		m_pRadioN[i] = (CButton*)GetDlgItem(IDC_RADIO_NML1 + i);
		m_pRadioI[i] = (CButton*)GetDlgItem(IDC_RADIO_IMP1 + i);
		
		m_pStatic[i]->ShowWindow(FALSE);
		m_pCheck[i]->SetWindowText(m_strRec[i]);
		m_pRadioN[i]->SetWindowText("");
		m_pRadioI[i]->SetWindowText("");

		m_pCheck[i]->SetCheck(FALSE);
		EnableRadio(i, FALSE);
	}

	
	m_btn_ok.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_ok.SetIcon(IDI_ICON_RIGHT);
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_ok.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	m_btn_no.SetShade(CShadeButtonST::SHS_VSHADE,8,50,5,RGB(255,255,55));
	m_btn_no.SetIcon(IDI_ICON_X);
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_btn_no.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	
	GetCurValues();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreAfn04F9::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::EnableRadio( int i, BOOL bEnable )
{
	m_pRadioI[i]->EnableWindow(bEnable);
	m_pRadioN[i]->EnableWindow(bEnable);


	if (m_pRadioN[i]->GetCheck() == FALSE && m_pRadioI[i]->GetCheck() == FALSE)
	{
		m_pRadioN[i]->SetCheck(TRUE);
	}
}

void CDlgPreAfn04F9::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	int i = 1;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	int i = 2;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	int i = 3;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck5() 
{
	// TODO: Add your control notification handler code here
	int i = 4;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck6() 
{
	// TODO: Add your control notification handler code here
	int i = 5;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck7() 
{
	// TODO: Add your control notification handler code here
	int i = 6;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck8() 
{
	// TODO: Add your control notification handler code here
	int i = 7;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck9() 
{
	// TODO: Add your control notification handler code here
	int i = 8;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck10() 
{
	// TODO: Add your control notification handler code here
	int i = 9;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck11() 
{
	// TODO: Add your control notification handler code here
	int i = 10;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck12() 
{
	// TODO: Add your control notification handler code here
	int i = 11;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck13() 
{
	// TODO: Add your control notification handler code here
	int i = 12;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck14() 
{
	// TODO: Add your control notification handler code here
	int i = 13;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck15() 
{
	// TODO: Add your control notification handler code here
	int i = 14;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck16() 
{
	// TODO: Add your control notification handler code here
	int i = 15;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck17() 
{
	// TODO: Add your control notification handler code here
	int i = 16;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck18() 
{
	// TODO: Add your control notification handler code here
	int i = 17;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck19() 
{
	// TODO: Add your control notification handler code here
	int i = 18;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheck20() 
{
	// TODO: Add your control notification handler code here
	int i = 19;
	EnableRadio(i, m_pCheck[i]->GetCheck());
}

void CDlgPreAfn04F9::OnCheckAllValid() 
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = m_check_all_valid.GetCheck();
	int i = 0;
	
	for	(i = 0; i < 20; i++)
	{
		m_pCheck[i]->SetCheck(bCheck);
		EnableRadio(i, bCheck);
	}

}

void CDlgPreAfn04F9::OnCheckAllNomarl() 
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = m_check_all_nml.GetCheck();
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		m_pRadioN[i]->SetCheck(bCheck);
			m_pRadioI[i]->SetCheck(!bCheck);
	}

	m_check_all_imp.SetCheck(!bCheck);
}

void CDlgPreAfn04F9::OnCheckAllImp() 
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = m_check_all_imp.GetCheck();
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		m_pRadioN[i]->SetCheck(!bCheck);
		m_pRadioI[i]->SetCheck(bCheck);
	}
	
	m_check_all_nml.SetCheck(!bCheck);
}

void CDlgPreAfn04F9::GetCurValues()
{


	CNxConfig cfg;
	sMcAfn04f9 sData;
	cfg.GetPreAfn04F9(&sData);
	int i = 0;
	int index = 0;
	
	m_edit_usImpRecNum = sData.usImpRecNum;
	m_edit_usNmlRecNum = sData.usNmlRecNum;
	
	for (i = 0; i < sData.ucNeed; i++)
	{
		index = sData.aNeed[i] - 1;
		m_pCheck[index]->SetCheck(TRUE);
		EnableRadio(index, TRUE);
		
		m_pRadioN[index]->SetCheck(TRUE);
		m_pRadioI[index]->SetCheck(FALSE);
	}

	for (i = 0; i < sData.ucImpt; i++)
	{
		index = sData.aImpt[i] - 1;
		m_pRadioN[index]->SetCheck(FALSE);
		m_pRadioI[index]->SetCheck(TRUE);
	}



	UpdateData(FALSE);
}

void CDlgPreAfn04F9::SetNewValues()
{
	UpdateData();

	CNxConfig cfg;
	sMcAfn04f9 sData;
	sData.usImpRecNum = m_edit_usImpRecNum;
	sData.usNmlRecNum = m_edit_usNmlRecNum;
	
	int i = 0;
	int index_imp = 0;
	int index_need = 0;
	eMcErc eErc;


	for (i = 0; i < 20; i++)
	{
		if (m_pCheck[i]->GetCheck() == TRUE)
		{
			eErc = (eMcErc)(i+1);
			sData.aNeed[index_need++] = eErc;

			if(m_pRadioI[i]->GetCheck() == TRUE)
			{
				sData.aImpt[index_imp++] = eErc;
			}
		}
	}
	
	sData.ucNeed = index_need;
	sData.ucImpt = index_imp;

	cfg.SetPreAfn04F9(&sData, TRUE, TRUE);		 
}
