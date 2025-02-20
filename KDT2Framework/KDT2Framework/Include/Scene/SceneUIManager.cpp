#include "SceneUIManager.h"

CSceneUIManager::CSceneUIManager()
{
}

CSceneUIManager::~CSceneUIManager()
{
}

void CSceneUIManager::AddToViewport(CWidget* Widget)
{
    mWidgetList.emplace_back(Widget);
}

bool CSceneUIManager::Init()
{
    return true;
}

void CSceneUIManager::Update(float DeltaTime)
{
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

void CSceneUIManager::Collision(float DeltaTime)
{
    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CSceneUIManager::SortCollision);
    }
}

void CSceneUIManager::Render()
{
    if (mWidgetList.size() >= 2)
    {
        std::sort(mWidgetList.begin(), mWidgetList.end(),
            CSceneUIManager::SortRender);
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

bool CSceneUIManager::SortCollision(const CSharedPtr<CWidget>& Src, 
    const CSharedPtr<CWidget>& Dest)
{
    return Src->GetZOrder() < Dest->GetZOrder();
}

bool CSceneUIManager::SortRender(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest)
{
    return Src->GetZOrder() > Dest->GetZOrder();
}
