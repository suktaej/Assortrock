#pragma once
#include "../GameInfo.h"

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();
protected:
	//참조 카운터
	int m_RefCount = 0;
	//객체 작동 상태 확인
	//씬에서 사용
	bool m_Active = true;
	//객체의 활성화 상태 확인
	bool m_Enable = true;
public:
	virtual void AddRef();
	virtual void Release();
	void Destroy() { m_Active = false; }
	bool IsActive() const { return m_Active; }
	void SetEnable(bool Enable) { m_Enable = Enable; }
	bool IsEnable() const { return m_Enable; }
};

