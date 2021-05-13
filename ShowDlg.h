#pragma once


// CShowDlg dialog

class CShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowDlg)

public:
	CShowDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShowDlg();

// Dialog Data
	enum { IDD = IDD_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_nWidth;	// 屏幕的宽
	int m_nHeight;	// 屏幕的高
	CDC m_memDC;	// 内存DC
	CRectTracker m_tracker;	// 橡皮筋，也就是可以伸缩矩形框
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// 添加快捷键
	//afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);	// 添加消息响应函数声明
	//afx_msg void OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2);
	//virtual BOOL DestroyWindow();
};
