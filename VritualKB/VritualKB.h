#pragma once
#include <afxwin.h>
#define  MAX_STRINGS 12
class CMyApp :public CWinApp
{
	virtual BOOL InitInstance();
};

class CMainWindow :public CWnd
{
protected:
	int m_cxChar;//字符平均宽度
	int m_cyChar;//字符高度
	int m_cyLine;//message box 高度
	int m_nTextPos;//text box 当前字符索引
	int m_nTapStops[7];//表格输出位置tap stop 
	int m_nTextLimit;//text box 字符最大宽度
	int m_nMsgPos;// 数组中m_strMessages 当前位置

	HCURSOR m_hCursorArrow;  //箭头鼠标句柄
	HCURSOR m_hCursorBeam; //竖杠光标句柄

	CPoint m_ptTextOrigin;//输入text的起点
	CPoint m_ptHeaderOrigin;//???
	CPoint m_ptUpperMsgOrigin;//messagebox 第一行起点
	CPoint m_ptLowerMsgOrigin;//最后一行起点
	CPoint m_ptCaretPos;//当前光标位置

	CRect m_rcTextBox;// of text box 坐标(coordinates)
	CRect m_rcTextBoxBorder;//文本框边框
	CRect m_rcMsgBoxBorder;// 消息框边框
	CRect m_rcScroll;//滚动矩形坐标

	CString m_strInputText;//input text
	CString m_strMessages[MAX_STRINGS]; //message  string 数组
public:
	CMainWindow();
protected:
	int GetNearestPos(CPoint point);
	void PositionCaret(CDC* pDC = NULL);
	void DrawInputText(CDC* pDC);
	void ShowMessage(LPCTSTR pszMessage, UINT nChar, UINT nRepcnt, UINT nFlags);
	void DrawMessageHeader(CDC* pDC);
	void DrawMessage(CDC* pDC);

protected:
	virtual void PostNcDestroy();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};