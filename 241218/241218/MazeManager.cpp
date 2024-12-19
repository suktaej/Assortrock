#include "MazeManager.h"

CMazeManager* CMazeManager::mInst = nullptr;

CMazeManager::CMazeManager()
{
}

CMazeManager::~CMazeManager()
{
	if (nullptr != mMazeArray)
	{
		for (int i = 0; i < mMazeCount; i++)
		{
			delete mMazeArray[i];
			mMazeArray[i] = nullptr;
		}
		delete[] mMazeArray;
	}
}

bool CMazeManager::Init()
{
	FILE* File = nullptr;
	fopen_s(&File, "MazeList.txt", "rt");

	if (!File)
		return false;

	char  Line[128] = {};

	fgets(Line, 128, File);
	mMazeCount = atoi(Line);
	//MazeList에서 첫번째 값(미로의 갯수)를 읽어와 int값으로 저장
	mMazeArray = new CMaze * [mMazeCount];
	//읽어온 미로의 주소를 저장하는 배열에 미로의 수 만큼 동적할당

	for (int i = 0;i < mMazeCount;i++)
	{
		fgets(Line, 128, File);
		//MazeList의 나머지값(line2 ~ )을 읽어옴
		int Length = strlen(Line);
		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;
		//라인의 마지막 값이 개행일 경우 null값을 입력
		//파일의 이름만 남음

		mMazeArray[i] = new CMaze;
		mMazeArray[i]->Init(Line);
	}

	fclose(File);
	return true;
}

int CMazeManager::Menu()
{
	system("cls");
	for (int i = 0;i < mMazeCount;i++)
	{
		std::cout << i + 1 << ". " << mMazeArray[i]->GetName() << std::endl;
	}
	std::cout << mMazeCount + 1 << ". 뒤로가기" << std::endl;
	std::cout << "선택: ";
	int Input;
	std::cin >> Input;

	if (Input<1 || Input>mMazeCount + 1)
		return 0;

	return Input;
}

void CMazeManager::Run()
{
	while (true)
	{
		int Input = Menu();
		if (Input == 0)
			continue;
		else if (Input == mMazeCount + 1)
			break;

		int Index = Input - 1;
		mMazeArray[Index]->Run();

		__int64 Time = mMazeArray[Index]->GetTime();
		if (mScoreCount < 5)
		{
			//시간 정렬(작은 시간에서 큰 시간 순서로)
			mScoreArray[mScoreCount] = Time;
			mScoreCount++;
		}
		else
		{
			//배열이 다 찼을 때, 현재 걸린 시간과 비교하여 현재 걸린시간이 더 작으면 한 칸씩 뒤로 밀고 그 자리에 현재 시간을 입력
		}
	}
}

void CMazeManager::RunScore()
{
	system("cls");
	//점수출력
	for (int i = 0;i < mScoreCount;i++)
	{
		std::cout << mScoreArray[i] << std::endl;
	}
	system("pause");
}
