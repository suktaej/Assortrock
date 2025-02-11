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
    //distance는 이동한 량(거리 = 벡터의 량)
    //현재 프레임의 이동한 거리만큼 감소
    mDistance -= mMovement->GetMoveDistance();
    
    //이동이 완료되면
    if (mDistance <= 0.f)
    {
        mDuration -= DeltaTime;
        //유지시간 종료 시 제거
        if (mDuration <= 0.f)
            Destroy();
        //정지
        mMovement->SetEnable(false);
        
        //씬에 존재하는 CMonsterObject 타입의 객체들을
        //현재 지역함수 내에 선언한 MonsterList로 받아옴
        std::list<CSharedPtr<CMonsterObject>>   MonsterList;
        mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

        auto    iter = MonsterList.begin();
        auto    iterEnd = MonsterList.end();
    
        for (; iter != iterEnd; ++iter)
        {
            //Monster의 위치
            FVector3D Pos = (*iter)->GetWorldPosition();
            //Monster로부터 탄환의 위치까지의 거리
            float Dist = Pos.Distance(GetWorldPosition());

            if (Dist <= mRange)
            {
                FVector3D   MoveDir;

                switch (mGravityType)
                {
                case EGravityType::Pull:
                    //벡터의 뺄셈
                    //탄환의 위치에서 몬스터의 위치를 뺌
                    //탄환의 방향
                    MoveDir = GetWorldPosition() - Pos;
                    break;
                    //몬스터의 위치에서 탄환의 위치를 뺌
                    //몬스터의 방향
                case EGravityType::Push:
                    MoveDir = Pos - GetWorldPosition();
                    break;
                }
                //방향의 단위벡터화
                MoveDir.Normalize();
                //몬스터의 좌표를 이동
                (*iter)->AddWorldPos(MoveDir * mGravitySpeed * DeltaTime);
            }
        }
    }
}


