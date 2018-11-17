
#include "Data Storage.h"
#include "Console.h"
#include "Array Reader.h"
#include "Enemy.h"
#include <stdio.h>


static PlayerPosition playerPosition;
static Enemy enemyObject[10];
static FogDistance fogDistance;
static MapArray mapArray;
static Torch torches[5];
static Torch torches[5];
static Trap traps[5];
static bool playerAlive;
static Exit exitLocation;

void dataStorage_init()
{
	playerPosition.x = playerPosition.y = 0;
	
	fogDistance.fogStart = fogDistance.fogEnd = 0;

	mapArray.width = mapArray.height = 0;

	playerAlive = true;
}

bool * dataStorage_getAliveBool()
{
	return &playerAlive;
}

void dataStorage_EnemyInit(char playerX, char playerY)
{
	char i = 0;

	int width = dataStorage_getMapDataOut()->width;
	int height = dataStorage_getMapDataOut()->height;

	/*Initialization of default enemies without position*/
	/*Change the positions of enemies when needed to spawn*/
	for (i = 0; i < 10; i++)
	{
		dataStorage_setEnemyPosition(-1, -1, i);
		enemyObject[i].patrolling = false;
		enemyObject[i].patrolx1 = -1;
		enemyObject[i].patrolx2 = -1;
		enemyObject[i].patroly1 = -1;
		enemyObject[i].patroly2 = -1;
		enemyObject[i].active = false;
		enemyObject[i].seen = false;
		enemyObject[i].patrolDirection = 0;
	}

	enemy_weightedMapInit(&mapArray);
	enemy_recursiveCheckPath(&mapArray, playerX, playerY, 1, 1);
	enemy_setWallWeight(-1,&mapArray);

}


void dataStorage_setPlayerPosition(int x, int y)
{
	playerPosition.x = x;
	playerPosition.y = y;
}

void dataStorage_getPlayerPosition(int *x, int *y)
{
	*x = playerPosition.x;
	*y = playerPosition.y;
}

void dataStorage_setEnemyPosition(int x, int y,short index)
{
	enemyObject[index].x = x;
	enemyObject[index].y = y;
}

void dataStorage_getEnemyPosition(int *x, int *y, short index)
{
	*x = enemyObject[index].x;
	*y = enemyObject[index].y;
}

void dataStorage_activateEnemy(char index)
{
	enemyObject[index].active = true;
}

Enemy* dataStorage_getEnemyObject(char index)
{
	return &enemyObject[index];
}

void dataStorage_setFogDistance(int start, int end)
{
	fogDistance.fogStart = start;
	fogDistance.fogEnd = end;
}

void dataStorage_getFogDistance(int *start, int *end)
{
	*start = fogDistance.fogStart;
	*end = fogDistance.fogEnd;
}

void dataStorage_setMapData(char *arr, int width, int height)
{
	mapArray.mapArray = arr;
	mapArray.width = width;
	mapArray.height = height;
}

void dataStorage_getMapData(int *width, int *height)
{
	*width = mapArray.width;
	*height = mapArray.height;
}

char dataStorage_getMapValue(int x, int y)
{
	return mapArray.mapArray[x + y * mapArray.width];
}
void dataStorage_getMapSize(int *width, int *height)
{
	*width = mapArray.width;
	*height = mapArray.height;
}

/*Edit in the future when theresmore than 1 map*/
MapArray* dataStorage_getMapDataOut()
{
	return &mapArray;
}

bool dataStorage_checkWall()
{
	switch (dataStorage_getMapValue(playerPosition.x, playerPosition.y))
	{
		case 0:
			return false;
			break;

		case 1:
			return true;
			break;
	}
}


/* Torch Functions ---------------------------------- */
void dataStorage_TorchInit()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		dataStorage_setTorchPos(i, -1, -1);
		torches[i].active = false;
	}
}

void dataStorage_setTorchPos(int index, int x, int y)
{
	torches[index].x = x;
	torches[index].y = y;
}

void dataStorage_getTorchPos(int index, int *x, int *y)
{
	*x = torches[index].x;
	*y = torches[index].y;
}

Torch* dataStorage_getTorchObj(int index)
{
	return &torches[index];
}

/* Trap Functions ---------------------------------- */
void dataStorage_TrapInit()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		dataStorage_setTrapPos(i, -1, -1);
		traps[i].active = false;
	}
}

void dataStorage_setTrapPos(int index, int x, int y)
{
	traps[index].x = x;
	traps[index].y = y;
}

void dataStorage_getTrapPos(int index, int *x, int *y)
{
	*x = traps[index].x;
	*y = traps[index].y;
}

Trap* dataStorage_getTrapObj(int index)
{
	return &traps[index];
}

void dataStorage_setExitPos(int x, int y)
{
	exitLocation.x = x;
	exitLocation.y = y;
}

void dataStorage_getExitPos(int *x, int *y)
{
	*x = exitLocation.x;
	*y = exitLocation.y;
}