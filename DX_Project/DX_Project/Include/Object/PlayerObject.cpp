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
    //mRoot = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CSpriteComponent>("Player");
    //mBody = CreateComponent<CColliderAABB2D>();
    //mBody = CreateComponent<CColliderSphere2D>();
    mBody = CreateComponent<CColliderOBB2D>();
    mLine = CreateComponent<CColliderLine2D>();
    //mRotationPivot = CreateComponent<CSceneComponent>();
    //mSub = CreateComponent<CSpriteComponent>();
    //mSub2 = CreateComponent<CSpriteComponent>();
    mCamera = CreateComponent<CCameraComponent>();
    mHPBar = CreateComponent<CWidgetComponent>();

    mHPBar->SetRelativePos(-50.f, 50.f);

    CHeadInfo* HeadInfo = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");

    mHPBar->SetWidget(HeadInfo);

    mRoot->AddChild(mHPBar);

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();
    mInventory = CreateComponent<CInventoryComponent>();

    mRoot->SetTexture("Teemo", TEXT("Texture/teemo.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

    mAnimation->AddSequence("PlayerIdle", 1.f, 1.f, true, false);
    mAnimation->AddSequence("PlayerRun", 0.7f, 1.f, true, false);
    mAnimation->AddSequence("PlayerWalk", 0.7f, 1.f, true, false);
    mAnimation->AddSequence("PlayerAttack", 1.f, 1.f, false, false);

    mAnimation->SetEndFunction<CPlayerObject>("PlayerAttack",
        this, &CPlayerObject::AttackEnd);
    mAnimation->AddNotify<CPlayerObject>("PlayerAttack",
        2, this, &CPlayerObject::AttackNotify);

    mRoot->SetWorldPos(500.f, 1000.f, 0.f);
    mRoot->SetWorldScale(100.f, 100.f, 1.f);

    SetRootComponent(mRoot);
    
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(100.f, 100.f);
    //mBody->SetRadius(50.f);

    mRoot->AddChild(mBody);
    mRoot->AddChild(mLine);

    // Default
    mLine->SetCollisionProfile("Player");
    mLine->SetRelativePos(0.f, 50.f);
    mLine->SetLineDistance(300.f);

    mCamera->SetProjectionType(ECameraProjectionType::Ortho);

    mRoot->AddChild(mCamera);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f); 
    //mRotation->SetUpdateComponent(mRotationPivot);
    //mRotation->SetVelocityInit(false);
    //mRotation->SetMoveZ(360.f);

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');
    mScene->GetInput()->AddBindKey("MoveRight", 'D');
    mScene->GetInput()->AddBindKey("MoveLeft", 'A');;
    mScene->GetInput()->AddBindKey("MovePoint", VK_RBUTTON);

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);

    mScene->GetInput()->AddBindKey("Skill1", '1');
    mScene->GetInput()->ChangeKeyCtrl("Skill1", true);
    mScene->GetInput()->ChangeKeyShift("Skill1", true);

    mScene->GetInput()->AddBindKey("Skill2", '2');
    mScene->GetInput()->AddBindKey("Skill3", '3');
    mScene->GetInput()->AddBindKey("Skill4", '4');
    mScene->GetInput()->AddBindKey("Skill5", '5');
    mScene->GetInput()->AddBindKey("Skill6", '6');
    mScene->GetInput()->AddBindKey("Skill7", '7');
    mScene->GetInput()->AddBindKey("Skill8", '8');
    mScene->GetInput()->AddBindKey("Skill9", '9');

    //0311
    //Jump키 변경
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp",
        EInputType::Hold, this, &CPlayerObject::Jump);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown",
        EInputType::Hold, this, &CPlayerObject::MoveDown);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveRight",
        EInputType::Hold, this, &CPlayerObject::MoveRight);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveLeft",
        EInputType::Hold, this, &CPlayerObject::MoveLeft);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MovePoint",
        EInputType::Down, this, &CPlayerObject::MovePoint);



   /* mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ",
        EInputType::Hold, this, &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInv",
        EInputType::Hold, this, &CPlayerObject::RotationZInv);*/

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Fire",
        EInputType::Down, this, &CPlayerObject::Fire);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill1",
        EInputType::Hold, this, &CPlayerObject::Skill1);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill1",
        EInputType::Up, this, &CPlayerObject::Skill1Fire);


    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill2",
        EInputType::Down, this, &CPlayerObject::Skill2);


    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill3",
        EInputType::Down, this, &CPlayerObject::Skill3);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill4",
        EInputType::Down, this, &CPlayerObject::Skill4);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill5",
        EInputType::Down, this, &CPlayerObject::Skill5);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill6",
        EInputType::Down, this, &CPlayerObject::Skill6);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill7",
        EInputType::Down, this, &CPlayerObject::Skill7);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill8",
        EInputType::Down, this, &CPlayerObject::Skill8);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("Skill9",
        EInputType::Down, this, &CPlayerObject::Skill9);

    return true;
}

