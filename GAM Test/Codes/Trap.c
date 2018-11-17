/************************************************
Filename: Trap.c
Author: Toh Kai Liang
DP Email: toh.k@digipen.edu
Course: GAM100

Brief Description:
Trap functions
*************************************************/

#include "Trap.h"
#include <stdio.h>

void placeTrap(int index, int x, int y)
{
	dataStorage_setTrapPos(index, x, y);
	dataStorage_getTrapObj(index)->active = true;
}

void destroyTrap(int index)
{
	dataStorage_setTrapPos(index, -1, -1);
	dataStorage_getTrapObj(index)->active = false;
}