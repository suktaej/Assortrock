#include "BowObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderOBB2D.h"
#include "../Scene/Scene.h"

CBowObject::CBowObject()
{
}

CBowObject::CBowObject(const CWeaponObject& Obj)
{
}

CBowObject::CBowObject(CWeaponObject&& Obj)
{
}

CBowObject::~CBowObject()
{
}

bool CBowObject::Init()
{
    CWeaponObject::Init();

    mName = "Bow";
    mRoot = CreateComponent<CSpriteComponent>("Bow");

    SetRootComponent(mRoot);

    mRoot->SetTexture("Bow", TEXT("Texture/Weapon/Bow.png"));
    mRoot->SetPivot(0.f, 0.5f);
    mRoot->SetRelativePos(0.f, 0.f);
    mRoot->SetWorldScale(17.f, 13.f, 1.f);

    return true;
}
