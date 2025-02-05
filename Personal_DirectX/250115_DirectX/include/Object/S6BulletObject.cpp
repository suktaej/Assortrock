#include "S6BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "MonsterObject.h"
#include "../Scene/Scene.h"

CS6BulletObject::CS6BulletObject()
{
}

CS6BulletObject::CS6BulletObject(const CS6BulletObject& Obj) :
    CSceneObject(Obj)
{
}

CS6BulletObject::CS6BulletObject(CS6BulletObject&& Obj) :
    CSceneObject(Obj)
{
}

CS6BulletObject::~CS6BulletObject()
{
}

bool CS6BulletObject::Init()
{
    mRoot = CreateComponent<CStaticMeshComponent>();
    mMovement = CreateComponent<CMovementComponent>();

    mRoot->SetMesh("BulletRect");
    mRoot->SetShader("ColorMeshShader");

    mRoot->SetWorldScale(50.f, 50.f, 1.f);

    SetRootComponent(mRoot);

    mMovement->SetUpdateComponent(mRoot);

    mMovement->SetMoveAxis(EAxis::Y);
    mMovement->SetMoveSpeed(500.f);

    return true;
}

void CS6BulletObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
    //distance�� �̵��� ��(�Ÿ� = ������ ��)
    //���� �������� �̵��� �Ÿ���ŭ ����
    mDistance -= mMovement->GetMoveDistance();
    
    //�̵��� �Ϸ�Ǹ�
    if (mDistance <= 0.f)
    {
        mDuration -= DeltaTime;
        //�����ð� ���� �� ����
        if (mDuration <= 0.f)
            Destroy();
        //����
        mMovement->SetEnable(false);
        
        //���� �����ϴ� CMonsterObject Ÿ���� ��ü����
        //���� �����Լ� ���� ������ MonsterList�� �޾ƿ�
        std::list<CSharedPtr<CMonsterObject>>   MonsterList;
        mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

        auto    iter = MonsterList.begin();
        auto    iterEnd = MonsterList.end();
    
        for (; iter != iterEnd; ++iter)
        {
            //Monster�� ��ġ
            FVector3D Pos = (*iter)->GetWorldPosition();
            //Monster�κ��� źȯ�� ��ġ������ �Ÿ�
            float Dist = Pos.Distance(GetWorldPosition());

            if (Dist <= mRange)
            {
                FVector3D   MoveDir;

                switch (mGravityType)
                {
                case EGravityType::Pull:
                    //������ ����
                    //źȯ�� ��ġ���� ������ ��ġ�� ��
                    //źȯ�� ����
                    MoveDir = GetWorldPosition() - Pos;
                    break;
                    //������ ��ġ���� źȯ�� ��ġ�� ��
                    //������ ����
                case EGravityType::Push:
                    MoveDir = Pos - GetWorldPosition();
                    break;
                }
                //������ ��������ȭ
                MoveDir.Normalize();
                //������ ��ǥ�� �̵�
                (*iter)->AddWorldPos(MoveDir * mGravitySpeed * DeltaTime);
            }
        }
    }
}


