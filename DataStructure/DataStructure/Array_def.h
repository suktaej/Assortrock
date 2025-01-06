#pragma once

#include <memory.h>
#include <assert.h>

template <typename T>
class CArrayIterator
{
	template <typename T>
	friend class CArray;

public:
	CArrayIterator()
	{
	}

	~CArrayIterator()
	{
	}

public:
	T& operator * ()
	{
		return mArray->mArray[mIndex];
	}

	void operator ++ ()
	{
		++mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	void operator ++ (int)
	{
		++mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	void operator -- ()
	{
		--mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	void operator -- (int)
	{
		--mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	CArrayIterator<T> operator + (int Num)	const
	{
		CArrayIterator<T>	iter;
		iter.mArray = mArray;
		iter.mIndex = mIndex + Num;
		assert((iter.mIndex <= mArray->mSize + 1 &&
			iter.mIndex >= 1));

		return iter;
	}

	CArrayIterator<T> operator - (int Num)	const
	{
		CArrayIterator<T>	iter;
		iter.mArray = mArray;
		iter.mIndex = mIndex - Num;
		assert((iter.mIndex <= mArray->mSize + 1 &&
			iter.mIndex >= 1));

		return iter;
	}

	const CArrayIterator<T>& operator += (int Num)
	{
		mIndex += Num;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));

		return *this;
	}

	const CArrayIterator<T>& operator -= (int Num)
	{
		mIndex -= Num;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));

		return *this;
	}

	// =, ->
	bool operator == (const CArrayIterator<T>& iter)	const
	{
		return mIndex == iter.mIndex;
	}

	bool operator != (const CArrayIterator<T>& iter)	const
	{
		return mIndex != iter.mIndex;
	}

private:
	int	mIndex = -1;
	CArray<T>* mArray;
	//T* mValue = nullptr;
};

template <typename T>
class CArray
{
	template <typename T>
	friend class CArrayIterator;

public:
	typedef CArrayIterator<T>	iterator;

public:
	CArray()
	{
	}

	CArray(const CArray<T>& Arr)
	{
	}

	CArray(CArray<T>&& Arr)
	{
	}

	~CArray()
	{
		if (nullptr != mArray)
			delete[] mArray;
	}

private:
	T* mArray = nullptr;
	int	mSize = 0;
	int	mCapacity = 0;

public:
	void push_back(const T& Data)
	{
		// 배열이 꽉 찼는지 판단한다.
		if (mCapacity == mSize)
		{
			if (nullptr == mArray)
			{
				ReAlloc(1);
			}

			else
			{
				int	NewCapacity = (int)(mCapacity * 1.5f);

				if (NewCapacity == 1)
					NewCapacity = 2;

				ReAlloc(NewCapacity);
			}
		}
		
		mArray[mSize + 1] = Data;
		++mSize;
	}

	void push_back(T&& Data)
	{
		// 배열이 꽉 찼는지 판단한다.
		if (mCapacity == mSize)
		{
			if (nullptr == mArray)
			{
				ReAlloc(1);
			}

			else
			{
				int	NewCapacity = (int)(mCapacity * 1.5f);

				if (NewCapacity == 1)
					NewCapacity = 2;

				ReAlloc(NewCapacity);
			}
		}

		mArray[mSize + 1] = Data;
		++mSize;
	}

	void pop_back()
	{
		assert(mSize != 0);

		--mSize;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	int size()	const
	{
		return mSize;
	}

	int capacity()	const
	{
		return mCapacity;
	}

	void clear()
	{
		mSize = 0;
	}

	// reserve는 기존 capacity보다 작게
	// 설정될 경우 아무런 일도 없다.
	// 클 경우 기존 사이즈는 그대로 유지하며
	// capacity만 지정된 크기로 늘어나서
	// 배열 크기만 이만큼 만들게 된다.
	// 기존의 값은 그대로 유지된다.
	void reserve(int NewCapacity)
	{
		if (NewCapacity > mCapacity)
		{
			ReAlloc(NewCapacity);
		}
	}

	// resize는 기존 capacity보다 작게
	// 설정될 경우 capacity는 유지하며
	// size만 감소시킨다.
	// 클 경우에는 capacity만 늘려준다.
	// 기존에 들어가있는 값이 있다면 유지한다.
	void resize(int NewCapacity)
	{
		/*if (NewCapacity < mCapacity)
		{
			mSize = NewCapacity;
		}*/

		if (NewCapacity > mCapacity)
		{
			ReAlloc(NewCapacity);
		}

		mSize = NewCapacity;
	}

	T& operator [] (int Index)
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index + 1];
	}

	iterator begin()
	{
		iterator	iter;
		iter.mArray = this;
		iter.mIndex = 1;
		return iter;
	}

	iterator end()
	{
		iterator	iter;
		iter.mArray = this;
		iter.mIndex = mSize + 1;
		return iter;
	}

	iterator erase(const iterator& iter)
	{
		assert((iter.mIndex < mSize + 1 &&
			iter.mIndex >= 1));

		for (int i = iter.mIndex; i < mSize; ++i)
		{
			mArray[i] = mArray[i + 1];
		}

		--mSize;

		return iter;
	}

private:
	void ReAlloc(int NewCapacity)
	{
		mCapacity = NewCapacity;
		// Begin과 End를 표현하기 위한
		// 여유공간 2개가 더 필요하다.
		T* Array = new T[mCapacity + 2];

		// 기존 데이터가 있을 경우 유지
		if (nullptr != mArray)
		{
			// 기존 데이터를 복제할 때 1번부터
			// 개수만큼 복제
			memcpy(Array + 1, mArray + 1,
				sizeof(T) * mSize);
			delete[] mArray;
		}

		mArray = Array;
	}
};

