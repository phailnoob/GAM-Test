/************************************************
Filename: Enemy.c
Author: Muhammad Adam Bin Mohamad Amin
DP Email: m.muhammadadambin@digipen.edu
Course: GAM100

Brief Description:
Functions for spawning and manipulating the enemy.
Includes pathfinding calculations.
*************************************************/

#include "Enemy.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "UI.h"
#include "PauseMenu.h"


/*Global weightmap array to be used by all enemy objects to calculate weight*/
MapArray ma_WeightMap;

const char * oofMessages[9] = { "Try placing down some torches.",
								"You can use traps to get rid of enemies.",
								"Don worri, ish sho shimple.",
								"It's still early for you to apply for withdrawal.",
								"There are only 2 actually useful tips.",
								"Noob mistake.",
								"if(youreBad) { gitGud() };",
								"Freshmen starts with F.",
								"GG! *FLIP TABLE*" };

MapArray* enemy_getWeightMap()
{
	return &ma_WeightMap;
}

/*
Initialises the weighted map
*/
void enemy_weightedMapInit(MapArray * currentMap)
{
	ma_WeightMap.mapArray = malloc((currentMap->width)*(currentMap->height));
	ma_WeightMap.width = currentMap->width;
	ma_WeightMap.height = currentMap->height;

	for (int i = 0; i < ma_WeightMap.height; i++)
	{
		for (int e = 0; e < ma_WeightMap.width; e++)
		{
			ma_WeightMap.mapArray[i*ma_WeightMap.width + e] = -5;
		}
	}
}

void enemy_weightedMapReset()
{
	if (ma_WeightMap.mapArray != NULL)
	{
		for (int i = 0; i < ma_WeightMap.height; i++)
		{
			for (int e = 0; e < ma_WeightMap.width; e++)
			{
				ma_WeightMap.mapArray[i*ma_WeightMap.width + e] = -5;
			}
		}
	}
}

/*Returns true if weight map contains specified value*/
bool enemy_checkWeightMapContainValue(char val)
{
	for (int i = 0; i < ma_WeightMap.height; i++)
	{
		for (int e = 0; e < ma_WeightMap.width; e++)
		{
			if (ma_WeightMap.mapArray[i*ma_WeightMap.width + e] == val)
			{
				return true;
			}
		}
	}
	return false;
}

char enemy_weightMapCheckTop(MapArray * levelmap,char nodeX, char nodeY,char currentWeight)
{
	if (ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width] != -5)
	{
		if (currentWeight < ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width]
			&& ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width] >= 0)
		{
			ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width] = currentWeight;
			return 0;
		}
		return -9;
	}
	if (levelmap->mapArray[nodeX + (nodeY - 1) * levelmap->width] == 1)
	{
		ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width] = -1;
		return -9;
	}
	else if (ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width] == -5)
	{
		ma_WeightMap.mapArray[nodeX + (nodeY - 1) * levelmap->width] = currentWeight;
	}
	return 0;
}

char enemy_weightMapCheckRight(MapArray * levelmap, char nodeX, char nodeY, char currentWeight)
{
	if (ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width] != -5)
	{
		if (currentWeight < ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width]
			&& ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width] >= 0)
		{
			ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width] = currentWeight;
			return 0;
		}
		return -9;
	}
	if (levelmap->mapArray[(nodeX + 1) + nodeY * levelmap->width] == 1)
	{
		ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width] = -1;
		return -9;
	}
	else if (ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width] == -5)
	{
		ma_WeightMap.mapArray[(nodeX + 1) + nodeY * levelmap->width] = currentWeight;
	}
	return 0;
}

char enemy_weightMapCheckBottom(MapArray * levelmap, char nodeX, char nodeY, char currentWeight)
{
	if (ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width] != -5)
	{
		if (currentWeight < ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width]
			&& ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width] >= 0)
		{
			ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width] = currentWeight;
			return 0;
		}
		return -9;
	}
	if (levelmap->mapArray[nodeX + (nodeY + 1) * levelmap->width] == 1)
	{
		ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width] = -1;
		return -9;
	}
	else if (ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width] == -5)
	{
		ma_WeightMap.mapArray[nodeX + (nodeY + 1) * levelmap->width] = currentWeight;
	}
	return 0;
}

