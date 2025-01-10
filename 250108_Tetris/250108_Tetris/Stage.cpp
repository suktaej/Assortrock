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
	
	//첫 블록 생성
	FObjectManager::GetInst()->CreateObj<FBlock>();
	
	//맵 초기화
	m_Map.resize(k_Ysize, std::vector<char>(k_Xsize));
	MapReset();

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

		//활성화 된 블록이 없다면 블록을 생성
		if(m_BlockActive==false)
			CreateBlock();
		//제어권 부여
		std::list<FObject*>::iterator iter = FObjectManager::GetInst()->GetObjList().begin();
		(*iter)->Update(m_DeltaTime);

		//출력
		MapReset();
		//블록이 고정되었다면 블록을 제거	
		if(m_BlockActive==false)
			FObjectManager::GetInst()->RemoveBlock();
		//그렇지 않다면 블록을 출력
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
				
				//벽면 충돌
				if (BlockX <= 0)
					return ECollisionType::LeftWall;
				if (BlockX >= k_Xsize-1)
					return ECollisionType::RightWall;
				if (BlockY < 0)
					return ECollisionType::End;
				if	(BlockY >= k_Ysize-1)
					return ECollisionType::Floor;
				
				//블록 충돌
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

//블록이 비활성화될 때마다 새 블록 생성 및 위치 초기화
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
