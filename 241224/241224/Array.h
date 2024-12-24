#pragma once
#include <memory.h>
#include <assert.h>


template <typename T>
class CArrayIterator
{
	template<typename T>
	friend class CArray;
public:
	CArrayIterator() {};
	~CArrayIterator() {};
private:
	//T* mValue = nullptr;
	int mIndex = -1;
	CArray<T>* mArray;
	//index�� ����ؼ� ���������� �迭�� ����
public:
	T& operator*()
	{
		return mArray->mArray[mIndex];
	}
	//�����ּҿ� ������ �˰� �����ʿ䰡 ����
	//size, reserve, push_back ������ begin, end ���� ��ġ�� �޶��� �� �ֱ� ����
	//������ ũ���� ���Ҵ��� �Ͼ ��� ������ Ŀ�� �� ����
	//������ �迭�� �����ع����� ������ �޸� �ּҰ� �޶����� ����
	void operator++()
	{
		//.end������ ���
		//size ���� �� .end�� ������ �޶��� �� ����
		//�ܺ� ��ü���� size�� ������ �� �־�� ��
		++mValue;
		assert((mIndex <= mArray->mSize + 1 && mIndex >= 1));
		//.end(): mSize+1
	}

	void operator++(int)
	{
		++mValue;
		assert((mIndex <= mArray->mSize + 1 && mIndex >= 1));
	}

	bool operator==(const CArrayIterator<T>& iter)
	{
		return mIndex == iter.mIndex;
	}

	CArrayIterator<T> operator+(int Num) const
	{
		CArrayIterator<T> iter;
		iter.mArray = mArray;
		iter.mIndex = mIndex + Num;
		assert((iter.mIndex <= mArray->mSize + 1 && iter.mIndex >= 1));

		return iter;
	}
	
	const CArrayIterator<T>& operator+=(int Num) 
	{
		mIndex += Num;
		assert((mIndex <= mArray->mSize+1 && mIndex >= 1));
		return *this;
	}
};



template <typename T>
class CArray
{
	template <typename T>
	friend class CArrayIterator;
public:
	typedef CArrayIterator<T> iterator;
	//inner Ŭ����'ó��' ����ϴ� ���
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

	iterator begin()
	{
		iterator iter;
		iter.mArray = this;
		iter.mIndex = 1;
		return iter;
	}

	iterator end() 
	{
		iterator iter;
		iter.mArray = this;
		iter.mIndex = mSize + 1;
		return iter;
	}

	iterator erase(cosnt iterator& iter)
	{
		//�߸��� index�� ���� ó�� �� assertó��
		//end���� ó��
		assert((iter.mIndex < mSize + 1 && iter.mIndex >= 1));
	
		//1.�ݺ����� ����
		for (int i = iter.mIndex;i < mSize;i++)
			mArray[i] = mArray[i + 1];
		--mSize;
	
		//2.memcpy�� ����(���翡 ����� swap)

		return iter;
	}
};

class CInner1 {};
class COuter1 
{
};
