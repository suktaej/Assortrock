#include "Monster.h"
#define DEFAULT_CAPACITY 4

enum class EMenu
{
	None,
	Add,
	Delete,
	Modify,
	Output,
	Save,
	Load,
	Exit
};
CMonster** gMonsterList;
int gMonsterCount = 0;
int gMonsterCapacity = DEFAULT_CAPACITY;

void AddMonster() 
{
	if (gMonsterCapacity == gMonsterCount)
	{
		gMonsterCapacity *= 2;
		CMonster** Array = new CMonster* [gMonsterCapacity];

		for (int i = 0;i < gMonsterCount;i++)
			Array[i] = gMonsterList[i];

		delete[] gMonsterList;

		gMonsterList = Array;
	}
	else 
	{
		system("cls");
		gMonsterList[gMonsterCount] = new CMonster;
		gMonsterList[gMonsterCount]->Init();
		++gMonsterCount;
	}
}
void DeleteMonster() {}
void ModifyMonster() {}
void OutputMonster() 
{
	system("cls");
	for (int i = 0;i < gMonsterCount;i++)
		gMonsterList[i]->Output();
	system("pause");
}
void SaveMonster() 
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.mls", "wb");

	if (!File)
		return;
	
	fwrite(&gMonsterCount, sizeof(int), 1, File);

	for (int i = 0; i < gMonsterCount;i++)
	{
		EBattleType BattleType = gMonsterList[i]->GetBatterType();
		fwrite(&BattleType, sizeof(EBattleType), 1, File);
		
		gMonsterList[i]->Save(File);
	}

	fclose(File);
}

void LoadMonster() 
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.mls", "rb");

	if (!File)
		return;
	
	int MonsterCount = 0;
	//읽어온 몬스터의 수가 배열 수보다 클 경우 배열을 새로 생성
	//다른 몬스터가 이미 들어가 있을 수 있으므로 재할당과는 다름
	//몬스터 수를 다른 변수에 저장

	fread(&gMonsterCount, sizeof(int), 1, File);

	if (MonsterCount > gMonsterCapacity)
	{
		for (int i = 0;i < gMonsterCount;i++)
		{
			delete gMonsterList[i];
		}

		gMonsterCapacity = gMonsterCount;

		delete[] gMonsterList;

		gMonsterList = new CMonster * [gMonsterCapacity];
	}

	gMonsterCount = MonsterCount;
	
	for (int i = 0; i < gMonsterCount;i++)
	{
		gMonsterList[i] = new CMonster;
		//추가작성
	}

	fclose(File);
}

int main()
{
	gMonsterList = new CMonster* [DEFAULT_CAPACITY];

	while (true)
	{
		system("cls");
		std::cout << "1. 몬스터추가" << std::endl;
		std::cout << "2. 몬스터삭제" << std::endl;
		std::cout << "3. 몬스터수정" << std::endl;
		std::cout << "4. 몬스터출력" << std::endl;
		std::cout << "5. 몬스터저장" << std::endl;
		std::cout << "6. 몬스터불러오기" << std::endl;
		std::cout << "7. 종료" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input == (int)EMenu::Exit)
			break;

		else if (Input <= (int)EMenu::None ||
			Input > (int)EMenu::Exit)
			continue;
	
		switch ((EMenu)Input)
		{
		case EMenu::Add:
			AddMonster();
			break;
		case EMenu::Delete:
			DeleteMonster();
			break;
		case EMenu::Modify:
			ModifyMonster();
			break;
		case EMenu::Output:
			OutputMonster();
			break;
		case EMenu::Save:
			SaveMonster();
			break;
		case EMenu::Load:
			LoadMonster();
			break;
		}
	}

	for (int i = 0; i < gMonsterCount; ++i)
		delete gMonsterList[i];
	delete[] gMonsterList;

	return 0;
}
