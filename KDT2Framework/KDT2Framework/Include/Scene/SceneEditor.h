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

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();

private:
	void TileTypeKey(float DeltaTime);
};

