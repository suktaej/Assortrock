#pragma once
#include "../GameInfo.h"

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();
protected:
	//���� ī����
	int m_RefCount = 0;
	//��ü �۵� ���� Ȯ��
	//������ ���
	bool m_Active = true;
	//��ü�� Ȱ��ȭ ���� Ȯ��
	bool m_Enable = true;
public:
	virtual void AddRef();
	virtual void Release();
	void Destroy() { m_Active = false; }
	bool IsActive() const { return m_Active; }
	void SetEnable(bool Enable) { m_Enable = Enable; }
	bool IsEnable() const { return m_Enable; }
};

