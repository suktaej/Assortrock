#include "CameraManager.h"

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::SetViewTarget(CCameraComponent* ViewTarget)
{
    m_ViewTarget = ViewTarget;
}

bool CCameraManager::Init()
{
    return true;
}

void CCameraManager::Update(float DeltaTime)
{
    if (m_ViewTarget)
    {
        if (!m_ViewTarget->IsActive())
            m_ViewTarget = nullptr;
    }
}
