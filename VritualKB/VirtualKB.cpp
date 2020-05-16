#include "VritualKB.h"

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
BEGIN_MESSAGE_MAP(CMainWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	ON_WM_CHAR()
	ON_WM_SYSCHAR()
	END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	m_nTextPos = 0;
	m_nMsgPos = 0;

	//保存鼠标句柄
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hCursorBeam = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);

	//register wndclass
	CString strWndClass = AfxRegisterWndClass(0, NULL, (HBRUSH)(COLOR_3DFACE + 1), AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));

	//create window
	CreateEx(0, strWndClass, _T("Virtual KeyBoard"), WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
	
}

int CMainWindow::GetNearestPos(CPoint point)
{
	if (point.x <= m_ptTextOrigin.x)
		return 0;

	CClientDC dc(this);
	int nlen = m_strInputText.GetLength();
	if (point.x >= (m_ptTextOrigin.x + (dc.GetTextExtent(m_strInputText, nlen)).cx))
		return nlen;

	int i = 0;
	int nPrevChar = m_ptTextOrigin.x;
	int nNextChar = m_ptTextOrigin.x;

	while (nNextChar<point.x)
	{
		i++;
		nPrevChar = nNextChar;
		nNextChar = m_ptTextOrigin.x +
			(dc.GetTextExtent(m_strInputText.Left(i), i)).cx;
	}
	return ((point.x - nPrevChar) < (nNextChar - point.x)) ? i-1 : i;
}
/*
int CMainWindow::GetNearestPos(CPoint point)
{
	//
	// Return 0 if (point.x, point.y) lies to the left of the text in
	// the text box.
	//
	if (point.x <= m_ptTextOrigin.x)
		return 0;

	//
	// Return the string length if (point.x, point.y) lies to the right
	// of the text in the text box.
	//
	CClientDC dc(this);
	int nLen = m_strInputText.GetLength();
	if (point.x >= (m_ptTextOrigin.x +
		(dc.GetTextExtent(m_strInputText, nLen)).cx))
		return nLen;

	//
	// Knowing that (point.x, point.y) lies somewhere within the text
	// in the text box, convert the coordinates into a character index.
	//
	int i = 0;
	int nPrevChar = m_ptTextOrigin.x;
	int nNextChar = m_ptTextOrigin.x;

	while (nNextChar < point.x) {
		i++;
		nPrevChar = nNextChar;
		nNextChar = m_ptTextOrigin.x +
			(dc.GetTextExtent(m_strInputText.Left(i), i)).cx;
	}
	return ((point.x - nPrevChar) < (nNextChar - point.x)) ? i - 1 : i;
}
*/

void CMainWindow::PositionCaret(CDC* pDC)
{
	BOOL bRelease = FALSE;

	//create dc if pdc==null
	if (pDC == NULL)
	{
		pDC = GetDC();
		bRelease = TRUE;
	}

	//
	CPoint point = m_ptTextOrigin;
	//?????????????????????????????????????????????????
	CString string = m_strInputText.Left(m_nTextPos);
	point.x += (pDC->GetTextExtent(string, string.GetLength())).cx;
	SetCaretPos(point);

	if (bRelease)
		ReleaseDC(pDC);
}

void CMainWindow::DrawInputText(CDC* pDC)
{
	//指定矩形内输出文字
	pDC->ExtTextOut(m_ptTextOrigin.x, m_ptTextOrigin.y, ETO_OPAQUE, m_rcTextBox, m_strInputText, NULL);
	//m_ptTextOrigin.x, m_ptTextOrigin.y, ETO_OPAQUE, m_rcTextBox, m_strMessages, NULL
}

