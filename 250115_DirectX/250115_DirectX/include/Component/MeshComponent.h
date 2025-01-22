#pragma once
#include "SceneComponent.h"

//Mesh�� ����ϱ� ���� component
class CMeshComponent :
    public CSceneComponent
{
public:
	CMeshComponent();
	CMeshComponent(const CMeshComponent& Com);
	CMeshComponent(CMeshComponent&& Com);
	~CMeshComponent() override;
protected:
	class CTransformCBuffer* m_TransformCBuffer;
public:
	bool Init() override;
	bool Init(const char* FileName) override;

	void PreUpdate(float DeltaTime)override;
	void Update(float DeltaTime)override;
	void PostUpdate(float DeltaTime)override;

	void PreRender()override;
	void Render()override;
	void PostRender()override;

	void Collision(float DeltaTime)override;

	CMeshComponent* Clone()override;
};
