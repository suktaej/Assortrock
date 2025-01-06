#pragma once
#include "Array.h"

template<typename T>
class CHeap
{
public:
	CHeap() {}
	~CHeap() {}
private:
	CArray<T> m_Array;
	//타입이 클래스나 구조체일 경우를 대비
	//2개의 인자를 비교하여 반환값을 받는 함수포인터
	//정렬순서를 정하기 위한 반환값(최대힙, 최소힙)
	bool (*m_Func)(const T&, const T&) = nullptr;
private:
	void insert(int ParentIndex, int CurrentIndex)
	{
		//배열이므로 0이 root
		if (ParentIndex < 0)
			return;

		if (m_Func(m_Array[ParentIndex],
			m_Array[CurrentIndex]))
		{
			T Temp = m_Array[ParentIndex];
			m_Array[ParentIndex] = m_Array[CurrentIndex];
			m_Array[CurrentIndex] = Temp;
			
			//재귀
			insert((ParentIndex + 1) / 2 - 1,
				ParentIndex);
			//insert((ParentIndex - 1) / 2,
			//	ParentIndex);
		}
	}

	void erase(int CurrentIndex)
	{
		int Count = m_Array.size();
		int LeftChild = CurrentIndex*2+1;
		int RightChild = CurrentIndex*2+2;
		
		//자식노드가 없을 경우
		if (LeftChild >= Count)
			return;

		int ChildIndex = LeftChild;

		if (RightChild < Count)
		{
			if (m_Func(m_Array[LeftChild], m_Array[RightChild]))
				ChildIndex = RightChild;
		}

		if (m_Func(m_Array[CurrentIndex], m_Array[ChildIndex]))
		{
			T Temp = m_Array[ChildIndex];
			m_Array[ChildIndex] = m_Array[CurrentIndex];
			m_Array[CurrentIndex] = Temp;

			erase(ChildIndex);
		}
	}

public:
	//함수포인터 호출용 함수
	void SetSortFunction(bool(*Func)(const T&, const T&)) { m_Func = Func; }
	void insert(const T& Data)
	{
		//SetSortFunction이 지정되었을 때만 실행
		//정렬순서(최대힙,최소힙)가 정해져야만 하기 때문
		if (!m_Func)
			return;

		m_Array.push_back(Data);
		insert(m_Array.size() / 2 - 1, 
			m_Array.size() - 1);
		//insert(((m_Array.size() - 1) - 1) / 2,
		//	m_Array.size() - 1);
	}

	void insert(const T* Array, int Count)
	{
		for (int i = 0;i < Count;i++)
		{
			m_Array.push_back(Array[i]);

			insert(m_Array.size() / 2 - 1,
				m_Array.size() - 1);
			//insert(((m_Array.size() - 1) - 1) / 2,
			//	m_Array.size() - 1);
		}
	}

	const T& front() { return m_Array[0]; }
	int size() const { return m_Array.size(); }
	bool empty() const { return m_Array.empty(); }

	void pop()
	{
		m_Array[0] = m_Array[m_Array.size()-1];
		m_Array.pop_back();
		erase(0);
	}
};

