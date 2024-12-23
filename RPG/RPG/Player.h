#pragma once
#include "Character.h"
#define MAX_SKILLSLOT 3
enum class EJob :unsigned char
{
    None,
    Fighter,
    Archer,
    Mage
};

class CPlayer :
    public CCharacter  
{
public:
    CPlayer();
    CPlayer(const CPlayer& Obj);
    ~CPlayer();

protected:
    EJob mJob;
    class CSkillActive* mSkillArray[MAX_SKILLSLOT] = {};

public:
    bool Init() override;
    void Output() override;
    CPlayer* Clone() override;
    
    void SetJob(EJob Job) { mJob = Job; }
};
