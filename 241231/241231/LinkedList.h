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
	//어떤 타입의 데이터가 삽입될 지 모르기 때문에 memset만 가능
	// 상함수가 있을 경우 문제가 발생할 수 있음
	//초기화를 하지 않는 쪽을 권장
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
	//iterator가 가지고 있는 노드를 비교 
	//두 iterator의 주소가 같을 경우 같은 것으로 판단
	bool operator==(const CListIterator<T>& iter) const
	{
		return mNode == iter.mNode;
	}
	bool operator!=(const CListIterator<T>& iter) const
	{
		return mNode != iter.mNode;
	}
	//++, -- 
	//반환값이 void일 경우 대입이 불가능
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

	//*(역참조)
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
	//클래스에서 CListNode<T> 대신 NODE로 선언 
public:
	typedef CListIterator<T> iterator;
	//외부에서 iterator 호출가능
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
	//End와 End이전 노드 사이에 추가
	void push_back(const T& Data)
		//클래스나 객체가 들어올 수 있으므로 레퍼런스를 인자로 사용
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
			//노드 삭제 전, 미리 다음노드를 불러옴
			delete Node;
			Node = Next;
		}
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	//Begin노드의 다음 노드를 가지고 있는 iterator를 반환
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

