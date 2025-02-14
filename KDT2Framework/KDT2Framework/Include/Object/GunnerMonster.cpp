#include "GunnerMonster.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "PlayerObject.h"

CGunnerMonster::CGunnerMonster()
{
}

CGunnerMonster::CGunnerMonster(const CGunnerMonster& Obj) :
    CMonsterObject(Obj)
{
}

CGunnerMonster::CGunnerMonster(CGunnerMonster&& Obj) :
    CMonsterObject(Obj)
{
}

CGunnerMonster::~CGunnerMonster()
{
}

bool CGunnerMonster::Init()
{
    CMonsterObject::Init();

    mRoot->SetTexture("Monster1Tex", TEXT("Texture/block_wall.png"));
    mRoot->SetPivot(0.5f, 0.5f);
    //mRoot->SetMesh("CenterTexRect");
    //mRoot->AddTexture(0, "Teemo", TEXT("Texture/teemo.png"), 0);
    //mRoot->SetMaterial(0, "Monster1");
    //mRoot->SetShader("StaticMeshShader");
    //mRoot->SetOpacity(0, 0.5f);

    SetTarget(mScene->FindObjectFromType<CPlayerObject>());

    return true;
}

void CGunnerMonster::Update(float DeltaTime)
{
    CMonsterObject::Update(DeltaTime);

    if (mTarget)
    {
        if (mTarget->IsEnable())
        {
            /*FVector3D   ViewDir = mTarget->GetWorldPosition() -
                GetWorldPosition();
            ViewDir.Normalize();

            float Angle = FVector3D::Axis[EAxis::Y].GetAngle(ViewDir);*/
            float Angle = GetWorldPosition().GetViewTargetAngle(
                mTarget->GetWorldPosition());

            SetWorldRotationZ(Angle);
        }
    }

    mFireTime -= DeltaTime;

    if (mFireTime <= 0.f)
    {
        mFireTime += 1.f;

        ++mFireCount;

        CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

        Bullet->SetBulletCollisionProfile("MonsterAttack");

        CSceneComponent* Root = Bullet->GetRootComponent();

        FVector3D Pos = mRoot->GetWorldPosition();
        FVector3D Dir = mRoot->GetAxis(EAxis::Y);

        Root->SetWorldScale(50.f, 50.f);
        Root->SetWorldRotation(mRoot->GetWorldRotation());
        Root->SetWorldPos(Pos + Dir * 75.f);

        Bullet->SetLifeTime(2.f);

        if (mFireCount == 4)
        {
            mFireCount = 0;
            Bullet = mScene->CreateObj<CBulletObject>("Bullet");

            Bullet->SetBulletCollisionProfile("MonsterAttack");

            Root = Bullet->GetRootComponent();

            Pos = mRoot->GetWorldPosition();
            Dir = mRoot->GetAxis(EAxis::Y);

            Root->SetWorldScale(50.f, 50.f);
            Root->SetWorldRotation(mRoot->GetWorldRotation());
            Root->AddWorldRotationZ(-45.f);
            Root->SetWorldPos(Pos + Dir * 75.f);

            Bullet->SetLifeTime(2.f);


            Bullet = mScene->CreateObj<CBulletObject>("Bullet");

            Bullet->SetBulletCollisionProfile("MonsterAttack");

            Root = Bullet->GetRootComponent();

            Pos = mRoot->GetWorldPosition();
            Dir = mRoot->GetAxis(EAxis::Y);

            Root->SetWorldScale(50.f, 50.f);
            Root->SetWorldRotation(mRoot->GetWorldRotation());
            Root->AddWorldRotationZ(45.f);
            Root->SetWorldPos(Pos + Dir * 75.f);

            Bullet->SetLifeTime(2.f);
        }
    }
}

