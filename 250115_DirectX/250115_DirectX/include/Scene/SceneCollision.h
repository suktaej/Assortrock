#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	//생성한 충돌체를 저장할 충돌체 목록
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList2D;
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList3D;
	class CCollisionQuadTree* mQuadTree;
	class CScene* mScene = nullptr;

public:
	//충돌체 등록(emplace_back)
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
	void Render();
	void ReturnNodePool();
};

