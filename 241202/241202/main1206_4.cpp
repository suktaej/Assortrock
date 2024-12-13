#include<iostream>

void Output()
{
	std::cout << "Output Function" << std::endl;
}


void Output1()
{
	std::cout << "Output Function1" << std::endl;

}
//함수의 형태는 반환타입과 인자로 결정됨
//Output function과 Output1 function은 같은 형식의 함수

int Add(int num1, int num2) { return num1 + num2; }
int Minus(int num1, int num2) {return num1 - num2;}
//Add와 Minus 함수 역시 동일한 타입의 함수

int main(void)
{
	std::cout << Output << std::endl;
	//함수의 이름은 함수의 메모리 주소를 나타냄
	Output();
	//함수주소();

	//함수포인터: 함수의 주소를 저장하기 위한 변수
	//함수의 형태는 반환타입과 인자로 결정됨
	//반환타입(*함수명)(인자)로 선언
	void(*FuncPointer)();
	//return type이 void, parameter가 없는 모든 함수의 주소를 저장 가능
	FuncPointer = Output;
	FuncPointer(); //호출

	FuncPointer = Output1;
	FuncPointer();

	int(*FuncInt)(int, int);
	//return type이 int, parameter가 int, int 로 들어오는 모든 함수 주소 저장 가능
	FuncInt = Add;
	std::cout << FuncInt(20, 10) << std::endl;
	FuncInt = Minus;
	std::cout << FuncInt(20, 10) << std::endl;
	
	int(*FuncArr[2])(int, int);
	//함수 포인터 배열
	FuncArr[0] = Add;
	FuncArr[1] = Minus;
	for (int i = 0;i < 2;i++)
		std::cout << FuncArr[i](20, 10) << std::endl;

	return 0;
}