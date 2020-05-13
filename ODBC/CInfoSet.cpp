#include "pch.h"
#include "CInfoSet.h"

///CInfoSet::CInfoSet(CDatabase* pDatabase) :CRecordset(pDatabase)
CInfoSet::CInfoSet()
{
	m_sno = L"";
	m_sname = L"";
	m_dept = L"";
	m_comment = L"";
	m_nFields = 4;

}

CString CInfoSet::GetDefaultConnect()
{
	return _T("DSN=stu;");
}

CString CInfoSet::GetDefaultSQL()
{
	return _T("[stu]");
}

void CInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[sno]"), m_sno);
	RFX_Text(pFX, _T("[sname]"), m_sname);
	RFX_Text(pFX, _T("[dept]"), m_dept);
	RFX_Text(pFX, _T("[comment]"), m_comment);


}
