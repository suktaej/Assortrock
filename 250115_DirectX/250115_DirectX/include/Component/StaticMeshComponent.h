#pragma once
#include "MeshComponent.h"
class CStaticMeshComponent :
	public CMeshComponent
{
public:
	CStaticMeshComponent();
	CStaticMeshComponent(const CStaticMeshComponent& Com);
	CStaticMeshComponent(CStaticMeshComponent&& Com);
	~CStaticMeshComponent() override;
protected:
	CSharedPtr<class CStaticMesh> m_Mesh;
	//트랜스폼 생성 후 상수버퍼 사용이후 출력
	//이는 모든 씬에서 공용
	//씬 컴포넌트가 반드시 출력용은 아니므로

	//어떤 쉐이더를 사용할 지 보유
	CSharedPtr<class CShader> m_Shader;
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
public:
	void SetShader(const std::string& Name);
};



