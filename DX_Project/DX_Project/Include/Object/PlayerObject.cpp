#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "TornadoBullet.h"
#include "TalonR.h"
#include "GravityBullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "BulletDot.h"
#include "PenetrationBullet.h"
#include "../Component/SpriteComponent.h"
#include "../Animation/Animation2D.h"
#include "../Share/Log.h"
#include "SpriteEffect.h"
#include "../Component/WidgetComponent.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/Common/ProgressBar.h"
#include "../UI/UserWidget/HeadInfo.h"
#include "../Component/InventoryComponent.h"
#include "../Scene/SceneAssetManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Object/TileMapObj.h"
#include "../Scene/Input.h"
#include "../Object/HitboxObj.h"
#include "../Object/SwordHitboxObj.h"
#include "../Object/WeaponObject.h"
//#include "../Object/BowObject.h
//#include "../Object/SwordObject.h"
#include "string"

CPlayerObject::CPlayerObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj)  :
    CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj) :
    CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
    mRoot = CreateComponent<CSpriteComponent>("Player");
    mBody = CreateComponent<CColliderAABB2D>();
    mMovement = CreateComponent<CMovementComponent>();

    mRotation = CreateComponent<CRotationComponent>();
    mRotationPivot = CreateComponent<CSceneComponent>();

    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mHPBar = CreateComponent<CWidgetComponent>();
    mInventory = CreateComponent<CInventoryComponent>();
    
    mCamera = CreateComponent<CCameraComponent>();
    
    mInput = mScene->GetInput();

    SetRootComponent(mRoot);
    
    //중심점 위치 조정
    mRoot->SetPivot(0.5f, 0.5f);
    mRoot->SetWorldPos(115.f, 120.f, 0.f);
    mRoot->SetWorldScale(20.f, 20.f, 1.f);
   
    mRoot->AddChild(mBody);
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(15.f, 20.f);
    
    mRoot->AddChild(mCamera);
    mCamera->SetProjectionType(ECameraProjectionType::Ortho);
    
    CHeadInfo* HeadInfo = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");
    
    mHPBar->SetRelativePos(-50.f, 50.f);
    mHPBar->SetWidget(HeadInfo);

    mRoot->AddChild(mHPBar);

    mAnimation->AddSequence("PlayerIdle", 0.7f, 1.f, true, false);
    mAnimation->AddSequence("PlayerRun", 1.f, 1.f, true, false);
    mAnimation->AddSequence("PlayerJump", 1.0f, 1.f, true, false);
    mAnimation->AddSequence("PlayerDie", 1.f, 1.f, true, false);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f); 

    mRoot->AddChild(mRotationPivot);

#pragma region Weapon
    //0313 > 0317 수정
    //무기 생성
    ////Default Slot은 Sword
    mWeaponSlot = mScene->CreateObj<CWeaponObject>("Slot");
    mWeaponSlot->GetRootComponent()->SetPivot(0.f, 0.5f);
    mWeaponSlot->GetRootComponent()->SetRelativePos(0.f, 0.f);

    mSwap = true;

    //RotationPivot Scale 초기화
    mRotationPivot->SetName("Hand");
    mRotationPivot->SetWorldScale(1.f, 1.f, 1.f);

    //Pivot에 Slot의 SpriteComponent 적용
    mRotationPivot->AddChild(mWeaponSlot->GetRootComponent());

