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

//Key: ��带 Ž���ϱ� ���� Ÿ��
//Value: ���� ��忡 �����ϱ� ���� Ÿ��
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
		//root���� ��� node�� Ž��
		//�θ��带 ã�ƿ´�
		NODE* Parent = FindNode(ParentKey, mRoot);

		//Parent Node�� ���ٸ� Root
		if (!Parent)
		{
			if (mRoot)
			{
				mRoot->mParent = Node;
				Node->mChildArray.push_back(mRoot);
			}
			mRoot = Node;
			//��Ʈ�� �� �Է°� ��ü
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
	// root(Node)�������� �����ؼ� �� ������ ����Լ��� ����
	// ã���� �ϴ� ���� �θ���(pKey)
	NODE* FindNode(const Key& pKey, NODE* Node)
	{
		//node�� nullptr�� ��� Ž������
		if (!Node)
			return nullptr;
		//��� �� pKey�� �߰��ϸ� �� ��带 ��ȯ
		else if (Node->mKey == pKey)
			return Node;

		//���� ��尡 ������ �ִ� child�� ��
		int ChildSize = Node->mChildArray.size();

		//child��ŭ ���
		for (int i = 0;i < ChildSize;i++)
		{
			NODE* Find = FindNode(pKey, Node->mChildArray[i]);
			//��� �߰� �� ��ȯ
			if (Find)
				return Find;
		}
		//��� node�� ��ġ���� ���� ��� nullptr ��ȯ
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

