#pragma once
#include "CUserManager.h"

// CSettingDialog 对话框

class CSettingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDialog)

public:
	CSettingDialog(CUserManager* pUserManager, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDialog();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetServerParam();
public:
	CUserManager* m_pUserManager;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboResolutionRatio();
	CComboBox m_ResolutionRatio;
};
