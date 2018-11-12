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
#include <stdio.h>


/*FREE*/
/*Global weightmap array to be used by all enemy objects to calculate weight*/
static MapArray ma_WeightMap;

MapArray* enemy_getWeightMap()
{
	return &ma_WeightMap;
}

/*
Initialises the weighted map
*/
void enemy_weightedMapInit(MapArray * currentMap)
{
	/*FREE*/
	ma_WeightMap.mapArray = malloc(sizeof(*currentMap));
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
	if (ma_WeightMap.mapArray[0] != NULL)
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

			enemy_moveEnemy(direction, index, dataStorage_getMapDataOut().mapArray);
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

*/
void enemy_spawnEnemy(int x, int y,char index)
{
	dataStorage_setEnemyPosition(x, y, index);
		
	/*TEMP to test AI*/
	(*dataStorage_getEnemyObject(index)).active = true;
}


bool enemy_checkWall(char x, char y,MapArray* map)
{
	if (map->mapArray[x + y * map->width] == 1)
	{
		return true;
	}
	return false;
}


void enemy_Update(int index)
{
	if ((*dataStorage_getEnemyObject(index)).active)
	{
		enemy_enemyChase(index);
	}
}

void enemy_deactivateEnemy(int index)
{
	dataStorage_getEnemyObject(index)->active = false;
	dataStorage_getEnemyObject(index)->x = -1;
	dataStorage_getEnemyObject(index)->y = -1;
}



