#include "UserWidget.h"

CUserWidget::CUserWidget()
{
}

CUserWidget::~CUserWidget()
{
}

bool CUserWidget::Init()
{
    CWidget::Init();

    return true;
}

void CUserWidget::Update(float DeltaTime)
{
    CWidget::Update(DeltaTime);
}

void CUserWidget::Render()
{
    CWidget::Render();
}

bool CUserWidget::CollisionMouse(const FVector2D& MousePos)
{
    bool Result = CWidget::CollisionMouse(MousePos);

    return Result;
}
