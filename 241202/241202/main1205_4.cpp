#include<iostream>

void OutputText(const char* Text);

int main()
{
	//������ ����
	//������ ���� Ÿ���� �޸� ũ�⸸ŭ ����,����
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
	//����Ÿ�� ���ʿ� const�� ���� ��� ��������� "��"�� ���� �Ұ�
	//*cpNumber = 333;
	cpNumber = &Number1;
	//���� ����� �����ϴ� ���� ����

	int* const pcNumber = &Number;
	*pcNumber = 12345;
	//pcNumber = &Number1;
	//����Ÿ�� �����ʿ� const�� ���� ��� ��������� ���� �Ұ�

	const int* const cpcNumber = &Number;
	//���� �о�� ���� ����

	//char* Text = "String";
	const char* Text = "String";
	//���ڿ� ���ͷ��� ��� const char
	OutputText("String Print!");

	int* PointerArray[10] = {};
	//pointer�� ���� �޸𸮸� �����ϹǷ� x64 �������� 8byte�� ���� ����
	std::cout << PointerArray << std::endl;
	std::cout << PointerArray + 1 << std::endl;
	//8byte ������ ����
	return 0;
}

void OutputText(const char* Text)
{
	std::cout << Text << std::endl;
}