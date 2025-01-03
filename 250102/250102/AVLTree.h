#pragma once
#pragma once
#include "Array.h"

template<typename Key, typename Value>
class CNode
{
	template <typename Key, typename Value>
	friend class CAVLTree;
	template <typename Key, typename Value>
	friend class CIterator;
public:
	CNode() {}
	~CNode() {}
private:
	CNode<Key, Value>* mParent = nullptr;
	CNode<Key, Value>* mLeft = nullptr;
	CNode<Key, Value>* mRight = nullptr;
	//tree�� ��� �������� �ݺ� ó���� �ʿ�
	//node�� ���ĸ� linked list�� ����
	CNode<Key, Value>* mNext = nullptr;
	CNode<Key, Value>* mPrev = nullptr;
public:
	Key mKey;
	Value mData;
	//Ž������Ʈ���� ��� ���� ��ȯ�� �� �־�� �ϹǷ� �����ʹ� ����
};

template<typename Key, typename Value>
class CIterator
{
	template<typename Key, typename Value>
	friend class CAVLTree;
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

//Ž�� �� ��ȸ ����
template<typename Key, typename Value>
class CAVLTree
{
public:
	CAVLTree()
	{
		mBegin = new NODE;
		mEnd = new NODE;
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}
	~CAVLTree()
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

		//������ key�� ����� key�� ���� �¿츦 �Ǵ�
		if (pKey < Node->mKey)
		{
			//���ʿ� �߰��� ��, ���� ��尡 ���� ���
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
				
				ReBalnace(Node->mParent);
			}
			//���� ��尡 ������ ���
			else
			{
				insert(pKey, Data, Node->mLeft);
			}
		}
		//������ ��带 �߰��� ��
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
				//����� �θ��� �θ��� ���� ������ �������Ƿ�
				ReBalnace(Node->mParent);
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
		//�� ���� �ڽĳ�尡 ���ٸ� ������ ��ȯ
		if (!Node->mLeft)
			return Node;
		//�����Ѵٸ� ���
		return FindMin(Node->mLeft);

		////while�� �������
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

	//���� ��ȸ
	//���� �켱 ��ȸ �� ���� ��ȸ
	void PreOrder(NODE* Node)
	{
		if (!Node)
			return;

		std::cout << "Key: " << Node->mKey << ", Value: " << Node->mData << std::endl;
		PreOrder(Node->mLeft);
		PreOrder(Node->mRight);
	}

	//���� ��ȸ
	//���� ���������� Ž�� ����
	//����
	void InOrder(NODE* Node)
	{
		if (!Node)
			return;

		InOrder(Node->mLeft);
		std::cout << "Key: " << Node->mKey << ", Value: " << Node->mData << std::endl;
		InOrder(Node->mRight);
	}
	//���� ��ȸ
	//���� ���������� Ž�� ����
	//�ڽ� ��尡 ��� ��� �� ���� �θ��带 ���
	//��Ʈ�� ���� �������� ���
	void PostOrder(NODE* Node)
	{
		if (!Node)
			return;

		PostOrder(Node->mLeft);
		PostOrder(Node->mRight);
		std::cout << "Key: " << Node->mKey << ", Value: " << Node->mData << std::endl;
	}
	//���ڷ� ���� ��带 �������� ���ʰ� �������� �������� Ȯ��
	int BalanceFactor(NODE* Node) const
	{
		if (!Node)
			return 0;

		return GetHeight(Node->mLeft) - GetHeight(Node->mRight);

	}

	NODE* RotationLeft(NODE* Node)
	{
		//���� ȸ�� �� ���س���� ������ child�� ���� �ö��(�θ���ȭ)
		NODE* RightChild = Node->mRight;
		//������ child�� ���� child�� ����
		NODE* RCLeftChild = RightChild->mLeft;
		//���س���� �θ���
		NODE* ParentNode = Node->mParent;

		if (ParentNode)
		{
			if (ParentNode->mLeft == Node)
				ParentNode->mLeft = RightChild;
			else
				ParentNode->mRight = RightChild;
		}
		else
			mRoot = RightChild;

		RightChild->mParent = ParentNode;

		RightChild->mLeft = Node;
		Node->mParent = RightChild;

		Node->mRight = RCLeftChild;
		if(RCLeftChild)
			RCLeftChild->mParent = Node;

		return RightChild;
	}

	NODE* RotationRight(NODE* Node)
	{
		NODE* LeftChild = Node->mLeft;
		NODE* LCRightChild = LeftChild->mRight;
		NODE* ParentNode = Node->mParent;

		if (ParentNode)
		{
			if (ParentNode->mLeft == Node)
				ParentNode->mLeft = LeftChild;
			else
				ParentNode->mRight = LeftChild;
		}
		else
			mRoot = LeftChild;

		LeftChild->mParent = ParentNode;

		LeftChild->mLeft = Node;
		Node->mParent = LeftChild;

		Node->mRight = LCRightChild;
		if (LCRightChild)
			LCRightChild->mParent = Node;

		return LeftChild;
	}

