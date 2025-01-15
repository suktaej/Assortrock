#pragma once
#include "../GameInfo.h"

class CSharedPtr
{
public:
	CSharedPtr();
	CSharedPtr(class CObject* Obj);
	CSharedPtr(class CSharedPtr& Ptr);
	CSharedPtr(CSharedPtr&& Ptr);
	~CSharedPtr();
private:
	class CObject* m_Obj = nullptr;
public:
	void operator=(class CObject* Obj);
	void operator=(const CSharedPtr& Ptr);
	void operator=(CSharedPtr&& Ptr);

	bool operator==(class CObject* Obj) const;
	bool operator==(const CSharedPtr& Ptr) const;
	bool operator==(CSharedPtr&& Ptr) const;
	
	bool operator!=(class CObject* Obj) const;
	bool operator!=(const CSharedPtr& Ptr) const;
	bool operator!=(CSharedPtr&& Ptr) const;
	
	class CObject* operator->() const;
	operator class CObject* () const;
	CObject* Get() const;
}


