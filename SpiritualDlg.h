
// SpiritualDlg.h : 头文件
//

#pragma once


// CSpiritualDlg 对话框
class CSpiritualDlg : public CDialogEx
{
// 构造
public:
	CSpiritualDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPIRITUAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	bool m_Close;//Window关闭
	bool m_Closing;//Window正在关闭
	bool m_WindowStatus;//Window状态(True:Create,False:Close)
	int m_WindowAlphaValue;//Window Alpha 透明度

// 实现
protected:
	HICON m_hIcon;
	HBRUSH m_hbrush;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void InitializeWindow();
	void RePaintWindow();
	void CleanUpWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	void SpiritualConfigWrite();
	void SpiritualConfigRead();
	void SpiritualCaculateMusicList();
	void SpiritualPlayMusic();
	afx_msg void OnClose();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
