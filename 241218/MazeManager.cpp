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
	//MazeList���� ù��° ��(�̷��� ����)�� �о�� int������ ����
	mMazeArray = new CMaze * [mMazeCount];
	//�о�� �̷��� �ּҸ� �����ϴ� �迭�� �̷��� �� ��ŭ �����Ҵ�

	for (int i = 0;i < mMazeCount;i++)
	{
		fgets(Line, 128, File);
		//MazeList�� ��������(line2 ~ )�� �о��
		int Length = strlen(Line);
		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;
		//������ ������ ���� ������ ��� null���� �Է�
		//������ �̸��� ����

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
	std::cout << mMazeCount + 1 << ". �ڷΰ���" << std::endl;
	std::cout << "����: ";
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
//	//�������
//	std::cout << "�ð�\t����" << std::endl;
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
