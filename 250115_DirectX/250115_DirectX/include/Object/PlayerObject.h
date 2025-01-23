#pragma once
#include "SceneObject.h"
class CPlayerObject :
    public CSceneObject
{
    friend class CScene;
protected:
    CPlayerObject();
    CPlayerObject(const CPlayerObject& Obj);
    CPlayerObject(CPlayerObject&& Obj);
    ~CPlayerObject() override;
protected:
    CSharedPtr<class CStaticMeshComponent> mRoot;
    CSharedPtr<class CStaticMeshComponent> mSub;
    CSharedPtr<class CSceneComponent> mRotationPivot;

    CSharedPtr<class CBulletObject> mSkill1Object;
protected:
    float mSkill1Scale = 1.f;
    float mPivotRotationSpeed = 180.f;
public:
    bool Init() override;
    void Update(float DeltaTime) override;
private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void Fire(float DeltaTime);
    void Skill1(float DeltaTime);
    void Skill1Fire(float DeltaTime);
};

