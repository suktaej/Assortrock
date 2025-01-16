#pragma once

template <typename T>
class CSharedPtr
{
private:
	T* m_Obj = nullptr;

public:
	CSharedPtr()
	{
	}

	CSharedPtr(T* Obj)
	{
		m_Obj = Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (m_Obj)
			m_Obj->AddRef();
	}

	CSharedPtr(const CSharedPtr& Ptr)
	{
		m_Obj = Ptr.m_Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (m_Obj)
			m_Obj->AddRef();
	}

	CSharedPtr(CSharedPtr&& Ptr)
	{
		m_Obj = Ptr.m_Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (m_Obj)
			m_Obj->AddRef();
	}

	~CSharedPtr()
	{
		// 오브젝트가 있을 경우 참조카운트가 증가되었기 때문에 참조카운트를 감소시킨다.
		if (m_Obj)
			m_Obj->Release();
	}


public:
	void operator = (T* Obj)
	{
		if (m_Obj)
			m_Obj->Release();

		m_Obj = Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (m_Obj)
			m_Obj->AddRef();
	}

	void operator = (const CSharedPtr& Ptr)
	{
		if (m_Obj)
			m_Obj->Release();

		m_Obj = Ptr.m_Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (m_Obj)
			m_Obj->AddRef();
	}

	void operator = (CSharedPtr&& Ptr)
	{
		if (m_Obj)
			m_Obj->Release();

		m_Obj = Ptr.m_Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (m_Obj)
			m_Obj->AddRef();
	}

	bool operator == (T* Obj)	const
	{
		return m_Obj == Obj;
	}

	bool operator == (const CSharedPtr& Ptr)	const
	{
		return m_Obj == Ptr.m_Obj;
	}

	bool operator == (CSharedPtr&& Ptr)	const
	{
		return m_Obj == Ptr.m_Obj;
	}

	bool operator != (T* Obj)	const
	{
		return m_Obj != Obj;
	}

	bool operator != (const CSharedPtr& Ptr)	const
	{
		return m_Obj != Ptr.m_Obj;
	}

	bool operator != (CSharedPtr&& Ptr)	const
	{
		return m_Obj != Ptr.m_Obj;
	}

	T* operator -> ()	const
	{
		return m_Obj;
	}

	operator T* ()	const
	{
		return m_Obj;
	}

	T* Get()	const
	{
		return m_Obj;
	}
};