#pragma endregion Weapon

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    //mScene->GetInput()->AddBindKey("MoveDown", 'S');
    mScene->GetInput()->AddBindKey("MoveRight", 'D');
    mScene->GetInput()->AddBindKey("MoveLeft", 'A');;
    mScene->GetInput()->AddBindKey("MovePoint", VK_RBUTTON);

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
    
    mScene->GetInput()->AddBindKey("Slot", '1');

    //mScene->GetInput()->AddBindKey("Skill1", '1');
    //mScene->GetInput()->ChangeKeyCtrl("Skill1", true);
    //mScene->GetInput()->ChangeKeyShift("Skill1", true);

    //0311
    //Jump키 변경
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp",
        EInputType::Hold, this, &CPlayerObject::Jump);
    //하단점프 추가 구현필요
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown",
        EInputType::Hold, this, &CPlayerObject::MoveDown);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveRight",
        EInputType::Hold, this, &CPlayerObject::MoveRight);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveLeft",
        EInputType::Hold, this, &CPlayerObject::MoveLeft);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MovePoint", EInputType::Down, this, &CPlayerObject::MovePoint);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>("Slot", EInputType::Down, this, &CPlayerObject::SwapWeapon);
    
   
    /* mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ",
        EInputType::Hold, this, &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInv",
        EInputType::Hold, this, &CPlayerObject::RotationZInv);*/

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Fire",
        EInputType::Down, this, &CPlayerObject::Fire);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{   
    //0311
    //Jump상태 확인
    if (mIsJumping)
        JumpUpdate(DeltaTime);
   
    //플레이어 위치 확인
    CheckWallCollision(DeltaTime);
    CheckBottomCollision(DeltaTime);
    CheckCeilingCollision(DeltaTime);
    
    //마우스 위치에 따른 플레이어 좌우반전
    CalPlayerDir();
    
    CSceneObject::Update(DeltaTime);
    CLog::PrintLog(std::to_string(mHP));
    //0313
    //마우스 위치를 가져옴
    const FVector2D& MousePos = mInput->GetMouseWorldPos2D();
    //Pivot과 마우스의 각도확인
    FollowMouse(DeltaTime, MousePos);
    //마우스 방향으로 무기를 듦
    mRotationPivot->SetWorldRotationZ(mMouseDeg);
    
    //무기가 검이라면 마우스 방향 90도 위치
    if(!strcmp("Sword",mWeaponSlot->GetWeaponName().c_str()))
		mWeaponSlot->GetSpriteComponent()->SetRelativeRotationZ(mSwingDeg);
    else
		mWeaponSlot->GetSpriteComponent()->SetRelativeRotationZ(0.f);

    if (mInput->GetMouseDown(EMouseButtonType::LButton))
    {   
        if (mSwap == true)
        {
            //Hitbox 생성 및 제거
            CSwordHitboxObj* SwordHitbox = mScene->CreateObj<CSwordHitboxObj>("SwordAttackHitBox");
            SwordHitbox->AttackAction(mWeaponPos, mWeaponDir, mWeaponRot);
            //무기좌표를 반전
            mWeaponSlot->GetSpriteComponent()->SetRelativeRotationZ(mSwingDeg+=180.f);
        }
        else
        {
            ArrowFire();
        }
    }

    //if (mSkill2Enable)
    //{
    //    UpdateSkill2(DeltaTime);
    //}

    //if (mSkill4Enable)
    //{
    //    UpdateSkill4(DeltaTime);
    //}

    if (mMovement->GetVelocityLength() == 0.f && mAutoBasePose)
        mAnimation->ChangeAnimation("PlayerIdle");

    static bool ItemTest = false;

    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        ItemTest = true;
    }

    else if (ItemTest)
    {
        ItemTest = false;

        std::string NameArray[2] =
        {
            "IconSword",
            "IconShield"
        };

        int RandIndex = rand() % 2;

        FItemData* Data = new FItemData;

        Data->Name = NameArray[RandIndex];

        if (RandIndex == 0)
            Data->Type = EItemType::Weapon;

        else if (RandIndex == 1)
            Data->Type = EItemType::Armor;

        if (mScene)
            Data->Icon = mScene->GetAssetManager()->FindTexture(NameArray[RandIndex]);

        else
            Data->Icon = CAssetManager::GetInst()->GetTextureManager()->FindTexture(NameArray[RandIndex]);

        mInventory->AddItem(Data);
    }

    static bool ItemTest1 = false;

    if (GetAsyncKeyState('0') & 0x8000)
    {
        ItemTest1 = true;
    }

    else if (ItemTest1)
    {
        ItemTest1 = false;

        mInventory->RemoveItem(rand() % 10);
    }
}

void CPlayerObject::Render()
{
    CSceneObject::Render();
}

void CPlayerObject::Damage(int Dmg)
{
    mHP -= Dmg;
}

float CPlayerObject::Damage(float Attack, CSceneObject* Obj)
{
    Attack = CSceneObject::Damage(Attack, Obj);

    mHP -= (int)Attack;

    return Attack;
}

void CPlayerObject::MoveUp(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));

    mAnimation->ChangeAnimation("PlayerJump");

    mAutoBasePose = true;
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);

    mAnimation->ChangeAnimation("PlayerRun");

    mAutoBasePose = true;
}

