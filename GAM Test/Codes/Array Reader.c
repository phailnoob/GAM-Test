
#include "Array Reader.h"
#include "Console.h"
#include "SpriteReference.h"
#include "Data Storage.h"
#include "Enemy.h"

static char *prevColor, *currColor, *prevMap, *currentMap;
static int width, height, i ,j, playerX, playerY, fogStart, fogEnd, distance, g, f;
static bool change;

void arrayReader_init()
{
	width = height = -1;
	i = j = g = f = -1;
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

<<<<<<< HEAD
	currentMap[playerY * height + playerX] = spriteReference_getSprite(2);
=======
	case 3:
/*
		dataStorage_getMapSize(&width, &height);
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				console_draw(i, j, enemy_getWeightMap()->mapArray[i + j * width]);
			}
		}*/
		break;
>>>>>>> 7996e2f02c8af5b63244ff00b8836c7237ae0e20

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


			if (arrayReader_checkDistance(j, i, playerX, playerY) < 9)
				currColor[i*height + j] = 7;
			else
				currColor[i*height + j] = 0;

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
