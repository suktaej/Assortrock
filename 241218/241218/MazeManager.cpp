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

void CMazeManager::Run()
{
	mMazeArray[0]->Output();
}
