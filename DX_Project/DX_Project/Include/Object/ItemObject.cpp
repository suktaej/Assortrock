#include "ItemObject.h"
#include "../Asset/Texture/Texture.h"
#include "../Component/SpriteComponent.h"

CItemObject::CItemObject()
{
}

CItemObject::CItemObject(const CItemObject& Obj)
{
}

CItemObject::CItemObject(CItemObject&& Obj)
{
}

CItemObject::~CItemObject()
{
}

bool CItemObject::Init()
{
    CSceneObject::Init();
    mRoot = CreateComponent<CSpriteComponent>("Slot");
    SetRootComponent(mRoot);

    return true;
}

void CItemObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}
