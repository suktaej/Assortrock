#include "Navigation.h"

CNavigation::CNavigation()
{
}

CNavigation::~CNavigation()
{
}

// Navgation class의 타일 정보를 초기화
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

    //탐색할 리스트 초기화
    PathList.clear();
    return false;
}
