#pragma once
#include "../Share/Object.h"
class CSceneObject :
    public CObject
{	//오브젝트는 씬에 배치될 예정
    friend class CScene;
protected:
    CSceneObject();
    ~CSceneObject() override;
    //씬 오브젝트는 복사해서 사용할 일이 많음
	CSceneObject(const CSceneObject& Obj);
	CSceneObject(CSceneObject&& Obj);
protected:
	//모든 오브젝트는 본인이 포함된 씬을 알고 있어야 함
	class CScene* mScene = nullptr;
	//씬 오브젝트의 이름정보
	std::string mName;
	//계층구조를 위해 루트 컴포넌트를 확인하기 위한 변수 
	CSharedPtr<class CSceneComponent> mRootComponent;
	//씬 컴포넌트가 아닌 컴포넌트 목록
	//부모자식의 구분이 필요 없음
	std::vector<CSharedPtr<class CComponent>> mNonComponentList;

	float mLifeTime = 0.f;
public:
	//포함 된 씬을 반환하기 위함
	class CScene* GetScene() const { return mScene; }
	//c_str() : std::string 타입의 문자열 포인터 반환
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
		
		//생성한 컴포넌트가 씬 컴포넌트인지 확인
		class CSceneComponent* Com = dynamic_cast<CSceneComponent*>(Component);
		//씬 컴포넌트가 아닐 경우 mComponentList에 저장
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

