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
	NODE* FindMin(NODE* Node)
	{
		while (Node->mLeft)
			Node = Node->mData;

		return Node;
	}
	NODE* FindMax(NODE* Node)
	{
		while (Node->mRight)
			Node = Node->mData;

		return Node;
	}
	void PreOrder(NODE* Node) 
	{
		if (!Node)
			return;

		std::cout << "Key:" << Node->mKey << std::endl;
		PreOrder(Node->mLeft);
		PreOrder(Node->mRight);
	}
	void InOrder(NODE* Node)
	{
		if (!Node)
			return;
		
		PreOrder(Node->mLeft);
		std::cout << "Key:" << Node->mKey << std::endl;
		PreOrder(Node->mRight);
	}
	void PostOrder(NODE* Node) 
	{
		if (!Node)
			return;
		
		PreOrder(Node->mLeft);
		PreOrder(Node->mRight);
		std::cout << "Key:" << Node->mKey << std::endl;
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

	ITR erase(const Key& pKey)
	{
		ITR iter = find(pKey);
		return erase(iter);
	}

	ITR erase(ITR& iter)
	{
		if (iter.mNode==mEnd)
			return iter;

		NODE* DeleteNode = nullptr;
		NODE* ChildNode = nullptr;

		//1.삭제할 노드가 리프노드인지 확인
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			//2.리프노드일 경우 자신의 부모노드에서 자신의 위치(L,R)를 확인하고 연결제거
			NODE* ParentNode = iter.mNode->mParent;
			//3.부모노드가 존재하지 않는다면 루트노드
			if (ParentNode)
			{
				if (ParentNode->mLeft == iter.mNode)
					ParentNode->mLeft == nullptr;
				else
					ParentNode->mRight == nullptr;
			}
			else
				mRoot = nullptr;

			//삭제할 노드의 주소 입력
			DeleteNode = iter.mNode;
			//삭제 후 반환할 다음 주소값 입력
			ResultNode = DeleteNode->mNext;
		}
		//4.리프노드가 아닐 경우
		else
		{
			NODE* ChildNode = nullptr;
			//좌측 우선 탐색(우측우선도 무관)
			//왼쪽 노드에서 가장 큰 노드를 탐색
			//(자신보다 작은 값 중에서 가장 큰 값)
			if (iter.mNode->mLeft)
			{
				DeleteNode = FindMax(iter.mNode->mLeft);
				ChildNode = DeleteNode->mLeft;
				ResultNode = iter.mNode->mNext;
			}
			//우측 노드에서 가장 작은 노드 탐색
			else
			{
				DeleteNode = FindMin(iter.mNode->mRight);
				ChildNode = DeleteNode->mRight;
				ResultNode = iter.mNode->mNext;
			}
			//발견한 노드와 현재 노드(iterator가 가르키는 노드)를 대체
			iter.mNode->mData = DeleteNode->mData;
			iter.mNode->mKey = DeleteNode->mKey;

			NODE* ParentNode = DeleteNode->mParent;

			if (ParentNode)
			{	//탐색이 완료된 노드(delete)가 부모노드의 어느 쪽에 위치하는 지 확인
				//부모노드의 자식노드(기존 자손노드)를 연결
				if (DeleteNode == ParentNode->mLeft)
					ParentNode->mLeft = ChildNode;
				else
					ParentNode->mRight = ChildNode;
			}
			//자식노드의 부모노드를 연결
			if (ChildNode)
				ChildNode->mParent = ParentNode;
		}

		NODE* Prev = DeleteNode->mPrev;
		NODE* Next = DeleteNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;
		
		delete DeleteNode;

		mSize--;

		ITR result;
		result.mNode = ResultNode;
		return result;
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

	void PreOrder() { PreOrder(mRoot); }
	void InOrder() { InOrder(mRoot); }
	void PostOrder() { PostOrder(mRoot); }
};
