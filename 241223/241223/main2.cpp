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
public:
	FString():Text(nullptr),Count(0) {}
	//일반 생성자 초기화
	FString(const char* _Text)
	{
		Count = (int)strlen(_Text);
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);
		strcpy_s(Text, Count + 1, _Text);
	}
	//문자열 초기화
	FString(const FString& str)
	{
		Count = str.Count;
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);
		strcpy_s(Text, Count + 1, str.Text);
	}
	//복사생성자 초기화
	FString(FString&& str)
	{
		Count = str.Count;
		Text = str.Text;
		//얕은 복사(rvalue type에 대한 참조를 하고 있음)
		str.Text = nullptr;
		//메모리 이동
	}
	//이동생성자의 필요성
	//임시객체의 메모리 주소를 대입받은 객체의 메모리로 복사
	//속도측면에서 빠름
	
	~FString() 
	{
		if (nullptr != Text)
			delete[] Text;
	}

private:
	char* Text;
	int Count;

public:
	char* GetChar() { return Text; }
	void operator = (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}
		//초기 문자열이 없을 경우 메모리 초기화 및 동적할당
		else
		{
			if (Count < str.Count)
			{
				delete[] Text;
				Count = str.Count;
				Text = new char[Count + 1];
				memset(Text, 0, Count + 1);
			}
			//새로 입력된 문자열 길이가 기존보다 길 경우
			//기존 문자열을 제거 후 재할당
		}
		strcpy_s(Text, str.Count+1, str.Text);
	}

	void operator = (const char* str)
	{
		int Length = (int)strlen(str);
		if (!Text)
		{
			Count = Length;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
		}

		else
		{
			if (Count < Length)
			{
				delete[] Text;
				Count = Length;
				Text = new char[Count + 1];
				memset(Text, 0, Count + 1);
			}
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

	FString operator + (const char* str) const
	{
		FString result;
	
		if (!Text)
			result = str;
		else
		{
			int Length = (int)strlen(str);
			result.Count = Count + Length+1;
			result.Text = new char[result.Count + 1];
			memset(result.Text, 0, result.Count + 1);
			strcpy_s(result.Text, Count + 1, Text);
			strcat_s(result.Text,result.Count+1,str);
		}
		return result;
	}

	void operator += (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);
			strcpy_s(Text, Count + 1, str.Text);
		}
		else
		{
			int Length = Count + str.Count + 1;
			char* _Text = new char[Length];
			memset(_Text, 0, Length);
			//strcpy_s(_Text, Length, Text);
			strcpy_s(_Text, Count + 1, Text);
			strcat_s(_Text, Length, str.Text);
			//두번째 인자의 경우 원본 문자열 길이+추가 문자열 길이가 아님
			//버퍼(배열)크기(위의 경우 Length)를 기준으로 동작

			delete[] Text;
			//기존 문자열 제거
			Count = Length - 1;
			Text = _Text;
			//결과 문자열의 주소를 기존 문자열에 대입
		}
	}

	bool operator == (const FString& str)	const
	{ return strcmp(Text, str.Text) == 0; }

	bool operator == (const char* str)	const
	{ return strcmp(Text, str) == 0; }

	bool operator != (const FString& str)	const
	{ return strcmp(Text, str.Text) != 0; }

	bool operator != (const char* str)	const
	{ return strcmp(Text, str) != 0; }

	const char* operator * ()	const
	{ return Text; }

	int Length() { return Count; }

	FString Split(const char* str)
	{
		char* Context = nullptr;
		char* Left = strtok_s(Text, str, &Context);

		Count = (int)strlen(Context);
		//잘리고 남은 문자열의 길이
		char* _Text = new char[Count + 1];
		memset(_Text, 0, Count + 1);
		strcpy_s(_Text, Count + 1, Context);
		//남은 문자열 시작주소 복사

		FString result = Left;
		//자른 문자열 반환
		delete[] Text;
		//기존 문자열 삭세
		Text = _Text;
		//남은 문자열 주소를 기존 문자열 주소에 저장

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

	FString str = "Copy";
	str = "String";
	str = "Split";

	FString str1;
	str1 = ": Test";
	
	FString strResult;
	strResult = str + str1;
	//std::cout << strResult.Text << std::endl;
	FString str2 = "New String";
	//생성자로 초기화
	FString str3 = str2;
	//복사생성자로 초기화

	FString("temp obj");
	//임시객체는 생성과 동시에 제거

	//FString str4 = FString("temp obj");
	//임시객체 최적화로 자동할당
	//임시객체가 제거되지 않고 참조로 인식됨
	//임시객체를 대입. 이동생성자 방식으로 메모리 이동이 일어남
	//str4가 제거될 때, 임시객체가 제거된 것과 같음

	FString str4 = std::move(FString("temp obj"));
	//강제 이동생성자
	
	std::cout << strResult.Split(":").GetChar();
	
	return 0;
}