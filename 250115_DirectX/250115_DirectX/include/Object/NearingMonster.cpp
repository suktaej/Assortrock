#include "NearingMonster.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "PlayerObject.h"

CNearingMonster::CNearingMonster()
{
}

CNearingMonster::CNearingMonster(const CNearingMonster& Obj) :
	CMonsterObject(Obj)
{
}

CNearingMonster::CNearingMonster(CNearingMonster&& Obj) :
	CMonsterObject(Obj)
{
}

CNearingMonster::~CNearingMonster()
{
}

bool CNearingMonster::Init()
{
	CMonsterObject::Init();
	mDetectDistance = 400.f;

	return true;
}

void CNearingMonster::Update(float DeltaTime)
{
	CMonsterObject::Update(DeltaTime);

	if (mTarget)
	{
		// 타겟과의 거리를 구한다.
		// 근접몬스터에서 gwp로 자신의 위치를 불러옴(Vector3D 반환) 
		// vector3D함수 distance에 타겟의 월드좌표를 인자로 전달
		// 두 벡터 사이의 거리를 반환받음
		float   Distance = GetWorldPosition().Distance(mTarget->GetWorldPosition());

		if (Distance <= mDetectDistance)
		{
			//회전각도 도출
			float RotAngle = GetWorldPosition().GetViewTargetAngle(mTarget->GetWorldPosition());
		
			//Z축 기준으로 각도만큼 회전
			SetWorldRotationZ(RotAngle);

			// 타겟과의 각도를 계산한다.
			// 기준 축은 Y축
			// 타겟을 바라보는 방향벡터를 구한다.
			FVector3D   View = mTarget->GetWorldPosition() - GetWorldPosition();
			View.Normalize();

			float Angle = GetAxis(EAxis::Y).GetAngle(View);

			if (Angle <= mDetectAngle)
			{
				mAttackTime -= DeltaTime;

				if (mAttackTime <= 0.f)
				{
					mAttackTime += 0.5f;
					//타겟이 몬스터오브젝트 클래스에서 씬 오브젝트로 생성되어 있음
					//다이나믹 캐스트로 다운캐스팅
					CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());
					//타겟이 플레이어 타입이라면 데미지
					if (Player)
					    Player->Damage(1);
				}
			}
			else
				mAttackTime = 1.f;
		}
		else
			mAttackTime = 1.f;
	}
}


