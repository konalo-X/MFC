#pragma once
#include<iostream>
#include<afxwin.h>

class CMainWindow : public  CFrameWnd
{
public:
	CMainWindow();
protected:
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT, CPoint);
	DECLARE_MESSAGE_MAP()
};

class CMyApp :public CWinApp
{
public:
	virtual BOOL InitInstance();
};

