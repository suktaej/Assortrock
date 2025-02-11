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
    //Init �� ������ �ִ� Scene�� ����
    //����Ʈ������ ��Ʈ���� ������ �ʿ��ϹǷ� ���� ����
    mQuadTree->mScene = mScene;
    mQuadTree->Init();

    return true;
}

void CSceneCollision::Update(float DeltaTime)
{
    mQuadTree->Update(DeltaTime);

    size_t Size = mColliderList2D.size();
    //Active�� false�� �Ǹ� size�� ����� �� ����
    for (size_t i = 0; i < Size;)
    {
        if (!mColliderList2D[i]->IsActive())
        {
            if (i < Size - 1)
            {
                //���� ������ �ʿ���� ������ ��� pop&swap�� ����
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

        // ����Ʈ���� �߰�
        mQuadTree->AddCollider(mColliderList2D[i]);

        ++i;
    }

    // ��� �浹ü�� ����Ʈ���� ��忡 �߰��Ǿ��� ������
    // �浹ó���� �����Ѵ�.
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
