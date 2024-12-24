#pragma once
#include <memory.h>
#include <assert.h>

template <typename T>
class CArray
{
public:
	CArray() {};
	CArray(const CArray<T>& Arr) {};
	//Ŭ���� ��ü�� ������ �� ����� Ÿ��(T)
	//���������
	CArray(CArray<T>&& Arr) {};
	//�̵�������
	~CArray() 
	{
		if (nullptr != mArray)
			delete[] mArray;
	};
private:
	T* mArray = nullptr;
	//Ÿ�Կ� ���� �����迭
	int mSize = 0;
	int mCapacity = 0;
	//ó������ �����迭�� �������� ����
private:
	//���� �޸� ���Ҵ�
	void ReAlloc(int NewCapacity)
	{
		mCapacity = NewCapacity;
		T* Array = new T[mCapacity+2];
		//���� �����Ͱ� ���� ��� ����
		//begin�� end�� ǥ���ϱ� ���� ���������� �ʿ�(+2)
		if (nullptr != mArray)
		{
			//���� �����͸� ������ �� 1������ ���� ��ŭ ����
			memcpy(Array+1, mArray+1, sizeof(T) * mSize);
			delete[] mArray;
		}
		mArray = Array;
	}
public:
	void push_back(const T& Data)
	{
		//1. �迭�� ��� �Ҵ�Ǿ����� Ȯ��
		if (mCapacity == mSize)
		{
			//1-1. mArray�� nullptr�� ���(�迭�� ����)
			//1-2. mArray�� ���� ������ ���� ���(�迭�� ������)
			if (nullptr == mArray)
				ReAlloc(1);
			else
			{ 
				int NewCapacity = (int)(mCapacity + 1.5f);
				if (NewCapacity == 1)
					NewCapacity = 2;

				ReAlloc(NewCapacity);
			}	
		}
		mArray[mSize+1] = Data;
		//+1�� ���� Ȯ��
		mSize++;
	}

	void push_back(T&& Data)
	{	
		//�迭�� á���� Ȯ��
		if (mCapacity == mSize)
		{
			if (nullptr == mArray)
				ReAlloc(1);
			else
			{
				int NewCapacity = (int)(mCapacity + 1.5f);
				if (NewCapacity == 1)
					NewCapacity = 2;

				ReAlloc(NewCapacity);
			}
		}
		mArray[mSize+1] = Data;
		mSize++;
	}

	void pop_back()
	{
		assert(mSize!=0);
		//�ڿ� �ƹ��͵� ���ٴ� ���� Ȯ��
		--mSize;
	}

	bool empty() const { return mSize == 0; }

	int size() const { retrun mSize; }

	int capacity() const { return mCapacity; }

	//�迭�� ������ ���ϴ� ��ŭ �Ҵ�
	//���� capacity���� ���� ���ڸ� ���� ��� �ƹ��� ������ ���� ����
	//Ŭ ��� ���� size�� ����. capacity�� ������ ũ��� ����
	//���� ��ҵ��� ������ ��� ���� ����
	void reserve(int NewCapacity)
	{
		if (NewCapacity > mCapacity)
			ReAlloc(new);
	}
	//���� �� �ƴ϶� �߰��� ��ҵ� ���� ��ŭ �Ҵ�
	//�߰��� ��Ҵ� �⺻��(0)���� �ʱ�ȭ
	//���� capacity���� ���� ���ڸ� ���� ��� capacity�� ������ ä, size�� ����
	//Ŭ ��쿡�� capacity�� ����
	//���� ��ҵ��� ������ ��� ���� ����
	void resize(int NewCapacity)
	{
//		if (NewCapacity < mCapacity) 
//		{
//			//int Count = mSize - NewCapacity;
//			//memset(TestArr,0,sizeof(CTestClass);
//			//�����Լ��� ������ ��ӹ޴� Ŭ���� ��� �� �Ϲ� ��ü���� ������ �߻�
//			//�����Լ� ���̺��� �ּұ��� ������ �� ����
//			mSize = NewCapacity;
//			//���� �� �߰� �� ������ �����
//		}
//		else if(NewCapacity > mCapacity)
//		{
//			ReAlloc(NewCapacity);
//			mSize = NewCapacity;
//		}
		if (NewCapacity > mCapacity)
			ReAlloc(NewCapacity);

		mSize = NewCapacity;
	}

	T& operator[] (int Index)
	{
		assert(0 <= Index && Index < mSize);
		return mArray[Index + 1];
	}
};

