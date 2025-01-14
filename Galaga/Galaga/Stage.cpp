#include "Stage.h"

CStage::CStage()
{
}

CStage::~CStage()
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

		Result = strtok_s(Line, ", ", &Context);
		Info.Type = (ESpawnType)atoi(Result);
		
		Result = strtok_s(Line, ", ", &Context);
		Info.x = atoi(Result);
		
		Result = strtok_s(Line, ", ", &Context);
		Info.y = atoi(Result);
		Info.Dir = (ESpawnDir)atoi(Context);

		m_InfoList.emplace_back(Info);
	}
	fclose(File);

	QueryPerformanceFrequency(&m_Second);
	m_StageTime = 0.f;

	m_Buffer = new char[(m_Xsize + 1) * m_Ysize + 1];
	memset(m_Buffer, 0, (m_Xsize + 1) * m_Ysize + 1);

	return true;
}

void CStage::Run()
{
	system("cls");

	QueryPerformanceCounter(&m_Time);
	m_StageTime = 0.f;

	while (true)
	{
		LARGE_INTEGER Time;
		QueryPerformanceCounter(&Time);

		m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;
		m_StageTime += m_DeltaTime;

		m_Time = Time;
		
		ComputeStageInfo();
	}
}

void CStage::ComputeStageInfo()
{
}
