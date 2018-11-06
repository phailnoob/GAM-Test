
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

typedef struct MapOffset
{
	int x;
	int y;
}
MapOffset;

static PlayerPosition playerPosition;
static FogDistance fogDistance;
static MapArray mapArray;

void dataStorage_init()
{
	playerPosition.x = playerPosition.y = 0;

	fogDistance.fogStart = fogDistance.fogEnd = 0;

	mapArray.width = mapArray.height = 0;
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

void dataStorage_getMapData(int *width, int *height)
{
	*width = mapArray.width;
	*height = mapArray.height;
}

char dataStorage_getMapValue(int x, int y)
{
	return mapArray.mapArray[x + y * mapArray.width];
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
