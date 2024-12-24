#include <iostream>
#include <list>

class C1
{

};

int main(void)
{
	std::list<int> IntList;
	std::list<int>::iterator iter;
	std::list<int>::iterator iterEnd = IntList.end();


	for (int i = 0;i < 10;i++)
	{
		//IntList.push_back(i + 1);
		IntList.emplace_back(i + 1);
	}
	IntList.emplace_front(111);

	for (iter = IntList.begin();iter != iterEnd;iter++)
		std::cout << *iter << std::endl;

	return 0;
}