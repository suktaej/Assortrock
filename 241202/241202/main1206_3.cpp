#include<iostream>

int Add(int num1,int num2=20)
{
	return num1 + num2;
}

int Add(int num)
{
	return num + 100;
}

int Factorial(int Num)
{
	if (Num == 1)
		return 1;

	return Num * Factorial(Num - 1);
}


int FactorialTail(int Result,int Number)
{
	if (Number == 1)
		return Result;

	return FactorialTail(Number*Result, Number-1);
}

int FactorialTail(int Number)
{
	return FactorialTail(0,Number);
}

int main()
{
	std::cout << Add(10, 20) << std::endl;
//	std::cout << Add(80) << std::endl;
	std::cout << Factorial(5) << std::endl;
	std::cout << FactorialTail(5) << std::endl;
	return 0;
}