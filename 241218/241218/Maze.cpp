#include "Maze.h"
#include "Player.h"
#include "ItemScore.h"
#include "ItemHP.h"
#include "Trap.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
	if (nullptr != mMazeArray)
	{
		for (int i = 0;i < mCountY;i++)
			delete[] mMazeArray[i];
	}
	delete mMazeArray;
	//���� Ȯ��
	if (nullptr != mOutputBuffer)
		delete[] mOutputBuffer;
}

bool CMaze::Init(const char* FileName)
{
	mObjectList = new CObject * [mObjectCapacity];
	//������ ������, ���� ���� �����ϱ� ���� ������Ʈ �迭

	FILE* File = nullptr;
	fopen_s(&File, FileName, "rt");

	if (!File)
		return false;

	char Buffer[128] = {};
	strcpy_s(Buffer, FileName);
	//�迭�� ���� �����ؼ� �����̸��� ����
	//���� .�������� ������ ������ Ȯ���� ����
	char* Context = nullptr;
	char* Result = strtok_s(Buffer, ".", &Context);
	strcpy_s(mName, Result);
	//������� mName�� Ȯ���ڸ� ������ �̷��� �̸��� ����

	char Line[128] = {};
	fgets(Line, 128, File);
	//ù��° ���� �迭�� ũ��(10, 10)
	Result = strtok_s(Line, ", ", &Context);
	//', '���� �и�
	mCountX = atoi(Result);
	mCountY = atoi(Context);

	SetFunc(File);

	return true;
}

void CMaze::Output() { std::cout << mOutputBuffer; }

void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo); // ���� Ŀ�� ���� ��������
	cursorInfo.bVisible = FALSE;                     // Ŀ���� ����
	SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Ŀ�� ���� ����
}

void CMaze::SetFunc(FILE* InputFile) //set
{
	for (int i = 0; i < mObjectCount;i++)
		SAFE_DELETE(mObjectList[i]);

	mTime = 0;
	mScore = 0;
	mObjectCount = 0;

	mMazeArray = new ETileType * [mCountY];	//set
	mOutputBuffer = new char[(mCountX + 1) * mCountY + 1]; //set
	memset(mOutputBuffer, 0, sizeof(char) * ((mCountX + 1) * mCountY + 1));

	for (int i = 0;i < mCountY;i++)
	{
		mMazeArray[i] = new ETileType[mCountX];

		char Line[128];
		fgets(Line, 128, InputFile);	//set

		for (int j = 0;j < mCountX;j++)
		{
			mMazeArray[i][j] = (ETileType)(Line[j] - '0');	//set

			int OutputIndex = i * (mCountX + 1) + j;

			switch (mMazeArray[i][j])
			{
			case ETileType::Road:
				mOutputBuffer[OutputIndex] = ' ';
				break;
			case ETileType::Wall:
				mOutputBuffer[OutputIndex] = '#';
				break;
			case ETileType::Start:
				mStartPos.X = j;
				mStartPos.Y = i;
				mOutputBuffer[OutputIndex] = 'S';
				break;
			case ETileType::Goal:
				mGoalPos.X = j;
				mGoalPos.Y = i;
				mOutputBuffer[OutputIndex] = 'G';
				break;
			case ETileType::Item:
			{
				CItem* Item = new CItemScore;
				Item->Init();
				Item->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
					ArrayRedef();

				mObjectList[mObjectCount] = Item;
				mObjectCount++;
				mOutputBuffer[OutputIndex] = ' ';
				break;
			}
			case ETileType::Trap:
			{
				CTrap* Trap = new CTrap;
				Trap->Init();
				Trap->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
					ArrayRedef();

				mObjectList[mObjectCount] = Trap;
				mObjectCount++;
				mOutputBuffer[OutputIndex] = ' ';
				break;
			}
			case ETileType::HP:
			{
				CItem* Item = new CItemHP;
				Item->Init();
				Item->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
					ArrayRedef();

				mObjectList[mObjectCount] = Item;
				mObjectCount++;
				mOutputBuffer[OutputIndex] = ' ';

				break;
			}
			}
		}
		int OutputIndex = i * (mCountX + 1) + mCountX;
		mOutputBuffer[OutputIndex] = '\n';
		//������ ������ ���๮�� �߰�
		//������ �� �ε����� mCountX+1 ��ŭ�̹Ƿ� mCountX�� ������ �� �ε����� ��
	}
}

void CMaze::SetFunc()
{
	for (int i = 0; i < mObjectCount;i++)
		SAFE_DELETE(mObjectList[i]);

	mTime = 0;
	mScore = 0;
	mObjectCount = 0;

	memset(mOutputBuffer, 0, sizeof(char) * ((mCountX + 1) * mCountY + 1));

	for (int i = 0;i < mCountY;i++)
	{
		for (int j = 0;j < mCountX;j++)
		{
			int OutputIndex = i * (mCountX + 1) + j;

			switch (mMazeArray[i][j])
			{
			case ETileType::Road:
				mOutputBuffer[OutputIndex] = ' ';
				break;
			case ETileType::Wall:
				mOutputBuffer[OutputIndex] = '#';
				break;
			case ETileType::Start:
				mStartPos.X = j;
				mStartPos.Y = i;
				mOutputBuffer[OutputIndex] = 'S';
				break;
			case ETileType::Goal:
				mGoalPos.X = j;
				mGoalPos.Y = i;
				mOutputBuffer[OutputIndex] = 'G';
				break;
			case ETileType::Item:
			{
				CItem* Item = new CItemScore;
				Item->Init();
				Item->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
					ArrayRedef();

				mObjectList[mObjectCount] = Item;
				mObjectCount++;
				mOutputBuffer[OutputIndex] = ' ';
				break;
			}
			case ETileType::Trap:
			{
				CTrap* Trap = new CTrap;
				Trap->Init();
				Trap->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
					ArrayRedef();

				mObjectList[mObjectCount] = Trap;
				mObjectCount++;
				mOutputBuffer[OutputIndex] = ' ';
				break;
			}
			case ETileType::HP:
			{
				CItem* Item = new CItemHP;
				Item->Init();
				Item->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
					ArrayRedef();

				mObjectList[mObjectCount] = Item;
				mObjectCount++;
				mOutputBuffer[OutputIndex] = ' ';

				break;
			}
			}
		}
		int OutputIndex = i * (mCountX + 1) + mCountX;
		mOutputBuffer[OutputIndex] = '\n';
	}
}

