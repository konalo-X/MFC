#include<afxwin.h>
#include<tchar.h>
#include"hello.h"
#include<math.h>
#define SEGMENTS 500
#define PI 3.1415926
CMyApp myApp;
BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	 
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

/////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	Create(NULL, _T("The Hello Application!"));
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	
	dc.DrawText(_T("Hello,MFC"), -1, &rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	//int nWidth = rect.Width();
	//int nHight = rect.Height();
	//画直线
	//dc.MoveTo(0, 0);
	//dc.LineTo(100, 100);

/*
	画正弦曲线
	CPoint Apoint[SEGMENTS];

	for (int i = 0; i < SEGMENTS; i++)
	{
		Apoint[i].x = (i * nWidth) / SEGMENTS;
		Apoint[i].y = (int)((nHight / 2) *
			(1 - (sin((2 * PI * i) / SEGMENTS))));
		
	}
		dc.Polyline(Apoint, SEGMENTS);
*/

}

void CMainWindow::OnRButtonDown(UINT nFlags , CPoint point)
{
	TCHAR szMsg[256];
	GetWindowText(szMsg, sizeof(szMsg) / sizeof(TCHAR));
	_tcscat_s(szMsg, _T("1"));
	if (nFlags == MK_RBUTTON)
		::MessageBox(NULL,szMsg, _T("Hello,MFC"),MB_OK);
		
}
