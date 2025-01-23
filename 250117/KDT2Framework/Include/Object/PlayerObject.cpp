#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "TornadoBullet.h"
#include "TalonR.h"
#include "../Component/MovementComponent.h"

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
    mRoot = CreateComponent<CStaticMeshComponent>();
    mRotationPivot = CreateComponent<CSceneComponent>();
    mSub = CreateComponent<CStaticMeshComponent>();
    mSub2 = CreateComponent<CStaticMeshComponent>();
    mMovement = CreateComponent<CMovementComponent>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldPos(0.f, 0.f, 5.5f);

    SetRootComponent(mRoot);

    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(2.f);

    mRoot->AddChild(mRotationPivot);
    mRotationPivot->AddChild(mSub);
    mRotationPivot->AddChild(mSub2);

    mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");

    mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);

    mSub2->SetMesh("CenterRect");
    mSub2->SetShader("ColorMeshShader");

    mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);

    mScene->GetInput()->AddBindKey("MoveUp", 'W');
    mScene->GetInput()->AddBindKey("MoveDown", 'S');

    mScene->GetInput()->AddBindKey("RotationZ", 'D');
    mScene->GetInput()->AddBindKey("RotationZInv", 'A');

    mScene->GetInput()->AddBindKey("Fire", VK_SPACE);

    mScene->GetInput()->AddBindKey("Skill1", '1');
    mScene->GetInput()->ChangeKeyCtrl("Skill1", true);
    mScene->GetInput()->ChangeKeyShift("Skill1", true);

    mScene->GetInput()->AddBindKey("Skill2", '2');
    mScene->GetInput()->AddBindKey("Skill3", '3');
    mScene->GetInput()->AddBindKey("Skill4", '4');
    mScene->GetInput()->AddBindKey("Skill5", '5');

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp",
        EInputType::Hold, this, &CPlayerObject::MoveUp);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown",
        EInputType::Hold, this, &CPlayerObject::MoveDown);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ",
        EInputType::Hold, this, &CPlayerObject::RotationZ);

    mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInv",
        EInputType::Hold, this, &CPlayerObject::RotationZInv);

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

    if (mSkill4Enable)
    {
        UpdateSkill4(DeltaTime);
    }
}

void CPlayerObject::MoveUp(float DeltaTime)
{
    mMovement->Move(mRootComponent->GetAxis(EAxis::Y));
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->Move(mRootComponent->GetAxis(EAxis::Y) * -1.f);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * 90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
    FVector3D   Rot = mRootComponent->GetWorldRotation();
    mRootComponent->SetWorldRotationZ(Rot.z + DeltaTime * -90.f);
}

void CPlayerObject::Fire(float DeltaTime)
{
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

    CSceneComponent* Root = Bullet->GetRootComponent();

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D   Dir = mRoot->GetAxis(EAxis::Y);

    Root->SetWorldRotation(mRoot->GetWorldRotation());
    Root->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(1.f);
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

void CPlayerObject::UpdateSkill2(float DeltaTime)
{
    mSkill2TimeAcc += DeltaTime;

    if (mSkill2TimeAcc >= mSkill2TimeInterval)
    {
        mSkill2TimeAcc -= mSkill2TimeInterval;

        CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mSub->GetWorldPosition();
        FVector3D   Dir = mSub->GetAxis(EAxis::Y);

        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir);

        Bullet->SetLifeTime(1.f);

        Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        Root = Bullet->GetRootComponent();

        Pos = mSub2->GetWorldPosition();
        Dir = mSub2->GetAxis(EAxis::Y);

        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir);

        Bullet->SetLifeTime(1.f);
    }

    mSkill2Time -= DeltaTime;

    if (mSkill2Time <= 0.f)
    {
        mSkill2Enable = false;
    }
}

void CPlayerObject::UpdateSkill4(float DeltaTime)
{
    mSkill4TimeAcc += DeltaTime;

    switch (mSkill4State)
    {
    case ESkill4State::Expansion:
        // DeltaTime / mSkill4ReadyTime 을 하게 되면 확장되는 2초라는
        // 시간에 대해서 현재 DeltaTime이 몇퍼센트의 시간이 흘렀는지를
        // 구해낸다.
        mSkill4Range += DeltaTime / mSkill4ReadyTime * 
            mSkill4RangeLength;
        if (mSkill4TimeAcc >= mSkill4ReadyTime)
        {
            mSkill4TimeAcc -= mSkill4ReadyTime;
            mSkill4Range = mSkill4MaxRange;
            mSkill4State = ESkill4State::Maintain;
        }

        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);

        mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
        break;
    case ESkill4State::Maintain:

        if (mSkill4TimeAcc >= mSkill4Time)
        {
            mSkill4TimeAcc = 0.f;
            mSkill4State = ESkill4State::Reduction;
        }
        break;
    case ESkill4State::Reduction:

        mSkill4Range -= DeltaTime / mSkill4ReadyTime *
            mSkill4RangeLength;
        if (mSkill4TimeAcc >= mSkill4ReadyTime)
        {
            mSkill4Enable = false;
            mSkill4TimeAcc = 0.f;
            mSkill4Range = 2.f;
            mSkill4State = ESkill4State::Expansion;
            mPivotRotationSpeed = 180.f;
        }

        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);

        mSub2->SetRelativePos(mSkill4Range, 0.f, 0.f);
        break;
    }

}
