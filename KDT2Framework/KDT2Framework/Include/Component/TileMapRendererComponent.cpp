#include "TileMapRendererComponent.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAssetManager.h"
#include "../Shader/TransformCBuffer.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Shader/SpriteCBuffer.h"
#include "../Scene/CameraManager.h"
#include "TileMapComponent.h"

CTileMapRendererComponent::CTileMapRendererComponent()
{
    mRenderType = EComponentRender::Render;
    mRenderLayerName = "BackGround";
}

CTileMapRendererComponent::CTileMapRendererComponent(const CTileMapRendererComponent& Com)  :
    CSceneComponent(Com)
{
}

CTileMapRendererComponent::CTileMapRendererComponent(CTileMapRendererComponent&& Com) :
    CSceneComponent(Com)
{
}

CTileMapRendererComponent::~CTileMapRendererComponent()
{
    SAFE_DELETE(mSpriteCBuffer);
}

void CTileMapRendererComponent::SetShader(const std::string& Name)
{
    mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CTileMapRendererComponent::SetShader(CShader* Shader)
{
    mShader = Shader;
}

void CTileMapRendererComponent::SetBackTexture(const std::string& Name)
{
    if (mScene)
        mBackTexture = mScene->GetAssetManager()->FindTexture(Name);

    else
        mBackTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
}

void CTileMapRendererComponent::SetBackTexture(const std::string& Name, const TCHAR* FileName)
{
    if (mScene)
    {
        if (!mScene->GetAssetManager()->LoadTexture(Name, FileName))
        {
            return;
        }
        mBackTexture = mScene->GetAssetManager()->FindTexture(Name);
    }

    else
    {
        if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
        {
            return;
        }
        mBackTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
    }
}

void CTileMapRendererComponent::SetBackTexture(CTexture* Texture)
{
    mBackTexture = Texture;
}

void CTileMapRendererComponent::SetTileTexture(const std::string& Name)
{
    if (mScene)
        mTileTexture = mScene->GetAssetManager()->FindTexture(Name);

    else
        mTileTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
}

void CTileMapRendererComponent::SetTileTexture(const std::string& Name, const TCHAR* FileName)
{
    if (mScene)
    {
        if (!mScene->GetAssetManager()->LoadTexture(Name, FileName))
        {
            return;
        }
        mTileTexture = mScene->GetAssetManager()->FindTexture(Name);
    }

    else
    {
        if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
        {
            return;
        }
        mTileTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
    }
}

void CTileMapRendererComponent::SetTileTexture(CTexture* Texture)
{
    mTileTexture = Texture;
}

bool CTileMapRendererComponent::Init()
{
    CSceneComponent::Init();

    mTileMap = mOwnerObject->FindNonSceneComponent<CTileMapComponent>();

    return true;
}

bool CTileMapRendererComponent::Init(const char* FileName)
{
    CSceneComponent::Init(FileName);

    mTileMap = mOwnerObject->FindNonSceneComponent<CTileMapComponent>();

    return true;
}

void CTileMapRendererComponent::PreUpdate(float DeltaTime)
{
    CSceneComponent::PreUpdate(DeltaTime);
}

void CTileMapRendererComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CTileMapRendererComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CTileMapRendererComponent::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CTileMapRendererComponent::PreRender()
{
    CSceneComponent::PreRender();
}

void CTileMapRendererComponent::Render()
{
    CSceneComponent::Render();
}

void CTileMapRendererComponent::PostRender()
{
    CSceneComponent::PostRender();
}

CTileMapRendererComponent* CTileMapRendererComponent::Clone()
{
    return new CTileMapRendererComponent(*this);
}
