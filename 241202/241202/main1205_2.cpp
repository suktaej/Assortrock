#include<iostream>
#include<locale.h>
#include<wchar.h>

int main()
{
	char Text[32] = {};

	strcpy_s(Text, "string data");

	std::cout << Text << std::endl;

	typedef int TestInt;
	//typedef : 타입을 다른 이름으로 사용할 수 있도록 타입의 이름을 추가
	//타입 재정의
	//int를 TestInt로도 사용할 수 있도록 해줌
	
	size_t Count = strlen(Text);

	std::cout << Count << std::endl;
	//size_t: 64bit unsigned integer
	
	if(strcmp("aa", "aa")==0) 
		std::cout << "Same" << std::endl;
	else
		std::cout << "Diff" << std::endl;
	//문자열이 같을 경우 0 반환, 다를 경우 0이 아닌 값을 반환

	strcat_s(Text, "bbb");
	//문자열의 뒤에 문자열 붙이기
	std::cout << Text << std::endl;
	
	//setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));

	wchar_t str[] = L"한국어 문자열";
	size_t len = wcslen(str);
	std::wcout << str << L"\t" << len << std::endl;

	return 0;
}