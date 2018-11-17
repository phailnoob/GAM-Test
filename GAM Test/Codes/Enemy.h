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

/*
Parameters
x - x Spawn coordinate
y - y Spawn coordinate
index - Enemy index
patrolling - Set true if patrolling
x1,x2,y1,y2 - Set 2 patrol points. If not patrolling set to -1
*/
void enemy_spawnEnemy(int x, int y, char index, bool patrolling, int x1, int y1, int x2, int y2);

/*

Function that checks if the enemy's position is over the player's position
*/
bool enemy_playerCollision(char index, int * playerX, int * playerY);


/*
Lets go on a magic carpet ride
*/
void enemy_recursiveCheckPath(MapArray * levelmap, char nodeX, char nodeY, char currentWeight, char entry);


/*
Sets all wall objects detected from the mapArray as val
*/
void enemy_setWallWeight(char val, MapArray * levelmap);

/*
Enemy Update Loop
*/
void enemy_Update(char index, Enemy* enemyObj);

/*
Resets the weighted map to -5. -5 is the condition to keep calling enemy_recursiveCheckPath
*/
void enemy_weightedMapReset();

/*
Call this function in the main Destructor method & between any transitions
FREE
*/
void enemy_Destructor();

/*
Debug printing out the weight map at the topleft corner of the screen
*/
void enemy_drawDebugWeight();

/*
Accessor function that returns the weight map
*/
MapArray* enemy_getWeightMap();