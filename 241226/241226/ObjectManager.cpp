#include "ObjectManager.h"
#include "Player.h"
CObjectManager* CObjectManager::mInst;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
    CreateObj<CPlayer>();
	return true;
}

void CObjectManager::Update(float DeltaTime)
{
    //for(CObject*& Obj : mObjList)
    std::list<CObject*>::iterator iter;
    std::list<CObject*>::iterator iterEnd = mObjList.end();

    for (iter = mObjList.begin();iter != iterEnd;)
    {
        (*iter)->Update(DeltaTime);

        if (!(*iter)->GetActive())      //플래그(mActive)가 false일 경우
        {
            SAFE_DELETE(*iter);         //동적할당 메모리 삭제
            //mObjList.erase(iter);     //리스트에서 제거
                                        //여기까지만 진행된다면 iterator가 가르키는 다음 노드를 알 수 없게 되어 오류 발생

            iter = mObjList.erase(iter);//삭제하면서 iter반환(다음 노드의 값)
            continue;                   //for문을 건너뛰고(for문 구조 확인)
        }
        ++iter;                         //iter 증가
    }   
    //충돌처리
    if (mObjList.size() >= 2)
    {
        iterEnd = mObjList.end();
        --iterEnd;

        for (iter = mObjList.begin(); iter != iterEnd;)
        {
            std::list<CObject*>::iterator iter1 = iter;
            iter1++;

            std::list<CObject*>::iterator iter1End = mObjList.end();

            bool IterErase = false;//iter이 지워지는지 확인

            for (;iter1 != iter1End;)
            {
                if ((*iter)->GetPos().X == (*iter1)->GetPos().X &&
                    (*iter)->GetPos().Y == (*iter1)->GetPos().Y)
                {
                    //타입 체크(충돌이 유효한 객체인지 판단)
                    //1.dynamic cast 
                    // 총알의 경우, 적이 쏜 것인지 플레이어가 쏜 것인지 구분할 수 없음
                    // 케스팅 비용이 소모됨
                    //2.enum

                    //player와 충돌할 수 있는 객체목록(적, 총알, 아이템...)

                    bool Death = false;
                    bool Death1 = false;

                    switch ((*iter)->CollisionEnable(*iter1))
                    {
                    case ECollisionType::Damage:
                        Death = (*iter)->Damage((*iter1)->GetDamage());
                        Death1 = (*iter1)->Damage((*iter)->GetDamage());
                        break;
                    case ECollisionType::Heal:
                        break;
                    case ECollisionType::Power:
                        break;
                    case ECollisionType::Score:
                        break;
                    }

                    if (Death1) //iter를 우선 제거 시 for문이 종료되므로 iter1을 선행
                    {
                        SAFE_DELETE(*iter1);
                        iter1 = mObjList.erase(iter1);
                        iter1End = mObjList.end();
                        iterEnd = iter1End;
                        --iterEnd;
                    }
                    if (Death)
                    {
                        IterErase = true; //iter 삭제여부 확인
                        SAFE_DELETE(*iter);
                        iter = mObjList.erase(iter);
                        iterEnd = mObjList.end();
                        break;
                    }
                    if (Death1)
                        continue;
                }
                ++iter1;
                //충돌이 안 될 경우 다음을 체크
            }
            if (!IterErase)  //iter가 지워지지 않았을 때만 증가
                ++iter;
        }
    }
}

void CObjectManager::Output(char* OutputBuffer)
{
    std::list<CObject*>::iterator iter;
    std::list<CObject*>::iterator iterEnd = mObjList.end();

    for (iter = mObjList.begin();iter != iterEnd;iter++)
        (*iter)->Output(OutputBuffer);
}
