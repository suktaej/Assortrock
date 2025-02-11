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
		// �������Ϳ��� gwp�� �ڽ��� ��ġ�� �ҷ���(Vector3D ��ȯ) 
		// vector3D�Լ� distance�� Ÿ���� ������ǥ�� ���ڷ� ����
		// �� ���� ������ �Ÿ��� ��ȯ����
		float   Distance = GetWorldPosition().Distance(mTarget->GetWorldPosition());

		if (Distance <= mDetectDistance)
		{
			//ȸ������ ����
			float RotAngle = GetWorldPosition().GetViewTargetAngle(mTarget->GetWorldPosition());
		
			//Z�� �������� ������ŭ ȸ��
			SetWorldRotationZ(RotAngle);

			// Ÿ�ٰ��� ������ ����Ѵ�.
			// ���� ���� Y��
			// Ÿ���� �ٶ󺸴� ���⺤�͸� ���Ѵ�.
			FVector3D   View = mTarget->GetWorldPosition() - GetWorldPosition();
			View.Normalize();

			float Angle = GetAxis(EAxis::Y).GetAngle(View);

			if (Angle <= mDetectAngle)
			{
				mAttackTime -= DeltaTime;

				if (mAttackTime <= 0.f)
				{
					mAttackTime += 0.5f;
					//Ÿ���� ���Ϳ�����Ʈ Ŭ�������� �� ������Ʈ�� �����Ǿ� ����
					//���̳��� ĳ��Ʈ�� �ٿ�ĳ����
					CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());
					//Ÿ���� �÷��̾� Ÿ���̶�� ������
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


