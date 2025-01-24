#pragma once
#include "../Share/Object.h"
class CSceneObject :
    public CObject
{	//������Ʈ�� ���� ��ġ�� ����
    friend class CScene;
protected:
    CSceneObject();
    ~CSceneObject() override;
    //�� ������Ʈ�� �����ؼ� ����� ���� ����
	CSceneObject(const CSceneObject& Obj);
	CSceneObject(CSceneObject&& Obj);
protected:
	//��� ������Ʈ�� ������ ���Ե� ���� �˰� �־�� ��
	class CScene* mScene = nullptr;
	//�� ������Ʈ�� �̸�����
	std::string mName;
	//���������� ���� ��Ʈ ������Ʈ�� Ȯ���ϱ� ���� �ڷ�
	//�ڽ� ������ ���ÿ� �̵��� �� �ֵ���
	CSharedPtr<class CSceneComponent> mRootComponent;
	float mLifeTime = 0;
public:
	//���� �� ���� ��ȯ�ϱ� ����
	class CScene* GetScene() const { return mScene; }
	//c_str() : std::string Ÿ���� ���ڿ� ������ ��ȯ
	const char* GetName() { return mName.c_str(); }
	void SetName(const std::string& Name) { mName = Name; }
	void SetLifeTime(float Time) { mLifeTime = Time; }
public:
	void SetRootComponent(class CSceneComponent* Root);
	class CSceneComponent* GetRootComponent() { return mRootComponent; }
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
public:
	template <typename T>
	T* CreateComponent()
	{
		T* Component = new T;
		
		Component->m_Scene = mScene;
		Component->m_OwnerObject = this;

		if (!Component->Init())
		{
			SAFE_DELETE(Component);
			return nullptr;
		}

		return Component;
	};
};

