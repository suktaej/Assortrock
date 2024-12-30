#include "Stage.h"
#include "ObjectManager.h"
#include "Item.h"
//#include "Object.h"
//#include "Player.h"

DEFINITION_SINGLE(CStage);

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
    mOutputBuffer = new char[(mXsize + 1) * mYsize + 1];
    memset(mOutputBuffer, 0, (mXsize + 1) * mYsize + 1);

    QueryPerformanceFrequency(&mSecond);
    mStageTime = 0.f;


    return true;
}

void CStage::Run()
{
    system("cls");
  
    QueryPerformanceCounter(&mTime);
    mStageTime = 0.f;
    
    while (true)
    {
        LARGE_INTEGER Time;
        QueryPerformanceCounter(&Time);

        mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
        mStageTime += mDeltaTime;
        mTime = Time;

        CObjectManager::GetInst()->Update(mDeltaTime);
        if (mDeath)
            return;

        COORD Start = {};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Start);

        for (int i = 0;i < mYsize;i++)
        {
            for (int j = 0;j < mXsize;j++)
            {
                int Index = i * (mXsize + 1) + j;

                if (i == 0 || j == 0 || i == mYsize - 1 || j == mXsize - 1)
                    //std::cout << "#";
                    mOutputBuffer[Index] = '#';
                else
                    //std::cout << " ";
                    mOutputBuffer[Index] = ' ';
            }
            //std::cout << std::endl;
            mOutputBuffer[i * (mXsize + 1) + mXsize] = '\n';
        }

        CObjectManager::GetInst()->Output(mOutputBuffer);
        std::cout << mOutputBuffer;
    }
}

