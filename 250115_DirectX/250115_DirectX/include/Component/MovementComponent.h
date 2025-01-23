#pragma once
#include "Component.h"
class CMovementComponent :
    public CComponent
{
    //friend class 
    //friend class 
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PreRender();
	virtual void PostRender();
	virtual CMovementComponent* Clone();
};

