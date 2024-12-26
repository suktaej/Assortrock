#include "Map.h"
#include "Player.h"

CMap* CMap::mInst = nullptr;

CMap::CMap()
{
}

CMap::~CMap()
{
    //if (mMapWall)
    //{
    //    for (int i = 0; i < mMapYSize; i++)
    //        delete[] mMapWall[i];
    //}
    //delete[] mMapWall;
}

bool CMap::Init()
{
    MakeWall();
    mOutputBuffer.resize(mMapXSize * mMapYSize);
    return true;
}

void CMap::MakeWall()
{
    //mMapWall = new int*[mMapYSize];
    //for (int i = 0;i < mMapYSize;i++)
    //    mMapWall[i] = new int[mMapXSize];
    mMapWall.resize(mMapYSize, std::vector<int>(mMapXSize, 0));

    for (int x = 0; x < mMapXSize; x++)
    {
        mMapWall[0][x] = (int)ETile::Wall;
        mMapWall[mMapYSize - 1][x] = (int)ETile::Wall;
    }
    for (int y = 0; y < mMapYSize; y++)
    {
        mMapWall[y][0] = (int)ETile::Wall;
        mMapWall[y][mMapXSize - 1] = (int)ETile::Wall;
    }
}

void CMap::Output() const
{
    for (const auto& row : mMapWall)
    {
        for (const auto& col : row)
        {
            if(col==(int)ETile::Space)
            std::cout << ' ';
            else if(col==(int)ETile::Wall)
            std::cout << '#';
        }
    std::cout << std::endl;
    }
}

void CMap::Run()
{
    CPlayer* Player = new CPlayer;
    Player->Init();
    Player->SetPos(7,12);
    //Player->SetMap(this);

    while (true)
    {
        system("cls");
        Player->Update();
        Output();
        Player->Output();
    }
}

int CMap::GetTile(int x, int y) const
{
    if (x < 0 || x >= mMapXSize || y < 0 || y >= mMapYSize)
        return (int)ETile::Wall;
    return mMapWall[y][x];
}
