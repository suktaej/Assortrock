#pragma once
#include "SceneObject.h"
#include "../Component/ColliderBase.h"
#include "../Component/SpriteComponent.h"

class CHitboxObj abstract :
    public CSceneObject
{
    friend class CScene;

protected:
    CHitboxObj();
    CHitboxObj(const CHitboxObj& Obj);
    CHitboxObj(CHitboxObj&& Obj);
    virtual ~CHitboxObj();

protected:
    CSharedPtr<class CSpriteComponent> mRoot;
    CSharedPtr<class CColliderBase> mBody;
    class CAnimation2D* mAnimation = nullptr;
    float mDamage = 0.f;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

protected:
    virtual void CollisionAttack(const FVector3D& HitPoint, class CColliderBase* Dest);
    void SetAttackCollisionProfile(const std::string& Name);

public:
    class CColliderBase* GetColliderComponent(){ return mBody; }
    void AttackAction(FVector3D Pos, FVector3D Dir, FVector3D Rot);
    void SetDamage(float dmg) { mDamage = dmg; }
    void SetBoxSize(float x, float y) { mBody->SetBoxSize(x, y); }
    void SetBoxSize(FVector2D Size) { mBody->SetBoxSize(Size); }
};

