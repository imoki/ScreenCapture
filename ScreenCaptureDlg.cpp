
// ScreenCaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"
#include "afxdialogex.h"
#include "ShowDlg.h"	// 点击截屏后弹出开始截屏的类

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenCaptureDlg dialog



CScreenCaptureDlg::CScreenCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenCaptureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenCaptureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CScreenCaptureDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CScreenCaptureDlg::OnBnClickedButton3)
	ON_WM_HOTKEY()	//快捷键
END_MESSAGE_MAP()


// CScreenCaptureDlg message handlers

BOOL CScreenCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// 快捷键
	::RegisterHotKey(m_hWnd, 199, MOD_CONTROL, 'U');	// 注册的热键id为199，可以自己改，Ctrl+U。MOD_ALU就是Alt
	::RegisterHotKey(m_hWnd, 200, MOD_CONTROL, 'I');
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//快捷键
void CScreenCaptureDlg::OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2)
{
	if (nHotKeyID == 199)
	{
		//AfxMessageBox(_T("使用了热键"));
		//DoModal();
		ShowWindow(SW_HIDE);	// 点击完后隐藏此对话框
		Sleep(500);	// 休眠500毫秒，以免截屏太快，上面的对话框没来得及完全消失
		CShowDlg dlg;	// 定义点击截图后弹出的窗口
		dlg.DoModal();	// 模态，点击截图，则弹出窗口
		return;
	}
	if (nHotKeyID == 200)
	{
		//AfxMessageBox(_T("使用了热键"));
		//DoModal();
		exit(0);
		return;
	}
	CDialogEx::OnHotKey(nHotKeyID, nKey1, nKey2);
}

BOOL CScreenCaptureDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	::UnregisterHotKey(m_hWnd, 199);
	return CDialogEx::DestroyWindow();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScreenCaptureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 截图按钮
void CScreenCaptureDlg::OnBnClickedButton1()
{
	ShowWindow(SW_HIDE);	// 点击完后隐藏此对话框
	Sleep(500);	// 休眠500毫秒，以免截屏太快，上面的对话框没来得及完全消失
	CShowDlg dlg;	// 定义点击截图后弹出的窗口
	dlg.DoModal();	// 模态，点击截图，则弹出窗口
}


void CScreenCaptureDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//CShowDlg dlg;	// 定义点击截图后弹出的窗口
	//dlg.DoModal();	// 模态，点击截图，则弹出窗口
	ShowWindow(SW_HIDE);	// 点击完后隐藏此对话框
}