char enemy_weightMapCheckLeft(MapArray * levelmap, char nodeX, char nodeY, char currentWeight)
{
	if (ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] != -5)
	{
		if (currentWeight < ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] 
			&& ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] >= 0)
		{
			ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] = currentWeight;
			return 0;
		}
		return -9;
	}
	if (levelmap->mapArray[(nodeX - 1) + nodeY * levelmap->width] == 1)
	{
		ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] = -1;
		return -9;
	}
	else if (ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] == -5)
	{
		ma_WeightMap.mapArray[(nodeX - 1) + nodeY * levelmap->width] = currentWeight;
	}
	return 0;
}


/*
Lets go on a magic carpet ride
*/
void enemy_recursiveCheckPath(MapArray * levelmap, char nodeX, char nodeY, char currentWeight,char entry)
{
	if (entry)
	{
		ma_WeightMap.mapArray[nodeX + nodeY * levelmap->width] = 0;
	}
	char up, down, left, right;

	if (nodeX >= 0 && nodeX < levelmap->width)
	{
		if (nodeY >= 0 && nodeY < levelmap->height)
		{
			if (nodeX == 0 && nodeY == 0)
			{
				enemy_weightMapCheckRight(levelmap, nodeX, nodeY, currentWeight);
				enemy_weightMapCheckBottom(levelmap, nodeX, nodeY, currentWeight);

				currentWeight++;
			}
			else if (nodeX == 0 && nodeY == (levelmap->height - 1))
			{
				enemy_weightMapCheckTop(levelmap, nodeX, nodeY, currentWeight);
				enemy_weightMapCheckRight(levelmap, nodeX, nodeY, currentWeight);

				currentWeight++;
			}
			else if (nodeX == (levelmap->width - 1) && nodeY == 0)
			{

				enemy_weightMapCheckBottom(levelmap, nodeX, nodeY, currentWeight);
				enemy_weightMapCheckLeft(levelmap, nodeX, nodeY, currentWeight);

				currentWeight++;
			}
			else if (nodeX == (levelmap->width - 1) && nodeY == (levelmap->height - 1))
			{
				enemy_weightMapCheckTop(levelmap, nodeX, nodeY, currentWeight);
				enemy_weightMapCheckLeft(levelmap, nodeX, nodeY, currentWeight);

				currentWeight++;
			}
			else
			{
				if (nodeX == 0)
				{
					up = enemy_weightMapCheckTop(levelmap, nodeX, nodeY, currentWeight);
					right = enemy_weightMapCheckRight(levelmap, nodeX, nodeY, currentWeight);
					down = enemy_weightMapCheckBottom(levelmap, nodeX, nodeY, currentWeight);

					currentWeight++;
					if (enemy_checkWeightMapContainValue(-5))
					{
						if(up != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY - 1, currentWeight,0);
						if(right != -9)
						enemy_recursiveCheckPath(levelmap, nodeX + 1, nodeY, currentWeight,0);
						if(down != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY + 1, currentWeight,0);
					}
				}
				else if (nodeX == (levelmap->width - 1))
				{
					up = enemy_weightMapCheckTop(levelmap, nodeX, nodeY, currentWeight);
					down = enemy_weightMapCheckBottom(levelmap, nodeX, nodeY, currentWeight);
					left = enemy_weightMapCheckLeft(levelmap, nodeX, nodeY, currentWeight);

					currentWeight++;
					if (enemy_checkWeightMapContainValue(-5))
					{
						if(up != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY - 1, currentWeight,0);
						if(down != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY + 1, currentWeight,0);
						if(left != -9)
						enemy_recursiveCheckPath(levelmap, nodeX - 1, nodeY, currentWeight,0);
					}
				}
				else if (nodeY == 0)
				{
					right = enemy_weightMapCheckRight(levelmap, nodeX, nodeY, currentWeight);
					down = enemy_weightMapCheckBottom(levelmap, nodeX, nodeY, currentWeight);
					left = enemy_weightMapCheckLeft(levelmap, nodeX, nodeY, currentWeight);

					currentWeight++;
					if (enemy_checkWeightMapContainValue(-5))
					{
						if(right != -9)
						enemy_recursiveCheckPath(levelmap, nodeX + 1, nodeY, currentWeight,0);
						if(down != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY + 1, currentWeight,0);
						if(left != -9)
						enemy_recursiveCheckPath(levelmap, nodeX - 1, nodeY, currentWeight,0);
					}
				}
				else if (nodeY == (levelmap->height - 1))
				{
					up = enemy_weightMapCheckTop(levelmap, nodeX, nodeY, currentWeight);
					right = enemy_weightMapCheckRight(levelmap, nodeX, nodeY, currentWeight);
					left = enemy_weightMapCheckLeft(levelmap, nodeX, nodeY, currentWeight);

					currentWeight++;
					if (enemy_checkWeightMapContainValue(-5))
					{
						if(up != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY - 1, currentWeight,0);
						if(right != -9)
						enemy_recursiveCheckPath(levelmap, nodeX + 1, nodeY, currentWeight,0);
						if(left != -9)
						enemy_recursiveCheckPath(levelmap, nodeX - 1, nodeY, currentWeight,0);
					}
				}
				else
				{
					up = enemy_weightMapCheckTop(levelmap, nodeX, nodeY, currentWeight);
					right = enemy_weightMapCheckRight(levelmap, nodeX, nodeY, currentWeight);
					down = enemy_weightMapCheckBottom(levelmap, nodeX, nodeY, currentWeight);
					left = enemy_weightMapCheckLeft(levelmap, nodeX, nodeY, currentWeight);

					currentWeight++;
					if (enemy_checkWeightMapContainValue(-5))
					{
						if(up != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY - 1, currentWeight,0);
						if(right != -9)
						enemy_recursiveCheckPath(levelmap, nodeX + 1, nodeY, currentWeight,0);
						if(down != -9)
						enemy_recursiveCheckPath(levelmap, nodeX, nodeY + 1, currentWeight,0);
						if(left != -9)
						enemy_recursiveCheckPath(levelmap, nodeX - 1, nodeY, currentWeight,0);
					}
				}
			}
		}
	}


}

