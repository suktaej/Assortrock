#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "S3BulletObject.h"

CPlayerObject::CPlayerObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj) :
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
    //CStaticMeshComponent* Root = CreateComponent<CStaticMeshComponent>();
    mRoot = CreateComponent<CStaticMeshComponent>();
    mSub = CreateComponent<CStaticMeshComponent>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    //mRoot 설정
    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldPos(0.f, 0.f, 5.5f);
    
    SetRootComponent(mRoot);

    mRoot->AddChild(mRotationPivot);    
    //mRotationPivot 설정
    mRotationPivot->AddChild(mSub);

    //mSub 설정
    mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");
    
    mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetRelativePos(-2.f, 0.f, 0.f);
       
    //키 지정
    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');
    mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
    mScene->GetInput()->AddBindKey("Skill1", '1');

    mScene->GetInput()->AddBindKey("Skill2", '2');
    
    mScene->GetInput()->AddBindKey("Skill3", '3');

    //Bind
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "MoveUp",
        EInputType::Hold,
        this,
        &CPlayerObject::MoveUp);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "MoveDown",
        EInputType::Hold,
        this,
        &CPlayerObject::MoveDown);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "RotationZ",
        EInputType::Hold,
        this,
        &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "RotationZInv",
        EInputType::Hold,
        this,
        &CPlayerObject::RotationZInv);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Fire",
        EInputType::Down,
        this,
        &CPlayerObject::Fire);

    //Skill 1
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill1",
        EInputType::Hold,
        this,
        &CPlayerObject::Skill1);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill1",
        EInputType::Up,
        this,
        &CPlayerObject::Skill1Fire);

    //Skill 2
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill2",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill2);

    //Skill 3
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill3",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill3);
	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    FVector3D Rot = mRotationPivot->GetRelativeRotation();
    Rot.z += DeltaTime * mPivotRotationSpeed;
    mRotationPivot->SetRelativeRotationZ(Rot.z);

    if (mSkill2Enable)
    {
        UpdateSkill2(DeltaTime);
    }
}

#pragma region movement
void CPlayerObject::MoveUp(float DeltaTime)
{
    FVector3D Pos = mRootComponent->GetWorldPosition();
    FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir * 3.f*DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    FVector3D Pos = mRootComponent->GetWorldPosition();
    FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    mRootComponent->SetWorldPos(Pos + Dir* -1 * 3.f* DeltaTime);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    FVector3D Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    FVector3D Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
}
#pragma endregion movement

#pragma region skill
void CPlayerObject::Fire(float DeltaTime)
{
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    //Root->SetWorldPos(mRoot->GetWorldPosition());
    
    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    //Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(2.f);
}
void CPlayerObject::Skill1(float DeltaTime)
{
    if (!mSkill1Object)
    {
        mSkill1Object = mScene->CreateObj<CBulletObject>("Bullet");
        mSkill1Object->SetSpeed(0.f);
    }
    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    mSkill1Object->GetRootComponent()->SetWorldRotation(mRoot->GetWorldRotation());
    mSkill1Object->GetRootComponent()->SetWorldPos(Pos + Dir);

    FVector3D Scale = mSkill1Object->GetRootComponent()->GetWorldScale();

    Scale.x += DeltaTime * 0.5f;
    Scale.y += DeltaTime * 0.5f;

    if (Scale.x >= 3.f)
        Scale.x = 3.f;

    if (Scale.y >= 3.f)
        Scale.y = 3.f;

    mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
}
void CPlayerObject::Skill1Fire(float DeltaTime)
{
    mSkill1Object->SetSpeed(2.f);
    mSkill1Object->SetLifeTime(2.f);

    mSkill1Object = nullptr;
}

void CPlayerObject::Skill2(float DeltaTime)
{
    if (!mSkill2Enable)
    {
        mSkill2Enable = true;
        mSkill2Time = 3.f;
        mSkill2TimeAcc = 0.f;
        mSkill2TimeInterval = 0.2f;
    }
}

void CPlayerObject::UpdateSkill2(float DeltaTime)
{
    mSkill2TimeAcc += DeltaTime;

    if (mSkill2TimeAcc >= mSkill2TimeInterval)
    {
        mSkill2TimeAcc -= mSkill2TimeInterval;

        CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mSub->GetWorldPosition();
        FVector3D Dir = mSub->GetAxis(EAxis::Y);

        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir);

        Bullet->SetLifeTime(2.f);

       /* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        Root = Bullet->GetRootComponent();

        Pos = mSub2->GetWorldPosition();
        Dir = mSub2->GetAxis(EAxis::Y);

        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir);

        Bullet->SetLifeTime(1.f);*/
    }

    mSkill2Time -= DeltaTime;

    if (mSkill2Time <= 0.f)
        mSkill2Enable = false;
}
void CPlayerObject::Skill3(float DeltaTime)
{
    CS3BulletObject* Bullet = mScene->CreateObj<CS3BulletObject>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    //Root->SetWorldPos(mRoot->GetWorldPosition());

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    //Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(2.f);
}
#pragma endregion skill
