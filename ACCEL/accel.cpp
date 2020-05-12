#include "accel.h"
CMyApp myApp;
CMainWnd::CMainWnd()
{
	Create(NULL, _T("Accel App"),WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL);
}

void CMainWnd::OnPaint()
{
	CPaintDC dc(this);
	CPen pen(PS_SOLID,0,RGB(192,192,192));
	CPen* OldPen = dc.SelectObject(&pen);

	CString cstring;
	CRect rect;
	dc.SetWindowOrg(m_nHScrollpos, m_nVScrollpos);
	for (int i=0;i<999;i++)
	{
		int y = (i * m_nCellHight) + m_nCellHight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nViewWidth, y);
	}
	for (int i=0;i<26;i++)
	{
		int x = (i * m_nCellwidth) + m_nRibbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_nViewHight);
	}

	dc.SelectObject(OldPen);

	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);
	CRect rcTop(0, 0, m_nViewWidth, m_nCellHight);
	//顶部与左侧灰色带填满

	dc.FillRect(&rcTop, &brush);

	CRect rcLeft(0, 0, m_nRibbonWidth, m_nViewHight);
	dc.FillRect(&rcLeft, &brush);
	
	//划线
	dc.MoveTo(0, m_nCellHight);
	dc.LineTo(m_nViewWidth, m_nCellHight);
	dc.MoveTo(m_nRibbonWidth, 0);
	dc.LineTo(m_nRibbonWidth, m_nViewHight);

	dc.SetBkMode(TRANSPARENT);
	
for (int i = 0; i < 999; i++)
	{
	
		int y = (i * m_nCellHight) + m_nCellHight;

		dc.MoveTo(0, y);
		dc.LineTo(m_nRibbonWidth, y );
		//rect.left = 0;
		//rect.top = y;
		//rect.right = m_nRibbonWidth;
		//rect.bottom = (i + 2) * m_nCellHight;
		cstring.Format(_T("%d"), i + 1);
		CRect rect(0, y, m_nRibbonWidth, y + m_nCellHight);

		dc.DrawText(cstring, &rect, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		rect.top++;
		dc.Draw3dRect(rect, RGB(255,255,255), RGB(128, 128, 128));
	}
	for (int i=0;i<26;i++)
	{
		int x = i * m_nCellwidth + m_nRibbonWidth;
		dc.MoveTo(x,0 );
		dc.LineTo(x, m_nCellHight);

		cstring.Format(_T("%c"), 'A' + i);
		CRect rect(x, 0, x + m_nCellwidth, m_nCellHight);
		dc.DrawText(cstring, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		rect.left++;
		dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}
}
//水平滚动处理
void CMainWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	switch (nSBCode)
	{
	case SB_LINELEFT:
		nDelta = -LINESIZE;
		break;
	case SB_LINERIGHT:
		nDelta =+ LINESIZE;
		break;

	case SB_PAGELEFT:
		nDelta = -m_nHPageSize;
		break;
	case SB_PAGERIGHT:
		nDelta =+ m_nHPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)nPos-m_nHScrollpos;
		break;

	default:
		return;
	}
	int nScorllPos = m_nHScrollpos + nDelta;
	int nMaxPos = m_nViewWidth-m_nHPageSize;


	if (nScorllPos<0)
	{
		nDelta = -m_nHScrollpos;
	}else if (nScorllPos>nMaxPos)
	{
		nDelta = nMaxPos - m_nHScrollpos;
	}
	if (nDelta != 0) 
	{
		m_nHScrollpos += nDelta;

		SetScrollPos(SB_HORZ, m_nHScrollpos, TRUE);
		ScrollWindow(-nDelta, 0);
	}

}

