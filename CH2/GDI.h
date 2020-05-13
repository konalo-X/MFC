#pragma once
#include<afxwin.h>
#include<Windows.h>

class CMyApp :public CWinApp {
	virtual BOOL InitInstance();
};

class CMainWindow :public CFrameWnd
{
	
public:
	CMainWindow();
protected:
	afx_msg	void OnPaint();
	afx_msg void OnLButtonDown(
		UINT nFlags,
		CPoint point
	);
	afx_msg void OnMouseMove(
		UINT nFlags,
		CPoint point
	);


	DECLARE_MESSAGE_MAP()

};