void CMainWindow::ShowMessage(LPCTSTR pszMessage, UINT nChar, UINT nRepcnt, UINT nFlags)
{
	CString string;
	string.Format(_T("%s\t %u\t %u\t %u\t %u\t %u\t %u\t %u"), pszMessage, nChar, nRepcnt, nFlags & 0xFF,
		(nFlags >> 8) & 0x01, (nFlags >> 13) & 0x01, (nFlags >> 14) & 0x01, (nFlags >> 15) & 0x01);
	ScrollWindow(0, -m_cyLine, &m_rcScroll);
	ValidateRect(m_rcScroll);

	CClientDC dc(this);
	dc.SetBkColor((COLORREF)::GetSysColor(COLOR_3DFACE));

	m_strMessages[m_nMsgPos] = string;
	dc.TabbedTextOutW(m_ptLowerMsgOrigin.x, m_ptLowerMsgOrigin.y, m_strMessages[m_nMsgPos], m_strMessages[m_nMsgPos].GetLength(), sizeof(m_nTapStops), m_nTapStops, m_ptLowerMsgOrigin.x);
	if (++m_nMsgPos == MAX_STRINGS)
		m_nMsgPos = 0;
}

void CMainWindow::DrawMessageHeader(CDC* pDC)
{
	static CString string = _T("Message\tChar\tRep\tScan\tExt\tCon\tPrv\tTran");
	pDC->SetBkColor((COLORREF)::GetSysColor(COLOR_3DFACE));
	pDC->TabbedTextOut(m_ptHeaderOrigin.x, m_ptHeaderOrigin.y, string, string.GetLength(), sizeof(m_nTapStops), m_nTapStops, m_ptHeaderOrigin.x);
}

void CMainWindow::DrawMessage(CDC* pDC)
{
	
	int nPos=m_nMsgPos;
	pDC->SetBkColor((COLORREF)::GetSysColor(COLOR_3DFACE));
	for (int i=0;i<MAX_STRINGS;i++)
	{
		//调用此成员函数在指定位置写入字符串，将制表符扩展到制表符停止位置数组中指定的值。
		pDC->TabbedTextOut(m_ptUpperMsgOrigin.x, m_ptUpperMsgOrigin.y + (m_cyLine * i),
			m_strMessages[nPos], m_strMessages[nPos].GetLength(), sizeof(m_nTapStops), m_nTapStops, m_ptUpperMsgOrigin.x
		);
		if (++nPos == MAX_STRINGS)
			nPos = 0;
	}
	
}

void CMainWindow::PostNcDestroy()
{
	delete this;
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		//OnCreate must return 0 to continue the creation of the CWnd object. If the application returns –1, the window will be destroyed. 
		return -1;
	//初始成员变量
	CClientDC dc(this);
	
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight;
	m_cyLine = tm.tmInternalLeading + tm.tmHeight;
	
	m_rcTextBoxBorder.SetRect(16, 16, (m_cxChar * 64) + 16, ((m_cyChar * 3) / 2) + 16);
	m_rcTextBox = m_rcTextBoxBorder;
	//InflateRect将CRect的边从其中心移开，从而使其膨胀。
	m_rcTextBox.InflateRect(-2, -2);

	m_rcMsgBoxBorder.SetRect(16, (m_cyChar * 4) + 16, (m_cxChar * 64) + 16, (m_cyLine * MAX_STRINGS) + (m_cyChar * 6) + 16);
	m_rcScroll.SetRect(m_cxChar + 16, (m_cyChar * 6) + 16, (m_cxChar * 63) + 16, (m_cyLine * MAX_STRINGS) + (m_cyChar * 5) + 16);

	m_ptTextOrigin.x = m_cxChar + 16;
	m_ptTextOrigin.y = (m_cyChar / 4) + 16;

	m_ptCaretPos = m_ptTextOrigin;
	m_nTextLimit = (m_cxChar * 63) + 16;

	m_ptHeaderOrigin.x = m_cxChar + 16;
	m_ptHeaderOrigin.y = (m_cyChar * 3) + 16;

	m_ptUpperMsgOrigin.x = m_cxChar + 16;
	m_ptUpperMsgOrigin.y = (m_cyChar * 5) + 16;

	m_ptLowerMsgOrigin.x = m_cxChar + 16;
	m_ptLowerMsgOrigin.y = (m_cyChar * 5) + (m_cyLine * (MAX_STRINGS - 1)) + 16;

	m_nTapStops[0] = (m_cxChar * 24) + 16;
	m_nTapStops[1] = (m_cxChar * 30) + 16;
	m_nTapStops[2] = (m_cxChar * 36) + 16;
	m_nTapStops[3] = (m_cxChar * 42) + 16;
	m_nTapStops[4] = (m_cxChar * 46) + 16;
	m_nTapStops[5] = (m_cxChar * 50) + 16;
	m_nTapStops[6] = (m_cxChar * 54) + 16;

	//size the window
	CRect rect(0, 0, m_rcMsgBoxBorder.right + 16, m_rcMsgBoxBorder.bottom + 16);
	
	CalcWindowRect(&rect);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOMOVE | SWP_NOREDRAW);

		return 0;
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);

	dc.DrawEdge(m_rcTextBoxBorder, EDGE_SUNKEN, BF_RECT);
	dc.DrawEdge(m_rcMsgBoxBorder, EDGE_SUNKEN, BF_RECT);
	
	DrawInputText(&dc);
	 DrawMessageHeader(&dc);
	DrawMessage(&dc);
}

