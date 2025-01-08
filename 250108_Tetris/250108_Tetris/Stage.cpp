#include "Stage.h"
#include "ObjectManager.h"
#include "IBlock.h"
#include "TBlock.h"

FStage::FStage()
{
}

FStage::~FStage()
{
}

bool FStage::Init()
{	
	QueryPerformanceFrequency(&m_Second);
	m_StageTime = 0.f;
	
	//행 종료 시 \n 문자, 모든 문자 입력 후 \0 문자
	m_OutputBuffer = new char[(k_Xsize + 1) * k_Ysize + 1];
	//출력버퍼 0으로 초기화
	memset(m_OutputBuffer, 0, (k_Xsize + 1) * k_Ysize + 1);

	return true;
}

void FStage::Run()
{
	system("cls");

	//현재 값
	QueryPerformanceCounter(&m_Time);
	m_StageTime = 0.f;

	while (true) {
		//시간계산
		LARGE_INTEGER Time;
		QueryPerformanceCounter(&Time);

		m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;
		m_StageTime += m_DeltaTime;
		m_Time = Time;
	
		if(m_BlockActive==true)
			CreateBlock();
		//m_CurrentBlock->Update(m_DeltaTime);
		//FObjectManager::GetInst()->Update(m_DeltaTime);
		CreateMap();
		//FObjectManager::GetInst()->Output(m_OutputBuffer);
		Output();
	}
}

void FStage::CreateBlock()
{
	m_BlockActive = false;
	FObjectManager::GetInst()->CreateObj<FIBlock>();

	//auto& ObjList = FObjectManager::GetInst()->GetObjList();
	//std::list<FObject*>::iterator iter = ObjList.begin();

	//if (!ObjList.empty())
	//{
	//	while (true)
	//	{
	//		if ((*iter)->GetState() == false)
	//		{
	//			m_CurrentBlock = *iter;
	//			break;
	//		}
	//		else
	//			iter++;
	//	}
	//}
}

void FStage::CreateMap()
{
	//커서 초기화
	COORD InitPos = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), InitPos);

	for(int i=0;i<k_Ysize;i++)
	{
		for (int j = 0;j < k_Xsize;j++)
		{
			int Index = i *(k_Xsize+1) + j;
			//배열 인덱스 값이므로 -1
			if (j == 0 || j == k_Xsize-1 || i == k_Ysize-1)
				m_OutputBuffer[Index] = '#';
			else
				m_OutputBuffer[Index] = ' ';
		}
		m_OutputBuffer[i * (k_Xsize + 1) + k_Xsize] = '\n';
	}
}

void FStage::Output()
{
	std::cout << m_OutputBuffer;
}

