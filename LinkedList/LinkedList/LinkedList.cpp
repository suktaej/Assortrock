#include <iostream>
#include "LinkedList2.h"

int main()
{
	CLinkedList<int> lst;
	CIterator<int> iter;
	CIterator<int> iterEnd = lst.end();

	for (int i = 0; i < 10; ++i)
		lst.push_back(i);
	
	iter = lst.begin();
	std::cout << *iter << std::endl;
	iter++;
	std::cout << *iter << std::endl;
	iter++;
	std::cout << *iter << std::endl;
	lst.insert(100,iter);
	std::cout << "insert after:" <<* iter << std::endl;
	iter++;
	std::cout << *iter << std::endl;
	iter++;
	std::cout << *iter << std::endl;
	iter++;
	std::cout << *iter << std::endl;
	iter++;
	std::cout << *iter << std::endl;
	lst.insert(200, iter);
	std::cout << "insert after:" <<* iter << std::endl;
	iter--;
	std::cout << *iter << std::endl;
	lst.erase(iter);
	std::cout <<"erase after:"<< * iter << std::endl;
	iter--;
	std::cout << *iter << std::endl;
	iter--;
	std::cout << *iter << std::endl;
	lst.erase(iter);
	std::cout <<"erase after:"<< * iter << std::endl;

	std::cout << "-----------------" << std::endl;

	for (iter = lst.begin(); iter != iterEnd; ++iter)
		std::cout << *iter << std::endl;

	return 0;
}
