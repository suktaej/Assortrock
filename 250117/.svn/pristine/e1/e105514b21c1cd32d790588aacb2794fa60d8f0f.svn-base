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
    virtual ~CPlayerObject();

protected:
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    CSharedPtr<class CSceneComponent>       mRotationPivot;
    CSharedPtr<class CStaticMeshComponent>  mSub;
    CSharedPtr<class CStaticMeshComponent>  mSub2;

    CSharedPtr<class CBulletObject> mSkill1Object;

    bool            mSkill2Enable = false;
    float           mSkill2Time = 3.f;
    float           mSkill2TimeAcc = 0.f;
    float           mSkill2TimeInterval = 0.2f;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);


private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void Fire(float DeltaTime);

    void Skill1(float DeltaTime);
    void Skill1Fire(float DeltaTime);

    void Skill2(float DeltaTime);

    void Skill3(float DeltaTime);


private:
    void UpdateSkill2(float DeltaTime);
};

