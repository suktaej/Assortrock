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

enum class EMainMenu :unsigned char		//�޴�����
{
	None,
	Battle,
	Store,
	Inventory,
	Exit
};
//���� ���� ���� ����� ���� ������ �ɷ�ġ�� �ٸ��� ����
//�÷��̾� ���� ���� �� �÷��̾� ���ݷ� - ���� ���� ��ŭ ���� ü�� ����
//�÷��̾��� ���ݷº��� ������ ������ ���ٸ� 0���� �����Ƿ� �ּҵ������� 1�� �������� ����

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
//		return;			//����ó�� �ʿ�
//	}
//	Player->HP = Player->HPMax;
//	Player->MP = Player->MPMax;
//	Player->Level = 1;
//	Player->Exp = 0;
//	Player->Gold = 10000;
}

bool Init(FPlayer* Player)
{
//�÷��̾� �ʱ�ȭ
	if (JobInit(Player) == false)
		return false;

	char Pname[32] = {};
	
	std::cout << "�̸�:";
	std::cin >> Pname;

	while (true) 
	{
		std::cout << "1.����" << std::endl;
		std::cout << "2.�ü�" << std::endl;
		std::cout << "3.������" << std::endl;
		std::cout << "���� ����:";

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
	//��ü �ʱ�ȭ �̹Ƿ� ���� �ʱ�ȭ ���� ����
	//���� �ʱ�ȭ �Լ��� ȣ���ϱ� ���� Battle.h ��� ȣ�� �ʿ�
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
	std::cout << "1.����" << std::endl;
	std::cout << "2.����" << std::endl;
	std::cout << "3.����" << std::endl;
	std::cout << "4.����" << std::endl;
	std::cout << "�޴� ����:";

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
