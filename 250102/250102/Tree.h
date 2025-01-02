#pragma once
#include <assert.h>
#include "Array.h"

template<typename Key, typename Value>
class CNode
{
	template <typename Key, typename Value>
	friend class CTree;
public:
	CNode() {}
	~CNode() {}
private:
	Key mKey;
	Value mData;
	CNode<Key,Value>* mParent = nullptr;
	CArray<CNode<Key, Value>*> mChildArray;
};

//Key: 노드를 탐색하기 위한 타입
//Value: 실제 노드에 저장하기 위한 타입
template <typename Key, typename Value>
class CTree
{
private:
	typedef CNode<Key, Value> NODE;
public:
	CTree() {}
	~CTree() 
	{
		clear();
	}
private:
	NODE* mRoot = nullptr;
	int mSize = 0;

public:
	void insert(const Key& pKey, const Value& Data, const Key& ParentKey)
	{
		NODE* Node = new NODE;

		Node->mKey = pKey;
		Node->mData = Data;
		//root부터 모든 node를 탐색
		//부모노드를 찾아온다
		NODE* Parent = FindNode(ParentKey, mRoot);

		//Parent Node가 없다면 Root
		if (!Parent)
		{
			if (mRoot)
			{
				mRoot->mParent = Node;
				Node->mChildArray.push_back(mRoot);
			}
			mRoot = Node;
			//루트를 새 입력과 교체
		}
		else
		{
			Parent->mChildArray.push_back(Node);
			Node->mParent = Parent;
		}

		mSize++;
	}

	void Output()
	{
		Output(mRoot);
	}
	
	void clear()
	{
		clear(mRoot);
		mSize = 0;
		mRoot = nullptr;
	}
private:
	// root(Node)에서부터 시작해서 각 노드들을 재귀함수로 변경
	// 찾고자 하는 것은 부모노드(pKey)
	NODE* FindNode(const Key& pKey, NODE* Node)
	{
		//node가 nullptr일 경우 탐색중지
		if (!Node)
			return nullptr;
		//재귀 중 pKey를 발견하면 그 노드를 반환
		else if (Node->mKey == pKey)
			return Node;

		//현재 노드가 가지고 있는 child의 수
		int ChildSize = Node->mChildArray.size();

		//child만큼 재귀
		for (int i = 0;i < ChildSize;i++)
		{
			NODE* Find = FindNode(pKey, Node->mChildArray[i]);
			//노드 발견 시 반환
			if (Find)
				return Find;
		}
		//모든 node가 일치하지 않을 경우 nullptr 반환
		return nullptr;
	}

	void Output(NODE* Node)
	{
		if (!Node)
			return;
		
		std::cout << "Parent: ";

		if (Node->mParent)
			std::cout << Node->mParent->mKey << std::endl;
		else
			std::cout << "None" << std::endl;

		std::cout << "Node: " << Node->mKey << std::endl;
		
		int ChildSize = Node->mChildArray.size();

		for (int i = 0;i < ChildSize;i++)
		{
			std::cout << "child" << i << ": " << Node->mChildArray[i]->mKey << '\t';
		}
		std::cout << std::endl;

		for (int i = 0;i < ChildSize;i++)
			Output(Node->mChildArray[i]);
	}
	
	void clear(NODE* Node)
	{
		if (!Node)
			return;

		int ChildSize = Node->mChildArray.size();

		for (int i = 0;i < ChildSize;i++)
		{
			clear(Node->mChildArray[i]);
		}
		delete Node;

	}
};

