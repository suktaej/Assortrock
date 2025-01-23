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
public:
    bool Init() override;
private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void RotationZ(float DeltaTime);
    void RotationZInv(float DeltaTime);
};

