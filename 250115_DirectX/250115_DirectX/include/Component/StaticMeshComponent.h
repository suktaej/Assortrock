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
	//모든 씬 컴포넌트 종류들은 트랜스폼 상수버퍼가 반드시 필요
	CSharedPtr<class CStaticMesh> m_Mesh;
	//트랜스폼 생성 후 상수버퍼를 사용해서 쉐이더로 전달
	//쉐이더가 이를 받아오고 원하는 메쉬에 출력
	//어떤 쉐이더를 사용할 지도 필요
	CSharedPtr<class CShader> m_Shader;
	//트랜스폼 상수버퍼는 모든 씬에 공용
	//씬 컴포넌트가 항상 출력용이 아님
public:
	bool Init() override;
	bool Init(const char* FileName) override;

	void PreUpdate(float DeltaTime) override;
	void Update(float DeltaTime) override;
	void PostUpdate(float DeltaTime) override;

	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void Collision(float DeltaTime) override;

	CStaticMeshComponent* Clone() override;
public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);
	void SetMesh(const std::string& Name);
	void SetMesh(class CMesh* Mesh);
};



