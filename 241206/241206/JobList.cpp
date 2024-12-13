#include "JobList.h"

bool JobList(void)
{
	FPlayer Player[3] = {};

	Player[0].HPMax = 100;
	Player[0].Attack = 50;
	Player[0].Defense = 25;
	Player[0].MPMax = 0;

	Player[1].HPMax = 200;
	Player[1].Attack = 80;
	Player[1].Defense = 75;
	Player[1].MPMax = 0;

	Player[2].HPMax = 150;
	Player[2].Attack = 70;
	Player[2].Defense = 50;
	Player[2].MPMax = 0;

	for (int i = 0; i < 3; i++)
	{
		Player[i].HP = Player[i].HPMax;
		Player[i].MP = Player[i].MPMax;
		Player[i].Level = 1;
		Player[i].Exp = 0;
		Player[i].Gold = 10000;
	}

	FILE* File = nullptr;
	fopen_s(&File, "JobList.lst", "wb");
	if (File)
	{
		fwrite(Player, sizeof(FPlayer), 3, File);
		fclose(File);
		return true;
	}
	return false;
}

bool JobList2(void)
{
	FILE* File = nullptr;
	fopen_s(&File, "PlayerInfo.pli", "wb");

	if (File)
	{
		int Attack = 10;
		int Defense = 10;
		int HP = 100;
		int MP = 100;
		
		fwrite(&Attack, sizeof(int), 1, File);
		fwrite(&Defense, sizeof(int), 1, File);
		fwrite(&HP, sizeof(int), 1, File);
		fwrite(&MP, sizeof(int), 1, File);

		Attack = 30;
		Defense = 30;
		HP = 300;
		MP = 300;
		
		fwrite(&Attack, sizeof(int), 1, File);
		fwrite(&Defense, sizeof(int), 1, File);
		fwrite(&HP, sizeof(int), 1, File);
		fwrite(&MP, sizeof(int), 1, File);

		Attack = 70;
		Defense = 70;
		HP = 700;
		MP = 700;
		
		fwrite(&Attack, sizeof(int), 1, File);
		fwrite(&Defense, sizeof(int), 1, File);
		fwrite(&HP, sizeof(int), 1, File);
		fwrite(&MP, sizeof(int), 1, File);
		
		fclose(File);
		return true;
	}
	return false;
}
