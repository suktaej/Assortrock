#pragma once

#include "../UI/UserWidget/WindowWidget.h"

class CSceneUIManager
{
	friend class CScene;

private:
	CSceneUIManager();
	~CSceneUIManager();

private:
	class CScene* mScene = nullptr;
	std::unordered_map<std::string, CSharedPtr<CWindowWidget>>	mWindowMap;
	std::vector<CSharedPtr<CWidget>>	mWidgetList;

public:
	void AddWindowWidget(const std::string& Name,
		CWindowWidget* Widget)
	{
		if (FindWindowWidget(Name))
			return;

		mWindowMap.insert(std::make_pair(Name, Widget));
	}

	CWindowWidget* FindWindowWidget(const std::string& Name)
	{
		auto	iter = mWindowMap.find(Name);

		if (iter == mWindowMap.end())
			return nullptr;

		return iter->second;
	}

public:
	bool Init();
	void Update(float DeltaTime);
	void Render();

public:
	template <typename T>
	T* CreateWidget(const std::string& Name,
		CSceneObject* Owner = nullptr)
	{
		T* Widget = new T;

		Widget->mScene = mScene;
		Widget->mOwnerObject = Owner;

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		mWidgetList.emplace_back(Widget);

		return Widget;
	}
};

