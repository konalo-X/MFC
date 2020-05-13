#pragma once
#include <afxwin.h>
class CMyapp :public CWinApp
{
	virtual BOOL InitInstance();

};

class CMainWindow :public CFrameWnd
{
public:
	CMainWindow();
protected:
	int m_nViewWidth;// work space in inch
	

	int m_nHScrollPos;//scrollbar position

	int m_nHPageSize;//horizontal page size

protected:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

};