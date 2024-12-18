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

void CMazeManager::Run()
{
	mMazeArray[0]->Output();
}
