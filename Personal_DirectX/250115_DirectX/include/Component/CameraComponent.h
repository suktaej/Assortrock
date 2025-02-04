#pragma once
#include "SceneComponent.h"

enum class ECameraProjectionType
{
	Prespective,
	Ortho
};

class CCameraComponent :
    public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;
protected:
	CCameraComponent();
	CCameraComponent(const CSceneComponent& Com);
	CCameraComponent(CSceneComponent&& Com);
	~CCameraComponent() override;
protected:
	ECameraProjectionType mProjType = ECameraProjectionType::Prespective;
	FMatrix mmatView;	//뷰 행렬
	FMatrix mmatProj;	//투영

	//카메라의 기본 값
	float mViewAngle = 90.f;
	float mWidth = 1280.f;
	float mHeight = 720.f;
	float mViewDistance = 1000.f;
public:
	void SetProjectionType(ECameraProjectionType Type);
public:
	void SetViewAngle(float Angle) { mViewAngle = Angle; }
	void SetViewResolution(float Width, float Height) { mWidth = Width;mHeight = Height; }
	void SetViewDistance(float Dist) { mViewDistance = Dist; }
	const FMatrix& GetViewMatrix() const { return mmatView; }
	const FMatrix& GetProjMatrix() const { return mmatProj; }
public:
	bool Init() override;
	bool Init(const char* FileName) override;
	void PreUpdate(float DeltaTime) override;
	void Update(float DeltaTime) override;
	void PostUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	CSceneComponent* Clone() override;
};

