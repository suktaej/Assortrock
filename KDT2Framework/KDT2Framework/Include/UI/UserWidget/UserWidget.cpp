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

    auto    iter = mWidgetList.begin();
    auto    iterEnd = mWidgetList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = mWidgetList.erase(iter);
            iterEnd = mWidgetList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Update(DeltaTime);
        ++iter;
    }
}

void CUserWidget::Render()
{
    CWidget::Render();

    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CUserWidget::SortRender);
    }

    auto    iter = mWidgetList.begin();
    auto    iterEnd = mWidgetList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = mWidgetList.erase(iter);
            iterEnd = mWidgetList.end();
            continue;
        }

        else if (!(*iter)->IsEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Render();
        ++iter;
    }
}

bool CUserWidget::CollisionMouse(const FVector2D& MousePos)
{
    bool Result = CWidget::CollisionMouse(MousePos);

    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CUserWidget::SortCollision);

        auto    iter = mWidgetList.begin();
        auto    iterEnd = mWidgetList.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->IsActive())
            {
                iter = mWidgetList.erase(iter);
                iterEnd = mWidgetList.end();
                continue;
            }

            else if (!(*iter)->IsEnable())
            {
                ++iter;
                continue;
            }

            if ((*iter)->CollisionMouse(MousePos))
            {
                return true;
            }
            ++iter;
        }
    }

    return Result;
}

bool CUserWidget::SortCollision(const CSharedPtr<CWidget>& Src,
    const CSharedPtr<CWidget>& Dest)
{
    return Src->GetZOrder() < Dest->GetZOrder();
}

bool CUserWidget::SortRender(const CSharedPtr<CWidget>& Src, 
    const CSharedPtr<CWidget>& Dest)
{
    return Src->GetZOrder() > Dest->GetZOrder();
}
