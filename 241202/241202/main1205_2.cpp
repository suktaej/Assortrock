#include<iostream>
#include<locale.h>
#include<wchar.h>

int main()
{
	char Text[32] = {};

	strcpy_s(Text, "string data");

	std::cout << Text << std::endl;

	typedef int TestInt;
	//typedef : Ÿ���� �ٸ� �̸����� ����� �� �ֵ��� Ÿ���� �̸��� �߰�
	//Ÿ�� ������
	//int�� TestInt�ε� ����� �� �ֵ��� ����
	
	size_t Count = strlen(Text);

	std::cout << Count << std::endl;
	//size_t: 64bit unsigned integer
	
	if(strcmp("aa", "aa")==0) 
		std::cout << "Same" << std::endl;
	else
		std::cout << "Diff" << std::endl;
	//���ڿ��� ���� ��� 0 ��ȯ, �ٸ� ��� 0�� �ƴ� ���� ��ȯ

	strcat_s(Text, "bbb");
	//���ڿ��� �ڿ� ���ڿ� ���̱�
	std::cout << Text << std::endl;
	
	//setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));

	wchar_t str[] = L"�ѱ��� ���ڿ�";
	size_t len = wcslen(str);
	std::wcout << str << L"\t" << len << std::endl;

	return 0;
}