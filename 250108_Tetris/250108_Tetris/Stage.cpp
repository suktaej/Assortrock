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
	HideCursor();
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
		if (m_BlockActive == false)
		{
			m_BlockActive = true;
			FObjectManager::GetInst()->CreateObj<FBlock>();
		}
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
		
		//하나의 라인이 생성된다면 라인 삭제
		//라인이 다 찰 경우 종료
		if (LineClear())
			return;
		Output();
	}
}

ECollisionType FStage::CheckCollison(FObject* Obj,int PrevX, int PrevY)
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
				if (BlockX <= 0 ||BlockX >= k_Xsize-1)
					return ECollisionType::Wall;
				if (BlockY < 0)
					return ECollisionType::End;
				if	(BlockY >= k_Ysize-1)
					return ECollisionType::Floor;
				
				//블록 충돌
				if (m_Map[BlockY][BlockX] == '+')
				{
					if (BlockX == PrevX)
						return ECollisionType::Wall;
					else
						return ECollisionType::Floor;
				}
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

void FStage::MapReset()
{
	for (int i = 0;i < k_Ysize;i++)
	{
		for (int j = 0;j < k_Xsize;j++)
		{	
			//벽면은 #으로 출력
			if (j == 0 || j == k_Xsize - 1 || i == k_Ysize - 1)
				m_Map[i][j] = '#';
			else if (i == 3)
				m_Map[i][j] = ',';
			// 고정된 블록(+)은 유지
			else if (m_Map[i][j] != '+')
				m_Map[i][j] = '.';
		}
	}
}

bool FStage::LineClear()
{
	//바닥부터 역순으로 탐색
	for (int i = k_Ysize-1;i > 0;i--)
	{
		for (int j = 1;j < k_Xsize-1;j++)
		{	
			//라인이 모두 채워지면 카운터는 0
			if (m_Map[i][j] == '+')
				m_LineCounter--;
			//블록 생성 지점에 블록이 고정될 경우 종료
			if (m_Map[4][j] == '+')
				return true;
		}
		
		if (m_LineCounter == 0)
		{
			m_Score += 100;
			//현재 라인을 새로운 변수에 할당
			//새 변수를 기준으로 라인 위쪽으로 역 탐색
			for (int k = i;k > 0;k--)
			{
				//모든 라인을 1씩 Y축으로 이동
				for (int j = 1;j < k_Xsize - 1;j++)
					m_Map[k][j] = m_Map[k - 1][j];
			}
			//라인을 아래로 내렸기 때문에 탐색은 현재 라인에서 다시 시작
			i--;
		}
		m_LineCounter = k_Xsize - 2;
	}
	return false;
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

	COORD ScorePos = { k_Xsize+2,2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
	std::cout << "Score: " << m_Score;
}

void FStage::HideCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);

	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
