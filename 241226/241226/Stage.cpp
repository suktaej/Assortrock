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
		char Line[128] = {};
		fgets(Line, 128, File);
		
		char* Context = nullptr;
		char* Result = nullptr;
		Result = strtok_s(Line, ", ", &Context);
		
		FStageInfo Info;
		Info.Time = atoi(Result);
		
		Result = strtok_s(nullptr, ", ", &Context);
		Info.Type = (ESpawnType)atoi(Result);
		
		Result = strtok_s(nullptr, ", ", &Context);
		Info.xPos = atoi(Result);
		
		Result = strtok_s(nullptr, ", ", &Context);
		Info.yPos = atoi(Result);

		Info.Dir = (ESpawnDir)atoi(Context);

		mInfoList.emplace_back(Info);
	}

	fclose(File);
	
	QueryPerformanceFrequency(&mSecond);	//���ػ� Ÿ�̸Ӱ� 1�ʴ� �󸶳� �帣�� �� ������
	mStageTime = 0.f;

	mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];
	memset(mOutputBuffer, 0, (mCountX + 1) * mCountY + 1);

	return true;
}

void CStage::Run()
{
	system("cls");
	QueryPerformanceCounter(&mTime);		//���� ������ ���ػ� Ÿ�̸��� ���� �����´�
	mStageTime = 0.f;
	
	while (true)
	{
		LARGE_INTEGER Time;
		QueryPerformanceCounter(&Time);		
		//(���� �� - ���� ��)/�ʴ� �� = �帥 �ð�
		
		mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
		mStageTime += mDeltaTime; //�ð� ����
		mTime = Time;		 //�� �����Ӹ��� �ð��� ����
		
		ComputeStageInfo();
		//stage ���� ó��
		CObjectManager::GetInst()->Update(mDeltaTime);

		COORD Start = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Start);
		
		int Index = 0;
		for (int i = 0;i < mCountY;i++)
		{
			for (int j = 0;j < mCountX;j++)
			{
				Index = i * (mCountX + 1) + j;
				if (i == 0 || j == 0 || i == mCountY - 1 || j == mCountX - 1)
				{
					mOutputBuffer[Index] = '#';
					//std::cout << "#";
				}
				else
				{
					mOutputBuffer[Index] = ' ';
					//std::cout << " ";
				}
			}
			mOutputBuffer[i * (mCountX + 1) + mCountX] = '\n';
			//std::cout << std::endl;
		}
		CObjectManager::GetInst()->Output(mOutputBuffer);
		//buffer ���
		std::cout << mOutputBuffer;

		COORD ScorePos;
		ScorePos.X = mCountX + 4;
		ScorePos.Y = mCountY = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
		std::cout << "Score: " << mScore;
	}
}

void CStage::ComputeStageInfo()
{
	if (!mInfoList.empty())
	{
		//����Ʈ�� �ִ� ù ��° ��Ҹ� ���´�
		const FStageInfo& Info = mInfoList.front();

		if (mStageTime >= Info.Time)
		{
			CEnemy* Enemy = nullptr;

			switch (Info.Type)
			{
			case ESpawnType::EnemyNormal:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			case ESpawnType::EnemyHard:
				break;
			case ESpawnType::EnemyBoss:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			}
			Enemy->SetType(EObjectType::Enemy);

			Enemy->SetPos(Info.xPos, Info.yPos);
			mInfoList.pop_front();
		}
	}
}