void CMaze::ArrayRedef()
{
	mObjectCapacity *= 2;
	CObject** Array = new CObject * [mObjectCapacity];
	memcpy(Array, mObjectList, sizeof(CObject*) * mObjectCount);

	delete[] mObjectList;

	mObjectList = Array;
}

void CMaze::Run()
{
	SetFunc();

	system("cls");
	//�ð�
	mScore = 0;
	__int64 TimeStart = time(0);

	//�÷��̾� ����
	CPlayer* Player = new CPlayer;

	Player->Init();
	Player->SetPos(mStartPos);
	Player->SetMaze(this);
	//===thisȮ��===

	int StartIndex = mStartPos.Y * (mCountX + 1) + mStartPos.X;
	int GoalIndex = mGoalPos.Y * (mCountX + 1) + mGoalPos.X;

	mPrevPlayerIndex = StartIndex;
	mPrevPlayerOutput = 0;
	//===+1 Ȯ��==17:54===
	//==1���� �迭 �������� ���������� ���������� ��ġ

	while (true)
	{
		//system("cls");
		//����� ����
		Player->Update();

		//�÷��̾� ��ġ �޾ƿ���
		COORD PlayerPos = Player->GetPos();
		int PlayerIndex = PlayerPos.Y * (mCountX + 1) + PlayerPos.X;

		//������Ʈ ������Ʈ
		for (int i = 0;i < mObjectCount;i++)
		{
			mObjectList[i]->Update();

			if (PlayerPos.X == mObjectList[i]->GetPos().X &&
				PlayerPos.Y == mObjectList[i]->GetPos().Y)
			{
				if (nullptr != dynamic_cast<CItem*>(mObjectList[i]))
				{
					if (dynamic_cast<CItemScore*>(mObjectList[i]))
						mScore += 10;
					else if (dynamic_cast<CItemHP*>(mObjectList[i]))
						Player->SetHP(1);

					mOutputBuffer[PlayerIndex] = ' ';
				}
				else if (nullptr != dynamic_cast<CTrap*>(mObjectList[i]))
				{
					mOutputBuffer[PlayerIndex] = ' ';
					if (Player->SetHP(-1))
					{
						SAFE_DELETE(Player);
						return;
					}
				}
				if (i < mObjectCount - 1)
				{
					CObject* Temp = mObjectList[i];
					mObjectList[i] = mObjectList[mObjectCount - 1];
					mObjectList[mObjectCount - 1] = Temp;
				}

				delete mObjectList[mObjectCount - 1];
				mObjectList[mObjectCount - 1] = nullptr;
				--mObjectCount;
				break;
			}
		}
		//���������� ���������� ����� ���۸� ���� ���� ����
		mOutputBuffer[StartIndex] = 'S';
		mOutputBuffer[GoalIndex] = 'G';

		//�÷��̾��� ���� ������ �ε����� ����
		if (mPrevPlayerOutput != 0)
			mOutputBuffer[mPrevPlayerIndex] = mPrevPlayerOutput;

		mPrevPlayerIndex = PlayerIndex;
		mPrevPlayerOutput = mOutputBuffer[PlayerIndex];
		//===25:55===

		for (int i = 0; i < mObjectCount; i++)
			mObjectList[i]->Output(mOutputBuffer, mCountX + 1);

		mOutputBuffer[PlayerIndex] = 'P';

		COORD Cursor = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
		//�ܼ� Ŀ���� ��ġ�� ó������ ������
		HideCursor();
		Output();

		if (GetTile(PlayerPos.X, PlayerPos.Y) == ETileType::Goal)
			break;
		//Player->Output();

		COORD ScorePos;
		ScorePos.X = 0;
		ScorePos.Y = mCountY + 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
		std::cout << "Score: " << mScore;
		//���ھ� ���

		__int64 Time = time(0);
		mTime = Time - TimeStart;

		COORD TimePos;
		TimePos.X = 10;
		TimePos.Y = mCountY + 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TimePos);

		int Minute = mTime / 60;
		int Second = mTime % 60;
		std::cout << "Time: " << Minute << ":" << Second;
		//�ð� ���

		COORD HPPos;
		HPPos.X = 0;
		HPPos.Y = mCountY + 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), HPPos);
		std::cout << "HP: " << Player->GetHP();
	}
	SAFE_DELETE(Player);
}

ETileType CMaze::GetTile(int x, int y) const
{
	if (x < 0 || x >= mCountX ||
		y < 0 || y >= mCountY)
		return ETileType::Wall;

	return mMazeArray[y][x];
}
