
#include <iostream>
#include <time.h>
#include <Windows.h>
#include "Heap.h"

#define	ARRAY_COUNT1	100000

// Bubble : 0.08
// Select : 0.12
// heap : 0.005, 0.004

bool SortFunc(const int& Src, const int& Dest)
{
	return Src < Dest;
}

int main()
{
	srand(time(0));
	rand();

	CHeap<int>	heap;

	heap.SetSortFunction(SortFunc);

	LARGE_INTEGER	Start, End, Second;
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Start);

	for (int i = 0; i < ARRAY_COUNT1; ++i)
	{
		heap.insert(rand());
		//std::cout << Number[i] << ", ";
	}

	while (!heap.empty())
	{
		//std::cout << heap.front() << std::endl;
		heap.pop();
	}

	QueryPerformanceCounter(&End);

	float	Time = (End.QuadPart - Start.QuadPart) /
		(float)Second.QuadPart;

	std::cout << "Time : " << Time << std::endl;

	return 0;
}