#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"

CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)   :
    CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj) :
    CSceneObject(Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

bool CMonsterObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetBoxSize(100.f, 100.f);

    mRoot->AddChild(mBody);

    return true;
}

void CMonsterObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    if (mTarget)
    {
        if (!mTarget->IsActive())
            mTarget = nullptr;
    }
}
