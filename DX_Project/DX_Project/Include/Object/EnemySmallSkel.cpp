#include "EnemySmallSkel.h"
#include "PlayerObject.h"
#include "MonsterHitboxObj.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/MovementComponent.h"
#include "../Scene/Scene.h"
#include "../Share/Log.h"

CEnemySmallSkel::CEnemySmallSkel()
{
}

CEnemySmallSkel::CEnemySmallSkel(const CEnemySmallSkel& Obj)
{
}

CEnemySmallSkel::CEnemySmallSkel(CEnemySmallSkel&& Obj)
{
}

CEnemySmallSkel::~CEnemySmallSkel()
{
}

bool CEnemySmallSkel::Init()
{
    CMonsterObject::Init();
    
    mRoot->SetTexture("SmallSkel", TEXT("Texture/Enemy/Skel/Small/idle.png"));
    
    mRoot->SetPivot(0.5f, 0.5f);
    mRoot->SetWorldScale(14.f, 19.f);
    mBody->SetBoxSize(14.f, 19.f);
    
    mAnimation->AddSequence("SmallSkelIdle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("SmallSkelMove", 1.f, 1.f, true, false);

    mAIAnimationName[(int)EMonsterAI::Idle] = "SmallSkelIdle";
    mAIAnimationName[(int)EMonsterAI::Trace] = "SmallSkelMove";
    mAIAnimationName[(int)EMonsterAI::Patrol] = "SmallSkelMove";
    
    //공격 animation은 별도의 충돌체
    mAttackAnime->AddSequence("SmallSkelAttack", 1.2f, 1.f, true, false);
    mAttackAnime->AddSequence("SmallSkelAttackIdle", 1.f, 1.f, false, false);

    mAIAnimationName[(int)EMonsterAI::Attack] = "SmallSkelAttack";
    mAIAnimationName[(int)EMonsterAI::AttackIdle] = "SmallSkelAttackIdle";

    mAttackAnime->SetEndFunction<CEnemySmallSkel>("SmallSkelAttack", this, &CEnemySmallSkel::AttackEnd);
    mAttackAnime->AddNotify<CEnemySmallSkel>("SmallSkelAttack", 6, this, &CEnemySmallSkel::AttackNotify);

    mAttackSprite->SetWorldScale(26.f, 30.f);
    
    SetDefaultPivot(0.f, 0.4f);
    mAttackSprite->SetPivot(mWeaponPivot);
    
    mDetectDistance = 100.f;
    mAttackDistance = 20.f;
	mAttackTime = 0.5f;

    return true;
}

void CEnemySmallSkel::Update(float DeltaTime)
{
    CMonsterObject::Update(DeltaTime);
}

void CEnemySmallSkel::AttackNotify()
{
    CMonsterHitboxObj* Hitbox = mScene->CreateObj<CMonsterHitboxObj>("SmallSkellHitbox");
	Hitbox->SetLifeTime(0.1f);
	Hitbox->SetBoxSize(26.f, 30.f);
	Hitbox->SetWorldPos(mHitpoint.x, mHitpoint.y);
}

void CEnemySmallSkel::AttackEnd()
{
    CLog::PrintLog("AttackEnd");
}
