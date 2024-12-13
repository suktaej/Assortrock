#include "GameManager.h"

int main(void)
{
	FPlayer Player;

	if(Init(&Player)==false)
		return 0;

	Run(&Player);
	Destroy();

	return 0;
}