
#ifndef DATASTORAGE_H

#define DATASTORAGE_H
#include <stdbool.h>


/*
Moves enemy in direction of
1= Left
2= Right
3= Up
4= Down
*/
typedef struct APathNode
{
	char direction;
	unsigned char X;
	unsigned char Y;
	bool active;
} APathNode;

typedef struct MapArray
{
	char *mapArray;
	int width;
	int height;
}
MapArray;

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
	char c_prevChar;
	bool active;
}
Enemy;


typedef struct FogDistance
{
	int fogStart;
	int fogEnd;
}
FogDistance;

void dataStorage_init();
void dataStorage_EnemyInit();

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

#endif
