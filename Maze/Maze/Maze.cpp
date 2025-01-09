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
	//������Ʈ �迭 �ʱ�ȭ
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

	//Buffer�� Index
	int StartIndex = m_StartPos.Y * (m_Xsize + 1) + m_StartPos.X;
	//int GoalIndex = m_GoalPos.Y * (m_Xsize + 1) + m_GoalPos.X;

	FPlayer* Player = new FPlayer;
	Player->Init();
	Player->SetPos(m_StartPos);
	//���簪�� �Ѱ���
	Player->SetMaze(this);
	
	//���� �� Player�� ��ǥ�� Start�� ����
	m_PrevPlayerIndex = StartIndex;
	//��¿�
	m_PrevPlayerOutput = 0;

	while (true)
	{
		//Ű���� �Է��� ������ m_MazeArray���� Player�� ��ġ�� ����
		Player->Update();
		//Player�� ���� ��ġ(Update ��)�� �޾ƿ�
		COORD PlayerPos = Player->GetPos();
		//Buffer�� �ε���
		int PlayerIndex = PlayerPos.Y * (m_Xsize + 1) + PlayerPos.X;

		for (int i = 0;i < m_ObjCount;i++)
			m_ObjList[i]->Update();
		
		//������Ʈ�� �÷��̾��� �浹ó��
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
				//��ǥ�� ������ ��� ��� ���
				//���� ��ǥ�� ���� m_MazeArray�� ����
				//��¸� ����
				m_Buffer[PlayerIndex] = ' ';
				//�浹�� �������� ����
				SwapNPop(i);
				break;
			}
		}
		//Player�� �浹�� ���? 
		//m_Buffer[StartIndex] = 'S';
		//m_Buffer[GoalIndex] = 'G';

		//������ ���
		for (int i = 0;i < m_ObjCount;i++)
			m_ObjList[i]->Output(m_Buffer, m_Xsize + 1);

		//�÷��̾��� ���� ������ �ε��� ����
		if (m_PrevPlayerOutput != 0)
			m_Buffer[m_PrevPlayerIndex] = m_PrevPlayerOutput;
		//�÷��̾��� ���� ��ġ�� ����
		m_PrevPlayerIndex = PlayerIndex;
		//�÷��̾� ���� ��ġ�� ���ڸ� ����
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
	//���� ������Ʈ ���� ����
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
	//���� ������Ʈ�� �迭 �� ������ �ε����� �ƴ� ���
	//������ �ε����� ��ü
	if (idx < m_ObjCount)
	{
		FObject* Temp = m_ObjList[idx];
		m_ObjList[idx] = m_ObjList[m_ObjCount-1];
		m_ObjList[m_ObjCount - 1] = Temp;
	}
	//������ �ε����� �����ϰ� �迭�� ũ��(Count)�� ����
	delete m_ObjList[m_ObjCount - 1];
	m_ObjList[m_ObjCount - 1] = nullptr;
	--m_ObjCount;
}

void FMaze::InfoOutput(__int64 TimeStart, FPlayer* Player)
{	
	//�ð� ���
	__int64 Time = time(0);
	m_Time = Time - TimeStart;

	COORD   TimePos;
	TimePos.X = m_Xsize + 2;
	TimePos.Y = 2;

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), TimePos); 

	__int64 Minute = m_Time / 60;
	__int64 Second = m_Time % 60;

	std::cout << Minute << ":" << Second << std::endl;

	//���� ���
	COORD   ScorePos;
	ScorePos.X = m_Xsize + 2;
	ScorePos.Y = 3;

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
	std::cout << "Score : " << m_Score;

	//ü�� ���
	COORD   HPPos;
	HPPos.X = m_Xsize + 2;
	HPPos.Y = 1;

	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), HPPos);
	std::cout << "HP : ";

	int HP = Player->GetHP();

	for (int i = 0; i < 5; ++i)
	{
		if (i < HP)
			std::cout << "��";

		else
			std::cout << "  ";
	}
}

