#include "ColliderBase.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneCollision.h"
#include "../ProfileManager.h"
#include "../Shader/ColliderCBuffer.h"
#include "../Shader/TransformCBuffer.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Scene/CameraManager.h"
#include "../Asset/Mesh/Mesh.h"

CColliderBase::CColliderBase()
{
}

CColliderBase::CColliderBase(const CColliderBase& Com) :
    CSceneComponent(Com)
{
}

CColliderBase::CColliderBase(CColliderBase&& Com) :
    CSceneComponent(Com)
{
}

CColliderBase::~CColliderBase()
{
#ifdef _DEBUG

    SAFE_DELETE(mTransformCBuffer);
    SAFE_DELETE(mCBuffer);

#endif // _DEBUG
}

void CColliderBase::SetCollisionProfile(const std::string& Name)
{
    mProfile = CProfileManager::GetInst()->FindProfile(Name);
}

void CColliderBase::CallCollisionBegin(const FVector3D& HitPoint,
    CColliderBase* Dest)
{
    // �浹���� ON
    mCollision = true;

    // �浹 ���� �� ȣ���ؾ� �� �Լ��� ���� ��� ȣ�����ش�.
    if (mCollisionBeginFunc)
        mCollisionBeginFunc(HitPoint, Dest);
}

void CColliderBase::CallCollisionEnd(CColliderBase* Dest)
{
    if (mCollisionEndFunc)
        mCollisionEndFunc(Dest);
}

bool CColliderBase::Init()
{
    if (!CSceneComponent::Init())
        return false;

    SetCollisionProfile("Default");

#ifdef _DEBUG

    mShader = CShaderManager::GetInst()->FindShader("FrameMeshShader");

    mCBuffer = new CColliderCBuffer;

    mCBuffer->Init();

    mTransformCBuffer = new CTransformCBuffer;

    mTransformCBuffer->Init();

#endif // _DEBUG

    //Object���� Init�� ȣ���ϰ� �Ǹ� Component�� ����
    //���� �����ִ� Scene�� Owner Object������ ����
    //Scene�� mCollision������ ��ȯ�޾ƿ�
    //�ڱ� �ڽ��� �ݸ����� �߰�
    mScene->GetCollision()->AddCollider(this);

    return true;
}

bool CColliderBase::Init(const char* FileName)
{
    if (!CSceneComponent::Init(FileName))
        return false;

    SetCollisionProfile("Default");

#ifdef _DEBUG

    mShader = CShaderManager::GetInst()->FindShader("FrameMeshShader");

    mCBuffer = new CColliderCBuffer;

    mCBuffer->Init();

    mTransformCBuffer = new CTransformCBuffer;

    mTransformCBuffer->Init();

#endif // _DEBUG

    mScene->GetCollision()->AddCollider(this);

    return true;
}

void CColliderBase::PreUpdate(float DeltaTime)
{
    CSceneComponent::PreUpdate(DeltaTime);
}

void CColliderBase::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CColliderBase::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CColliderBase::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CColliderBase::PreRender()
{
    CSceneComponent::PreRender();
}

void CColliderBase::Render()
{
    CSceneComponent::Render();

#ifdef _DEBUG

    FMatrix matRot, matScale, matTranslate, matWorld;
    //OBB�� ȸ���� �����ų �� �־�� ��
    if (mEnableRotation)
        //ȸ����� ����
        matRot.Rotation(m_WorldRot);

    matScale.Scaling(m_WorldScale);
    matTranslate.Translation(m_WorldPos);
    //mEnableRotation�� false�� ��� �׵������ ����
    //�� ������ �ϴ��� ���簪�� ����
    matWorld = matScale * matTranslate * matRot;

    mTransformCBuffer->SetWorldMatrix(matWorld);
    mTransformCBuffer->SetViewMatrix(mScene->GetCameraManager()->GetViewMatrix());
    mTransformCBuffer->SetProjMatrix(mScene->GetCameraManager()->GetProjMatrix());

    mTransformCBuffer->UpdateBuffer();

    if (mCollision)
        mCBuffer->SetColor(1.f, 0.f, 0.f, 1.f);

    else
        mCBuffer->SetColor(0.f, 1.f, 0.f, 1.f);

    mCBuffer->UpdateBuffer();

    mShader->SetShader();

    mMesh->Render();

#endif // _DEBUG

    mCollision = false;

}

void CColliderBase::PostRender()
{
    CSceneComponent::PostRender();
}

CColliderBase* CColliderBase::Clone()
{
    return nullptr;
}
