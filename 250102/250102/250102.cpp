#include <iostream>
#include "Stack.h"
#include "Queue.h"


int main()
{
	//CStackDynamicArray<int> IntStack;
	CStackStaticArray<int> IntStack;
	//CQueue<int> IntQueue;
	CCircleQueue<int> IntQueue;

	for (int i = 0;i < 10;i++)
		//IntStack.push(i);
		IntQueue.push(i);

	while (!IntQueue.empty())
	{
		//std::cout << IntStack.pop() << std::endl;
		std::cout << IntQueue.pop() << std::endl;
	}

	return 0;
}
