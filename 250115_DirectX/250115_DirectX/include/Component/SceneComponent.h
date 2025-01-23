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
	CSceneComponent(const CSceneComponent& Com);
	CSceneComponent(CSceneComponent&& Com);
public:
	void AddChild(CSceneComponent* Child);
protected:
	CSceneComponent* m_Parent = nullptr;
	//컴포넌트는 삭제되는 경우가 거의 없음
	//child를 위한 vector 구현
	std::vector<CSharedPtr<CSceneComponent>> m_ChildList;
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

protected:
	//Transform 정보
	//최종적으로 월드 정보를 구현
	//트랜스폼 정보는 상대적인 정보
	//scale값은 0 이상
	FVector3D m_RelativeScale = FVector3D(1.f,1.f,1.f);
	FVector3D m_RelativeRot;
	FVector3D m_RelativePos;
	//월드 정보
	FVector3D m_WorldScale = FVector3D(1.f,1.f,1.f);
	FVector3D m_WorldRot;
	FVector3D m_WorldPos;

	FVector3D mAxis[static_cast<int>(EAxis::End)] =
	{
		FVector3D(1.f, 0.f, 0.f),
		FVector3D(0.f, 1.f, 0.f),
		FVector3D(0.f, 0.f, 1.f)
	};
	
	FMatrix m_MatScale;
	FMatrix m_MatRot;
	FMatrix m_MatTranslate;
	FMatrix m_MatWorld;

public:
	const FMatrix& GetScaleMatrix()	const { return m_MatScale; }
	const FMatrix& GetRotationMatrix()	const { return m_MatRot; }
	const FMatrix& GetTranslateMatrix()	const { return m_MatTranslate; }
	const FMatrix& GetWorldMatrix()	const { return m_MatWorld; }

	const FVector3D& GetAxis(EAxis Axis) const
	{
		return mAxis[static_cast<int>(Axis)];
	}

	const FVector3D& GetRelativeScale()	const { return m_RelativeScale; }
	const FVector3D& GetRelativeRotation()	const { return m_RelativeRot; }
	const FVector3D& GetRelativePosition()	const { return m_RelativePos; }

	const FVector3D& GetWorldScale()	const { return m_WorldScale; }
	const FVector3D& GetWorldRotation()	const { return m_WorldRot; }
	const FVector3D& GetWorldPosition()	const { return m_WorldPos; }
	
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
private:
	void ComputeTransform();
};



