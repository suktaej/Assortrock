#include<iostream>

void Output()
{
	std::cout << "Output Function" << std::endl;
}


void Output1()
{
	std::cout << "Output Function1" << std::endl;

}
//�Լ��� ���´� ��ȯŸ�԰� ���ڷ� ������
//Output function�� Output1 function�� ���� ������ �Լ�

int Add(int num1, int num2) { return num1 + num2; }
int Minus(int num1, int num2) {return num1 - num2;}
//Add�� Minus �Լ� ���� ������ Ÿ���� �Լ�

int main(void)
{
	std::cout << Output << std::endl;
	//�Լ��� �̸��� �Լ��� �޸� �ּҸ� ��Ÿ��
	Output();
	//�Լ��ּ�();

	//�Լ�������: �Լ��� �ּҸ� �����ϱ� ���� ����
	//�Լ��� ���´� ��ȯŸ�԰� ���ڷ� ������
	//��ȯŸ��(*�Լ���)(����)�� ����
	void(*FuncPointer)();
	//return type�� void, parameter�� ���� ��� �Լ��� �ּҸ� ���� ����
	FuncPointer = Output;
	FuncPointer(); //ȣ��

	FuncPointer = Output1;
	FuncPointer();

	int(*FuncInt)(int, int);
	//return type�� int, parameter�� int, int �� ������ ��� �Լ� �ּ� ���� ����
	FuncInt = Add;
	std::cout << FuncInt(20, 10) << std::endl;
	FuncInt = Minus;
	std::cout << FuncInt(20, 10) << std::endl;
	
	int(*FuncArr[2])(int, int);
	//�Լ� ������ �迭
	FuncArr[0] = Add;
	FuncArr[1] = Minus;
	for (int i = 0;i < 2;i++)
		std::cout << FuncArr[i](20, 10) << std::endl;

	return 0;
}