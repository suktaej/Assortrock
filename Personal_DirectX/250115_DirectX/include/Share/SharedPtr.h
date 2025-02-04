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

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	CSharedPtr(const CSharedPtr& Ptr)
	{
		mObj = Ptr.mObj;

		if (mObj)
			mObj->AddRef();
	}

	CSharedPtr(CSharedPtr&& Ptr)
	{
		mObj = Ptr.mObj;

		if (mObj)
			mObj->AddRef();
	}

	~CSharedPtr()
	{
		if (mObj)
			mObj->Release();
	}


public:
	void operator = (T* Obj)
	{
		//���� �����ڰ� ���� ��� ������
		if (mObj)
			mObj->Release();

		mObj = Obj;

		if (mObj)
			mObj->AddRef();
	}

	void operator = (const CSharedPtr& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		if (mObj)
			mObj->AddRef();
	}

	void operator = (CSharedPtr&& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

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

