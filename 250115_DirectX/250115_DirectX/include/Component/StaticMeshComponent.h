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
	//Ʈ������ ���� �� ������� ������� ���
	//�̴� ��� ������ ����
	//�� ������Ʈ�� �ݵ�� ��¿��� �ƴϹǷ�

	//� ���̴��� ����� �� ����
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



