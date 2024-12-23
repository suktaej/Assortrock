#include "MazeManager.h"
#include "Score.h"

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

		mScore = new CScore;
		mScore->SetScore(mMazeArray[Index]);
	}
}
void CMazeManager::RunScore()
{
	mScore->OutputScore();
}
<<<<<<< HEAD:241218/MazeManager.cpp

void CMazeManager::ResetMaze()
{

}
=======
//{
//	system("cls");
//	//점수출력
//	std::cout << "시간\t점수" << std::endl;
//
//	for (int i = 0; i < mScoreCount; ++i)
//	{
//		__int64 Minute = mScoreArray[i].Time / 60;
//		__int64 Second = mScoreArray[i].Time % 60;
//
//		std::cout << Minute << ":" << Second << "\t" <<
//			mScoreArray[i].Score << std::endl;
//	}
//	system("pause");
//}
//


>>>>>>> 3b54cb982d9f6ac9aad46879d29b5974319ce203:241218/241218/MazeManager.cpp
