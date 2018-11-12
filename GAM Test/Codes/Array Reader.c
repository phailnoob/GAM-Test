
#include "Array Reader.h"
#include "Console.h"
#include "SpriteReference.h"
#include "Data Storage.h"
#include "Enemy.h"

static char *prevColor, *currColor, *prevMap, *currentMap;
static int width, height, i ,j, playerX, playerY, fogStart, fogEnd, distance, f, g, h, playerRange = 3;
static bool change;
Enemy *en;

void arrayReader_init()
{
	width = height = -1;
	i = j = f = g = h = -1;
	playerX = playerY = -1;
	fogStart = fogEnd = distance = -1;
}

/*---Returns squared value---*/
short arrayReader_checkDistance(short x1, short y1, short x2, short y2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void arrayReader_setMap(short size)
{
	free(prevColor);
	prevColor = malloc(size);

	free(currColor);
	currColor = malloc(size);

	free(prevMap);
	prevMap = malloc(size);

	free(currentMap);
	currentMap = malloc(size);

	memset(prevColor, -1, size);
	memset(prevMap, -1, size);
	memset(currColor, 0, size);

	dataStorage_getMapData(&width, &height);
	dataStorage_getPlayerPosition(&playerX, &playerY);

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
				currColor[i*height + j] = 7;
		}
	}
}

void arrayReader_draw()
{
	dataStorage_getPlayerPosition(&playerX, &playerY);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			change = false;

			if (j == playerX && i == playerY)
				currentMap[i * height + j] = spriteReference_getSprite(2);
			else if (currentMap[i * height + j] == spriteReference_getSprite(2))
				currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));

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
							break;
						}
						else if (currentMap[i * height + j] == spriteReference_getSprite(3))
							currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));
					}
				}
			}
			else
			{
				currColor[i*height + j] = 8;

				if (currentMap[i * height + j] == spriteReference_getSprite(3))
					currentMap[i * height + j] = spriteReference_getSprite(dataStorage_getMapValue(j, i));
			}

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
