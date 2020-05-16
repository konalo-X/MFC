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
	int m_cxChar;//�ַ�ƽ�����
	int m_cyChar;//�ַ��߶�
	int m_cyLine;//message box �߶�
	int m_nTextPos;//text box ��ǰ�ַ�����
	int m_nTapStops[7];//������λ��tap stop 
	int m_nTextLimit;//text box �ַ������
	int m_nMsgPos;// ������m_strMessages ��ǰλ��

	HCURSOR m_hCursorArrow;  //��ͷ�����
	HCURSOR m_hCursorBeam; //���ܹ����

	CPoint m_ptTextOrigin;//����text�����
	CPoint m_ptHeaderOrigin;//???
	CPoint m_ptUpperMsgOrigin;//messagebox ��һ�����
	CPoint m_ptLowerMsgOrigin;//���һ�����
	CPoint m_ptCaretPos;//��ǰ���λ��

	CRect m_rcTextBox;// of text box ����(coordinates)
	CRect m_rcTextBoxBorder;//�ı���߿�
	CRect m_rcMsgBoxBorder;// ��Ϣ��߿�
	CRect m_rcScroll;//������������

	CString m_strInputText;//input text
	CString m_strMessages[MAX_STRINGS]; //message  string ����
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