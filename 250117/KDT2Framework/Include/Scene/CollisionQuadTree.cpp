#include "CollisionQuadTree.h"
#include "../Device.h"
#include "Scene.h"
#include "CameraManager.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderBase.h"

CCollisionQuadTreeNode::CCollisionQuadTreeNode()
{
}

CCollisionQuadTreeNode::~CCollisionQuadTreeNode()
{
	// 자식노드는 하나라도 있을 경우 무조건 4개를 다 분할한
	// 것이기 때문에 첫번째 자식이 있을 경우 4개의 노드를
	// 모두 제거한다.
	if (mChild[0])
	{
		SAFE_DELETE(mChild[0]);
		SAFE_DELETE(mChild[1]);
		SAFE_DELETE(mChild[2]);
		SAFE_DELETE(mChild[3]);
	}
}

void CCollisionQuadTreeNode::AddCollider(CColliderBase* Collider, 
	std::vector<CCollisionQuadTreeNode*>& NodePool)
{
	// 충돌체가 노드 안에 포함되는지를 판단한다.
	if (!IsInCollider(Collider))
		return;

	// 자식 노드가 없을 경우
	if (!mChild[0])
	{
		// 충돌 목록에 추가한다.
		mColliderList.emplace_back(Collider);

		// 노드가 가지고 있는 충돌체가 2개 이상일 경우 상호간의
		// 충돌체크를 해야하기 때문에 충돌 노드 목록에
		// 넣어준다.
		if (mColliderList.size() == 2)
		{
			mTree->AddCollisionNodeList(this);
		}

		// 충돌목록에 추가된 개수가 노드를 분할해야할 개수 이상인지
		// 판단한다.
		// 너무 많이 분할하면 느려질 수 있기 때문에 최대 분할개수를
		// 정해둔다.
		if (mColliderList.size() >= mDivisionCount &&
			mDepth < QUADTREE_DEPTH_MAX)
		{
			// 노드를 분할한다.
			CreateChild(NodePool);

			// 4개의 노드가 분할되었으므로 현재 노드가 가지고 있는
			// 충돌체들을 각 Child에 분배해준다.
			size_t	Size = mColliderList.size();

			for (size_t i = 0; i < Size; ++i)
			{
				// 여러 자식 영역에 겹쳐있는 충돌체가 있을 수
				// 있으므로 각 자식 안에 들어가는지 판단하여
				// 추가한다.
				for (int j = 0; j < 4; ++j)
				{
					if (mChild[j]->IsInCollider(mColliderList[i]))
					{
						mChild[j]->AddCollider(mColliderList[i], NodePool);
					}
				}
			}

			// 자식에 모두 분배가 끝났기 때문에 목록을 비워준다.
			mColliderList.clear();

			// 현재 노드는 가지고 있는 충돌체를 자식노드에 분배
			// 해주었기 때문에 더이상 충돌 노드목록에 있으면 안된다.
			// 충돌 노드목록에서 현재 노드를 제거해야 한다.
			mTree->EraseCollisionNodeList(this);
		}

		/*else
		{
		}*/
	}

	else
	{
		mChild[0]->AddCollider(Collider, NodePool);
		mChild[1]->AddCollider(Collider, NodePool);
		mChild[2]->AddCollider(Collider, NodePool);
		mChild[3]->AddCollider(Collider, NodePool);
	}
}

void CCollisionQuadTreeNode::CreateChild(
	std::vector<CCollisionQuadTreeNode*>& NodePool)
{
	if (NodePool.empty())
	{
		// 노드 풀이 비어있을 경우 4개의 자식노드를 분할해야
		// 하기 때문에 새로운 노드 4개를 만들어서 노드풀에
		// 넣어준다.
		NodePool.emplace_back(new CCollisionQuadTreeNode);
		NodePool.emplace_back(new CCollisionQuadTreeNode);
		NodePool.emplace_back(new CCollisionQuadTreeNode);
		NodePool.emplace_back(new CCollisionQuadTreeNode);
	}

	// 만약 노드풀이 이미 있었다면 위의 if문은 동작하지 않고
	// 아래의 코드가 바로 동작되기 때문에 노드풀이 가지고 있는
	// 노드로 활용한다.
	// 가장 뒤의 노드를 꺼내온다.
	for (int i = 0; i < 4; ++i)
	{
		mChild[i] = NodePool.back();

		mChild[i]->mTree = mTree;

		// 실제 사용되는 노드로 빠졌기 때문에 가장 뒤의 노드를 지운다.
		NodePool.pop_back();

		// 자식노드의 가로, 세로 크기는 현재 노드의 가로, 세로 크기의
		// 절반크기로 지정한다.
		mChild[i]->mSize = mSize * 0.5f;

		// 왼쪽, 오른쪽으로 나누어서 x 위치를 구해준다.
		if (i % 2 == 0)
			mChild[i]->mCenter.x = mCenter.x - mSize.x * 0.25f;

		else
			mChild[i]->mCenter.x = mCenter.x + mSize.x * 0.25f;

		if(i <= 1)
			mChild[i]->mCenter.y = mCenter.y + mSize.y * 0.25f;

		else
			mChild[i]->mCenter.y = mCenter.y - mSize.y * 0.25f;

		mChild[i]->mParent = this;
		mChild[i]->mDepth = mDepth + 1;
	}
}

