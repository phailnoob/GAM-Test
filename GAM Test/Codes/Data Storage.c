
#include "Data Storage.h"
#include "Console.h"
#include "Array Reader.h"
#include <stdio.h>

typedef struct PlayerPosition
{
	int x;
	int y;
}
PlayerPosition;

typedef struct FogDistance
{
	int fogStart;
	int fogEnd;
}
FogDistance;

typedef struct MapArray
{
	char *mapArray;
	int width;
	int height;
}
MapArray;

static PlayerPosition playerPosition;
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
