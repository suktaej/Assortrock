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
	//���������� ���� ��Ʈ ������Ʈ�� Ȯ���ϱ� ���� ���� 
	CSharedPtr<class CSceneComponent> mRootComponent;
	//�� ������Ʈ�� �ƴ� ������Ʈ ���
	//�θ��ڽ��� ������ �ʿ� ����
	std::vector<CSharedPtr<class CComponent>> mNonComponentList;

	float mLifeTime = 0.f;
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
		
		Component->mScene = mScene;
		Component->m_OwnerObject = this;

		if (!Component->Init())
		{
			SAFE_DELETE(Component);
			return nullptr;
		}
		
		//������ ������Ʈ�� �� ������Ʈ���� Ȯ��
		class CSceneComponent* Com = dynamic_cast<CSceneComponent*>(Component);
		//�� ������Ʈ�� �ƴ� ��� mComponentList�� ����
		if (!Com)
			mNonComponentList.emplace_back(Component);

		return Component;
	};

public:
	const FMatrix& GetScaleMatrix()	const;
	const FMatrix& GetRotationMatrix()	const;
	const FMatrix& GetTranslateMatrix()	const;
	const FMatrix& GetWorldMatrix()	const;
	const FVector3D& GetAxis(EAxis Axis) const;

	const FVector3D& GetRelativeScale()	const;
	const FVector3D& GetRelativeRotation()	const;
	const FVector3D& GetRelativePosition()	const;
	const FVector3D& GetWorldScale()	const;
	const FVector3D& GetWorldRotation()	const;
	const FVector3D& GetWorldPosition()	const;

	void SetRelativeScale(const FVector3D& Scale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeScale(const FVector2D& Scale);
	void SetRelativeScale(float x, float y);

	void SetRelativeRotation(const FVector3D& Rot);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotation(const FVector2D& Rot);
	void SetRelativeRotation(float x, float y);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativeRotationAxis(float Angle, const FVector3D& Axis);

	void SetRelativePos(const FVector3D& Pos);
	void SetRelativePos(float x, float y, float z);
	void SetRelativePos(const FVector2D& Pos);
	void SetRelativePos(float x, float y);

	void SetWorldScale(const FVector3D& Scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(const FVector2D& Scale);
	void SetWorldScale(float x, float y);

	void SetWorldRotation(const FVector3D& Rot);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(const FVector2D& Rot);
	void SetWorldRotation(float x, float y);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldRotationAxis(float Angle, const FVector3D& Axis);

	void SetWorldPos(const FVector3D& Pos);
	void SetWorldPos(float x, float y, float z);
	void SetWorldPos(const FVector2D& Pos);
	void SetWorldPos(float x, float y);

public:
	void AddRelativeScale(const FVector3D& Scale);
	void AddRelativeScale(float x, float y, float z);
	void AddRelativeScale(const FVector2D& Scale);
	void AddRelativeScale(float x, float y);

	void AddRelativeRotation(const FVector3D& Rot);
	void AddRelativeRotation(float x, float y, float z);
	void AddRelativeRotation(const FVector2D& Rot);
	void AddRelativeRotation(float x, float y);
	void AddRelativeRotationX(float x);
	void AddRelativeRotationY(float y);
	void AddRelativeRotationZ(float z);

	void AddRelativePos(const FVector3D& Pos);
	void AddRelativePos(float x, float y, float z);
	void AddRelativePos(const FVector2D& Pos);
	void AddRelativePos(float x, float y);

	void AddWorldScale(const FVector3D& Scale);
	void AddWorldScale(float x, float y, float z);
	void AddWorldScale(const FVector2D& Scale);
	void AddWorldScale(float x, float y);

	void AddWorldRotation(const FVector3D& Rot);
	void AddWorldRotation(float x, float y, float z);
	void AddWorldRotation(const FVector2D& Rot);
	void AddWorldRotation(float x, float y);
	void AddWorldRotationX(float x);
	void AddWorldRotationY(float y);
	void AddWorldRotationZ(float z);

	void AddWorldPos(const FVector3D& Pos);
	void AddWorldPos(float x, float y, float z);
	void AddWorldPos(const FVector2D& Pos);
	void AddWorldPos(float x, float y);
};