void enemy_setWallWeight(char val,MapArray * levelmap)
{
	for (int y = 0; y < ma_WeightMap.height; y++)
	{
		for (int x = 0; x < ma_WeightMap.width; x++)
		{
			if (levelmap->mapArray[x + y * ma_WeightMap.width] == 1)
			{
				ma_WeightMap.mapArray[x + y * ma_WeightMap.width] = val;
			}
		}
	}
}

void enemy_enemyChase(char index)
{
	int lowestValDirection = 0,direction = -1,x,y,width,height;
	char i;
	if ((*dataStorage_getEnemyObject(index)).active)
	{
		if (!enemy_checkWeightMapContainValue(-5))
		{
			dataStorage_getEnemyPosition(&x, &y, index);
			dataStorage_getMapSize(&width, &height);

			if (y > 0)
			if (ma_WeightMap.mapArray[x + (y - 1) * width] >= 0)
			{
				lowestValDirection = ma_WeightMap.mapArray[x + (y - 1) * width];
				direction = 1;
			}
			else
			{
				lowestValDirection = 200;
			}

			if (x < width - 1)
			if (ma_WeightMap.mapArray[(x + 1) + y * width] >= 0)
			{
				if (lowestValDirection > ma_WeightMap.mapArray[(x + 1) + y * width])
				{
					lowestValDirection = ma_WeightMap.mapArray[(x + 1) + y * width];
					direction = 2;
				}
			}

			if (y < height - 1)
			if (ma_WeightMap.mapArray[x + (y + 1) * width] >= 0)
			{
				if (lowestValDirection > ma_WeightMap.mapArray[x + (y + 1) * width])
				{
					lowestValDirection = ma_WeightMap.mapArray[x + (y + 1) * width];
					direction = 3;
				}
			}

			if (x > 0)
			if (ma_WeightMap.mapArray[(x - 1) + y * width] >= 0)
			{
				
				if (lowestValDirection > ma_WeightMap.mapArray[(x - 1) + y * width])
				{
					lowestValDirection = ma_WeightMap.mapArray[(x - 1) + y * width];
					direction = 4;
				}
			}

			for (i = 0; i < 10; i++)
			{
				if (dataStorage_getEnemyObject(i)->active)
				{
					switch (direction)
					{
					case 1:
						if (dataStorage_getEnemyObject(i)->x == x && dataStorage_getEnemyObject(i)->y == (y - 1))
						{
							return;
						}
						break;
					case 2:
						if (dataStorage_getEnemyObject(i)->x == (x + 1) && dataStorage_getEnemyObject(i)->y == y)
						{
							return;
						}
						break;
					case 3:
						if (dataStorage_getEnemyObject(i)->x == x && dataStorage_getEnemyObject(i)->y == (y + 1))
						{
							return;
						}
						break;
					case 4:
						if (dataStorage_getEnemyObject(i)->x == (x - 1) && dataStorage_getEnemyObject(i)->y == y)
						{
							return;
						}
						break;
					}
				}
			}
			enemy_moveEnemy(direction, index, dataStorage_getMapDataOut()->mapArray);
		}
	}
}


