#pragma once
#include "Array.h"

template<typename Key, typename Value>
class CNode
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;
	template <typename Key, typename Value>
	friend class CIterator;
public:
	CNode() {}
	~CNode() {}
private:
	CNode<Key, Value>* mParent = nullptr;
	CNode<Key, Value>* mLeft = nullptr;
	CNode<Key, Value>* mRight = nullptr;
	//tree의 경우 데이터의 반복 처리가 필요
	//node의 전후를 linked list로 구현
	CNode<Key, Value>* mNext = nullptr;
	CNode<Key, Value>* mPrev = nullptr;
public:
	Key mKey;
	Value mData;
	//탐색이진트리의 경우 값을 반환할 수 있어야 하므로 데이터는 공개
};

template<typename Key, typename Value>
class CIterator
{
	template<typename Key, typename Value>
	friend class CBinarySearchTree;
public:
	CIterator() {}
	~CIterator() {}
private:
	typedef CNode<Key, Value> NODE;
private:
	NODE* mNode = nullptr;
public:
	bool operator==(const CIterator<Key,Value>& iter)
	{
		return mNode == iter.mNode;
	}
	bool operator!=(const CIterator<Key,Value>& iter)
	{
		return mNode != iter.mNode;
	}
	const CIterator<Key, Value>& operator++()
	{
		mNode = mNode->mNext;
		return *this;
	}
	const CIterator<Key, Value>& operator++(int)
	{
		mNode = mNode->mNext;
		return *this;
	}
	const CIterator<Key, Value>& operator--()
	{
		mNode = mNode->mPrev;
		return *this;
	}
	const CIterator<Key, Value>& operator--(int)
	{
		mNode = mNode->mPrev;
		return *this;
	}
	const NODE* operator->() const
	{
		return mNode;
	}
};

//탐색 및 순회 가능
template<typename Key,typename Value>
class CBinarySearchTree
{
public:
	CBinarySearchTree() 
	{
		mBegin = new NODE;
		mEnd = new NODE;
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}
	~CBinarySearchTree() 
	{
		clear();
		delete mBegin;
		delete mEnd;
	}
private:
	typedef CNode<Key, Value> NODE;
public:
	typedef CIterator<Key, Value> ITR;
private:
	NODE* mRoot = nullptr;
	NODE* mBegin;
	NODE* mEnd;
	int mSize = 0;
private:
	void insert(const Key& pKey, const Value& Data, NODE* Node)
	{
		if (!Node)
			return;

		//인자의 key와 노드의 key를 비교해 좌우를 판단
		if (pKey < Node->mKey)
		{
			//왼쪽에 추가할 때, 왼쪽 노드가 없을 경우
			if(!Node->mLeft)
			{
				NODE* NewNode = new NODE;

				NewNode->mKey = pKey;
				NewNode->mData = Data;

				Node->mLeft = NewNode;
				NewNode->mParent = Node;

				NODE* Prev = Node->mPrev;

				Prev->mNext = NewNode;
				NewNode->mPrev = Prev;

				NewNode->mNext = Node;
				Node->mPrev = NewNode;
			}
			//왼쪽 노드가 존재할 경우
			else
			{
				insert(pKey, Data, Node->mLeft);
			}
		}
		//오른쪽 노드를 추가할 때
		else
		{
			if (!Node->mRight)
			{
				NODE* NewNode = new NODE;

				NewNode->mKey = pKey;
				NewNode->mData = Data;
				
				Node->mRight= NewNode;
				NewNode->mParent = Node;
				
				NODE* Next = Node->mNext;

				Next->mPrev = NewNode;
				NewNode->mPrev = Node;

				NewNode->mNext = Next;
				Node->mPrev = NewNode;
			}
			else
			{
				insert(pKey, Data, Node->mRight);
			}
		}
	}

	ITR find(const Key& pKey, NODE* Node) const
	{
		if (!Node)
			return end();

		if (pKey == Node->mKey)
		{
			ITR iter;
			iter.mNode = Node;
			return iter;
		}
		else if (pKey < Node->mKey)
			return find(pKey, Node->mLeft);
		else
			return find(pKey, Node->mRight);
	}

public:
	void insert(const Key& pKey, const Value& Data)
	{
		if (!mRoot)
		{
			mRoot = new NODE;
			mRoot->mKey = pKey;
			mRoot->mData = Data;

			mBegin->mNext = mRoot;
			mRoot->mPrev = mBegin;

			mRoot->mNext = mEnd;
			mEnd->mPrev = mRoot;
		}
		else
		{
			insert(pKey, Data, mRoot);
		}
		mSize++;
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }

	void clear()
	{
		NODE* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			NODE* Next = Node->mNext;
			delete Node;
			Node = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	ITR begin() const
	{
		ITR iter;
		iter.mNode = mBegin->mNext;
		return iter;
	}

	ITR end() const
	{
		ITR iter;
		iter.mNode = mEnd;
		return iter;
	}

	ITR find(const Key& pKey) const
	{
		return find(pKey, mRoot);
	}

};
