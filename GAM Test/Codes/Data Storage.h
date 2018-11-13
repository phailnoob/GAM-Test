
#ifndef DATASTORAGE_H

#define DATASTORAGE_H
#include <stdbool.h>

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

typedef struct PlayerPosition
{
	short x;
	short y;
}
PlayerPosition;

typedef struct Enemy
{
	int x;
	int y;
	bool active;
	bool seen;
}
Enemy;

typedef struct FogDistance
{
	int fogStart;
	int fogEnd;
}
FogDistance;

typedef struct Torch
{
	int x;
	int y;
	bool active;
}
Torch;


void dataStorage_init();
void dataStorage_EnemyInit(char playerX, char playerY);

void dataStorage_setPlayerPosition(int x, int y);
void dataStorage_getPlayerPosition(int *x, int *y);

void dataStorage_setEnemyPosition(int x, int y, short index);
void dataStorage_getEnemyPosition(int *x, int *y, short index);
void dataStorage_activateEnemy(char index);
Enemy* dataStorage_getEnemyObject(char index);

void dataStorage_setFogDistance(int start, int end);
void dataStorage_getFogDistance(int *start, int *end); 
void dataStorage_getMapSize(int *width, int *height);

void dataStorage_setMapData(char *arr, int width, int height);
void dataStorage_getMapData(int *width, int *height);
char dataStorage_getMapValue(int x, int y);
MapArray dataStorage_getMapDataOut();

bool dataStorage_checkWall();

void dataStorage_TorchInit();
void dataStorage_setTorchPos(int index, int x, int y);
void dataStorage_getTorchPos(int index, int *x, int *y);
Torch* dataStorage_getTorchObj(int index);

#endif
