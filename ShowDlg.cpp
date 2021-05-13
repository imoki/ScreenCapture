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
	// �ɼ���Ļ��ǰ˲���ͼ��

	// ��ȡ��Ļ�Ŀ�͸�
	m_nWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// ��ȡ����DC
	// �豸������
	CDC *pDC = GetDesktopWindow()->GetDC();
	// ����λͼ
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, m_nWidth, m_nHeight);
	// �����ڴ�DC
	m_memDC.CreateCompatibleDC(pDC);
	m_memDC.SelectObject(&bmp);
	m_memDC.BitBlt(0, 0, m_nWidth, m_nHeight, pDC, 0, 0, SRCCOPY);

	// �ͷ�DC���ͷ�GDI����
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
	//ON_WM_HOTKEY()	//��ݼ�
END_MESSAGE_MAP()


// CShowDlg message handlers


// ��ʼ��
BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��ݼ�
	::RegisterHotKey(m_hWnd, 199, MOD_CONTROL, 'U');	// ע����ȼ�idΪ199�������Լ��ģ�Ctrl+U��MOD_ALU����Alt

	// �������ƶ������ڳɺ���Ļһ����,ǰ��λ�������ƶ����ĳ�ʼ���������Ͻǣ�����λ���������������½�
	MoveWindow(0, 0, m_nWidth, m_nHeight);
	
	// ��ʼ����Ƥ��
	// resizeInside�ǵ����resizeOutside�����⣬dottedline������,solidLine��ʵ��
	m_tracker.m_nStyle = (CRectTracker::resizeInside | CRectTracker::solidLine); 
	m_tracker.m_nHandleSize = 5;	// ���Ʊ������ش�С
	m_tracker.m_rect.SetRect(0, 0, 0, 0);	// ��ʼ��ѡ���С��û�д�С
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*
//��ݼ�
void CShowDlg::OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2)
{
	if (nHotKeyID == 199)
	{
		AfxMessageBox(_T("ʹ�����ȼ�"));
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

	// ������ͼ����ʾ���Ի����ϣ��ﵽһ��������Ļ�͡�������
	dc.BitBlt(0, 0, m_nWidth, m_nHeight, &m_memDC, 0, 0, SRCCOPY);

	// ������Ƥ��
	m_tracker.Draw(&dc);
}


void CShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	// ѡ��������F1�����Զ�ȥ���������˵����������HitTest�ķ���ֵ
	// CRectTracker::hitNothing    �C1
	//	CRectTracker::hitTopLeft   0
	//	CRectTracker::hitTopRight   1
	//	CRectTracker::hitBottomRight   2
	//	CRectTracker::hitBottomLeft   3
	//	CRectTracker::hitTop   4
	//	CRectTracker::hitRight   5
	//	CRectTracker::hitBottom   6
	//	CRectTracker::hitLeft   7
	//	CRectTracker::hitMiddle   8

	// ������е���������һ�ο�ѡ��������ô������ֻ�������Ϳ�������һ���������¿�ѡ
	if (m_tracker.HitTest(point) == CRectTracker::hitNothing)
	{
		m_tracker.TrackRubberBand(this, point, TRUE);	// �Ƿ�����ת��TRUE������FALSE�ǲ�����
		m_tracker.m_rect.NormalizeRect();	// �������ת��ô��Ҫ�þ�������������
	}
	else // ���������ѡȡ���棬������ƶ�ѡ��
	{
		m_tracker.Track(this, point, TRUE);	// Ų��ѡ��,����Ǳ�����Ըı��С�����ڲ�������ƶ�
		m_tracker.m_rect.NormalizeRect();
	}

	Invalidate(FALSE);	// FALSEˢ�²���������

	CDialogEx::OnLButtonDown(nFlags, point);
}

// ˫��
void CShowDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	// ��ȡѡ���С
	int nWidth = m_tracker.m_rect.Width();
	int nHeight = m_tracker.m_rect.Height();
	// ����һ��λͼ
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&m_memDC, nWidth, nHeight);	
	// ��һ����ʱ�ڴ�DC
	CDC tempDC;
	tempDC.CreateCompatibleDC(NULL);
	tempDC.SelectObject(&bmp);
	// ��������
	tempDC.BitBlt(0, 0, nWidth, nHeight, &m_memDC, m_tracker.m_rect.left, m_tracker.m_rect.top, SRCCOPY);

	// �ŵ����а���ȴ򿪼��а�
	OpenClipboard();
	// ��ռ��а�
	EmptyClipboard();
	// ���ü��а�����
	SetClipboardData(CF_BITMAP, bmp);
	// �رռ��а�
	CloseClipboard();

	// ��������
	//exit(0);
	EndDialog(0);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}



