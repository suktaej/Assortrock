#include "SwordObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderOBB2D.h"
#include "../Scene/Scene.h"

CSwordObject::CSwordObject()
{
}

CSwordObject::CSwordObject(const CWeaponObject& Obj)
{
}

CSwordObject::CSwordObject(CWeaponObject&& Obj)
{
}

CSwordObject::~CSwordObject()
{
}

bool CSwordObject::Init()
{
	CWeaponObject::Init();
    
    mName = "Sword";
   
    mRoot = CreateComponent<CSpriteComponent>("Sword");

    SetRootComponent(mRoot);

    mRoot->SetTexture("Sword", TEXT("Texture/Weapon/Sword.png"));
    //mRoot->SetPivot(0.f, 0.5f);
    //mRoot->SetRelativePos(0.f, 0.f);
    mRoot->SetWorldScale(19.f, 7.f, 1.f);

    return true;
}
