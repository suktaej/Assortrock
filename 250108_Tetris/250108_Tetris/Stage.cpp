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
	HideCursor();
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
		if (m_BlockActive == false)
		{
			m_BlockActive = true;
			FObjectManager::GetInst()->CreateObj<FBlock>();
		}
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
		
		//�ϳ��� ������ �����ȴٸ� ���� ����
		//������ �� �� ��� ����
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
				
				//���� �浹
				if (BlockX <= 0 ||BlockX >= k_Xsize-1)
					return ECollisionType::Wall;
				if (BlockY < 0)
					return ECollisionType::End;
				if	(BlockY >= k_Ysize-1)
					return ECollisionType::Floor;
				
				//��� �浹
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
			//������ #���� ���
			if (j == 0 || j == k_Xsize - 1 || i == k_Ysize - 1)
				m_Map[i][j] = '#';
			else if (i == 3)
				m_Map[i][j] = ',';
			// ������ ���(+)�� ����
			else if (m_Map[i][j] != '+')
				m_Map[i][j] = '.';
		}
	}
}

bool FStage::LineClear()
{
	//�ٴں��� �������� Ž��
	for (int i = k_Ysize-1;i > 0;i--)
	{
		for (int j = 1;j < k_Xsize-1;j++)
		{	
			//������ ��� ä������ ī���ʹ� 0
			if (m_Map[i][j] == '+')
				m_LineCounter--;
			//��� ���� ������ ����� ������ ��� ����
			if (m_Map[4][j] == '+')
				return true;
		}
		
		if (m_LineCounter == 0)
		{
			m_Score += 100;
			//���� ������ ���ο� ������ �Ҵ�
			//�� ������ �������� ���� �������� �� Ž��
			for (int k = i;k > 0;k--)
			{
				//��� ������ 1�� Y������ �̵�
				for (int j = 1;j < k_Xsize - 1;j++)
					m_Map[k][j] = m_Map[k - 1][j];
			}
			//������ �Ʒ��� ���ȱ� ������ Ž���� ���� ���ο��� �ٽ� ����
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
