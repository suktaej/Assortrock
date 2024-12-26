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
	
	//������ ��(���� ��)�� ���� ��� 
	//feof(File);
	//������ ���� �Ǵ��� �ִ� �Լ�
	//������ ���� �����ϸ� 0�� �ƴ� ��(true)��ȯ
	//���� ���� �ƴϸ� 0�� ��ȯ
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
