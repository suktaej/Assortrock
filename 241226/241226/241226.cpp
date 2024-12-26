#include <iostream>
#include <unordered_map>
#include <map>
#include <set>

void MapFunc()
{
	std::map<std::string, int> IntMap1;
	//미리 입력 한 이후 정렬이 필요한 경우
	IntMap1.insert(std::make_pair("ccc", 30));
	IntMap1.insert(std::make_pair("aaa", 10));
	IntMap1.insert(std::make_pair("eee", 50));
	IntMap1.insert(std::make_pair("bbb", 20));

	for (auto MapPair : IntMap1)
		std::cout << "Key: " << MapPair.first << " value: " << MapPair.second << std::endl;
 }

void UnorderedMapFunc()
{
	//메모리 주소를 비교
	//문자열 사용 시, operator==를 통해 자체생성
	//C++표준 문자열 클래스 사용
	std::unordered_map <std::string, int> IntMap;

	IntMap.insert({"aaa",10});
	
	//키를 이용하여 렌덤 액세스 연산자를 지원
	//해당 키가 없을 경우 해당 키로 새로 만들고 대입해주는 값을 value로 설정
	//키가 있을 경우 value를 리턴
	IntMap["bbb"] = 20;
	std::cout << IntMap["bbb"] << std::endl;
	std::cout << IntMap["ccc"] << std::endl;

	IntMap.insert(std::make_pair("ddd", 40));
	IntMap.insert(std::make_pair("ddd", 400));
	//키 값이 중복일 경우 삽입 불가(허용하지 않음)
	IntMap["ddd"] = 41;
	//내용 수정은 가능

	//find:key 값을 넣을 경우 key와 value를 가지고 있는 iterator를 반환
	//key가 없을 경우 end()를 반환
	std::unordered_map<std::string,int>::iterator iter = IntMap.find("aaa");

	if (iter == IntMap.end())
		std::cout << "None" << std::endl;
	else
		std::cout << "Find Key: " << iter->first << " Value: " << iter->second << std::endl;
	
	//iterator를 통한 반복 가능
	std::unordered_map<std::string, int>::iterator iterEnd = IntMap.end();
	for (iter = IntMap.begin();iter != iterEnd;iter++)
	{
		std::cout << "Key: " << iter->first << " Value: " << iter->second << std::endl;
	}

	for (const std::pair<std::string, int>& pair : IntMap)
	{
		std::cout << "Key: " << pair.first << " Value: " << pair.second << std::endl;
	}
	
	//IntMap.clear();
	//IntMap.erase();

	//특정키가 있는지 확인용도
	//없을 경우 0, 있을 경우 1	
	std::cout << IntMap.count("aaa") << std::endl;
	std::cout << IntMap.count("fff") << std::endl;
}

void UnorderedMultiMapFunc()
{
	//키 값 중복허용
	std::unordered_multimap<std::string, int> IntMultiMap;

	IntMultiMap.insert({ "aaa",10 });
	IntMultiMap.insert({ "bbb",20 });
	IntMultiMap.insert({ "aaa",11 });
	IntMultiMap.insert({ "aaa",12 });
	IntMultiMap.insert({ "aaa",13 });
	IntMultiMap.insert({ "aaa",14 });
	
	//키 값이 같은 요소를 모두 호출
	auto range = IntMultiMap.equal_range("aaa");
	//auto는 대입받는 값의 타입으로 자동으로 설정되는 타입
	//range는 iterator
	std::cout << typeid(range).name() << std::endl;
	//들어올 수 있는 범위가 큼

	for (auto iter = range.first;iter != range.second;iter++)
		std::cout << "key: " << iter->first << " Value: " << iter->second << std::endl;

	auto iterFind = IntMultiMap.find("aaa");
	//multimap은 find 실행 시 키가 여러개 있을 경우 첫번째 키의 pair를 탐색

	for (auto MultiPair : IntMultiMap)
		std::cout << "key: "<< MultiPair.first<<" value: " <<MultiPair.second << std::endl;

	std::cout << IntMultiMap.count("aaa") << std::endl;
	//키가 중복되는 갯수

	IntMultiMap.erase(iterFind);
	//인자로 들어간 iterator 하나만 제거
	IntMultiMap.erase("aaa");
	//인자로 들어간 키의 모두를 제거

	//IntMultiMap["aaa"];
	//키가 여러개 중복이기 때문에 렌덤엑세스 불가능
	//find를 통해 탐색 후 iterator로 사용
}


int main()
{
	const char* cText = "abc";
	char Text[4] = {};
	strcpy_s(Text, "abc");
	
	std::cout << (cText == Text) << std::endl;
	
	//Map
	MapFunc();
	std::cout << "-----------------------" << std::endl;
	//UnorderedMap
	UnorderedMapFunc();
	std::cout << "-----------------------" << std::endl;
	//UnorderedMultiMap
	UnorderedMultiMapFunc();
	//몬스터나 아이템의 원본 객체를 저장, 탐색을 통해 원본객체를 가져오고 사용

	return 0;
}