	int GetHeight(NODE* Node) const
	{
		if (!Node)
			return 0;

		int Left = GetHeight(Node->mLeft);
		int Right = GetHeight(Node->mRight);

		//��� 1���� �� �߰��Ǿ����Ƿ� 1�� ����
		return Left < Right ? Right + 1 : Left + 1;
	
	}
	//ȸ�� �� ���� �ö��(�θ��尡 ��) ��带 ��ȯ
	NODE* Balance(NODE* Node) 
	{
		int Factor = BalanceFactor(Node);

		if (abs(Factor) < 2)
			return Node;
		//���ʿ��� ������ ���� ���� �����Ƿ�
		//0���� ũ�ٴ� ���� �������� �������� Ȯ��
		//�������� ������ ���
		if (Factor > 0)
		{
			//����->���������� ������ ���
			if(BalanceFactor(Node->mLeft)<0)
				//���� �ڽĳ�带 �������� ȸ��
				RotationLeft(Node->mLeft);
			//���س�带 ���������� ȸ��
			Node = RotationRight(Node);
		}
		//���������� ������ ���
		else
		{
			//������->�������� ������ ���
			if (BalanceFactor(Node->mRight) > 0)
				//������ �ڽĳ�带 ���������� ȸ��
				RotationRight(Node->mRight);
			//���س�带 �������� ȸ��
			Node = RotationLeft(Node);
		}
	}

	void ReBalnace(NODE* Node)
	{
		while (Node)
		{
			Node = Balance(Node);
			Node = Node->mParent;
		}
	}
	
	void Output(NODE* Node)
	{
		if (!Node)
			return;
		std::cout << "Key : " << Node->mKey << ", Value : " <<
			Node->mData << std::endl;
		std::cout << "Parent : ";
		if (Node->mParent)
			std::cout << Node->mParent->mKey << std::endl;
		else
			std::cout << "None" << std::endl;

		std::cout << "Left : ";
		if (Node->mLeft)
			std::cout << Node->mLeft->mKey << std::endl;
		else
			std::cout << "None" << std::endl;

		std::cout << "Right : ";
		if (Node->mRight)
			std::cout << Node->mRight->mKey << std::endl;
		else
			std::cout << "None" << std::endl;

		Output(Node->mLeft);
		Output(Node->mRight);
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

	ITR erase(const Key& pKey)
	{
		ITR iter = find(pKey);
		return erase(iter);
	}

	ITR erase(const ITR& iter)
	{
		if (iter.mNode == mEnd)
			return iter;

		//����(��ü)�� ���
		NODE* DeleteNode = nullptr;
		NODE* ResultNode = nullptr;

		//leaf node�� ���
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			//���� ��忡 �θ��尡 �ִ��� Ȯ��
			NODE* Parent = iter.mNode->mParent;
			//�θ��尡 �ִٸ� ����� �ڽĳ������ Ȯ��
			//�θ���� ���� ����� ������ ����
			if (Parent)
			{
				if (iter.mNode == Parent->mLeft)
					Parent->mLeft = nullptr;
				else
					Parent->mRight = nullptr;
			}
			//�θ��尡 ���ٸ� Root���
			else
				mRoot = nullptr;

			DeleteNode = iter.mNode;
			ResultNode = DeleteNode->mNext;
		}
		else
		{
			//Ž�� �� child node�� ���� �� �ִ� ���� �̸� ����
			NODE* ChildNode = nullptr;
			//�ڽ� ��带 ������ ���� ���
			//���� �켱 Ž��(�����켱 Ž���� ����)
			if (iter.mNode->mLeft)
			{
				//���ʿ� ��尡 �����Ѵٸ� ���� ū ��带 Ž��
				//�߰��� ��带 ������ ���� ���
				DeleteNode = FindMax(iter.mNode->mLeft);
				ChildNode = DeleteNode->mLeft;
				ResultNode = iter.mNode->mNext;
			}
			else
			{
				//�����ʿ� ��尡 �ִٸ� ���� ���� ��带 Ž��
				//�߰��� ��带 ������ ���� ���
				DeleteNode = FindMin(iter.mNode->mRight);
				ChildNode = DeleteNode->mRight;
				ResultNode = iter.mNode;
			}
			//������ Ž���� ����� ������ iterator�� ������ ���(���� ���)�� ���� ��ü
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

		//iterator ó��
		NODE* Prev = DeleteNode->mPrev;
		NODE* Next = DeleteNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;
		
		//Rebanance();
		delete DeleteNode;

		mSize--;

		ITR iter;
		iter.mNode = Next;
		return iter;
	}

	void PreOrder() { PreOrder(mRoot); }
	void InOrder() { InOrder(mRoot); }
	void PostOrder() { PostOrder(mRoot); }
	void Output() { Output(mRoot); }
};

