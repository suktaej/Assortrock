#pragma once
#include <assert.h>

template<typename T>
class CNode
{
	template<typename T>
	friend class CLinkedList;
	template<typename T>
	frined class CIterator;
public:
	CNode() {};
	~CNode() {};
private:
	T mData;
	CNode<T>* mNext = nullptr;
	CNode<T>* mPrev = nullptr;
};

template<typename T>
class CIterator
{
	template<typename T>
	friend class CLinkedList;
public:
	CIterator() {}
	~CIterator() {}
private:
	CNode<T>* mNode = nullptr;
public:
	bool operator==(const CIterator<T>& iter) const
	{
		return mNode == iter.mNode;
	}
	bool operator!=(const CIterator<T>& iter) const
	{
		return mNode != iter.mNode;
	}
	const CIterator<T>& operator++()
	{
		mNode = mNode->mNext;
		
		assert(mNode != nullptr);
		return this*;
	}
	const CIterator<T>& operator++(int)
	{
		mNode = mNode->mNext;
		
		assert(mNode != nullptr);
		return this*;
	}
	const CIterator<T>& operator -- ()
	{
		mNode = mNode->mPrev;
		assert(mNode != nullptr);

		return *this;
	}
	const CIterator<T>& operator -- (int)
	{
		mNode = mNode->mPrev;
		assert(mNode != nullptr);

		return *this;
	}
	T& operator*()
	{
		assert(mNode != nullptr);
		return mNode->mData;
	}

};

template<typename T>
class CLinkedList
{
public:
	CLinkedList() 
	{
		mBegin = new Node;
		mEnd = new Node;
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}
	~CLinkedList() 
	{
		clear();
		delete mBegin;
		delete mEnd;
	}
private:
	typedef CNode<T> NODE;
	typedef CIterator<T> iterator;
private:
	int mCount = 0;
	CNode<T>* mBegin = nullptr;
	CNode<T>* mEnd = nullptr;
public:
	void push_back(const T& Data)
	{
		CNode<T>* Node = new CNode;

		Node->mData = Data;

		CNode<T>* BeforeEnd = mEnd->mPrev;
		
		Node->mPrev = BeforeEnd;
		Node->mNext = mEnd;

		BeforeEnd->mNext = Node;

		mEnd->mPrev = Node;

		mSize++;
	}
	void push_front(const T& Data)
	{
		CNode<T>* Node = new CNode;

		Node->mData = Data;

		CNode<T>* AfterBegin = mBegin->mNext;

		Node->mNext = AfterBegin;
		Node->mPrev = mBegin;

		AfterBegin->mPrev = Node;
		mBegin->mNext = Node;

		mSize++;
	}

	void pop_back()
	{
		assert(mSize != 0);

		CNode<T>* Node = mEnd->mPrev;

		mEnd->mPrev = Node->mPrev;
		Node->mPrev->mNext = mEnd;

		delete Node;
		mSize--;
	}

	void pop_front()
	{
		assert(mSize != 0);

		CNode<T>* Node = mBegin->mNext;
	
		mBegin->mNext = Node->mNext;
		Node->mNext->mPrev = mBegin;

		delete Node;
		mSize--;
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }

	void clear()
	{
		CNode<T>* Node = mBeign->mNext;
		while (!mEnd)
		{
			CNode<T>* Next = Node->mNext;
			delete Node;
			Node = Next;
		}
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	iterator begin() const
	{
		iterator iter;
		iter.mNode = mBegin->mNext;

		return iter;
	}

	iterator end() const
	{
		iterator iter;
		iter.mNode = mEnd;

		return iter;
	}

	void insert(const iterator& iter, const T& Data)
	{
		NODE* Node = new NODE;
		Node->mData = Data;

		NODE* Prev = iter.mNode->mPrev;

		Node->mPrev = Prev;
		Node->mNext = iter.mNode;

		Prev->mNext = Node;
		iter.mNode->mPrev = Node;

		mSize++;
	}

	iterator erase(const iterator& iter)
	{
		if (!mSize)
			return end();
		
		NODE* Prev = iter.mNode->mPrev;
		NODE* Next = iter.mNode->mNext;

		delete iter.mNode;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		mSize--;

		iterator result;
		result.mNode = Next;
		return result;
	}
};

