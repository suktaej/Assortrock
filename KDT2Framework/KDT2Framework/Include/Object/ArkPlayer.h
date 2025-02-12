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
    CSharedPtr<class CStaticMeshComponent>  mRoot;
    //CSharedPtr<class CStaticMeshComponent>  mSub;
    CSharedPtr<class CColliderAABB2D>       mBody;
    //CSharedPtr<class CColliderLine2D>       mLine;
    CSharedPtr<class CCameraComponent>      mCamera;

    CSharedPtr<class CMovementComponent>    mMovement;
    int mBallCount = 1;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    void SetBallCount() { mBallCount = 1; }

private:
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void Fire(float DeltaTime);
};

