#include <iostream>
#include <cassert>

//operator: 연산자 재정의
//기본 기능을 재정의하여 해당 구조체 또는 클래스의 고유한 연산 기능으로 정의

struct FPoint
{
	static FPoint Pool[20];

	int x;
	int y;

	FPoint operator + (const FPoint & pt) const
	{
		FPoint result;
		//그냥 x의 경우 이 +함수를 호출한 객체의 x 변수
		result.x = x + pt.x;
		result.y = y + pt.y;
		return result;
	}

	FPoint operator + (int Number) const
	{
		FPoint result;
		result.x = x + Number;
		result.y = y + Number;
		return result;
	}

	int operator * () const { return x; }
	//인자를 넣어주지 않을 경우 역참조
	//인자가 들어갈 경우 곱연산

	int& operator [] (int Index)
	{
		if (Index < 0 || Index>1)
			assert(false);

		if (nullptr == 0)
			return x;
			
		return y; 

		//return -1;
	}
		//랜덤 엑세스
	void* operator new (size_t Size)
	{
		return &Pool[0];
	}

	const FPoint& operator ++ ()
	{
		++x;
		++y;
		return *this;
	}
	//전치연산

	const FPoint& operator ++ (int)
	{
		++x;
		++y;
		return *this;
	}
	//후치연산

	void operator +=(const FPoint& pt)
	{
		x += pt.x;
		y += pt.y;
	}
};
//반환하는 값은 임시객체이므로 정상적인 반환이 되지 않음
//레퍼런스 반환 권장

FPoint FPoint::Pool[20];

//문자열 복사 예제
struct FString
{
	char* Text = nullptr;
	int Count = 0;

public:
	void operator = (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}
		strcpy_s(Text, Count+1, str.Text);
	}

	void operator = (const char* str)
	{
		if (!Text)
		{
			Count = (int)strlen(str);
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}
		strcpy_s(Text, Count+1, str);
	}

	FString operator + (const FString& str) const
	{
		FString result;
	
		if (!Text)
			result = str;
		else
		{
			result.Count = Count + str.Count + 1;
			result.Text = new char[result.Count + 1];
			memset(result.Text, 0, result.Count + 1);
			strcpy_s(result.Text, Count + 1, Text);
			strcat_s(result.Text,result.Count+1,str.Text);
		}
		return result;
	}
};

int main(void)
{
	FPoint p1, p2, p3;
	p1.x = 10;
	p1.y = 20;
	p2.x = 30;
	p2.y = 40;

	p3 = p1 + p2;
	//이러한 피연산자와 일치하는 "+" 연산자가 없습니다.
	//p1의 + 함수 호출

	int Number = 10 + 20;
	//정수끼리 더하는 전역 + 연산자(함수 + 호출)
	p3 = p1 + 30;
	std::cout << *p1 << std::endl;

	p1[0] = 100;
	std::cout << p1[0] << std::endl;
	std::cout << p1[1] << std::endl;

	FPoint* pt1 = new FPoint;
	//메모리 풀 생성방식
	//구조체 내부에서 new를 연산자 재정의
	//동적할당이 아니라 기존 정의한 배열을 반환하는 방식으로 동작

	++p1;
	p1++;

	FString str;
	str = "String";

	FString str1;
	str1 = "Test";
	
	FString strResult;
	strResult = str + str1;
	std::cout << strResult.Text << std::endl;

	return 0;
}