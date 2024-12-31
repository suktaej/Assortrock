#include <iostream>
#include "LinkedList.h"

int main()
{
	CLinkedList<int> IntList;

	for (int i = 0;i < 100;i++)
		IntList.push_back(i);
	
	for (int i = 0;i < 100;i++)
		IntList.pop_back();

	return 0;
}
