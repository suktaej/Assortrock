#include "Stage.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "Player.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

void CStage::ComputeStageInfo()
{
	if (!mInfoList.empty())
	{
		//리스트에 있는 첫 번째 요소를 얻어온다
		const FStageInfo& Info = mInfoList.front();

		if (mStageTime >= Info.Time)
		{
			CEnemy* Enemy = nullptr;
			switch (Info.Type)
			{
			case EObjectType::EnemyNormal:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			case EObjectType::EnemyHard:
				break;
			case EObjectType::Boss:
				break;
			}
			Enemy->SetPos(Info.xPos, Info.yPos);
			mInfoList.pop_front();
		}
	}
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
	
	QueryPerformanceFrequency(&mSecond);	//고해상도 타이머가 1초당 얼마나 흐르는 지 가져옴
	mStageTime = 0.f;
	return true;
}

void CStage::Run()
{
	system("cls");
	QueryPerformanceCounter(&mTime);		//현재 윈도우 고해상도 타이머의 값을 가져온다
	mStageTime = 0.f;
	
	while (true)
	{
		LARGE_INTEGER Time;
		QueryPerformanceCounter(&Time);		
		//(현재 값 - 이전 값)/초당 값 = 흐른 시간
		
		mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
		mStageTime += mDeltaTime; //시간 누적
		mTime = Time;		 //매 프레임마다 시간을 갱신
		
		ComputeStageInfo();
		//stage 정보 처리

		COORD Start = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Start);

		for (int i = 0;i < mCountY;i++)
		{
			for (int j = 0;j < mCountX;j++)
			{
				if (i == 0 || j == 0 || i == mCountY - 1 || j == mCountX - 1)
					std::cout << "#";
				else
					std::cout << " ";
			}
			std::cout << std::endl;
		}
		CObjectManager::GetInst()->Output();
		//buffer 출력
	}
}
