#include<iostream>
#include<ctime>

#define ArrSize 25

void Shuffle(int*);
void PrintInfo(int*);
bool ChangeStar(int*, int);
int LineCheck(int*);

int main() {

	int Arr[ArrSize] = {};
	int AIArr[ArrSize] = {};
	int AIInput[ArrSize] = {};	//AI의 입력을 처리하기 위해 배열
	int AIInputCount = ArrSize;	//AI배열의 크기

	srand(time(0));
	rand();

	for (int i = 0;i < ArrSize;i++)
	{
		Arr[i] = i + 1;
		AIArr[i] = i + 1;
	}

	Shuffle(Arr);
	Shuffle(AIArr);

	for (int i = 0; i < 25; ++i)
	{
		AIInput[i] = AIArr[i];
	}

	int LineCount = 0;
	int AILineCount = 0;

	while (1)
	{
		system("cls");

		PrintInfo(Arr);
		std::cout << "Player Line Counter:" << LineCount << std::endl;
		std::cout << "==================================\n";
		PrintInfo(AIArr);
		std::cout << "AI Line Counter:" << AILineCount << std::endl;
		std::cout << "==================================\n";

		if (LineCount >= 5 || AILineCount >= 5)
			break;

		//입력	
		int Input = 0;
		std::cout << "Input Number:";
		std::cin >> Input;

		if (Input == 0)						//0입력 종료	
			break;
		else if (Input < 0 || Input>25)		//범위 오입력
			continue;

		if (ChangeStar(Arr, Input))			//사용자 입력을 사용자 배열에 적용
			continue;
		
		ChangeStar(AIArr, Input);			//사용자 입력을 AI배열에 적용

		// AI의 입력용 숫자에서 현재 입력한 이 숫자를 찾아서
		// 제거한다. AIInputCount에는 AI의 입력용 숫자가 몇개
		// 남았는지 저장해놓고 있다.
		for (int i = 0; i < AIInputCount; ++i)
		{
			if (AIInput[i] == Input)
			{
				// 현재 i번째 위치의 값과 배열의 사용할 수 있는
				// 부분 중 마지막 값을 바꾼다.
				AIInput[i] = AIInput[AIInputCount - 1];
				--AIInputCount;
				break;
			}
		}
		// 남은 입력용 배열에서 랜덤한 인덱스를 구하여 값을
		// 가져와 AI의 입력으로 사용한다.
		int	AISelect = rand() % AIInputCount;
		Input = AIInput[AISelect];

		// AI도 하나를 입력했기 때문에 해당 위치를 비워주고
		// AIInputCount를 1 감소시켜준다.
		AIInput[AISelect] = AIInput[AIInputCount - 1];
		--AIInputCount;

		ChangeStar(Arr, Input);			//AI 입력을 사용자 배열에 적용
		ChangeStar(AIArr, Input);		//AI 입력을 AI 배열에 적용

		//줄 수(bingo)확인
		LineCount = LineCheck(Arr);
		AILineCount = LineCheck(AIArr);
	}
	return 0;
}

void Shuffle(int* arr)
{
	for (int i = ArrSize - 1; i > 0; --i)
	{
		int j = rand() % ArrSize;
		std::swap(arr[i], arr[j]);
	}
}

void PrintInfo(int* arr)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i * 5 + j] == INT_MAX)
				std::cout << "*\t";
			else
				std::cout << arr[i * 5 + j] << "\t";
		}
		std::cout << "\n";
	}
}

bool ChangeStar(int* Arr, int Input)
{
	for (int i = 0;i < ArrSize;i++)
	{
		if (Input == Arr[i])
		{
			Arr[i] = INT_MAX;
			return false;
		}
	}
	return true;
}

int LineCheck(int* Arr)
{
	int LineCount = 0;
	for (int i = 0;i < 5;i++)
	{
		int HCheckCount = 0;	//line 확인 전 초기화
		int VCheckCount = 0;

		for (int j = 0;j < 5;j++)
		{
			if (Arr[i * 5 + j] == INT_MAX) HCheckCount++;	//가로줄 *개수 확인
			if (Arr[j * 5 + i] == INT_MAX) VCheckCount++;	//세로줄 *개수 확인
		}
		if (HCheckCount == 5)	LineCount++;
		if (VCheckCount == 5)	LineCount++;
	}

	int CCheckCount = 0;	//line 확인 전 초기화
	//좌하단
	for (int i = 0;i < 25;i += 6)
	{
		if (Arr[i] == INT_MAX) CCheckCount++;
	}
	if (CCheckCount == 5) LineCount++;

	//우하단
	CCheckCount = 0;
	for (int i = 4;i <= 20;i += 4)
	{
		if (Arr[i] == INT_MAX) CCheckCount++;
	}
	if (CCheckCount == 5) LineCount++;

	return LineCount;
}