void enemy_patrolEnemy(char index)
{
	Enemy* enemy = dataStorage_getEnemyObject(index);
	if (enemy->patrolling)
	{
		if (enemy->patrolDirection)/*Move towards direction 1*/
		{
			if (enemy->x == enemy->patrolx1 && enemy->y == enemy->patroly1)
			{
				enemy->patrolDirection = !enemy->patrolDirection;
			}
			else if (enemy->x - enemy->patrolx1 < 0)
			{
				enemy_moveEnemy(2, index, dataStorage_getMapDataOut()->mapArray);
			}
			else if (enemy->x - enemy->patrolx1 > 0)
			{
				enemy_moveEnemy(4, index, dataStorage_getMapDataOut()->mapArray);
			}
			else if (enemy->y - enemy->patroly1 < 0)
			{
				enemy_moveEnemy(3, index, dataStorage_getMapDataOut()->mapArray);
			}
			else if (enemy->y - enemy->patroly1 > 0)
			{
				enemy_moveEnemy(1, index, dataStorage_getMapDataOut()->mapArray);
			}
		}
		else/*Move towards direction 2*/
		{
			if (enemy->x == enemy->patrolx2 && enemy->y == enemy->patroly2)
			{
				enemy->patrolDirection = !enemy->patrolDirection;
			}
			else if (enemy->x - enemy->patrolx2 < 0)
			{
				enemy_moveEnemy(2, index, dataStorage_getMapDataOut()->mapArray);
			}
			else if (enemy->x - enemy->patrolx2 > 0)
			{
				enemy_moveEnemy(4, index, dataStorage_getMapDataOut()->mapArray);
			}
			else if (enemy->y - enemy->patroly2 < 0)
			{
				enemy_moveEnemy(3, index, dataStorage_getMapDataOut()->mapArray);
			}
			else if (enemy->y - enemy->patroly2 > 0)
			{
				enemy_moveEnemy(1, index, dataStorage_getMapDataOut()->mapArray);
			}
		}
	}
}


/*
Moves enemy in direction of
1= Up
2= Right
3= Down
4= Left
*/
void enemy_moveEnemy(int direction,int index, char *arr)
{
	int x, y,width,height;
	
	dataStorage_getEnemyPosition(&x, &y, index);
	dataStorage_getMapSize(&width, &height);
	if (x >= 0 && y >= 0)
	{
		switch (direction)
		{
		case 1:
			/*Checks to the top of the enemy is wall*/
			if (y > 0)
				if (arr[x + (y - 1) * width] != 1)
				{
					dataStorage_setEnemyPosition(x, --y, index);
				}
			break;
		case 2:
			/*Checks to the right of the enemy is wall*/
			if(x < width - 1)
				if (arr[(x + 1) + y * width] != 1)
				{
					dataStorage_setEnemyPosition(++x, y, index);
				}
			break;
		case 3:
			/*Checks to the bottom of the enemy is wall*/
			if (y < height - 1)
				if (arr[x + (y + 1) * width] != 1)
				{
					dataStorage_setEnemyPosition(x, ++y, index);
				}
				
			break;
		case 4:
			/*Checks to the left of the enemy is wall*/
			if (x > 0)
				if (arr[(x - 1) + y * width] != 1)
				{
					dataStorage_setEnemyPosition(--x, y, index);
				}
			break;
		}
	}
}

