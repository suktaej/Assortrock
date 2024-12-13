#include "GameManager.h"

int main(void)
{
	FPlayer Player;

	if(Init(&Player)==false)	//게임 초기화
		return 0;
	
	Run(&Player);				//게임 실행

	return 0;
}