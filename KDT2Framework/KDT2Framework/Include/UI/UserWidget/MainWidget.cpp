#include "MainWidget.h"
#include "../Common/Button.h"
#include "../Common/TextBlock.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"

CMainWidget::CMainWidget()
{
}

CMainWidget::~CMainWidget()
{
}

bool CMainWidget::Init()
{
    CUserWidget::Init();

    CSharedPtr<CButton>    Button = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");

    Button->SetPos(100.f, 100.f);
    Button->SetSize(100.f, 100.f);
    //Button->SetTint(EButtonState::Normal, 1.f, 0.f, 0.f);
    Button->SetTexture(EButtonState::Normal, "StartButton", 
        TEXT("Texture\\Start.png"));
    Button->SetTexture(EButtonState::Hovered, "StartButton",
        TEXT("Texture\\Start.png"));
    Button->SetTexture(EButtonState::Click, "StartButton",
        TEXT("Texture\\Start.png"));

    Button->SetTint(EButtonState::Normal, 0.8f, 0.8f, 0.8f);
    Button->SetTint(EButtonState::Hovered, 1.f, 1.f, 1.f);
    Button->SetTint(EButtonState::Click, 0.6f, 0.6f, 0.6f);

    Button->SetSound(EButtonEventState::Hovered, "ButtonHovered",
        "Sound\\TeemoSmile.mp3");
    Button->SetSound(EButtonEventState::Click, "ButtonClick",
        "Sound\\TeemoStartClicck.mp3");

    AddWidget(Button);

    CSharedPtr<CTextBlock>    Text = 
        mScene->GetUIManager()->CreateWidget<CTextBlock>("TestButtonText");

    Text->SetText(TEXT("Button"));
    Text->SetTextColor(255, 0, 0, 255);
    Text->SetPos(100.f, 100.f);
    Text->SetSize(100.f, 100.f);
    Text->SetAlignH(ETextAlignH::Center);
    Text->SetFontSize(40.f);

    Button->SetChild(Text);


    return true;
}

void CMainWidget::Update(float DeltaTime)
{
    CUserWidget::Update(DeltaTime);
}

void CMainWidget::Render()
{
    CUserWidget::Render();
}
