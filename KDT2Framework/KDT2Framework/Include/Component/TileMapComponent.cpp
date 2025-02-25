#include "TileMapComponent.h"

CTileMapComponent::CTileMapComponent()
{
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& Com)  :
    CComponent(Com)
{
}

CTileMapComponent::CTileMapComponent(CTileMapComponent&& Com) :
    CComponent(Com)
{
}

CTileMapComponent::~CTileMapComponent()
{
}

bool CTileMapComponent::Init()
{
    CComponent::Init();

    return true;
}

bool CTileMapComponent::Init(const char* FileName)
{
    CComponent::Init(FileName);

    return true;
}

void CTileMapComponent::PreUpdate(float DeltaTime)
{
    CComponent::PreUpdate(DeltaTime);
}

void CTileMapComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);
}

CTileMapComponent* CTileMapComponent::Clone()
{
    return new CTileMapComponent(*this);
}

void CTileMapComponent::EndFrame()
{
    CComponent::EndFrame();
}

void CTileMapComponent::CreateTile(int CountX, int CountY,
    const FVector2D& TileSize)
{
    mCountX = CountX;
    mCountY = CountY;
    mTileSize = TileSize;

    mTileList.resize(mCountX * mCountY);

    for (int i = 0; i < mCountY; ++i)
    {
        for (int j = 0; j < mCountX; ++j)
        {
            CTile* Tile = new CTile;

            Tile->mPos.x = j * mTileSize.x;
            Tile->mPos.y = i * mTileSize.y;
            Tile->mSize = mTileSize;
            Tile->mCenter = Tile->mPos + mTileSize * 0.5f;

            mTileList[i * mCountX + j] = Tile;
        }
    }
}
