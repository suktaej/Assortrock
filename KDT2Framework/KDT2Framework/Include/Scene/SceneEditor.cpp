#include "SceneEditor.h"
#include "../Object/TileMapObj.h"
#include "../Object/EditorPlayer.h"
#include "Input.h"

CSceneEditor::CSceneEditor()
{
}

CSceneEditor::~CSceneEditor()
{
}

bool CSceneEditor::InitAsset()
{
    return true;
}

bool CSceneEditor::InitObject()
{
    CEditorPlayer* EditorPlayer = CreateObj<CEditorPlayer>("EditorPlayer");

    mTileMapObj = CreateObj<CTileMapObj>("TileMap");


    mInput->AddBindKey("TileType", '1');

    mInput->AddBindFunction<CSceneEditor>("TileType",
        EInputType::Down, this, &CSceneEditor::TileTypeKey);

    return true;
}

bool CSceneEditor::InitWidget()
{
    return true;
}

void CSceneEditor::TileTypeKey(float DeltaTime)
{
    mTileMapObj->AddTileType();
}