//垂直滚动处理
void CMainWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	switch (nSBCode)
	{
	case SB_LINEDOWN:
		nDelta = +LINESIZE;
		break;
	case SB_LINEUP:
		nDelta = -LINESIZE;
		break;
	case SB_PAGEDOWN:
		nDelta = +m_nVPageSize;
		break;
	case SB_PAGEUP:
		nDelta = -m_nVPageSize;
		break;

	case SB_THUMBTRACK:
		nDelta = nPos - m_nVScrollpos;
		break;
	default:
		return ;
	}

	//变化后的位置
	int n_ScrollPos = m_nVScrollpos + nDelta;
	//最大位移量
	int nMaxPos = m_nViewHight - m_nVPageSize ;
	if (n_ScrollPos<0)
	{
		nDelta = -m_nVScrollpos;
	}
	else if (n_ScrollPos>nMaxPos)
	{
		nDelta = nMaxPos - m_nVScrollpos;
	}
	if (nDelta!=0)
	{
		m_nVScrollpos += nDelta;
		SetScrollPos(SB_VERT, m_nVScrollpos, TRUE);
		ScrollWindow(0, -nDelta);
	}
}

void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_LEFT:
		SendMessage(WM_HSCROLL, (WPARAM)SB_LINELEFT, 0L);
		break;
	case VK_RIGHT:
		SendMessage(WM_HSCROLL, (WPARAM)SB_LINERIGHT, 0L);
		break;
	case VK_UP:
		SendMessage(WM_VSCROLL, (WPARAM)SB_LINEUP, 0L);
		break;
	case VK_DOWN:
		SendMessage(WM_VSCROLL, (WPARAM)SB_LINEDOWN, 0L);
		break;
	case VK_PRIOR:
		SendMessage(WM_VSCROLL, (WPARAM)SB_PAGEUP, 0L);
		break;
	case VK_NEXT:
		SendMessage(WM_VSCROLL, (WPARAM)SB_PAGEDOWN, 0L);
		break;
	default:
		return ;
	}
}

BOOL CMainWnd::OnMouseWheel(UINT nFlag, short zDelta, CPoint point)
{
	BOOL bUp = TRUE;
	int nDelta = zDelta;
	if (zDelta<0)
	{
		bUp = FALSE;
		nDelta = -nDelta;
	}

	UINT nWheelScrollLines;
	::SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0,&nWheelScrollLines,0);
	if (nWheelScrollLines==WHEEL_PAGESCROLL)
	{
		SendMessage(WM_VSCROLL, MAKEWPARAM(bUp ? SB_PAGEUP : SB_PAGEDOWN, 0), 0);
	}
	else {
		int nLines = (nDelta * nWheelScrollLines) / WHEEL_DELTA;
		while (nLines--)
		{
			SendMessage(WM_VSCROLL, MAKEWPARAM(bUp ? SB_LINEUP : SB_LINEDOWN, 0), 0);
		}
	}
	return TRUE;
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CClientDC dc(this);
	m_nCellwidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_nCellHight=dc.GetDeviceCaps(LOGPIXELSY)/4;
	m_nRibbonWidth = m_nCellwidth / 2;
	m_nViewWidth = (26 * m_nCellwidth) + m_nRibbonWidth;
	m_nViewHight = m_nCellHight * 1000;

	return TRUE;
}

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	//设置水平滚动条参数
	int m_nHScrollMax = 0;    
	m_nHScrollpos = m_nHPageSize = 0;//初始化
	if (cx<m_nViewWidth)
	{
		m_nHPageSize = cx;
		m_nHScrollMax = m_nViewWidth - 1;
		m_nHScrollpos = min(m_nHScrollpos, m_nViewWidth - m_nHPageSize - 1);
	}
	SCROLLINFO si;
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = m_nHScrollMax;
	si.nPos = m_nHScrollpos;
	si.nPage = m_nHPageSize;

	SetScrollInfo(SB_HORZ, &si, TRUE);
	
	//设置垂直滚动条参数
	int m_nVScrollMax = 0;
	m_nVScrollpos = m_nVPageSize = 0;
	if (cy<m_nViewHight)
	{
		m_nVPageSize = cy;
		m_nVScrollMax = m_nViewHight - 1;
		m_nVScrollpos = min(m_nVScrollpos, m_nViewHight - m_nVPageSize - 1);
	}
	si.fMask = SIF_ALL;
	si.nMax = m_nVScrollMax;
	si.nMin = 0;
	si.nPage = m_nVPageSize;
	si.nPos = m_nVScrollpos;

	SetScrollInfo(SB_VERT, &si, TRUE);

}

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

//////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	END_MESSAGE_MAP()
