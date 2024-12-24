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
	//index를 사용해서 직접적으로 배열에 접근
public:
	T& operator*()
	{
		return mArray->mArray[mIndex];
	}
	//시작주소와 개수를 알고 있을필요가 있음
	//size, reserve, push_back 등으로 begin, end 등의 위치가 달라질 수 있기 때문
	//더욱이 크기의 재할당이 일어날 경우 오류가 커질 수 있음
	//기존의 배열을 제거해버리기 때문에 메모리 주소가 달라지기 때문
	void operator++()
	{
		//.end까지만 허용
		//size 변경 시 .end의 범위도 달라질 수 있음
		//외부 객체에서 size를 가져올 수 있어야 함
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
	//inner 클래스'처럼' 사용하는 방법
public:
	CArray() {};
	CArray(const CArray<T>& Arr) {};
	//클래스 객체를 생성할 때 사용한 타입(T)
	//복사생성자
	CArray(CArray<T>&& Arr) {};
	//이동생성자
	~CArray() 
	{
		if (nullptr != mArray)
			delete[] mArray;
	};
private:
	T* mArray = nullptr;
	//타입에 대한 동적배열
	int mSize = 0;
	int mCapacity = 0;
	//처음에는 동적배열을 생성하지 않음
private:
	//실제 메모리 재할당
	void ReAlloc(int NewCapacity)
	{
		mCapacity = NewCapacity;
		T* Array = new T[mCapacity+2];
		//기존 데이터가 있을 경우 유지
		//begin과 end를 표현하기 위한 여유공간이 필요(+2)
		if (nullptr != mArray)
		{
			//기존 데이터를 복제할 때 1번부터 개수 만큼 복제
			memcpy(Array+1, mArray+1, sizeof(T) * mSize);
			delete[] mArray;
		}
		mArray = Array;
	}
public:
	void push_back(const T& Data)
	{
		//1. 배열이 모두 할당되었는지 확인
		if (mCapacity == mSize)
		{
			//1-1. mArray가 nullptr인 경우(배열이 없음)
			//1-2. mArray가 값을 가지고 있을 경우(배열이 생성됨)
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
		//+1의 이유 확인
		mSize++;
	}

	void push_back(T&& Data)
	{	
		//배열이 찼는지 확인
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
		//뒤에 아무것도 없다는 것을 확인
		--mSize;
	}

	bool empty() const { return mSize == 0; }

	int size() const { retrun mSize; }

	int capacity() const { return mCapacity; }

	//배열의 공간을 원하는 만큼 할당
	//기존 capacity보다 작은 인자를 받을 경우 아무런 동작을 하지 않음
	//클 경우 기존 size는 유지. capacity만 지정된 크기로 증가
	//기존 요소들이 존재할 경우 값을 유지
	void reserve(int NewCapacity)
	{
		if (NewCapacity > mCapacity)
			ReAlloc(new);
	}
	//공간 뿐 아니라 추가된 요소도 인자 만큼 할당
	//추가된 요소는 기본값(0)으로 초기화
	//기존 capacity보다 작은 인자를 받을 경우 capacity는 유지한 채, size만 감소
	//클 경우에는 capacity만 증가
	//기존 요소들이 존재할 경우 값을 유지
	void resize(int NewCapacity)
	{
//		if (NewCapacity < mCapacity) 
//		{
//			//int Count = mSize - NewCapacity;
//			//memset(TestArr,0,sizeof(CTestClass);
//			//가상함수를 가지는 상속받는 클래스 사용 시 일반 객체에서 문제가 발생
//			//가상함수 테이블의 주소까지 삭제될 수 있음
//			mSize = NewCapacity;
//			//선언 후 추가 시 내용을 덮어쓴다
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
		//잘못된 index에 대한 처리 시 assert처리
		//end까지 처리
		assert((iter.mIndex < mSize + 1 && iter.mIndex >= 1));
	
		//1.반복으로 구현
		for (int i = iter.mIndex;i < mSize;i++)
			mArray[i] = mArray[i + 1];
		--mSize;
	
		//2.memcpy로 구현(복사에 복사로 swap)

		return iter;
	}
};

class CInner1 {};
class COuter1 
{
};