/*
Parameters
x - x Spawn coordinate
y - y Spawn coordinate
index - Enemy index
patrolling - Set true if patrolling
x1,x2,y1,y2 - Set 2 patrol points. If not patrolling set to -1
*/
void enemy_spawnEnemy(int x, int y,char index,bool patrolling,int x1,int y1, int x2, int y2)
{
	dataStorage_setEnemyPosition(x, y, index);
	Enemy *enemy = dataStorage_getEnemyObject(index);

	enemy->patrolling = patrolling;
	enemy->patrolx1 = x1;
	enemy->patrolx2 = x2;
	enemy->patroly1 = y1;
	enemy->patroly2 = y2;
	enemy->active = true;
}


float enemy_returnDistanceToPlayer(Enemy *enemyC)
{
	float distance = -1.0f;
	int x, y;
	dataStorage_getPlayerPosition(&x, &y);
	if(enemyC->x != 0 || enemyC->y != 0 || y != 0 || x != 0)
	distance = (float)((enemyC->x - x)*(enemyC->x - x) + (enemyC->y - y)*(enemyC->y - y));

	return distance;
}

/*
Line Of Sight

Checks line of sight from enemy input to player
Returns false if blocked by a wall
True if LoS touches the player
*/
bool enemy_isInlineOfSight(Enemy * enemyC)
{
	int x, y;
	dataStorage_getPlayerPosition(&x, &y);

	int x0 = enemyC->x, y0 = enemyC->y;

	int dx = abs(x - x0), sx = x0 < x ? 1 : -1;
	int dy = abs(y - y0), sy = y0 < y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;) 
	{
		if (dataStorage_getMapValue(x0, y0) == 1)
		{
			return false;
		}
		if (x0 == x && y0 == y) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
	return true;

}

/*
Function that returns if an enemy collided with a player
*/
bool enemy_playerCollision(char index,int * playerX, int * playerY)
{
	Enemy * enemy = dataStorage_getEnemyObject(index);

	if (*playerX == enemy->x && *playerY == enemy->y)
	{
		return true;
	}
	return false;
}


bool enemy_checkWall(char x, char y,MapArray* map)
{
	if (map->mapArray[x + y * map->width] == 1)
	{
		return true;
	}
	return false;
}

void enemy_drawDebugWeight()
{
	for (int i = 0; i < ma_WeightMap.height; i++)
	{
		for (int j = 0; j < ma_WeightMap.width; j++)
		{

			console_setCursorPosition(j *3, i * 3);
			printf("%3d", ma_WeightMap.mapArray[j + i * ma_WeightMap.width]);
		}

	}
}


void enemy_Update(char index,Enemy* enemyObj)
{
	int playerx, playery;
	dataStorage_getPlayerPosition(&playerx, &playery);
	if ((*enemyObj).active)
	{
		if (enemyObj->seen)
		{
			enemy_enemyChase(index);
			if (enemy_playerCollision(index, &playerx, &playery))
			{
				/*COLLISION*/
				if(*dataStorage_getAliveBool())
				if (*dataStorage_getLives() >= 0)
				{
					UI_redrawSkulls();
					if (--(*dataStorage_getLives()) == 0)
					{
						*dataStorage_getAliveBool() = false;
					}
					else
					{
						char len = (char)strlen(oofMessages[rand() % 9]);
						PauseClearScreen();
						
						console_setCursorPosition(console_getConsoleWidth() / 2 - (len/2), console_getConsoleHeight() / 2);
						printf("%s", oofMessages[rand()%9]);
						Sleep(2000);
						PauseClearScreen();
						game_RestartCurrentMap();
					}
				}
			}
		}
		else
		{
			if (enemyObj->patrolling)
			{
				enemy_patrolEnemy(index);
			}
			if (enemy_returnDistanceToPlayer(enemyObj) <= 9.0f)
			{
				if (enemy_isInlineOfSight(enemyObj))
				{
					enemyObj->seen = true;
				}
			}
		}
	}
}



void enemy_deactivateEnemy(char index)
{
	dataStorage_getEnemyObject(index)->active = false;
	dataStorage_getEnemyObject(index)->x = -1;
	dataStorage_getEnemyObject(index)->y = -1;
}

void enemy_Destructor()
{
	free(ma_WeightMap.mapArray);
}

