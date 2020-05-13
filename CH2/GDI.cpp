#include "GDI.h"

CMyApp myApp;
int OldDC;
BOOL CMyApp::InitInstance()
{
	
	m_pMainWnd = new CMainWindow;
	//m_pMainWnd->SetWindowTextW(_T("你猜猜"));
	
	//m_pMainWnd->DragAcceptFiles();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	
	
	return true;
}
POINT pt1, pt2;
CRect rect;
CMainWindow::CMainWindow()
{

	Create(NULL, _T("用GDI画图"), WS_OVERLAPPEDWINDOW);
	
}
void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;

	/*GetClientRect(&rect);
	dc.SelectStockObject(NULL_PEN);
	dc.SelectStockObject(LTGRAY_BRUSH);
	dc.Ellipse(&rect);*/
	CPen pen;
	pen.CreateStockObject(NULL_PEN);
	dc.SelectObject(pen);
	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);
	dc.SelectObject(brush);
	dc.Ellipse(0, 0, 100, 100);



	//CRect rect;
	//GetClientRect(&rect);

	//
	////font.CreatePointFont(720, _T("UBuntu Light"));

	//CPaintDC dc(this);
	//

	/////CString string = _T("Hello MFC ,Light");

	////rect.OffsetRect(16, 16);//矩形偏移一定方向
	////dc.SetTextColor(RGB(192, 192, 192));
	//
	//dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	//dc.SetBkMode(TRANSPARENT);
	//for (int i=0;i<3600;i+=150)
	//{
	//	CFont font;
	//	LOGFONT lf;
	//	::ZeroMemory(&lf, sizeof(lf));
	//	lf.lfHeight = 160;
	//	lf.lfWeight = FW_BOLD;
	//	lf.lfEscapement = i;
	//	lf.lfOrientation = i;
	//	::lstrcpy(lf.lfFaceName, _T("Arial"));
	//	font.CreatePointFontIndirect(&lf);

	//	CFont* fontOld = dc.SelectObject(&font);

	//	dc.TextOut(0, 0, CString(_T("Hello MFC")));
	//	dc.SelectObject(fontOld);
	//}
	//dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
	//dc.SetTextColor(RGB(0, 0, 0));
	//rect.OffsetRect(16, 16);
//dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}
/*
void CMainWindow::OnPaint()
{
	//CPaintDC dc(this);
	//CDC* pDC = CWnd::GetDC();

	PAINTSTRUCT ps;
	CPaintDC* pDC=(CPaintDC*)BeginPaint(&ps);
	
	
	GetClientRect(&rect);
	//dc.DrawText(_T("hello"), &rect, DT_CENTER);
	//pDC->DrawText(_T("hello"), &rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	
	CPen pPen(PS_DASHDOT, 2, RGB(255, 0, 255));
	HGDIOBJ hOldBrush, hOldPen;
	//hOldBrush=dc.SelectObject(pBrush);
	hOldPen = pDC->SelectObject(pPen);
	OldDC = pDC->SaveDC();

	pDC->SetTextColor(RGB( 255, 0,0));
	
	//pDC->SetBkMode(TRANSPARENT);
	//pDC->Rectangle(rect);
	//pDC->DrawText(L"Hello", &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	//pDC->MoveTo(-10, 0);
	//pDC->LineTo(1000, 10000);
	//ReleaseDC(pDC);
	//pDC->SetMapMode(MM_ANISOTROPIC);
	//pDC->Rectangle(100, -100, 450, -450);
	//pDC->SetWindowExt(1000, 1500);
	//pDC->SetViewportExt(rect.Width(), rect.Height());
	pDC->Rectangle(0, 0, 500, 500);
	pDC->Ellipse(0, 0, 500, 500);
	//pDC->SetBkMode(TRANSPARENT);
	//CFont cf;
	////cf.CreatePointFont(120, _T("Times New Roman"));
	//LOGFONT lf;
	//ZeroMemory(&lf, sizeof(lf));
	//lf.lfHeight = 120;
	//lf.lfWeight = FW_BOLD;
	//lf.lfItalic = TRUE;
	//::lstrcpy(lf.lfFaceName, TEXT("Times New Roman"));

	//cf.CreateFontIndirectW(&lf);
	//pDC->SelectObject(cf);
	//pDC->DrawText(TEXT("Hello MFC"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	////pDC->LPtoDP(&pt1);
	////pDC->LPtoDP(&pt2);

	EndPaint(&ps);
	
	//CDC* pDC1 = GetWindowDC();
	
	///ReleaseDC(pDC1);
}
*/
void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	//CBrush pBrush(RGB(255, 0, 255));
	//CPen pPen(PS_DASHDOT, 2, RGB(255, 0, 255));
	//HGDIOBJ hOldBrush, hOldPen;
	// dc.RestoreDC(OldDC);
	// dc.SetBkMode(TRANSPARENT);
	//hOldBrush=dc.SelectObject(pBrush);
	//hOldPen=dc.SelectObject(pPen);
	//dc.Ellipse(point.x - 100, point.y - 100, point.x + 100, point.y + 100);
	//delete(pBrush);
	//dc.Ellipse(100, 100, 1000, 1000);
	//dc.SelectObject(hOldBrush);
	//dc.SelectObject(hOldPen);
	//InvalidateRect(NULL, FALSE);
	

	//dc.DPtoLP(&point);
	//if ((point.x>0&&point.x<500)&& (point.y > 0 && point.y < 500))
	//{
	//	MessageBox(_T("在范围内"), NULL, MB_OK);
	//}
}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	//OnLButtonDown(nFlags, point);
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()
