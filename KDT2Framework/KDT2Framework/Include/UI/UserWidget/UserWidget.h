#pragma once

#include "../Widget.h"

class CUserWidget :
    public CWidget
{
	friend class CSceneUIManager;

protected:
	CUserWidget();
	virtual ~CUserWidget();

protected:
	std::vector<CSharedPtr<CWidget>>	mWidgetList;

public:
	void AddWidget(CWidget* Widget)
	{
		mWidgetList.emplace_back(Widget);
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
	virtual bool CollisionMouse(const FVector2D& MousePos);
};

