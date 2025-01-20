#pragma once
#include "SceneComponent.h"
class CMeshComponent :
    public CSceneComponent
{
public:
	CMeshComponent();
	CMeshComponent(const CMeshComponent& Com);
	CMeshComponent(CMeshComponent&& Com);
	~CMeshComponent() override;
protected:
	class CTransformCBuffer
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);

	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual void Collision(float DeltaTime);

	virtual CSceneComponent* Clone();
};

