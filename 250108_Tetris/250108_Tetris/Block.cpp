#include "Block.h"
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"

FBlock::FBlock()
{
}

FBlock::~FBlock()
{
}

bool FBlock::Init()
{
    EBlockType BlockType = (EBlockType)(rand() % 6);

    switch (BlockType)
    {
	case FBlock::EBlockType::I:
		m_BlockShape =
		{ {'.', '.', '.', '.'},
		  {'*', '*', '*', '*'},
		  {'.', '.', '.', '.'},
		  {'.', '.', '.', '.'} };
        break;
    case FBlock::EBlockType::O:
        m_BlockShape =
        { {'.', '.', '.', '.'},
          {'.', '*', '*', '.'},
          {'.', '*', '*', '.'},
          {'.', '.', '.', '.'} };
        break;
    case FBlock::EBlockType::J:
        m_BlockShape =
        { {'.', '.', '.', '.'},
          {'.', '*', '*', '*'},
          {'.', '.', '.', '*'},
          {'.', '.', '.', '.'} };
        break;
    case FBlock::EBlockType::L:
        m_BlockShape =
        { {'.', '.', '.', '.'},
          {'.', '*', '*', '*'},
          {'.', '*', '.', '.'},
          {'.', '.', '.', '.'} };
        break;
    case FBlock::EBlockType::T:
        m_BlockShape =
        { {'.', '.', '.', '.'},
          {'.', '*', '*', '*'},
          {'.', '.', '*', '.'},
          {'.', '.', '.', '.'} };
        break;
    case FBlock::EBlockType::S:
        m_BlockShape =
        { {'.', '.', '.', '.'},
          {'.', '.', '*', '*'},
          {'.', '*', '*', '.'},
          {'.', '.', '.', '.'} };
        break;
    case FBlock::EBlockType::Z:
        m_BlockShape =
        { {'.', '.', '.', '.'},
          {'.', '*', '*', '.'},
          {'.', '.', '*', '*'},
          {'.', '.', '.', '.'} };
        break;
    }
    
    mPos = { (MAP_XSIZE)/2-2 , 0 };
    mMoveX = 0.f;
    mMoveY = 0.f;
    mDirX = 0.f;
    mDirY = 0.f;

	return true;
}

void FBlock::Output(std::vector<std::vector<char>>& Map)
{
    for (int i = 0; i < BLOCKSIZE;i++)
    {
        for (int j = 0;j < BLOCKSIZE;j++)
        {
            if (m_BlockShape[i][j] == '*')
            {
                int MapPosX = mPos.X + j;
                int MapPosY = mPos.Y + i;

                if (MapPosX >= 0 && MapPosX < Map[0].size() &&
                    MapPosY >= 0 && MapPosY < Map.size())
                    Map[MapPosY][MapPosX] = '*';
            }
        }
    }

	//Map[mPos.Y][mPos.X] = 'X';
}

void FBlock::Rotate() {
    int size = m_BlockShape.size();
    std::vector<std::vector<char>> rotated(size, std::vector<char>(size, 0));
    //블록의 행렬 변경
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            rotated[i][j] = m_BlockShape[size - j - 1][i];
        }
    }
    //충돌 검증
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size;j++)
        {
            if (rotated[i][j] == '*')
            {
                int ColX = mPos.X + j;
                int ColY = mPos.Y + i;
                
                if (ColX <= 0 ||
                    ColX >= MAP_XSIZE - 1 ||
                    ColY >= MAP_YSIZE - 1 ||
                    FStageManager::GetInst()->GetStage()->GetBlock(ColX, ColY) == '+')
                    return;
            }
        }
    }
    m_BlockShape = rotated;
}

void FBlock::Update(float DeltaTime)
{
	int PrevX = mPos.X;

    //키조작
    if (_kbhit() > 0)
    {
        int Key = _getch();

        if ((EKey)Key == EKey::MoveKey)
        {
            Key = _getch();

            switch ((EKey)Key)
            {
            case EKey::Up:
                Rotate();
                break;
            case EKey::Down:
                ++mPos.Y;
                break;
            case EKey::Left:
                --mPos.X;
                break;
            case EKey::Right:
                ++mPos.X;
                break;
			}
        }
        else if ((EKey)Key == EKey::Space)
        {
            while (true)
            {
                ++mPos.Y;
                ECollisionType Type = FStageManager::GetInst()->GetStage()->CheckCollison(this, PrevX);

                if (Type == ECollisionType::Floor)
                {
                    --mPos.Y;
                    FStageManager::GetInst()->GetStage()->LockBlock(this);
                    return;
                }
            }
        }
    }
    
    //자동이동
	mMoveY += DeltaTime * 2;

	if (mMoveY >= 1.f)
	{
		mMoveY -= 1.f;
		mPos.Y++;
	}
    
    //충돌 발생 시
    ECollisionType CollisionType = FStageManager::GetInst()->GetStage()->CheckCollison(this,PrevX);

    switch (CollisionType)
    {
    case ECollisionType::None:
        break;
    case ECollisionType::Wall:
        mPos.X = PrevX;
        break;
    case ECollisionType::Floor:
    {
        --mPos.Y;
        //블록 고정
        FStageManager::GetInst()->GetStage()->LockBlock(this);
		break;
    }
    case ECollisionType::End:
        return;
    }
}


