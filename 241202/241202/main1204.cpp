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
	int AIInput[ArrSize] = {};	//AI�� �Է��� ó���ϱ� ���� �迭
	int AIInputCount = ArrSize;	//AI�迭�� ũ��

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

		//�Է�	
		int Input = 0;
		std::cout << "Input Number:";
		std::cin >> Input;

		if (Input == 0)						//0�Է� ����	
			break;
		else if (Input < 0 || Input>25)		//���� ���Է�
			continue;

		if (ChangeStar(Arr, Input))			//����� �Է��� ����� �迭�� ����
			continue;
		
		ChangeStar(AIArr, Input);			//����� �Է��� AI�迭�� ����

		// AI�� �Է¿� ���ڿ��� ���� �Է��� �� ���ڸ� ã�Ƽ�
		// �����Ѵ�. AIInputCount���� AI�� �Է¿� ���ڰ� �
		// ���Ҵ��� �����س��� �ִ�.
		for (int i = 0; i < AIInputCount; ++i)
		{
			if (AIInput[i] == Input)
			{
				// ���� i��° ��ġ�� ���� �迭�� ����� �� �ִ�
				// �κ� �� ������ ���� �ٲ۴�.
				AIInput[i] = AIInput[AIInputCount - 1];
				--AIInputCount;
				break;
			}
		}
		// ���� �Է¿� �迭���� ������ �ε����� ���Ͽ� ����
		// ������ AI�� �Է����� ����Ѵ�.
		int	AISelect = rand() % AIInputCount;
		Input = AIInput[AISelect];

		// AI�� �ϳ��� �Է��߱� ������ �ش� ��ġ�� ����ְ�
		// AIInputCount�� 1 ���ҽ����ش�.
		AIInput[AISelect] = AIInput[AIInputCount - 1];
		--AIInputCount;

		ChangeStar(Arr, Input);			//AI �Է��� ����� �迭�� ����
		ChangeStar(AIArr, Input);		//AI �Է��� AI �迭�� ����

		//�� ��(bingo)Ȯ��
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
		int HCheckCount = 0;	//line Ȯ�� �� �ʱ�ȭ
		int VCheckCount = 0;

		for (int j = 0;j < 5;j++)
		{
			if (Arr[i * 5 + j] == INT_MAX) HCheckCount++;	//������ *���� Ȯ��
			if (Arr[j * 5 + i] == INT_MAX) VCheckCount++;	//������ *���� Ȯ��
		}
		if (HCheckCount == 5)	LineCount++;
		if (VCheckCount == 5)	LineCount++;
	}

	int CCheckCount = 0;	//line Ȯ�� �� �ʱ�ȭ
	//���ϴ�
	for (int i = 0;i < 25;i += 6)
	{
		if (Arr[i] == INT_MAX) CCheckCount++;
	}
	if (CCheckCount == 5) LineCount++;

	//���ϴ�
	CCheckCount = 0;
	for (int i = 4;i <= 20;i += 4)
	{
		if (Arr[i] == INT_MAX) CCheckCount++;
	}
	if (CCheckCount == 5) LineCount++;

	return LineCount;
}
