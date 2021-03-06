#pragma once
#include "CSqliteDB.h"
#include "CUserManager.h"
#include "CGroupManager.h"
// CGroupDialog 对话框
class CMessageGroupInfo 
{
public:
	string m_strGroupName;
	string m_strCreaterId;
	string m_strGroupId;
};
class CGroupDialog : public CDialogEx, public IGroupManagerListener
{
	DECLARE_DYNAMIC(CGroupDialog)

public:
	CGroupDialog(CUserManager* pUserManager, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGroupDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IM_GROUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void getGroupList();
	void resetGroupList();
	void clearMsgList();
	void getMsgList(string conversationId);
	void resetMsgList();

	void getGroupMemberList(string strGroupId);
	void resetGroupMemberList();

	void clearHistoryList();
	void getHistoryList();
	void addHistoryList(CHistoryBean* pHistoryBean, string strFromId);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCreateGroup();
	afx_msg void OnBnClickedButtonGroupSendMsg();
public:
	/**
	 * 群成员数发生变化
	 * @param groupID
	 * @param number
	 */
	virtual void onMembersUpdeted(string groupID, int number);

	/**
	 * 自己被移出群组
	 * @param groupID
	 */
	virtual void onSelfKicked(string groupID);

	/**
	 * 群组已经被删除
	 * @param groupID
	 */
	virtual void onGroupDeleted(string groupID);

	/**
	 *  收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(string groupId, CIMMessage* pMessage);

	/**
	 *  创建群组回调
	 * @param message
	 */
	virtual void onApplyCreateGroupFin(string groupID);

	/**
	 *  删除群组回调
	 * @param message
	 */
	virtual void onApplyDelGroupFin(string groupID);

	/**
	 *  添加成员回调
	 * @param message
	 */
	virtual void onApplyAddUserToGroupFin(string groupID);

	/**
	 *  删除成员回调
	 * @param message
	 */
	virtual void onApplyRemoveUserFromGroupFin(string groupID);
public:
	CListCtrl m_groupList;
	CListBox m_recvDataListBox;
	CEdit m_sendMsgEdit;
	list<CMessageBean*> mDatas;
	list<CHistoryBean*> mHistoryDatas;
	list<CMessageGroupInfo> mGroupList;
	list<string> mGroupMemberList;
	CMessageGroupInfo* m_pCurrentGroup;
	CSqliteDB* m_pSqliteDB;
	CGroupManager* m_pGroupManager;
	CUserManager* m_pUserManager;
	
	afx_msg void OnNMClickListGroupList(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_GroupName;
	afx_msg void OnMenuGroupAddMem();
	afx_msg void OnMenuGroupSetRecvmsgStatus();
	afx_msg void OnNMRClickListGroupList(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_GroupMemberList;
	afx_msg void OnBnClickedButtonGroupAddMember();
};
