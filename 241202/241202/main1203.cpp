#include <iostream>
#include <ctime>
#include <cstdlib>

void shuffle(int[], int);
void shuffle2(int[], int);

int main()
{
	int Num[20] = {};
	int Input[2] = {};
	int cnt = 1;
	int Score = 0;

	for (int i = 0;i < 10;i++) {
		Num[i] = cnt;
		Num[i + 10] = cnt;
		cnt++;
	}
	//배열생성

	srand(time(0));
	rand();

	shuffle2(Num,20);

	do
	{
		system("cls");
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 10;j++) {
				if (Num[i * 10 + j] == INT_MAX) std::cout << '*'<<"\t";
				else std::cout << Num[i*10+j] << "\t";
			}
			std::cout << std::endl;
		}
		//배열출력
		std::cout << "Input Number(ex:1 11):";
		std::cin >> Input[0] >> Input[1];
		//if (Input[0] == -1 || Input[1] == -1)
		//	break;

		if (Num[Input[0]] == Num[Input[1]])
		{
			std::cout << "Same" << std::endl;
			Num[Input[0]] = INT_MAX;
			Num[Input[1]] = INT_MAX;
			Score++;
		}
		else
			std::cout << "Diff" << std::endl;

		if(Score == 10) break;
		//모두 매칭 확인
//		bool Exit = true;
//
//		for (int i = 0;i < sizeof(Num) / sizeof(int);i++) {
//			if (Num[i] != INT_MAX) {
//				Exit = false;
//				break;
//			}
//		}
//
//		if (Exit == true) break;

	} while (1);
	//진행
	return 0;
}

void shuffle(int arr[], int size)
{
	for (int i = size - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		std::swap(arr[i], arr[j]);
	}
}

void shuffle2(int arr[], int size) {

	for (int i = 0;i < 100;i++) {
		int RandomIndex1 = rand() % 20;
		int RandomIndex2 = rand() % 20;
		int temp;

		temp = arr[RandomIndex1];
		arr[RandomIndex1] = arr[RandomIndex2];
		arr[RandomIndex2] = temp;
	}
}
