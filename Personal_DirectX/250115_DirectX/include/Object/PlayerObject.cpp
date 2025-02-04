#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "S3BulletObject.h"
#include "S5BulletObject.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"

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
    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();
    mCamera = CreateComponent<CCameraComponent>();

    //mRoot 설정
    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");
    
    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetWorldScale(100.f,100.f,1.f);
    
    SetRootComponent(mRoot);

    //무브번트가 루트를 움직이기 위해서 update함수를 호출하여 사용
    mMovement->SetUpdateComponent(mRoot);
    //직교투영으로 변하면서 픽셀단위 움직임으로 변경됨
    mMovement->SetMoveSpeed(200.f);

    mRotation->SetUpdateComponent(mRotationPivot);
    //Velocity 초기화X
    mRotation->SetVelocityInit(false);
    mRotation->SetMoveZ(360.f);

    mRoot->AddChild(mRotationPivot);    
    //mRotationPivot 설정
    mRotationPivot->AddChild(mSub);

    //카메라 설정을 직교투영
    mCamera->SetProjectionType(ECameraProjectionType::Ortho);
    mRoot->AddChild(mCamera);

    //mSub 설정
    mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");
   
    //직교투영으로 변하며 상대스케일 값은 부모의 월드 스케일을 곱해서 최종 스케일이 도출
    //월드 스케일로 직접 지정해도 무관
    mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
       
    //키 지정
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
    //5번스킬 수정
    mScene->GetInput()->AddBindKey("Skill5", '5');

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
    
    //Skill 4
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill4",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill4);
    
    //Skill 5
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill5",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill5);

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    //RotationComponent 삽입으로 기능 제거
    //FVector3D Rot = mRotationPivot->GetRelativeRotation();
    //Rot.z += DeltaTime * mPivotRotationSpeed;
    //mRotationPivot->SetRelativeRotationZ(Rot.z);

    if (mSkill2Enable)
        UpdateSkill2(DeltaTime);
    
    if (mSkill4Enable)
        UpdateSkill4(DeltaTime);
}

#pragma region movement
void CPlayerObject::MoveUp(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));
    //FVector3D Pos = mRootComponent->GetWorldPosition();
    //FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    //mRootComponent->SetWorldPos(Pos + Dir * 3.f*DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1.f);
    //FVector3D Pos = mRootComponent->GetWorldPosition();
    //FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

    //mRootComponent->SetWorldPos(Pos + Dir* -1 * 3.f* DeltaTime);
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

    Root->SetWorldScale(50.f, 50.f);
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
void CPlayerObject::Skill4(float DeltaTime)
{
    if (!mSkill4Enable)
    {
        mSkill4Enable = true;
        mSkill4Time = 3.f;
        mSkill4TimeAcc = 0.f;
        mSkill4ReadyTime = 2.f;
        mPivotRotationSpeed = 360.f;
        mSkill4State = ESkillState::Expansion;
    }
}

void CPlayerObject::UpdateSkill4(float DeltaTime)
{
    mSkill4TimeAcc += DeltaTime;

    switch (mSkill4State)
    {
    case ESkillState::Expansion:
		// DeltaTime / mSkill4ReadyTime 을 하게 되면 확장되는 2초라는
        // 시간에 대해서 현재 DeltaTime이 몇퍼센트의 시간이 흘렀는지를
        // 구해낸다.
        mSkill4Range += DeltaTime / mSkill4ReadyTime * mSkill4RangeLength;

        if (mSkill4TimeAcc >= mSkill4ReadyTime)
        {
            mSkill4TimeAcc -= mSkill4ReadyTime;
            mSkill4Range = mSkill4MaxRange;
            mSkill4State = ESkillState::Maintain;
        }

		mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
        break;
    case ESkillState::Maintain:

        if (mSkill4TimeAcc >= mSkill4Time)
        {
            mSkill4TimeAcc = 0.f;
            mSkill4State = ESkillState::Reduction;
        }
        break;
    case ESkillState::Reduction:

        mSkill4Range -= DeltaTime / mSkill4ReadyTime * mSkill4RangeLength;
        if (mSkill4TimeAcc >= mSkill4ReadyTime)
        {
            mSkill4Enable = false;
            mSkill4TimeAcc = 0.f;
            mSkill4Range = 2.f;
            mSkill4State = ESkillState::Expansion;
            mPivotRotationSpeed = 180.f;
        }
        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
        break;
    }
}

void CPlayerObject::Skill5(float DeltaTime)
{
    //플레이어의 방향을 가져온다
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);
    FVector3D Rot = mRoot->GetWorldRotation();
    
    FMatrix matRot;
    matRot.RotationZ(45.f);

    for (int i = 0;i < 8;i++)
    {
        CS5BulletObject* Bullet = mScene->CreateObj<CS5BulletObject>("Bullet");

        Bullet->SetTarget(this);

        CSceneComponent* Root = Bullet->GetRootComponent();

        //Root->SetWorldPos(mRoot->GetWorldPosition());

        FVector3D Pos = mRoot->GetWorldPosition();

        Root->SetWorldRotation(Rot);
        Root->SetWorldPos(Pos + Dir);

        Rot.z += 45.f;
        Dir = Dir.TransformNormal(matRot);
        Dir.Normalize();
    }
}
#pragma endregion skill
