#include "Battle.h"

int	gLevelUpTable[LEVEL_MAX - 1] =			//확인 필요
{
	2000,
	5000,
	10000,
	18000,
	30000,
	45000,
	65000,
	90000,
	150000
};
enum class EMap : unsigned char
{
	None,
	Easy,
	Normal,
	Hard,
	Back
};

FMonster gOriginMonster[3];
//전역변수로 설정해야하는가?

enum class EBattleMenu : unsigned char
{
	None,
	Attack,
	Back
};

enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

bool InitBattle()		//전투 초기화 코드
{	
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.lst", "rb");
	if (!File)
		return false;
	fread(gOriginMonster, sizeof(FMonster), 3, File);

	fclose(File);

	fopen_s(&File, "LevelUpTable.txt", "rt");

	if (!File)
		return false;
	char Line[128] = {};
	fgets(Line, 128, File);
	int maxLevel = atoi(Line);

//	int MaxLevel = 0;
//	fscanf_s(File, "%d", &MaxLevel);

	fgets(Line, 128, File);
	//strtok_s:문자열 분리 함수
	//strtok_s(원본문자,분리자,남은자)
	char* Context = nullptr;
	char* Result = strtok_s(Line, ", ", &Context);
	gLevelUpTable[0] = atoi(Result);

	for (int i = 1; i < 9;i++)
	{
		Result = strtok_s(nullptr, ", ", &Context);
		//nullptr이 들어갈 경우 남은자 부터 시작
		gLevelUpTable[i] = atoi(Result);
	}

//	for (int i = 0;i < 9;i++)
//	{
//		fscanf_s(File, "%d, ", &gLevelUpTable[i]);
//	}


	//문자열 토큰

	fclose(File);

	return true;
}

EMap BattleMenu()
{
	system("cls");
	std::cout << "1.쉬움" << std::endl;
	std::cout << "2.보통" << std::endl;
	std::cout << "3.어려움" << std::endl;
	std::cout << "4.뒤로가기" << std::endl;
	std::cout << "메뉴 선택:";

	int SelectMenu = 0;
	std::cin >> SelectMenu;

	if (SelectMenu <= static_cast<int>(EMap::None) ||
		SelectMenu > static_cast<int>(EMap::Back))
		return EMap::None;

	return static_cast<EMap>(SelectMenu);
}

FMonster* CreateMonster(EMap Map)
{
	FMonster* Monster = new FMonster;
	*Monster = gOriginMonster[static_cast<int>(Map) - 1];
//	switch (Map)
//	{
//	case EMap::Easy:
//		strcpy_s(Monster->Name, "고블린");
//		Monster->Attack = 30;
//		Monster->Defense = 10;
//		Monster->HP = 100;
//		Monster->HPMax = 100;
//		Monster->MP = 10;
//		Monster->MPMax = 10;
//		Monster->Level = 1;
//		Monster->Exp = 1000;
//		Monster->Gold = 1000;
//		break;
//	case EMap::Normal:
//		strcpy_s(Monster->Name, "오크");
//		Monster->Attack = 70;
//		Monster->Defense = 40;
//		Monster->HP = 600;
//		Monster->HPMax = 600;
//		Monster->MP = 100;
//		Monster->MPMax = 100;
//		Monster->Level = 5;
//		Monster->Exp = 5000;
//		Monster->Gold = 5000;
//		break;
//	case EMap::Hard:
//		strcpy_s(Monster->Name, "드래곤");
//		Monster->Attack = 200;
//		Monster->Defense = 150;
//		Monster->HP = 2000;
//		Monster->HPMax = 2000;
//		Monster->MP = 1000;
//		Monster->MPMax = 1000;
//		Monster->Level = 10;
//		Monster->Exp = 10000;
//		Monster->Gold = 10000;
//		break;
//	}
	return Monster;
}

const char* JobToText(EJob Job)
{
	switch (Job)
	{
	case EJob::None:    return "Novice";
	case EJob::Fighter: return "Fighter";
	case EJob::Archer:  return "Archer";
	case EJob::Mage:    return "Mage";
	default:            return "Unknown";	//오류처리
	}
}

