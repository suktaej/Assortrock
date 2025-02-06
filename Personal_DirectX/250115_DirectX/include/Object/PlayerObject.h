#pragma once
#include "SceneObject.h"

enum class ESkillState
{
    Expansion,
    Maintain,
    Reduction
};

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
    CSharedPtr<class CColliderAABB2D> mBody;
    CSharedPtr<class CStaticMeshComponent> mSub;
    CSharedPtr<class CSceneComponent> mRotationPivot;
    CSharedPtr<class CCameraComponent> mCamera;

    CSharedPtr<class CMovementComponent> mMovement;
    CSharedPtr<class CRotationComponent> mRotation;

    CSharedPtr<class CBulletObject> mSkill1Object;
private:
    float m_PlayerX = 100.f;
    float m_PlayerY = 100.f;
protected:
    float mPivotRotationSpeed = 180.f;
    
    float mSkill1Scale = 1.f;
   
    bool mSkill2Enable = false;
    float mSkill2Time = 3.f;
    float mSkill2TimeAcc = 0.f;
    float mSkill2TimeInterval = 0.2f;

    bool mSkill4Enable = false;
    float mSkill4Time = 3.f;
    float mSkill4TimeAcc = 0.f;
    float mSkill4ReadyTime = 2.f;
    float mSkill4MaxRange = 400.f;
    //직교투영으로 변하며 거리를 수정
    float mSkill4Range = 150.f;
    float mSkill4RangeLength = 200.f;
    ESkillState mSkill4State = ESkillState::Expansion;

    int mHP = 5;
public:
    virtual void Damage(int Dmg);
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
    void Skill4(float DeltaTime);
    void UpdateSkill4(float DeltaTime);
    void Skill5(float DeltaTime);
    void Skill6(float DeltaTime);
    void Skill7(float DeltaTime);
};

