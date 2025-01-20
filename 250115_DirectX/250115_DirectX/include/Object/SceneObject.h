#pragma once
#include "../Share/Object.h"
class CSceneObject :
    public CObject
{
    friend class CScene;
protected:
    CSceneObject();
    virtual ~CSceneObject();
    //�� ������Ʈ�� �����ؼ� ����� ���� ����
    CSceneObject(const CSceneObject& Obj) {}
    CSceneObject(CSceneObject&& Obj) {}
protected:
	//��� ������Ʈ�� ������ ���Ե� ���� �˰� �־�� ��
	class CScene* m_Scene = nullptr;
	//�� ������Ʈ�� �̸�����
	std::string m_Name;
	//���������� ���� ��Ʈ ������Ʈ�� Ȯ���ϱ� ���� �ڷ�
	//�ڽ� ������ ���ÿ� �̵��� �� �ֵ���
	CSharedPtr<class CSceneComponent> m_RootComponent;
public:
	//���� �� ���� ��ȯ�ϱ� ����
	class CScene* GetScene() const { return m_Scene; }
	//c_str() : std::string Ÿ���� ���ڿ� ������ ��ȯ
	const char* GetName() { return m_Name.c_str(); }
	void SetName(const std::string& Name) { m_Name = Name; }
public:
	void SetRootComponent(class CSceneComponent* Root);
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
	virtual CSceneObject* Clone();
};

