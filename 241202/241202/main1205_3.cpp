#include<iostream>

struct FMonster
{
	char Name[32];
	int Level;
	int Attack;
	int HP;
};

void changenumber(int* num) //포인터를 통한 함수 내 변경
{
	*num += 100;
}

int* GetInt() //댕글링 포인터 테스트
{
	int FuncInt = 100;
	return &FuncInt;
}

int main()
{
	int num = 100;
	int* pnum = &num;

	float fnum = 10.f;
	float* pfnum = &fnum;

	//int* pnum = &fnum;
	//타입 불일치

	void* pvnum = &num;
	pvnum = &fnum;
	//void 포인터의 경우는 예외
	std::cout << "pnum:" << *pnum << std::endl;
	*pnum = 200;
	std::cout << "pnum의 역참조:" << *pnum << std::endl;
	changenumber(pnum);
	std::cout << "pnum의 함수전달:" << *pnum<<std::endl;
	//포인터 변수가 가지고 있는 주소(&num)의 값(num=100)을 출력

	int* funcnum = GetInt();
	std::cout << funcnum << std::endl;
	*funcnum = 1111;
	std::cout << *funcnum << std::endl;
	//함수가 호출될 때 메모리 생성, 함수 종료 시 메모리 제거
	//함수가 종료될 때 반환된 주소는 이미 제거된 메모리
	//제거된 메모리에 역참조 시도 시 문제 발생
	//댕글링 포인터:메모리가 제거된 주소를 가지고 있는 포인터

	int Array[10] = {};
	Array[2] = 5000;

	std::cout << Array[2] << std::endl;
	//배열 이름은 배열의 시작주소
	//포인터 변수에 배열의 시작주소를 저장

	int* pArray = Array;
	*(pArray + 2) = 3000;
	std::cout << Array[2] << std::endl;

	FMonster monster;
	FMonster* pMonster = &monster;

	//*pMonster.Level = 300;
	// 연산자는 우선순위가 존재
	// '.' 또한 역참조
	(*pMonster).Level = 300;
	std::cout << pMonster->Level << std::endl;
	pMonster->Level = 500;
	std::cout << monster.Level << std::endl;
	//일반변수의 경우 역참조, 값 대입을 위함


	return 0;
}
