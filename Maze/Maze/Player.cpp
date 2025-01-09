#include "Player.h"
#include "Maze.h"

FPlayer::FPlayer()
{
}

FPlayer::~FPlayer()
{
}

bool FPlayer::Init()
{
    return true;
}

void FPlayer::Update()
{
    if (_kbhit())
    {
        int Key = _getch();

        if (Key == (int)EKeyType::MoveKey)
        {
            Key = _getch();
            switch ((EKeyType)Key)
            {
            case EKeyType::Up:
                --mPos.Y;
                if (m_Maze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    ++mPos.Y;
                break;
            case EKeyType::Down:
                ++mPos.Y;
                if (m_Maze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    --mPos.Y;
                break;
            case EKeyType::Left:
                --mPos.X;
                if (m_Maze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    ++mPos.X;
                break;
            case EKeyType::Right:
                ++mPos.X;
                if (m_Maze->GetTile(mPos.X, mPos.Y) == ETileType::Wall)
                    --mPos.X;
                break;
            }

        }
    }
}

void FPlayer::Output(char* Buffer, int CountX)
{
}
