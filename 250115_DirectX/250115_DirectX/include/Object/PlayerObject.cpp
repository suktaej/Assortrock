#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"

CPlayerObject::CPlayerObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj) :
    CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj) :
    CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
    CStaticMeshComponent* Root = CreateComponent<CStaticMeshComponent>();

    Root->SetMesh("CenterRect");
    Root->SetShader("ColorMeshShader");

    Root->SetWorldPos(0.f, 0.f, 0.5f);

    SetRootComponent(Root);

	return true;
}
