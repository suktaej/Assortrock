#pragma once

template <typename T>
class CSharedPtr
{
public:
	CSharedPtr()
	{
	}

	CSharedPtr(T* Obj)
	{
		mObj = Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (mObj)
			mObj->AddRef();
	}

	CSharedPtr(const CSharedPtr& Ptr)
	{
		mObj = Ptr.mObj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (mObj)
			mObj->AddRef();
	}

	CSharedPtr(CSharedPtr&& Ptr)
	{
		mObj = Ptr.mObj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (mObj)
			mObj->AddRef();
	}

	~CSharedPtr()
	{
		// 오브젝트가 있을 경우 참조카운트가 증가되었기 때문에 참조카운트를 감소시킨다.
		if (mObj)
			mObj->Release();
	}


public:
	void operator = (T* Obj)
	{
		if (mObj)
			mObj->Release();

		mObj = Obj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (mObj)
			mObj->AddRef();
	}

	void operator = (const CSharedPtr& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (mObj)
			mObj->AddRef();
	}

	void operator = (CSharedPtr&& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		// 오브젝트가 있을 경우 참조가 일어나는 것이기 때문에 참조 카운트를 1 증가시킨다.
		if (mObj)
			mObj->AddRef();
	}

	bool operator == (T* Obj)	const
	{
		return mObj == Obj;
	}

	bool operator == (const CSharedPtr& Ptr)	const
	{
		return mObj == Ptr.mObj;
	}

	bool operator == (CSharedPtr&& Ptr)	const
	{
		return mObj == Ptr.mObj;
	}

	bool operator != (T* Obj)	const
	{
		return mObj != Obj;
	}

	bool operator != (const CSharedPtr& Ptr)	const
	{
		return mObj != Ptr.mObj;
	}

	bool operator != (CSharedPtr&& Ptr)	const
	{
		return mObj != Ptr.mObj;
	}

	T* operator -> ()	const
	{
		return mObj;
	}

	operator T* ()	const
	{
		return mObj;
	}

	T* Get()	const
	{
		return mObj;
	}

private:
	T* mObj = nullptr;
};

