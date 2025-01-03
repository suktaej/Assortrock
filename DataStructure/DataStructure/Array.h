#pragma once
#include <assert.h>

template <typename T>
class CArray
{
public:
	CArray() {}
	CArray(const CArray<T>& Arr) {}
	CArray(CArray<T>&& Arr) {}
	~CArray() 
	{
		if (mArray != nullptr)
			delete[] mArray;
	}

private:
	T* mArray = nullptr;
	int mSize = 0;
	int mCapacity = 0;
private:
	void ReAlloc(int NewCapacity = mCapacity * 2)
	{
		mCapacity = NewCapacity;
		T* Array = new T[mCapacity + 2];
		//Begin, End를 위한 공간 추가
		if (nullptr != mArray)
		{
			//Begin이 0번 공간에 할당되어 있으므로 +1번 공간만큼 복사
			memcpy(Array + 1, mArray + 1, sizeof(T) * mSize);
			delete[] mArray;
		}
		mArray = Array;
	}
public:
	void push_back(const T& Data)
	{
		if (mCapacity == mSize)
		{
			if (mCapacity == 0)
				ReAlloc(1);
			else
				ReAlloc();
		}
		mArray[mSize + 1] = Data;
		mSize++;
	}
};
