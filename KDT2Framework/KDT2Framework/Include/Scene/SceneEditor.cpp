#include "SceneEditor.h"
#include "../Object/TileMapObj.h"
#include "../Object/EditorPlayer.h"

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

    CTileMapObj* TileMap = CreateObj<CTileMapObj>("TileMap");


    return true;
}

bool CSceneEditor::InitWidget()
{
    return true;
}
