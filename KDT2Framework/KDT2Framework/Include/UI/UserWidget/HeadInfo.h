#pragma once

#include "UserWidget.h"
#include "../Common/TextBlock.h"
#include "../Common/ProgressBar.h"

class CHeadInfo :
    public CUserWidget
{
	friend class CSceneUIManager;

protected:
	CHeadInfo();
	virtual ~CHeadInfo();

protected:
	CSharedPtr<CTextBlock>		mNameText;
	CSharedPtr<CProgressBar>	mHPBar;

public:
	virtual bool Init();
	virtual void Render();
	virtual void Render(const FVector3D& Pos);
};

