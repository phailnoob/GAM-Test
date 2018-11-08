#pragma once

#include "Data Storage.h"
#include "Console.h"
#include <windows.h>
#include <stdio.h>
#include "Array Reader.h"
#include "SpriteReference.h"


void enemy_initPathNode(APathNode* Node);

void enemy_moveEnemy(char direction, char index, char *arr);

void enemy_spawnEnemy(char x, char y, char index, MapArray map);

void enemy_recursiveCheckPath(MapArray * levelmap, char nodeX, char nodeY, char currentWeight, char entry);
void enemy_setWallWeight(char val, MapArray * levelmap);
void enemy_Update(char index);


MapArray* enemy_getWeightMap();