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
		//마지막 문자가 개행일 경우 null로 변경

		//mvecFileName.emplace_back(Line);
		//입력할 개수를 모를 때 emplace 권장
		//mvecFileName[i] = Line;
		//입력 개수를 알고 있으므로 resize로 공간을 확보 후 대입
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
		//c_str 문자열 포인터 반환
		mStage->Run();
	}
	SAFE_DELETE(mStage);
}
