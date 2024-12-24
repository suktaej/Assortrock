#pragma once
#include <memory.h>
#include <assert.h>

template <typename T>
class CArray
{
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
};

