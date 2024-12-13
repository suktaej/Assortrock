#include <iostream>
#include <time.h>

enum EJob
{
	Job_None,
	Job_Knight,
	Job_Archer,
	Job_Magicion
};

enum class EItemType
{
	Weapon,
	Armor,
	Etc
};
//0부터 시작(None = 0, Knight =1 ...)

void Func1(unsigned int& Reinf);
void Func2(unsigned int& Reinf, float Pcnt, float Succ_pcnt);

int main()
{
	srand(time(0));

	unsigned int Reinf = 4;
	char temp = 'a';

	while (1)
	{
		std::cin >> temp;
		Func1(Reinf);
	}
	return 0;
}

void Func1(unsigned int& Reinf)
{
	float Pcnt = rand() % 10001 * 0.01f;

	if (Reinf >= 0 && Reinf <= 3) {
		Reinf++;
		std::cout << "(Success)Level:" << Reinf << std::endl;
	}
	else if (Reinf >= 4 && Reinf <= 6) { Func2(Reinf, Pcnt, 50.f); }
	else if (Reinf >= 7 && Reinf <= 9) { Func2(Reinf, Pcnt, 20.f); }
	else if (Reinf >= 10 && Reinf <= 12) { Func2(Reinf, Pcnt, 2.f); }
	else if (Reinf >= 13) { Func2(Reinf, Pcnt, 0.7f); }
}

void Func2(unsigned int& Reinf, float Pcnt, float Succ_pcnt)
{
	std::cout << "Success Rate:" << Succ_pcnt <<"%" << std::endl;
	std::cout << "Percent:"<< Pcnt << "%" << std::endl;
	if (Pcnt <= Succ_pcnt)
	{
		Reinf++;
		std::cout << "(Success)Level:" << Reinf << std::endl;
	}
	else
	{
		std::cout << "(Fail)Level:" << Reinf << std::endl;
	}
} 