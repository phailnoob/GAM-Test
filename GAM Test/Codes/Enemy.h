#pragma once

#include "Data Storage.h"
#include "Console.h"
#include <windows.h>
#include <stdio.h>
#include "Array Reader.h"
#include "SpriteReference.h"


/*
---Enemy Movement Direction---
1 - Left
2 - Right
3 - Up
4 - Down
*/
void enemy_moveEnemy(int direction, int index, char *arr);

void enemy_spawnEnemy(int x, int y, char index);

void enemy_recursiveCheckPath(MapArray * levelmap, char nodeX, char nodeY, char currentWeight, char entry);
void enemy_setWallWeight(char val, MapArray * levelmap);
void enemy_Update(char index, Enemy* enemyObj);
void enemy_weightedMapReset();
void enemy_Destructor();
void enemy_drawDebugWeight();

MapArray* enemy_getWeightMap();