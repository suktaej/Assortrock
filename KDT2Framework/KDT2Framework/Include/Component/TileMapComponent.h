#pragma once

#include "Component.h"
#include "Tile.h"

class CTileMapComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CTileMapComponent();
	CTileMapComponent(const CTileMapComponent& Com);
	CTileMapComponent(CTileMapComponent&& Com);
	virtual ~CTileMapComponent();

protected:
	std::vector<CTile*>	mTileList;
	FVector2D	mTileSize;
	int			mCountX = 0;
	int			mCountY = 0;

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTileMapComponent* Clone();
	virtual void EndFrame();

public:
	void CreateTile(int CountX, int CountY,
		const FVector2D& TileSize);
};

