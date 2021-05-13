// ShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenCapture.h"
#include "ShowDlg.h"
#include "afxdialogex.h"


// CShowDlg dialog

IMPLEMENT_DYNAMIC(CShowDlg, CDialogEx)

CShowDlg::CShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowDlg::IDD, pParent)
{
	// 采集屏幕当前瞬间的图像

	// 获取屏幕的宽和高
	m_nWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// 获取桌面DC
	// 设备上下文
	CDC *pDC = GetDesktopWindow()->GetDC();
	// 创建位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, m_nWidth, m_nHeight);
	// 创建内存DC
	m_memDC.CreateCompatibleDC(pDC);
	m_memDC.SelectObject(&bmp);
	m_memDC.BitBlt(0, 0, m_nWidth, m_nHeight, pDC, 0, 0, SRCCOPY);

	// 释放DC，释放GDI对象
	pDC->DeleteDC();
	bmp.DeleteObject();

}

CShowDlg::~CShowDlg()
{
}

void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//ON_MESSAGE(WM_HOTKEY,OnHotKey) 
	//ON_WM_HOTKEY()	//快捷键
END_MESSAGE_MAP()


// CShowDlg message handlers


// 初始化
BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 快捷键
	::RegisterHotKey(m_hWnd, 199, MOD_CONTROL, 'U');	// 注册的热键id为199，可以自己改，Ctrl+U。MOD_ALU就是Alt

	// 将窗口移动，调节成和屏幕一样大,前两位参数是移动到的初始坐标在左上角，后两位的最后的坐标在右下角
	MoveWindow(0, 0, m_nWidth, m_nHeight);
	
	// 初始化橡皮筋
	// resizeInside是点向里，resizeOutside点向外，dottedline是虚线,solidLine是实线
	m_tracker.m_nStyle = (CRectTracker::resizeInside | CRectTracker::solidLine); 
	m_tracker.m_nHandleSize = 5;	// 控制柄的像素大小
	m_tracker.m_rect.SetRect(0, 0, 0, 0);	// 初始化选框大小，没有大小
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*
//快捷键
void CShowDlg::OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2)
{
	if (nHotKeyID == 199)
	{
		AfxMessageBox(_T("使用了热键"));
		//DoModal();
		return;
	}
	CDialogEx::OnHotKey(nHotKeyID, nKey1, nKey2);
}

BOOL CShowDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	::UnregisterHotKey(m_hWnd, 199);
	return CDialogEx::DestroyWindow();
}
*/

void CShowDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	// 将桌面图像显示到对话框上，达到一截屏就屏幕就“不动”
	dc.BitBlt(0, 0, m_nWidth, m_nHeight, &m_memDC, 0, 0, SRCCOPY);

	// 绘制橡皮筋
	m_tracker.Draw(&dc);
}


void CShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	// 选择函数，按F1可以自动去浏览器查找说明。这里是HitTest的返回值
	// CRectTracker::hitNothing    –1
	//	CRectTracker::hitTopLeft   0
	//	CRectTracker::hitTopRight   1
	//	CRectTracker::hitBottomRight   2
	//	CRectTracker::hitBottomLeft   3
	//	CRectTracker::hitTop   4
	//	CRectTracker::hitRight   5
	//	CRectTracker::hitBottom   6
	//	CRectTracker::hitLeft   7
	//	CRectTracker::hitMiddle   8

	// 如果点中的区域是上一次框选的区域，那么不会出现画，否则就可以在另一个区域重新框选
	if (m_tracker.HitTest(point) == CRectTracker::hitNothing)
	{
		m_tracker.TrackRubberBand(this, point, TRUE);	// 是否允许翻转，TRUE是允许，FALSE是不允许
		m_tracker.m_rect.NormalizeRect();	// 如果允许翻转那么需要让矩形坐标正常化
	}
	else // 如果鼠标点在选取里面，则可以移动选区
	{
		m_tracker.Track(this, point, TRUE);	// 挪动选区,如果是边则可以改变大小，在内部则可以移动
		m_tracker.m_rect.NormalizeRect();
	}

	Invalidate(FALSE);	// FALSE刷新不擦除背景

	CDialogEx::OnLButtonDown(nFlags, point);
}

// 双击
void CShowDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	// 获取选框大小
	int nWidth = m_tracker.m_rect.Width();
	int nHeight = m_tracker.m_rect.Height();
	// 创建一个位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&m_memDC, nWidth, nHeight);	
	// 做一个临时内存DC
	CDC tempDC;
	tempDC.CreateCompatibleDC(NULL);
	tempDC.SelectObject(&bmp);
	// 复制数据
	tempDC.BitBlt(0, 0, nWidth, nHeight, &m_memDC, m_tracker.m_rect.left, m_tracker.m_rect.top, SRCCOPY);

	// 放到剪切板里，先打开剪切板
	OpenClipboard();
	// 清空剪切板
	EmptyClipboard();
	// 设置剪切板数据
	SetClipboardData(CF_BITMAP, bmp);
	// 关闭剪切板
	CloseClipboard();

	// 结束程序
	//exit(0);
	EndDialog(0);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}



