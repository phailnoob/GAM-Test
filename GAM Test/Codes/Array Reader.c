
#include "Array Reader.h"
#include "Console.h"
#include "SpriteReference.h"
#include "Data Storage.h"
#include "Enemy.h"
#include "Torch.h"
#include "Trap.h"

#include <stdlib.h>
#include <string.h>

static char *currColor, *currentMap;
static int width, height, i, j, playerX, playerY, fogStart, fogEnd, distance, f, g, h, playerRange = 3;
Enemy *en;

static bool change, initialDraw = false;

Torch *torch;
static int k, torchX, torchY, torchRange;

Trap *trap;
static int a, trapX, trapY;
static int exitX, exitY;

void arrayReader_init()
{
	width = height = -1;
	i = j = f = g = h = k = a = -1;
	torchX = torchY = -1;
	torchRange = 5;
	playerX = playerY = -1;
	fogStart = fogEnd = distance = -1;
//	enemySeen = false;
}

/*---Returns squared value---*/
int arrayReader_checkDistance(int x1, int y1, int x2, int y2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void arrayReader_setMap(int size)
{
	currColor = malloc(size);

	currentMap = malloc(size);

	dataStorage_getMapData(&width, &height);
	dataStorage_getPlayerPosition(&playerX, &playerY);

	dataStorage_getExitPos(&exitX, &exitY);
}

void arrayReader_draw()
{
	dataStorage_getPlayerPosition(&playerX, &playerY);
	dataStorage_getExitPos(&exitX, &exitY);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			currColor[i*height + j] = 8;

			currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));


			if (arrayReader_checkDistance(j, i, playerX, playerY) < playerRange * playerRange)
			{
				currColor[i*height + j] = 15;

				if (exitY == i && exitX == j)
				{
					currentMap[i * height + j] = spriteReference_getSprite(5);
					currColor[i*height + j] = 10;
				}
				for (h = 0; h < 10; h++)
				{
					en = dataStorage_getEnemyObject(h);
					if (en->active)
					{
						dataStorage_getEnemyPosition(&f, &g, h);
						if (j == f && i == g)
						{
							currentMap[i * height + j] = spriteReference_getSprite(3);

							if (en->seen)
								currColor[i * height + j] = 12;
							else
								currColor[i * height + j] = 14;
							break;
						}
					}
				}
			}

			
			
			for (a = 0; a < 5; ++a)
			{
				trap = dataStorage_getTrapObj(a);
				dataStorage_getTrapPos(a, &trapX, &trapY);

				if (trap->active)
				{
					for (h = 0; h < 10; h++)
					{
						en = dataStorage_getEnemyObject(h);
						if (en->active)
						{
							dataStorage_getEnemyPosition(&f, &g, (short)h);
							if (j == f && i == g)
							{
								//currentMap[i * height + j] = spriteReference_getSprite(3);

								if (trapX == f && trapY == g)
								{
									enemy_deactivateEnemy((char)h);
									placeTrap(a, -1, -1);
									break;
								}

								break;
							}

							else if (currentMap[i * height + j] == spriteReference_getSprite(3))
								currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));
						}
					}

					if (j == trapX && i == trapY)
					{
						currentMap[i * height + j] = spriteReference_getSprite(6);
						break;
					}
				}
			}
			if (arrayReader_checkDistance(j, i, playerX, playerY) >= playerRange * playerRange &&
				arrayReader_checkDistance(j, i, playerX, playerY) < torchRange * torchRange)
			{
				currColor[i*height + j] = 7;
			}
			for (k = 0; k < 5; ++k)
			{
				torch = dataStorage_getTorchObj(k);
				dataStorage_getTorchPos(k, &torchX, &torchY);

				if (torch->active)
				{
					if (arrayReader_checkDistance(j, i, torchX, torchY) < torchRange * torchRange)
					{
						currColor[i*height + j] = 15;

						if (exitY == i && exitX == j)
						{
							currentMap[i * height + j] = spriteReference_getSprite(5);
							currColor[i*height + j] = 10;
						}
						for (h = 0; h < 10; h++)
						{
							en = dataStorage_getEnemyObject(h);
							if (en->active)
							{
								dataStorage_getEnemyPosition(&f, &g, h);
								if (j == f && i == g)
								{
									currentMap[i * height + j] = spriteReference_getSprite(3);
									if (en->seen)
										currColor[i * height + j] = 12;
									else
										currColor[i * height + j] = 14;
									break;
								}
							}
						}
					}

					if (j == torchX && i == torchY)
					{
						currentMap[i * height + j] = spriteReference_getSprite(4);
						break;
					}
				}
			}

			


			/* draw player */
			if (j == playerX && i == playerY)
				currentMap[i * height + j] = spriteReference_getSprite(2);

				console_draw((console_getConsoleWidth() - width) / 2 + j + 18,
				(console_getConsoleHeight() - height) / 2 + i + 2,
					currentMap[i*height + j],
					currColor[i*height + j]);

			
		}
	}
}

void arrayReader_Destructor()
{
	free(currColor);

	free(currentMap);
}

void arrayReader_setInitialDraw(bool someBool)
{
	initialDraw = someBool;
}