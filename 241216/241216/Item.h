#pragma once

#include "Object.h"

class CItem :
    public CObject
{
public:
	CItem();
	CItem(const CItem& Obj);
	~CItem();

protected:
	EItemType	mType;
	int			mOption = 0;
	int			mBuy = 0;
	int			mSell = 0;

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CItem* Clone();
	/*
	override 키워드 : 이 함수가 부모의 함수를 재정의
	한 함수임을 명시한다.
	만약 부모에 같은 형태의 함수가 없다면
	이 함수는 에러를 발생시킨다.
	*/
	virtual void OverrideTest()	override;
	//virtual void OverrideTest(int Number)	override;
	virtual void VirtualPure();
	virtual void VirtualPure1();
	virtual void VirtualPure2();
	virtual void VirtualPure3();
	// 부모에는 CObject*를 리턴하는데 여기서는
	// CItem* 로 재정의를 해도 된다.
};

