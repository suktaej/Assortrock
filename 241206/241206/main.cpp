#include "GameManager.h"

int main(void)
{
	FPlayer Player;

	if(Init(&Player)==false)	//���� �ʱ�ȭ
		return 0;
	
	Run(&Player);				//���� ����

	return 0;
}