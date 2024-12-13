#include<iostream>

void OutputText(const char* Text);

int main()
{
	//포인터 연산
	//포인터 변수 타입의 메모리 크기만큼 증가,감소
	int Array[10] = {};
	int* pArray = Array;
	bool* pArrayb = (bool*)Array;

	*pArray = 500;
	*(pArray + 2) = 100;

	std::cout << pArray << std::endl;
	std::cout << pArray + 1 << std::endl;
	std::cout << pArray + 2 << std::endl;

	std::cout << pArrayb + 1 << std::endl;
	std::cout << pArrayb + 2 << std::endl;

	std::cout << pArray[2] << std::endl;
	std::cout << *(pArray + 2) << std::endl;

	int Number = 100;
	int Number1 = 200;
	int* pNumber = &Number;

	*pNumber = 111;
	pNumber = &Number1;
	*pNumber = 222;

	const int* cpNumber = &Number;
	//변수타입 왼쪽에 const가 붙을 경우 참조대상의 "값"을 변경 불가
	//*cpNumber = 333;
	cpNumber = &Number1;
	//참조 대상을 변경하는 것은 가능

	int* const pcNumber = &Number;
	*pcNumber = 12345;
	//pcNumber = &Number1;
	//변수타입 오른쪽에 const가 붙을 경우 참조대상을 변경 불가

	const int* const cpcNumber = &Number;
	//값을 읽어올 수만 있음

	//char* Text = "String";
	const char* Text = "String";
	//문자열 리터럴의 경우 const char
	OutputText("String Print!");

	int* PointerArray[10] = {};
	//pointer의 경우는 메모리를 참고하므로 x64 기준으로 8byte의 값을 보유
	std::cout << PointerArray << std::endl;
	std::cout << PointerArray + 1 << std::endl;
	//8byte 단위로 증가
	return 0;
}

void OutputText(const char* Text)
{
	std::cout << Text << std::endl;
}