#include<iostream>

struct FMonster
{
	char Name[32];
	int Level;
	int Attack;
	int HP;
};

void changenumber(int* num) //�����͸� ���� �Լ� �� ����
{
	*num += 100;
}

int* GetInt() //��۸� ������ �׽�Ʈ
{
	int FuncInt = 100;
	return &FuncInt;
}

int main()
{
	int num = 100;
	int* pnum = &num;

	float fnum = 10.f;
	float* pfnum = &fnum;

	//int* pnum = &fnum;
	//Ÿ�� ����ġ

	void* pvnum = &num;
	pvnum = &fnum;
	//void �������� ���� ����
	std::cout << "pnum:" << *pnum << std::endl;
	*pnum = 200;
	std::cout << "pnum�� ������:" << *pnum << std::endl;
	changenumber(pnum);
	std::cout << "pnum�� �Լ�����:" << *pnum<<std::endl;
	//������ ������ ������ �ִ� �ּ�(&num)�� ��(num=100)�� ���

	int* funcnum = GetInt();
	std::cout << funcnum << std::endl;
	*funcnum = 1111;
	std::cout << *funcnum << std::endl;
	//�Լ��� ȣ��� �� �޸� ����, �Լ� ���� �� �޸� ����
	//�Լ��� ����� �� ��ȯ�� �ּҴ� �̹� ���ŵ� �޸�
	//���ŵ� �޸𸮿� ������ �õ� �� ���� �߻�
	//��۸� ������:�޸𸮰� ���ŵ� �ּҸ� ������ �ִ� ������

	int Array[10] = {};
	Array[2] = 5000;

	std::cout << Array[2] << std::endl;
	//�迭 �̸��� �迭�� �����ּ�
	//������ ������ �迭�� �����ּҸ� ����

	int* pArray = Array;
	*(pArray + 2) = 3000;
	std::cout << Array[2] << std::endl;

	FMonster monster;
	FMonster* pMonster = &monster;

	//*pMonster.Level = 300;
	// �����ڴ� �켱������ ����
	// '.' ���� ������
	(*pMonster).Level = 300;
	std::cout << pMonster->Level << std::endl;
	pMonster->Level = 500;
	std::cout << monster.Level << std::endl;
	//�Ϲݺ����� ��� ������, �� ������ ����


	return 0;
}
