
#include <iostream>
#include "Dijkstra.h"

int main()
{
	CDijkstra<int>	PathFinder;

	PathFinder.AddData(1);
	PathFinder.AddData(2);
	PathFinder.AddData(3);
	PathFinder.AddData(4);
	PathFinder.AddData(5);
	PathFinder.AddData(6);
	PathFinder.AddData(7);

	PathFinder.AddEdge(1, 2, 2);
	PathFinder.AddEdge(1, 3, 3);

	PathFinder.AddEdge(2, 5, 7);

	PathFinder.AddEdge(3, 4, 2);
	PathFinder.AddEdge(3, 6, 7);

	PathFinder.AddEdge(4, 5, 2);

	PathFinder.AddEdge(5, 7, 2);

	PathFinder.AddEdge(6, 7, 3);

	CArray<int>	PathArray;
	PathFinder.FindPath(PathArray, 1, 7);

	int	Size = PathArray.size();

	for (int i = 0; i < Size; ++i)
		std::cout << PathArray[i] << " -> ";

	return 0;
}
