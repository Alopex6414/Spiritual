
// SpiritualDlg.h : ͷ�ļ�
//

#pragma once


// CSpiritualDlg �Ի���
class CSpiritualDlg : public CDialogEx
{
// ����
public:
	CSpiritualDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPIRITUAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	bool m_Close;//Window�ر�
	bool m_Closing;//Window���ڹر�
	bool m_WindowStatus;//Window״̬(True:Create,False:Close)
	int m_WindowAlphaValue;//Window Alpha ͸����

// ʵ��
protected:
	HICON m_hIcon;
	HBRUSH m_hbrush;

	// ���ɵ���Ϣӳ�亯��
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
