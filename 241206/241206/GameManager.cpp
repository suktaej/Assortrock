#include "GameManager.h"
#include "Battle.h"
#include "StoreManager.h"
#include "Inventory.h"
#include "ItemList.h"
#include "JobList.h"

struct FPlayerFileInfo
{
	int Attack;
	int Defense;
	int HP;
	int MP;
};

enum class EMainMenu :unsigned char		//메뉴선택
{
	None,
	Battle,
	Store,
	Inventory,
	Exit
};
//전투 쉬움 보통 어려움에 따라 몬스터의 능력치를 다르게 설정
//플레이어 먼저 공격 시 플레이어 공격력 - 몬스터 방어력 만큼 몬스터 체력 감소
//플레이어의 공격력보다 몬스터의 방어력이 높다면 0값이 나오므로 최소데미지인 1이 나오도록 구현

FPlayer PlayerJob[3] = {};

bool JobInit(FPlayer* Player)
{
	FILE* File = nullptr;

	fopen_s(&File, "JobList.lst", "rb");
	if (File)
	{
		fread(PlayerJob, sizeof(FPlayer), 3, File);
		fclose(File);
		return true;
	}
	return false;
//	switch (Player->Job)
//	{
//	case EJob::None:
//		Player->HPMax = 100;
//		Player->Attack = 50;
//		Player->Defense = 25;
//		Player->MPMax = 0;
//		break;
//	case EJob::Fighter:
//		Player->HPMax = 200;
//		Player->Attack = 80;
//		Player->Defense = 75;
//		Player->MPMax = 0;
//		break;
//	case EJob::Archer:
//		Player->HPMax = 150;
//		Player->Attack = 70;
//		Player->Defense = 50;
//		Player->MPMax = 0;
//		break;
//	case EJob::Mage:
//		Player->HPMax = 125;
//		Player->Attack = 60;
//		Player->Defense = 30;
//		Player->MPMax = 0;
//		break;
//	default:
//		return;			//오류처리 필요
//	}
//	Player->HP = Player->HPMax;
//	Player->MP = Player->MPMax;
//	Player->Level = 1;
//	Player->Exp = 0;
//	Player->Gold = 10000;
}

bool Init(FPlayer* Player)
{
//플레이어 초기화
	if (JobInit(Player) == false)
		return false;

	char Pname[32] = {};
	
	std::cout << "이름:";
	std::cin >> Pname;

	while (true) 
	{
		std::cout << "1.전사" << std::endl;
		std::cout << "2.궁수" << std::endl;
		std::cout << "3.마법사" << std::endl;
		std::cout << "직업 선택:";

		int Job = 0;
		std::cin >> Job;

		if (Job <= static_cast<int>(EJob::None) ||
			Job >= static_cast<int>(EJob::End))
			continue;
		
		*Player = PlayerJob[Job-1];
		Player->Job = static_cast<EJob>(Job);
		strcpy_s(Player->Name, Pname);
	
		break;
	}
	//전체 초기화 이므로 전투 초기화 역시 진행
	//전투 초기화 함수를 호출하기 위해 Battle.h 헤더 호출 필요
	if (InitBattle() == false)
		return false;

	if (InitStoreManager() == false)
		return false;

	if (JobList() == false)
		return false;
	
	if (InitItem() == false)
		return false;

	return true;
}

void Destory()
{
	DestroyStoreManager();
	DestroyInventory();
}

EMainMenu Menu()
{
	system("cls");
	std::cout << "1.전투" << std::endl;
	std::cout << "2.상점" << std::endl;
	std::cout << "3.가방" << std::endl;
	std::cout << "4.종료" << std::endl;
	std::cout << "메뉴 선택:";

	int SelectMenu = 0;
	std::cin >> SelectMenu;

	if (SelectMenu <= static_cast<int>(EMainMenu::None) ||
		SelectMenu > static_cast<int>(EMainMenu::Exit))
		return EMainMenu::None;

	return static_cast<EMainMenu>(SelectMenu);
}


void Run(FPlayer* Player)
{

	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Battle:
			RunBattle(Player);
			break;
		case EMainMenu::Store:
			RunStoreManager(Player);
			break;
		case EMainMenu::Inventory:
			RunInventory(Player);
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
