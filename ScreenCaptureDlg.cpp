
// ScreenCaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"
#include "afxdialogex.h"
#include "ShowDlg.h"	// ��������󵯳���ʼ��������

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
	ON_WM_HOTKEY()	//��ݼ�
END_MESSAGE_MAP()


// CScreenCaptureDlg message handlers

BOOL CScreenCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// ��ݼ�
	::RegisterHotKey(m_hWnd, 199, MOD_CONTROL, 'U');	// ע����ȼ�idΪ199�������Լ��ģ�Ctrl+U��MOD_ALU����Alt
	::RegisterHotKey(m_hWnd, 200, MOD_CONTROL, 'I');
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//��ݼ�
void CScreenCaptureDlg::OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2)
{
	if (nHotKeyID == 199)
	{
		//AfxMessageBox(_T("ʹ�����ȼ�"));
		//DoModal();
		ShowWindow(SW_HIDE);	// ���������ش˶Ի���
		Sleep(500);	// ����500���룬�������̫�죬����ĶԻ���û���ü���ȫ��ʧ
		CShowDlg dlg;	// ��������ͼ�󵯳��Ĵ���
		dlg.DoModal();	// ģ̬�������ͼ���򵯳�����
		return;
	}
	if (nHotKeyID == 200)
	{
		//AfxMessageBox(_T("ʹ�����ȼ�"));
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


// ��ͼ��ť
void CScreenCaptureDlg::OnBnClickedButton1()
{
	ShowWindow(SW_HIDE);	// ���������ش˶Ի���
	Sleep(500);	// ����500���룬�������̫�죬����ĶԻ���û���ü���ȫ��ʧ
	CShowDlg dlg;	// ��������ͼ�󵯳��Ĵ���
	dlg.DoModal();	// ģ̬�������ͼ���򵯳�����
}


void CScreenCaptureDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//CShowDlg dlg;	// ��������ͼ�󵯳��Ĵ���
	//dlg.DoModal();	// ģ̬�������ͼ���򵯳�����
	ShowWindow(SW_HIDE);	// ���������ش˶Ի���
}



