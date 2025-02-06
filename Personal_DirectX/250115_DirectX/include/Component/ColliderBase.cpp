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
    // 충돌상태 ON
    mCollision = true;

    // 충돌 시작 시 호출해야 할 함수가 있을 경우 호출해준다.
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

    //Object에서 Init을 호출하게 되면 Component를 생성
    //이후 속해있는 Scene과 Owner Object정보가 지정
    //Scene의 mCollision변수를 반환받아옴
    //자기 자신을 콜리전에 추가
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
    //OBB는 회전을 적용시킬 수 있어야 함
    if (mEnableRotation)
        //회전행렬 생성
        matRot.Rotation(m_WorldRot);

    matScale.Scaling(m_WorldScale);
    matTranslate.Translation(m_WorldPos);
    //mEnableRotation이 false일 경우 항등행렬이 유지
    //곱 연산을 하더라도 현재값이 도출
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
