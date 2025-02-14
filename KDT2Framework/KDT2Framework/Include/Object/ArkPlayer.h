#include "SceneObject.h"

class CArkPlayer: 
    public CSceneObject
{
    friend class CScene;

protected:
    CArkPlayer();
    CArkPlayer(const CArkPlayer& Obj);
    CArkPlayer(CArkPlayer&& Obj);
    virtual ~CArkPlayer();

protected:
    CSharedPtr<class CSpriteComponent>  mRoot;
    CSharedPtr<class CColliderOBB2D>       mBody;
    CSharedPtr<class CCameraComponent>      mCamera;
    CSharedPtr<class CMovementComponent>    mMovement;
    int mBallCount = 1;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    void SetMoveStop();
    void SetMoveStart();

private:
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void Fire(float DeltaTime);
    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);
    void MoveDown(float DeltaTime);
    void MoveUp(float DeltaTime);
};

