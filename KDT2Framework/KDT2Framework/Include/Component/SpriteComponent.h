#pragma once

#include "SceneComponent.h"

class CSpriteComponent :
    public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSpriteComponent();
	CSpriteComponent(const CSpriteComponent& Com);
	CSpriteComponent(CSpriteComponent&& Com);
	virtual ~CSpriteComponent();

protected:
	CSharedPtr<class CMesh>			mMesh;
	CSharedPtr<class CShader>		mShader;
	CSharedPtr<class CTexture>		mTexture;
	FVector4D	mTint = FVector4D::White;
	int			mTextureIndex = 0;

	class CSpriteCBuffer* mSpriteCBuffer;

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);
	void SetTexture(const std::string& Name,
		int TextureIndex = 0);
	void SetTexture(const std::string& Name,
		const TCHAR* FileName,
		int TextureIndex = 0);
	void SetTexture(class CTexture* Texture,
		int TextureIndex = 0);
	void SetTint(float r, float g, float b);
	void SetOpacity(float Opacity);

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CSpriteComponent* Clone();
};

