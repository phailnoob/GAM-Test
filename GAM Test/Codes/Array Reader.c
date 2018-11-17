
#include "Array Reader.h"
#include "Console.h"
#include "SpriteReference.h"
#include "Data Storage.h"
#include "Enemy.h"
#include "Torch.h"
#include "Trap.h"

#include <stdlib.h>

static char *prevColor, *currColor, *prevMap, *currentMap;
static int width, height, i ,j, playerX, playerY, fogStart, fogEnd, distance, f, g, h, playerRange = 3;
static bool change;
Enemy *en;

Torch *torch;
static int k, torchX, torchY, torchRange;
bool enemySeen;

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
	bool enemySeen = false;
}

/*---Returns squared value---*/
short arrayReader_checkDistance(short x1, short y1, short x2, short y2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void arrayReader_setMap(short size)
{
	prevColor = malloc(size);

	currColor = malloc(size);

	prevMap = malloc(size);

	currentMap = malloc(size);

	memset(prevColor, -1, size);
	memset(prevMap, -1, size);
	memset(currColor, 0, size);

	dataStorage_getMapData(&width, &height);
	dataStorage_getPlayerPosition(&playerX, &playerY);

	dataStorage_getExitPos(&exitX, &exitY);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			currentMap[i*height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));
		}
	}

	currentMap[playerY * height + playerX] = spriteReference_getSprite(2);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (arrayReader_checkDistance(j, i, playerX, playerY) < 9)
				currColor[i*height + j] = 15;
			else
				currColor[i*height + j] = 8;
		}
	}

	for (k = 0; k < 5; ++k)
		destroyTorch(k);

	for (a = 0; a < 5; ++a)
		destroyTrap(a);


}

void arrayReader_draw()
{
	dataStorage_getPlayerPosition(&playerX, &playerY);
	dataStorage_getExitPos(&exitX, &exitY);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			change = false;

			currColor[i*height + j] = 8;
			enemySeen = false;

			currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));

			if (exitY == i && exitX == j)
				currentMap[i * height + j] = spriteReference_getSprite(5);

			if (arrayReader_checkDistance(j, i, playerX, playerY) < playerRange * playerRange)
			{
				currColor[i*height + j] = 15;

				for (h = 0; h < 10; h++)
				{
					en = dataStorage_getEnemyObject((char)h);
					if (en->active)
					{
						dataStorage_getEnemyPosition(&f, &g, (short)h);
						if (j == f && i == g)
						{
							currentMap[i * height + j] = spriteReference_getSprite(3);

							if (en->seen)
								currColor[i * height + j] = 12;
							else
								currColor[i * height + j] = 14;
							break;
						}
						else if (currentMap[i * height + j] == spriteReference_getSprite(3))
							currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));
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
						en = dataStorage_getEnemyObject((char)h);
						if (en->active)
						{
							dataStorage_getEnemyPosition(&f, &g, (short)h);
							if (j == f && i == g)
							{
								currentMap[i * height + j] = spriteReference_getSprite(3);

								if (trapX == f && trapY == g)
								{
									enemy_deactivateEnemy(h);
									destroyTrap(a);
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

			for (k = 0; k < 5; ++k)
			{
				torch = dataStorage_getTorchObj(k);
				dataStorage_getTorchPos(k, &torchX, &torchY);

				if (torch->active)
				{
					if (arrayReader_checkDistance(j, i, torchX, torchY) < torchRange * torchRange)
					{
						currColor[i*height + j] = 15;

						for (h = 0; h < 10; h++)
						{
							en = dataStorage_getEnemyObject((char)h);
							if (en->active)
							{
								dataStorage_getEnemyPosition(&f, &g, (short)h);
								if (j == f && i == g)
								{
									currentMap[i * height + j] = spriteReference_getSprite(3);
									break;
								}
								else if (currentMap[i * height + j] == spriteReference_getSprite(3))
									currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));
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

			if (currentMap[i*height + j] != prevMap[i*height + j])
			{
				prevMap[i*height + j] = currentMap[i*height + j];
				change = true;
			}

			if (currColor[i*height + j] != prevColor[i*height + j])
			{
				prevColor[i*height + j] = currColor[i*height + j];
				change = true;
			}

			if (change)
				console_draw((console_getConsoleWidth() - width) / 2 + j,
					(console_getConsoleHeight() - height) / 2 + i,
					currentMap[i*height + j],
					currColor[i*height + j]);
		}
	}
}

void arrayReader_Destructor()
{
	free(prevColor);

	free(currColor);

	free(prevMap);

	free(currentMap);
}