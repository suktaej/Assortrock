#include <iostream>

class C1
{
private:
	int num;
public:
	C1() {}
	C1(int num) { this->num = num; }
	C1(const C1& ref) { this->num = ref.num; }
	C1(C1&& ref) 
	{
		std::cout << "�̵�������" << std::endl;
	}
	//�̵�������: ��ü�� ����ִ� ���¿��� ������� �ʴ´ٰ� ������ �� �ִ� ��Ȳ�� �� ���

	int& RefFunc(int num) { return num; }
};

int Func1(int num)
{
	std::cout << num << std::endl;
	return num;
}

int Func2(const int& num)	
//�ӽð�ü�� �������� ����
{
	std::cout << num << std::endl;
	return num;
}

int main(void)
{
	C1 temp;
	//temp = C1(30);
	//1. �ӽð�ü ����
	//2. ����
	//3. ������ ������ ������ �ӽð�ü ����
	//�ӽð�ü�� �������� ���� ���, ������ �Ұ���(�ڵ�������)
	C1* ptemp = &C1(40);
	//�ӽð�ü�� �ּҸ� ��ȯ�� �ִ� ���, �ּҿ� L-value���� �����Ƿ� ��۸� ������ ���� ��
	//C1(30) = temp;
	
	return 0;
}