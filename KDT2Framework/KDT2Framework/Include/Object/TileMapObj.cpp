#include "TileMapObj.h"

CTileMapObj::CTileMapObj()
{
}

CTileMapObj::CTileMapObj(const CTileMapObj& Obj)    :
    CSceneObject(Obj)
{
}

CTileMapObj::CTileMapObj(CTileMapObj&& Obj) :
    CSceneObject(Obj)
{
}

CTileMapObj::~CTileMapObj()
{
}

bool CTileMapObj::Init()
{
    CSceneObject::Init();

    mTileMapRenderer = CreateComponent<CTileMapRendererComponent>();
    mTileMap = CreateComponent<CTileMapComponent>();

    mTileMap->SetTileOutLineRender(true);

    mTileMapRenderer->SetBackTexture("TileMapBack",
        TEXT("Texture\\MapBackGround.png"));

    SetRootComponent(mTileMapRenderer);

    mTileMap->CreateTile(ETileShape::Rect,
        100, 100, FVector2D(64.f, 64.f));

    return true;
}

void CTileMapObj::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}
