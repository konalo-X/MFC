#pragma once
#include "pch.h"
class CInfoSet :public CRecordset
{
	public:
	CString m_sno;
	CString m_sname;
	CString m_dept;
	CString m_comment;                          //��long intתΪCString
public:
	//CInfoSet(CDatabase* pDatabase = NULL);
	CInfoSet();
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���
	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

};
