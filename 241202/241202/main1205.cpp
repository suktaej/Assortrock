#include<iostream>

enum class EItemType : unsigned char //12.3 확인
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
//구조체 크기는 구조체 멤버 맞춤을 진행
//기본 단위는 4byte
//char로 선언하더라도 우선 4byte를 할당하고 1byte만 사용
//추가로 bool(1byte)를 할당하더라도 기존 생성한 4byte에서 남는 공간에 적용

struct FEmpty {};
//빈 구조체는 1byte만 할당 됨

void OutputItem(const FItem& item);

int main()
{
	FItem item = {};
	//구조체 선언 후 0으로 값 초기화
	FItem item2 = { "철검",EItemType::Weapon };
	//순차적으로 초기화, option, price는 값이 입력되지 않았음으로 쓰레기 값이 들어가 있음
	FItem itemArr[10];

	item.ItemType = EItemType::Weapon;
	item.Option = 100;
	item.Price = 1000;
	strcpy_s(item.Name, "목검");

	std::cout << sizeof(FItem) <<" "<< sizeof(FEmpty);

	return 0;
}

void OutputItem(const FItem& item) //const 변경 불가
{

}
