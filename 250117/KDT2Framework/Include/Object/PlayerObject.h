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
    CSharedPtr<class CStaticMeshComponent> mRoot;
    CSharedPtr<class CStaticMeshComponent> mSub;
public:
    virtual bool Init();


private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);

    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);
};

