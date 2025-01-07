#pragma once
#include <assert.h>

template<typename T>
class CNode
{
	template<typename T>
	friend class CIterator;
	template<typename T>
	friend class CLinkedList;
private:
	CNode() {}
	~CNode() {}
private:
	T m_Data;
	CNode<T>* m_Next = nullptr;
	CNode<T>* m_Prev = nullptr;
};

template<typename T>
class CIterator
{
	template<typename T>
	friend class CLinkedList;
private:
	typedef CIterator<T> ITR;
public:
	CIterator() {}
	~CIterator() {}
private:
	CNode<T>* m_Node;
public:
	bool operator==(const ITR& iter)
	{
		return m_Node == iter.m_Node;
	}
	bool operator!=(const ITR& iter)
	{
		return m_Node != iter.m_Node;
	}
	T operator*()
	{
		return m_Node->m_Data;
	}
	ITR& operator++()
	{
		m_Node = m_Node->m_Next;
		return *this;
	}
	ITR& operator++(int)
	{
		m_Node = m_Node->m_Next;
		return *this;
	}
	ITR& operator--()
	{
		m_Node = m_Node->m_Prev;
		return *this;
	}
	ITR& operator--(int)
	{
		m_Node = m_Node->m_Prev;
		return *this;
	}
};

template<typename T>
class CLinkedList
{
private:
	typedef CNode<T> NODE;
	typedef CIterator<T> ITR;
public:
	CLinkedList() 
	{
		m_Begin = new NODE;
		m_End = new NODE;

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;
	}
	~CLinkedList() 
	{
		clear();
		delete m_Begin;
		delete m_End;
	}
private:
	int m_Size = 0;
	NODE* m_Begin = nullptr;
	NODE* m_End = nullptr;
public:
	void push_back(const T& Data)
	{
		NODE* Node = new NODE;
		NODE* Prev = m_End->m_Prev;

		Node->m_Data = Data;

		Prev->m_Next = Node;
		Node->m_Prev = Prev;

		Node->m_Next = m_End;
		m_End->m_Prev = Node;

		m_Size++;
	}
	void push_front(const T& Data)
	{
		NODE* Node = new NODE;
		NODE* Next = m_Begin->m_Next;

		Node->m_Data = Data;

		Next->m_Prev = Node;
		Node->m_Next = Next;
		
		Node->m_Prev = m_Begin;
		m_Begin->m_Next = Node;

		m_Size++;

	}
	void pop_back()
	{
		assert(m_Size);

		NODE* DelNode = m_End->m_Prev;

		m_End->m_Prev = DelNode->m_Prev;
		DelNode->m_Prev->m_Next = m_End;

		delete DelNode;

		m_Size--;
	}
	void pop_front()
	{
		assert(m_Size);

		NODE* DelNode = m_Begin->m_Next;

		m_Begin->m_Next = DelNode->m_Next;
		DelNode->m_Next->m_Prev = m_Begin;

		delete DelNode;

		m_Size--;
	}

	bool empty() { return m_Size == 0; }

	int size() { return m_Size; }

	ITR begin()
	{
		ITR iter;
		iter.m_Node = m_Begin->m_Next;
		return iter;
	}

	ITR end()
	{
		ITR iter;
		iter.m_Node = m_End;
		return iter;
	}

	void insert(const T& Data, const ITR& iter)
	{
		NODE* Node = new NODE;
		//NODE* Next = iter.m_Node->m_Next;
		NODE* Prev = iter.m_Node->m_Prev;

		Node->m_Data = Data;

		//Node->m_Next = Next;
		//Next->m_Prev = Node;

		//Node->m_Prev = iter.m_Node;
		//iter.m_Node->m_Next = Node;
		Prev->m_Next = Node;
		Node->m_Prev = Prev;
		
		Node->m_Next = iter.m_Node;
		iter.m_Node->m_Prev = Node;

		m_Size++;
	}

	void erase(ITR& iter)
	{
		assert(m_Size);

		NODE* Prev = iter.m_Node->m_Prev;
		NODE* Next = iter.m_Node->m_Next;

		Next->m_Prev = Prev;
		Prev->m_Next = Next;

		delete iter.m_Node;
		
		iter.m_Node = Next;

		m_Size--;
	}

	void clear()
	{
		NODE* DelNode = m_Begin->m_Next;

		while (DelNode != m_End)
		{
			NODE* Next = DelNode->m_Next;
			delete DelNode;
			DelNode = Next;
		}

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;
		m_Size = 0;
	}
};
