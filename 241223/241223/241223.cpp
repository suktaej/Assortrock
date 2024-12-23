#include <iostream>
#include <typeinfo>

template <typename T1, typename T2 = short>
//디폴트 타입
class Ccls
{
private:
	int i;
	float f;
	T1 temp1;
	T2 temp2;
public:
	void Output() const
	{
		std::cout << "T1:" << (typeid(T1).name) << std::endl;
		std::cout << "T2:" << (typeid(T2).name) << std::endl;
	}
};

class Ccls2
{
public:
	template<typename T3>
	void Output(T3 test) const
	{
		std::cout << "T3:" << typeid(T3).name << std::endl;
	}
};
//클래스 내 템플릿

class CObject {};
class CPlayer : CObject {};
class CMonster : CObject {};
class CItem :CObject {};

template <typename T>
T* CreateObject()
{
	T* Obj = new T;
	return Obj;
}

CPlayer* Player = CreateObject<CPlayer>();
CMonster* Monster = CreateObject<CMonster>();


template<int Number>
//인자를 사용하지 않았음에도 템플릿을 변수나 상수처럼 사용
void TestTypeTemplate1()
{
	//int Cnt = 100;
	//int Array[Cnt];
	//동적할당이 아닌 일반 배열의 경우 변수가 아닌 상수로 할당되어야 함
	int TempArray[Number];
	//비타입 템플릿 인자는 상수로 취급
	//컴파일 타임에 어떤 값이 들어갈 지 결정되기 때문에 상수로 취급
	std::cout << Number << std::endl; 
	
}

template<int Number = 1000>
void TestTypeTemplate2()
{ std::cout << Number << std::endl; }

template <typename T, int Number = 1000>
T* CreateArray()
{
	T* Array = new T[Number];
	return Array;
}

template <typename T>
void OutputType(T Test)
{
	std::cout << typeid(T).name() < std::endl;
}

//템플릿 특수화: 특정 타입만 다른 방식으로 처리하기 위해 사용되는 문법
//const char*같은 문장이 대표적 예시

template <typename T>
T Add(T num1 , T num2) { return num1 + num2; }

template <>
const char* Add(const char* num1, const char* num2)
{
	char Text[128] = {};
	memset(Text, 0, 256);

	strcpy_s(Text,256, num1);
	strcat_s(Text,256, num2);

	return Text;
}

int main(void)
{
	Ccls<int, float> test1;
	Ccls<int> test2;

	test1.Output();
	test2.Output();

	Ccls2 test3;
	test3.Output<int>(10);
	//클래스 내 템플릿 함수 사용법
	test3.Output(3.14f);
	//암시적 타입 지정 사용가능

	TestTypeTemplate1<300>();
	TestTypeTemplate2();
	//일반적인 경우 런타임에 스택을 생성하고 호출과 반환을 반복
	//템플릿의 경우 컴파일 타임에 이미 값이 입력되어 있음

	return 0;
}

