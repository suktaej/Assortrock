#pragma once
#include "GameInfo.h"

extern FItem* gInventory[INVENTORY_MAX];
extern int gInventoryCount;

bool InitInventory();
void DestroyInventory();
void RunInventory(FPlayer* Player);
