#pragma once
#include "ItemObject.h"
#include "../Component/ColliderOBB2D.h"
#include "../Asset/Texture/Texture.h"
#include "../Component/SpriteComponent.h"
#include "HitboxObj.h"

class CWeaponObject:
    public CItemObject
{
public:
    CWeaponObject();
    CWeaponObject(const CWeaponObject& Obj);
    CWeaponObject(CWeaponObject&& Obj);
    virtual ~CWeaponObject();

public:
    bool Init() override;
    void Update(float DeltaTime) override;
   
public:
    void SetInfo(const std::string& Name, const TCHAR* FileName, const FVector2D& size);
    void SetTexture(const std::string& Name, const TCHAR* FileName) { mRoot->SetTexture(Name, FileName); } 
    void SetSize(const FVector2D& _size) { mRoot->SetWorldScale(_size); }
    class CSpriteComponent* GetSpriteComponent() { return mRoot; }
};

