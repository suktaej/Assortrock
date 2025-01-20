#pragma once
#include "Component.h"
class CSceneComponent :
	public CComponent
{
	friend class CScene;
	friend class CSceneObject;
protected:
	CSceneComponent();
	virtual ~CSceneComponent();
	CSceneComponent(const CSceneComponent& Com) {}
	CSceneComponent(CSceneComponent&& Com) {}
protected:
	CSceneComponent* m_Parent = nullptr;
	//컴포넌트는 삭제되는 경우가 거의 없음
	//vector 구현
	std::vector<CSharedPtr<CSceneComponent>> m_ChildList;
	//Transform 정보
	//최종적으로 월드 정보를 구현
	//트랜스폼 정보는 상대적인 정보
	FVector3D m_RelativeScale;
	FVector3D m_RelativeRot;
	FVector3D m_RelativePos;
	//월드 정보
	FVector3D m_WorldScale;
	FVector3D m_WorldRot;
	FVector3D m_WorldPos;
	
	FMatrix m_MatScale;
	FMatrix m_MatRot;
	FMatrix m_MatTranslate;
	FMatrix m_MatWorld;
public:
	void AddChild(CSceneComponent* Child);
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);

	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual void Collision(float DeltaTime);

	virtual CSceneComponent* Clone();
public:
	void SetRelativeScale(const FVector3D& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScale(const FVector2D& Scale);
	void SetRelativeScale(float x, float y);

	void SetRelativeRotation(const FVector3D& Rot);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotation(const FVector2D& Rot);
	void SetRelativeRotation(float x, float y);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativeRotationAxis(float Angle, const FVector3D& Axis);

	void SetRelativePos(const FVector3D& Pos);
	void SetRelativePos(float x, float y, float z);
	void SetRelativePos(const FVector2D& Pos);
	void SetRelativePos(float x, float y);
	
	void SetWorldScale(const FVector3D& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(const FVector2D& Scale);
	void SetWorldScale(float x, float y);

	void SetWorldRotation(const FVector3D& Rot);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(const FVector2D& Rot);
	void SetWorldRotation(float x, float y);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldRotationAxis(float Angle, const FVector3D& Axis);

	void SetWorldPos(const FVector3D& Pos);
	void SetWorldPos(float x, float y, float z);
	void SetWorldPos(const FVector2D& Pos);
	void SetWorldPos(float x, float y);
};



