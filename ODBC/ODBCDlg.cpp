
// ODBCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ODBC.h"
#include "ODBCDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "CInfoSet.h"
#include<afxcmn.h >
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CODBCDlg 对话框



CODBCDlg::CODBCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ODBC_DIALOG, pParent)
	, m_count(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//if (m_db.Open(_T("stu"), FALSE, FALSE, L"ODBC;"))
	//{
	//	AfxMessageBox(L"未打开数据库");
	//}
	//else
	//{
	//	m_rs = new CRecordset(&m_db);   //记录集指针
	//	m_rs->Open(CRecordset::snapshot, L"SELECT `sno`,`sname`,`dept`,`comment`,  FROM `student`");  //注意：这里的sql语句不能直接写表名(虽然帮助文档说可以，或许还需要其他代码)
	//	if (!m_rs->IsOpen())
	//	{
	//		AfxMessageBox(L"数据集创建失败");
	//	}


	//}
}
void CODBCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Control(pDX, IDC_EDIT1, (CWnd&)m_count);
}
BEGIN_MESSAGE_MAP(CODBCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CODBCDlg::OnLbnSelchangeList1)

END_MESSAGE_MAP()


// CODBCDlg 消息处理程序

BOOL CODBCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_listctrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//设置列表视图控件为网格状风格，且为全选状态(鼠标点击某一行表现为全选状态)    
	m_listctrl.InsertColumn(0, TEXT("学号"), LVCFMT_LEFT, 110,-1);//参数分别为字段索引，字段名，对齐方式，像素(每个字段宽度)
	m_listctrl.InsertColumn(1, TEXT("姓名"), LVCFMT_LEFT, 100, -1);
	m_listctrl.InsertColumn(2, TEXT("系别"), LVCFMT_LEFT, 120, -1);
	m_listctrl.InsertColumn(3, TEXT("评语"), LVCFMT_LEFT, 100, -1);
	CString SQL = TEXT("SELECT * FROM stu");          //可以通过更改表名达到列出同一数据源中不同表的目的
	ListStuInfo(SQL);                               //列出指定表中所有信息
	SetTimer(1, 1, NULL);//计时器
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CODBCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CODBCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CODBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CODBCDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CODBCDlg::ListStuInfo(CString strSQL)
{
	m_listctrl.DeleteAllItems();                                      //首先删除所有项目
	CInfoSet Infoset;                                                 //创建一个记录集对象
	if (!Infoset.Open(CRecordset::dynaset, strSQL, CRecordset::readOnly))//连接数据源并执行给定的SQL语句
	{
		MessageBox(L"连接数据源失败!",L"警告", MB_ICONASTERISK | MB_OK);
		return;
	}
	CString strTemp;
	int i = 0;
	while (!Infoset.IsEOF())
	{
		m_listctrl.InsertItem(i, Infoset.m_sno);
		m_listctrl.SetItemText(i, 1, Infoset.m_sname);
		m_listctrl.SetItemText(i, 2, Infoset.m_dept);
	
		m_listctrl.SetItemText(i, 3, Infoset.m_comment);
		
		Infoset.MoveNext();
		i++;
	}
	m_count = i;
	CString string;
	string.Format(TEXT("%d"), m_count);
	HWND hEdit=::GetDlgItem(*AfxGetApp()->m_pMainWnd, IDC_EDIT1);
	::AfxSetWindowText(hEdit, string);

	Infoset.Close();                                                   //关闭记录集
	UpdateData(FALSE);                                                 //将控件变量值传给对应控件显示
}




//
//InsertDlg::InsertDlg()
//{
//	OnInitDialog();
//	Create(IDD_PROPPAGE_MEDIUM);
//}
//BEGIN_MESSAGE_MAP(InsertDlg, CDialogEx)
//
//	ON_BN_CLICKED(IDC_BUTTON1, &InsertDlg::OnBnClickedAdd)
//END_MESSAGE_MAP()

