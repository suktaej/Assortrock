#include "Maze.h"
#include "Player.h"
#include "ScoreItem.h"
#include "DamageItem.h"
#include "HealItem.h"

FMaze::FMaze()
{
}

FMaze::~FMaze()
{
	if (nullptr != m_MazeArray)
	{
		for (int i = 0;i < m_Ysize;i++)
		{
			delete[] m_MazeArray[i];
		}
		delete[] m_MazeArray;
	}

	if (nullptr != m_Buffer)
		delete[] m_Buffer;
}

bool FMaze::Init()
{
	//오브젝트 배열 초기화
	m_ObjList = new FObject * [m_ObjCapacity];

	FILE* File = nullptr;

	fopen_s(&File, "Maze1.txt", "rt");
	
	if (!File)
		return false;

	char Line[64] = {};

	fgets(Line, 64, File);
	
	char* YString = nullptr;
	char* XString = strtok_s(Line, ", ", &YString);

	m_Ysize = atoi(YString);
	m_Xsize = atoi(XString);

	m_MazeArray = new ETileType * [m_Ysize];
	m_Buffer = new char[(m_Xsize + 1) * m_Ysize + 1];
	memset(m_Buffer, 0, sizeof(char) * ((m_Xsize + 1) * m_Ysize + 1));

	for (int i = 0;i < m_Ysize;i++)
	{
		m_MazeArray[i] = new ETileType[m_Xsize];
		fgets(Line, 64, File);

		for (int j = 0;j < m_Xsize;j++)
			m_MazeArray[i][j] = (ETileType)(Line[j] - '0');
	}

	fclose(File);
	return true;
}


void FMaze::Run()
{
	Reset();
	system("cls");
	
	__int64 TimeStart = time(0);

	//Buffer용 Index
	int StartIndex = m_StartPos.Y * (m_Xsize + 1) + m_StartPos.X;
	//int GoalIndex = m_GoalPos.Y * (m_Xsize + 1) + m_GoalPos.X;

	FPlayer* Player = new FPlayer;
	Player->Init();
	Player->SetPos(m_StartPos);
	//현재값을 넘겨줌
	Player->SetMaze(this);
	
	//시작 시 Player의 좌표는 Start와 동일
	m_PrevPlayerIndex = StartIndex;
	//출력용
	m_PrevPlayerOutput = 0;

	while (true)
	{
		//키보드 입력을 받으면 m_MazeArray에서 Player의 위치가 변경
		Player->Update();
		//Player의 현재 위치(Update 후)를 받아옴
		COORD PlayerPos = Player->GetPos();
		//Buffer용 인덱스
		int PlayerIndex = PlayerPos.Y * (m_Xsize + 1) + PlayerPos.X;

		for (int i = 0;i < m_ObjCount;i++)
			m_ObjList[i]->Update();
		
		//오브젝트와 플레이어의 충돌처리
		for (int i = 0;i < m_ObjCount;i++)
		{
			if (PlayerPos.X == m_ObjList[i]->GetPos().X &&
				PlayerPos.Y == m_ObjList[i]->GetPos().Y)
			{
				if (nullptr != dynamic_cast<FScoreItem*>(m_ObjList[i]))
					m_Score += 10;
				else if (nullptr != dynamic_cast<FHealItem*>(m_ObjList[i]))
					Player->AddHP(1);
				else if (nullptr != dynamic_cast<FDamageItem*>(m_ObjList[i]))
				{
					if (Player->AddHP(-1))
					{
						SAFE_DELETE(Player);
						return;
					}
				}
				//좌표가 겹쳤을 경우 길로 출력
				//실제 좌표의 값은 m_MazeArray에 존재
				//출력만 변경
				m_Buffer[PlayerIndex] = ' ';
				//충돌한 아이템을 제거
				SwapNPop(i);
				break;
			}
		}
		//Player와 충돌할 경우? 
		//m_Buffer[StartIndex] = 'S';
		//m_Buffer[GoalIndex] = 'G';

		//아이템 출력
		for (int i = 0;i < m_ObjCount;i++)
			m_ObjList[i]->Output(m_Buffer, m_Xsize + 1);

		//플레이어의 이전 프레임 인덱스 복구
		if (m_PrevPlayerOutput != 0)
			m_Buffer[m_PrevPlayerIndex] = m_PrevPlayerOutput;
		//플레이어의 현재 위치를 저장
		m_PrevPlayerIndex = PlayerIndex;
		//플레이어 현재 위치의 문자를 저장
		m_PrevPlayerOutput = m_Buffer[PlayerIndex];

		m_Buffer[PlayerIndex] = 'P';
	
		COORD   Cursor = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);

		std::cout << m_Buffer;

		if (GetTile(PlayerPos.X, PlayerPos.Y) == ETileType::Goal)
			break;

		InfoOutput(TimeStart, Player);
	}
	SAFE_DELETE(Player);
}

