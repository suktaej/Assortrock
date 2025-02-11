#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "BulletObject.h"
#include "S3BulletObject.h"
#include "S5BulletObject.h"
#include "S6BulletObject.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"

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
    mBody = CreateComponent<CColliderAABB2D>();
    mSub = CreateComponent<CStaticMeshComponent>();
    mRotationPivot = CreateComponent<CSceneComponent>();

    mMovement = CreateComponent<CMovementComponent>();
    mRotation = CreateComponent<CRotationComponent>();
    mCamera = CreateComponent<CCameraComponent>();

    //mRoot ����
    mRoot->SetMesh("PlayerRect");
    mRoot->SetShader("ColorMeshShader");
    
    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetWorldScale(m_PlayerX,m_PlayerY,1.f);
    //������ mRoot�� ��������Ʈ�� ��Ʈ�� ���� 
    SetRootComponent(mRoot);

    //�浹ü �Ҵ�
    mRoot->AddChild(mBody);
    mBody->SetCollisionProfile("Player");
    mBody->SetBoxSize(m_PlayerX, m_PlayerY);

    //�����Ʈ�� ��Ʈ�� �����̱� ���ؼ� update�Լ��� ȣ���Ͽ� ���
    mMovement->SetUpdateComponent(mRoot);
    //������������ ���ϸ鼭 �ȼ����� ���������� �����
    mMovement->SetMoveSpeed(200.f);

    mRotation->SetUpdateComponent(mRotationPivot);
    //Velocity �ʱ�ȭX
    mRotation->SetVelocityInit(false);
    mRotation->SetMoveZ(360.f);

    mRoot->AddChild(mRotationPivot);    
    //mRotationPivot ����
    mRotationPivot->AddChild(mSub);

    //ī�޶� ������ ��������
    mCamera->SetProjectionType(ECameraProjectionType::Ortho);
    mRoot->AddChild(mCamera);

    //mSub ����
    mSub->SetMesh("CenterRect");
    mSub->SetShader("ColorMeshShader");
   
    //������������ ���ϸ� ��뽺���� ���� �θ��� ���� �������� ���ؼ� ���� �������� ����
    //���� �����Ϸ� ���� �����ص� ����
    mSub->SetRelativeScale(0.5f, 0.5f, 1.f);
    mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
       
    //Ű ����
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
    mScene->GetInput()->AddBindKey("Skill6", '6');
    mScene->GetInput()->AddBindKey("Skill7", '7');

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

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill2",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill2);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill3",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill3);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill4",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill4);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill5",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill5);

    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill6",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill6);
    
    mScene->GetInput()->AddBindFunction<CPlayerObject>(
        "Skill7",
        EInputType::Down,
        this, 
        &CPlayerObject::Skill7);

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    //RotationComponent �������� ��� ����
    //FVector3D Rot = mRotationPivot->GetRelativeRotation();
    //Rot.z += DeltaTime * mPivotRotationSpeed;
    //mRotationPivot->SetRelativeRotationZ(Rot.z);

    if (mSkill2Enable)
        UpdateSkill2(DeltaTime);
    
    if (mSkill4Enable)
        UpdateSkill4(DeltaTime);
}

#pragma region movement
void CPlayerObject::Damage(int Dmg)
{
    mHP -= Dmg;
}
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
    //źȯ ����
    CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
    //������ źȯ������Ʈ ���� �� init ����
    //staticmesh ������Ʈ�� �����ϰ� mRoot�� ����
    Bullet->SetBulletCollisionProfile("PlayerBullet");
    //staticmesh ������Ʈ�� �ҷ��ͼ� Root�� ����
    CSceneComponent* Root = Bullet->GetRootComponent();

    //Root->SetWorldPos(mRoot->GetWorldPosition());

    //mRoot�� ��ġ,ȸ��
    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);
   
    //��ȯ���� ������Ʈ�� Ʈ�������� ����
    Root->SetWorldScale(50.f, 50.f);
    Root->SetWorldRotation(mRoot->GetWorldRotation());

    Root->SetWorldPos(Pos + Dir);
    //Root->SetWorldPos(Pos);

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
    mSkill1Object->GetRootComponent()->SetWorldPos(Pos + Dir*100);

    FVector3D Scale = mSkill1Object->GetRootComponent()->GetWorldScale();

    Scale.x += DeltaTime * 100.f;
    Scale.y += DeltaTime * 100.f;

    if (Scale.x >= 200.f)
        Scale.x = 200.f;

    if (Scale.y >= 200.f)
        Scale.y = 200.f;

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
        Root->SetWorldScale(50.f, 50.f);

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
		// DeltaTime / mSkill4ReadyTime �� �ϰ� �Ǹ� Ȯ��Ǵ� 2�ʶ��
        // �ð��� ���ؼ� ���� DeltaTime�� ���ۼ�Ʈ�� �ð��� �귶������
        // ���س���.
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
            mSkill4Range = 150.f;
            mSkill4State = ESkillState::Expansion;
            mPivotRotationSpeed = 180.f;
        }
        mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
        break;
    }
}

void CPlayerObject::Skill5(float DeltaTime)
{
    //�÷��̾��� ������ �����´�
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
void CPlayerObject::Skill6(float DeltaTime)
{
    CS6BulletObject* Bullet = mScene->CreateObj<CS6BulletObject>("Bullet");

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Bullet->SetWorldScale(50.f, 50.f);
    Bullet->SetWorldRotation(mRoot->GetWorldRotation());
    Bullet->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(2.f);
}
void CPlayerObject::Skill7(float DeltaTime)
{
    CS6BulletObject* Bullet = mScene->CreateObj<CS6BulletObject>("Bullet");
    
    Bullet->SetGravityType(EGravityType::Push);

    FVector3D Pos = mRoot->GetWorldPosition();
    FVector3D Dir = mRoot->GetAxis(EAxis::Y);

    Bullet->SetWorldScale(50.f, 50.f);
    Bullet->SetWorldRotation(mRoot->GetWorldRotation());
    Bullet->SetWorldPos(Pos + Dir);

    Bullet->SetLifeTime(2.f);
}
#pragma endregion skill