void CCollisionQuadTreeNode::Collision(float DeltaTime)
{
}

void CCollisionQuadTreeNode::ReturnNodePool(
	std::vector<CCollisionQuadTreeNode*>& NodePool)
{
	mColliderList.clear();

	if (mChild[0])
	{
		for (int i = 0; i < 4; ++i)
		{
			NodePool.emplace_back(mChild[i]);

			mChild[i]->ReturnNodePool(NodePool);

			mChild[i] = nullptr;
		}
	}
}

bool CCollisionQuadTreeNode::IsInCollider(CColliderBase* Collider)
{
	FVector2D	Min, Max;
	Min.x = Collider->GetMin().x;
	Min.y = Collider->GetMin().y;

	Max.x = Collider->GetMax().x;
	Max.y = Collider->GetMax().y;

	FVector2D	NodeMin, NodeMax;

	NodeMin = mCenter - mSize * 0.5f;
	NodeMax = NodeMin + mSize;

	if (Min.x > NodeMax.x)
		return false;

	else if (Max.x < NodeMin.x)
		return false;

	else if (Min.y > NodeMax.y)
		return false;

	else if (Max.y < NodeMin.y)
		return false;

	return true;
}

CCollisionQuadTree::CCollisionQuadTree()
{
}

CCollisionQuadTree::~CCollisionQuadTree()
{
	size_t	Size = mNodePool.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(mNodePool[i]);
	}

	SAFE_DELETE(mRoot);
}

void CCollisionQuadTree::SetDivisionCount(int Count)
{
	mDivisionCount = Count;
}

void CCollisionQuadTree::EraseCollisionNodeList(
	CCollisionQuadTreeNode* Node)
{
	auto	iter = mCollisionNodeList.begin();
	auto	iterEnd = mCollisionNodeList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == Node)
		{
			mCollisionNodeList.erase(iter);
			break;
		}
	}
}

bool CCollisionQuadTree::Init()
{
	mRoot = new CCollisionQuadTreeNode;

	const FResolution& RS = CDevice::GetInst()->GetResolution();

	mRoot->mSize.x = RS.Width * 1.5f;
	mRoot->mSize.y = RS.Height * 1.5f;
	mRoot->mDivisionCount = mDivisionCount;
	mRoot->mTree = this;

	return true;
}

void CCollisionQuadTree::AddCollider(CColliderBase* Collider)
{
	mRoot->AddCollider(Collider, mNodePool);
}

void CCollisionQuadTree::Update(float DeltaTime)
{
	CCameraComponent* Camera = mScene->GetCameraManager()->GetViewTarget();

	// 카메라를 얻어와서 카메라의 위치로 루트의 센터를 지정한다.
	// 카메라의 위치가 화면의 중심이 되도록 구성되었기 때문이다.
	if (Camera)
	{
		mRoot->mCenter.x = Camera->GetWorldPosition().x;
		mRoot->mCenter.y = Camera->GetWorldPosition().y;
	}
}

void CCollisionQuadTree::Collision(float DeltaTime)
{
	auto	iter = mCollisionNodeList.begin();
	auto	iterEnd = mCollisionNodeList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Collision(DeltaTime);
	}

	// 충돌이 완료되고 난 후에는 목록을 비워준다.
	mCollisionNodeList.clear();

	// 생성된 노드들을 노드 풀에 수거하고 다음 프레임에
	// 활용할 수 있게 해준다.
	mRoot->ReturnNodePool(mNodePool);
}
