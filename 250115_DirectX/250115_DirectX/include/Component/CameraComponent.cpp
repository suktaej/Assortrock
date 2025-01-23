#include "CameraComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h" 

CCameraComponent::CCameraComponent()
{
}

CCameraComponent::CCameraComponent(const CSceneComponent& Com)
	: CSceneComponent(Com)
{
}

CCameraComponent::CCameraComponent(CSceneComponent&& Com)
	:CSceneComponent(Com)
{
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::SetProjectionType(ECameraProjectionType Type)
{
	mProjType = Type;

	switch (mProjType)
	{
		//원근투영의 경우
	case ECameraProjectionType::Prespective:
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(mViewAngle),
			mWidth / mHeight,
			0.5f,
			mViewDistance);
		break;
		//직교투영의 경우
	case ECameraProjectionType::Ortho:
		//left, right는 0,0을 기준으로 가운데
		//크기의 절반을 -값, +값
		DirectX::XMMatrixOrthographicOffCenterLH(
			mWidth / -2.f,
			mWidth / 2.f,
			mHeight / -2.f,
			mHeight / 2.f,
			0.f,
			mViewDistance);
		break;
	}
}

bool CCameraComponent::Init()
{
	//카메라 메니저가 가지고 있는 뷰타겟이 nullptr일때
	//첫번째 생성되는 카메라 컴포넌트로 viewtarget을 체움
	if (!CSceneComponent::Init())
		return false;

	SetProjectionType(ECameraProjectionType::Prespective);

	if (!m_Scene->GetCameraManager()->GetViewTarget())
		m_Scene->GetCameraManager()->SetViewTarget(this);

	return true;
}

bool CCameraComponent::Init(const char* FileName)
{
	if (!CSceneComponent::Init())
		return false;

	SetProjectionType(ECameraProjectionType::Prespective);

	if (!m_Scene->GetCameraManager()->GetViewTarget())
		m_Scene->GetCameraManager()->SetViewTarget(this);

	return true;
}

void CCameraComponent::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}

void CCameraComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CCameraComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
	//뷰공간 변환이 일어날 경우 카메라는 Z+방향을 바라보게 회전
	//이 때 카메라를 구성하는 3개의 축은 월드의 축과 정확하게 일치
	//카메라 x축 * 뷰 행렬 = 1, 0, 0
	//카메라 y축 * 뷰 행렬 = 0, 1, 0
	//카메라 z축 * 뷰 행렬 = 0, 0, 1
	//카메라 축을 이용해 행렬을 구성하고 뷰 행렬과 곱 연산 시 항등행렬 도출
	//A행렬에 B를 곱했을 때 항등행렬이 나온다면 B는 A의 역행렬
	//직교행렬 : 행렬을 구성하는 각 축이 서로에 90도인 행렬
	//직교행렬은 전치행렬과 역행렬이 같음

	mmatView.Idnetify();

	for (int i = 0;i < (int)EAxis::End;i++)
	{
		FVector3D Axis = mAxis[i];
		memcpy(&mmatView[i][0], &Axis, sizeof(FVector3D));
	}

	mmatView.Transpose();

	for (int i = 0;i < (int)EAxis::End;i++)
		mmatView[3][i] = -1 * mAxis[i].Dot(m_WorldPos);
}

void CCameraComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CCameraComponent::PreRender()
{
	CSceneComponent::PreRender();
}

void CCameraComponent::Render()
{
	CSceneComponent::Render();
}

void CCameraComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSceneComponent* CCameraComponent::Clone()
{
	return nullptr;
}
