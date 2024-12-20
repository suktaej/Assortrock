#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
private:
    class CMaze* mMaze = nullptr;
    int mHP = 5;
public:
    bool Init() override;
    void Update() override;
    void Output(char* OutBuffer, int CountX) override;
    void SetMaze(class CMaze* Maze) { mMaze = Maze; }
    int GetHP() const { return mHP; }
    bool SetHP(int Input);
};
