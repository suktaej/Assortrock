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

        if (!(*iter)->GetActive())      //�÷���(mActive)�� false�� ���
        {
            SAFE_DELETE(*iter);         //�����Ҵ� �޸� ����
            //mObjList.erase(iter);     //����Ʈ���� ����
                                        //��������� ����ȴٸ� iterator�� ����Ű�� ���� ��带 �� �� ���� �Ǿ� ���� �߻�

            iter = mObjList.erase(iter);//�����ϸ鼭 iter��ȯ(���� ����� ��)
            continue;                   //for���� �ǳʶٰ�(for�� ���� Ȯ��)
        }
        ++iter;                         //iter ����
    }   
    //�浹ó��
    if (mObjList.size() >= 2)
    {
        iterEnd = mObjList.end();
        --iterEnd;

        for (iter = mObjList.begin(); iter != iterEnd;)
        {
            std::list<CObject*>::iterator iter1 = iter;
            iter1++;

            std::list<CObject*>::iterator iter1End = mObjList.end();

            bool IterErase = false;//iter�� ���������� Ȯ��

            for (;iter1 != iter1End;)
            {
                if ((*iter)->GetPos().X == (*iter1)->GetPos().X &&
                    (*iter)->GetPos().Y == (*iter1)->GetPos().Y)
                {
                    //Ÿ�� üũ(�浹�� ��ȿ�� ��ü���� �Ǵ�)
                    //1.dynamic cast 
                    // �Ѿ��� ���, ���� �� ������ �÷��̾ �� ������ ������ �� ����
                    // �ɽ��� ����� �Ҹ��
                    //2.enum

                    //player�� �浹�� �� �ִ� ��ü���(��, �Ѿ�, ������...)

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

                    if (Death1) //iter�� �켱 ���� �� for���� ����ǹǷ� iter1�� ����
                    {
                        SAFE_DELETE(*iter1);
                        iter1 = mObjList.erase(iter1);
                        iter1End = mObjList.end();
                        iterEnd = iter1End;
                        --iterEnd;
                    }
                    if (Death)
                    {
                        IterErase = true; //iter �������� Ȯ��
                        SAFE_DELETE(*iter);
                        iter = mObjList.erase(iter);
                        iterEnd = mObjList.end();
                        break;
                    }
                    if (Death1)
                        continue;
                }
                ++iter1;
                //�浹�� �� �� ��� ������ üũ
            }
            if (!IterErase)  //iter�� �������� �ʾ��� ���� ����
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
