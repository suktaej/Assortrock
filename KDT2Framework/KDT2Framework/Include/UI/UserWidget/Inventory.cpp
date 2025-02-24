#include "Inventory.h"
#include "../Common/Button.h"
#include "../Common/TextBlock.h"
#include "../Common/TitleBar.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

bool CInventory::Init()
{
    CWindowWidget::Init();

    SetSize(400.f, 500.f);

    CSharedPtr<CTitleBar>    TitleBar = 
        mScene->GetUIManager()->CreateWidget<CTitleBar>("TitleBar");

    TitleBar->SetSize(360.f, 40.f);
    TitleBar->SetPos(0.f, 460.f);
    TitleBar->SetTexture("MPBar", TEXT("Texture\\MPBar.png"));
    TitleBar->SetText(TEXT("인벤토리"));

    TitleBar->SetUpdateWidget(this);

    AddWidget(TitleBar);

    CSharedPtr<CButton>    Button = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");

    Button->SetPos(360.f, 460.f);
    Button->SetSize(40.f, 40.f);
    //Button->SetTint(EButtonState::Normal, 1.f, 0.f, 0.f);
    Button->SetTexture(EButtonState::Normal, "StartButton",
        TEXT("Texture\\End.png"));
    Button->SetTexture(EButtonState::Hovered, "StartButton",
        TEXT("Texture\\End.png"));
    Button->SetTexture(EButtonState::Click, "StartButton",
        TEXT("Texture\\End.png"));

    Button->SetTint(EButtonState::Normal, 0.8f, 0.8f, 0.8f);
    Button->SetTint(EButtonState::Hovered, 1.f, 1.f, 1.f);
    Button->SetTint(EButtonState::Click, 0.6f, 0.6f, 0.6f);

    /*Button->SetSound(EButtonEventState::Hovered, "ButtonHovered",
        "Sound\\TeemoSmile.mp3");
    Button->SetSound(EButtonEventState::Click, "ButtonClick",
        "Sound\\TeemoStartClicck.mp3");*/

    AddWidget(Button);

    return true;
}

void CInventory::Update(float DeltaTime)
{
    CWindowWidget::Update(DeltaTime);
}

void CInventory::Render()
{
    CWindowWidget::Render();
}
