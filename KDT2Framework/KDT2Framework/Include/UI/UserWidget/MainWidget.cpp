#include "MainWidget.h"
#include "../Common/Button.h"
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
    //Button->SetTexture(EButtonState::Normal, "Button.png");

    AddWidget(Button);

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
