#pragma once

template<typename Key, typename Value>
class CNode
{
	template<typename Key, typename Value>
	friend class CAVLTree;
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
	friend class CAVLTree;
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
	~CAVLTree() {}
private:
	typedef CAVLTree<Key, Value> CBT;
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

		//���� ���� ��(������� �߰�)
		if (pKey < Node->mKey)
		{
			// ������ ��尡 ���� ���
			if (!Node->mLeft)
			{
				NODE* NewNode = new NODE;

				NewNode->mData = Data;
				NewNode->mKey = pKey;
				NewNode->mParent = Node;

				Node->mLeft = NewNode;
				//Tree ����

				NODE* Prev = Node->mPrev;

				Prev->mNext = NewNode;
				NewNode->mPrev = Prev;

				NewNode->mNext = Node;
				Node->mPrev = NewNode;
				//Linkedlist ����
				ReBalance_1(Node->mParent);
			}
			// ������ ��尡 ���� ���
			else
				insert(pKey, Data, Node->mLeft);
		}
		//���� Ŭ ��
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
				Node->mNext = NewNode;

				ReBalance_1(Node->mParent);
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
			Node = Node->mLeft;

		return Node;
	}
	NODE* FindMax(NODE* Node)
	{
		while (Node->mRight)
			Node = Node->mRight;

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

	//����� ���̸� Ȯ��
	int GetHeight(NODE* Node)
	{
		if (!Node)
			return 0;

		int Left = GetHeight(Node->mLeft);
		int Right = GetHeight(Node->mRight);

		return Left < Right ? Right + 1 : Left + 1;
	}
	//�¿� �뷱���� Ȯ���ϰ� �������� ��ȯ
	int BalanceFactor(NODE* Node)
	{
		if (!Node)
			return 0;

		return GetHeight(Node->mLeft) - GetHeight(Node->mRight);
		//��ȯ�� ���� ���밪�� 2���� Ŭ ��� �뷱���� ��������
		//�������� ��� ���� ����
		//����� ��� ���� ����
	}

	//�뷱���� �������� Ʈ���� ������
	NODE* Balance(NODE* Node)
	{

	}


	//����ȸ��
	NODE* RotationLeft(NODE* Node)
	{
		NODE* RightChild = Node->mRight;
		NODE* RCLeftChild = RightChild->mLeft;
		NODE* Parent = Node->mParent;

		if (Parent)
		{
			if (Parent->mLeft == Node)
				Parent->mLeft = RightChild;
			else
				Parent->mRight = RightChild;
		}
		else
			mRoot = RightChild;

		RightChild->mParent = Parent;

		RightChild->mLeft = Node;
		Node->mParent = RightChild;

		Node->mRight = RCLeftChild;
		if (RCLeftChild)
			RCLeftChild->mParent = Node;

		return RightChild;
	}
	//����ȸ��
	NODE* RotationRight(NODE* Node)
	{
		NODE* LeftChild = Node->mLeft;
		NODE* LCRightChild = LeftChild->mRight;
		NODE* Parent = Node->mParent;

		if (Parent)
		{
			if (Parent->mLeft == Node)
				Parent->mLeft = LeftChild;
			else
				Parent->mRight = LeftChild;
		}
		else
			mRoot = LeftChild;

		LeftChild->mParent = Parent;

		LeftChild->mRight = Node;
		Node->mParent = LeftChild;

		Node->mLeft = LCRightChild;
		if(LCRightChild)
			LCRightChild->mParent = Node;

		return LeftChild;
	}
	
	void ReBalance_1(NODE* Node)
	{
		while (Node)
		{
			int Factor = BalanceFactor(Node);

			//������ Ŭ ���
			if (Factor > 1)
			{
				//LR
				if (BalanceFactor(Node->mLeft) < 0)
					RotationLeft(Node->mLeft);
				//LL
				Node = RotationRight(Node);
			}
			else if (Factor < -1)
			{
				//RL
				if (BalanceFactor(Node->mRight) > 0)
					RotationLeft(Node->mRight);
				//RR
				Node = RotationLeft(Node);
			}
		//ȸ������ ������ ���� �� ��Ʈ������ ����Ž��
		Node = Node->mParent;
		}
	}

	void Output(NODE* Node)
	{
		if (!Node)
			return;
		std::cout << std::endl;
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
		if (iter.mNode == mEnd)
			return iter;

		NODE* DeleteNode = nullptr;
		NODE* ResultNode = nullptr;

		//1.������ ��尡 ����������� Ȯ��
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			//2.��������� ��� �ڽ��� �θ��忡�� �ڽ��� ��ġ(L,R)�� Ȯ���ϰ� ��������
			NODE* ParentNode = iter.mNode->mParent;
			//3.�θ��尡 �������� �ʴ´ٸ� ��Ʈ���
			if (ParentNode)
			{
				if (ParentNode->mLeft == iter.mNode)
					ParentNode->mLeft = nullptr;
				else
					ParentNode->mRight = nullptr;
			}
			else
				mRoot = nullptr;

			//������ ����� �ּ� �Է�
			DeleteNode = iter.mNode;
			//���� �� ��ȯ�� ���� �ּҰ� �Է�
			ResultNode = DeleteNode->mNext;
		}
		//4.������尡 �ƴ� ���
		else
		{
			NODE* ChildNode = nullptr;
			//���� �켱 Ž��(�����켱�� ����)
			//���� ��忡�� ���� ū ��带 Ž��
			//(�ڽź��� ���� �� �߿��� ���� ū ��)
			if (iter.mNode->mLeft)
			{
				DeleteNode = FindMax(iter.mNode->mLeft);
				ChildNode = DeleteNode->mLeft;
				ResultNode = iter.mNode->mNext;
			}
			//���� ��忡�� ���� ���� ��� Ž��
			else
			{
				DeleteNode = FindMin(iter.mNode->mRight);
				ChildNode = DeleteNode->mRight;
				ResultNode = iter.mNode->mNext;
			}
			//�߰��� ���� ���� ���(iterator�� ����Ű�� ���)�� ��ü
			iter.mNode->mData = DeleteNode->mData;
			iter.mNode->mKey = DeleteNode->mKey;

			NODE* ParentNode = DeleteNode->mParent;

			if (ParentNode)
			{	//Ž���� �Ϸ�� ���(delete)�� �θ����� ��� �ʿ� ��ġ�ϴ� �� Ȯ��
				//�θ����� �ڽĳ��(���� �ڼճ��)�� ����
				if (DeleteNode == ParentNode->mLeft)
					ParentNode->mLeft = ChildNode;
				else
					ParentNode->mRight = ChildNode;
			}
			//�ڽĳ���� �θ��带 ����
			if (ChildNode)
				ChildNode->mParent = ParentNode;
		}

		NODE* Prev = DeleteNode->mPrev;
		NODE* Next = DeleteNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		ReBalance_1(DeleteNode->mParent);

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
	void Output() { Output(mRoot); }
};