void FMaze::Reset()
{
	//남은 오브젝트 전부 제거
	for (int i = 0;i < m_ObjCount;i++)
		SAFE_DELETE(m_ObjList[i]);

	m_ObjCount = 0;
	m_Score = 0;
	m_Time = 0;

	memset(m_Buffer, 0, sizeof(char) * ((m_Xsize + 1) * m_Ysize + 1));

	for (int i = 0;i < m_Ysize;i++)
	{
		for (int j = 0;j < m_Xsize;j++)
		{
			int BufferIndex = i * (m_Xsize + 1) + j;

			switch (m_MazeArray[i][j])
			{
			case ETileType::Road:
				m_Buffer[BufferIndex] = '.';
				break;
			case ETileType::Wall:
				m_Buffer[BufferIndex] = '#';
				break;
			case ETileType::Start:
				m_StartPos.X = j;
				m_StartPos.Y = i;
				m_Buffer[BufferIndex] = 'S';
				break;
			case ETileType::Goal:
				m_GoalPos.X = j;
				m_GoalPos.Y = i;
				m_Buffer[BufferIndex] = 'G';
				break;
			case ETileType::Score:
			{
				FScoreItem* ScoreItem = new FScoreItem;

				ScoreItem->Init();
				ScoreItem->SetPos(j, i);
				
				ReAlloc();
				m_ObjList[m_ObjCount] = ScoreItem;
				m_ObjCount++;

				m_Buffer[BufferIndex] = ' ';
				break;
			}
			case ETileType::Damage:
			{
				FDamageItem* DamageItem = new FDamageItem;
	
				DamageItem->Init();
				DamageItem->SetPos(j, i);

				ReAlloc();
				m_ObjList[m_ObjCount] = DamageItem;
				m_ObjCount++;
				
				m_Buffer[BufferIndex] = ' ';
				break;
			}
			case ETileType::Heal:
			{
				FHealItem* HealItem = new FHealItem;

				HealItem->Init();
				HealItem->SetPos(j, i);

				ReAlloc();
				m_ObjList[m_ObjCount] = HealItem;
				m_ObjCount++;
				
				m_Buffer[BufferIndex] = ' ';
				break;
			}
			}
		}
		int BufferIndex = i * (m_Xsize + 1) + m_Xsize;
		m_Buffer[BufferIndex] = '\n';
	}
}

void FMaze::ReAlloc()
{
	if (m_ObjCapacity == m_ObjCount)
	{
		m_ObjCapacity *= 2;
		FObject** Temp = new FObject * [m_ObjCapacity];
		memcpy(Temp, m_ObjList, sizeof(FObject*) * m_ObjCount);
		delete[] m_ObjList;
		m_ObjList = Temp;
	}
}

void FMaze::SwapNPop(int idx)
{
	//현재 오브젝트가 배열 내 마지막 인덱스가 아닐 경우
	//마지막 인덱스와 교체
	if (idx < m_ObjCount)
	{
		FObject* Temp = m_ObjList[idx];
		m_ObjList[idx] = m_ObjList[m_ObjCount-1];
		m_ObjList[m_ObjCount - 1] = Temp;
	}
	//마지막 인덱스를 제거하고 배열의 크기(Count)를 감소
	delete m_ObjList[m_ObjCount - 1];
	m_ObjList[m_ObjCount - 1] = nullptr;
	--m_ObjCount;
}

void FMaze::InfoOutput(__int64 TimeStart, FPlayer* Player)
{	
	//시간 출력
	__int64 Time = time(0);
	m_Time = Time - TimeStart;

	COORD   TimePos;
	TimePos.X = m_Xsize + 2;
	TimePos.Y = 2;

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), TimePos); 

	__int64 Minute = m_Time / 60;
	__int64 Second = m_Time % 60;

	std::cout << Minute << ":" << Second << std::endl;

	//점수 출력
	COORD   ScorePos;
	ScorePos.X = m_Xsize + 2;
	ScorePos.Y = 3;

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
	std::cout << "Score : " << m_Score;

	//체력 출력
	COORD   HPPos;
	HPPos.X = m_Xsize + 2;
	HPPos.Y = 1;

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), HPPos);
	std::cout << "HP : ";

	int HP = Player->GetHP();

	for (int i = 0; i < 5; ++i)
	{
		if (i < HP)
			std::cout << "♥";

		else
			std::cout << "  ";
	}
}

