#pragma once
#include "CProcessInfo.h"
#include "CLiveProgram.h"
#include "CUserManager.h"
#include "CDataShowView.h"

#include "CLiveManager.h"
// CInteracteLiveDlg 对话框
class CShowPicData
{
public:
	CShowPicData(int width, int height, uint8_t* videoData, int dataLength)
	{
		m_nWidth = width;
		m_nHeight = height;
		m_nDataLength = dataLength;
		m_pVideoData = new uint8_t[dataLength];
		memset(m_pVideoData, 0, sizeof(uint8_t)*dataLength);
		memcpy(m_pVideoData, videoData, sizeof(uint8_t)*dataLength);
	}
	~CShowPicData() 
	{
		if (m_pVideoData != NULL)
		{
			delete[] m_pVideoData;
			m_pVideoData = NULL;
		}
	}
public:
	int m_nWidth;
	int m_nHeight;
	uint8_t* m_pVideoData;
	int m_nDataLength;
};
/*
 * 互动直播对话框
 */
class CInteracteLiveDlg : public CDialogEx, public CPicControlCallback, virtual public IVdnManagerListener, virtual public ISrcManagerListener, public IChatroomManagerListener
{
	DECLARE_DYNAMIC(CInteracteLiveDlg)

public:
	CInteracteLiveDlg(CUserManager* pUserManager, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInteracteLiveDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	/*
	 * 获取直播列表
	 */
	void getLiveList();

	/*
	 * 刷新列表
	 */
	afx_msg void OnBnClickedButtonLiveBrushList();
	/*
	 * 关闭当前直播
	 */
	afx_msg LRESULT setShowPictures(WPARAM wParam, LPARAM lParam);
	/*
	 * 绘制
	 */
	afx_msg void OnPaint();
	/*
	 * list 选择改变
	 */
	afx_msg void OnLbnSelchangeList1();
	/*
	 * 销毁函数
	 */
	afx_msg void OnDestroy();
	/*
	 * 创建新直播
	 */
	afx_msg void OnBnClickedButtonCreateNewLive();
	/*
	 * 初始化对话框
	 */
	virtual BOOL OnInitDialog();
	
	/*
	 * 查询直播内容
	 */
	CLiveProgram* getLiveProgram(CString strName);

	/*
	 * 将显示图片放入队列
	 */
	void putShowPicData(int width, int height, uint8_t* videoData, int dataLength);

	/*
	 * 清空显示图片队列
	 */
	void clearShowPicDataQueue();

public:
	// picture control 回调函数
	/*
	 * 右键退出回调
	 */
	virtual void liveExit(void* pParam);
	/*
	 * 双击修改配置回调
	 */
	virtual void changeStreamConfig(void* pParam, int upid);
	/*
	 * 关闭当前直播
	 */
	virtual void closeCurrentLive(void* pParam);
	/*
	 * 开启人脸识别
	 */
	virtual void startFaceFeature(void* pParam);
	/*
	 * 停止人脸识别
	 */
	virtual void stopFaceFeature(void* pParam);

public:
	// start回调函数
	virtual int downloadChannelClosed();
	virtual int downloadChannelLeave();
	virtual int downloadNetworkUnnormal();
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum);
	virtual int uploaderAdd(char* upUserId, int upId);
	virtual int uploaderRemove(char* upUserId, int upId);
	virtual int getRealtimeData(int upId, uint8_t* data, int len);
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	virtual int deleteChannel(char* channelId);
	virtual int stopOK();
	virtual int srcError(char* errString);
public:
	/**
	 * 聊天室成员数变化
	 * @param number
	 */
	virtual void onMembersUpdated(int number);

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked();

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfMuted(int seconds);

	/**
	 * 聊天室已关闭
	 */
	virtual void onClosed();

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage);

	/**
	 * 收到私信消息
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage);
public:
	CListBox m_liveList;
	CDataShowView* m_pDataShowView;
	CUserManager* m_pUserManager;

	CLiveManager* m_pLiveManager;
	vector<CLiveProgram> mVLivePrograms;
	HANDLE m_hGetCameraDataThread;
	HANDLE m_hGetDataEvent;
	HANDLE m_hExitEvent;

	HANDLE m_hSetShowPicThread;
	HANDLE m_hSetShowPicEvent;


	queue<CShowPicData*> m_ShowPicDataQueue;
	CRITICAL_SECTION m_csShowPicDataQueue;

	HANDLE m_hShowPicThread;

	int m_nUpId;
	bool m_bExit;
	bool m_bStop;
	CStatic m_ShowArea;
	CListCtrl m_liveListListControl;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
