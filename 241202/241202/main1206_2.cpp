#include<iostream>

int* CreateDynamicInt()
{
	return new int;
}

//bool Ÿ������ �����Ҵ��� �Ǿ�����, �ƴ����� Ȯ���ϴ� ���
bool CreateDynamicInt1(int** Alloc)
{
	*Alloc = new int;
	return true;
}
//���� �����Ͱ� �ƴ϶� �����͸� ���ڷ� �޾ƿ� ���...

bool CreateDynamicInt2(int*& Alloc)
{
	Alloc = new int;
	return true;
}

int main()
{
	//new int;
	//int�� �޸𸮸� �����Ҵ��ϰ� �ּҸ� ��ȯ
	//�ּҰ��� ��ȯ ���� ������ ������ �ʿ䰡 ����
	int* IntAddr = new int;

	IntAddr = CreateDynamicInt();

	//new���� �Ҵ��� int�� �޸𸮿��� ����
	//�Ҵ��� �������� ���� ��� �޸� ���� �߻�(memory leak)
	delete IntAddr;

	CreateDynamicInt1(&IntAddr);
	delete IntAddr;

	CreateDynamicInt2(IntAddr);
	delete IntAddr;

	int* IntArrAddr = new int[10];
	//�迭ũ��*������ ����Ʈ ��ŭ �����Ҵ��� �ϰ� ù �ּҸ� ��ȯ
	delete[] IntArrAddr;
	//�迭 �Ҵ� ����

	return 0;
}
