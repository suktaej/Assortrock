#include<iostream>

int* CreateDynamicInt()
{
	return new int;
}

//bool 타입으로 공간할당이 되었는지, 아닌지를 확인하는 방법
bool CreateDynamicInt1(int** Alloc)
{
	*Alloc = new int;
	return true;
}
//이중 포인터가 아니라 포인터를 인자로 받아올 경우...

bool CreateDynamicInt2(int*& Alloc)
{
	Alloc = new int;
	return true;
}

int main()
{
	//new int;
	//int형 메모리를 동적할당하고 주소를 반환
	//주소값을 반환 받을 변수가 존재할 필요가 있음
	int* IntAddr = new int;

	IntAddr = CreateDynamicInt();

	//new에서 할당한 int를 메모리에서 제거
	//할당을 제거하지 않을 경우 메모리 누수 발생(memory leak)
	delete IntAddr;

	CreateDynamicInt1(&IntAddr);
	delete IntAddr;

	CreateDynamicInt2(IntAddr);
	delete IntAddr;

	int* IntArrAddr = new int[10];
	//배열크기*변수형 바이트 만큼 동적할당을 하고 첫 주소를 반환
	delete[] IntArrAddr;
	//배열 할당 제거

	return 0;
}
