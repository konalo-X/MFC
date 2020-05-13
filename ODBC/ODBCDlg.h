
// ODBCDlg.h: 头文件
//

#pragma once


// CODBCDlg 对话框
class CODBCDlg : public CDialogEx
{
// 构造
public:
	CODBCDlg(CWnd* pParent = nullptr);	// 标准构造函数
public:
	CDatabase m_db;    //数据库
	CRecordset* m_rs;   //记录集指针
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ODBC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void CODBCDlg::ListStuInfo(CString strSQL);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	CListCtrl m_listctrl;
	int m_count;

};


