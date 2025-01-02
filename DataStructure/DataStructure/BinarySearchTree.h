#pragma once

template<typename Key, typename Value>
class CNode
{
	template<typename Key, typename Value>
	friend class CBinarySearchTree;
	template<typename Key, typename Value>
	friend class CIterator;
private:
	CNode() {}
	~CNode() {}
private:
	typedef CNode<Key, Value> NODE;
public:
	Key mKey;
	Value mData;
private:
	NODE* mParent = nullptr;
	NODE* mLeft = nullptr;
	NODE* mRight = nullptr;
	NODE* mNext = nullptr;
	NODE* mPrev = nullptr;
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
	typedef CIterator<Key, Value> ITR;
	typedef CNode<Key, Value> NODE;
private:
	NODE* mNode = nullptr;
public:
	bool operator==(const ITR& iter)
	{
		return iter.mNode == mNode;
	}
	bool operator!=(const ITR& iter)
	{
		return iter.mNode != mNode;
	}
	const ITR& operator++()
	{
		mNode = mNode->mNext;
		return *this;
	}
	const ITR& operator++(int)
	{
		mNode = mNode->mNext;
		return *this;
	}
	const ITR& operator--()
	{
		mNode = mNode->mPrev;
		return *this;
	}
	const ITR& operator--(int)
	{
		mNode = mNode->mPrev;
		return *this;
	}
	const NODE* operator->() const
	{
		return mNode;
	}
};


template<typename Key, typename Value>
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
	~CBinarySearchTree() {}
private:
	typedef CBinarySearchTree<Key, Value> CBT;
	typedef CNode<Key, Value> NODE;
public:
	typedef CIterator<Key, Value> ITR;
private:
	NODE* mRoot = nullptr;
	NODE* mBegin = nullptr;
	NODE* mEnd = nullptr;
	int mSize = 0;
private:
	void insert(const Key& pKey, const Value& Data, NODE* Node)
	{
		if (!Node)
			return;

		//값이 작을 때(좌측노드 추가)
		if (pKey < Node->mKey)
		{
			// 좌측에 노드가 없을 경우
			if (!Node->mLeft)
			{
				NODE* NewNode = new NODE;

				NewNode->mData = Data;
				NewNode->mKey = pKey;
				NewNode->mParent = Node;

				Node->mLeft = NewNode;
				//Tree 생성

				NODE* Prev = Node->mPrev;

				Prev->mNext = NewNode;
				NewNode->mPrev = Prev;

				NewNode->mNext = Node;
				Node->mPrev = NewNode;
				//Linkedlist 생성
			}
			// 좌측에 노드가 있을 경우
			else
				insert(pKey, Data, Node->mLeft);
		}
		//값이 클 때
		else
		{
			if (!Node->mRight)
			{
				NODE* NewNode = new NODE;

				NewNode->mData = Data;
				NewNode->mKey = pKey;
				NewNode->mParent = Node;

				Node->mRight = NewNode;

				NODE* Next = Node->mNext;

				Next->mPrev = NewNode;
				NewNode->mNext = Next;

				NewNode->mPrev = Node;
				Node->mNext= NewNode;
			}
			else
				insert(pKey, Data, Node->mRight);
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
		if(!mRoot)
		{
			mRoot = new NODE;
			mRoot->mKey = pKey;
			mRoot->mData = Data;

			mBegin->mNext = mRoot;
			mRoot->mPrev = mBegin;

			mEnd->mPrev = mRoot;
			mRoot->mNext = mEnd;
		}
		else
			insert(pKey, Data, mRoot); 

		mSize++;
	}

	bool empty() const { return mSize == 0; }
	int size() const { return mSize; }

	void clear()
	{
		NODE* DelNode = mBegin->mNext;

		while (DelNode != mEnd)
		{
			NODE* Next = DelNode->mNext;
			delete DelNode;
			DelNode = Next;
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
