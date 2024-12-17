#include "ItemWeapon.h"
#include "ItemArmor.h"

#define DEFAULT_CAPACITY 4

enum class EMenu
{
	None,
	ItemAdd,
	ItemDelete,
	ItemSave,
	ItemLoad,
	ItemOutput,
	Exit
};

CItem** gItemList;
int gItemCount = 0;				//실제 추가된 아이템 수
int gItemCapacity = 4;		//배열의 최대 크기		

void AddItem()
{
	//아이템 추가 시 배열이 가득 찬 건지 확인
	if (gItemCapacity == gItemCount)
	{
		gItemCapacity *= 2;
		//새로운 배열을 전체 배열의 수 2배만큼 할당
		CItem** Array = new CItem* [gItemCapacity];
		
		//원래 있던 배열에서 데이터를 복사
		for (int i = 0;i < gItemCount;i++)
			Array[i] = gItemList[i];
		//원래 있던 배열을 제거
		delete[] gItemList;
		//새로운 배열의 주소를 저장
		gItemList = Array;
	}
	else
	{
		EItemType ItemType;

		while (true)
		{
			system("cls");
			//어떠한 타입의 장비를 생성할 지 선택
			std::cout << "1.Weapon" << std::endl;
			std::cout << "2.Armor" << std::endl;
			std::cout << "Select>> ";
			int Input;
			std::cin >> Input;

			if (Input < 1 || Input>2)
				continue;

			ItemType = (EItemType)(Input - 1);
			break;
		}

		switch (ItemType)
		{
		case EItemType::Weapon:
			gItemList[gItemCount] = new CItemWeapon;
			break;
		case EItemType::Armor:
			gItemList[gItemCount] = new CItemArmor;
			break;
		default:
			break;
		}

		gItemList[gItemCount]->Init();
		gItemCount++;
	}
};
void DeleteItem() {};
void SaveItem() 
{
	FILE* File = nullptr;

	fopen_s(&File, "", "wb");
	
	if (!File)
		return;
	//저장할 무기의 수 확인
	int WeaponCount = 0;
	for (int i = 0;i < gItemCount;i++)
	{
		if (gItemList[i]->GetItemType() == EItemType::Weapon)
			WeaponCount++;
	}
	//무기 수 입력
	fwrite(&WeaponCount, sizeof(int), 1, File);
	//무기로 확인한 객체 저장	
	for (int i = 0;i < gItemCount;i++)
	{
		if(gItemList[i]->GetItemType() == EItemType::Weapon)
			gItemList[i]->Save(File);
	}
	fclose(File);

	//저장할 방어구 수 확인
	int ArmorCount = gItemCount - WeaponCount;
	//이하 무기 코드와 동일 

//	//아이템 모두 저장
//	fwrite(&gItemCount, sizeof(int), 1, File);
//
//	for (int i = 0;i < gItemCount;i++)
//	{
//		gItemList[i]->Save(File);
//	}
//	fclose(File);

	//자기자신을 파일에 저장하는 함수
};
void LoadItem() {};
void Output()
{
	system("cls");
	for (int i = 0; i < gItemCount;i++)
		gItemList[i]->Output();
	system("pause");
};

int main(void)
{
	gItemList = new CItem * [gItemCapacity];
	for (int i = 0; i < gItemCapacity; i++) { gItemList[i] = nullptr; }

	while (true)
	{
		system("cls");
		std::cout << "1.Add Item" << std::endl;
		std::cout << "2.Delete Item" << std::endl;
		std::cout << "3.Save Item" << std::endl;
		std::cout << "4.Load Item" << std::endl;
		std::cout << "5.Item Output" << std::endl;
		std::cout << "6.Exit" << std::endl;
		std::cout << "Select Menu>> ";
		int Input;
		std::cin >> Input;

		if (Input == (int)EMenu::Exit)
			return 0;
		else if ((int)EMenu::ItemAdd > Input ||
			(int)EMenu::Exit < Input)
			continue;

		switch ((EMenu)Input)
		{
		case EMenu::ItemAdd:
			AddItem();
			break;
		case EMenu::ItemDelete:
			DeleteItem();
			break;
		case EMenu::ItemSave:
			SaveItem();
			break;
		case EMenu::ItemLoad:
			LoadItem();
			break;
		case EMenu::ItemOutput:
			Output();
			break;
		}
	}

	for (int i = 0; i < gItemCount; i++)
	{
		if (gItemList[i] != nullptr)
		{
			delete gItemList[i];
			gItemList[i] = nullptr;
		}
	}
	return 0;
}

