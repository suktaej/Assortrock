#pragma once

#include "GameInfo.h"

// 클래스에 final 을 붙여줄 경우 부모클래스로
// 사용할 수 없다. 이 클래스는 더이상 상속을
// 받을 수 없는 클래스가 된다.
class CObject1// final
{
public:
	CObject1();
	virtual ~CObject1();

protected:
	//char	mName[32];
};

