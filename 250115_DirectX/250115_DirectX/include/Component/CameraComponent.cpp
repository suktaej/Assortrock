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
		//���������� ���
	case ECameraProjectionType::Prespective:
		mmatProj = DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(mViewAngle),
			mWidth / mHeight,
			0.5f,
			mViewDistance);
		break;
		//���������� ���
	case ECameraProjectionType::Ortho:
		//left, right�� 0,0�� �������� ���
		//ũ���� ������ -��, +��
		//�⺻ ��߰��� ���ϴ�
		mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(
			mWidth / -2.f,
			mWidth / 2.f,
			mHeight / -2.f,
			mHeight / 2.f,
			0.f,
			mViewDistance);
		break;
		/*
		�� ����� �佺���̽� ��ȯ ��
		ī�޶��� ��ġ�� 100,100,100�̶�� �̸� 0,0,0���� �̵�
		���� �Բ� ��� ������Ʈ�� �̵��� -100,-100,-100
		�̵� ����� 41,42,43�� ���� �����ϹǷ�
		������� 41,42,43�� -x, -y, -z�� ���� ��
		 
		ī�޶� +z ������ �ٶ󺸵��� ȸ��
		��� ������Ʈ�� ī�޶� �߽����� ����
		���� ��� = ũ�� * ���� * ���� * �̵� * �θ�

		ī�޶� �����ϴ� ��(x,y,z)�� �� ���������� ������ ��� ��ġ
		�� �������� ��ȯ�� ī�޶��� ���� 
		ī�޶� x�� * �� ��� = 1, 0, 0
		ī�޶� y�� * �� ��� = 0, 1, 0
		ī�޶� z�� * �� ��� = 0, 0, 1
		*/
	}
}

bool CCameraComponent::Init()
{
	//ī�޶� �޴����� ������ �ִ� ��Ÿ���� nullptr�϶�
	//ù��° �����Ǵ� ī�޶� ������Ʈ�� viewtarget�� ü��
	if (!CSceneComponent::Init())
		return false;

	//�ʱ�ȭ �� ������ ����
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
	����� ��ȯ�� �Ͼ ��� ī�޶�� Z+������ �ٶ󺸰� ȸ��
	�� �� ī�޶� �����ϴ� 3���� ���� ������ ��� ��Ȯ�ϰ� ��ġ
	ī�޶� x�� * �� ��� = 1, 0, 0
	ī�޶� y�� * �� ��� = 0, 1, 0
	ī�޶� z�� * �� ��� = 0, 0, 1

	ī�޶� ���� �̿��� ����� �����ϰ� �� ��İ� �� ���� �� �׵���� ����
	A��Ŀ� B�� ������ �� �׵������ ���´ٸ� B�� A�� �����

	������� : ����� �����ϴ� �� ���� ���ο� 90���� ���
	��������� ��ġ��İ� ������� ����

	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1
	ī�޶��� ���� ȸ�� ���

	1   0  0 0
	0   1  0 0
	0   0  1 0
	-x -y -z 1
	ī�޶��� �̵����

	1   0  0 0   Xx Yx Zx 0   Xx   Yx   Zx   0
	0   1  0 0 * Xy Yy Zy 0 = Xy   Yy   Zy   0
	0   0  1 0   Xz Yz Zz 0   Xz   Yz   Zz   0
	-x -y -z 1   0  0  0  1   -X.P -Y.P -Z.P 1 (P:����)
	���� �� ���
	*/
	
	//�׵���� ����
	mmatView.Idnetify();

	for (int i = 0;i < (int)EAxis::End;i++)
	{
		//�޸𸮰� ���������� �� �����Ƿ� i��°�� �޸�ī��
		FVector3D Axis = mAxis[i];
		memcpy(&mmatView[i][0], &Axis, sizeof(FVector3D));
	}
	/*
	������ ����� ��ġ
	Xx Xy Xz 0		Xx Yx Zx 0
	Yx Yy Yz 0	����Xy Yy Zy 0
	Zx Zy Zz 0		Xz Yz Zz 0
	0  0  0  1		0  0  0  1
	*/
	mmatView.Transpose();

	/*
	4 °�� ������ ����
	Xx   Yx   Zx   0
	Xy   Yy   Zy   0
	Xz   Yz   Zz   0
	-X.P -Y.P -Z.P 1

	���� �� ��� ����
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
