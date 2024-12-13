#include "GameInfo.h"

void MosterList(void)
{
	FMonster Monster[3] = {};

	strcpy_s(Monster[0].Name, "고블린");
	Monster[0].Attack = 30;
	Monster[0].Defense = 10;
	Monster[0].HP = 100;
	Monster[0].HPMax = 100;
	Monster[0].MP = 10;
	Monster[0].MPMax = 10;
	Monster[0].Level = 1;
	Monster[0].Exp = 1000;
	Monster[0].Gold = 1000;

	strcpy_s(Monster[1].Name, "오크");
	Monster[1].Attack = 70;
	Monster[1].Defense = 40;
	Monster[1].HP = 600;
	Monster[1].HPMax = 600;
	Monster[1].MP = 100;
	Monster[1].MPMax = 100;
	Monster[1].Level = 5;
	Monster[1].Exp = 5000;
	Monster[1].Gold = 5000;

	strcpy_s(Monster[2].Name, "드래곤");
	Monster[2].Attack = 200;
	Monster[2].Defense = 150;
	Monster[2].HP = 2000;
	Monster[2].HPMax = 2000;
	Monster[2].MP = 1000;
	Monster[2].MPMax = 1000;
	Monster[2].Level = 10;
	Monster[2].Exp = 10000;
	Monster[2].Gold = 10000;

	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.lst", "wb");

	if (File)
	{
		fwrite(Monster,sizeof(FMonster),3,File);
		fclose(File);
	}
}