void CMainWindow::OnSetFocus(CWnd* pOldWnd)
{
	CreateSolidCaret(max(2, ::GetSystemMetrics(SM_CXBORDER)), m_cyChar);
	SetCaretPos(m_ptCaretPos);
	ShowCaret();
}

void CMainWindow::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret();
	m_ptCaretPos = GetCaretPos();
	::DestroyCaret();
}


//The framework calls this member function if mouse input is not captured and the mouse causes cursor movement within the CWnd object. 
BOOL CMainWindow::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest==HTCLIENT)
	{
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);
		::SetCursor(m_rcTextBox.PtInRect(point) ? m_hCursorBeam : m_hCursorArrow);
	}
	return TRUE;
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_rcTextBox.PtInRect(point))
	{
		m_nTextPos = GetNearestPos(point);
		PositionCaret();
	}
}

void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ShowMessage(_T("WM_KEYDOWN"), nChar, nRepCnt, nFlags);

	switch (nChar)
	{
	case VK_LEFT:
		if (m_nTextPos!=0)
		{
			m_nTextPos--;
			PositionCaret();
		}
		break;
	case VK_RIGHT:
		if (m_nTextPos!=m_strInputText.GetLength())
		{
			m_nTextPos++;
			PositionCaret();
		}
		break;
	case VK_HOME:
		m_nTextPos = 0;
		PositionCaret();
		break;
	case VK_END:
		m_nTextPos = m_strInputText.GetLength();
		PositionCaret();
		break;
	}
}

void CMainWindow::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ShowMessage(_T("WM_KEYUP"), nChar, nRepCnt, nFlags);
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMainWindow::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ShowMessage(_T("WM_SYSKEYDOWN"), nChar, nRepCnt, nFlags);
	CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CMainWindow::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ShowMessage(_T("WM_SYSKEYUP"), nChar, nRepCnt, nFlags);
	CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CMainWindow::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ShowMessage(_T("WM_CHAR"), nChar, nRepCnt, nFlags);
	CClientDC dc(this);

	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_RETURN:
		m_strInputText.Empty();
		m_nTextPos = 0;
		break;
	case VK_BACK:
		if (m_nTextPos!=0)
		{
			m_strInputText = m_strInputText.Left(m_nTextPos - 1) + m_strInputText.Right(m_strInputText.GetLength() - m_nTextPos);
			m_nTextPos--;
		}
		break;
	default:
		if ((nChar >= 0) && (nChar <= 31))
			return;
		if (m_nTextPos == m_strInputText.GetLength())
		{
			m_strInputText +=(CHAR)nChar;
			m_nTextPos++;
		}
		else
			m_strInputText.SetAt(m_nTextPos++, nChar);
		CSize size = dc.GetTextExtent(m_strInputText, m_strInputText.GetLength());
		if ((m_ptHeaderOrigin.x+size.cx)>m_nTextLimit)
		{
			m_strInputText = (CHAR)nChar;
			m_nTextPos = 1;
		}
		break;
	}
	HideCaret();
	DrawInputText(&dc);
	PositionCaret(&dc);
	ShowCaret();
}

void CMainWindow::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ShowMessage(_T("WM_SYSCHAR"), nChar, nRepCnt, nFlags);
	CWnd::OnSysChar(nChar, nRepCnt, nFlags);
}
