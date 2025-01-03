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
	bool operator==(const CIterator<Key, Value>& iter)
	{
		return mNode == iter.mNode;
	}
	bool operator!=(const CIterator<Key, Value>& iter)
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
			if (!Node->mLeft)
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

				Node->mRight = NewNode;
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

	NODE* FindMin(NODE* Node)
	{
		//더 작은 자식노드가 없다면 현재노드 반환
		if (!Node->mLeft)
			return Node;
		//존재한다면 재귀
		return FindMin(Node->mLeft);

		////while문 구현방법
		//while (Node->mLeft)
		//	Node = Node->mData;

		//return Node;
	}

	NODE* FindMax(NODE* Node)
	{
		while (Node->mRight)
			Node = Node->mData;

		return Node;
	}

	//전위 순회
	//좌측 우선 순회 후 우측 순회
	void PreOrder(NODE* Node)
	{
		if (!Node)
			return;

		std::cout << "Key: " << Node->mKey << ", Value: " << Node->mData << std::endl;
		PreOrder(Node->mLeft);
		PreOrder(Node->mRight);
	}

	//중위 순회
	//좌측 리프노드부터 탐색 진행
	//정렬
	void InOrder(NODE* Node)
	{
		if (!Node)
			return;

		InOrder(Node->mLeft);
		std::cout << "Key: " << Node->mKey << ", Value: " << Node->mData << std::endl;
		InOrder(Node->mRight);
	}
	//후위 순회
	//좌측 리프노드부터 탐색 진행
	//자식 노드가 모두 출력 된 이후 부모노드를 출력
	//루트가 가장 마지막에 출력
	void PostOrder(NODE* Node)
	{
		if (!Node)
			return;

		PostOrder(Node->mLeft);
		PostOrder(Node->mRight);
		std::cout << "Key: " << Node->mKey << ", Value: " << Node->mData << std::endl;
	}
	//레벨순회
	//깊이우선탐색

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

	ITR erase(const Key& pKey)
	{
		ITR iter = find(pKey);
		return erase(iter);
	}

	ITR erase(const ITR& iter)
	{
		if (iter.mNode == mEnd)
			return iter;

		//삭제(대체)할 노드
		NODE* DeleteNode = nullptr;
		NODE* ResultNode = nullptr;

		//leaf node일 경우
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			//현재 노드에 부모노드가 있는지 확인
			NODE* Parent = iter.mNode->mParent;
			//부모노드가 있다면 어느쪽 자식노드인지 확인
			//부모노드와 현재 노드의 연결을 제거
			if (Parent)
			{
				if (iter.mNode == Parent->mLeft)
					Parent->mLeft = nullptr;
				else
					Parent->mRight = nullptr;
			}
			//부모노드가 없다면 Root노드
			else
				mRoot = nullptr;

			DeleteNode = iter.mNode;
			ResultNode = DeleteNode->mNext;
		}
		else
		{
			//탐색 중 child node로 사용될 수 있는 값을 미리 저장
			NODE* ChildNode = nullptr;
			//자식 노드를 가지고 있을 경우
			//좌측 우선 탐색(우측우선 탐색도 무관)
			if (iter.mNode->mLeft)
			{
				//왼쪽에 노드가 존재한다면 가장 큰 노드를 탐색
				//발견한 노드를 삭제할 노드로 사용
				DeleteNode = FindMax(iter.mNode->mLeft);
				ChildNode = DeleteNode->mLeft;
				ResultNode = iter.mNode->mNext;
			}
			else
			{
				//오른쪽에 노드가 있다면 가장 작은 노드를 탐색
				//발견한 노드를 삭제할 노드로 사용
				DeleteNode = FindMin(iter.mNode->mRight);
				ChildNode = DeleteNode->mRight;
				ResultNode = iter.mNode;
			}
			//위에서 탐색한 노드의 값으로 iterator가 보유한 노드(현재 노드)의 값을 대체
			iter.mNode->mKey = DeleteNode->mKey;
			iter.mNode->mData = DeleteNode->mData;

			NODE* Parent = DeleteNode->mParent;

			if (Parent)
			{
				if (DeleteNode == Parent->mLeft)
					Parent->mLeft = ChildNode;
				else
					Parent->mRight = ChildNode;
			}

			if (ChildNode)
				ChildNode->mParent = Parent;
		}

		//iterator 처리
		NODE* Prev = DeleteNode->mPrev;
		NODE* Next = DeleteNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		delete DeleteNode;

		mSize--;

		ITR iter;
		iter.mNode = Next;
		return iter;
	}

	void PreOrder() { PreOrder(mRoot); }
	void InOrder() { InOrder(mRoot); }
	void PostOrder() { PostOrder(mRoot); }
};
