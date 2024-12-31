#pragma once
#include <assert.h>

template<typename T>
class CListNode
{
	template<typename T>
	friend class CLinkedList;
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

template<typename T>
class CLinkedList
{
private:
	typedef CListNode<T> NODE;
	//Ŭ�������� CListNode<T> ��� NODE�� ���� 
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

		++mSzie;
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
};

