#pragma once

#include "SceneObject.h"

enum class ESkill4State
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
    virtual ~CPlayerObject();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;
    CSharedPtr<class CColliderAABB2D>        mBody;
    CSharedPtr<class CCameraComponent>      mCamera;
    CSharedPtr<class CWidgetComponent>    mHPBar;
    CSharedPtr<class CSceneComponent>       mRotationPivot;
    CSharedPtr<class CMovementComponent>    mMovement;
    CSharedPtr<class CRotationComponent>    mRotation;
    CSharedPtr<class CInventoryComponent>    mInventory;

    CSharedPtr<class CBulletObject> mSkill1Object;

    class CAnimation2D* mAnimation = nullptr;
    bool                mAutoBasePose = true;

    bool            mSkill2Enable = false;
    float           mSkill2Time = 3.f;
    float           mSkill2TimeAcc = 0.f;
    float           mSkill2TimeInterval = 0.2f;

    bool            mSkill4Enable = false;
    float           mSkill4Time = 5.f;
    float           mSkill4TimeAcc = 0.f;
    float           mSkill4ReadyTime = 2.f;
    float           mSkill4MaxRange = 4.f;
    float           mSkill4Range = 100.f;
    float           mSkill4RangeLength = 2.f;
    float           mPivotRotationSpeed = 180.f;
    ESkill4State    mSkill4State = ESkill4State::Expansion;

    int             mHP = 10;
    //0311
    bool mIsOnGround = false;   //바닥 충돌상태
    bool mIsJumping = false;    //도약 상태
    float mJumpingTime = 0.5f;    //도약시간
    //0313
    class CInput* mInput = nullptr;
    
    FVector2D mMousePos;    //마우스 좌표
    float mMouseDeg = 0.f;    //플레이어에서 마우스까지의 각도
    float mSwingDeg = 90.f;     //마우스 방향에서 무기를 수직으로 변경

    FVector3D mWeaponPos;
    FVector3D mWeaponDir;
    FVector3D mWeaponRot;

    //CSharedPtr<class CSwordObject> mSword;  //무기1
    //CSharedPtr<class CBowObject> mBow; //무기2
    //CSharedPtr<class CSpriteComponent>  mWeaponSlot;
    CSharedPtr<class CWeaponObject> mWeaponSlot;

    //FWeaponData mSword;
    //FWeaponData mBow;

    bool mSwap = true;  //무기전환
    
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
    virtual void Damage(int Dmg);
    virtual float Damage(float Attack, CSceneObject* Obj);


private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void MovePoint(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);

    void MoveRight(float DeltaTime);
    void MoveLeft(float DeltaTime);


    void Fire(float DeltaTime);

    void Skill1(float DeltaTime);
    void Skill1Fire(float DeltaTime);

    void Skill2(float DeltaTime);

    void Skill3(float DeltaTime);

    void Skill4(float DeltaTime);

    void Skill5(float DeltaTime);

    void Skill6(float DeltaTime);

    void Skill7(float DeltaTime);

    void Skill8(float DeltaTime);

    void Skill9(float DeltaTime);


//private:
//    void UpdateSkill2(float DeltaTime);
//    void UpdateSkill4(float DeltaTime);

public:
    void AttackEnd();
    void AttackNotify();

private:
    //0311
    //점프 구현
    void Jump(float DeltaTime);
    void JumpUpdate(float DeltaTime);
    //플레이어 충돌
    void CheckBottomCollision(float DeltaTime);
    void CheckWallCollision(float DeltaTime);
    void CheckCeilingCollision(float DeltaTime);
    //0313
    //마우스 좌표 회전
    void FollowMouse(float DeltaTime,const FVector2D& MousePos);
    //화살발사
    void ArrowFire();
    //플레이어 좌우방향
    void CalPlayerDir();
public:
    //무기 슬롯
    void SwapWeapon(float DeltaTime);
};