#pragma once
#include "pch.h"
class CInfoSet :public CRecordset
{
	public:
	CString m_sno;
	CString m_sname;
	CString m_dept;
	CString m_comment;                          //将long int转为CString
public:
	//CInfoSet(CDatabase* pDatabase = NULL);
	CInfoSet();
	virtual CString GetDefaultConnect();	// 默认连接字符串
	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

};
