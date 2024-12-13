#include<iostream>
#include<fstream>

enum class EItemType: unsigned char
{
	Weapon,
	Armor
};
struct FItem
{
	char Name[32];
	EItemType Type;
	int Cost;
};
int main()
{
	FILE* File = nullptr;
	//file 포인터

	fopen_s(&File, "TestFile.txt", "wt");
	//파일을 저장할 수 있는 경우
	if (nullptr != File)
	{
		fputc('A', File);
		fputs("\nHello", File);

		int Number = 100;
		fprintf(File, "\nNumber = %d", Number);

		fclose(File);
	}

	fopen_s(&File, "TestFile.txt", "rt");
	if (nullptr != File)
	{
	//	char Ch1 = fgetc(File);
	//	std::cout << Ch1 << std::endl;

		char Text[64] = {};
		fgets(Text,64,File);
		std::cout << Text << std::endl;
		//fgets(Text,64,File);
		//std::cout << Text << std::endl;

		fclose(File);

		float FNumber= 3.14;
		//fscanf_s(File, "Float Number = %f", &FNumber);
	}

	fopen_s(&File, "BinaryFile.b", "wb");
	if (File)
	{
		int Number = 100;
		FItem Item;
		strcpy_s(Item.Name, "목검");
		Item.Type = EItemType::Weapon;
		Item.Cost = 100;

		fwrite(&Number, sizeof(int), 1, File);
		//(저장변수명,변수크기,배열크키,파일명)
		fwrite(&Item, sizeof(FItem), 1, File);
		fclose(File);
	}

	fopen_s(&File, "BinaryFile.b", "rb");
	if (File)
	{
		int Number = 100;
		fread(&Number, sizeof(int), 1, File);
		std::cout << Number << std::endl;

		FItem Item = {};
		fread(&Item, sizeof(FItem), 1, File);
		std::cout << Item.Name << std::endl;
		std::cout << static_cast<int>(Item.Type) << std::endl;
		std::cout << Item.Cost << std::endl;
		fclose(File);
	}
	return 0;
}