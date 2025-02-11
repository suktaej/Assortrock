#pragma once

#include "Component.h"

class CRotationComponent :
    public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CRotationComponent();
	CRotationComponent(const CRotationComponent& Com);
	CRotationComponent(CRotationComponent&& Com);
	virtual ~CRotationComponent();

protected:
	//movement들이 공용으로 사용하는 component를 생성
	//이를 상속받아 사용하도록 공유하는 것을 권장
	//타일맵, 맵에디터 등을 생성할 경우 이동컴포넌트의 공통적 요소가 필요
	CSharedPtr<class CSceneComponent> mUpdateComponent;
protected:
	FVector3D mVelocity;
	FVector3D mRotationStep;
	bool mVelocityInit = true;
public:
	const FVector3D& GetRotationStep() const { return mRotationStep; }
	float GetRotationDistance()	const { return mRotationStep.Length(); }
public:
	void SetUpdateComponent(class CSceneComponent* Target);
public:
	void AddMove(const FVector3D& Rot) { mVelocity += Rot; }
	void AddMoveX(float x) { mVelocity.x += x; }
	void AddMoveY(float y) { mVelocity.y += y; }
	void AddMoveZ(float z) { mVelocity.z += z; }

	void SetMove(const FVector3D& Rot) { mVelocity = Rot; }
	void SetMoveX(float x) { mVelocity.x = x; }
	void SetMoveY(float y) { mVelocity.y = y; }
	void SetMoveZ(float z) { mVelocity.z = z; }

	void SetVelocityInit(bool VelocityInit) { mVelocityInit = VelocityInit; }
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PostRender();
	virtual CRotationComponent* Clone();
};

