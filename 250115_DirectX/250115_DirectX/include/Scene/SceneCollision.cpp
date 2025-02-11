#include "SceneCollision.h"
#include "../Component/ColliderBase.h"
#include "CollisionQuadTree.h"

CSceneCollision::CSceneCollision()
{
}

CSceneCollision::~CSceneCollision()
{
    SAFE_DELETE(mQuadTree);
}

void CSceneCollision::AddCollider(CColliderBase* Collider)
{
    if (Collider->GetColliderType() == EColliderType::Colider2D)
        mColliderList2D.emplace_back(Collider);

    else
        mColliderList3D.emplace_back(Collider);
}

bool CSceneCollision::Init()
{
    mQuadTree = new CCollisionQuadTree;
    //Init 전 가지고 있는 Scene을 전달
    //쿼드트리에서 루트노드는 무조건 필요하므로 씬을 전달
    mQuadTree->mScene = mScene;
    mQuadTree->Init();

    return true;
}

void CSceneCollision::Update(float DeltaTime)
{
    mQuadTree->Update(DeltaTime);

    size_t Size = mColliderList2D.size();
    //Active가 false가 되면 size가 변경될 수 있음
    for (size_t i = 0; i < Size;)
    {
        if (!mColliderList2D[i]->IsActive())
        {
            if (i < Size - 1)
            {
                //순서 유지가 필요없는 벡터의 경우 pop&swap이 빠름
                /*CSharedPtr<CColliderBase> Temp = mColliderList2D[i];
                mColliderList2D[i] = mColliderList2D[Size - 1];
                mColliderList2D[Size - 1] = Temp;*/
                mColliderList2D[i] = mColliderList2D[Size - 1];
            }
            mColliderList2D.pop_back();
            --Size;
            continue;
        }

        else if (!mColliderList2D[i]->IsEnable())
        {
            ++i;
            continue;
        }

        // 쿼드트리에 추가
        mQuadTree->AddCollider(mColliderList2D[i]);

        ++i;
    }

    // 모든 충돌체가 쿼드트리의 노드에 추가되었기 때문에
    // 충돌처리를 진행한다.
    mQuadTree->Collision(DeltaTime);
}

void CSceneCollision::Render()
{
    mQuadTree->Render();
}

void CSceneCollision::ReturnNodePool()
{
    mQuadTree->ReturnNodePool();
}
