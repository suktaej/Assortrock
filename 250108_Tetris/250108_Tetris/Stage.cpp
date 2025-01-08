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
	
	//�� ���� �� \n ����, ��� ���� �Է� �� \0 ����
	m_OutputBuffer = new char[(k_Xsize + 1) * k_Ysize + 1];
	//��¹��� 0���� �ʱ�ȭ
	memset(m_OutputBuffer, 0, (k_Xsize + 1) * k_Ysize + 1);

	return true;
}

void FStage::Run()
{
	system("cls");

	//���� ��
	QueryPerformanceCounter(&m_Time);
	m_StageTime = 0.f;

	while (true) {
		//�ð����
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
	//Ŀ�� �ʱ�ȭ
	COORD InitPos = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), InitPos);

	for(int i=0;i<k_Ysize;i++)
	{
		for (int j = 0;j < k_Xsize;j++)
		{
			int Index = i *(k_Xsize+1) + j;
			//�迭 �ε��� ���̹Ƿ� -1
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

