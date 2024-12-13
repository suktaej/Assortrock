#include "GameManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}
CGameManager::~CGameManager()
{
	//if(mPlayer!=nullptr)
	if (mPlayer)
	{
		delete mPlayer;
		mPlayer = nullptr;
	}

	if (mAI)
	{
		delete mAI;
		mAI = nullptr;
	}
}

bool CGameManager::Init()
{
	srand(time(0));
	rand();

	mPlayer = new CPlayer;
	mAI = new CAI;
	
	if (false == mPlayer->Init())
		return false;
	if (false == mAI->Init())
		return false;
	return true;
}

void CGameManager::Run() 
{
	while (true)
	{
		system("cls");
		mPlayer->Output();
		std::cout << "Line: " << mPlayer->GetLineCount() << std::endl;
		mAI->Output();
		std::cout << "Line: " << mAI->GetLineCount() << std::endl;
		
		if (mPlayer->GetLineCount() >= 5)
			break;

		//mPlayer->ResetLineCount();
		//mAI->ResetLineCount();
	
		int Input = 0;
		std::cout << "�����Է�(0:����): ";
		std::cin >> Input;

		if (Input == 0)
			break;

		else if (Input < 0 || Input >25)
			continue;

		if (mPlayer->ChangeNumber(Input))	//����� �Է� ����ں���
			continue;
		mAI->ChangeNumber(Input); //����� �Է� AI����
		mAI->DeleteNumber(Input);
		
		Input = mAI->AINumberInput();
		mPlayer->ChangeNumber(Input);
		mAI->ChangeNumber(Input);
		mAI->DeleteNumber(Input);
		
		mPlayer->CheckLine();
		mAI->CheckLine();
	}
}
