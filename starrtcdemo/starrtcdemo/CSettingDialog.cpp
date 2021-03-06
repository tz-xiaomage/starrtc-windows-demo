// CSettingDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "starrtcdemo.h"
#include "CSettingDialog.h"
#include "afxdialogex.h"
#include "CSeviceParamDialog.h"

// CSettingDialog 对话框

IMPLEMENT_DYNAMIC(CSettingDialog, CDialogEx)

CSettingDialog::CSettingDialog(CUserManager* pUserManager, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{
	m_pUserManager = pUserManager;
}

CSettingDialog::~CSettingDialog()
{
}

void CSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION_RATIO, m_ResolutionRatio);
}


BEGIN_MESSAGE_MAP(CSettingDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SET_SERVER_PARAM, &CSettingDialog::OnBnClickedButtonSetServerParam)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION_RATIO, &CSettingDialog::OnCbnSelchangeComboResolutionRatio)
END_MESSAGE_MAP()


// CSettingDialog 消息处理程序


void CSettingDialog::OnBnClickedButtonSetServerParam()
{
	CSeviceParamDialog dlg(m_pUserManager);
	dlg.DoModal();
}


BOOL CSettingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_ResolutionRatio.AddString("大图:176*320|小图:无");
	m_ResolutionRatio.AddString("大图:176*320|小图:88*160");

	m_ResolutionRatio.AddString("大图:240*320|小图:无");
	m_ResolutionRatio.AddString("大图:240*320|小图:120*160");

	m_ResolutionRatio.AddString("大图:480*480|小图:无");
	m_ResolutionRatio.AddString("大图:480*480|小图:120*120");
	m_ResolutionRatio.AddString("大图:480*480|小图:240*240");

	m_ResolutionRatio.AddString("大图:360*640|小图:无");
	m_ResolutionRatio.AddString("大图:360*640|小图:90*160");
	m_ResolutionRatio.AddString("大图:360*640|小图:180*320");

	m_ResolutionRatio.AddString("大图:480*640|小图:无");
	m_ResolutionRatio.AddString("大图:480*640|小图:120*160");
	m_ResolutionRatio.AddString("大图:480*640|小图:240*320");

	m_ResolutionRatio.AddString("大图:640*640|小图:无");
	m_ResolutionRatio.AddString("大图:640*640|小图:160*160");
	m_ResolutionRatio.AddString("大图:640*640|小图:320*320");

	m_ResolutionRatio.AddString("大图:720*1280|小图:无");
	m_ResolutionRatio.AddString("大图:720*1280|小图:90*160");
	m_ResolutionRatio.AddString("大图:720*1280|小图:180*320");
	m_ResolutionRatio.AddString("大图:720*1280|小图:360*640");

	m_ResolutionRatio.AddString("大图:1080*1920|小图:无");
	m_ResolutionRatio.AddString("大图:1080*1920|小图:135*240");
	m_ResolutionRatio.AddString("大图:1080*1920|小图:270*480");
	m_ResolutionRatio.AddString("大图:1080*1920|小图:540*960");

	m_ResolutionRatio.AddString("大图:特殊制定|小图:无");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSettingDialog::OnCbnSelchangeComboResolutionRatio()
{
	
}
