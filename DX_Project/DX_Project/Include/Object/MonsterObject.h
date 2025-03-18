#pragma once

#include "SceneObject.h"

enum class EMonsterAI : unsigned char
{
    Idle,
    Trace,
    Patrol,
    Attack,
    AttackIdle,
    Death,
    Skill,
    Custom,
    End
};

class CMonsterObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CMonsterObject();
    CMonsterObject(const CMonsterObject& Obj);
    CMonsterObject(CMonsterObject&& Obj);
    virtual ~CMonsterObject();

protected:
    CSharedPtr<class CSpriteComponent> mRoot;
    CSharedPtr<class CColliderAABB2D> mBody;
    //???탐지 범위는 원형이 일반적인가?
    CSharedPtr<class CColliderSphere2D> mDetect;
    CSharedPtr<class CColliderSphere2D> mAttackRange;
    CSharedPtr<class CMovementComponent> mMovement;

    CSharedPtr<CSceneObject>  mTarget;
    class CAnimation2D* mAnimation = nullptr;
    EMonsterAI          mAI = EMonsterAI::Idle;
    std::string         mAIAnimationName[(int)EMonsterAI::End];

    float           mDetectDistance = 0.f;
    int             mHP = 5;

    //0317
    bool mIsOnGround = false;
    float mAttackDistance = 0.f;    //공격범위
    float mTargetDistance = 0.f;    //타겟이 생성되었을 때 타겟까지의 거리

    bool mAttackActive = false;     //공격이 시작되는지 확인
    float mAttackCoolTime = 1.f;    //공격 후 다음 공격까지의 시간
    float mCoolTimeAcc = mAttackCoolTime;   //DeltaTime 누적을 위한 변수
    
    FVector2D mWeaponPivot;
    FVector3D mHitpoint;    //공격범위로 들어온 좌표값을 저장
    
    CSharedPtr<class CSpriteComponent> mAttackSprite;
    class CAnimation2D* mAttackAnime = nullptr;

public:
    void SetTarget(class CSceneObject* Target) { mTarget = Target; }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    virtual float Damage(float Attack, CSceneObject* Obj);

protected:
    virtual void DetectTarget();
    virtual void DetectTargetRelease();

private:
    void CollisionMonster(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionMonsterEnd(class CColliderBase* Dest);

    void CollisionMonsterDetect(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionMonsterDetectEnd(class CColliderBase* Dest);

protected:  // ============ AI Virtual Function ===============
    virtual void AIIdle();
    virtual void AIPatrol();
    virtual void AITrace();
    virtual void AIAttack();
    virtual void AIDeath();
    virtual void AISkill();
    virtual void AICustom();

    //0317
    //타일충돌
    void CheckBottomCollision(float DeltaTime);
    void CheckWallCollision(float DeltaTime);
    void CheckCeilingCollision(float DeltaTime);
    //타겟(플레이어)방향으로 애니메이션 반전
    void CalTargetDir();
    //몬스터 무기 오른쪽 방향 위치 지정
    void SetDefaultPivot(float x, float y) { mWeaponPivot = FVector2D(x, y); }
    void SetCoolTime(float time) { mAttackCoolTime = time; }
    //몬스터 공격범위
    void CollisionMonsterAttackRange(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionMonsterAttackRangeEnd(class CColliderBase* Dest);
    //Notify를 통해 호출될 함수
    virtual void AttackEnd();
    virtual void AttackNotify();
};

