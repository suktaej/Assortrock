#pragma once

#include "Scene.h"

class CSceneEditor :
    public CScene
{
	friend class CSceneManager;

private:
	CSceneEditor();
	virtual ~CSceneEditor();

private:
	CSharedPtr<class CTileMapObj>	mTileMapObj;
	EEditorMode		mEditorMode = EEditorMode::TileType;
	ETileType       mEditTileType = ETileType::Normal;
	ETileType       mOnMousePrevTileType = ETileType::None;
	int             mOnMousePrevIndex = -1;

	int				mEditTileFrame = 0;

public:
	virtual void Update(float DeltaTime);

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();

private:
	void EditorMode(float DeltaTime);
	void TileTypeKey(float DeltaTime);
	void TileFrameKey(float DeltaTime);
	void SaveKey(float DeltaTime);
	void LoadKey(float DeltaTime);
};

