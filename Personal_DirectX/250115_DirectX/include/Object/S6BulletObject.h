#pragma once
#include "SceneObject.h"

enum class EGravityType
{
    Pull,
    Push
};

class CS6BulletObject :
    public CSceneObject
{
    friend class CScene;

protected:
    CS6BulletObject();
    CS6BulletObject(const CS6BulletObject& Obj);
    CS6BulletObject(CS6BulletObject&& Obj);
    virtual ~CS6BulletObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    //update ���� movement�� �� ������ ȣ��
    //������ ���� �̵��� ���� ��
    //�̵��� ���� ��ȯ���� �ʿ䰡 ���� 
    CSharedPtr<class CMovementComponent>    mMovement;
    EGravityType       mGravityType = EGravityType::Pull;

    float   mSpeed = 400.f;
    float   mDistance = 150.f;
    float   mRange = 500.f;
    float   mDuration = 1.f;
    float   mGravitySpeed = 400.f;

public:
    void SetSpeed(float Speed) { mSpeed = Speed; }
    void SetGravityType(EGravityType Type) { mGravityType = Type; }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

