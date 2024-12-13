#include<iostream>
#include<fstream>
#define MODETYPE 13;

enum class EItemType : unsigned char
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

int main(void)
{
	int flag = MODETYPE;

	FILE* File = nullptr;

	if (flag == 10)
	{
		//File = fopen("CTextFile.txt", "wt");
		fopen_s(&File, "CTextFile.txt", "wt");
		if (nullptr != File)
		{
			fputc('C', File);
			fputs("fopen_s write", File);

			int num = 100;
			//fputs(num, File);	//int형은 작성불가
			fprintf(File, "\nNumber = %d", num);

			fclose(File);
		}
	}
	else if (flag == 11)
	{
		fopen_s(&File, "CTextFile.txt", "rt");
		if (nullptr != File)
		{
			char Ch1 = 'A';
			char Text[32] = {};
			
			Ch1 = fgetc(File);
			//파일포인터가 첫번째 문자를 읽음
			//파일포인터가 두번째 문자로 이동
			std::cout << Ch1;
			
			fgets(Text, sizeof(Text), File);
			//파일포인터가 두번째 문자부터 개행 또는 크기만큼 읽음
			std::cout << Text;

			while (fgets(Text, sizeof(Text), File) != nullptr) // EOF 전까지 반복
			{
				std::cout << Text; 
			}
			//모든 라인 읽어오기
			fclose(File);
		}
	}
	else if (flag == 12)
	{
		fopen_s(&File, "CBinFile1.b", "wb");
		if (File)
		{
			int num = 100;

			FItem Item;
			strcpy_s(Item.Name, "목검");
			Item.Type = EItemType::Weapon;
			Item.Cost = 100;

			fwrite(&num, sizeof(int), 1, File);
			fwrite(&Item, sizeof(FItem), 1, File);
			fclose(File);
		}
	}
	else if (flag == 13)
	{
		fopen_s(&File, "CBinFile1.b", "rb");
		if (File)
		{
			int num;
			fread(&num, sizeof(int), 1, File);
			std::cout << num << std::endl;

			FItem Item = {};
			fread(&Item, sizeof(FItem), 1, File);
			std::cout << Item.Name << std::endl;
			std::cout << static_cast<int>(Item.Type) << std::endl;
			std::cout << Item.Cost << std::endl;

			fclose(File);
		}
	}
	else if (flag == 0)
	{
		std::ofstream ostream;

		ostream.open("CppTextFile1.txt");
		ostream.write("AA", 2);

		char Text[32] = {};
		strcpy_s(Text, "문자열");

		ostream.write(Text, strlen(Text));
		ostream.close();
	}
	else if (flag == 1)
	{
		std::ifstream istream;

		istream.open("TestFile2.txt");
		if (istream.is_open())
		{
			while (!istream.eof())
			{
				char Line[32] = {};
				istream.getline(Line, 32);
				std::cout << Line << std::endl;
			}
		}
	}
	else if (flag == 2)
	{
		std::ofstream ostream;
		ostream.open("TestFile3.b", std::ios::binary);
		if (ostream.is_open())
		{
			int Number = 100;
			ostream.write((const char*)&Number, sizeof(int));

			FItem Item;
			strcpy_s(Item.Name, "목검");
			Item.Type = EItemType::Weapon;
			Item.Cost = 100;
			ostream.write((const char*)&Item, sizeof(FItem));

			ostream.close();
		}
	}
	else if (flag == 4)
	{
		std::ifstream istream;

		istream.open("TestFile3.b", std::ios::binary);
		if (istream.is_open())
		{
			int Number1 = 0;
			istream.read((char*)&Number1, sizeof(int));
			std::cout << Number1 << std::endl;

			FItem Item1 = {};
			istream.read((char*)&Item1, sizeof(FItem));
			std::cout << Item1.Name << std::endl;
			std::cout << static_cast<int>(Item1.Type) << std::endl;
			std::cout << Item1.Cost << std::endl;
		}
	}
	return 0;
}