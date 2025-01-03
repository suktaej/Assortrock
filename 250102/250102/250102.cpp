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
	
	
	
	//==========bin_tree================
	//CBinarySearchTree<std::string, int>	IntMap;

	//IntMap.insert("R", 100);
	//IntMap.insert("F", 200);
	//IntMap.insert("V", 300);
	//IntMap.insert("D", 400);
	//IntMap.insert("T", 500);

	//CBinarySearchTree<std::string, int>::ITR iter;
	//CBinarySearchTree<std::string, int>::ITR iterEnd = IntMap.end();

	//for (iter = IntMap.begin(); iter != iterEnd; ++iter)
	//{
	//	std::cout << "Key : " << iter->mKey << " Value : " <<
	//		iter->mData << std::endl;
	//}

	//iter = IntMap.find("D");

	//if (iter != IntMap.end())
	//{
	//	std::cout << "Find Key : " << iter->mKey << " Value : " <<
	//		iter->mData << std::endl;
	//}

	//else
	//	std::cout << "None Key" << std::endl;


	CBinarySearchTree<int, int>	IntTree;

	IntTree.insert(10, 10);
	IntTree.insert(4, 4);
	IntTree.insert(2, 2);
	IntTree.insert(1, 1);
	IntTree.insert(3, 3);
	IntTree.insert(8, 8);
	IntTree.insert(7, 7);

	IntTree.insert(30, 30);
	IntTree.insert(20, 20);
	IntTree.insert(15, 15);
	IntTree.insert(25, 25);

	IntTree.insert(50, 50);
	IntTree.insert(40, 40);
	IntTree.insert(80, 80);
	IntTree.insert(45, 45);

	CBinarySearchTree<int, int>::ITR iter;
	CBinarySearchTree<int, int>::ITR iterEnd =
		IntTree.end();

	/*iter = IntTree.erase(4);
	std::cout << "erase Next Key : " << iter->mKey <<
		", Value : " << iter->mData << std::endl;*/

	for (iter = IntTree.begin(); iter != iterEnd; ++iter)
	{
		std::cout << "Key : " << iter->mKey <<
			", Value : " << iter->mData << std::endl;
	}

	std::cout << "======== PreOrder ========" <<
		std::endl;
	IntTree.PreOrder();

	std::cout << "======== InOrder ========" <<
		std::endl;
	IntTree.InOrder();

	std::cout << "======== PostOrder ========" <<
		std::endl;
	IntTree.PostOrder();

	return 0;
}
