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
    //???Ž�� ������ ������ �Ϲ����ΰ�?
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
    float mAttackDistance = 0.f;    //���ݹ���
    float mTargetDistance = 0.f;    //Ÿ���� �����Ǿ��� �� Ÿ�ٱ����� �Ÿ�

    bool mAttackActive = false;     //������ ���۵Ǵ��� Ȯ��
    float mAttackCoolTime = 1.f;    //���� �� ���� ���ݱ����� �ð�
    float mCoolTimeAcc = mAttackCoolTime;   //DeltaTime ������ ���� ����
    
    FVector2D mWeaponPivot;
    FVector3D mHitpoint;    //���ݹ����� ���� ��ǥ���� ����
    
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
    //Ÿ���浹
    void CheckBottomCollision(float DeltaTime);
    void CheckWallCollision(float DeltaTime);
    void CheckCeilingCollision(float DeltaTime);
    //Ÿ��(�÷��̾�)�������� �ִϸ��̼� ����
    void CalTargetDir();
    //���� ���� ������ ���� ��ġ ����
    void SetDefaultPivot(float x, float y) { mWeaponPivot = FVector2D(x, y); }
    void SetCoolTime(float time) { mAttackCoolTime = time; }
    //���� ���ݹ���
    void CollisionMonsterAttackRange(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionMonsterAttackRangeEnd(class CColliderBase* Dest);
    //Notify�� ���� ȣ��� �Լ�
    virtual void AttackEnd();
    virtual void AttackNotify();
};

