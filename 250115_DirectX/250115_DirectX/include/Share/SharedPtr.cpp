#include "SharedPtr.h"
#include "Object.h"

CSharedPtr::CSharedPtr()
{
}

CSharedPtr::CSharedPtr(CObject* Obj)
{
	m_Obj = Obj;

	//오브젝트가 있을 경우 참조가 발생
	//참조 카운트를 증가
	if (m_Obj)
		m_Obj->AddRef();
}

CSharedPtr::CSharedPtr(CSharedPtr& Ptr)
{
	m_Obj = Ptr.m_Obj;

	if (m_Obj)
		m_Obj->AddRef();
}

CSharedPtr::CSharedPtr(CSharedPtr&& Ptr)
{
	m_Obj = Ptr.m_Obj;

	if (m_Obj)
		m_Obj->AddRef();
}

CSharedPtr::~CSharedPtr()
{
	//오브젝트가 있을 경우(!nullptr)
	//참조 카운트가 증가되었기 때문에 참조카운트 감소
	if (m_Obj)
		m_Obj->Release();
}

void CSharedPtr::operator=(CObject* Obj)
{
	m_Obj = Obj;
	if (m_Obj)
		m_Obj->AddRef();
}

void CSharedPtr::operator=(const CSharedPtr& Ptr)
{
	m_Obj = Ptr.m_Obj;
	if (m_Obj)
		m_Obj->AddRef();
}

void CSharedPtr::operator=(CSharedPtr&& Ptr)
{
	m_Obj = Ptr.m_Obj;
	if (m_Obj)
		m_Obj->AddRef();

}

bool CSharedPtr::operator==(CObject* Obj) const
{
	return m_Obj == Obj;
}

bool CSharedPtr::operator==(const CSharedPtr& Ptr) const
{
	return m_Obj == Ptr.m_Obj;
}

bool CSharedPtr::operator==(CSharedPtr&& Ptr) const
{
	return m_Obj == Ptr.m_Obj;
}

bool CSharedPtr::operator!=(CObject* Obj) const
{
	return m_Obj != Obj;
}

bool CSharedPtr::operator!=(const CSharedPtr& Ptr) const
{
	return m_Obj != Ptr.m_Obj;
}

bool CSharedPtr::operator!=(CSharedPtr&& Ptr) const
{
	return m_Obj != Ptr.m_Obj;
}

CObject* CSharedPtr::operator->() const
{
	return m_Obj;
}

CSharedPtr::operator class CObject* () const
{
	return m_Obj;
}

CObject* CSharedPtr::Get() const
{
	return m_Obj;
}


