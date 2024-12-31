#include <iostream>
#include "LinkedList.h"

int main()
{
	CLinkedList<int> IntList;

	for (int i = 0;i < 10;i++)
		IntList.push_back(i);
	
	CLinkedList<int>::iterator iter;
	CLinkedList<int>::iterator iterEnd = IntList.end();

	for (iter = IntList.begin();iter!=iterEnd;iter++)
		std::cout << *iter << std::endl;

	return 0;
}
