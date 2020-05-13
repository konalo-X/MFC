#include"MouseCap.h"

CMyApp myapp;

BOOL CMyApp::InitInstance()
{
    m_pMainWnd=new CMainWindow();
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

//反转线条

void CMainWindow::InvertLine(CDC* pDC, CPoint ptFrom, CPoint ptTo)
{
    int nOldMode = pDC->SetROP2(R2_NOT);
    CPen pen(PS_DASH, 1, RGB(255, 0, 0));
    HGDIOBJ oldPen =pDC->SelectObject(pen);
    pDC->MoveTo(ptFrom);
    pDC->LineTo(ptTo);
    pDC->SelectObject(oldPen);
    pDC->SetROP2(nOldMode);
}



CMainWindow::CMainWindow()
{
	m_bTracking = FALSE;
	m_bCaptureEnabled = TRUE;
    CString wndclass = AfxRegisterWndClass(
		NULL, 
		AfxGetApp()->LoadStandardCursor(IDC_CROSS),
		(HBRUSH)GetStockObject(WHITE_BRUSH), 
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));
    Create(wndclass,_T("Mouse Capture Demo(capture Enabled)"));
}

void CMainWindow::OnLButtonDown(UINT nFlags,CPoint point)
{
    if(m_bCaptureEnabled)
        SetCapture();

    m_bTracking = TRUE;
    m_ptFrom = point;
    m_ptTo = point;
   

}

void CMainWindow::OnLButtonUp(UINT nFlags,CPoint point)
{
    

  
    if (m_bTracking)
    {
        m_bTracking = FALSE;
        if(GetCapture()==this)
            ::ReleaseCapture();
    }
	CClientDC dc(this);

	InvertLine(&dc, m_ptFrom, point);

	CPen RedPen(PS_SOLID, 16, RGB(255, 0, 0));
	HGDIOBJ OldPen = dc.SelectObject(RedPen);

	dc.MoveTo(m_ptFrom);
	dc.LineTo(point);
    dc.SelectObject(OldPen);
}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
    CClientDC dc(this);
    //CPoint ptTmp(point);
    if (m_bTracking)
    {
        dc.SetBkMode(TRANSPARENT);
        
        InvertLine(&dc, m_ptFrom, m_ptTo);
        InvertLine(&dc, m_ptFrom, point);
        m_ptTo = point;
        
    }
}

void CMainWindow::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    if (nHitTest == HTCAPTION)
    {
       m_bCaptureEnabled = m_bCaptureEnabled ? FALSE : TRUE;
       SetWindowText( m_bCaptureEnabled ? _T("Mouse Capture Demo(capture Enabled)"):_T("Mouse Capture Demo(capture Disabled)"));
    }
    CFrameWnd::OnNcLButtonDown(nHitTest, point);
    
}

///Message Map
BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()