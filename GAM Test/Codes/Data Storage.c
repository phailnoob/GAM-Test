
#include "Data Storage.h"
#include "Console.h"
#include "Array Reader.h"
#include "Enemy.h"
#include <stdio.h>




static PlayerPosition playerPosition;
static Enemy enemyObject[10];
static FogDistance fogDistance;
static MapArray mapArray;

void dataStorage_init()
{
	
	playerPosition.x = 0;
	playerPosition.y = 0;

	fogDistance.fogStart = 0;
	fogDistance.fogEnd = 0;

	mapArray.width = 0;
	mapArray.height = 0;

}

void dataStorage_EnemyInit()
{
	char i,e,counter = 0;

	int width = dataStorage_getMapData().width;
	int height = dataStorage_getMapData().height;

	/*Initialization of default enemies without position*/
	/*Change the positions of enemies when needed to spawn*/
	for (i = 0; i < 10; i++)
	{

		dataStorage_setEnemyPosition(-1, -1, i);
		enemyObject[i].active = false;
		enemyObject[i].c_prevChar = 0;

	}
	
	for (i = 0; i < dataStorage_getMapData().width; i++)
	{
		for (e = 0; e < dataStorage_getMapData().height; e++)
		{
			if (dataStorage_getMapData().mapArray[i + e * width] == 3)
			{
				enemy_spawnEnemy(i, e, counter++, dataStorage_getMapData());

			}
			
		}
	}
	enemy_weightedMapInit(&mapArray);
	enemy_recursiveCheckPath(&mapArray, 5, 7, 1, 1);
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

void dataStorage_getMapSize(int *width, int *height)
{
	*width = mapArray.width;
	*height = mapArray.height;
}

/*Edit in the future when theresmore than 1 map*/
MapArray dataStorage_getMapData()
{
	return mapArray;
}

bool dataStorage_checkWall()
{
	switch (mapArray.mapArray[playerPosition.x + playerPosition.y * mapArray.width])
	{
		case 0:
			return false;
			break;

		case 1:
			return true;
			break;
	}
}

void dataStorage_clearDraw(int drawOrder)
{
	switch (drawOrder)
	{
	case 0:
		arrayReader_clear(0, mapArray.mapArray);
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;
	}
}

void dataStorage_draw(int drawOrder)
{
	switch (drawOrder)
	{
	case 0:
		arrayReader_draw(0, mapArray.mapArray);
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;
	}
}
