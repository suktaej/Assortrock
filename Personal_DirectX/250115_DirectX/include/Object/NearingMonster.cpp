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
		// Ÿ�ٰ��� �Ÿ��� ���Ѵ�.
		float   Distance = GetWorldPosition().Distance(mTarget->GetWorldPosition());

		if (Distance <= mDetectDistance)
		{
			float RotAngle = GetWorldPosition().GetViewTargetAngle(
				mTarget->GetWorldPosition());

			SetWorldRotationZ(RotAngle);

			// Ÿ�ٰ��� ������ ����Ѵ�.
			// Ÿ���� �ٶ󺸴� ���⺤�͸� ���Ѵ�.
			FVector3D   View = mTarget->GetWorldPosition() -
				GetWorldPosition();
			View.Normalize();

			float Angle = GetAxis(EAxis::Y).GetAngle(View);

			if (Angle <= mDetectAngle)
			{
				mAttackTime -= DeltaTime;

				//if (mAttackTime <= 0.f)
				//{
				//	mAttackTime += 0.5f;

				//	CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());

				//	if (Player)
				//	{
				//	    Player->Damage(1);
				//	}
				//}
			}
			else
				mAttackTime = 0.5f;
		}
		else
			mAttackTime = 0.5f;
	}
}


