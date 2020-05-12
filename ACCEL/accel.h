#pragma once
#include <afxwin.h>

#define  LINESIZE 8
class CMyApp :public CWinApp
{
	virtual BOOL InitInstance();
};

class CMainWnd :public CFrameWnd
{
public:
	CMainWnd();
protected:
	int m_nCellwidth=0;  //cell width in pixel
	int m_nCellHight = 0;
	int m_nRibbonWidth = 0;
	int m_nViewWidth = 0;
	int m_nViewHight = 0;

	int m_nHScrollpos = 0;
	int m_nVScrollpos = 0;
	int m_nHPageSize = 0;
	int m_nVPageSize = 0;


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlag, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP()
};