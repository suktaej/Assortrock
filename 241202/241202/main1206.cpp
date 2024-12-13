#include<iostream>

int gNumber = 1000;
//프로그램 시작 시 메모리 생성
//프로그램 종료 시 메모리 제거
int main()
{
	int Number = 100;
	int Number1 = 200;
	int* pNumber = &Number;
	int* pNumber1 = pNumber;
	//동일한 포인터까리는 대입 가능
	
	//int** ppNumber = &Number;
	int** ppNumber = &pNumber;

	//pNumber는 Number 변수의 메모리 주소를 가짐
	//역참조로 Number변수의 값을 변경 가능
	*pNumber = 500;

	//ppNumber는 pNumber 포인터 변수의 메모리 주소를 가짐
	//역참조로 pNumber 포인터 변수가 가지고 있는 메모리 주소를 다른 주소로 변경가능
	*ppNumber = &Number1;
	
	std::cout << "Number =" << Number << std::endl;
	std::cout << "Number1 =" << Number1 << std::endl;
	
	std::cout << "Number Addr=" << &Number << std::endl;
	std::cout << "Number1 Addr=" << &Number1 << std::endl;

	std::cout << "pNumber =" << pNumber << std::endl;
	std::cout << "*pNumber =" << *pNumber << std::endl;
	std::cout << "pNumber Addr =" << &pNumber << std::endl;

	std::cout << "ppNumber =" << ppNumber << std::endl;
	std::cout << "*ppNumber =" << *ppNumber << std::endl;
	std::cout << "**ppNumber =" << **ppNumber << std::endl;
	std::cout << "ppNumber Addr =" << &ppNumber << std::endl;

	return 0;
}