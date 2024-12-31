#pragma once
#include <assert.h>

template<typename T>
class CListNode
{
	template<typename T>
	friend class CLinkedList;
	template<typename T>
	friend class CListIterator;

private:
	CListNode() {}
	~CListNode() 
	{
	}
private:
	T mData;	
	//� Ÿ���� �����Ͱ� ���Ե� �� �𸣱� ������ memset�� ����
	// ���Լ��� ���� ��� ������ �߻��� �� ����
	//�ʱ�ȭ�� ���� �ʴ� ���� ����
	CListNode<T>* mNext = nullptr;
	CListNode<T>* mPrev = nullptr;
};

template <typename T>
class CListIterator
{
	template<typename T>
	friend class CLinkedList;

public:
	CListIterator() 
	{

	}
	~CListIterator()
	{

	}
private:
	CListNode<T>* mNode = nullptr;
public:
	//==, !=
	//iterator�� ������ �ִ� ��带 �� 
	//�� iterator�� �ּҰ� ���� ��� ���� ������ �Ǵ�
	bool operator==(const CListIterator<T>& iter) const
	{
		return mNode == iter.mNode;
	}
	bool operator!=(const CListIterator<T>& iter) const
	{
		return mNode != iter.mNode;
	}
	//++, -- 
	//��ȯ���� void�� ��� ������ �Ұ���
	//iter = iter++;
	const CListIterator<T>& operator++ ()
	{
		mNode = mNode->mNext;
		assert(mNode != nullptr);

		return *this;
	}

	const CListIterator<T>& operator++ (int)
	{
		mNode = mNode->mNext;
		assert(mNode != nullptr);

		return *this;
	}

	//*(������)
	T& operator *()
	{
		assert(mNode != nullptr);

		return mNode->mData;
	}
};

template<typename T>
class CLinkedList
{
private:
	typedef CListNode<T> NODE;
	//Ŭ�������� CListNode<T> ��� NODE�� ���� 
public:
	typedef CListIterator<T> iterator;
	//�ܺο��� iterator ȣ�Ⱑ��
public:
	CLinkedList()
	{
		mBegin = new NODE;
		mEnd = new NODE;

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
	NODE* mBegin;
	NODE* mEnd;
	int mSize = 0;
public:
	//End�� End���� ��� ���̿� �߰�
	void push_back(const T& Data)
		//Ŭ������ ��ü�� ���� �� �����Ƿ� ���۷����� ���ڷ� ���
	{
		NODE* Node = new NODE;
		NODE* Prev = mEnd->mPrev;

		Node->mData = Data;

		Prev->mNext = Node;
		Node->mPrev = Prev;

		mEnd->mPrev = Node;
		Node->mNext = mEnd;

		++mSize;
	}

	void push_front(const T& Data)
	{
		NODE* Node = new NODE;
		NODE* Next = mBegin->mNext;

		Node->mData = Data;

		Node->mNext = Next;
		Next->mPrev = Node;

		mBegin->mNext = Node;
		Node->mPrev = mBegin;

		++mSize;
	}
	void pop_back()
	{
		//if(mSize == 0)
		assert(mSize != 0);

		NODE* DeleteNode = mEnd->mPrev;
		NODE* Prev = DeleteNode->mPrev;

		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		delete DeleteNode;
		--mSize;
	}
	bool empty() const 
	{
		return mSize == 0;
	}

	int size() const
	{
		return mSize;
	}

	void pop_front()
	{
		assert(mSize != 0);

		NODE* DeleteNode = mBegin->mNext;
		NODE* Next = DeleteNode->mNext;

		mBegin->mNext = Next;
		Next->mPrev = mBegin;

		delete DeleteNode;
		--mSize;
	}

	void clear()
	{
		NODE* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			NODE* Next = Node->mNext;
			//��� ���� ��, �̸� ������带 �ҷ���
			delete Node;
			Node = Next;
		}
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	//Begin����� ���� ��带 ������ �ִ� iterator�� ��ȯ
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
		Prev->mNext = Node;
		Node->mPrev = Prev;

		Node->mNext = iter.Node;
		iter.mNode->mPrev = Node;

		mSize++;
	}

	//iterator erase(const T& Data)
	//{

	//}

	iterator erase(const iterator* iter)
	{
		if (mSize == 0)
			return end();

		NODE* Prev = iter.mNode->mPrev;
		NODE* Next = iter.mNode->mNext;

		delete iter.mNode;

		Prev.mNext = Next;
		Next.mPrev = Prev;

		mSize--;

		iterator result;
		result.mNode = Next;
		return result;
	}
};

