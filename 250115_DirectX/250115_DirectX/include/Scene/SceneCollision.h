#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	//������ �浹ü�� ������ �浹ü ���
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList2D;
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList3D;
	class CCollisionQuadTree* mQuadTree;
	class CScene* mScene = nullptr;

public:
	//�浹ü ���(emplace_back)
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
	void Render();
	void ReturnNodePool();
};

