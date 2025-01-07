#pragma once
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
//public:
	T m_Data;
	CNode* m_Prev = nullptr;
	CNode* m_Next = nullptr;
};

template<typename T>
class CIterator
{
	template<typename T>
	friend class CLinkedList;
public:
	CIterator() {}
	~CIterator() {}
//public:
private:
	CNode<T>* m_Node;
public:
	bool operator==(const CIterator<T>& iter)
	{ return m_Node == iter.m_Node; }
	bool operator!=(const CIterator<T>& iter)
	{ return m_Node != iter.m_Node; }
	T operator*()
	{ return m_Node->m_Data; }
	CIterator<T>& operator++()
	{
		m_Node = m_Node->m_Next;
		return *this;
	}
	CIterator<T>& operator++(int)
	{
		m_Node = m_Node->m_Next;
		return *this;
	}
	CIterator<T>& operator--()
	{
		m_Node = m_Node->m_Prev;
		return *this;
	}
	CIterator<T>& operator--(int)
	{
		m_Node = m_Node->m_Prev;
		return *this;
	}
};

template<typename T>
class CLinkedList
{
public:
	CLinkedList() 
	{
		m_Begin = new CNode<T>;
		m_End = new CNode<T>;

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
	CNode<T>* m_Begin = nullptr;
	CNode<T>* m_End = nullptr;

public:
	void push_back(const T& Data)
	{
		CNode<T>* Node = new CNode<T>;
		CNode<T>* PrevNode = m_End->m_Prev;

		Node->m_Data = Data;
		
		Node->m_Prev = PrevNode;
		Node->m_Next = m_End;
		
		m_End->m_Prev = Node;
		PrevNode->m_Next = Node;
		
		m_Size++;
	}
	void push_front(const T& Data)
	{ 
		CNode<T>* Node = new CNode<T>;
		CNode<T>* NextNode = m_Begin->m_Next;

		Node->m_Data = Data;

		Node->m_Prev = m_Begin;
		Node->m_Next = NextNode;
		
		m_Begin->m_Next = Node;
		NextNode->m_Next = Node;
		
		m_Size++;
	}

	void pop_back()
	{
		CNode<T>* Node = m_End->m_Prev;
		CNode<T>* PrevNode = Node->m_Prev;

		PrevNode->m_Next = m_End;
		m_End->m_Prev = PrevNode;

		delete Node;
	}
	void pop_front()
	{
		CNode<T>* Node = m_Begin->m_Next;
		CNode<T>* NextNode = Node->m_Next;

		NextNode->m_Prev = m_Begin;
		m_Begin->m_Next = NextNode;

		delete Node;
	}
	void size() { return m_Size; }

	void empty() { return m_Size == 0; }

	CIterator<T> begin() 
	{	
		CIterator<T> iter;
		iter.m_Node = m_Begin->m_Next;

		return iter;
	}

	CIterator<T> end()
	{
		CIterator<T> iter;
		iter.m_Node = m_End;

		return iter;
	}

	void insert(const T& Data, const CIterator<T>& iter)
	{
		CNode<T>* Node = new CNode<T>;

		Node->m_Data = Data;

		iter.m_Node->m_Next->m_Prev = Node;	
		Node->m_Next = iter.m_Node->m_Next;

		iter.m_Node->m_Next = Node;
		Node->m_Prev = iter.m_Node;

		m_Size++;
	}

	CIterator<T> erase(const CIterator<T>& iter)
	{
		if (m_Size == 0)
			return end();

		CNode<T>* Prev = iter.m_Node->m_Prev;
		CNode<T>* Next = iter.m_Node->m_Next;

		Prev->m_Next = Next;
		Next->m_Prev = Prev;

		delete iter.m_Node;

		m_Size--;

		CIterator<T> result;
		result.m_Node = Next;
		return result;
	}

	void clear()
	{
		CNode<T>* DelNode = m_Begin->m_Next;

		while (DelNode != m_End)
		{
			CNode<T>* Next = DelNode->m_Next;
			delete DelNode;
			DelNode = Next;
		}
		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;
		m_Size = 0;
	}
};

