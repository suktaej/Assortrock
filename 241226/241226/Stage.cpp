#include "Stage.h"
#include "ObjectManager.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init(const char* FileName)
{
	FILE* File = nullptr;
	fopen_s(&File, FileName, "rt");

	if (!File)
		return false;
	
	//파일의 수(라인 수)가 많을 경우 
	//feof(File);
	//파일의 끝을 판단해 주는 함수
	//파일의 끝에 도달하면 0이 아닌 값(true)반환
	//파일 끝이 아니면 0을 반환
	while (!feof(File))
	{
		char Line[64] = {};
		fgets(Line, 64, File);
		
		char* Context = nullptr;
		char* Result = nullptr;
		Result = strtok_s(Line, ", ", &Context);
		
		FStageInfo Info;
		Info.Time = atoi(Result);
		
		Result = strtok_s(Line, ", ", &Context);
		Info.Type = (EObjectType)atoi(Result);
		
		Result = strtok_s(Line, ", ", &Context);
		Info.xPos = atoi(Result);
		
		Result = strtok_s(Line, ", ", &Context);
		Info.yPos = atoi(Result);

		Info.Dir = (ESpawnDir)atoi(Context);

		mInfoList.emplace_back(Info);
	}

	fclose(File);
	return true;
}

void CStage::Run()
{
	system("cls");
	while (true)
	{
		CObjectManager::GetInst()->Update();
		CObjectManager::GetInst()->Output();
	}
}
