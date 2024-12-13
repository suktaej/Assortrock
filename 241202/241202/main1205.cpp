#include<iostream>

enum class EItemType : unsigned char //12.3 Ȯ��
{
	Weapon,
	Armor,
	Ring
};
struct FItem		//44byte
{
	char Name[32];	//32byte(char array)
	EItemType ItemType;	//1byte(unsigned char)
	int Option;		//4byte(int)
	int Price;		//4byte(int)
	double f;
};
//����ü ũ��� ����ü ��� ������ ����
//�⺻ ������ 4byte
//char�� �����ϴ��� �켱 4byte�� �Ҵ��ϰ� 1byte�� ���
//�߰��� bool(1byte)�� �Ҵ��ϴ��� ���� ������ 4byte���� ���� ������ ����

struct FEmpty {};
//�� ����ü�� 1byte�� �Ҵ� ��

void OutputItem(const FItem& item);

int main()
{
	FItem item = {};
	//����ü ���� �� 0���� �� �ʱ�ȭ
	FItem item2 = { "ö��",EItemType::Weapon };
	//���������� �ʱ�ȭ, option, price�� ���� �Էµ��� �ʾ������� ������ ���� �� ����
	FItem itemArr[10];

	item.ItemType = EItemType::Weapon;
	item.Option = 100;
	item.Price = 1000;
	strcpy_s(item.Name, "���");

	std::cout << sizeof(FItem) <<" "<< sizeof(FEmpty);

	return 0;
}

void OutputItem(const FItem& item) //const ���� �Ұ�
{

}
