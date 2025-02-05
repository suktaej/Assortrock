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

	CSharedPtr(const CSharedPtr<T>& Ptr)
	{
		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	CSharedPtr(CSharedPtr<T>&& Ptr)
	{
		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	~CSharedPtr()
	{
		// ������Ʈ�� ���� ��� ����ī��Ʈ�� �����Ǿ��� ������ ����ī��Ʈ�� ���ҽ�Ų��.
		if (mObj)
			mObj->Release();
	}


public:
	void operator = (T* Obj)
	{
		if (mObj)
			mObj->Release();

		mObj = Obj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	void operator = (const CSharedPtr<T>& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	void operator = (CSharedPtr<T>&& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	bool operator == (T* Obj)	const
	{
		return mObj == Obj;
	}

	bool operator == (const CSharedPtr<T>& Ptr)	const
	{
		return mObj == Ptr.mObj;
	}

	bool operator == (CSharedPtr<T>&& Ptr)	const
	{
		return mObj == Ptr.mObj;
	}

	bool operator != (T* Obj)	const
	{
		return mObj != Obj;
	}

	bool operator != (const CSharedPtr<T>& Ptr)	const
	{
		return mObj != Ptr.mObj;
	}

	bool operator != (CSharedPtr<T>&& Ptr)	const
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

