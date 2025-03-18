#include "WeaponObject.h"
#include "SwordHitboxObj.h"
#include "../Scene/Scene.h"

CWeaponObject::CWeaponObject()
{
}

CWeaponObject::CWeaponObject(const CWeaponObject& Obj)
{
}

CWeaponObject::CWeaponObject(CWeaponObject&& Obj)
{
}

CWeaponObject::~CWeaponObject()
{
}

bool CWeaponObject::Init()
{
    CItemObject::Init();
      
    SetItemType(EItemType::Weapon);
    
    mData.Name = "Sword";
    mRoot->SetTexture("Sword", TEXT("Texture/Weapon/Sword.png"));
    mRoot->SetWorldScale(19.f, 7.f);

    return true;
}

void CWeaponObject::Update(float DeltaTime)
{
    CItemObject::Update(DeltaTime);
}

void CWeaponObject::SetInfo(const std::string& Name, const TCHAR* FileName, const FVector2D& _size)
{
    mData.Name = Name;
    mRoot->SetTexture(Name, FileName);
    mRoot->SetWorldScale(_size);
}
