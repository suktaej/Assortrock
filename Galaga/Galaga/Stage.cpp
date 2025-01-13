#include "Stage.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

void CStage::ComputeStageInfo()
{
}

bool CStage::Init(const char* FileName)
{
	FILE* File;

	fopen_s(&File, FileName, "rt");

	if (!File)
		return false;

	while (!feof(File))
	{
		char Line[32] = {};
		char* Context = nullptr;
		char* Result = nullptr;

		fgets(Line, 32, File);
		
		FStagInfo Info;
		Result = strtok_s(Line, ", ", &Context);
		Info.Time = atoi(Result);

	}
	fclose(File);
	return true;
}

void CStage::Run()
{
}
