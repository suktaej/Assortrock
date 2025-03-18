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
    //공격범위
    mAttackRange->SetCollisionProfile("MonsterAttackRange");
    mAttackRange->SetRadius(20.f);
    mAttackRange->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterAttackRange);
    mAttackRange->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterAttackRangeEnd);
    mRoot->AddChild(mAttackRange);

    //공격용 Hitbox
    mAttackSprite = CreateComponent<CSpriteComponent>();

    mRoot->AddChild(mAttackSprite);
    
    //Default 설정(자식 클래스에서 크기 재설정)
    mAttackSprite->SetWorldScale(100.f, 100.f, 1.f);

    //무기의 Pivot 반전
    //추후 몬스터 타입을 추가하여 몬스터가 무기가 있는 경우와 없는 경우로 구분
    //무기가 없을 경우 아래 Component 및 설정을 호출하지 않도록 설정
    SetDefaultPivot(0.5f, 0.5f);
    mAttackSprite->SetPivot(mWeaponPivot);
    
    //공격 시 호출함수는 별도로 지정
    //mHitbox->SetCollisionBeginFunc<Class>(this, &Class::Function);

    //AddSequence는 자식 클래스에서 설정
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
            CalTargetDir(); //타겟 방향을 바라봄(X축)
			mTargetDistance = GetWorldPosition().Distance(mTarget->GetWorldPosition()); // 타겟과의 거리
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
    //대기 상태 시 이동을 정지
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
    //기본 속도는 100
    mMovement->SetMoveSpeed(100.f);

    //속도 초기화 금지
	mMovement->SetVelocityInit(false);

    //타겟의 x값을 판단하고 그 방향으로 velocity추가
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
    //공격 상태 시 이동을 정지
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
            //상태를 바닥 위로 설정
            mIsOnGround = true;
        }
        else
            //바닥 타일이 없다면 공중
            mIsOnGround = false;

        //바닥과 충돌 상태가 아니라면 중력 생성
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

        //좌측 벽 충돌
        if (TileMap->IsTileBlocked(LT.x, LT.y) ||
            TileMap->IsTileBlocked(LT.x, Center.y) ||
            TileMap->IsTileBlocked(LT.x, RB.y + 1))
        {
            // 좌측 이동을 방지
            mMovement->AddMoveX(1);
        }
        //우측 벽 충돌
        else if (TileMap->IsTileBlocked(RB.x, LT.y) ||
            TileMap->IsTileBlocked(RB.x, Center.y) ||
            TileMap->IsTileBlocked(RB.x, RB.y + 1))
        {
            // 우측 이동을 방지
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

//공격범위 내 플레이어가 접근 시
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
