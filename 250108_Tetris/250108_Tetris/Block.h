#pragma once
#include "Object.h"
class FBlock :
    public FObject
{
    enum class EBlockType{ I, O, J, L, T, S, Z};
public:
    FBlock();
    ~FBlock() override;
private:
    EBlockType m_BlockType;
    std::vector<std::vector<char>> m_BlockShape;
public:
    bool Init() override;
    void Output(std::vector<std::vector<char>>&) override;
    void Update(float) override;
public:
    void Rotate();
public:
    std::vector<std::vector<char>>& GetShape() { return m_BlockShape; }
};

