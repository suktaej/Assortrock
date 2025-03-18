#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "TileMapObj.h"
#include "../Scene/Scene.h"
#include "../Component/MovementComponent.h"

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
    mRoot = CreateComponent<CSpriteComponent>();
    mBody = CreateComponent<CColliderAABB2D>();
    mDetect = CreateComponent<CColliderSphere2D>();
    mAttackRange = CreateComponent<CColliderSphere2D>();
    mMovement = CreateComponent<CMovementComponent>();
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);

    mBody->SetCollisionProfile("Monster");
    mBody->SetBoxSize(100.f, 100.f);

    mBody->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonster);
    mBody->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterEnd);

    mRoot->AddChild(mBody);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(100.f);

    mDetect->SetCollisionProfile("MonsterDetect");
    mDetect->SetRadius(100.f);
    mDetect->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterDetect);
    mDetect->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterDetectEnd);
    mRoot->AddChild(mDetect);

    //0318
    //���ݹ���
    mAttackRange->SetCollisionProfile("MonsterAttackRange");
    mAttackRange->SetRadius(20.f);
    mAttackRange->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterAttackRange);
    mAttackRange->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterAttackRangeEnd);
    mRoot->AddChild(mAttackRange);

    //���ݿ� Hitbox
    mAttackSprite = CreateComponent<CSpriteComponent>();

    mRoot->AddChild(mAttackSprite);
    
    //Default ����(�ڽ� Ŭ�������� ũ�� �缳��)
    mAttackSprite->SetWorldScale(100.f, 100.f, 1.f);

    //������ Pivot ����
    //���� ���� Ÿ���� �߰��Ͽ� ���Ͱ� ���Ⱑ �ִ� ���� ���� ���� ����
    //���Ⱑ ���� ��� �Ʒ� Component �� ������ ȣ������ �ʵ��� ����
    SetDefaultPivot(0.5f, 0.5f);
    mAttackSprite->SetPivot(mWeaponPivot);
    
    //���� �� ȣ���Լ��� ������ ����
    //mHitbox->SetCollisionBeginFunc<Class>(this, &Class::Function);

    //AddSequence�� �ڽ� Ŭ�������� ����
    mAttackAnime= mAttackSprite->CreateAnimation2D<CAnimation2D>();
    //mAttackAnime->AddSequence("Attack", 1.f, 1.f, true, false);
    //mAttackAnime->ChangeAnimation("Attack");

    return true;
}

void CMonsterObject::Update(float DeltaTime)
{
    CheckWallCollision(DeltaTime);
    CheckBottomCollision(DeltaTime);
    CheckCeilingCollision(DeltaTime);

    CSceneObject::Update(DeltaTime);

    if (mTarget)
    {
        CLog::PrintLog("Target Find");
        if (!mTarget->IsActive())
        {
            mAI = EMonsterAI::Idle;
            mTarget = nullptr;
        }
        else
        {
            CalTargetDir(); //Ÿ�� ������ �ٶ�(X��)
			mTargetDistance = GetWorldPosition().Distance(mTarget->GetWorldPosition()); // Ÿ�ٰ��� �Ÿ�
        }
    }
    else
    {
        CLog::PrintLog("Target Lost");
        mAI = EMonsterAI::Idle;
    }

    switch (mAI)
    {
    case EMonsterAI::Idle:
        CLog::PrintLog("Idle");
        AIIdle();
        break;
    case EMonsterAI::Trace:
        CLog::PrintLog("Trace");
        AITrace();
        break;
    case EMonsterAI::Patrol:
        CLog::PrintLog("Patrol");
        AIPatrol();
        break;
    case EMonsterAI::Attack:
    {
        CLog::PrintLog("Attack");
        AIAttack();
        break;
    }
    case EMonsterAI::Death:
        CLog::PrintLog("Death");
        AIDeath();
        break;
    case EMonsterAI::Skill:
        AISkill();
        break;
    case EMonsterAI::Custom:
        AICustom();
        break;
    }
}

float CMonsterObject::Damage(float Attack, CSceneObject* Obj)
{
    float Dmg = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Dmg;

    if (mHP <= 0)
        Destroy();

    return Dmg;
}

void CMonsterObject::DetectTarget()
{
}

void CMonsterObject::DetectTargetRelease()
{
}

void CMonsterObject::CollisionMonster( const FVector3D& HitPoint, CColliderBase* Dest)
{
    //CLog::PrintLog("Collision");
}

void CMonsterObject::CollisionMonsterEnd( CColliderBase* Dest)
{
    //CLog::PrintLog("CollisionEnd");
}

void CMonsterObject::CollisionMonsterDetect(const FVector3D& HitPoint, CColliderBase* Dest)
{
    mTarget = Dest->GetOwner();
    mAI = EMonsterAI::Trace;
    DetectTarget();
}

void CMonsterObject::CollisionMonsterDetectEnd(CColliderBase* Dest)
{
    mTarget = nullptr;
    mAI = EMonsterAI::Idle;
    DetectTargetRelease();
}

void CMonsterObject::AIIdle()
{
    //��� ���� �� �̵��� ����
	mMovement->SetMove(FVector3D(0.f, 0.f, 0.f));
    
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
    if (mAttackAnime)
        mAttackAnime->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
}

void CMonsterObject::AIPatrol()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Patrol]);
    if (mAttackAnime)
        mAttackAnime->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
}

