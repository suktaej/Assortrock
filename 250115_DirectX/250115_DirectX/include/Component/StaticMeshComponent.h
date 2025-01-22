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
	//��� �� ������Ʈ �������� Ʈ������ ������۰� �ݵ�� �ʿ�
	CSharedPtr<class CStaticMesh> m_Mesh;
	//Ʈ������ ���� �� ������۸� ����ؼ� ���̴��� ����
	//���̴��� �̸� �޾ƿ��� ���ϴ� �޽��� ���
	//� ���̴��� ����� ���� �ʿ�
	CSharedPtr<class CShader> m_Shader;
	//Ʈ������ ������۴� ��� ���� ����
	//�� ������Ʈ�� �׻� ��¿��� �ƴ�
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



