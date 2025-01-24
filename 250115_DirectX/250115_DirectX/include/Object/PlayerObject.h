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
    float mPivotRotationSpeed = 180.f;
    
    float mSkill1Scale = 1.f;
   
    bool mSkill2Enable = false;
    float mSkill2Time = 3.f;
    float mSkill2TimeAcc = 0.f;
    float mSkill2TimeInterval = 0.2f;

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

    void Skill2(float DeltaTime);
    void UpdateSkill2(float DeltaTime);
    
    void Skill3(float DeltaTime);
};

