#include <iostream>
//#include "Stack.h"
//#include "Queue.h"
//#include "Tree.h"
#include "BinarySearchTree.h"

int main()
{
	//============stack=================
	////CStackDynamicArray<int> IntStack;
	//CStackStaticArray<int> IntStack;
	////CQueue<int> IntQueue;
	//CCircleQueue<int> IntQueue;

	//for (int i = 0;i < 10;i++)
	//	//IntStack.push(i);
	//	IntQueue.push(i);

	//while (!IntQueue.empty())
	//{
	//	//std::cout << IntStack.pop() << std::endl;
	//	std::cout << IntQueue.pop() << std::endl;
	//}

	//==============tree================
	//CTree<std::string, int> Tree1;
	//Tree1.insert("Node1", 10, "None");
	//Tree1.insert("Node2", 20, "Node1");
	//Tree1.insert("Node3", 30, "Node1");
	//Tree1.insert("Node4", 40, "Node2");
	//Tree1.insert("Node5", 50, "Node2");
	//Tree1.insert("Node6", 60, "Node2");
	//Tree1.insert("Node7", 70, "Node3");
	//Tree1.insert("Node8", 80, "Node4");
	//Tree1.insert("Node9", 90, "None");
	//Tree1.Output();

	//==========BST_tree================
	CBinarySearchTree<std::string, int>	IntMap;

	IntMap.insert("R", 100);
	IntMap.insert("F", 200);
	IntMap.insert("V", 300);
	IntMap.insert("D", 400);
	IntMap.insert("T", 500);

	CBinarySearchTree<std::string, int>::ITR iter;
	CBinarySearchTree<std::string, int>::ITR iterEnd = IntMap.end();

	for (iter = IntMap.begin(); iter != iterEnd; ++iter)
	{
		std::cout << "Key : " << iter->mKey << " Value : " <<
			iter->mData << std::endl;
	}

	iter = IntMap.find("Y");

	if (iter != IntMap.end())
	{
		std::cout << "Find Key : " << iter->mKey << " Value : " <<
			iter->mData << std::endl;
	}

	else
		std::cout << "Key does not exist" << std::endl;

	return 0;
}
