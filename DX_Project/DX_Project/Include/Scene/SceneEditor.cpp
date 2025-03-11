#include "SceneEditor.h"
#include "../Object/TileMapObj.h"
#include "../Object/EditorPlayer.h"
#include "Input.h"
#include "../GameManager.h"

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


    mInput->AddBindKey("EditorMode", '1');

    mInput->AddBindFunction<CSceneEditor>("EditorMode",
        EInputType::Down, this, &CSceneEditor::EditorMode);

    mInput->AddBindKey("TileType", '2');

    mInput->AddBindFunction<CSceneEditor>("TileType",
        EInputType::Down, this, &CSceneEditor::TileTypeKey);

    mInput->AddBindKey("TileFrame", '3');

    mInput->AddBindFunction<CSceneEditor>("TileFrame",
        EInputType::Down, this, &CSceneEditor::TileFrameKey);

    mInput->AddBindKey("Save", 'S');
    mInput->ChangeKeyCtrl("Save", true);

    mInput->AddBindFunction<CSceneEditor>("Save",
        EInputType::Down, this, &CSceneEditor::SaveKey);

    mInput->AddBindKey("Load", 'O');
    mInput->ChangeKeyCtrl("Load", true);

    mInput->AddBindFunction<CSceneEditor>("Load",
        EInputType::Down, this, &CSceneEditor::LoadKey);

    return true;
}

bool CSceneEditor::InitWidget()
{
    return true;
}

void CSceneEditor::EditorMode(float DeltaTime)
{
    mEditorMode = (EEditorMode)((int)mEditorMode + 1);

    if (mEditorMode == EEditorMode::End)
        mEditorMode = EEditorMode::TileType;

    mTileMapObj->SetEditorMode(mEditorMode);
}

void CSceneEditor::TileTypeKey(float DeltaTime)
{
    mTileMapObj->AddTileType();
}

void CSceneEditor::TileFrameKey(float DeltaTime)
{
    mTileMapObj->AddTileFrame();
}

void CSceneEditor::SaveKey(float DeltaTime)
{
    OPENFILENAME    ofn = {};

    // 선택한 경로를 저장하기 위한 배열
    TCHAR   FullPath[MAX_PATH] = {};
    TCHAR   Filter[] = TEXT("모든파일\0*.*\0Map 파일\0*.tlm\0");
    
    TCHAR	DefaultPath[MAX_PATH] = {};

    lstrcpy(DefaultPath, gRootPath);
    lstrcat(DefaultPath, TEXT("Asset\\Data\\"));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CGameManager::GetInst()->GetWindowHandle();
    ofn.lpstrFilter = Filter;
    ofn.lpstrDefExt = TEXT("tlm");
    ofn.lpstrInitialDir = DefaultPath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = FullPath;

    ShowCursor(TRUE);

    if (GetSaveFileName(&ofn) != 0)
    {
        mTileMapObj->Save(FullPath);
    }

    ShowCursor(FALSE);
}

void CSceneEditor::LoadKey(float DeltaTime)
{
    OPENFILENAME    ofn = {};

    // 선택한 경로를 저장하기 위한 배열
    TCHAR   FullPath[MAX_PATH] = {};
    TCHAR   Filter[] = TEXT("모든파일\0*.*\0Map 파일\0*.tlm\0");

    TCHAR	DefaultPath[MAX_PATH] = {};

    lstrcpy(DefaultPath, gRootPath);
    lstrcat(DefaultPath, TEXT("Asset\\Data\\"));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CGameManager::GetInst()->GetWindowHandle();
    ofn.lpstrFilter = Filter;
    ofn.lpstrDefExt = TEXT("tlm");
    ofn.lpstrInitialDir = DefaultPath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = FullPath;

    ShowCursor(TRUE);

    if (GetOpenFileName(&ofn) != 0)
    {
        mTileMapObj->Load(FullPath);
    }

    ShowCursor(FALSE);
}
