#pragma once
#include "SceneObject.h"

class CItemObject abstract:
    public CSceneObject
{
    friend class CScene;

public:
    CItemObject();
    CItemObject(const CItemObject& Obj);
    CItemObject(CItemObject&& Obj);
    virtual ~CItemObject();

protected:
    CSharedPtr<class CSpriteComponent> mRoot;
    FItemData mData;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

protected:
    void SetItemType(EItemType Type) { mData.Type= Type; }
    void SetName(std::string _name) { mData.Name = _name; }
    void SetIcon(class CTexture* texture) { mData.Icon = texture; }

public:
    std::string GetWeaponName() { return mData.Name; }
};
