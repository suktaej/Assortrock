#include "StageManager.h"

DEFINITION_SINGLE(CStageManager)

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

	char Line[32] = {};

	fgets(Line, 32, File);
	m_Count = atoi(Line);

	m_vecFileName.resize(m_Count);
	m_vecName.resize(m_Count);

	for (int i = 0;i < m_Count;i++)
	{
		fgets(Line, 32, File);
		
		int Len = (int)strlen(Line);

		if (Line[Len - 1] == '\n')
			Line[Len - 1] = 0;

		m_vecFileName[i] = Line;

		char* Context = nullptr;
		m_vecName[i] = strtok_s(Line, ".", &Context);
	}

	fclose(File);
	return true;
}

void CStageManager::Run()
{
	m_Stage = nullptr;

	while (true)
	{
		system("cls");
		size_t Size = m_vecName.size();

		for (size_t i = 0;i < Size;i++)
			std::cout << i + 1 << ". " << m_vecName[i] << std::endl;

		std::cout << Size + 1 << ". 뒤로가기" << std::endl;
		std::cout << "스테이지를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input <= 0 || Input > Size + 1)
			continue;
		else if (Input == Size + 1)
			break;

		m_Stage = new CStage;
		m_Stage->Init(m_vecFileName[Input - 1].c_str());
		m_Stage->Run();
	}
	SAFE_DELETE(m_Stage);
}
