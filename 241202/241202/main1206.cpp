#include<iostream>

int gNumber = 1000;
//���α׷� ���� �� �޸� ����
//���α׷� ���� �� �޸� ����
int main()
{
	int Number = 100;
	int Number1 = 200;
	int* pNumber = &Number;
	int* pNumber1 = pNumber;
	//������ �����ͱ�� ���� ����
	
	//int** ppNumber = &Number;
	int** ppNumber = &pNumber;

	//pNumber�� Number ������ �޸� �ּҸ� ����
	//�������� Number������ ���� ���� ����
	*pNumber = 500;

	//ppNumber�� pNumber ������ ������ �޸� �ּҸ� ����
	//�������� pNumber ������ ������ ������ �ִ� �޸� �ּҸ� �ٸ� �ּҷ� ���氡��
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