void CPlayerObject::MovePoint(float DeltaTime)
{
    mMovement->SetMovePoint(mScene->GetInput()->GetMouseWorldPos2D());
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
}

void CPlayerObject::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));

    //CalPlayerDir();
    //mAnimation->SetUVRev(false);
    mAnimation->ChangeAnimation("PlayerRun");
	
    //mAnimation->SetAnimationReverseX(false);

    mAutoBasePose = true;
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1);

    //CalPlayerDir();
    //mAnimation->SetUVRev(true);
    mAnimation->ChangeAnimation("PlayerRun");

    //mAnimation->SetAnimationReverseX(true);

    mAutoBasePose = true;
}

void CPlayerObject::Fire(float DeltaTime)
{
    mAnimation->ChangeAnimation("PlayerAttack");

    mAutoBasePose = false;
}

void CPlayerObject::Skill1(float DeltaTime)
{
    if (!mSkill1Object)
    {
        mSkill1Object = mScene->CreateObj<CBulletObject>("Bullet");
        mSkill1Object->SetSpeed(0.f);
    }

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);

    mSkill1Object->GetRootComponent()->SetWorldRotation(mRoot->GetWorldRotation());
    mSkill1Object->GetRootComponent()->SetWorldPos(Pos + Dir);

    FVector3D   Scale = mSkill1Object->GetRootComponent()->GetWorldScale();

    Scale.x += DeltaTime * 0.5f;
    Scale.y += DeltaTime * 0.5f;

    if (Scale.x >= 4.f)
        Scale.x = 4.f;

    if (Scale.y >= 4.f)
        Scale.y = 4.f;

    mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
    mSkill1Object->SetSpeed(2.f);

    mSkill1Object->SetLifeTime(1.f);

    mSkill1Object = nullptr;
}

void CPlayerObject::Skill2(float DeltaTime)
{
    // 스킬 2번이 비활성화일 경우 활성화한다.
    if (!mSkill2Enable)
    {
        mSkill2Enable = true;
        mSkill2Time = 3.f;
        mSkill2TimeAcc = 0.f;
        mSkill2TimeInterval = 0.2f;
    }
}

void CPlayerObject::Skill3(float DeltaTime)
{
    CTornadoBullet* Bullet = mScene->CreateObj<CTornadoBullet>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(10.f);
}

void CPlayerObject::Skill4(float DeltaTime)
{
    if (!mSkill4Enable)
    {
        mSkill4Enable = true;
        mSkill4Time = 5.f;
        mSkill4TimeAcc = 0.f;
        mSkill4ReadyTime = 2.f;

        mPivotRotationSpeed = 360.f;
        mSkill4State = ESkill4State::Expansion;
    }
}

void CPlayerObject::Skill5(float DeltaTime)
{
    // 8개 방향에 총알을 생성한다.
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);
    FVector3D   Rot = mRoot->GetWorldRotation();

    FMatrix matRot;
    matRot.RotationZ(45.f);

    for (int i = 0; i < 8; ++i)
    {
        CTalonR* Bullet = mScene->CreateObj<CTalonR>("Bullet");

        Bullet->SetTarget(this);

        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mRoot->GetWorldPosition();

        Root->SetWorldRotation(Rot);
        Root->SetWorldPos(Pos + Dir);

        Rot.z += 45.f;

        Dir = Dir.TransformNormal(matRot);
        Dir.Normalize();
    }
}

void CPlayerObject::Skill6(float DeltaTime)
{
    CGravityBullet* Bullet = mScene->CreateObj<CGravityBullet>("Bullet");

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Bullet->SetWorldScale(50.f, 50.f);
    Bullet->SetWorldRotation(mRoot->GetWorldRotation());
    Bullet->SetWorldPos(Pos + Dir * 75.f);
}

void CPlayerObject::Skill7(float DeltaTime)
{
    CGravityBullet* Bullet = mScene->CreateObj<CGravityBullet>("Bullet");

    Bullet->SetGravityType(EGravityType::Push);

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Bullet->SetWorldScale(50.f, 50.f);
    Bullet->SetWorldRotation(mRoot->GetWorldRotation());
    Bullet->SetWorldPos(Pos + Dir * 75.f);
}

