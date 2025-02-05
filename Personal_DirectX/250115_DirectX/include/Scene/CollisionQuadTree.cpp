#include "CollisionQuadTree.h"
#include "../Device.h"
#include "Scene.h"
#include "CameraManager.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderBase.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Shader/TransformCBuffer.h"
#include "../Shader/ColliderCBuffer.h"

CCollisionQuadTreeNode::CCollisionQuadTreeNode()
{
#ifdef _DEBUG
	mTransformCBuffer = new CTransformCBuffer;

	mTransformCBuffer->Init();
#endif
}

CCollisionQuadTreeNode::~CCollisionQuadTreeNode()
{
#ifdef _DEBUG
	SAFE_DELETE(mTransformCBuffer);
#endif
	// �ڽĳ��� �ϳ��� ���� ��� ������ 4���� �� ������
	// ���̱� ������ ù��° �ڽ��� ���� ��� 4���� ��带
	// ��� �����Ѵ�.
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
	// �浹ü�� ��� �ȿ� ���ԵǴ����� �Ǵ��Ѵ�.
	if (!IsInCollider(Collider))
		return;

	// �ڽ� ��尡 ���� ���
	if (!mChild[0])
	{
		// �浹 ��Ͽ� �߰��Ѵ�.
		mColliderList.emplace_back(Collider);

		// ��尡 ������ �ִ� �浹ü�� 2�� �̻��� ��� ��ȣ����
		// �浹üũ�� �ؾ��ϱ� ������ �浹 ��� ��Ͽ�
		// �־��ش�.
		if (mColliderList.size() == 2)
		{
			mTree->AddCollisionNodeList(this);
		}

		// �浹��Ͽ� �߰��� ������ ��带 �����ؾ��� ���� �̻�����
		// �Ǵ��Ѵ�.
		// �ʹ� ���� �����ϸ� ������ �� �ֱ� ������ �ִ� ���Ұ�����
		// ���صд�.
		if (mColliderList.size() >= mDivisionCount &&
			mDepth < QUADTREE_DEPTH_MAX)
		{
			// ��带 �����Ѵ�.
			CreateChild(NodePool);

			// 4���� ��尡 ���ҵǾ����Ƿ� ���� ��尡 ������ �ִ�
			// �浹ü���� �� Child�� �й����ش�.
			size_t	Size = mColliderList.size();

			for (size_t i = 0; i < Size; ++i)
			{
				// ���� �ڽ� ������ �����ִ� �浹ü�� ���� ��
				// �����Ƿ� �� �ڽ� �ȿ� ������ �Ǵ��Ͽ�
				// �߰��Ѵ�.
				for (int j = 0; j < 4; ++j)
				{
					if (mChild[j]->IsInCollider(mColliderList[i]))
					{
						mChild[j]->AddCollider(mColliderList[i], NodePool);
					}
				}
			}

			// �ڽĿ� ��� �й谡 ������ ������ ����� ����ش�.
			mColliderList.clear();

			// ���� ���� ������ �ִ� �浹ü�� �ڽĳ�忡 �й�
			// ���־��� ������ ���̻� �浹 ����Ͽ� ������ �ȵȴ�.
			// �浹 ����Ͽ��� ���� ��带 �����ؾ� �Ѵ�.
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
		// ��� Ǯ�� ������� ��� 4���� �ڽĳ�带 �����ؾ�
		// �ϱ� ������ ���ο� ��� 4���� ���� ���Ǯ��
		// �־��ش�.
		NodePool.emplace_back(new CCollisionQuadTreeNode);
		NodePool.emplace_back(new CCollisionQuadTreeNode);
		NodePool.emplace_back(new CCollisionQuadTreeNode);
		NodePool.emplace_back(new CCollisionQuadTreeNode);
	}

	// ���� ���Ǯ�� �̹� �־��ٸ� ���� if���� �������� �ʰ�
	// �Ʒ��� �ڵ尡 �ٷ� ���۵Ǳ� ������ ���Ǯ�� ������ �ִ�
	// ���� Ȱ���Ѵ�.
	// ���� ���� ��带 �����´�.
	for (int i = 0; i < 4; ++i)
	{
		mChild[i] = NodePool.back();

		mChild[i]->mTree = mTree;
		mChild[i]->mScene = mScene;

		// ���� ���Ǵ� ���� ������ ������ ���� ���� ��带 �����.
		NodePool.pop_back();

		// �ڽĳ���� ����, ���� ũ��� ���� ����� ����, ���� ũ����
		// ����ũ��� �����Ѵ�.
		mChild[i]->mSize = mSize * 0.5f;

		// ����, ���������� ����� x ��ġ�� �����ش�.
		if (i % 2 == 0)
			mChild[i]->mCenter.x = mCenter.x - mSize.x * 0.25f;

		else
			mChild[i]->mCenter.x = mCenter.x + mSize.x * 0.25f;

		if (i <= 1)
			mChild[i]->mCenter.y = mCenter.y + mSize.y * 0.25f;

		else
			mChild[i]->mCenter.y = mCenter.y - mSize.y * 0.25f;

		mChild[i]->mParent = this;
		mChild[i]->mDepth = mDepth + 1;
	}
}

void CCollisionQuadTreeNode::Collision(float DeltaTime)
{
	size_t	Size = mColliderList.size();

	for (size_t i = 0; i < Size - 1;)
	{
		CColliderBase* Src = mColliderList[i];

		if (!mColliderList[i]->IsActive())
		{
			if (i < Size - 1)
			{
				mColliderList[i] = mColliderList[Size - 1];
			}
			mColliderList.pop_back();
			--Size;
			continue;
		}

		else if (!mColliderList[i]->IsEnable())
		{
			++i;
			continue;
		}

		FCollisionProfile* SrcProfile = mColliderList[i]->GetProfile();

		if (!SrcProfile->Enable)
		{
			++i;
			continue;
		}

		for (size_t j = i + 1; j < Size;)
		{
			CColliderBase* Dest = mColliderList[j];

			if (!mColliderList[j]->IsActive())
			{
				if (j < Size - 1)
				{
					mColliderList[j] = mColliderList[Size - 1];
				}
				mColliderList.pop_back();
				--Size;
				continue;
			}

			else if (!mColliderList[j]->IsEnable())
			{
				++j;
				continue;
			}

			FCollisionProfile* DestProfile = mColliderList[j]->GetProfile();

			if (!DestProfile->Enable)
			{
				++j;
				continue;
			}

			// Src�� Dest�� ��ȣ���� Collision���� �Ǿ� �ִ�����
			// �Ǵ��Ѵ�.
			else if (SrcProfile->Interaction[DestProfile->Channel] == ECollisionInteraction::Ignore ||
				DestProfile->Interaction[SrcProfile->Channel] == ECollisionInteraction::Ignore)
			{
				++j;
				continue;
			}

			// ���� �浹ó���� �����Ѵ�.
			FVector3D	HitPoint;

			if (Src->Collision(HitPoint, Dest))
			{
				Src->CallCollisionBegin(HitPoint, Dest);
				Dest->CallCollisionBegin(HitPoint, Src);
			}

			else
			{
			}

			++j;
		}

		++i;
	}
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

void CCollisionQuadTreeNode::Render(CMesh* Mesh, CShader* Shader)
{
#ifdef _DEBUG

	FMatrix	matScale, matTranslate, matWorld;
	matScale.Scaling(mSize);
	matTranslate.Translation(mCenter);

	matWorld = matScale * matTranslate;

	FMatrix	matView, matProj;

	matView = mScene->GetCameraManager()->GetViewMatrix();
	matProj = mScene->GetCameraManager()->GetProjMatrix();

	mTransformCBuffer->SetWorldMatrix(matWorld);
	mTransformCBuffer->SetViewMatrix(matView);
	mTransformCBuffer->SetProjMatrix(matProj);

	mTransformCBuffer->UpdateBuffer();

	Shader->SetShader();

	Mesh->Render();

#endif // _DEBUG

	if (mChild[0])
	{
		mChild[0]->Render(Mesh, Shader);
		mChild[1]->Render(Mesh, Shader);
		mChild[2]->Render(Mesh, Shader);
		mChild[3]->Render(Mesh, Shader);
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
	SAFE_DELETE(mColliderCBuffer);

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
#ifdef _DEBUG

	mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("FrameCenterRect");
	mShader = CShaderManager::GetInst()->FindShader("FrameMeshShader");
	mColliderCBuffer = new CColliderCBuffer;

	mColliderCBuffer->Init();

	mColliderCBuffer->SetColor(1.f, 1.f, 1.f, 1.f);

#endif // _DEBUG


	mRoot = new CCollisionQuadTreeNode;

	mRoot->mScene = mScene;

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

	// ī�޶� ���ͼ� ī�޶��� ��ġ�� ��Ʈ�� ���͸� �����Ѵ�.
	// ī�޶��� ��ġ�� ȭ���� �߽��� �ǵ��� �����Ǿ��� �����̴�.
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

	// �浹�� �Ϸ�ǰ� �� �Ŀ��� ����� ����ش�.
	mCollisionNodeList.clear();
}

void CCollisionQuadTree::Render()
{
#ifdef _DEBUG

	mColliderCBuffer->UpdateBuffer();

	// Shader�� ���⿡�� SetShader �ѹ��� ���൵ ��� ��尡
	// ����� �� �ش� Shader�� �̿��Ͽ� ����Ѵ�.

	mRoot->Render(mMesh, mShader);

#endif // _DEBUG
}

void CCollisionQuadTree::ReturnNodePool()
{
	// ������ ������ ��� Ǯ�� �����ϰ� ���� �����ӿ�
	// Ȱ���� �� �ְ� ���ش�.
	mRoot->ReturnNodePool(mNodePool);
}
