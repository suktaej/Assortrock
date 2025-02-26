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