void OutputPlayer(FPlayer* Player)
{
	std::cout << "============================" << std::endl;
	std::cout << "       Player Status       " << std::endl;
	std::cout << "============================" << std::endl;
	std::cout << "Name:   " << Player->Name << std::endl;
	std::cout << "Level:  " << Player->Level << std::endl;
	std::cout << "EXP:    " << Player->Exp << std::endl;
	std::cout << "Job:    " << JobToText(Player->Job) << std::endl;
	std::cout << "HP:     " << Player->HP << " / " << Player->HPMax << std::endl;
	std::cout << "MP:     " << Player->MP << " / " << Player->MPMax << std::endl;
	std::cout << "ATK:    " << Player->Attack << std::endl;
	std::cout << "DEF:    " << Player->Defense << std::endl;
	std::cout << "Gold:   " << Player->Gold << std::endl;
}

void OutputMonster(FMonster* Monster)
{
	std::cout << "============================" << std::endl;
	std::cout << "       Monster Status       " << std::endl;
	std::cout << "============================" << std::endl;
	std::cout << "Name:   " << Monster->Name << std::endl;
	std::cout << "Level:  " << Monster->Level << std::endl;
	std::cout << "HP:     " << Monster->HP << " / " << Monster->HPMax << std::endl;
	std::cout << "ATK:    " << Monster->Attack << std::endl;
	std::cout << "DEF:    " << Monster->Defense << std::endl;
}

EBattleResult Battle(FPlayer* Player, FMonster* Monster)
{
	int Damage;
	Damage = (Player->Attack) - (Monster->Defense);
	if (Damage <= 0) Damage = 1;
	std::cout << Player->Name << "의 공격! " << Damage << "의 데미지를 입혔다." << std::endl;
	
	Monster->HP -= Damage;
	if (Monster->HP <= 0)
	{
		std::cout << Player->Name << "의 승리." << std::endl;
		return EBattleResult::MonsterDeath;
	}

	Damage = (Monster->Attack) - (Player->Defense);
	if (Damage <= 0) Damage = 1;
	std::cout << Monster->Name << "의 공격! " << Damage << "의 데미지를 입었다." << std::endl;
	Player->HP -= Damage;
	if (Player->HP <= 0)
	{
		std::cout << Player->Name << "의 패배." << std::endl;
		return EBattleResult::PlayerDeath;
	}
	return EBattleResult::None;
}

void RunStage(EMap Map, FPlayer* Player)
{
	FMonster* Monster = CreateMonster(Map);

	while (true)
	{
		system("cls");							//출력
		OutputPlayer(Player);
		OutputMonster(Monster);

		int Fight = 0;							//선택
		std::cout << "1.전투 2.도주 : ";
		std::cin >> Fight;

		if (Fight == static_cast<int>(EBattleMenu::Back))
		{
			delete Monster;						//도주시 몬스터 제거
			return;
		}
		else if (Fight <= static_cast<int>(EBattleMenu::None)||
			Fight > static_cast<int>(EBattleMenu::Back))
			continue;

		switch (Battle(Player, Monster))
		{
		case EBattleResult::PlayerDeath:
			Player->HP = Player->HPMax;
			Player->MP = Player->MPMax;
			Player->Exp *= 0.9f;
			Player->Gold *= 0.9f;
			return;
		case EBattleResult::MonsterDeath:
			Player->Exp += Monster->Exp;

			if (Player->Level < LEVEL_MAX)
			{
				if (Player->Exp >= gLevelUpTable[Player->Level - 1])
				{
					Player->Exp -= gLevelUpTable[Player->Level - 1];
					++Player->Level;
					Player->Attack *= 1.2f;
					Player->Defense *= 1.2f;
					Player->HPMax *= 1.2f;
					Player->MPMax *= 1.2f;
					Player->HP = Player->HPMax;
					Player->MP = Player->MPMax;
				}
			}

			Player->Gold += Monster->Gold;
			delete Monster;
			Monster = CreateMonster(Map);
			break;
		}
		system("pause");
	}
}

void RunBattle(FPlayer* Player)
{
	while (true)
	{
		EMap Menu = BattleMenu();

		if (Menu == EMap::Back)
			return;
		else if (Menu == EMap::None)
			continue;

		RunStage(Menu, Player);
	}
}
