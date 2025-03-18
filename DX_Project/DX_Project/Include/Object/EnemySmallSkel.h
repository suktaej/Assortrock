#pragma once
#include "MonsterObject.h"
class CEnemySmallSkel :
    public CMonsterObject
{
    friend class CScene;

protected:
    CEnemySmallSkel();
    CEnemySmallSkel(const CEnemySmallSkel& Obj);
    CEnemySmallSkel(CEnemySmallSkel&& Obj);
    virtual ~CEnemySmallSkel();

protected:
    float mAttackTime = 0.5f;

public:
    bool Init() final;
    void Update(float DeltaTime) final;
    void AttackNotify() final;
    void AttackEnd() final;
};

