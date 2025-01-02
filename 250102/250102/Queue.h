#pragma once
#include <assert.h>

template<typename T>
class CQueueNode
{
	template<typename T>
	friend class CQueue;
public:
	CQueueNode() {};
	~CQueueNode() {};
private:
	T mData;
	CQueueNode<T>* mNext = nullptr;
};

template <typename T>
class CQueue
{
public:
	CQueue() {}
	~CQueue() { clear(); }
private:
	CQueueNode<T>* mFirst = nullptr;
	CQueueNode<T>* mLast= nullptr;
	int mSize = 0;
public:
	void push(const T& Data)
	{
		CQueueNode<T>* Node = new CQueueNode<T>;
		Node->mData = Data;

		if (!mFirst)
			mFirst = Node;
		else
			mLast->mNext = Node;

		mLast = Node;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		CQueueNode<T>* Next = mFirst->mNext;
		T Data = mFirst->mData;

		delete mFirst;
		mFirst = Next;

		--mSize;

		if (mSize == 0)
			mLast = nullptr;

		return Data;
	}

	void clear()
	{
		while (mFirst)
		{
			CQueueNode<T>* Next = mFirst->mNext;
			delete mFirst;
			mFirst = Next;
		}
		mSize = 0;
		mLast = nullptr;
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }
};


template <typename T,int Count = 100>
class CCircleQueue
{
public:
	CCircleQueue() {}
	~CCircleQueue() {}
private:
	T mArray[Count] = {};
	int mSize = 0;
	int mHead = 0;	//pop
	int mTail = 0;	//push
public:
	void push(const T& Data)
	{
		assert(mSize != Count);

		mArray[mTail] = Data;
		mTail = (mTail + 1) % Count;
		//배열의 위치를 증가시키다가 배열의 크기와 값이 동일할 경우
		//처음 인덱스[0]으로 순환
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		T Data = mArray[mHead];
		mHead = (mHead + 1) % Count;

		--mSize;

		return Data;
	}
	
	int size() { return mSize; }
	bool empty() { return mSize == 0; }
	bool clear()
	{
		mSize = 0;
		mHead = 0;
		mTail = 0;
	}
};

