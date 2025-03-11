#pragma once

#include "SceneObject.h"
#include "../Component/TileMapComponent.h"
#include "../Component/TileMapRendererComponent.h"

class CTileMapObj :
    public CSceneObject
{
    friend class CScene;

protected:
    CTileMapObj();
    CTileMapObj(const CTileMapObj& Obj);
    CTileMapObj(CTileMapObj&& Obj);
    virtual ~CTileMapObj();

private:
    CSharedPtr<CTileMapRendererComponent>   mTileMapRenderer;
    CSharedPtr<CTileMapComponent>   mTileMap;
    ETileType       mEditTileType = ETileType::Normal;
    ETileType       mOnMousePrevTileType = ETileType::None;
    int             mOnMousePrevIndex = -1;
    EEditorMode     mEditorMode = EEditorMode::TileType;

    int         mEditTileFrame = 0;

public:
    void SetEditorMode(EEditorMode Mode) { mEditorMode = Mode; }
    void AddTileType();
    void AddTileFrame();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void Save(const TCHAR* FullPath);
    void Load(const TCHAR* FullPath);

public:
	//0311
	//충돌가능여부 확인
    bool IsTileBlocked(FVector2D Pos) { return mTileMap->IsTileBlocked(Pos); }
    //타일크기 반환
    FVector2D GetTileSize() { return mTileMap->GetTileSize(); }
};

