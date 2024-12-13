#include <iostream>
#include <bitset>
#include <time.h>

int main(void)
{
	std::cout << "Hello world!"<< std::endl;

	char Text = 'a';
	int cast_int = 10;

	float float_num = 3.14f;
	printf("float number = %.3f", float_num);

	cast_int = float_num;
	std::cout << cast_int << std::endl; //float의 int형 자동 형변환, 
										//소수점 이하 생략되는 문제 있음

	int num2 = 1234567;
	float num3 = 1234567.0f;

	int Buf = 0;
	const int Attack = 0x1;		//1
	const int Defense = 0x2;	//10
	const int HP = 0x4;			//100
	const int MP = 0x8;			//1000
	const int Speed = 0x10;		//10000

	//Buf는 0이다.
	//Buf = 0 | 1 =1
	Buf = Buf | Attack;

	//Buf = 001 | 100 = 101 = 5
	Buf = Buf | HP;

	//Buf = 00101 | 10000 = 10101
	Buf = Buf | Speed;

	//Buf = 10101 ^ 00100 = 10001
	Buf = Buf ^ HP; //toggle 방식으로 사용 가능
	//Buf = 10001 ^ 00100 = 10001
	Buf = Buf ^ HP;

	std::cout << "Attack=" << (Buf & Attack) << std::endl;
	std::cout << "Defense=" << (Buf & Defense) << std::endl;
	std::cout << "HP=" << (Buf & HP) << std::endl;
	std::cout << "MP=" << (Buf & MP) << std::endl;
	std::cout << "Speed=" << (Buf & Speed) << std::endl;

	unsigned int Color = 0;
	unsigned char r = 255;
	unsigned char g = 80;
	unsigned char b = 102;
	unsigned char a = 37;

	Color = a;
	Color = Color << 8;
	Color = Color | r;

	Color = Color << 8;
	Color = Color | g;

	Color = Color << 8;
	Color = Color | b;

	std::cout << Color << std::endl;
	
	std::cout << std::bitset<8>(0xff) << std::endl;
	std::cout << "b=" << (Color & 0xff) << std::endl;
	std::cout << "g=" << ((Color>>8) & 0xff) << std::endl;
	std::cout << "r=" << ((Color>>16) & 0xff) << std::endl;
	std::cout << "a=" << ((Color>>24) & 0xff) << std::endl;

	srand(time(0));
	rand();
	std::cout << "time:"<<time(0) << std::endl;
	std::cout << "random:"<< rand() << std::endl;
	//rand() : C++에서 난수를 발생시키는 함수

	return 0;
} 