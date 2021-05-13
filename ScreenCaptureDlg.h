
// ScreenCaptureDlg.h : header file
//

#pragma once


// CScreenCaptureDlg dialog
class CScreenCaptureDlg : public CDialogEx
{
// Construction
public:
	CScreenCaptureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCREENCAPTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	// ¿ì½Ý¼ü
	afx_msg void OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2);
	virtual BOOL DestroyWindow();
};
