#include "StageManager.h"

CStageManager* CStageManager::mInst = nullptr;

CStageManager::CStageManager()
{
}

CStageManager::~CStageManager()
{
}

bool CStageManager::Init()
{
	FILE* File = nullptr;
	fopen_s(&File, "StageList.txt", "rt");
	if (!File)
		return false;

	char Line[64] = {};
	fgets(Line, 64, File);
	mStageCount = atoi(Line);


	//mvecFileName.reserve(mStageCount);
	mvecFileName.resize(mStageCount);

	for (int i = 0;i < mStageCount;i++)
	{
		fgets(Line, 64, File);

		int Length = (int)strlen(Line);
		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;
		//������ ���ڰ� ������ ��� null�� ����

		//mvecFileName.emplace_back(Line);
		//�Է��� ������ �� �� emplace ����
		//mvecFileName[i] = Line;
		//�Է� ������ �˰� �����Ƿ� resize�� ������ Ȯ�� �� ����
		char *Context;
		mvecFileName[i] = strtok_s(Line, ".",&Context);
	}

	fclose(File);
	return true;
}

void CStageManager::Run()
{
	mStage = nullptr;

	while (true)
	{
		system("cls");
		size_t Size = mvecFileName.size();
		//unsigned __int64

		for (size_t i = 0;i < Size;i++)
		{
			std::cout << i + 1 << "." << mvecFileName[i] << std::endl;
		}

		std::cout << Size + 1 << ".Back" << std::endl;
		std::cout << "Select Stage: ";
		int Input;
		std::cin >> Input;

		if (Input <= 0 || Input > Size + 1)
			continue;
		else if (Input == Size + 1)
			break;

		mStage = new CStage;
		mStage->Init(mvecFileName[Input - 1].c_str());
		//c_str ���ڿ� ������ ��ȯ
		mStage->Run();
	}
	SAFE_DELETE(mStage);
}
