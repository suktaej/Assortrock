#include "Stage.h"
#include "ObjectManager.h"
#include "Block.h"

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
	
	//ù ��� ����
	FObjectManager::GetInst()->CreateObj<FBlock>();
	
	//�� �ʱ�ȭ
	m_Map.resize(k_Ysize, std::vector<char>(k_Xsize));
	MapReset();

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

		//Ȱ��ȭ �� ����� ���ٸ� ����� ����
		if(m_BlockActive==false)
			CreateBlock();
		//����� �ο�
		std::list<FObject*>::iterator iter = FObjectManager::GetInst()->GetObjList().begin();
		(*iter)->Update(m_DeltaTime);

		//���
		MapReset();
		//����� �����Ǿ��ٸ� ����� ����	
		if(m_BlockActive==false)
			FObjectManager::GetInst()->RemoveBlock();
		//�׷��� �ʴٸ� ����� ���
		else
			(*iter)->Output(m_Map);	

		Output();
	}
}

ECollisionType FStage::CheckCollison(FObject* Obj)
{
	FBlock* Block = dynamic_cast<FBlock*>(Obj);
	
	assert(Block);

	const COORD& Pos = Block->GetPos();
	const std::vector<std::vector<char>>& Shape = Block->GetShape();

	for (int i = 0; i < BLOCKSIZE;i++)
	{
		for (int j = 0; j < BLOCKSIZE; j++)
		{
			if (Shape[i][j] == '*')
			{
				int BlockX = Pos.X + j;
				int BlockY = Pos.Y + i;
				
				//���� �浹
				if (BlockX <= 0)
					return ECollisionType::LeftWall;
				if (BlockX >= k_Xsize-1)
					return ECollisionType::RightWall;
				if (BlockY < 0)
					return ECollisionType::End;
				if	(BlockY >= k_Ysize-1)
					return ECollisionType::Floor;
				
				//��� �浹
				//if (m_Map[BlockY][BlockX] == '+')

			}
		}
	}
	return ECollisionType::None;
}

void FStage::LockBlock(FObject* Obj)
{
	FBlock* Block = dynamic_cast<FBlock*>(Obj);

	assert(Block);

	const COORD& Pos = Block->GetPos();
	const std::vector<std::vector<char>>& Shape = Block->GetShape();

	for (int i = 0; i < BLOCKSIZE;i++)
	{
		for (int j = 0; j < BLOCKSIZE; j++)
		{
			if (Shape[i][j] == '*')
			{
				int BlockX = Pos.X + j;
				int BlockY = Pos.Y + i;
				
				m_Map[BlockY][BlockX] = '+';
			}
		}
	}
	m_BlockActive = false;
}

//����� ��Ȱ��ȭ�� ������ �� ��� ���� �� ��ġ �ʱ�ȭ
void FStage::CreateBlock()
{
	m_BlockActive = true;
	FObjectManager::GetInst()->CreateObj<FBlock>();
}

void FStage::MapReset()
{
	for (int i = 0;i < k_Ysize;i++)
	{
		for (int j = 0;j < k_Xsize;j++)
		{
			if (j == 0 || j == k_Xsize - 1 || i == k_Ysize - 1)
				m_Map[i][j] = '#';
			else if (m_Map[i][j] != '+')
				m_Map[i][j] = '.'; 
		}
	}
}

void FStage::Output()
{
	COORD InitPos = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), InitPos);
	
	for (int i = 0;i < k_Ysize;i++)
	{
		for (int j = 0;j < k_Xsize;j++)
			std::cout << m_Map[i][j];
		std::cout << '\n';
	}
}
