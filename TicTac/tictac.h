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
	//9������
	static const CRect m_rcSquares[9];
	//��������
	int m_nGameGrid[9];
	//��һ���ַ�(EX ��OH
	int m_nNextChar;

	//��÷���ID
	int GetRectID(CPoint point);

	//��
	void DrawBoard(CDC* pDC);
	
	//��X
	void DrawX(CDC* pDC, int nPos);
	
	//��O
	void DrawO(CDC* pDC, int nPos);
	
	//reset
	void ResetGame();
	
	//����Ƿ����
	void CheckforGameOver();

	//�ж�ʤ��
	int isWinner();

	//�ж��Ƿ��л���
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