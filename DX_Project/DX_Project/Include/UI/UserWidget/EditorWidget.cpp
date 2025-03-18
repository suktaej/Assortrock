#include "EditorWidget.h"
#include "../Common/Image.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneMain.h"
#include "../../Scene/SceneEditor.h"
#include "../../Device.h"
#include "../../GameManager.h"
#include "../../Object/TileMapObj.h"

CEditorWidget::CEditorWidget()
{
}

CEditorWidget::~CEditorWidget()
{
}

bool CEditorWidget::Init()
{
    CUserWidget::Init();
    
    return true;
}

void CEditorWidget::Update(float DeltaTime)
{
    CUserWidget::Update(DeltaTime);

    FAnimationFrame	TileFrame = mScene->FindObjectFromType<CTileMapObj>()->GetTileInfo();

    CSharedPtr<CImage>  TileTexture = mScene->GetUIManager()->CreateWidget<CImage>("Tile");
    TileTexture->SetTexture("Tile", TEXT("Texture\\Back.png"));
    TileTexture->SetSize(64.f, 64.f);
}

void CEditorWidget::Render()
{
}
