#pragma once
#include<afxwin.h>
#define EX 1
#define OH 2
class CMyApp :public CWinApp
{
public:
	virtual BOOL InitInstance();
};
class CMainWindow :public CWnd
{
protected:
	//9个矩形
	static const CRect m_rcSquares[9];
	//矩形内容
	int m_nGameGrid[9];
	//下一个字符(EX 或OH
	int m_nNextChar;

	//获得方块ID
	int GetRectID(CPoint point);

	//画
	void DrawBoard(CDC* pDC);
	
	//画X
	void DrawX(CDC* pDC, int nPos);
	
	//画O
	void DrawO(CDC* pDC, int nPos);
	
	//reset
	void ResetGame();
	
	//检查是否结束
	void CheckforGameOver();

	//判断胜负
	int isWinner();

	//判断是否有画过
	BOOL IsDraw();

public:
	CMainWindow();
protected:
	virtual void PostNcDestory();

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP();
};

class TestDlg :public CFrameWnd
{
public:
	TestDlg();


};