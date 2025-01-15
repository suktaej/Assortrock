#include "SharedPtr.h"
#include "Object.h"

CSharedPtr::CSharedPtr()
{
}

CSharedPtr::CSharedPtr(CObject* Obj)
{
	m_Obj = Obj;

	//������Ʈ�� ���� ��� ������ �߻�
	//���� ī��Ʈ�� ����
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
	//������Ʈ�� ���� ���(!nullptr)
	//���� ī��Ʈ�� �����Ǿ��� ������ ����ī��Ʈ ����
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


