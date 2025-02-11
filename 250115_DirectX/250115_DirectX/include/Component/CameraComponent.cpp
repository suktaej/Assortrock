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
		mmatProj = DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(mViewAngle),
			mWidth / mHeight,
			0.5f,
			mViewDistance);
		break;
		//직교투영의 경우
	case ECameraProjectionType::Ortho:
		//left, right는 0,0을 기준으로 가운데
		//크기의 절반을 -값, +값
		//기본 출발값은 좌하단
		mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(
			mWidth / -2.f,
			mWidth / 2.f,
			mHeight / -2.f,
			mHeight / 2.f,
			0.f,
			mViewDistance);
		break;
		/*
		뷰 행렬의 뷰스페이스 변환 시
		카메라의 위치가 100,100,100이라면 이를 0,0,0으로 이동
		이후 함께 모든 오브젝트의 이동을 -100,-100,-100
		이동 행렬은 41,42,43에 값이 존재하므로
		뷰행렬의 41,42,43에 -x, -y, -z가 들어가야 함
		 
		카메라가 +z 방향을 바라보도록 회전
		모든 오브젝트가 카메라를 중심으로 공전
		월드 행렬 = 크기 * 자전 * 공전 * 이동 * 부모

		카메라를 구성하는 축(x,y,z)이 뷰 공간에서는 월드의 축과 일치
		뷰 공간으로 전환한 카메라의 축은 
		카메라 x축 * 뷰 행렬 = 1, 0, 0
		카메라 y축 * 뷰 행렬 = 0, 1, 0
		카메라 z축 * 뷰 행렬 = 0, 0, 1
		*/
	}
}

bool CCameraComponent::Init()
{
	//카메라 메니저가 가지고 있는 뷰타겟이 nullptr일때
	//첫번째 생성되는 카메라 컴포넌트로 viewtarget을 체움
	if (!CSceneComponent::Init())
		return false;

	//초기화 시 투영을 생성
	SetProjectionType(ECameraProjectionType::Prespective);

	if (!mScene->GetCameraManager()->GetViewTarget())
		mScene->GetCameraManager()->SetViewTarget(this);

	return true;
}

bool CCameraComponent::Init(const char* FileName)
{
	if (!CSceneComponent::Init())
		return false;

	SetProjectionType(ECameraProjectionType::Prespective);

	if (!mScene->GetCameraManager()->GetViewTarget())
		mScene->GetCameraManager()->SetViewTarget(this);

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
	/*
	뷰공간 변환이 일어날 경우 카메라는 Z+방향을 바라보게 회전
	이 때 카메라를 구성하는 3개의 축은 월드의 축과 정확하게 일치
	카메라 x축 * 뷰 행렬 = 1, 0, 0
	카메라 y축 * 뷰 행렬 = 0, 1, 0
	카메라 z축 * 뷰 행렬 = 0, 0, 1

	카메라 축을 이용해 행렬을 구성하고 뷰 행렬과 곱 연산 시 항등행렬 도출
	A행렬에 B를 곱했을 때 항등행렬이 나온다면 B는 A의 역행렬

	직교행렬 : 행렬을 구성하는 각 축이 서로에 90도인 행렬
	직교행렬은 전치행렬과 역행렬이 같음

	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1
	카메라의 최종 회전 행렬

	1   0  0 0
	0   1  0 0
	0   0  1 0
	-x -y -z 1
	카메라의 이동행렬

	1   0  0 0   Xx Yx Zx 0   Xx   Yx   Zx   0
	0   1  0 0 * Xy Yy Zy 0 = Xy   Yy   Zy   0
	0   0  1 0   Xz Yz Zz 0   Xz   Yz   Zz   0
	-x -y -z 1   0  0  0  1   -X.P -Y.P -Z.P 1 (P:내적)
	최종 뷰 행렬
	*/
	
	//항등행렬 생성
	mmatView.Idnetify();

	for (int i = 0;i < (int)EAxis::End;i++)
	{
		//메모리가 연속적으로 들어가 있으므로 i번째를 메모리카피
		FVector3D Axis = mAxis[i];
		memcpy(&mmatView[i][0], &Axis, sizeof(FVector3D));
	}
	/*
	생성한 행렬을 전치
	Xx Xy Xz 0		Xx Yx Zx 0
	Yx Yy Yz 0	＞　Xy Yy Zy 0
	Zx Zy Zz 0		Xz Yz Zz 0
	0  0  0  1		0  0  0  1
	*/
	mmatView.Transpose();

	/*
	4 째줄 내적값 삽입
	Xx   Yx   Zx   0
	Xy   Yy   Zy   0
	Xz   Yz   Zz   0
	-X.P -Y.P -Z.P 1

	최종 뷰 행렬 생성
	*/
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