void CPlayerObject::Update(float DeltaTime)
{   
    //0311
    //플레이어 위치 확인
    IsPlayerOnGround(DeltaTime); 
    IsPlayerCollsionTile(DeltaTime);
    
    //Jump상태 확인
    if (mIsJumping)
        JumpUpdate(DeltaTime);

    CSceneObject::Update(DeltaTime);

 
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

    mAnimation->ChangeAnimation("PlayerWalk");

    mAutoBasePose = true;
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);

    mAnimation->ChangeAnimation("PlayerWalk");

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

    mAnimation->ChangeAnimation("PlayerWalk");

    mAnimation->SetAnimationReverseX(false);

    mAutoBasePose = true;
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1);

    mAnimation->ChangeAnimation("PlayerWalk");

    mAnimation->SetAnimationReverseX(true);

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

//0311
//중력 적용
void CPlayerObject::IsPlayerOnGround(float DeltaTime)
{
    //***비교값은 y축만이므로 FVector2D를 사용하지말고 float로 자료크기를 줄일 수 있음
     
    //플레이어 객체의 하단 좌표
    //좌표값을 가지는 RootComponent의 전역공간에서의 중심점
    //컴포넌트의 스케일에서 절반을 뺀 크기만큼의 좌표
    FVector2D FeetPos = FVector2D(mRoot->GetWorldPosition().x, mRoot->GetWorldPosition().y - mRoot->GetWorldScale().y / 2);
    
    //자신이 속해있는 Scene에서 TileMapObj탐색
    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();
    //타일맵이 존재한다면
    if (TileMap)
    {
        //플레이어의 발이 위치한 좌표의 타일의 이동가능 여부를 확인
        if (TileMap->IsTileBlocked(FeetPos))
        {
            //상태를 바닥 위로 설정
            mIsOnGround = true;
            //플레이어의 Y좌표를 다시 지정
            //발의 위치를 타일 크기만큼 나누면
            //해당 타일이 Y축으로 몇 번째 타일인지 확인 가능
            //정수부에 타일의 크기를 다시 곱하면 타일의 좌표를 도출
            //플레이어의 발에 위치를 타일의 위치로 변경
            //플레이어의 중심좌표를 설정해야 하므로 크기의 절반을 합
            mRoot->SetWorldPos(mRoot->GetWorldPosition().x,
                (FeetPos.y / TileMap->GetTileSize().y) * TileMap->GetTileSize().y + mRoot->GetWorldScale().y / 2);
        }
        else
            //상태를 공중으로 설정
            mIsOnGround = false;
    }

    //MovementComponent의 Velocity변수를 변경하는 함수
    //변경 후 상태가 Update되어야 하므로 SceneObjec::Update() 전에 사용
    if (!mIsOnGround)
		mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1);
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

    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * 2);
   
    if (mJumpingTime <= 0.f)
        mIsJumping = false;
}

void CPlayerObject::IsPlayerCollsionTile(float DeltaTime)
{
    //좌표값을 가지는 RootComponent의 전역공간에서의 중심점
    //컴포넌트의 스케일에서 절반을 뺀 크기만큼의 좌표
    FVector2D RightPos = FVector2D(mRoot->GetWorldPosition().x + mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y);
    FVector2D LeftPos = FVector2D(mRoot->GetWorldPosition().x - mRoot->GetWorldScale().x / 2, mRoot->GetWorldPosition().y);

    CTileMapObj* TileMap = mScene->FindObjectFromType<CTileMapObj>();

    if (TileMap)
    {
        if (TileMap->IsTileBlocked(RightPos))
            mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * -1);
        else if (TileMap->IsTileBlocked(LeftPos))
            mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));
    }
}

