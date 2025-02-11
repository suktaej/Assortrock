#include "ColliderAABB2D.h"
#include "../Collision.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "ColliderSphere2D.h"
#include "ColliderOBB2D.h"

CColliderAABB2D::CColliderAABB2D()
{
    mColliderType = EColliderType::Colider2D;
    mColliderShape = EColliderShape::AABB2D;

    mBoxSize.x = 50.f;
    mBoxSize.y = 50.f;
}

CColliderAABB2D::CColliderAABB2D(const CColliderAABB2D& Com) :
    CColliderBase(Com)
{
    mColliderType = EColliderType::Colider2D;
    mColliderShape = EColliderShape::AABB2D;

    mBoxSize = Com.mBoxSize;
}

CColliderAABB2D::CColliderAABB2D(CColliderAABB2D&& Com) :
    CColliderBase(Com)
{
    mColliderType = EColliderType::Colider2D;
    mColliderShape = EColliderShape::AABB2D;

    mBoxSize = Com.mBoxSize;
}

CColliderAABB2D::~CColliderAABB2D()
{
}

bool CColliderAABB2D::Init()
{
    if (!CColliderBase::Init())
        return false;

#ifdef _DEBUG

    mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("FrameCenterRect");

#endif // _DEBUG


    return true;
}

bool CColliderAABB2D::Init(const char* FileName)
{
    if (!CColliderBase::Init(FileName))
        return false;

    return true;
}

void CColliderAABB2D::PreUpdate(float DeltaTime)
{
    CColliderBase::PreUpdate(DeltaTime);
}

void CColliderAABB2D::Update(float DeltaTime)
{
    CColliderBase::Update(DeltaTime);

    mAABB.Min.x = m_WorldPos.x - mBoxSize.x * 0.5f;
    mAABB.Min.y = m_WorldPos.y - mBoxSize.y * 0.5f;

    mAABB.Max.x = m_WorldPos.x + mBoxSize.x * 0.5f;
    mAABB.Max.y = m_WorldPos.y + mBoxSize.y * 0.5f;

    mMin.x = mAABB.Min.x;
    mMin.y = mAABB.Min.y;
    mMax.x = mAABB.Max.x;
    mMax.y = mAABB.Max.y;

    SetWorldScale(mBoxSize);
}

void CColliderAABB2D::PostUpdate(float DeltaTime)
{
    CColliderBase::PostUpdate(DeltaTime);
}

void CColliderAABB2D::Collision(float DeltaTime)
{
    CColliderBase::Collision(DeltaTime);
}

void CColliderAABB2D::PreRender()
{
    CColliderBase::PreRender();
}

void CColliderAABB2D::Render()
{
    CColliderBase::Render();
}

void CColliderAABB2D::PostRender()
{
    CColliderBase::PostRender();
}

CColliderAABB2D* CColliderAABB2D::Clone()
{
    return new CColliderAABB2D(*this);
}

bool CColliderAABB2D::Collision(FVector3D& HitPoint,
    CColliderBase* Dest)
{
    if (Dest->GetColliderType() == EColliderType::Colider3D)
        return false;

    switch (Dest->GetColliderShape())
    {
    case EColliderShape::AABB2D:
        return CCollision::CollisionAABB2DToAABB2D(HitPoint,
            this, (CColliderAABB2D*)Dest);
    case EColliderShape::Sphere2D:
        return CCollision::CollisionAABB2DToSphere2D(
            HitPoint, this, (CColliderSphere2D*)Dest);
    }

    return false;
}

