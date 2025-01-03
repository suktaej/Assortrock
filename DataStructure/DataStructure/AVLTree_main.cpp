
#include <iostream>
#include "AVLTree.h"

int main()
{
	CAVLTree<int, int>	IntTree;

	for (int i = 1; i < 30; ++i)
	{
		IntTree.insert(i, i);
	}

	IntTree.Output();

	return 0;
}
