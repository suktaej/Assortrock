#include "Navigation.h"

CNavigation::CNavigation()
{
}

CNavigation::~CNavigation()
{
}

// Navgation class�� Ÿ�� ������ �ʱ�ȭ
void CNavigation::SetTileMap(CTileMapCOmponent* TileMap)
{
}

bool CNavigation::Init()
{
    return true;
}

bool CNavigation::FindPath(const FVector2D& Start, const FVector2D& End, std::list<FVector2D>& PathList)
{
    if (!mTileMap)
        return false;

    int StartIndex = mTileMap->GetTileIndex(Start);

    int EndIndex = 

    //Ž���� ����Ʈ �ʱ�ȭ
    PathList.clear();
    return false;
}
