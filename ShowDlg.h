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
	int m_nWidth;	// ��Ļ�Ŀ�
	int m_nHeight;	// ��Ļ�ĸ�
	CDC m_memDC;	// �ڴ�DC
	CRectTracker m_tracker;	// ��Ƥ�Ҳ���ǿ����������ο�
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// ��ӿ�ݼ�
	//afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);	// �����Ϣ��Ӧ��������
	//afx_msg void OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2);
	//virtual BOOL DestroyWindow();
};
