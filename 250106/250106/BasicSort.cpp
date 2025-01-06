#include <iostream>
#include <ctime>
#include <windows.h>

#define ARRAY_COUNT 1000

void BubbleSort(int* Array, int Count)
{
	for (int i = 0;i < Count-1;i++)
	{
		for (int j = 0; j < Count - i - 1;j++)
		{
			if (Array[j] > Array[j + 1])
			{
				int Temp = Array[j];
				Array[i] = Array[j + 1];
				Array[j + 1] = Temp;
			}
		}
	}
}

void SelectionSort(int* Array, int Count)
{
	for (int i = 0;i<Count-1;i++)
	{
		for (int j = i + 1;j < Count;j++)
		{
			if (Array[i] > Array[j])
			{
				int Temp = Array[i];
				Array[i] = Array[j];
				Array[j] = Temp;
			}
		}
	}
}

int main(void)
{
	srand(time(0));
	rand();

	int Number[100] = {};
	int Number[10][10] = {};

	for (int i = 0;i < 10;i++)
		Number[i] = rand() % ARRAY_COUNT;

	BubbleSort(Number, 10);
	//SelectionSort(Number, 10);
	
	for (int i = 0;i < 10;i++)
		std::cout << Number[i] << std::endl;

	return 0;
}