void CMonsterObject::AITrace()
{
    //�⺻ �ӵ��� 100
    mMovement->SetMoveSpeed(100.f);

    //�ӵ� �ʱ�ȭ ����
	mMovement->SetVelocityInit(false);

    //Ÿ���� x���� �Ǵ��ϰ� �� �������� velocity�߰�
	if (GetWorldPosition().x - mTarget->GetWorldPosition().x < 0)
		mMovement->AddMoveX(1.f);
	else
		mMovement->AddMoveX(-1.f);

    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Trace]);
    if (mAttackAnime)
        mAttackAnime->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
}

void CMonsterObject::AIAttack()
{
    //���� ���� �� �̵��� ����
	mMovement->SetMove(FVector3D(0.f, 0.f, 0.f));

    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Idle]);
    if (mAttackAnime)
        mAttackAnime->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Attack]);
}

void CMonsterObject::AIDeath()
{
}

void CMonsterObject::AISkill()
{
    if (mAnimation)
        mAnimation->ChangeAnimation(mAIAnimationName[(int)EMonsterAI::Skill]);
}

void CMonsterObject::AICustom()
{
}

//0317
void CMonsterObject::CheckBottomCollision(float DeltaTime)
{
    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();

    FVector2D LT(mRoot->GetWorldPosition().x - mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y + mRoot->GetWorldScale().y / 2);
    FVector2D RB(mRoot->GetWorldPosition().x + mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y - mRoot->GetWorldScale().y / 2);
    FVector2D Center(mRoot->GetWorldPosition().x, mRoot->GetWorldPosition().y);

    if (TileMap)
    {
        if (TileMap->IsTileBlocked(LT.x + 1, RB.y) ||
            TileMap->IsTileBlocked(RB.x - 1, RB.y) ||
            TileMap->IsTileBlocked(Center.x, RB.y))
        {
            //���¸� �ٴ� ���� ����
            mIsOnGround = true;
        }
        else
            //�ٴ� Ÿ���� ���ٸ� ����
            mIsOnGround = false;

        //�ٴڰ� �浹 ���°� �ƴ϶�� �߷� ����
        if (!mIsOnGround)
            mMovement->AddMoveY(-1);
    }
}

void CMonsterObject::CheckWallCollision(float DeltaTime)
{
    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();

    FVector2D LT(mRoot->GetWorldPosition().x - mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y + mRoot->GetWorldScale().y / 2);
    FVector2D RB(mRoot->GetWorldPosition().x + mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y - mRoot->GetWorldScale().y / 2);
    FVector2D Center(mRoot->GetWorldPosition().x, mRoot->GetWorldPosition().y);

    if (TileMap)
    {
        float TileSizeX = TileMap->GetTileSize().x;
        float MonsterX = mRoot->GetWorldPosition().x;

        //���� �� �浹
        if (TileMap->IsTileBlocked(LT.x, LT.y) ||
            TileMap->IsTileBlocked(LT.x, Center.y) ||
            TileMap->IsTileBlocked(LT.x, RB.y + 1))
        {
            // ���� �̵��� ����
            mMovement->AddMoveX(1);
        }
        //���� �� �浹
        else if (TileMap->IsTileBlocked(RB.x, LT.y) ||
            TileMap->IsTileBlocked(RB.x, Center.y) ||
            TileMap->IsTileBlocked(RB.x, RB.y + 1))
        {
            // ���� �̵��� ����
            mMovement->AddMoveX(-1);
        }
    }
}

void CMonsterObject::CheckCeilingCollision(float DeltaTime)
{
    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();

    FVector2D LT(mRoot->GetWorldPosition().x - mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y + mRoot->GetWorldScale().y / 2);
    FVector2D RB(mRoot->GetWorldPosition().x + mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y - mRoot->GetWorldScale().y / 2);
    FVector2D Center(mRoot->GetWorldPosition().x, mRoot->GetWorldPosition().y);

    if (TileMap)
    {
        if (TileMap->IsTileBlocked(LT.x, LT.y) ||
            TileMap->IsTileBlocked(RB.x, LT.y) ||
            TileMap->IsTileBlocked(Center.x, LT.y))
        {
            mIsOnGround = false;
        }
    }
}

void CMonsterObject::CalTargetDir()
{
    if (mTarget->GetWorldPosition().x - mRoot->GetWorldPosition().x > 0)
    {
        mAnimation->SetUVRev(false);
        mAttackAnime->SetUVRev(false);
        mAttackSprite->SetPivot(mWeaponPivot);
    }
    else
    {
        mAnimation->SetUVRev(true);
        mAttackAnime->SetUVRev(true);
        mAttackSprite->SetPivot(1 - mWeaponPivot.x, mWeaponPivot.y);
    }
}

//���ݹ��� �� �÷��̾ ���� ��
void CMonsterObject::CollisionMonsterAttackRange(const FVector3D& HitPoint, CColliderBase* Dest)
{
    mTarget = Dest->GetOwner();
    mHitpoint = HitPoint;
    mAI = EMonsterAI::Attack;
    DetectTarget();
}

void CMonsterObject::CollisionMonsterAttackRangeEnd(CColliderBase* Dest)
{
    mTarget = nullptr;
    mAI = EMonsterAI::Idle;
    DetectTargetRelease();
}

void CMonsterObject::AttackEnd()
{
    CLog::PrintLog("AttackEnd");
}

void CMonsterObject::AttackNotify()
{
}
