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
	//Ÿ���� Ŭ������ ����ü�� ��츦 ���
	//2���� ���ڸ� ���Ͽ� ��ȯ���� �޴� �Լ�������
	//���ļ����� ���ϱ� ���� ��ȯ��(�ִ���, �ּ���)
	bool (*m_Func)(const T&, const T&) = nullptr;
private:
	void insert(int ParentIndex, int CurrentIndex)
	{
		//�迭�̹Ƿ� 0�� root
		if (ParentIndex < 0)
			return;

		if (m_Func(m_Array[ParentIndex],
			m_Array[CurrentIndex]))
		{
			T Temp = m_Array[ParentIndex];
			m_Array[ParentIndex] = m_Array[CurrentIndex];
			m_Array[CurrentIndex] = Temp;
			
			//���
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
		
		//�ڽĳ�尡 ���� ���
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
	//�Լ������� ȣ��� �Լ�
	void SetSortFunction(bool(*Func)(const T&, const T&)) { m_Func = Func; }
	void insert(const T& Data)
	{
		//SetSortFunction�� �����Ǿ��� ���� ����
		//���ļ���(�ִ���,�ּ���)�� �������߸� �ϱ� ����
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

