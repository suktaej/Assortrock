#pragma once
#include <assert.h>

template <typename T>
class CStackDynamicArray
{
public:
	CStackDynamicArray()
	{

	}
	~CStackDynamicArray()
	{
		if (mArray)
			delete[] mArray;
	}
private:
	T *mArray = nullptr;
	int mSize = 0;
	int mCapacity = 0;
private:
	void ReAlloc(int NewCapacity = mCapacity*2)
	{
		mCapacity = NewCapacity;

		T* Temp = new T[mCapacity];
		if (nullptr != mArray)
			memcpy(Temp, mArray, sizeof(T) * mSize);

		delete[] mArray;
		mArray = Temp;
	}
public:
	void push(const T& Data)
	{
		if (mSize == 0)
			ReAlloc(1);
		else if(mSize==mCapacity)
			ReAlloc(mCapacity * 2);

		mArray[mSize] = Data;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);
		//크기가 0일 경우, 오류출력

		--mSize;
		return mArray[mSize];
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }
	int capacity() const { return mCapacity; }
	void clear() { mSize = 0; }

};

template <typename T,int Count = 100>
//비타입 템플릿 인자는 상수 취급
class CStackStaticArray
{
public:
	CStackStaticArray()
	{

	}
	~CStackStaticArray()
	{

	}
private:
	T mArray[Count] = {};
	int mSize = 0;
public:
	void push(const T& Data)
	{
		assert(mSize != Count);

		mArray[mSize] = Data;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		mSize--;
		return mArray[mSize];
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }
	void clear() { mSize = 0; }
};

template<typename T>
class CStackNode
{
	template<typename T>
	friend class CStackList;
private:
	CStackNode()
	{

	}
	~CStackNode()
	{

	}
private:
	T mData;
	CStackNode<T>* mNext = nullptr;
};

template<typename T>
class CStackList
{
public:
	CStackList() {}
	~CStackList() { clear(); }

private:
	CStackNode<T>& mEnd = nullptr;
	int mSize = 0;
public:
	void push(const T& Data)
	{
		CStackNode<T>* Node = new CStackNode<T>;
		Node->mData = Data;
		Node->mNext = mEnd;
		mEnd = Node;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		CStackNode<T>* NextNode = mEnd->mNext;
		T Data = mEnd->mData;

		delete mEnd;
		mEnd = NextNode;
		--mSize;

		return Data;
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }
	void clear() 
	{
		while (mEnd)
		{
			CStackNode<T>* Next = mEnd->mNext;
			delete mEnd;
			mEnd = Next;
		}
		mSize = 0;
	}
};


