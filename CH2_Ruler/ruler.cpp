#include "ruler.h"
#include"resource.h"

CMyapp myApp;

BOOL CMyapp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON1)),FALSE);
	
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("Ruler"),WS_OVERLAPPEDWINDOW|WS_HSCROLL);
}
///////////////////////////////////////



void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	//dc.SetMapMode(MM_LOENGLISH);
	dc.SetBkMode(TRANSPARENT);
	dc.SetWindowOrg(m_nHScrollPos, 0);
	CBrush	 brush(RGB(255, 255, 0));
	CBrush* pOldBrush = dc.SelectObject(&brush);

	dc.Rectangle(100, 100, 13000, 200);
	dc.SelectObject(pOldBrush);

	for (int i=125;i<13000;i+=25)
	{
		dc.MoveTo(i, 192);
		dc.LineTo(i, 200);
	}
	for (int i = 150; i < 13000; i += 50)
	{
		dc.MoveTo(i, 184);
		dc.LineTo(i, 200);
	}
	dc.SetTextAlign(TA_CENTER);
	for (int i = 200; i < 13000; i += 100)
	{
		dc.MoveTo(i, 175);
		dc.LineTo(i, 200);

		CString string;
		string.Format(_T("%d"), (i / 100) - 1);
		dc.TextOut(i, 165, string);
	}
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct)==-1)
		return -1;
	
	CClientDC dc(this);
	m_nViewWidth = 13000;
	//m_nViewWidth = lpCreateStruct->cx;
	return 0;
}

void CMainWindow::OnSize(UINT nType, int cx, int cy)
{

	
	int nHScrollMax = 0;
	m_nHScrollPos = m_nHPageSize = 0;
	if (cx<m_nViewWidth)
	{
		nHScrollMax = m_nViewWidth - 1;
		m_nHPageSize = cx;
		m_nHScrollPos = min(m_nHScrollPos, m_nViewWidth - m_nHPageSize - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = nHScrollMax;
	si.nPos = m_nHScrollPos;
	si.nPage = m_nHPageSize;
	SetScrollInfo(SB_HORZ, &si, TRUE);
}

void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar==VK_RIGHT)
	{
		//MessageBox(_T("LEFT°´ÏÂ"), NULL, MB_OK);
		SendMessage(WM_HSCROLL, SB_PAGERIGHT, 0);
	}


}

void CMainWindow::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	switch (nSBCode)
	{
	case SB_PAGELEFT:
		nDelta = -m_nHPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)nPos - m_nHScrollPos;
		break;
	case SB_PAGERIGHT:
		nDelta = m_nHPageSize;
		break;

	default:
		return ;
	}
	int nScrollPos = m_nHScrollPos + nDelta;
	int nMaxPos = m_nViewWidth - m_nHPageSize;
	if (nScrollPos<0)
	{
		nDelta = -m_nHScrollPos;
	}
	else if (nScrollPos > nMaxPos)
		nDelta = nMaxPos - m_nHScrollPos;
	if (nDelta != 0) {
		m_nHScrollPos += nDelta;
		SetScrollPos(SB_HORZ, m_nHScrollPos, TRUE);
		ScrollWindow(-nDelta, 0);
	}
}
