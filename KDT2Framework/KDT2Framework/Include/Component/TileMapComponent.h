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
	ETileShape	mTileShape = ETileShape::Rect;
	FVector2D	mTileSize;
	int			mCountX = 0;
	int			mCountY = 0;
	bool		mTileOutLineRender = false;
	CSharedPtr<class CMesh>			mOutLineMesh;
	CSharedPtr<class CShader>		mOutLineShader;
	class CTransformCBuffer* mLineTransformCBuffer = nullptr;
	class CColliderCBuffer* mColorCBuffer = nullptr;

	int			mViewStartX;
	int			mViewStartY;
	int			mViewEndX;
	int			mViewEndY;

public:
	const FVector2D& GetTileSize()	const
	{
		return mTileSize;
	}

	int GetTileCountX()	const
	{
		return mCountX;
	}

	int GetTileCountY()	const
	{
		return mCountY;
	}

public:
	void SetTileOutLineRender(bool Render);

public:
	int GetTileIndexX(const FVector3D& Pos)	const;
	int GetTileIndexX(const FVector2D& Pos)	const;
	int GetTileIndexX(float x)	const;

	int GetTileIndexY(const FVector3D& Pos)	const;
	int GetTileIndexY(const FVector2D& Pos)	const;
	int GetTileIndexY(float y)	const;

	int GetTileIndex(const FVector3D& Pos)	const;
	int GetTileIndex(const FVector2D& Pos)	const;
	int GetTileIndex(float x, float y)	const;

	const CTile* GetTile(const FVector3D& Pos)	const;
	const CTile* GetTile(const FVector2D& Pos)	const;
	const CTile* GetTile(float x, float y)	const;

	ETileType ChangeTileType(ETileType Type, const FVector3D& Pos);
	ETileType ChangeTileType(ETileType Type, const FVector2D& Pos);
	ETileType ChangeTileType(ETileType Type, float x, float y);
	ETileType ChangeTileType(ETileType Type, int Index);

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTileMapComponent* Clone();
	virtual void EndFrame();

public:
	void RenderTile();
	void RenderTileOutLine();

public:
	void CreateTile(ETileShape Shape, int CountX, int CountY,
		const FVector2D& TileSize);
};