void CPlayerObject::Skill8(float DeltaTime)
{
    CBulletDot* Bullet = mScene->CreateObj<CBulletDot>("Bullet");

    Bullet->SetBulletCollisionProfile("PlayerAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(300.f, 300.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetBoxSize(300.f, 300.f);
}

void CPlayerObject::Skill9(float DeltaTime)
{
    CPenetrationBullet* Bullet =
        mScene->CreateObj<CPenetrationBullet>("Bullet");

    Bullet->SetBulletCollisionProfile("PlayerAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);
}

//void CPlayerObject::UpdateSkill2(float DeltaTime)
//{
//    mSkill2TimeAcc += DeltaTime;
//
//    if (mSkill2TimeAcc >= mSkill2TimeInterval)
//    {
//        mSkill2TimeAcc -= mSkill2TimeInterval;
//
//        CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
//
//        CSceneComponent* Root = Bullet->GetRootComponent();
//
//        FVector3D Pos = mSub->GetWorldPosition();
//        FVector3D   Dir = mSub->GetAxis(EAxis::Y);
//
//        Root->SetWorldRotation(mRoot->GetWorldRotation());
//        Root->SetWorldPos(Pos + Dir);
//
//        Bullet->SetLifeTime(1.f);
//
//        Bullet = mScene->CreateObj<CBulletObject>("Bullet");
//
//        Root = Bullet->GetRootComponent();
//
//        Pos = mSub2->GetWorldPosition();
//        Dir = mSub2->GetAxis(EAxis::Y);
//
//        Root->SetWorldRotation(mRoot->GetWorldRotation());
//        Root->SetWorldPos(Pos + Dir);
//
//        Bullet->SetLifeTime(1.f);
//    }
//
//    mSkill2Time -= DeltaTime;
//
//    if (mSkill2Time <= 0.f)
//    {
//        mSkill2Enable = false;
//    }
//}
//
//void CPlayerObject::UpdateSkill4(float DeltaTime)
//{
//    mSkill4TimeAcc += DeltaTime;
//
//    switch (mSkill4State)
//    {
//    case ESkill4State::Expansion:
//        // DeltaTime / mSkill4ReadyTime 을 하게 되면 확장되는 2초라는
//        // 시간에 대해서 현재 DeltaTime이 몇퍼센트의 시간이 흘렀는지를
//        // 구해낸다.
//        mSkill4Range += DeltaTime / mSkill4ReadyTime * 
//            mSkill4RangeLength;
//        if (mSkill4TimeAcc >= mSkill4ReadyTime)
//        {
//            mSkill4TimeAcc -= mSkill4ReadyTime;
//            mSkill4Range = mSkill4MaxRange;
//            mSkill4State = ESkill4State::Maintain;
//        }
//
//        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
//
//        mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
//        break;
//    case ESkill4State::Maintain:
//
//        if (mSkill4TimeAcc >= mSkill4Time)
//        {
//            mSkill4TimeAcc = 0.f;
//            mSkill4State = ESkill4State::Reduction;
//        }
//        break;
//    case ESkill4State::Reduction:
//
//        mSkill4Range -= DeltaTime / mSkill4ReadyTime *
//            mSkill4RangeLength;
//        if (mSkill4TimeAcc >= mSkill4ReadyTime)
//        {
//            mSkill4Enable = false;
//            mSkill4TimeAcc = 0.f;
//            mSkill4Range = 2.f;
//            mSkill4State = ESkill4State::Expansion;
//            mPivotRotationSpeed = 180.f;
//        }
//
//        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
//
//        mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
//        break;
//    }
//
//}

void CPlayerObject::AttackEnd()
{
    CLog::PrintLog("AttackEnd");
    mAnimation->ChangeAnimation("PlayerIdle");
}

void CPlayerObject::AttackNotify()
{
    CLog::PrintLog("Attack");
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    Bullet->SetBulletCollisionProfile("PlayerAttack");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 75.f);

    Bullet->SetLifeTime(2.f);
}

void CPlayerObject::Jump(float DeltaTime)
{
    //공중에 있다면 점프 불가
    if (!mIsOnGround)
        return;
    
    if (!mIsJumping)
    {
        mIsJumping = true;
		mIsOnGround = false;
        mJumpingTime = 0.5f;
    }
}

void CPlayerObject::JumpUpdate(float DeltaTime)
{
    mJumpingTime -= DeltaTime;

    mMovement->AddMoveY(2);
   
    if (mJumpingTime <= 0.f)
    {
        mIsJumping = false;
    }
}
//0312
//방향별 충돌 확인
void CPlayerObject::CheckBottomCollision(float DeltaTime)
{
    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();

    FVector2D LT(mRoot->GetWorldPosition().x - mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y + mRoot->GetWorldScale().y / 2);
    FVector2D RB(mRoot->GetWorldPosition().x + mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y - mRoot->GetWorldScale().y / 2);
    FVector2D Center(mRoot->GetWorldPosition().x, mRoot->GetWorldPosition().y);

    if (TileMap)
    {
        if (TileMap->IsTileBlocked(LT.x+1, RB.y) ||
            TileMap->IsTileBlocked(RB.x-1, RB.y) ||
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

void CPlayerObject::CheckWallCollision(float DeltaTime)
{
    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();

    FVector2D LT(mRoot->GetWorldPosition().x - mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y + mRoot->GetWorldScale().y / 2);
    FVector2D RB(mRoot->GetWorldPosition().x + mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y - mRoot->GetWorldScale().y / 2);
    FVector2D Center(mRoot->GetWorldPosition().x, mRoot->GetWorldPosition().y);

    if (TileMap)
    {
        float TileSizeX = TileMap->GetTileSize().x; 
		float PlayerX = mRoot->GetWorldPosition().x; 

        //좌측 벽 충돌
        if (TileMap->IsTileBlocked(LT.x, LT.y) ||
            TileMap->IsTileBlocked(LT.x, Center.y)||
            TileMap->IsTileBlocked(LT.x, RB.y+1))
        {
            // 좌측 이동을 방지
            mMovement->AddMoveX(1);
        }
        //우측 벽 충돌
		else if (TileMap->IsTileBlocked(RB.x, LT.y) ||
			TileMap->IsTileBlocked(RB.x, Center.y) ||
			TileMap->IsTileBlocked(RB.x, RB.y+1))
        {
            // 우측 이동을 방지
            mMovement->AddMoveX(-1);
        }
    }
}

void CPlayerObject::CheckCeilingCollision(float DeltaTime)
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
            mIsJumping = false;
            mIsOnGround = false;
            //mMovement->SetMoveSpeed(400);
        }
    }
}

void CPlayerObject::FollowMouse(float DeltaTime,const FVector2D& MousePos)
{
    FVector3D PivotPos = mRotationPivot->GetWorldPosition();
 
    mMousePos = FVector2D(MousePos.x - PivotPos.x, MousePos.y - PivotPos.y);
    mMousePos.Normalize();

    float angleRad = atan2(mMousePos.y, mMousePos.x);
    mMouseDeg = angleRad * (180.0 / 3.14159265358979323846);

    mWeaponPos =FVector3D(mRotationPivot->GetWorldPosition());
	mWeaponDir = FVector3D(mMousePos.x, mMousePos.y, 0.f);
    mWeaponRot = FVector3D(mRotationPivot->GetWorldRotation());
}

void CPlayerObject::ArrowFire()
{
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Arrow");
    CSceneComponent* Root = Bullet->GetRootComponent();

    Bullet->SetBulletCollisionProfile("PlayerAttack");

    FVector3D Pos = mRotationPivot->GetWorldPosition();
    FVector3D Dir(mMousePos.x, mMousePos.y, 0.f);

    Root->SetWorldScale(13.f, 5.f);
    Root->SetWorldRotation(mRotationPivot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir * 20.f);

    Bullet->SetLifeTime(2.f);
}

void CPlayerObject::CalPlayerDir()
{
    //CLog::PrintLog(std::to_string(mMousePos.x));
    if(mMousePos.x > 0)
        mAnimation->SetUVRev(false);
    else
        mAnimation->SetUVRev(true);
}

void CPlayerObject::SwapWeapon(float DeltaTime)
{
    if (mSwap)
    {
        mSwap = false;
        mWeaponSlot->SetInfo("Bow", TEXT("Texture/Weapon/Bow.png"), FVector2D(17.f, 13.f));
    }
    else
    {
        mSwap = true; 
        mWeaponSlot->SetInfo("Sword", TEXT("Texture/Weapon/Sword.png"), FVector2D(19.f, 7.f));
    }
}
